#include "AudioGrabber.h"
#pragma once

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

	private: System::Windows::Forms::GroupBox^  GroupInputStream;
	private: System::Windows::Forms::GroupBox^  GroupInputFile;
	private: System::Windows::Forms::GroupBox^  GroupOutputStream;
	private: System::Windows::Forms::GroupBox^  GroupOutputFile;

	private: System::Windows::Forms::ComboBox^  ComboInputStreamSource;
	private: System::Windows::Forms::ComboBox^  ComboInputStreamSamplerate;
	private: System::Windows::Forms::ComboBox^  ComboOutputStreamSamplerate;
	private: System::Windows::Forms::ComboBox^  ComboOutputStreamSource;
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

	private: System::Windows::Forms::Label^  StaticLabelInputStreamSource;
	private: System::Windows::Forms::Label^  StaticLabelInputStreamSamplerate;
	private: System::Windows::Forms::Label^  StaticLabelInputFileSource;
	private: System::Windows::Forms::Label^  StaticLabelInputFileTime;

	private: System::Windows::Forms::Label^  StaticLabelOutputStreamSource;
	private: System::Windows::Forms::Label^  StaticLabelOutputStreamSamplerate;
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
			this->GroupInputStream = (gcnew System::Windows::Forms::GroupBox());
			this->ComboInputStreamSamplerate = (gcnew System::Windows::Forms::ComboBox());
			this->ComboInputStreamSource = (gcnew System::Windows::Forms::ComboBox());
			this->StaticLabelInputStreamSamplerate = (gcnew System::Windows::Forms::Label());
			this->ButtonInputStreamStart = (gcnew System::Windows::Forms::Button());
			this->StaticLabelInputStreamSource = (gcnew System::Windows::Forms::Label());
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
			this->GroupOutputStream = (gcnew System::Windows::Forms::GroupBox());
			this->ComboOutputStreamSamplerate = (gcnew System::Windows::Forms::ComboBox());
			this->ComboOutputStreamSource = (gcnew System::Windows::Forms::ComboBox());
			this->StaticLabelOutputStreamSamplerate = (gcnew System::Windows::Forms::Label());
			this->ButtonOutputStreamStart = (gcnew System::Windows::Forms::Button());
			this->StaticLabelOutputStreamSource = (gcnew System::Windows::Forms::Label());
			this->rackItem8 = (gcnew RackControls::RackItem());
			this->rackItem7 = (gcnew RackControls::RackItem());
			this->rackItem6 = (gcnew RackControls::RackItem());
			this->rackItem5 = (gcnew RackControls::RackItem());
			this->rackItem4 = (gcnew RackControls::RackItem());
			this->rackItem3 = (gcnew RackControls::RackItem());
			this->rackItem2 = (gcnew RackControls::RackItem());
			this->GroupInputStream->SuspendLayout();
			this->GroupInputFile->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SeekbarInputFile))->BeginInit();
			this->GroupOutputFile->SuspendLayout();
			this->GroupOutputStream->SuspendLayout();
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
			// 
			// GroupInputStream
			// 
			this->GroupInputStream->Controls->Add(this->ComboInputStreamSamplerate);
			this->GroupInputStream->Controls->Add(this->ComboInputStreamSource);
			this->GroupInputStream->Controls->Add(this->StaticLabelInputStreamSamplerate);
			this->GroupInputStream->Controls->Add(this->ButtonInputStreamStart);
			this->GroupInputStream->Controls->Add(this->StaticLabelInputStreamSource);
			this->GroupInputStream->Location = System::Drawing::Point(12, 58);
			this->GroupInputStream->Name = L"GroupInputStream";
			this->GroupInputStream->Size = System::Drawing::Size(317, 86);
			this->GroupInputStream->TabIndex = 8;
			this->GroupInputStream->TabStop = false;
			this->GroupInputStream->Text = L"Input (stream)";
			// 
			// ComboInputStreamSamplerate
			// 
			this->ComboInputStreamSamplerate->FormattingEnabled = true;
			this->ComboInputStreamSamplerate->Location = System::Drawing::Point(92, 48);
			this->ComboInputStreamSamplerate->Name = L"ComboInputStreamSamplerate";
			this->ComboInputStreamSamplerate->Size = System::Drawing::Size(165, 21);
			this->ComboInputStreamSamplerate->TabIndex = 3;
			// 
			// ComboInputStreamSource
			// 
			this->ComboInputStreamSource->FormattingEnabled = true;
			this->ComboInputStreamSource->Location = System::Drawing::Point(92, 23);
			this->ComboInputStreamSource->Name = L"ComboInputStreamSource";
			this->ComboInputStreamSource->Size = System::Drawing::Size(165, 21);
			this->ComboInputStreamSource->TabIndex = 2;
			// 
			// StaticLabelInputStreamSamplerate
			// 
			this->StaticLabelInputStreamSamplerate->AutoSize = true;
			this->StaticLabelInputStreamSamplerate->Location = System::Drawing::Point(6, 51);
			this->StaticLabelInputStreamSamplerate->Name = L"StaticLabelInputStreamSamplerate";
			this->StaticLabelInputStreamSamplerate->Size = System::Drawing::Size(63, 13);
			this->StaticLabelInputStreamSamplerate->TabIndex = 1;
			this->StaticLabelInputStreamSamplerate->Text = L"Sample rate";
			// 
			// ButtonInputStreamStart
			// 
			this->ButtonInputStreamStart->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonInputStreamStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->ButtonInputStreamStart->ImageIndex = 3;
			this->ButtonInputStreamStart->ImageList = this->Icons32;
			this->ButtonInputStreamStart->Location = System::Drawing::Point(263, 23);
			this->ButtonInputStreamStart->Name = L"ButtonInputStreamStart";
			this->ButtonInputStreamStart->Size = System::Drawing::Size(48, 46);
			this->ButtonInputStreamStart->TabIndex = 11;
			this->ButtonInputStreamStart->UseVisualStyleBackColor = true;
			// 
			// StaticLabelInputStreamSource
			// 
			this->StaticLabelInputStreamSource->AutoSize = true;
			this->StaticLabelInputStreamSource->Location = System::Drawing::Point(6, 26);
			this->StaticLabelInputStreamSource->Name = L"StaticLabelInputStreamSource";
			this->StaticLabelInputStreamSource->Size = System::Drawing::Size(75, 13);
			this->StaticLabelInputStreamSource->TabIndex = 0;
			this->StaticLabelInputStreamSource->Text = L"Stream source";
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
			this->GroupInputFile->Location = System::Drawing::Point(12, 150);
			this->GroupInputFile->Name = L"GroupInputFile";
			this->GroupInputFile->Size = System::Drawing::Size(317, 100);
			this->GroupInputFile->TabIndex = 12;
			this->GroupInputFile->TabStop = false;
			this->GroupInputFile->Text = L"Input (file)";
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
			this->ButtonInputFileStart->Location = System::Drawing::Point(263, 23);
			this->ButtonInputFileStart->Name = L"ButtonInputFileStart";
			this->ButtonInputFileStart->Size = System::Drawing::Size(48, 46);
			this->ButtonInputFileStart->TabIndex = 11;
			this->ButtonInputFileStart->UseVisualStyleBackColor = true;
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
			this->GroupOutputFile->Location = System::Drawing::Point(12, 348);
			this->GroupOutputFile->Name = L"GroupOutputFile";
			this->GroupOutputFile->Size = System::Drawing::Size(317, 85);
			this->GroupOutputFile->TabIndex = 14;
			this->GroupOutputFile->TabStop = false;
			this->GroupOutputFile->Text = L"Output (file)";
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
			this->ButtonOutputFileStart->Location = System::Drawing::Point(263, 23);
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
			this->StaticLabelOutputFileSource->Size = System::Drawing::Size(54, 13);
			this->StaticLabelOutputFileSource->TabIndex = 0;
			this->StaticLabelOutputFileSource->Text = L"Target file";
			// 
			// GroupOutputStream
			// 
			this->GroupOutputStream->Controls->Add(this->ComboOutputStreamSamplerate);
			this->GroupOutputStream->Controls->Add(this->ComboOutputStreamSource);
			this->GroupOutputStream->Controls->Add(this->StaticLabelOutputStreamSamplerate);
			this->GroupOutputStream->Controls->Add(this->ButtonOutputStreamStart);
			this->GroupOutputStream->Controls->Add(this->StaticLabelOutputStreamSource);
			this->GroupOutputStream->Location = System::Drawing::Point(12, 256);
			this->GroupOutputStream->Name = L"GroupOutputStream";
			this->GroupOutputStream->Size = System::Drawing::Size(317, 86);
			this->GroupOutputStream->TabIndex = 13;
			this->GroupOutputStream->TabStop = false;
			this->GroupOutputStream->Text = L"Output (stream)";
			// 
			// ComboOutputStreamSamplerate
			// 
			this->ComboOutputStreamSamplerate->FormattingEnabled = true;
			this->ComboOutputStreamSamplerate->Location = System::Drawing::Point(92, 48);
			this->ComboOutputStreamSamplerate->Name = L"ComboOutputStreamSamplerate";
			this->ComboOutputStreamSamplerate->Size = System::Drawing::Size(165, 21);
			this->ComboOutputStreamSamplerate->TabIndex = 3;
			// 
			// ComboOutputStreamSource
			// 
			this->ComboOutputStreamSource->FormattingEnabled = true;
			this->ComboOutputStreamSource->Location = System::Drawing::Point(92, 23);
			this->ComboOutputStreamSource->Name = L"ComboOutputStreamSource";
			this->ComboOutputStreamSource->Size = System::Drawing::Size(165, 21);
			this->ComboOutputStreamSource->TabIndex = 2;
			// 
			// StaticLabelOutputStreamSamplerate
			// 
			this->StaticLabelOutputStreamSamplerate->AutoSize = true;
			this->StaticLabelOutputStreamSamplerate->Location = System::Drawing::Point(6, 51);
			this->StaticLabelOutputStreamSamplerate->Name = L"StaticLabelOutputStreamSamplerate";
			this->StaticLabelOutputStreamSamplerate->Size = System::Drawing::Size(63, 13);
			this->StaticLabelOutputStreamSamplerate->TabIndex = 1;
			this->StaticLabelOutputStreamSamplerate->Text = L"Sample rate";
			// 
			// ButtonOutputStreamStart
			// 
			this->ButtonOutputStreamStart->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonOutputStreamStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->ButtonOutputStreamStart->ImageIndex = 8;
			this->ButtonOutputStreamStart->ImageList = this->Icons32;
			this->ButtonOutputStreamStart->Location = System::Drawing::Point(263, 23);
			this->ButtonOutputStreamStart->Name = L"ButtonOutputStreamStart";
			this->ButtonOutputStreamStart->Size = System::Drawing::Size(48, 46);
			this->ButtonOutputStreamStart->TabIndex = 11;
			this->ButtonOutputStreamStart->UseVisualStyleBackColor = true;
			// 
			// StaticLabelOutputStreamSource
			// 
			this->StaticLabelOutputStreamSource->AutoSize = true;
			this->StaticLabelOutputStreamSource->Location = System::Drawing::Point(6, 26);
			this->StaticLabelOutputStreamSource->Name = L"StaticLabelOutputStreamSource";
			this->StaticLabelOutputStreamSource->Size = System::Drawing::Size(73, 13);
			this->StaticLabelOutputStreamSource->TabIndex = 0;
			this->StaticLabelOutputStreamSource->Text = L"Target source";
			// 
			// rackItem8
			// 
			this->rackItem8->Location = System::Drawing::Point(352, 372);
			this->rackItem8->MixVolume = 0;
			this->rackItem8->Name = L"rackItem8";
			this->rackItem8->RackItemId = 0;
			this->rackItem8->Size = System::Drawing::Size(407, 61);
			this->rackItem8->TabIndex = 21;
			// 
			// rackItem7
			// 
			this->rackItem7->Location = System::Drawing::Point(352, 311);
			this->rackItem7->MixVolume = 0;
			this->rackItem7->Name = L"rackItem7";
			this->rackItem7->RackItemId = 0;
			this->rackItem7->Size = System::Drawing::Size(407, 61);
			this->rackItem7->TabIndex = 20;
			// 
			// rackItem6
			// 
			this->rackItem6->Location = System::Drawing::Point(352, 250);
			this->rackItem6->MixVolume = 0;
			this->rackItem6->Name = L"rackItem6";
			this->rackItem6->RackItemId = 0;
			this->rackItem6->Size = System::Drawing::Size(407, 61);
			this->rackItem6->TabIndex = 19;
			// 
			// rackItem5
			// 
			this->rackItem5->Location = System::Drawing::Point(352, 189);
			this->rackItem5->MixVolume = 0;
			this->rackItem5->Name = L"rackItem5";
			this->rackItem5->RackItemId = 0;
			this->rackItem5->Size = System::Drawing::Size(407, 61);
			this->rackItem5->TabIndex = 18;
			// 
			// rackItem4
			// 
			this->rackItem4->Location = System::Drawing::Point(352, 128);
			this->rackItem4->MixVolume = 0;
			this->rackItem4->Name = L"rackItem4";
			this->rackItem4->RackItemId = 0;
			this->rackItem4->Size = System::Drawing::Size(407, 61);
			this->rackItem4->TabIndex = 17;
			// 
			// rackItem3
			// 
			this->rackItem3->Location = System::Drawing::Point(352, 67);
			this->rackItem3->MixVolume = 0;
			this->rackItem3->Name = L"rackItem3";
			this->rackItem3->RackItemId = 0;
			this->rackItem3->Size = System::Drawing::Size(407, 61);
			this->rackItem3->TabIndex = 16;
			// 
			// rackItem2
			// 
			this->rackItem2->Location = System::Drawing::Point(352, 6);
			this->rackItem2->MixVolume = 0;
			this->rackItem2->Name = L"rackItem2";
			this->rackItem2->RackItemId = 0;
			this->rackItem2->Size = System::Drawing::Size(407, 61);
			this->rackItem2->TabIndex = 15;
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(762, 444);
			this->Controls->Add(this->rackItem8);
			this->Controls->Add(this->rackItem7);
			this->Controls->Add(this->rackItem6);
			this->Controls->Add(this->rackItem5);
			this->Controls->Add(this->rackItem4);
			this->Controls->Add(this->rackItem3);
			this->Controls->Add(this->rackItem2);
			this->Controls->Add(this->GroupOutputFile);
			this->Controls->Add(this->GroupInputFile);
			this->Controls->Add(this->GroupOutputStream);
			this->Controls->Add(this->ButtonSaveFile);
			this->Controls->Add(this->ButtonOpenFile);
			this->Controls->Add(this->GroupInputStream);
			this->Controls->Add(this->ButtonNewFile);
			this->Name = L"MainWindow";
			this->Text = L"Audio Analyser";
			this->GroupInputStream->ResumeLayout(false);
			this->GroupInputStream->PerformLayout();
			this->GroupInputFile->ResumeLayout(false);
			this->GroupInputFile->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SeekbarInputFile))->EndInit();
			this->GroupOutputFile->ResumeLayout(false);
			this->GroupOutputFile->PerformLayout();
			this->GroupOutputStream->ResumeLayout(false);
			this->GroupOutputStream->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Btn_StartGrabbing_Click(System::Object^  sender, System::EventArgs^  e)
	{
		AudioGrabber::GetAudioGrabber();
	}

	};
}
