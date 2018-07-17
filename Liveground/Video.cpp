/*
 *
 * Getting the SDL Window behind the desktop icons based on code by Gerald Degeneve
 * Displaying video to SDL window from FFMPEG based on code from Stephen Dranger
 *
 */

#include "Video.h"
#include <Windows.h>
#include <timeapi.h>
#include <thread>
#include <SDL.h>
#include <SDL_syswm.h>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

HWND workerWindow;
BOOL CALLBACK enumWindowsFunc(__in const HWND tophandle, __in LPARAM topparamhandle) {
	const HWND p = FindWindowEx(tophandle, 0, L"SHELLDLL_DefView", 0);

	if (p != 0)
		// Gets the workerWindow Window after the current one.
		workerWindow = FindWindowEx(0, tophandle, L"workerW", 0);

	return true;
}

namespace Video {
	// Declare variables for the video
	SDL_Window *window = NULL;
	AVCodecContext *pCodecCtx = NULL;
	AVFormatContext *pFormatCtx = NULL;
	Uint8 *yPlane, *uPlane, *vPlane;
	AVFrame *pFrame = NULL;
	int videoStream;
	int uvPitch;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	struct SwsContext *sws_ctx = NULL;
	short timeToWait;
	bool stop;
	std::thread *play;

	bool openFile(const char *filePath) {
		// Open video file
		if (avformat_open_input(&pFormatCtx, filePath, NULL, NULL) != 0)
			return false; // Couldn't open file

		av_dump_format(pFormatCtx, 0, filePath, 0);

		return true;
	}

	bool initalizeWindow() {
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) return false;

		// Find screen resolution
		RECT desktop;
		// Get a handle to the desktop window
		const HWND hDesktop = GetDesktopWindow();
		// Get the size of screen to the variable desktop
		GetWindowRect(hDesktop, &desktop);
		// The top left corner will have coordinates (0,0)
		// and the bottom right corner will have coordinates
		// (horizontal, vertical)

		// Make a screen to put our video
		window = SDL_CreateWindow(
			"Liveground",
			0,
			0,
			desktop.right,
			desktop.bottom,
			SDL_WINDOW_BORDERLESS
		);

		if (!window) return false;

		// Set window as background
		SDL_SysWMinfo systemInfo;
		SDL_VERSION(&systemInfo.version);
		if (!SDL_GetWindowWMInfo(window, &systemInfo))
			return false;
		const HWND progman = FindWindow(L"Progman", NULL);
		SendMessageTimeout(progman, 0x052C, 0, 0, 0, 1000, 0);
		if (!EnumWindows(enumWindowsFunc, 0)) return false;
		SetParent(systemInfo.info.win.window, workerWindow);

