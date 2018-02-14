#pragma once
#include "PCH.h"
#include "SoundFile.h"
#include "IoManager.h"

namespace AudioAnalyser
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Okno ze szczegó³ami obecnie uruchomionego pliku.
	/// </summary>
	public ref class FileDetailsWindow : public System::Windows::Forms::Form
	{
	public:
		FileDetailsWindow(void)
		{
			InitializeComponent();
			PopulateWindow();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FileDetailsWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^  StaticLabelFilename;
	private: System::Windows::Forms::Label^  StaticLabelChannels;
	private: System::Windows::Forms::Label^  StaticLabelSamplerate;
	private: System::Windows::Forms::Label^  StaticLabelFilesize;
	private: System::Windows::Forms::Label^  StaticLabelLength;
	private: System::Windows::Forms::Label^  DynamicLabelFilename;
	private: System::Windows::Forms::Label^  DynamicLabelChannels;
	private: System::Windows::Forms::Label^  DynamicLabelSamplerate;
	private: System::Windows::Forms::Label^  DynamicLabelFilesize;
	private: System::Windows::Forms::Label^  DynamicLabelLength;
	private: System::Windows::Forms::Button^  ButtonClose;

			 /// <summary>
			 /// Required designer variable.
			 /// </summary>
			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FileDetailsWindow::typeid));
				 this->StaticLabelFilename = (gcnew System::Windows::Forms::Label());
				 this->DynamicLabelFilename = (gcnew System::Windows::Forms::Label());
				 this->DynamicLabelChannels = (gcnew System::Windows::Forms::Label());
				 this->StaticLabelChannels = (gcnew System::Windows::Forms::Label());
				 this->DynamicLabelSamplerate = (gcnew System::Windows::Forms::Label());
				 this->StaticLabelSamplerate = (gcnew System::Windows::Forms::Label());
				 this->DynamicLabelFilesize = (gcnew System::Windows::Forms::Label());
				 this->StaticLabelFilesize = (gcnew System::Windows::Forms::Label());
				 this->DynamicLabelLength = (gcnew System::Windows::Forms::Label());
				 this->StaticLabelLength = (gcnew System::Windows::Forms::Label());
				 this->ButtonClose = (gcnew System::Windows::Forms::Button());
				 this->SuspendLayout();
				 // 
				 // StaticLabelFilename
				 // 
				 this->StaticLabelFilename->AutoSize = true;
				 this->StaticLabelFilename->Location = System::Drawing::Point(12, 13);
				 this->StaticLabelFilename->Name = L"StaticLabelFilename";
				 this->StaticLabelFilename->Size = System::Drawing::Size(52, 13);
				 this->StaticLabelFilename->TabIndex = 0;
				 this->StaticLabelFilename->Text = L"File name";
				 // 
				 // DynamicLabelFilename
				 // 
				 this->DynamicLabelFilename->AutoSize = true;
				 this->DynamicLabelFilename->Location = System::Drawing::Point(106, 13);
				 this->DynamicLabelFilename->Name = L"DynamicLabelFilename";
				 this->DynamicLabelFilename->Size = System::Drawing::Size(10, 13);
				 this->DynamicLabelFilename->TabIndex = 1;
				 this->DynamicLabelFilename->Text = L"-";
				 // 
				 // DynamicLabelChannels
				 // 
				 this->DynamicLabelChannels->AutoSize = true;
				 this->DynamicLabelChannels->Location = System::Drawing::Point(106, 57);
				 this->DynamicLabelChannels->Name = L"DynamicLabelChannels";
				 this->DynamicLabelChannels->Size = System::Drawing::Size(10, 13);
				 this->DynamicLabelChannels->TabIndex = 5;
				 this->DynamicLabelChannels->Text = L"-";
				 // 
				 // StaticLabelChannels
				 // 
				 this->StaticLabelChannels->AutoSize = true;
				 this->StaticLabelChannels->Location = System::Drawing::Point(12, 57);
				 this->StaticLabelChannels->Name = L"StaticLabelChannels";
				 this->StaticLabelChannels->Size = System::Drawing::Size(51, 13);
				 this->StaticLabelChannels->TabIndex = 4;
				 this->StaticLabelChannels->Text = L"Channels";
				 // 
				 // DynamicLabelSamplerate
				 // 
				 this->DynamicLabelSamplerate->AutoSize = true;
				 this->DynamicLabelSamplerate->Location = System::Drawing::Point(106, 79);
				 this->DynamicLabelSamplerate->Name = L"DynamicLabelSamplerate";
				 this->DynamicLabelSamplerate->Size = System::Drawing::Size(10, 13);
				 this->DynamicLabelSamplerate->TabIndex = 7;
				 this->DynamicLabelSamplerate->Text = L"-";
				 // 
				 // StaticLabelSamplerate
				 // 
				 this->StaticLabelSamplerate->AutoSize = true;
				 this->StaticLabelSamplerate->Location = System::Drawing::Point(12, 79);
				 this->StaticLabelSamplerate->Name = L"StaticLabelSamplerate";
				 this->StaticLabelSamplerate->Size = System::Drawing::Size(63, 13);
				 this->StaticLabelSamplerate->TabIndex = 6;
				 this->StaticLabelSamplerate->Text = L"Sample rate";
				 // 
				 // DynamicLabelFilesize
				 // 
				 this->DynamicLabelFilesize->AutoSize = true;
				 this->DynamicLabelFilesize->Location = System::Drawing::Point(106, 35);
				 this->DynamicLabelFilesize->Name = L"DynamicLabelFilesize";
				 this->DynamicLabelFilesize->Size = System::Drawing::Size(10, 13);
				 this->DynamicLabelFilesize->TabIndex = 9;
				 this->DynamicLabelFilesize->Text = L"-";
				 // 
				 // StaticLabelFilesize
				 // 
				 this->StaticLabelFilesize->AutoSize = true;
				 this->StaticLabelFilesize->Location = System::Drawing::Point(12, 35);
				 this->StaticLabelFilesize->Name = L"StaticLabelFilesize";
				 this->StaticLabelFilesize->Size = System::Drawing::Size(44, 13);
				 this->StaticLabelFilesize->TabIndex = 8;
				 this->StaticLabelFilesize->Text = L"File size";
				 // 
				 // DynamicLabelLength
				 // 
				 this->DynamicLabelLength->AutoSize = true;
				 this->DynamicLabelLength->Location = System::Drawing::Point(106, 101);
				 this->DynamicLabelLength->Name = L"DynamicLabelLength";
				 this->DynamicLabelLength->Size = System::Drawing::Size(10, 13);
				 this->DynamicLabelLength->TabIndex = 11;
				 this->DynamicLabelLength->Text = L"-";
				 // 
				 // StaticLabelLength
				 // 
				 this->StaticLabelLength->AutoSize = true;
				 this->StaticLabelLength->Location = System::Drawing::Point(12, 101);
				 this->StaticLabelLength->Name = L"StaticLabelLength";
				 this->StaticLabelLength->Size = System::Drawing::Size(40, 13);
				 this->StaticLabelLength->TabIndex = 10;
				 this->StaticLabelLength->Text = L"Length";
				 // 
				 // ButtonClose
				 // 
				 this->ButtonClose->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				 this->ButtonClose->Location = System::Drawing::Point(325, 127);
				 this->ButtonClose->Name = L"ButtonClose";
				 this->ButtonClose->Size = System::Drawing::Size(75, 23);
				 this->ButtonClose->TabIndex = 12;
				 this->ButtonClose->Text = L"OK";
				 this->ButtonClose->UseVisualStyleBackColor = true;
				 // 
				 // FileDetailsWindow
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->CancelButton = this->ButtonClose;
				 this->ClientSize = System::Drawing::Size(412, 162);
				 this->Controls->Add(this->ButtonClose);
				 this->Controls->Add(this->DynamicLabelLength);
				 this->Controls->Add(this->StaticLabelLength);
				 this->Controls->Add(this->DynamicLabelFilesize);
				 this->Controls->Add(this->StaticLabelFilesize);
				 this->Controls->Add(this->DynamicLabelSamplerate);
				 this->Controls->Add(this->StaticLabelSamplerate);
				 this->Controls->Add(this->DynamicLabelChannels);
				 this->Controls->Add(this->StaticLabelChannels);
				 this->Controls->Add(this->DynamicLabelFilename);
				 this->Controls->Add(this->StaticLabelFilename);
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				 this->MaximizeBox = false;
				 this->Name = L"FileDetailsWindow";
				 this->Text = L"File details";
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

	public:
		System::Void PopulateWindow()
		{
			AudioFileInfo Data = IoManager::GetInstance()->GetInputFileDetails();

			if (Data.FileOk)
			{
				DynamicLabelFilename->Text = Utilities::SystemStringFromWide((Data.Filepath + Data.Filename));
				DynamicLabelChannels->Text = Data.IsStereo ? "2" : "1";
				DynamicLabelSamplerate->Text = Data.SampleRate.ToString() + " samples per second";
				DynamicLabelFilesize->Text = (gcnew System::IO::FileInfo(DynamicLabelFilename->Text))->Length.ToString() + " bytes";

				System::TimeSpan FileLength = System::TimeSpan(0, 0, 0, 0, (int)(1000.f * (float)Data.Length / (float)Data.SampleRate));
				DynamicLabelLength->Text = Data.Length.ToString() + " samples (" + FileLength.ToString("g") + ")";
			}
			else
			{
				DynamicLabelFilename->Text = "-";
				DynamicLabelChannels->Text = "-";
				DynamicLabelSamplerate->Text = "-";
				DynamicLabelFilesize->Text = "-";
				DynamicLabelLength->Text = "-";
			}
		}
	};
}
