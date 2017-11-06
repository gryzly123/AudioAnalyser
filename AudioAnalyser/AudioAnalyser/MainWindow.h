#pragma once
#include "ConfigWindow.h"
#include "DynamicPluginConfigWindow.h"
#include "IoManager.h"
#include "Utilities.h"
#include "FileSerializer.h"

namespace AudioAnalyser
{
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

			PluginConfigWindows = gcnew System::Collections::Generic::List<DynamicPluginConfigWindow^>();
			for (int i = 0; i < GUI_RACKITEMS_COUNT; i++)
			{
				UpdateRackItemContents(i);
				PluginConfigWindows->Add(gcnew DynamicPluginConfigWindow());
				PluginConfigWindows[i]->OnWindowShutdown += gcnew WindowShutdown(this, &MainWindow::CreateNewPluginConfig);
			}
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

	private: System::Collections::Generic::List<DynamicPluginConfigWindow^>^ PluginConfigWindows;
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
	private: System::Windows::Forms::Button^  ButtonStartProcessing;
	
	private: System::Windows::Forms::Label^  StaticLabelInputFileSource;
	private: System::Windows::Forms::Label^  StaticLabelInputFileTime;
	private: System::Windows::Forms::Label^  StaticLabelOutputFileSource;
	private: System::Windows::Forms::Label^  StaticLabelOutputFileFormat;
	
	private: System::Windows::Forms::TrackBar^ SeekbarInputFile;
	private: System::Windows::Forms::TextBox^  TextboxOutputFilePath;
	private: System::Windows::Forms::TextBox^  TextboxInputFilePath;
	
	private: RackControls::RackItem^  RackItem0;
	private: RackControls::RackItem^  RackItem1;
	private: RackControls::RackItem^  RackItem2;
	private: RackControls::RackItem^  RackItem3;
	private: RackControls::RackItem^  RackItem4;
	private: RackControls::RackItem^  RackItem5;
	private: RackControls::RackItem^  RackItem6;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  ButtonOpenConfig;

	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::OpenFileDialog^  OpenDialogRack;
	private: System::Windows::Forms::OpenFileDialog^  OpenDialogFile;
	private: System::Windows::Forms::SaveFileDialog^  SaveDialogRack;
	private: System::Windows::Forms::SaveFileDialog^  SaveDialogFile;