		return true;
	}

	bool initalizeVideo() {
		/// TODO: Add hardware acceleration

		// Retrieve stream information
		if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
			return false; // Couldn't find stream information

						  // Find the first video stream
		videoStream = -1;
		for (unsigned i = 0; i < pFormatCtx->nb_streams; i++)
			if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
				videoStream = i;
				break;
			}
		if (videoStream == -1)
			return false; // Didn't find a video stream

						  // Get a pointer to the codec context for the video stream
		AVCodecContext *pCodecCtxOrig = pFormatCtx->streams[videoStream]->codec;

		AVCodec *pCodec = avcodec_find_decoder(pCodecCtxOrig->codec_id);
		if (!pCodec) return false;

		// Copy context
		pCodecCtx = avcodec_alloc_context3(pCodec);
		if (avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) return false; // Error copying codec context

																			   // Open codec
		if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) return false; // Could not open codec

																	  // Allocate video frame
		pFrame = av_frame_alloc();

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (!renderer) return false;

		// Allocate a place to put our YUV image on that screen
		texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_YV12,
			SDL_TEXTUREACCESS_STREAMING,
			pCodecCtx->width,
			pCodecCtx->height
		);
		if (!texture)
			return false;

		// Initialize SWS context for software scaling
		sws_ctx = sws_getContext(
			pCodecCtx->width, pCodecCtx->height,
			pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
			AV_PIX_FMT_YUV420P,
			SWS_BILINEAR,
			NULL,
			NULL,
			NULL
		);

		// Set up YV12 pixel array (12 bits per pixel)
		const size_t yPlaneSz = pCodecCtx->width * pCodecCtx->height;
		const size_t uvPlaneSz = pCodecCtx->width * pCodecCtx->height / 4;
		yPlane = static_cast<Uint8*>(malloc(yPlaneSz));
		uPlane = static_cast<Uint8*>(malloc(uvPlaneSz));
		vPlane = static_cast<Uint8*>(malloc(uvPlaneSz));
		if (!yPlane || !uPlane || !vPlane)
			return false;

		uvPitch = pCodecCtx->width / 2;

		// Make time functions more accurate
		timeBeginPeriod(1);
		timeEndPeriod(1);

		timeToWait = 1000 / (pFormatCtx->streams[videoStream]->avg_frame_rate.num / pFormatCtx->streams[videoStream]->avg_frame_rate.den);    // Doesn't work sometimes, divides by zero

		avcodec_close(pCodecCtxOrig); // avcodec_free_context causes errors

		return true;
	}

	int decode(AVCodecContext *avctx, AVFrame *frame, int *got_frame, AVPacket *pkt) {
		int ret;

		*got_frame = 0;

		if (pkt) {
			ret = avcodec_send_packet(avctx, pkt);
			// In particular, we don't expect AVERROR(EAGAIN), because we read all
			// decoded frames with avcodec_receive_frame() until done.
			if (ret < 0)
				return ret == AVERROR_EOF ? 0 : ret;
		}

		ret = avcodec_receive_frame(avctx, frame);
		if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
			return ret;
		if (ret >= 0)
			*got_frame = 1;

		return 0;
	}

	bool playVideo() {
		int frameFinished = 0;
		AVPacket packet;

		while (!stop) {
			av_seek_frame(pFormatCtx, -1, 0, NULL);
			Uint32 lastTime = SDL_GetTicks();

			// Play video
			while (av_read_frame(pFormatCtx, &packet) >= 0 && !stop) {

				// Check for packet from video stream
				if (packet.stream_index == videoStream) {
					// Decode video frame
					decode(pCodecCtx, pFrame, &frameFinished, &packet);

					//avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

					// Check for video frame
					if (frameFinished) {
						AVFrame pict;
						pict.data[0] = yPlane;
						pict.data[1] = uPlane;
						pict.data[2] = vPlane;
						pict.linesize[0] = pCodecCtx->width;
						pict.linesize[1] = uvPitch;
						pict.linesize[2] = uvPitch;

						// Convert the image into YUV format that SDL uses
						sws_scale(sws_ctx, static_cast<uint8_t const* const*>(pFrame->data), pFrame->linesize, 0, pCodecCtx->height, pict.data, pict.linesize);

						SDL_UpdateYUVTexture(
							texture,
							NULL,
							yPlane,
							pCodecCtx->width,
							uPlane,
							uvPitch,
							vPlane,
							uvPitch
						);

						SDL_RenderClear(renderer);
						SDL_RenderCopy(renderer, texture, NULL, NULL);

						// If the frame hasn't been displayed long enough then wait
						// Yes I know that this is probably the worst way to do it but it's the only way I could think of
						while (SDL_GetTicks() < lastTime + timeToWait && !stop) { Sleep(1); } // This is kind of inaccurate, but an empty while loop is too CPU hungry and Sleep is too inaccurate waiting for a specific time.

																							  // LAST FRAME END
						SDL_RenderPresent(renderer);    // Present frame to screen
														// NEXT FRAME BEGIN

						lastTime = SDL_GetTicks();
					}
				}
				// Free the packet that was allocated by av_read_frame
				av_packet_unref(&packet);
			}
			av_packet_unref(&packet);
		}
		return true;
	}

	void startVideoThread() {
		play = new std::thread(playVideo);
	}

	void stopVideoThread() {
		stop = true;
		play->join();
		delete play;
	}

	bool closeVideo() {
		// Free the YUV frame
		av_frame_free(&pFrame);
		free(yPlane);
		free(uPlane);
		free(vPlane);

		// Close the codec
		avcodec_free_context(&pCodecCtx);

		sws_freeContext(sws_ctx);

		// Close the video file
		avformat_close_input(&pFormatCtx);

		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(texture);
		SDL_DestroyWindow(window);

		SDL_Quit();

		//CloseWindow(workerWindow);

		return true;
	}
}