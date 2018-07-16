#include "Window.h"
#include "Video.h"
using namespace System;
using namespace System::Windows::Forms;

#undef main
[STAThread]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Liveground::Window window;
	Application::Run(%window);
	return 0;
}

namespace Liveground {
	void promptFile(System::Windows::Forms::OpenFileDialog^ fileDiaglog, System::Windows::Forms::TextBox^ textBox) {
		fileDiaglog->ShowDialog();
		textBox->Text = fileDiaglog->FileName;
	}
	void removeBackground(System::Windows::Forms::Button^ close, System::Windows::Forms::ToolStripMenuItem^ remove) {
		/// TODO: Change background to normal background and remove program from startup

		Video::stopVideoThread();

		Video::closeVideo();

		close->Enabled = false;
		remove->Enabled = false;
	}

	System::Void Window::M_openVideo_Click(System::Object^ sender, System::EventArgs^ e) {
		promptFile(F_dialog, T_filePath);
	}
	System::Void Window::M_remove_Click(System::Object^ sender, System::EventArgs^ e) {
		removeBackground(B_remove, M_remove);
	}
	System::Void Window::M_uninstall_Click(System::Object^ sender, System::EventArgs^ e) {
		// TODO: Create an installer and uninstaller
	}
	System::Void Window::M_exit_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}
	System::Void Window::M_help_Click(System::Object^ sender, System::EventArgs^ e) {
		/// TODO: Change URL to an actual help page
		System::Diagnostics::Process::Start("https://www.github.com/Skyluker4/Liveground");
	}
	System::Void Window::M_update_Click(System::Object^ sender, System::EventArgs^ e) {
		// TODO: Contact some sort of server and check for updates
	}
	System::Void Window::M_about_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show(this, "Version 0.1\nhttps://www.github.com/Skyluker4/Liveground\nThis software is licensed under the GNU GPLv3 License.", "About");
	}

	System::Void Window::T_filePath_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		if (T_filePath->TextLength == 0)
			Window::L_pathHint->Show();
		else
			Window::L_pathHint->Hide();
	}
	System::Void Window::B_browse_Click(System::Object^ sender, System::EventArgs^ e) {
		promptFile(F_dialog, T_filePath);
	}
	System::Void Window::B_set_Click(System::Object^ sender, System::EventArgs^ e) {
		// Create startup entry (service)
		// Leave data for filename for startup

		if (!Video::openFile((char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(T_filePath->Text).ToPointer())) {
			return;
		}
		if (!Video::initalizeWindow()) {
			return;
		}
		if (!Video::initalizeVideo()) {
			return;
		}
		Video::startVideoThread();

		B_remove->Enabled = true;
		M_remove->Enabled = true;
	}
	System::Void Window::B_remove_Click(System::Object^ sender, System::EventArgs^ e) {
		removeBackground(B_remove, M_remove);
	}
}