	private: System::ComponentModel::IContainer^  components;
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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->ButtonOpenConfig = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
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
			this->SaveDialogFile = (gcnew System::Windows::Forms::SaveFileDialog());
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
			// ButtonStartProcessing
			// 
			this->ButtonStartProcessing->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonStartProcessing->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->ButtonStartProcessing->ImageIndex = 9;
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
			this->RackItem6->Location = System::Drawing::Point(18, 536);
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
			this->RackItem5->Location = System::Drawing::Point(18, 475);
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
			this->RackItem4->Location = System::Drawing::Point(18, 414);
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
			this->RackItem3->Location = System::Drawing::Point(18, 353);
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
			this->RackItem2->Location = System::Drawing::Point(18, 292);
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
			this->RackItem1->Location = System::Drawing::Point(18, 231);
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
			this->RackItem0->Location = System::Drawing::Point(18, 170);
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
			this->OpenDialogRack->FileName = L"openFileDialog1";
			this->OpenDialogRack->Filter = L"Audio Analyser Project|*.aap";
			this->OpenDialogRack->Title = L"Open rack configuration";
			this->OpenDialogRack->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainWindow::OpenDialogRack_FileOk);
			// 
			// OpenDialogFile
			// 
			this->OpenDialogFile->FileName = L"openFileDialog1";
			// 
			// SaveDialogRack
			// 
			this->SaveDialogRack->DefaultExt = L"aap";
			this->SaveDialogRack->Filter = L"Audio Analyser Project|*.aap";
			this->SaveDialogRack->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainWindow::SaveDialogRack_FileOk);
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(438, 697);
			this->Controls->Add(this->ButtonStartProcessing);
			this->Controls->Add(this->button2);
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
		System::Void ButtonNewFile_Click(System::Object^  sender, System::EventArgs^  e)
		{
			AudioProcessor::GetInstance()->ResetPlugins();
			PerformFullRackRefresh(true);
		}
		System::Void ButtonOpenFile_Click(System::Object^  sender, System::EventArgs^  e)
		{
			OpenDialogRack->ShowDialog();
		}
		System::Void ButtonSaveFile_Click(System::Object^  sender, System::EventArgs^  e)
		{
			SaveDialogRack->ShowDialog();
		}
		System::Void ButtonStartProcessing_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (IoManager::GetInstance()->IsProcessing()) IoManager::GetInstance()->StartProcessing();
			else IoManager::GetInstance()->StopProcessing();
		}
		System::Void ButtonOpenConfig_Click(System::Object^  sender, System::EventArgs^  e)
		{
			ConfigWindow^ Config = gcnew ConfigWindow();
			Config->ShowDialog();
		}
		
		//Interfejs MainWindow - switche otwierania sygna³ów audio (stream-in, file-in, stream-out, file-out)
		System::Void ButtonInputStreamStart_Click(System::Object^  sender, System::EventArgs^  e)
		{
		}
		System::Void ButtonInputFileStart_Click(System::Object^  sender, System::EventArgs^  e)
		{
		}
		System::Void ButtonOutputStreamStart_Click(System::Object^  sender, System::EventArgs^  e)
		{
		}
		System::Void ButtonOutputFileStart_Click(System::Object^  sender, System::EventArgs^  e)
		{
		}

		//Interfejs MainWindow - obs³uga plików projektu (aap)
		System::Void OpenDialogRack_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
		{
			System::String^ TargetPath = OpenDialogRack->FileName;
			XmlTextReader^ XmlReader = gcnew XmlTextReader(TargetPath);
			FileSerializer::DeserializeRack(XmlReader);
			PerformFullRackRefresh(true);
			XmlReader->Close();

		}
		System::Void SaveDialogRack_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
		{
			System::String^ TargetPath = SaveDialogRack->FileName;
			XmlTextWriter^ XmlWriter = gcnew XmlTextWriter(TargetPath, System::Text::Encoding::UTF8);
			FileSerializer::SerializeRack(XmlWriter);
			XmlWriter->Close();
		}

		//Helpery RackItemów
		System::Void PerformFullRackRefresh(bool IncludeDryWetMixes)
		{
			for (int i = 0; i < GUI_RACKITEMS_COUNT; ++i)
			{
				UpdateRackItemContents(i);
				PluginConfigWindows[i]->Close();
				CreateNewPluginConfig(i);
				if (IncludeDryWetMixes)
					SelectRackItem(i)->UpdateVolumeMixStatus(
						AudioProcessor::GetInstance()->GetPluginVolumeMix(i));
			}
		}
		RackControls::RackItem^ SelectRackItem(System::Int32 AtIndex)
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
		System::Void CreateNewPluginConfig(Int32 AtIndex)
		{
			PluginConfigWindows[AtIndex] = gcnew DynamicPluginConfigWindow();
			const std::vector <DspPluginParameter*> Params = AudioProcessor::GetInstance()->GetPluginParameters(AtIndex);
			PluginConfigWindows[AtIndex]->PopulateWithParameters(Params, AtIndex);
			PluginConfigWindows[AtIndex]->OnWindowShutdown += gcnew WindowShutdown(this, &MainWindow::CreateNewPluginConfig);
		}
		System::Void UpdateConfigWindow(System::Int32 AtIndex)
		{
			bool PluginHasConfigWindow, B;

			//Jeœli stare okno konfiguracji istnieje, zamknij je
			DynamicPluginConfigWindow^ Window = PluginConfigWindows[AtIndex];
			bool WasWindowOpenedBeforeShutdown = Window->IsOpened;
			System::Drawing::Point WindowLocation;
			if (WasWindowOpenedBeforeShutdown)
			{
				WindowLocation = Window->DesktopLocation;
				Window->Close();
			}

			//Stwórz nowe okno konfiguracji
			CreateNewPluginConfig(AtIndex);
			Window = PluginConfigWindows[AtIndex];

			//Poka¿ nowe okno konfiguracji, jeœli stare by³o otwarte, a nowe je posiada
			AudioProcessor::GetInstance()->GetPluginWindowCapabilities(AtIndex, PluginHasConfigWindow, B);
			if (WasWindowOpenedBeforeShutdown && PluginHasConfigWindow)
			{
				Window->Show();
				Window->IsOpened = true;
				Window->DesktopLocation = WindowLocation;
			}
		}
		System::Void UpdateRackItemContents(System::Int32 AtIndex)
		{
			AudioProcessor* Ap = AudioProcessor::GetInstance();
			RackItemContents^ NewContents = gcnew RackItemContents();
			bool ConfigWindow, VisWindow;
			Ap->GetPluginWindowCapabilities(AtIndex, ConfigWindow, VisWindow);

			NewContents->CurrentPluginName = gcnew System::String(Ap->GetPluginName(AtIndex).c_str());
			NewContents->IsBypassed = Ap->IsPluginBypassed(AtIndex);
			NewContents->IsNullPlugin = (Ap->GetPluginName(AtIndex) == L"(none)");
			NewContents->HasConfigWindow = ConfigWindow;
			NewContents->HasVisWindow = VisWindow;

			RackControls::RackItem^ RackItemRef = SelectRackItem(AtIndex);
			RackItemRef->SetContents(NewContents);
			RackItemRef->UpdateForm();
		}

		//Kontrola RackItemów
		System::Void RackItem_NewPluginRequested(System::Int32 AtIndex, System::String^  NewPluginName)
		{
			//Stwórz nowego plugina
			AudioProcessor::GetInstance()->ChangePlugin(AtIndex, Utilities::WideFromSystemString(NewPluginName));

			//Zaktualizuj okna konfiguracji
			UpdateConfigWindow(AtIndex);

			//Zaktualizuj parametery RackItemu
			UpdateRackItemContents(AtIndex);
		}
		System::Void RackItem_SwapRequested(System::Int32 AtIndex, System::Boolean IsDownwards)
		{
			AudioProcessor::GetInstance()->SwapPlugins(AtIndex, IsDownwards ? MoveDownInRack : MoveUpInRack);
			
			UpdateRackItemContents(AtIndex);
			UpdateRackItemContents(AtIndex + (IsDownwards ? 1 : -1));

			UpdateConfigWindow(AtIndex);
			UpdateConfigWindow(AtIndex + (IsDownwards ? 1 : -1));
		}
		System::Void RackItem_ConfigWindowRequested(System::Int32 AtIndex)
		{
			DynamicPluginConfigWindow^ ConfigWindow = PluginConfigWindows[AtIndex];
			ConfigWindow->Show();
			ConfigWindow->BringToFront();
			ConfigWindow->IsOpened = true;
		}
		System::Void RackItem_VisWindowRequested(System::Int32 AtIndex)
		{

		}
		System::Void RackItem_BypassRequested(System::Int32 AtIndex)
		{
			AudioProcessor::GetInstance()->SetPluginBypassed(AtIndex);
			UpdateRackItemContents(AtIndex);
		}
		System::Void RackItem_SoloRequested(System::Int32 AtIndex)
		{
			AudioProcessor::GetInstance()->SetPluginSolo(AtIndex);
			for(int i = 0; i < GUI_RACKITEMS_COUNT; i++) UpdateRackItemContents(i);
		}
		System::Void RackItem_VolumeMixChanged(System::Int32 AtIndex, System::Single NewValue)
		{
			AudioProcessor::GetInstance()->SetPluginVolumeMix(AtIndex, NewValue);
		}

};
}
