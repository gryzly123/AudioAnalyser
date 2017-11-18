#pragma once
#include "PCH.h"
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
	/// Summary for ConfigWindow
	/// </summary>
	public ref class ConfigWindow : public System::Windows::Forms::Form
	{
	public:
		ConfigWindow(void)
		{
			InitializeComponent();
			CustomInitCode();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ConfigWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::ComboBox^  ComboOutputStreamSource;
	private: System::Windows::Forms::Label^  StaticLabelOutputStreamSource;
	private: System::Windows::Forms::GroupBox^  GroupStreamConfig;
	private: System::Windows::Forms::ComboBox^  ComboInputStreamSource;
	private: System::Windows::Forms::Label^  StaticLabelInputStreamSource;
	private: System::Windows::Forms::GroupBox^  GroupProcessing;
	private: System::Windows::Forms::ComboBox^  ComboInputStreamBlocksize;
	private: System::Windows::Forms::Label^  StaticLabelBlocksize;
	private: System::Windows::Forms::Button^  ButtonOk;
	private: System::Windows::Forms::Button^  ButtonCancel;



	private: System::Windows::Forms::CheckBox^  CheckboxStartOnApply;

	private:
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ConfigWindow::typeid));
			this->ComboOutputStreamSource = (gcnew System::Windows::Forms::ComboBox());
			this->StaticLabelOutputStreamSource = (gcnew System::Windows::Forms::Label());
			this->GroupStreamConfig = (gcnew System::Windows::Forms::GroupBox());
			this->ComboInputStreamSource = (gcnew System::Windows::Forms::ComboBox());
			this->StaticLabelInputStreamSource = (gcnew System::Windows::Forms::Label());
			this->GroupProcessing = (gcnew System::Windows::Forms::GroupBox());
			this->ComboInputStreamBlocksize = (gcnew System::Windows::Forms::ComboBox());
			this->StaticLabelBlocksize = (gcnew System::Windows::Forms::Label());
			this->ButtonOk = (gcnew System::Windows::Forms::Button());
			this->ButtonCancel = (gcnew System::Windows::Forms::Button());
			this->CheckboxStartOnApply = (gcnew System::Windows::Forms::CheckBox());
			this->GroupStreamConfig->SuspendLayout();
			this->GroupProcessing->SuspendLayout();
			this->SuspendLayout();
			// 
			// ComboOutputStreamSource
			// 
			this->ComboOutputStreamSource->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComboOutputStreamSource->FormattingEnabled = true;
			this->ComboOutputStreamSource->Location = System::Drawing::Point(92, 50);
			this->ComboOutputStreamSource->Name = L"ComboOutputStreamSource";
			this->ComboOutputStreamSource->Size = System::Drawing::Size(165, 21);
			this->ComboOutputStreamSource->TabIndex = 2;
			// 
			// StaticLabelOutputStreamSource
			// 
			this->StaticLabelOutputStreamSource->AutoSize = true;
			this->StaticLabelOutputStreamSource->Location = System::Drawing::Point(6, 53);
			this->StaticLabelOutputStreamSource->Name = L"StaticLabelOutputStreamSource";
			this->StaticLabelOutputStreamSource->Size = System::Drawing::Size(74, 13);
			this->StaticLabelOutputStreamSource->TabIndex = 0;
			this->StaticLabelOutputStreamSource->Text = L"Output device";
			// 
			// GroupStreamConfig
			// 
			this->GroupStreamConfig->Controls->Add(this->ComboInputStreamSource);
			this->GroupStreamConfig->Controls->Add(this->ComboOutputStreamSource);
			this->GroupStreamConfig->Controls->Add(this->StaticLabelInputStreamSource);
			this->GroupStreamConfig->Controls->Add(this->StaticLabelOutputStreamSource);
			this->GroupStreamConfig->Location = System::Drawing::Point(12, 72);
			this->GroupStreamConfig->Name = L"GroupStreamConfig";
			this->GroupStreamConfig->Size = System::Drawing::Size(266, 86);
			this->GroupStreamConfig->TabIndex = 14;
			this->GroupStreamConfig->TabStop = false;
			this->GroupStreamConfig->Text = L"Input/Output";
			// 
			// ComboInputStreamSource
			// 
			this->ComboInputStreamSource->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComboInputStreamSource->FormattingEnabled = true;
			this->ComboInputStreamSource->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->ComboInputStreamSource->Location = System::Drawing::Point(92, 23);
			this->ComboInputStreamSource->Name = L"ComboInputStreamSource";
			this->ComboInputStreamSource->Size = System::Drawing::Size(165, 21);
			this->ComboInputStreamSource->TabIndex = 2;
			// 
			// StaticLabelInputStreamSource
			// 
			this->StaticLabelInputStreamSource->AutoSize = true;
			this->StaticLabelInputStreamSource->Location = System::Drawing::Point(6, 26);
			this->StaticLabelInputStreamSource->Name = L"StaticLabelInputStreamSource";
			this->StaticLabelInputStreamSource->Size = System::Drawing::Size(66, 13);
			this->StaticLabelInputStreamSource->TabIndex = 0;
			this->StaticLabelInputStreamSource->Text = L"Input device";
			// 
			// GroupProcessing
			// 
			this->GroupProcessing->Controls->Add(this->ComboInputStreamBlocksize);
			this->GroupProcessing->Controls->Add(this->StaticLabelBlocksize);
			this->GroupProcessing->Location = System::Drawing::Point(12, 12);
			this->GroupProcessing->Name = L"GroupProcessing";
			this->GroupProcessing->Size = System::Drawing::Size(266, 54);
			this->GroupProcessing->TabIndex = 16;
			this->GroupProcessing->TabStop = false;
			this->GroupProcessing->Text = L"Processing";
			// 
			// ComboInputStreamBlocksize
			// 
			this->ComboInputStreamBlocksize->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComboInputStreamBlocksize->FormattingEnabled = true;
			this->ComboInputStreamBlocksize->Items->AddRange(gcnew cli::array< System::Object^  >(11) {
				L"64", L"128", L"256", L"512",
					L"1024", L"2048", L"4096", L"8192", L"16384", L"32768", L"65536"
			});
			this->ComboInputStreamBlocksize->Location = System::Drawing::Point(92, 19);
			this->ComboInputStreamBlocksize->Name = L"ComboInputStreamBlocksize";
			this->ComboInputStreamBlocksize->Size = System::Drawing::Size(165, 21);
			this->ComboInputStreamBlocksize->TabIndex = 5;
			// 
			// StaticLabelBlocksize
			// 
			this->StaticLabelBlocksize->AutoSize = true;
			this->StaticLabelBlocksize->Location = System::Drawing::Point(6, 22);
			this->StaticLabelBlocksize->Name = L"StaticLabelBlocksize";
			this->StaticLabelBlocksize->Size = System::Drawing::Size(55, 13);
			this->StaticLabelBlocksize->TabIndex = 4;
			this->StaticLabelBlocksize->Text = L"Block size";
			// 
			// ButtonOk
			// 
			this->ButtonOk->Location = System::Drawing::Point(123, 164);
			this->ButtonOk->Name = L"ButtonOk";
			this->ButtonOk->Size = System::Drawing::Size(75, 23);
			this->ButtonOk->TabIndex = 17;
			this->ButtonOk->Text = L"OK";
			this->ButtonOk->UseVisualStyleBackColor = true;
			this->ButtonOk->Click += gcnew System::EventHandler(this, &ConfigWindow::ButtonOk_Click);
			// 
			// ButtonCancel
			// 
			this->ButtonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->ButtonCancel->Location = System::Drawing::Point(204, 164);
			this->ButtonCancel->Name = L"ButtonCancel";
			this->ButtonCancel->Size = System::Drawing::Size(75, 23);
			this->ButtonCancel->TabIndex = 18;
			this->ButtonCancel->Text = L"Cancel";
			this->ButtonCancel->UseVisualStyleBackColor = true;
			// 
			// CheckboxStartOnApply
			// 
			this->CheckboxStartOnApply->AutoSize = true;
			this->CheckboxStartOnApply->Location = System::Drawing::Point(13, 168);
			this->CheckboxStartOnApply->Name = L"CheckboxStartOnApply";
			this->CheckboxStartOnApply->Size = System::Drawing::Size(91, 17);
			this->CheckboxStartOnApply->TabIndex = 19;
			this->CheckboxStartOnApply->Text = L"Start on apply";
			this->CheckboxStartOnApply->UseVisualStyleBackColor = true;
			this->CheckboxStartOnApply->Visible = false;
			// 
			// ConfigWindow
			// 
			this->AcceptButton = this->ButtonOk;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->ButtonCancel;
			this->ClientSize = System::Drawing::Size(288, 196);
			this->Controls->Add(this->CheckboxStartOnApply);
			this->Controls->Add(this->ButtonCancel);
			this->Controls->Add(this->ButtonOk);
			this->Controls->Add(this->GroupProcessing);
			this->Controls->Add(this->GroupStreamConfig);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"ConfigWindow";
			this->Text = L"Stream configuration";
			this->GroupStreamConfig->ResumeLayout(false);
			this->GroupStreamConfig->PerformLayout();
			this->GroupProcessing->ResumeLayout(false);
			this->GroupProcessing->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private:
		void CustomInitCode()
		{
			CheckboxStartOnApply->Visible = !IoManager::GetInstance()->IsProcessing();

			int CurrentIn, CurrentOut, Blocksize;
			int A, B;
			std::vector<AudioDevice> InDevices, OutDevices;
			IoManager::GetInstance()->GetCurrentConfig(CurrentIn, A, CurrentOut, B, InDevices, OutDevices, Blocksize);

			int InputDevicesCount = InDevices.size();
			int OutputDevicesCount = OutDevices.size();

			for (int i = 0; i < InputDevicesCount; ++i)
			{
				System::String^ Str = gcnew System::String(InDevices[i].DeviceName.c_str());
				ComboInputStreamSource->Items->Add(Str);
			}

			for (int i = 0; i < OutputDevicesCount; ++i)
			{
				System::String^ Str = gcnew System::String(OutDevices[i].DeviceName.c_str());
				ComboOutputStreamSource->Items->Add(Str);
			}

			int BlocksizeSelectedIndex = 0;
			Blocksize /= 64;
			while (Blocksize > 1)
			{
				BlocksizeSelectedIndex++;
				Blocksize /= 2;
			}

			ComboInputStreamBlocksize->SelectedIndex = BlocksizeSelectedIndex;
			ComboInputStreamSource->SelectedIndex = CurrentIn;
			ComboOutputStreamSource->SelectedIndex = CurrentOut;
		}

		//Interfejs ConfigWindow
		System::Void ButtonOk_Click(System::Object^  sender, System::EventArgs^  e)
		{
			IoManager::GetInstance()->SetNewConfig(
				ComboInputStreamSource->SelectedIndex,
				ComboOutputStreamSource->SelectedIndex,
				ComboInputStreamBlocksize->SelectedIndex,
				CheckboxStartOnApply->Checked
			);

			this->Close();
		}
};
}
