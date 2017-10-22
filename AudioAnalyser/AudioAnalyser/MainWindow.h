#pragma once
#include "ConfigWindow.h"

namespace AudioAnalyser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::ImageList^  Icons32;


	private: System::Windows::Forms::GroupBox^  GroupInputFile;

	private: System::Windows::Forms::GroupBox^  GroupOutputFile;





	private: System::Windows::Forms::ComboBox^  ComboOutputFileFormat;

	private: System::Windows::Forms::Button^  ButtonNewFile;
	private: System::Windows::Forms::Button^  ButtonOpenFile;
	private: System::Windows::Forms::Button^  ButtonSaveFile;
	private: System::Windows::Forms::Button^  ButtonInputStreamStart;
	private: System::Windows::Forms::Button^  ButtonInputFileBrowse;
	private: System::Windows::Forms::Button^  ButtonInputFileStart;
	private: System::Windows::Forms::Button^  ButtonOutputStreamStart;
	private: System::Windows::Forms::Button^  ButtonOutputFileBrowse;
	private: System::Windows::Forms::Button^  ButtonOutputFileStart;



	private: System::Windows::Forms::Label^  StaticLabelInputFileSource;
	private: System::Windows::Forms::Label^  StaticLabelInputFileTime;



	private: System::Windows::Forms::Label^  StaticLabelOutputFileSource;
	private: System::Windows::Forms::Label^  StaticLabelOutputFileFormat;

	private: System::Windows::Forms::TrackBar^ SeekbarInputFile;

	private: System::Windows::Forms::TextBox^  TextboxOutputFilePath;
	private: System::Windows::Forms::TextBox^  TextboxInputFilePath;

	private: RackControls::RackItem^  rackItem2;
	private: RackControls::RackItem^  rackItem3;
	private: RackControls::RackItem^  rackItem4;
	private: RackControls::RackItem^  rackItem5;
	private: RackControls::RackItem^  rackItem6;
	private: RackControls::RackItem^  rackItem7;
	private: RackControls::RackItem^  rackItem8;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  ButtonOpenConfig;

	private: System::Windows::Forms::Button^  button2;


	private: System::ComponentModel::IContainer^  components;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->ButtonNewFile = (gcnew System::Windows::Forms::Button());
			this->Icons32 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->ButtonInputStreamStart = (gcnew System::Windows::Forms::Button());
			this->ButtonOpenFile = (gcnew System::Windows::Forms::Button());
			this->ButtonSaveFile = (gcnew System::Windows::Forms::Button());
			this->GroupInputFile = (gcnew System::Windows::Forms::GroupBox());
			this->StaticLabelInputFileTime = (gcnew System::Windows::Forms::Label());
			this->SeekbarInputFile = (gcnew System::Windows::Forms::TrackBar());
			this->ButtonInputFileBrowse = (gcnew System::Windows::Forms::Button());
			this->TextboxInputFilePath = (gcnew System::Windows::Forms::TextBox());
			this->ButtonInputFileStart = (gcnew System::Windows::Forms::Button());
			this->StaticLabelInputFileSource = (gcnew System::Windows::Forms::Label());
			this->GroupOutputFile = (gcnew System::Windows::Forms::GroupBox());
			this->ComboOutputFileFormat = (gcnew System::Windows::Forms::ComboBox());
			this->ButtonOutputFileBrowse = (gcnew System::Windows::Forms::Button());
			this->StaticLabelOutputFileFormat = (gcnew System::Windows::Forms::Label());
			this->TextboxOutputFilePath = (gcnew System::Windows::Forms::TextBox());
			this->ButtonOutputFileStart = (gcnew System::Windows::Forms::Button());
			this->StaticLabelOutputFileSource = (gcnew System::Windows::Forms::Label());
			this->ButtonOutputStreamStart = (gcnew System::Windows::Forms::Button());
			this->rackItem8 = (gcnew RackControls::RackItem());
			this->rackItem7 = (gcnew RackControls::RackItem());
			this->rackItem6 = (gcnew RackControls::RackItem());
			this->rackItem5 = (gcnew RackControls::RackItem());
			this->rackItem4 = (gcnew RackControls::RackItem());
			this->rackItem3 = (gcnew RackControls::RackItem());
			this->rackItem2 = (gcnew RackControls::RackItem());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->ButtonOpenConfig = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->GroupInputFile->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SeekbarInputFile))->BeginInit();
			this->GroupOutputFile->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// ButtonNewFile
			// 
			this->ButtonNewFile->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonNewFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonNewFile->ImageIndex = 0;
			this->ButtonNewFile->ImageList = this->Icons32;
			this->ButtonNewFile->Location = System::Drawing::Point(12, 12);
			this->ButtonNewFile->Name = L"ButtonNewFile";
			this->ButtonNewFile->Size = System::Drawing::Size(40, 40);
			this->ButtonNewFile->TabIndex = 3;
			this->ButtonNewFile->UseVisualStyleBackColor = true;
			// 
			// Icons32
			// 
			this->Icons32->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"Icons32.ImageStream")));
			this->Icons32->TransparentColor = System::Drawing::Color::Transparent;
			this->Icons32->Images->SetKeyName(0, L"Icons-01.png");
			this->Icons32->Images->SetKeyName(1, L"Icons-03.png");
			this->Icons32->Images->SetKeyName(2, L"Icons-05.png");
			this->Icons32->Images->SetKeyName(3, L"Icons-04.png");
			this->Icons32->Images->SetKeyName(4, L"Icons-07.png");
			this->Icons32->Images->SetKeyName(5, L"Icons-08.png");
			this->Icons32->Images->SetKeyName(6, L"Icons-15.png");
			this->Icons32->Images->SetKeyName(7, L"Icons-16.png");
			this->Icons32->Images->SetKeyName(8, L"Icons-17.png");
			this->Icons32->Images->SetKeyName(9, L"Config.png");
			this->Icons32->Images->SetKeyName(10, L"About.png");
			// 
			// ButtonInputStreamStart
			// 
			this->ButtonInputStreamStart->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonInputStreamStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->ButtonInputStreamStart->ImageIndex = 3;
			this->ButtonInputStreamStart->ImageList = this->Icons32;
			this->ButtonInputStreamStart->Location = System::Drawing::Point(23, 23);
			this->ButtonInputStreamStart->Name = L"ButtonInputStreamStart";
			this->ButtonInputStreamStart->Size = System::Drawing::Size(48, 46);
			this->ButtonInputStreamStart->TabIndex = 11;
			this->ButtonInputStreamStart->UseVisualStyleBackColor = true;
			// 
			// ButtonOpenFile
			// 
			this->ButtonOpenFile->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonOpenFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonOpenFile->ImageIndex = 1;
			this->ButtonOpenFile->ImageList = this->Icons32;
			this->ButtonOpenFile->Location = System::Drawing::Point(58, 12);
			this->ButtonOpenFile->Name = L"ButtonOpenFile";
			this->ButtonOpenFile->Size = System::Drawing::Size(40, 40);
			this->ButtonOpenFile->TabIndex = 9;
			this->ButtonOpenFile->UseVisualStyleBackColor = true;
			// 
			// ButtonSaveFile
			// 
			this->ButtonSaveFile->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonSaveFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonSaveFile->ImageIndex = 2;
			this->ButtonSaveFile->ImageList = this->Icons32;
			this->ButtonSaveFile->Location = System::Drawing::Point(104, 12);
			this->ButtonSaveFile->Name = L"ButtonSaveFile";
			this->ButtonSaveFile->Size = System::Drawing::Size(40, 40);
			this->ButtonSaveFile->TabIndex = 10;
			this->ButtonSaveFile->UseVisualStyleBackColor = true;
			// 
			// GroupInputFile
			// 
			this->GroupInputFile->Controls->Add(this->StaticLabelInputFileTime);
			this->GroupInputFile->Controls->Add(this->SeekbarInputFile);
			this->GroupInputFile->Controls->Add(this->ButtonInputFileBrowse);
			this->GroupInputFile->Controls->Add(this->TextboxInputFilePath);
			this->GroupInputFile->Controls->Add(this->ButtonInputFileStart);
			this->GroupInputFile->Controls->Add(this->StaticLabelInputFileSource);
			this->GroupInputFile->Location = System::Drawing::Point(111, 64);
			this->GroupInputFile->Name = L"GroupInputFile";
			this->GroupInputFile->Size = System::Drawing::Size(317, 100);
			this->GroupInputFile->TabIndex = 12;
			this->GroupInputFile->TabStop = false;
			this->GroupInputFile->Text = L"Input file";
			// 
			// StaticLabelInputFileTime
			// 
			this->StaticLabelInputFileTime->Location = System::Drawing::Point(263, 72);
			this->StaticLabelInputFileTime->Name = L"StaticLabelInputFileTime";
			this->StaticLabelInputFileTime->Size = System::Drawing::Size(48, 22);
			this->StaticLabelInputFileTime->TabIndex = 12;
			this->StaticLabelInputFileTime->Text = L"00:00";
			this->StaticLabelInputFileTime->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// SeekbarInputFile
			// 
			this->SeekbarInputFile->Location = System::Drawing::Point(9, 49);
			this->SeekbarInputFile->Name = L"SeekbarInputFile";
			this->SeekbarInputFile->Size = System::Drawing::Size(248, 45);
			this->SeekbarInputFile->TabIndex = 15;
			// 
			// ButtonInputFileBrowse
			// 
			this->ButtonInputFileBrowse->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonInputFileBrowse->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonInputFileBrowse->ImageIndex = 6;
			this->ButtonInputFileBrowse->Location = System::Drawing::Point(227, 23);
			this->ButtonInputFileBrowse->Margin = System::Windows::Forms::Padding(0);
			this->ButtonInputFileBrowse->Name = L"ButtonInputFileBrowse";
			this->ButtonInputFileBrowse->Size = System::Drawing::Size(30, 20);
			this->ButtonInputFileBrowse->TabIndex = 16;
			this->ButtonInputFileBrowse->Text = L"...";
			this->ButtonInputFileBrowse->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->ButtonInputFileBrowse->UseVisualStyleBackColor = true;
			// 
			// TextboxInputFilePath
			// 
			this->TextboxInputFilePath->CausesValidation = false;
			this->TextboxInputFilePath->Location = System::Drawing::Point(92, 23);
			this->TextboxInputFilePath->Name = L"TextboxInputFilePath";
			this->TextboxInputFilePath->Size = System::Drawing::Size(132, 20);
			this->TextboxInputFilePath->TabIndex = 16;
			// 
			// ButtonInputFileStart
			// 
			this->ButtonInputFileStart->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonInputFileStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->ButtonInputFileStart->ImageIndex = 4;
			this->ButtonInputFileStart->ImageList = this->Icons32;
			this->ButtonInputFileStart->Location = System::Drawing::Point(261, 23);
			this->ButtonInputFileStart->Name = L"ButtonInputFileStart";
			this->ButtonInputFileStart->Size = System::Drawing::Size(48, 46);
			this->ButtonInputFileStart->TabIndex = 11;
			this->ButtonInputFileStart->UseVisualStyleBackColor = true;
			this->ButtonInputFileStart->Click += gcnew System::EventHandler(this, &MainWindow::ButtonInputFileStart_Click);
			// 
			// StaticLabelInputFileSource
			// 
			this->StaticLabelInputFileSource->AutoSize = true;
			this->StaticLabelInputFileSource->Location = System::Drawing::Point(6, 26);
			this->StaticLabelInputFileSource->Name = L"StaticLabelInputFileSource";
			this->StaticLabelInputFileSource->Size = System::Drawing::Size(58, 13);
			this->StaticLabelInputFileSource->TabIndex = 0;
			this->StaticLabelInputFileSource->Text = L"File source";
			// 
			// GroupOutputFile
			// 
			this->GroupOutputFile->Controls->Add(this->ComboOutputFileFormat);
			this->GroupOutputFile->Controls->Add(this->ButtonOutputFileBrowse);
			this->GroupOutputFile->Controls->Add(this->StaticLabelOutputFileFormat);
			this->GroupOutputFile->Controls->Add(this->TextboxOutputFilePath);
			this->GroupOutputFile->Controls->Add(this->ButtonOutputFileStart);
			this->GroupOutputFile->Controls->Add(this->StaticLabelOutputFileSource);
			this->GroupOutputFile->Location = System::Drawing::Point(111, 603);
			this->GroupOutputFile->Name = L"GroupOutputFile";
			this->GroupOutputFile->Size = System::Drawing::Size(317, 85);
			this->GroupOutputFile->TabIndex = 14;
			this->GroupOutputFile->TabStop = false;
			this->GroupOutputFile->Text = L"Output file";
			// 
			// ComboOutputFileFormat
			// 
			this->ComboOutputFileFormat->FormattingEnabled = true;
			this->ComboOutputFileFormat->Location = System::Drawing::Point(92, 48);
			this->ComboOutputFileFormat->Name = L"ComboOutputFileFormat";
			this->ComboOutputFileFormat->Size = System::Drawing::Size(165, 21);
			this->ComboOutputFileFormat->TabIndex = 13;
			// 
			// ButtonOutputFileBrowse
			// 
			this->ButtonOutputFileBrowse->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonOutputFileBrowse->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonOutputFileBrowse->ImageIndex = 6;
			this->ButtonOutputFileBrowse->Location = System::Drawing::Point(227, 23);
			this->ButtonOutputFileBrowse->Margin = System::Windows::Forms::Padding(0);
			this->ButtonOutputFileBrowse->Name = L"ButtonOutputFileBrowse";
			this->ButtonOutputFileBrowse->Size = System::Drawing::Size(30, 20);
			this->ButtonOutputFileBrowse->TabIndex = 16;
			this->ButtonOutputFileBrowse->Text = L"...";
			this->ButtonOutputFileBrowse->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->ButtonOutputFileBrowse->UseVisualStyleBackColor = true;
			// 
			// StaticLabelOutputFileFormat
			// 
			this->StaticLabelOutputFileFormat->AutoSize = true;
			this->StaticLabelOutputFileFormat->Location = System::Drawing::Point(6, 51);
			this->StaticLabelOutputFileFormat->Name = L"StaticLabelOutputFileFormat";
			this->StaticLabelOutputFileFormat->Size = System::Drawing::Size(55, 13);
			this->StaticLabelOutputFileFormat->TabIndex = 12;
			this->StaticLabelOutputFileFormat->Text = L"File format";
			// 
			// TextboxOutputFilePath
			// 
			this->TextboxOutputFilePath->Location = System::Drawing::Point(92, 23);
			this->TextboxOutputFilePath->Name = L"TextboxOutputFilePath";
			this->TextboxOutputFilePath->Size = System::Drawing::Size(132, 20);
			this->TextboxOutputFilePath->TabIndex = 16;
			// 
			// ButtonOutputFileStart
			// 
			this->ButtonOutputFileStart->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonOutputFileStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->ButtonOutputFileStart->ImageIndex = 6;
			this->ButtonOutputFileStart->ImageList = this->Icons32;
			this->ButtonOutputFileStart->Location = System::Drawing::Point(261, 23);
			this->ButtonOutputFileStart->Name = L"ButtonOutputFileStart";
			this->ButtonOutputFileStart->Size = System::Drawing::Size(48, 46);
			this->ButtonOutputFileStart->TabIndex = 11;
			this->ButtonOutputFileStart->UseVisualStyleBackColor = true;
			// 
			// StaticLabelOutputFileSource
			// 
			this->StaticLabelOutputFileSource->AutoSize = true;
			this->StaticLabelOutputFileSource->Location = System::Drawing::Point(6, 26);
			this->StaticLabelOutputFileSource->Name = L"StaticLabelOutputFileSource";
			this->StaticLabelOutputFileSource->Size = System::Drawing::Size(44, 13);
			this->StaticLabelOutputFileSource->TabIndex = 0;
			this->StaticLabelOutputFileSource->Text = L"Save at";
			// 
			// ButtonOutputStreamStart
			// 
			this->ButtonOutputStreamStart->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonOutputStreamStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->ButtonOutputStreamStart->ImageIndex = 8;
			this->ButtonOutputStreamStart->ImageList = this->Icons32;
			this->ButtonOutputStreamStart->Location = System::Drawing::Point(21, 23);
			this->ButtonOutputStreamStart->Name = L"ButtonOutputStreamStart";
			this->ButtonOutputStreamStart->Size = System::Drawing::Size(48, 46);
			this->ButtonOutputStreamStart->TabIndex = 11;
			this->ButtonOutputStreamStart->UseVisualStyleBackColor = true;
			// 
			// rackItem8
			// 
			this->rackItem8->Location = System::Drawing::Point(18, 536);
			this->rackItem8->MixVolume = 0;
			this->rackItem8->Name = L"rackItem8";
			this->rackItem8->RackItemId = 0;
			this->rackItem8->Size = System::Drawing::Size(407, 61);
			this->rackItem8->TabIndex = 21;
			// 
			// rackItem7
			// 
			this->rackItem7->Location = System::Drawing::Point(18, 475);
			this->rackItem7->MixVolume = 0;
			this->rackItem7->Name = L"rackItem7";
			this->rackItem7->RackItemId = 0;
			this->rackItem7->Size = System::Drawing::Size(407, 61);
			this->rackItem7->TabIndex = 20;
			// 
			// rackItem6
			// 
			this->rackItem6->Location = System::Drawing::Point(18, 414);
			this->rackItem6->MixVolume = 0;
			this->rackItem6->Name = L"rackItem6";
			this->rackItem6->RackItemId = 0;
			this->rackItem6->Size = System::Drawing::Size(407, 61);
			this->rackItem6->TabIndex = 19;
			// 
			// rackItem5
			// 
			this->rackItem5->Location = System::Drawing::Point(18, 353);
			this->rackItem5->MixVolume = 0;
			this->rackItem5->Name = L"rackItem5";
			this->rackItem5->RackItemId = 0;
			this->rackItem5->Size = System::Drawing::Size(407, 61);
			this->rackItem5->TabIndex = 18;
			// 
			// rackItem4
			// 
			this->rackItem4->Location = System::Drawing::Point(18, 292);
			this->rackItem4->MixVolume = 0;
			this->rackItem4->Name = L"rackItem4";
			this->rackItem4->RackItemId = 0;
			this->rackItem4->Size = System::Drawing::Size(407, 61);
			this->rackItem4->TabIndex = 17;
			// 
			// rackItem3
			// 
			this->rackItem3->Location = System::Drawing::Point(18, 231);
			this->rackItem3->MixVolume = 0;
			this->rackItem3->Name = L"rackItem3";
			this->rackItem3->RackItemId = 0;
			this->rackItem3->Size = System::Drawing::Size(407, 61);
			this->rackItem3->TabIndex = 16;
			// 
			// rackItem2
			// 
			this->rackItem2->Location = System::Drawing::Point(18, 170);
			this->rackItem2->MixVolume = 0;
			this->rackItem2->Name = L"rackItem2";
			this->rackItem2->RackItemId = 0;
			this->rackItem2->Size = System::Drawing::Size(407, 61);
			this->rackItem2->TabIndex = 15;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->ButtonInputStreamStart);
			this->groupBox1->Location = System::Drawing::Point(12, 64);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(93, 100);
			this->groupBox1->TabIndex = 22;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Input stream";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->ButtonOutputStreamStart);
			this->groupBox2->Location = System::Drawing::Point(14, 603);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(91, 85);
			this->groupBox2->TabIndex = 23;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Output stream";
			// 
			// ButtonOpenConfig
			// 
			this->ButtonOpenConfig->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonOpenConfig->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonOpenConfig->ImageIndex = 9;
			this->ButtonOpenConfig->ImageList = this->Icons32;
			this->ButtonOpenConfig->Location = System::Drawing::Point(342, 12);
			this->ButtonOpenConfig->Name = L"ButtonOpenConfig";
			this->ButtonOpenConfig->Size = System::Drawing::Size(40, 40);
			this->ButtonOpenConfig->TabIndex = 24;
			this->ButtonOpenConfig->UseVisualStyleBackColor = true;
			this->ButtonOpenConfig->Click += gcnew System::EventHandler(this, &MainWindow::ButtonOpenConfig_Click);
			// 
			// button2
			// 
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button2->ImageIndex = 10;
			this->button2->ImageList = this->Icons32;
			this->button2->Location = System::Drawing::Point(388, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(40, 40);
			this->button2->TabIndex = 25;
			this->button2->UseVisualStyleBackColor = true;
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(438, 697);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->ButtonOpenConfig);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->rackItem8);
			this->Controls->Add(this->rackItem7);
			this->Controls->Add(this->rackItem6);
			this->Controls->Add(this->rackItem5);
			this->Controls->Add(this->rackItem4);
			this->Controls->Add(this->rackItem3);
			this->Controls->Add(this->rackItem2);
			this->Controls->Add(this->GroupOutputFile);
			this->Controls->Add(this->GroupInputFile);
			this->Controls->Add(this->ButtonSaveFile);
			this->Controls->Add(this->ButtonOpenFile);
			this->Controls->Add(this->ButtonNewFile);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MainWindow";
			this->Text = L"Audio Analyser";
			this->GroupInputFile->ResumeLayout(false);
			this->GroupInputFile->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SeekbarInputFile))->EndInit();
			this->GroupOutputFile->ResumeLayout(false);
			this->GroupOutputFile->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Btn_StartGrabbing_Click(System::Object^  sender, System::EventArgs^  e)
	{
	}

	private: System::Void ButtonInputFileStart_Click(System::Object^  sender, System::EventArgs^  e)
	{

	}
	private: System::Void ButtonOpenConfig_Click(System::Object^  sender, System::EventArgs^  e)
	{
		ConfigWindow^ Config = gcnew ConfigWindow();
		Config->ShowDialog();
	}
};
}
