#pragma once

namespace Video {
	bool openFile(const char *filePath);
	bool initalizeWindow();
	bool initalizeVideo();
	void startVideoThread();
	void stopVideoThread();
	bool closeVideo();
}