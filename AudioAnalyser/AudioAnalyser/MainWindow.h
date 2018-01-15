#pragma once
#include "ConfigWindow.h"
#include "DynamicPluginConfigWindow.h"
#include "DynamicPluginVizWindow.h"
#include "FileDetailsWindow.h"
#include "AboutWindow.h"

#include "IoManager.h"
#include "Utilities.h"
#include "FileSerializer.h"

namespace AudioAnalyser
{
	using namespace System;

	/// <summary>
	/// G³ówne okno aplikacji
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			LightGreen = System::Drawing::Color::FromArgb(
				static_cast<System::Int32>(static_cast<System::Byte>(210)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));

			InitializeComponent();

			PluginConfigWindows = gcnew System::Collections::Generic::List<DynamicPluginConfigWindow^>();
			PluginVizWindows = gcnew System::Collections::Generic::List<DynamicPluginVizWindow^>();

			for (int i = 0; i < GUI_RACKITEMS_COUNT; i++)
			{
				UpdateRackItemContents(i);
				PluginConfigWindows->Add(gcnew DynamicPluginConfigWindow());
				PluginConfigWindows[i]->OnWindowShutdown += gcnew WindowShutdown(this, &MainWindow::CreateNewPluginConfig);

				PluginVizWindows->Add(gcnew DynamicPluginVizWindow());
				PluginVizWindows[i]->OnWindowShutdown += gcnew WindowShutdown(this, &MainWindow::CreateNewPluginViz);
			}

