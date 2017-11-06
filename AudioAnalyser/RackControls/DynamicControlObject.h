#pragma once
#define FROM_RACK_CONTROLS
#include "../AudioAnalyser/DspPlugin.h"
#undef FROM_RACK_CONTROLS

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
		private: System::Windows::Forms::TextBox^  TextboxFloatVal;
		public:
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
			this->TextboxFloatVal = (gcnew System::Windows::Forms::TextBox());
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
			this->LabelFloatVal->DoubleClick += gcnew System::EventHandler(this, &DynamicControlObject::LabelFloatVal_DoubleClick);
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
			// TextboxFloatVal
			// 
			this->TextboxFloatVal->Location = System::Drawing::Point(283, 1);
			this->TextboxFloatVal->Name = L"TextboxFloatVal";
			this->TextboxFloatVal->Size = System::Drawing::Size(64, 20);
			this->TextboxFloatVal->TabIndex = 5;
			this->TextboxFloatVal->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->TextboxFloatVal->Visible = false;
			this->TextboxFloatVal->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &DynamicControlObject::TextboxFloatVal_KeyDown);
			this->TextboxFloatVal->Leave += gcnew System::EventHandler(this, &DynamicControlObject::TextboxFloatVal_Leave);
			// 
			// DynamicControlObject
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->TextboxFloatVal);
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
			//Inicjalizacja
			System::Void FeedWithParameterData(const DspPluginParameter* Parameter, System::Int32 ParameterIndex)
		{
			this->ParameterIndex = ParameterIndex;
			this->LabelParamName->Text = gcnew System::String(Parameter->Name.c_str());
			StepSize = 1 / Parameter->FloatValueStep;

			switch (Parameter->Type)
			{
				case DspPluginParameterType::PT_Boolean:

					this->ListEnumValue->Visible = false;
					this->LabelFloatVal->Visible = false;
					this->TrackbarFloatVal->Visible = false;
					this->CheckBoolVal->Visible = true;
					this->CheckBoolVal->Checked = Parameter->CurrentValue > 0 ? true : false;


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

					this->ListEnumValue->SelectedIndex = (int)Parameter->CurrentValue;

				break;
				case DspPluginParameterType::PT_Float:

					this->ListEnumValue->Visible = false;
					this->LabelFloatVal->Visible = true;
					this->TrackbarFloatVal->Visible = true;
					this->CheckBoolVal->Visible = false;

					this->TrackbarFloatVal->Minimum = (int)(Parameter->MinimumValue * StepSize);
					this->TrackbarFloatVal->Maximum = (int)(Parameter->MaximumValue * StepSize);
					this->TrackbarFloatVal->Value   = (int)(Parameter->CurrentValue * StepSize);

					UpdateFloatLabel();

				break;
			}
		}

			//Interfejs DynamicControlObject
			System::Void UpdateFloatLabel()
		{
			LabelFloatVal->Text = (this->TrackbarFloatVal->Value / StepSize).ToString();
		}
			System::Void LabelFloatVal_DoubleClick(System::Object^  sender, System::EventArgs^  e)
		{
			TextboxFloatVal->Text = LabelFloatVal->Text;
			TextboxFloatVal->SelectionStart = 0;
			TextboxFloatVal->SelectionLength = TextboxFloatVal->Text->Length;
			TextboxFloatVal->Visible = true;
			TextboxFloatVal->Focus();
		}
			System::Void TextboxFloatVal_Leave(System::Object^  sender, System::EventArgs^  e)
		{
			SaveTextboxData();
		}
			System::Void TextboxFloatVal_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^  e)
		{
			if (e->KeyCode == Keys::Enter)
			{
				TrackbarFloatVal->Focus();
				SaveTextboxData();
			}
		}
		
			//Update dla enumeratorów, booleanów i floatów (sliderem i textboxem)
			System::Void ListEnumValue_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		{
			UpdateParameter(ParameterIndex, (float)ListEnumValue->SelectedIndex);
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
			System::Void SaveTextboxData()
		{
			Single NewNumber = 0;
			if (Single::TryParse(TextboxFloatVal->Text, NewNumber))
			{
				Single NewNumberStepped = NewNumber * StepSize;
				if (NewNumberStepped < (float)TrackbarFloatVal->Minimum) NewNumberStepped = (float)TrackbarFloatVal->Minimum;
				if (NewNumberStepped > (float)TrackbarFloatVal->Maximum) NewNumberStepped = (float)TrackbarFloatVal->Maximum;

				TrackbarFloatVal->Value = (int)NewNumberStepped;
				NewNumber = NewNumberStepped / StepSize;
				UpdateParameter(ParameterIndex, NewNumber);
				UpdateFloatLabel();
			}

			TextboxFloatVal->Visible = false;
		}
	};
}
