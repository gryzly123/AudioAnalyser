#pragma once
#include "../AudioAnalyser//DspPlugin.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace RackControls {

	/// <summary>
	/// Summary for DynamicControlObject
	/// </summary>

	public delegate System::Void UpdateParameter(Int32, Single);


	public ref class DynamicControlObject : public System::Windows::Forms::UserControl
	{
	public:
		property Int32 ParameterIndex;
		Int32 EnumMinimum;
		float StepSize = 10;

		DynamicControlObject(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DynamicControlObject()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TrackBar^  TrackbarFloatVal;
	protected:
	private: System::Windows::Forms::Label^  LabelFloatVal;
	private: System::Windows::Forms::ComboBox^  ListEnumValue;
	private: System::Windows::Forms::Label^  LabelParamName;
	private: System::Windows::Forms::CheckBox^  CheckBoolVal;
	public:  event UpdateParameter^ UpdateParameter;

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
			this->TrackbarFloatVal = (gcnew System::Windows::Forms::TrackBar());
			this->LabelFloatVal = (gcnew System::Windows::Forms::Label());
			this->ListEnumValue = (gcnew System::Windows::Forms::ComboBox());
			this->LabelParamName = (gcnew System::Windows::Forms::Label());
			this->CheckBoolVal = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackbarFloatVal))->BeginInit();
			this->SuspendLayout();
			// 
			// TrackbarFloatVal
			// 
			this->TrackbarFloatVal->Location = System::Drawing::Point(129, 3);
			this->TrackbarFloatVal->Name = L"TrackbarFloatVal";
			this->TrackbarFloatVal->Size = System::Drawing::Size(148, 45);
			this->TrackbarFloatVal->TabIndex = 0;
			this->TrackbarFloatVal->Scroll += gcnew System::EventHandler(this, &DynamicControlObject::TrackbarFloatVal_Scroll);
			// 
			// LabelFloatVal
			// 
			this->LabelFloatVal->Location = System::Drawing::Point(283, 3);
			this->LabelFloatVal->Name = L"LabelFloatVal";
			this->LabelFloatVal->Size = System::Drawing::Size(64, 17);
			this->LabelFloatVal->TabIndex = 1;
			this->LabelFloatVal->Text = L"0.0";
			this->LabelFloatVal->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// ListEnumValue
			// 
			this->ListEnumValue->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ListEnumValue->FormattingEnabled = true;
			this->ListEnumValue->Location = System::Drawing::Point(129, 0);
			this->ListEnumValue->Name = L"ListEnumValue";
			this->ListEnumValue->Size = System::Drawing::Size(148, 21);
			this->ListEnumValue->TabIndex = 2;
			this->ListEnumValue->SelectedIndexChanged += gcnew System::EventHandler(this, &DynamicControlObject::ListEnumValue_SelectedIndexChanged);
			// 
			// LabelParamName
			// 
			this->LabelParamName->Location = System::Drawing::Point(3, 3);
			this->LabelParamName->Name = L"LabelParamName";
			this->LabelParamName->Size = System::Drawing::Size(120, 17);
			this->LabelParamName->TabIndex = 3;
			this->LabelParamName->Text = L"Parameter name";
			// 
			// CheckBoolVal
			// 
			this->CheckBoolVal->AutoSize = true;
			this->CheckBoolVal->Location = System::Drawing::Point(136, 2);
			this->CheckBoolVal->Name = L"CheckBoolVal";
			this->CheckBoolVal->Size = System::Drawing::Size(15, 14);
			this->CheckBoolVal->TabIndex = 4;
			this->CheckBoolVal->UseVisualStyleBackColor = true;
			this->CheckBoolVal->CheckedChanged += gcnew System::EventHandler(this, &DynamicControlObject::CheckBoolVal_CheckedChanged);
			// 
			// DynamicControlObject
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->CheckBoolVal);
			this->Controls->Add(this->LabelParamName);
			this->Controls->Add(this->ListEnumValue);
			this->Controls->Add(this->LabelFloatVal);
			this->Controls->Add(this->TrackbarFloatVal);
			this->Name = L"DynamicControlObject";
			this->Size = System::Drawing::Size(350, 50);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackbarFloatVal))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public:
		System::Void FeedWithParameterData(const DspPluginParameter* Parameter, System::Int32 ParameterIndex)
		{
			this->ParameterIndex = ParameterIndex;
			this->LabelParamName->Text = gcnew System::String(Parameter->Name.c_str());


			switch (Parameter->Type)
			{
				case DspPluginParameterType::PT_Boolean:

					this->ListEnumValue->Visible = false;
					this->LabelFloatVal->Visible = false;
					this->TrackbarFloatVal->Visible = false;
					this->CheckBoolVal->Visible = true;
					this->CheckBoolVal->Checked = Parameter->CurrentValue;


				break;
				case DspPluginParameterType::PT_Enum:

					this->ListEnumValue->Visible = true;
					this->LabelFloatVal->Visible = false;
					this->TrackbarFloatVal->Visible = false;
					this->CheckBoolVal->Visible = false;

					for (int i = 0; i < Parameter->MaximumValue; i++)
					{
						this->ListEnumValue->Items->Add(gcnew System::String(Parameter->EnumNames[i].c_str()));
					}

				break;
				case DspPluginParameterType::PT_Float:

					this->ListEnumValue->Visible = false;
					this->LabelFloatVal->Visible = true;
					this->TrackbarFloatVal->Visible = true;
					this->CheckBoolVal->Visible = false;

					this->TrackbarFloatVal->Minimum = Parameter->MinimumValue * StepSize;
					this->TrackbarFloatVal->Maximum = Parameter->MaximumValue * StepSize;
					this->TrackbarFloatVal->Value   = Parameter->CurrentValue * StepSize;

					UpdateFloatLabel();

				break;
			}
		}

		System::Void UpdateFloatLabel()
		{
			LabelFloatVal->Text = (this->TrackbarFloatVal->Value / StepSize).ToString();
		}
	
		System::Void ListEnumValue_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		{
			UpdateParameter(ParameterIndex, ListEnumValue->SelectedIndex);
		}

		System::Void CheckBoolVal_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			UpdateParameter(ParameterIndex, CheckBoolVal->Checked);
		}

		System::Void TrackbarFloatVal_Scroll(System::Object^  sender, System::EventArgs^  e)
		{
			Single Value = (Single)TrackbarFloatVal->Value / StepSize;
			UpdateParameter(ParameterIndex, Value);
			UpdateFloatLabel();
		}
};
}