			SetProcessButtonsEnabled();
			UpdateWorkingFolderPath(System::Environment::GetFolderPath(System::Environment::SpecialFolder::Desktop));
		}

	protected:
		~MainWindow() { if (components) delete components; }

	private:
		bool IsSeekbarClicked = false;
		bool IsInputFileOpened = false;
		Color LightGreen;


	private: System::Collections::Generic::List<DynamicPluginConfigWindow^>^ PluginConfigWindows;
	private: System::Collections::Generic::List<DynamicPluginVizWindow^>^ PluginVizWindows;
	private: System::Windows::Forms::ImageList^  Icons32;

	private: System::Windows::Forms::GroupBox^  GroupInputFile;
	private: System::Windows::Forms::GroupBox^  GroupOutputFile;

	private: System::Windows::Forms::Button^  ButtonNewFile;
	private: System::Windows::Forms::Button^  ButtonOpenFile;
	private: System::Windows::Forms::Button^  ButtonSaveFile;
	private: System::Windows::Forms::Button^  ButtonOpenConfig;
	private: System::Windows::Forms::Button^  ButtonInputStreamStart;
	private: System::Windows::Forms::Button^  ButtonInputFileBrowse;
	private: System::Windows::Forms::Button^  ButtonInputFileStart;
	private: System::Windows::Forms::Button^  ButtonInputFileAbout;
	private: System::Windows::Forms::Button^  ButtonOutputStreamStart;
	private: System::Windows::Forms::Button^  ButtonOutputFileBrowse;
	private: System::Windows::Forms::Button^  ButtonOutputFileStart;
	private: System::Windows::Forms::Button^  ButtonStartProcessing;
	private: System::Windows::Forms::Button^  ButtonAbout;

	private: System::Windows::Forms::Label^  StaticLabelInputFileSource;
	private: System::Windows::Forms::Label^  StaticLabelOutputFileSource;
	private: System::Windows::Forms::Label^  StaticLabelOutputFileFormat;
	private: System::Windows::Forms::Label^  DynamicLabelInputFileTime;
	private: System::Windows::Forms::Label^  DynamicLabelInputFileSource;

	private: System::Windows::Forms::TrackBar^ SeekbarInputFile;

	private: System::Windows::Forms::TextBox^  TextboxOutputFilePath;
	private: System::Windows::Forms::TextBox^  TextboxFilenamePrefix;

	private: RackControls::RackItem^  RackItem0;
	private: RackControls::RackItem^  RackItem1;
	private: RackControls::RackItem^  RackItem2;
	private: RackControls::RackItem^  RackItem3;
	private: RackControls::RackItem^  RackItem4;
	private: RackControls::RackItem^  RackItem5;
	private: RackControls::RackItem^  RackItem6;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;

	private: System::Windows::Forms::OpenFileDialog^  OpenDialogRack;
	private: System::Windows::Forms::OpenFileDialog^  OpenDialogFile;
	private: System::Windows::Forms::SaveFileDialog^  SaveDialogRack;

	private: System::Windows::Forms::FolderBrowserDialog^  SaveDialogFile;
	private: System::Windows::Forms::Timer^  PlayerUpdateTimer;

	private: System::ComponentModel::IContainer^  components;

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
				 this->ButtonInputFileAbout = (gcnew System::Windows::Forms::Button());
				 this->DynamicLabelInputFileSource = (gcnew System::Windows::Forms::Label());
				 this->DynamicLabelInputFileTime = (gcnew System::Windows::Forms::Label());
				 this->SeekbarInputFile = (gcnew System::Windows::Forms::TrackBar());
				 this->ButtonInputFileBrowse = (gcnew System::Windows::Forms::Button());
				 this->ButtonInputFileStart = (gcnew System::Windows::Forms::Button());
				 this->StaticLabelInputFileSource = (gcnew System::Windows::Forms::Label());
				 this->GroupOutputFile = (gcnew System::Windows::Forms::GroupBox());
				 this->TextboxFilenamePrefix = (gcnew System::Windows::Forms::TextBox());
				 this->ButtonOutputFileBrowse = (gcnew System::Windows::Forms::Button());
				 this->StaticLabelOutputFileFormat = (gcnew System::Windows::Forms::Label());
				 this->TextboxOutputFilePath = (gcnew System::Windows::Forms::TextBox());
				 this->ButtonOutputFileStart = (gcnew System::Windows::Forms::Button());
				 this->StaticLabelOutputFileSource = (gcnew System::Windows::Forms::Label());
				 this->ButtonOutputStreamStart = (gcnew System::Windows::Forms::Button());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
				 this->ButtonOpenConfig = (gcnew System::Windows::Forms::Button());
				 this->ButtonAbout = (gcnew System::Windows::Forms::Button());
				 this->ButtonStartProcessing = (gcnew System::Windows::Forms::Button());
				 this->RackItem6 = (gcnew RackControls::RackItem());
				 this->RackItem5 = (gcnew RackControls::RackItem());
				 this->RackItem4 = (gcnew RackControls::RackItem());
				 this->RackItem3 = (gcnew RackControls::RackItem());
				 this->RackItem2 = (gcnew RackControls::RackItem());
				 this->RackItem1 = (gcnew RackControls::RackItem());
				 this->RackItem0 = (gcnew RackControls::RackItem());
				 this->OpenDialogRack = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->OpenDialogFile = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->SaveDialogRack = (gcnew System::Windows::Forms::SaveFileDialog());
				 this->SaveDialogFile = (gcnew System::Windows::Forms::FolderBrowserDialog());
				 this->PlayerUpdateTimer = (gcnew System::Windows::Forms::Timer(this->components));
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
				 this->ButtonNewFile->Click += gcnew System::EventHandler(this, &MainWindow::ButtonNewFile_Click);
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
				 this->Icons32->Images->SetKeyName(11, L"ProcessorOff.png");
				 this->Icons32->Images->SetKeyName(12, L"ProcessorOn.png");
				 // 
				 // ButtonInputStreamStart
				 // 
				 this->ButtonInputStreamStart->BackColor = System::Drawing::SystemColors::Control;
				 this->ButtonInputStreamStart->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->ButtonInputStreamStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
				 this->ButtonInputStreamStart->ImageIndex = 3;
				 this->ButtonInputStreamStart->ImageList = this->Icons32;
				 this->ButtonInputStreamStart->Location = System::Drawing::Point(23, 23);
				 this->ButtonInputStreamStart->Name = L"ButtonInputStreamStart";
				 this->ButtonInputStreamStart->Size = System::Drawing::Size(48, 46);
				 this->ButtonInputStreamStart->TabIndex = 11;
				 this->ButtonInputStreamStart->UseVisualStyleBackColor = false;
				 this->ButtonInputStreamStart->Click += gcnew System::EventHandler(this, &MainWindow::ButtonInputStreamStart_Click);
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
				 this->ButtonOpenFile->Click += gcnew System::EventHandler(this, &MainWindow::ButtonOpenFile_Click);
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
				 this->ButtonSaveFile->Click += gcnew System::EventHandler(this, &MainWindow::ButtonSaveFile_Click);
				 // 
				 // GroupInputFile
				 // 
				 this->GroupInputFile->Controls->Add(this->ButtonInputFileAbout);
				 this->GroupInputFile->Controls->Add(this->DynamicLabelInputFileSource);
				 this->GroupInputFile->Controls->Add(this->DynamicLabelInputFileTime);
				 this->GroupInputFile->Controls->Add(this->SeekbarInputFile);
				 this->GroupInputFile->Controls->Add(this->ButtonInputFileBrowse);
				 this->GroupInputFile->Controls->Add(this->ButtonInputFileStart);
				 this->GroupInputFile->Controls->Add(this->StaticLabelInputFileSource);
				 this->GroupInputFile->Location = System::Drawing::Point(111, 64);
				 this->GroupInputFile->Name = L"GroupInputFile";
				 this->GroupInputFile->Size = System::Drawing::Size(317, 96);
				 this->GroupInputFile->TabIndex = 12;
				 this->GroupInputFile->TabStop = false;
				 this->GroupInputFile->Text = L"Input file";
				 // 
				 // ButtonInputFileAbout
				 // 
				 this->ButtonInputFileAbout->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->ButtonInputFileAbout->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(238)));
				 this->ButtonInputFileAbout->ImageIndex = 6;
				 this->ButtonInputFileAbout->Location = System::Drawing::Point(204, 23);
				 this->ButtonInputFileAbout->Margin = System::Windows::Forms::Padding(0);
				 this->ButtonInputFileAbout->Name = L"ButtonInputFileAbout";
				 this->ButtonInputFileAbout->Size = System::Drawing::Size(24, 20);
				 this->ButtonInputFileAbout->TabIndex = 18;
				 this->ButtonInputFileAbout->Text = L"\?";
				 this->ButtonInputFileAbout->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
				 this->ButtonInputFileAbout->UseVisualStyleBackColor = true;
				 this->ButtonInputFileAbout->Click += gcnew System::EventHandler(this, &MainWindow::ButtonInputFileAbout_Click);
				 // 
				 // DynamicLabelInputFileSource
				 // 
				 this->DynamicLabelInputFileSource->AutoSize = true;
				 this->DynamicLabelInputFileSource->Location = System::Drawing::Point(89, 26);
				 this->DynamicLabelInputFileSource->Name = L"DynamicLabelInputFileSource";
				 this->DynamicLabelInputFileSource->Size = System::Drawing::Size(37, 13);
				 this->DynamicLabelInputFileSource->TabIndex = 17;
				 this->DynamicLabelInputFileSource->Text = L"(none)";
				 // 
				 // DynamicLabelInputFileTime
				 // 
				 this->DynamicLabelInputFileTime->Location = System::Drawing::Point(261, 72);
				 this->DynamicLabelInputFileTime->Name = L"DynamicLabelInputFileTime";
				 this->DynamicLabelInputFileTime->Size = System::Drawing::Size(48, 13);
				 this->DynamicLabelInputFileTime->TabIndex = 12;
				 this->DynamicLabelInputFileTime->Text = L"00:00";
				 this->DynamicLabelInputFileTime->TextAlign = System::Drawing::ContentAlignment::TopCenter;
				 // 
				 // SeekbarInputFile
				 // 
				 this->SeekbarInputFile->Location = System::Drawing::Point(9, 49);
				 this->SeekbarInputFile->Maximum = 0;
				 this->SeekbarInputFile->Name = L"SeekbarInputFile";
				 this->SeekbarInputFile->Size = System::Drawing::Size(248, 45);
				 this->SeekbarInputFile->TabIndex = 15;
				 this->SeekbarInputFile->Scroll += gcnew System::EventHandler(this, &MainWindow::SeekbarInputFile_Scroll);
				 this->SeekbarInputFile->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainWindow::SeekbarInputFile_MouseDown);
				 this->SeekbarInputFile->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainWindow::SeekbarInputFile_MouseUp);
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
				 this->ButtonInputFileBrowse->Size = System::Drawing::Size(24, 20);
				 this->ButtonInputFileBrowse->TabIndex = 16;
				 this->ButtonInputFileBrowse->Text = L"...";
				 this->ButtonInputFileBrowse->TextAlign = System::Drawing::ContentAlignment::TopCenter;
				 this->ButtonInputFileBrowse->UseVisualStyleBackColor = true;
				 this->ButtonInputFileBrowse->Click += gcnew System::EventHandler(this, &MainWindow::ButtonInputFileBrowse_Click);
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
				 this->GroupOutputFile->Controls->Add(this->TextboxFilenamePrefix);
				 this->GroupOutputFile->Controls->Add(this->ButtonOutputFileBrowse);
				 this->GroupOutputFile->Controls->Add(this->StaticLabelOutputFileFormat);
				 this->GroupOutputFile->Controls->Add(this->TextboxOutputFilePath);
				 this->GroupOutputFile->Controls->Add(this->ButtonOutputFileStart);
				 this->GroupOutputFile->Controls->Add(this->StaticLabelOutputFileSource);
				 this->GroupOutputFile->Location = System::Drawing::Point(111, 592);
				 this->GroupOutputFile->Name = L"GroupOutputFile";
				 this->GroupOutputFile->Size = System::Drawing::Size(317, 85);
				 this->GroupOutputFile->TabIndex = 14;
				 this->GroupOutputFile->TabStop = false;
				 this->GroupOutputFile->Text = L"Output file";
				 // 
				 // TextboxFilenamePrefix
				 // 
				 this->TextboxFilenamePrefix->Location = System::Drawing::Point(92, 48);
				 this->TextboxFilenamePrefix->Name = L"TextboxFilenamePrefix";
				 this->TextboxFilenamePrefix->Size = System::Drawing::Size(159, 20);
				 this->TextboxFilenamePrefix->TabIndex = 17;
				 this->TextboxFilenamePrefix->Text = L"Untitled project";
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
				 this->ButtonOutputFileBrowse->Size = System::Drawing::Size(24, 20);
				 this->ButtonOutputFileBrowse->TabIndex = 16;
				 this->ButtonOutputFileBrowse->Text = L"...";
				 this->ButtonOutputFileBrowse->TextAlign = System::Drawing::ContentAlignment::TopCenter;
				 this->ButtonOutputFileBrowse->UseVisualStyleBackColor = true;
				 this->ButtonOutputFileBrowse->Click += gcnew System::EventHandler(this, &MainWindow::ButtonOutputFileBrowse_Click);
				 // 
				 // StaticLabelOutputFileFormat
				 // 
				 this->StaticLabelOutputFileFormat->AutoSize = true;
				 this->StaticLabelOutputFileFormat->Location = System::Drawing::Point(6, 51);
				 this->StaticLabelOutputFileFormat->Name = L"StaticLabelOutputFileFormat";
				 this->StaticLabelOutputFileFormat->Size = System::Drawing::Size(80, 13);
				 this->StaticLabelOutputFileFormat->TabIndex = 12;
				 this->StaticLabelOutputFileFormat->Text = L"File name prefix";
				 // 
				 // TextboxOutputFilePath
				 // 
				 this->TextboxOutputFilePath->Location = System::Drawing::Point(92, 23);
				 this->TextboxOutputFilePath->Name = L"TextboxOutputFilePath";
				 this->TextboxOutputFilePath->ReadOnly = true;
				 this->TextboxOutputFilePath->Size = System::Drawing::Size(132, 20);
				 this->TextboxOutputFilePath->TabIndex = 16;
				 // 
				 // ButtonOutputFileStart
				 // 
				 this->ButtonOutputFileStart->BackColor = System::Drawing::SystemColors::Control;
				 this->ButtonOutputFileStart->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->ButtonOutputFileStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
				 this->ButtonOutputFileStart->ImageIndex = 6;
				 this->ButtonOutputFileStart->ImageList = this->Icons32;
				 this->ButtonOutputFileStart->Location = System::Drawing::Point(261, 23);
				 this->ButtonOutputFileStart->Name = L"ButtonOutputFileStart";
				 this->ButtonOutputFileStart->Size = System::Drawing::Size(48, 46);
				 this->ButtonOutputFileStart->TabIndex = 11;
				 this->ButtonOutputFileStart->UseVisualStyleBackColor = false;
				 this->ButtonOutputFileStart->Click += gcnew System::EventHandler(this, &MainWindow::ButtonOutputFileStart_Click);
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
				 this->ButtonOutputStreamStart->Click += gcnew System::EventHandler(this, &MainWindow::ButtonOutputStreamStart_Click);
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->Controls->Add(this->ButtonInputStreamStart);
				 this->groupBox1->Location = System::Drawing::Point(12, 64);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(93, 96);
				 this->groupBox1->TabIndex = 22;
				 this->groupBox1->TabStop = false;
				 this->groupBox1->Text = L"Input stream";
				 // 
				 // groupBox2
				 // 
				 this->groupBox2->Controls->Add(this->ButtonOutputStreamStart);
				 this->groupBox2->Location = System::Drawing::Point(14, 592);
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
				 // ButtonAbout
				 // 
				 this->ButtonAbout->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->ButtonAbout->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(238)));
				 this->ButtonAbout->ImageIndex = 10;
				 this->ButtonAbout->ImageList = this->Icons32;
				 this->ButtonAbout->Location = System::Drawing::Point(388, 12);
				 this->ButtonAbout->Name = L"ButtonAbout";
				 this->ButtonAbout->Size = System::Drawing::Size(40, 40);
				 this->ButtonAbout->TabIndex = 25;
				 this->ButtonAbout->UseVisualStyleBackColor = true;
				 this->ButtonAbout->Click += gcnew System::EventHandler(this, &MainWindow::ButtonAbout_Click);
				 // 
				 // ButtonStartProcessing
				 // 
				 this->ButtonStartProcessing->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->ButtonStartProcessing->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
				 this->ButtonStartProcessing->ImageIndex = 11;
				 this->ButtonStartProcessing->ImageList = this->Icons32;
				 this->ButtonStartProcessing->Location = System::Drawing::Point(150, 12);
				 this->ButtonStartProcessing->Name = L"ButtonStartProcessing";
				 this->ButtonStartProcessing->Size = System::Drawing::Size(40, 40);
				 this->ButtonStartProcessing->TabIndex = 26;
				 this->ButtonStartProcessing->UseVisualStyleBackColor = true;
				 this->ButtonStartProcessing->Click += gcnew System::EventHandler(this, &MainWindow::ButtonStartProcessing_Click);
				 // 
				 // RackItem6
				 // 
				 this->RackItem6->LastRackItem = true;
				 this->RackItem6->Location = System::Drawing::Point(18, 525);
				 this->RackItem6->MixVolume = 100;
				 this->RackItem6->Name = L"RackItem6";
				 this->RackItem6->RackItemId = 6;
				 this->RackItem6->Size = System::Drawing::Size(407, 61);
				 this->RackItem6->TabIndex = 21;
				 this->RackItem6->SwapRequested += gcnew RackControls::OnSwapRequested(this, &MainWindow::RackItem_SwapRequested);
				 this->RackItem6->SoloRequested += gcnew RackControls::OnSoloRequested(this, &MainWindow::RackItem_SoloRequested);
				 this->RackItem6->BypassRequested += gcnew RackControls::OnBypassRequested(this, &MainWindow::RackItem_BypassRequested);
				 this->RackItem6->VisWindowRequested += gcnew RackControls::OnVisWindowRequested(this, &MainWindow::RackItem_VisWindowRequested);
				 this->RackItem6->ConfigWindowRequested += gcnew RackControls::OnConfigWindowRequested(this, &MainWindow::RackItem_ConfigWindowRequested);
				 this->RackItem6->NewPluginRequested += gcnew RackControls::OnNewPluginRequested(this, &MainWindow::RackItem_NewPluginRequested);
				 this->RackItem6->VolumeMixChanged += gcnew RackControls::OnVolumeMixChanged(this, &MainWindow::RackItem_VolumeMixChanged);
				 // 
				 // RackItem5
				 // 
				 this->RackItem5->LastRackItem = false;
				 this->RackItem5->Location = System::Drawing::Point(18, 464);
				 this->RackItem5->MixVolume = 100;
				 this->RackItem5->Name = L"RackItem5";
				 this->RackItem5->RackItemId = 5;
				 this->RackItem5->Size = System::Drawing::Size(407, 61);
				 this->RackItem5->TabIndex = 20;
				 this->RackItem5->SwapRequested += gcnew RackControls::OnSwapRequested(this, &MainWindow::RackItem_SwapRequested);
				 this->RackItem5->SoloRequested += gcnew RackControls::OnSoloRequested(this, &MainWindow::RackItem_SoloRequested);
				 this->RackItem5->BypassRequested += gcnew RackControls::OnBypassRequested(this, &MainWindow::RackItem_BypassRequested);
				 this->RackItem5->VisWindowRequested += gcnew RackControls::OnVisWindowRequested(this, &MainWindow::RackItem_VisWindowRequested);
				 this->RackItem5->ConfigWindowRequested += gcnew RackControls::OnConfigWindowRequested(this, &MainWindow::RackItem_ConfigWindowRequested);
				 this->RackItem5->NewPluginRequested += gcnew RackControls::OnNewPluginRequested(this, &MainWindow::RackItem_NewPluginRequested);
				 this->RackItem5->VolumeMixChanged += gcnew RackControls::OnVolumeMixChanged(this, &MainWindow::RackItem_VolumeMixChanged);
				 // 
				 // RackItem4
				 // 
				 this->RackItem4->LastRackItem = false;
				 this->RackItem4->Location = System::Drawing::Point(18, 403);
				 this->RackItem4->MixVolume = 100;
				 this->RackItem4->Name = L"RackItem4";
				 this->RackItem4->RackItemId = 4;
				 this->RackItem4->Size = System::Drawing::Size(407, 61);
				 this->RackItem4->TabIndex = 19;
				 this->RackItem4->SwapRequested += gcnew RackControls::OnSwapRequested(this, &MainWindow::RackItem_SwapRequested);
				 this->RackItem4->SoloRequested += gcnew RackControls::OnSoloRequested(this, &MainWindow::RackItem_SoloRequested);
				 this->RackItem4->BypassRequested += gcnew RackControls::OnBypassRequested(this, &MainWindow::RackItem_BypassRequested);
				 this->RackItem4->VisWindowRequested += gcnew RackControls::OnVisWindowRequested(this, &MainWindow::RackItem_VisWindowRequested);
				 this->RackItem4->ConfigWindowRequested += gcnew RackControls::OnConfigWindowRequested(this, &MainWindow::RackItem_ConfigWindowRequested);
				 this->RackItem4->NewPluginRequested += gcnew RackControls::OnNewPluginRequested(this, &MainWindow::RackItem_NewPluginRequested);
				 this->RackItem4->VolumeMixChanged += gcnew RackControls::OnVolumeMixChanged(this, &MainWindow::RackItem_VolumeMixChanged);
				 // 
				 // RackItem3
				 // 
				 this->RackItem3->LastRackItem = false;
				 this->RackItem3->Location = System::Drawing::Point(18, 342);
				 this->RackItem3->MixVolume = 100;
				 this->RackItem3->Name = L"RackItem3";
				 this->RackItem3->RackItemId = 3;
				 this->RackItem3->Size = System::Drawing::Size(407, 61);
				 this->RackItem3->TabIndex = 18;
				 this->RackItem3->SwapRequested += gcnew RackControls::OnSwapRequested(this, &MainWindow::RackItem_SwapRequested);
				 this->RackItem3->SoloRequested += gcnew RackControls::OnSoloRequested(this, &MainWindow::RackItem_SoloRequested);
				 this->RackItem3->BypassRequested += gcnew RackControls::OnBypassRequested(this, &MainWindow::RackItem_BypassRequested);
				 this->RackItem3->VisWindowRequested += gcnew RackControls::OnVisWindowRequested(this, &MainWindow::RackItem_VisWindowRequested);
				 this->RackItem3->ConfigWindowRequested += gcnew RackControls::OnConfigWindowRequested(this, &MainWindow::RackItem_ConfigWindowRequested);
				 this->RackItem3->NewPluginRequested += gcnew RackControls::OnNewPluginRequested(this, &MainWindow::RackItem_NewPluginRequested);
				 this->RackItem3->VolumeMixChanged += gcnew RackControls::OnVolumeMixChanged(this, &MainWindow::RackItem_VolumeMixChanged);
				 // 
				 // RackItem2
				 // 
				 this->RackItem2->LastRackItem = false;
				 this->RackItem2->Location = System::Drawing::Point(18, 281);
				 this->RackItem2->MixVolume = 100;
				 this->RackItem2->Name = L"RackItem2";
				 this->RackItem2->RackItemId = 2;
				 this->RackItem2->Size = System::Drawing::Size(407, 61);
				 this->RackItem2->TabIndex = 17;
				 this->RackItem2->SwapRequested += gcnew RackControls::OnSwapRequested(this, &MainWindow::RackItem_SwapRequested);
				 this->RackItem2->SoloRequested += gcnew RackControls::OnSoloRequested(this, &MainWindow::RackItem_SoloRequested);
				 this->RackItem2->BypassRequested += gcnew RackControls::OnBypassRequested(this, &MainWindow::RackItem_BypassRequested);
				 this->RackItem2->VisWindowRequested += gcnew RackControls::OnVisWindowRequested(this, &MainWindow::RackItem_VisWindowRequested);
				 this->RackItem2->ConfigWindowRequested += gcnew RackControls::OnConfigWindowRequested(this, &MainWindow::RackItem_ConfigWindowRequested);
				 this->RackItem2->NewPluginRequested += gcnew RackControls::OnNewPluginRequested(this, &MainWindow::RackItem_NewPluginRequested);
				 this->RackItem2->VolumeMixChanged += gcnew RackControls::OnVolumeMixChanged(this, &MainWindow::RackItem_VolumeMixChanged);
				 // 
				 // RackItem1
				 // 
				 this->RackItem1->LastRackItem = false;
				 this->RackItem1->Location = System::Drawing::Point(18, 220);
				 this->RackItem1->MixVolume = 100;
				 this->RackItem1->Name = L"RackItem1";
				 this->RackItem1->RackItemId = 1;
				 this->RackItem1->Size = System::Drawing::Size(407, 61);
				 this->RackItem1->TabIndex = 16;
				 this->RackItem1->SwapRequested += gcnew RackControls::OnSwapRequested(this, &MainWindow::RackItem_SwapRequested);
				 this->RackItem1->SoloRequested += gcnew RackControls::OnSoloRequested(this, &MainWindow::RackItem_SoloRequested);
				 this->RackItem1->BypassRequested += gcnew RackControls::OnBypassRequested(this, &MainWindow::RackItem_BypassRequested);
				 this->RackItem1->VisWindowRequested += gcnew RackControls::OnVisWindowRequested(this, &MainWindow::RackItem_VisWindowRequested);
				 this->RackItem1->ConfigWindowRequested += gcnew RackControls::OnConfigWindowRequested(this, &MainWindow::RackItem_ConfigWindowRequested);
				 this->RackItem1->NewPluginRequested += gcnew RackControls::OnNewPluginRequested(this, &MainWindow::RackItem_NewPluginRequested);
				 this->RackItem1->VolumeMixChanged += gcnew RackControls::OnVolumeMixChanged(this, &MainWindow::RackItem_VolumeMixChanged);
				 // 
				 // RackItem0
				 // 
				 this->RackItem0->LastRackItem = false;
				 this->RackItem0->Location = System::Drawing::Point(18, 159);
				 this->RackItem0->MixVolume = 100;
				 this->RackItem0->Name = L"RackItem0";
				 this->RackItem0->RackItemId = 0;
				 this->RackItem0->Size = System::Drawing::Size(407, 61);
				 this->RackItem0->TabIndex = 15;
				 this->RackItem0->SwapRequested += gcnew RackControls::OnSwapRequested(this, &MainWindow::RackItem_SwapRequested);
				 this->RackItem0->SoloRequested += gcnew RackControls::OnSoloRequested(this, &MainWindow::RackItem_SoloRequested);
				 this->RackItem0->BypassRequested += gcnew RackControls::OnBypassRequested(this, &MainWindow::RackItem_BypassRequested);
				 this->RackItem0->VisWindowRequested += gcnew RackControls::OnVisWindowRequested(this, &MainWindow::RackItem_VisWindowRequested);
				 this->RackItem0->ConfigWindowRequested += gcnew RackControls::OnConfigWindowRequested(this, &MainWindow::RackItem_ConfigWindowRequested);
				 this->RackItem0->NewPluginRequested += gcnew RackControls::OnNewPluginRequested(this, &MainWindow::RackItem_NewPluginRequested);
				 this->RackItem0->VolumeMixChanged += gcnew RackControls::OnVolumeMixChanged(this, &MainWindow::RackItem_VolumeMixChanged);
				 // 
				 // OpenDialogRack
				 // 
				 this->OpenDialogRack->DefaultExt = L"aap";
				 this->OpenDialogRack->Filter = L"Audio Analyser Project|*.aap";
				 this->OpenDialogRack->Title = L"Open rack configuration";
				 this->OpenDialogRack->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainWindow::OpenDialogRack_FileOk);
				 // 
				 // OpenDialogFile
				 // 
				 this->OpenDialogFile->DefaultExt = L"wav";
				 this->OpenDialogFile->Filter = L"WAVE file|*.wav";
				 this->OpenDialogFile->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainWindow::OpenDialogFile_FileOk);
				 // 
				 // SaveDialogRack
				 // 
				 this->SaveDialogRack->DefaultExt = L"aap";
				 this->SaveDialogRack->Filter = L"Audio Analyser Project|*.aap";
				 this->SaveDialogRack->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainWindow::SaveDialogRack_FileOk);
				 // 
				 // PlayerUpdateTimer
				 // 
				 this->PlayerUpdateTimer->Tick += gcnew System::EventHandler(this, &MainWindow::PlayerUpdateTimer_Tick);
				 // 
				 // MainWindow
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(438, 685);
				 this->Controls->Add(this->ButtonStartProcessing);
				 this->Controls->Add(this->ButtonAbout);
				 this->Controls->Add(this->ButtonOpenConfig);
				 this->Controls->Add(this->groupBox2);
				 this->Controls->Add(this->groupBox1);
				 this->Controls->Add(this->RackItem6);
				 this->Controls->Add(this->RackItem5);
				 this->Controls->Add(this->RackItem4);
				 this->Controls->Add(this->RackItem3);
				 this->Controls->Add(this->RackItem2);
				 this->Controls->Add(this->RackItem1);
				 this->Controls->Add(this->RackItem0);
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
	private:

		//Interfejs MainWindow - przyciski w menu g³ównym
		Void ButtonNewFile_Click(Object^  sender, EventArgs^  e)
		{
			AudioProcessor::GetInstance()->ResetPlugins();
			PerformFullRackRefresh(true);
			TextboxFilenamePrefix->Text = L"Untitled project";
		}
		Void ButtonOpenFile_Click(Object^  sender, EventArgs^  e)
		{
			OpenDialogRack->ShowDialog();
		}
		Void ButtonSaveFile_Click(Object^  sender, EventArgs^  e)
		{
			SaveDialogRack->FileName = TextboxFilenamePrefix->Text + ".aap";
			SaveDialogRack->ShowDialog();
		}
		Void ButtonStartProcessing_Click(Object^  sender, EventArgs^  e)
		{
			if (IoManager::GetInstance()->IsProcessing())
				IoManager::GetInstance()->StopProcessing();
			else
				IoManager::GetInstance()->StartProcessing();

			SetProcessButtonsEnabled();
			UpdateProcessButtonsIcons();
		}
		Void ButtonOpenConfig_Click(Object^  sender, EventArgs^  e)
		{
			ConfigWindow^ Config = gcnew ConfigWindow();
			Config->ShowDialog();
			SetProcessButtonsEnabled();
			UpdateProcessButtonsIcons();
		}
		Void ButtonInputFileBrowse_Click(Object^  sender, EventArgs^  e)
		{
			OpenDialogFile->ShowDialog();

		}
		Void ButtonOutputFileBrowse_Click(Object^  sender, EventArgs^  e)
		{
			System::Windows::Forms::DialogResult Result = SaveDialogFile->ShowDialog();
			if (Result == System::Windows::Forms::DialogResult::OK) UpdateWorkingFolderPath(SaveDialogFile->SelectedPath);
		}

		Void UpdateWorkingFolderPath(String^ WorkingPath)
		{
			IoManager::GetInstance()->SetOutFilesWorkingFolder(
				Utilities::WideFromSystemString(WorkingPath));

			TextboxOutputFilePath->Text = WorkingPath;
		}

		Void ButtonInputFileAbout_Click(Object^  sender, EventArgs^  e)
		{
			FileDetailsWindow^ Window = gcnew FileDetailsWindow();
			Window->ShowDialog();
		}

		//Interfejs MainWindow - switche otwierania sygna³ów audio (stream-in, file-in, stream-out, file-out)
		Void SetProcessButtonsEnabled()
		{
			bool IsProcessing = IoManager::GetInstance()->IsProcessing();
			ButtonInputStreamStart->Enabled = IsProcessing;
			ButtonInputFileStart->Enabled = IsProcessing && IsInputFileOpened;
			ButtonOutputStreamStart->Enabled = IsProcessing;
			ButtonOutputFileStart->Enabled = IsProcessing;
		}
		Void UpdateProcessButtonsIcons()
		{
			InputSource IS; OutputSource OS;
			IoManager::GetInstance()->GetCurrentSources(IS, OS);

			int On = 5;
			int InStreamOff = 3, InFileOff = 4;
			int OutStreamOff = 7, OutStreamOn = 8, OutFileOff = 6;

			switch (IS)
			{
			case IS_None:
				ButtonInputStreamStart->ImageIndex = InStreamOff;
				ButtonInputStreamStart->BackColor = SystemColors::Control;

				ButtonInputFileStart->ImageIndex = InFileOff;
				ButtonInputFileStart->BackColor = SystemColors::Control;
				break;
			case IS_Stream:
				ButtonInputStreamStart->ImageIndex = On;
				ButtonInputStreamStart->BackColor = LightGreen;

				ButtonInputFileStart->ImageIndex = InFileOff;
				ButtonInputFileStart->BackColor = SystemColors::Control;
				break;
			case IS_File:
				ButtonInputStreamStart->ImageIndex = InStreamOff;
				ButtonInputStreamStart->BackColor = SystemColors::Control;

				ButtonInputFileStart->ImageIndex = On;
				ButtonInputFileStart->BackColor = LightGreen;
				break;
			}

			switch (OS)
			{
			case OS_None:
				ButtonOutputStreamStart->ImageIndex = OutStreamOff;
				ButtonOutputStreamStart->BackColor = SystemColors::Control;

				ButtonOutputFileStart->ImageIndex = OutFileOff;
				ButtonOutputFileStart->BackColor = SystemColors::Control;
				break;
			case OS_File:
				ButtonOutputStreamStart->ImageIndex = OutStreamOff;
				ButtonOutputStreamStart->BackColor = SystemColors::Control;

				ButtonOutputFileStart->ImageIndex = On;
				ButtonOutputFileStart->BackColor = Color::Pink;
				break;
			case OS_Stream:
				ButtonOutputStreamStart->ImageIndex = OutStreamOn;
				ButtonOutputStreamStart->BackColor = Color::Pink;

				ButtonOutputFileStart->ImageIndex = OutFileOff;
				ButtonOutputFileStart->BackColor = SystemColors::Control;
				break;
			case OS_Both:
				ButtonOutputStreamStart->ImageIndex = OutStreamOn;
				ButtonOutputStreamStart->BackColor = Color::Pink;

				ButtonOutputFileStart->ImageIndex = On;
				ButtonOutputFileStart->BackColor = Color::Pink;
				break;
			}

			ButtonStartProcessing->BackColor =
				(IoManager::GetInstance()->IsProcessing())
				? LightGreen : SystemColors::Control;

			ButtonStartProcessing->ImageIndex =
				(IoManager::GetInstance()->IsProcessing())
				? 12 : 11;
		}


		Void ButtonInputStreamStart_Click(Object^  sender, EventArgs^  e)
		{
			IoManager::GetInstance()->SetInputSource(InputSource::IS_Stream);
			UpdateProcessButtonsIcons();
		}
		Void ButtonInputFileStart_Click(Object^  sender, EventArgs^  e)
		{
			IoManager::GetInstance()->SetInputSource(InputSource::IS_File);
			UpdateProcessButtonsIcons();
			PlayerUpdateTimer->Start();
		}
		Void ButtonOutputStreamStart_Click(Object^  sender, EventArgs^  e)
		{
			IoManager::GetInstance()->SetOutputSource(OutputSource::OS_Stream);
			UpdateProcessButtonsIcons();
		}
		Void ButtonOutputFileStart_Click(Object^  sender, EventArgs^  e)
		{
			IoManager::GetInstance()->SetOutFilesPrefix(Utilities::WideFromSystemString(TextboxFilenamePrefix->Text));
			IoManager::GetInstance()->SetOutputSource(OutputSource::OS_File);
			UpdateProcessButtonsIcons();
		}
		Void PlayerUpdateTimer_Tick(Object^  sender, EventArgs^  e)
		{
			UpdateAudioPlayerLabels();
		}
		Void UpdateAudioPlayerLabels()
		{
			int TotalSeconds, CurrentSeconds, A, B;
			IoManager::GetInstance()->GetInputFilePosition(A, CurrentSeconds, B, TotalSeconds);
			SeekbarInputFile->Maximum = TotalSeconds;
			if (!IsSeekbarClicked) SeekbarInputFile->Value = CurrentSeconds;
			DynamicLabelInputFileTime->Text = String::Format("{0:00}:{1:00}", CurrentSeconds / 60, CurrentSeconds % 60);

			if (A == B)
			{
				IoManager::GetInstance()->SetInputSource(InputSource::IS_File);
				IoManager::GetInstance()->SetInputFilePosition(0);
				UpdateProcessButtonsIcons();
				SeekbarInputFile->Value = 0;
				PlayerUpdateTimer->Stop();
			}
		}

		//Interfejs MainWindow - obs³uga plików projektu (aap)
		Void OpenDialogRack_FileOk(Object^  sender, System::ComponentModel::CancelEventArgs^  e)
		{
			String^ TargetPath = OpenDialogRack->FileName;
			XmlTextReader^ XmlReader = gcnew XmlTextReader(TargetPath);
			FileSerializer::DeserializeRack(XmlReader);
			PerformFullRackRefresh(true);
			XmlReader->Close();

			TextboxFilenamePrefix->Text = IO::Path::GetFileNameWithoutExtension(TargetPath);
		}
		Void SaveDialogRack_FileOk(Object^  sender, System::ComponentModel::CancelEventArgs^  e)
		{
			String^ TargetPath = SaveDialogRack->FileName;
			XmlTextWriter^ XmlWriter = gcnew XmlTextWriter(TargetPath, System::Text::Encoding::UTF8);
			FileSerializer::SerializeRack(XmlWriter);
			XmlWriter->Close();
		}

		//Interfejs MainWindow - obs³uga plików audio
		Void OpenDialogFile_FileOk(Object^  sender, System::ComponentModel::CancelEventArgs^  e)
		{
			IsInputFileOpened = IoManager::GetInstance()->OpenNewInputFile(Utilities::WideFromSystemString(OpenDialogFile->FileName));

			String^ Filename = IsInputFileOpened ?
				Utilities::SystemStringFromWide(IoManager::GetInstance()->GetInputFileDetails().Filename)
				: "(none)";
			Filename = Filename->Substring(1);
			if (Filename->Length > 20) Filename = Filename->Substring(0, 20);
			DynamicLabelInputFileSource->Text = Filename;

			SetProcessButtonsEnabled();
			UpdateProcessButtonsIcons();
		}
		Void SaveDialogFile_FileOk(Object^  sender, System::ComponentModel::CancelEventArgs^  e)
		{
		}

		//Helpery RackItemów
		Void PerformFullRackRefresh(bool IncludeDryWetMixes)
		{
			for (int i = 0; i < GUI_RACKITEMS_COUNT; ++i)
			{
				UpdateRackItemContents(i);
				PluginConfigWindows[i]->Close();
				PluginVizWindows[i]->Close();
				CreateNewPluginConfig(i);
				CreateNewPluginViz(i);
				if (IncludeDryWetMixes)
					SelectRackItem(i)->UpdateVolumeMixStatus(
						AudioProcessor::GetInstance()->GetPluginVolumeMix(i));
			}
		}
		RackControls::RackItem^ SelectRackItem(Int32 AtIndex)
		{
			RackControls::RackItem^ Item;
			switch (AtIndex)
			{
			case 0: Item = RackItem0; break;
			case 1: Item = RackItem1; break;
			case 2: Item = RackItem2; break;
			case 3: Item = RackItem3; break;
			case 4: Item = RackItem4; break;
			case 5: Item = RackItem5; break;
			case 6: Item = RackItem6; break;
			}

			return Item;
		}
		Void CreateNewPluginConfig(Int32 AtIndex)
		{
			PluginConfigWindows[AtIndex] = gcnew DynamicPluginConfigWindow();
			PluginConfigWindows[AtIndex]->PopulateWithParameters(AtIndex);
			PluginConfigWindows[AtIndex]->OnWindowShutdown += gcnew WindowShutdown(this, &MainWindow::CreateNewPluginConfig);
		}
		Void CreateNewPluginViz(Int32 AtIndex)
		{
			PluginVizWindows[AtIndex] = gcnew DynamicPluginVizWindow();
			PluginVizWindows[AtIndex]->SetIndex(AtIndex);
			PluginVizWindows[AtIndex]->OnWindowShutdown += gcnew WindowShutdown(this, &MainWindow::CreateNewPluginViz);
		}
		Void UpdateRackItemContents(Int32 AtIndex)
		{
			AudioProcessor* Ap = AudioProcessor::GetInstance();
			RackItemContents^ NewContents = gcnew RackItemContents();
			bool ConfigWindow, VisWindow;
			Ap->GetPluginWindowCapabilities(AtIndex, ConfigWindow, VisWindow);

			NewContents->CurrentPluginName = gcnew String(Utilities::SystemStringFromWide(Ap->GetPluginName(AtIndex)));
			NewContents->DryWetMix = Ap->GetPluginVolumeMix(AtIndex);
			NewContents->IsBypassed = Ap->IsPluginBypassed(AtIndex);
			NewContents->IsNullPlugin = (Ap->GetPluginName(AtIndex) == L"(none)");
			NewContents->HasConfigWindow = ConfigWindow;
			NewContents->HasVisWindow = VisWindow;

			RackControls::RackItem^ RackItemRef = SelectRackItem(AtIndex);
			RackItemRef->SetContents(NewContents);
			RackItemRef->UpdateForm();
		}

		//Przekazywanie intencji miêdzy RackItemami i AudioProcessorem
		Void RackItem_NewPluginRequested(Int32 AtIndex, String^  NewPluginName)
		{
			//Stwórz nowego plugina
			AudioProcessor::GetInstance()->ChangePlugin(AtIndex, Utilities::WideFromSystemString(NewPluginName));

			//Skonfiguruj okna konfiguracyjne i wizualizacji
			DynamicPluginConfigWindow^ WindowC = PluginConfigWindows[AtIndex];
			DynamicPluginVizWindow^ WindowV = PluginVizWindows[AtIndex];
			bool HasConfig, HasVis;
			AudioProcessor::GetInstance()->GetPluginWindowCapabilities(AtIndex, HasConfig, HasVis);
			if(HasConfig) WindowC->PopulateWithParameters(AtIndex);
			else
			{
				if (WindowC->IsOpened) WindowC->Close();
				CreateNewPluginConfig(AtIndex);
			}

			if (HasVis) WindowV->SetIndex(AtIndex);
			else
			{
				if (WindowV->IsOpened) WindowV->Close();
				CreateNewPluginViz(AtIndex);
			}

			//Zaktualizuj parametery RackItemu
			UpdateRackItemContents(AtIndex);
		}
		Void RackItem_SwapRequested(Int32 AtIndex, System::Boolean IsDownwards)
		{
			AudioProcessor::GetInstance()->SwapPlugins(AtIndex, IsDownwards ? MoveDownInRack : MoveUpInRack);

			Int32 I1 = AtIndex;
			Int32 I2 = AtIndex + (IsDownwards ? 1 : -1);

			UpdateRackItemContents(I1);
			UpdateRackItemContents(I2);

			DynamicPluginConfigWindow^ WC1 = PluginConfigWindows[I1];
			DynamicPluginConfigWindow^ WC2 = PluginConfigWindows[I2];
			PluginConfigWindows[I1] = WC2;
			PluginConfigWindows[I2] = WC1;
			WC1->PopulateWithParameters(I2);
			WC2->PopulateWithParameters(I1);

			DynamicPluginVizWindow^ WV1 = PluginVizWindows[I1];
			DynamicPluginVizWindow^ WV2 = PluginVizWindows[I2];
			PluginVizWindows[I1] = WV2;
			PluginVizWindows[I2] = WV1;
			WV1->SetIndex(I2);
			WV2->SetIndex(I1);
			
		}
		Void RackItem_ConfigWindowRequested(Int32 AtIndex)
		{
			DynamicPluginConfigWindow^ ConfigWindow = PluginConfigWindows[AtIndex];
			ConfigWindow->PopulateWithParameters(AtIndex);
			ConfigWindow->Show();
			ConfigWindow->BringToFront();
			ConfigWindow->IsOpened = true;
		}
		Void RackItem_VisWindowRequested(Int32 AtIndex)
		{
			DynamicPluginVizWindow^ VizWindow = PluginVizWindows[AtIndex];
			VizWindow->SetIndex(AtIndex);
			VizWindow->Show();
			VizWindow->BringToFront();
			VizWindow->OnShown();
		}
		Void RackItem_BypassRequested(Int32 AtIndex)
		{
			AudioProcessor::GetInstance()->SetPluginBypassed(AtIndex);
			UpdateRackItemContents(AtIndex);
		}
		Void RackItem_SoloRequested(Int32 AtIndex)
		{
			AudioProcessor::GetInstance()->SetPluginSolo(AtIndex);
			for (int i = 0; i < GUI_RACKITEMS_COUNT; i++) UpdateRackItemContents(i);
		}
		Void RackItem_VolumeMixChanged(Int32 AtIndex, Single NewValue)
		{
			AudioProcessor::GetInstance()->SetPluginVolumeMix(AtIndex, NewValue);
		}

		Void SeekbarInputFile_Scroll(Object^  sender, EventArgs^  e)
		{
			if (SeekbarInputFile->Maximum == 0) return;
			IoManager::GetInstance()->SetInputFilePosition(SeekbarInputFile->Value);
		}
		Void SeekbarInputFile_MouseDown(Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			IsSeekbarClicked = true;
		}
		Void SeekbarInputFile_MouseUp(Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			IsSeekbarClicked = false;
		}

		Void ButtonAbout_Click(System::Object^  sender, System::EventArgs^  e)
		{
			AboutWindow^ Window = gcnew AboutWindow();
			Window->ShowDialog();
		}
	};
}
