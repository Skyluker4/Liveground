#pragma once

/// TODO: Make logo

namespace Liveground {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// The main window
	/// </summary>
	public ref class Window : public System::Windows::Forms::Form {
	private:
		//Create controls
		System::Windows::Forms::TextBox^ T_filePath;
		System::Windows::Forms::Label^ L_pathHint;
		System::Windows::Forms::OpenFileDialog^  F_dialog;
		System::Windows::Forms::Button^ B_browse;
		System::Windows::Forms::Button^ B_set;
		System::Windows::Forms::Button^ B_remove;

		System::Windows::Forms::MenuStrip^ M_Strip;

		System::Windows::Forms::ToolStripMenuItem^ M_listFile;
		System::Windows::Forms::ToolStripMenuItem^ M_openVideo;
		System::Windows::Forms::ToolStripMenuItem^ M_remove;
		System::Windows::Forms::ToolStripMenuItem^ M_uninstall;
		System::Windows::Forms::ToolStripSeparator^ M_seperateFile;
		System::Windows::Forms::ToolStripMenuItem^ M_exit;

		System::Windows::Forms::ToolStripMenuItem^ M_listHelp;
		System::Windows::Forms::ToolStripMenuItem^ M_help;
		System::Windows::Forms::ToolStripSeparator^ M_seperateHelp;
		System::Windows::Forms::ToolStripMenuItem^ M_update;
		System::Windows::Forms::ToolStripMenuItem^ M_about;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::IContainer^ components;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void) {
			this->F_dialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->B_set = (gcnew System::Windows::Forms::Button());
			this->B_remove = (gcnew System::Windows::Forms::Button());
			this->B_browse = (gcnew System::Windows::Forms::Button());
			this->T_filePath = (gcnew System::Windows::Forms::TextBox());
			this->L_pathHint = (gcnew System::Windows::Forms::Label());
			this->M_Strip = (gcnew System::Windows::Forms::MenuStrip());
			this->M_listFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->M_openVideo = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->M_remove = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->M_uninstall = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->M_seperateFile = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->M_exit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->M_listHelp = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->M_help = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->M_seperateHelp = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->M_update = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->M_about = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->M_Strip->SuspendLayout();
			this->SuspendLayout();
			// 
			// F_dialog
			// 
			this->F_dialog->Filter = L"Videos (*.amv, *.avi, *.mp4, *.mpg, *.webm, *.wmv)|*.amv;*.avi;*.mp4;*.mpg;*.webm"
				L";*.wmv";
			// 
			// B_set
			// 
			this->B_set->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->B_set->Location = System::Drawing::Point(75, 53);
			this->B_set->Name = L"B_set";
			this->B_set->Size = System::Drawing::Size(360, 25);
			this->B_set->TabIndex = 2;
			this->B_set->Text = L"Confirm";
			this->B_set->UseVisualStyleBackColor = true;
			this->B_set->Click += gcnew System::EventHandler(this, &Window::B_set_Click);
			// 
			// B_remove
			// 
			this->B_remove->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->B_remove->Enabled = false;
			this->B_remove->Location = System::Drawing::Point(12, 53);
			this->B_remove->Name = L"B_remove";
			this->B_remove->Size = System::Drawing::Size(57, 25);
			this->B_remove->TabIndex = 3;
			this->B_remove->Text = L"Remove";
			this->B_remove->UseVisualStyleBackColor = true;
			this->B_remove->Click += gcnew System::EventHandler(this, &Window::B_remove_Click);
			// 
			// B_browse
			// 
			this->B_browse->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->B_browse->Location = System::Drawing::Point(383, 27);
			this->B_browse->Name = L"B_browse";
			this->B_browse->Size = System::Drawing::Size(52, 20);
			this->B_browse->TabIndex = 0;
			this->B_browse->Text = L"Browse";
			this->B_browse->UseVisualStyleBackColor = true;
			this->B_browse->Click += gcnew System::EventHandler(this, &Window::B_browse_Click);
			// 
			// T_filePath
			// 
			this->T_filePath->AllowDrop = true;
			this->T_filePath->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->T_filePath->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::SuggestAppend;
			this->T_filePath->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::FileSystem;
			this->T_filePath->Location = System::Drawing::Point(12, 27);
			this->T_filePath->Name = L"T_filePath";
			this->T_filePath->Size = System::Drawing::Size(365, 20);
			this->T_filePath->TabIndex = 1;
			this->T_filePath->TextChanged += gcnew System::EventHandler(this, &Window::T_filePath_TextChanged);
			// 
			// L_pathHint
			// 
			this->L_pathHint->AutoSize = true;
			this->L_pathHint->BackColor = System::Drawing::SystemColors::Window;
			this->L_pathHint->ForeColor = System::Drawing::SystemColors::GrayText;
			this->L_pathHint->Location = System::Drawing::Point(22, 30);
			this->L_pathHint->Name = L"L_pathHint";
			this->L_pathHint->Size = System::Drawing::Size(47, 13);
			this->L_pathHint->TabIndex = 4;
			this->L_pathHint->Text = L"File path";
			this->L_pathHint->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// M_Strip
			// 
			this->M_Strip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->M_listFile, this->M_listHelp });
			this->M_Strip->Location = System::Drawing::Point(0, 0);
			this->M_Strip->Name = L"M_Strip";
			this->M_Strip->Size = System::Drawing::Size(447, 24);
			this->M_Strip->TabIndex = 5;
			this->M_Strip->Text = L"menuStrip1";
			// 
			// M_listFile
			// 
			this->M_listFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->M_openVideo,
					this->M_remove, this->M_uninstall, this->M_seperateFile, this->M_exit
			});
			this->M_listFile->Name = L"M_listFile";
			this->M_listFile->Size = System::Drawing::Size(37, 20);
			this->M_listFile->Text = L"File";
			// 
			// M_openVideo
			// 
			this->M_openVideo->Name = L"M_openVideo";
			this->M_openVideo->Size = System::Drawing::Size(180, 22);
			this->M_openVideo->Text = L"Open video";
			this->M_openVideo->Click += gcnew System::EventHandler(this, &Window::M_openVideo_Click);
			// 
			// M_remove
			// 
			this->M_remove->Enabled = false;
			this->M_remove->Name = L"M_remove";
			this->M_remove->Size = System::Drawing::Size(180, 22);
			this->M_remove->Text = L"Remove";
			this->M_remove->Click += gcnew System::EventHandler(this, &Window::M_remove_Click);
			// 
			// M_uninstall
			// 
			this->M_uninstall->Enabled = false;
			this->M_uninstall->Name = L"M_uninstall";
			this->M_uninstall->Size = System::Drawing::Size(180, 22);
			this->M_uninstall->Text = L"Uninstall";
			this->M_uninstall->Click += gcnew System::EventHandler(this, &Window::M_uninstall_Click);
			// 
			// M_seperateFile
			// 
			this->M_seperateFile->Name = L"M_seperateFile";
			this->M_seperateFile->Size = System::Drawing::Size(177, 6);
			// 
			// M_exit
			// 
			this->M_exit->Name = L"M_exit";
			this->M_exit->Size = System::Drawing::Size(180, 22);
			this->M_exit->Text = L"Exit";
			this->M_exit->Click += gcnew System::EventHandler(this, &Window::M_exit_Click);
			// 
			// M_listHelp
			// 
			this->M_listHelp->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->M_help, this->M_seperateHelp,
					this->M_update, this->M_about
			});
			this->M_listHelp->Name = L"M_listHelp";
			this->M_listHelp->Size = System::Drawing::Size(44, 20);
			this->M_listHelp->Text = L"Help";
			// 
			// M_help
			// 
			this->M_help->Name = L"M_help";
			this->M_help->Size = System::Drawing::Size(180, 22);
			this->M_help->Text = L"Online Help";
			this->M_help->Click += gcnew System::EventHandler(this, &Window::M_help_Click);
			// 
			// M_seperateHelp
			// 
			this->M_seperateHelp->Name = L"M_seperateHelp";
			this->M_seperateHelp->Size = System::Drawing::Size(177, 6);
			// 
			// M_update
			// 
			this->M_update->Enabled = false;
			this->M_update->Name = L"M_update";
			this->M_update->Size = System::Drawing::Size(180, 22);
			this->M_update->Text = L"Check for Updates";
			this->M_update->Click += gcnew System::EventHandler(this, &Window::M_update_Click);
			// 
			// M_about
			// 
			this->M_about->Name = L"M_about";
			this->M_about->Size = System::Drawing::Size(180, 22);
			this->M_about->Text = L"About";
			this->M_about->Click += gcnew System::EventHandler(this, &Window::M_about_Click);
			// 
			// Window
			// 
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(447, 86);
			this->Controls->Add(this->L_pathHint);
			this->Controls->Add(this->B_remove);
			this->Controls->Add(this->B_set);
			this->Controls->Add(this->T_filePath);
			this->Controls->Add(this->B_browse);
			this->Controls->Add(this->M_Strip);
			this->HelpButton = true;
			this->MainMenuStrip = this->M_Strip;
			this->MaximizeBox = false;
			this->Name = L"Window";
			this->Text = L"Liveground";
			this->M_Strip->ResumeLayout(false);
			this->M_Strip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//Event Handlers
		System::Void M_openVideo_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void M_remove_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void M_uninstall_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void M_exit_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void M_help_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void M_update_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void M_about_Click(System::Object^ sender, System::EventArgs^ e);

		System::Void T_filePath_TextChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void B_browse_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void B_set_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void B_remove_Click(System::Object^ sender, System::EventArgs^ e);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Window() {
			if (components) {
				delete components;
			}
		}

	public:
		Window(void) {
			InitializeComponent();
			F_dialog->InitialDirectory = Environment::GetFolderPath(Environment::SpecialFolder::MyVideos);
			if (false) {   // Change later
				B_remove->Enabled = true;
				M_remove->Enabled = true;
			}
		}
	};
}