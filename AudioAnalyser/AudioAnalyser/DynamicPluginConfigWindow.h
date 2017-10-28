#pragma once
#include "AudioProcessor.h"

namespace AudioAnalyser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Summary for DynamicPluginConfigWindow
	/// </summary>
	public ref class DynamicPluginConfigWindow : public System::Windows::Forms::Form
	{
	public:
		DynamicPluginConfigWindow(void)
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
		~DynamicPluginConfigWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: RackControls::DynamicControlObject^  DynamicControlObject0;
	private: System::Collections::Generic::List<RackControls::DynamicControlObject^>^ ControlObjects = gcnew System::Collections::Generic::List<RackControls::DynamicControlObject^>();
	protected:

	protected:

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(DynamicPluginConfigWindow::typeid));
			this->DynamicControlObject0 = (gcnew RackControls::DynamicControlObject());
			this->SuspendLayout();
			// 
			// DynamicControlObject0
			// 
			this->DynamicControlObject0->Location = System::Drawing::Point(8, 10);
			this->DynamicControlObject0->Name = L"DynamicControlObject0";
			this->DynamicControlObject0->ParameterIndex = 0;
			this->DynamicControlObject0->Size = System::Drawing::Size(350, 50);
			this->DynamicControlObject0->TabIndex = 0;
			this->DynamicControlObject0->Visible = false;
			this->DynamicControlObject0->UpdateParameter += gcnew RackControls::UpdateParameter(this, &DynamicPluginConfigWindow::DynamicControlObject0_UpdateParameter);
			// 
			// DynamicPluginConfigWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(365, 65);
			this->Controls->Add(this->DynamicControlObject0);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"DynamicPluginConfigWindow";
			this->Text = L"DynamicPluginConfigWindow";
			this->ResumeLayout(false);

		}
#pragma endregion

		Int32 PluginIndex = -1;
	public:
		System::Void PopulateWithParameters(std::vector<DspPluginParameter*> Parameters, System::Int32 PluginIndex)
		{
			this->SuspendLayout();
			this->PluginIndex = PluginIndex;

			for (int i = 0; i < Parameters.size(); ++i)
			{
				RackControls::DynamicControlObject ^ TempObj = (gcnew RackControls::DynamicControlObject());
				TempObj->FeedWithParameterData(Parameters[i], i);
			
				TempObj->Location = System::Drawing::Point(8, 10 + (i * 55));
				TempObj->Name = L"DynamicControlObject" + i.ToString();
				TempObj->Size = System::Drawing::Size(350, 50);
				TempObj->TabIndex = 0;
				TempObj->Visible = true;
				TempObj->UpdateParameter += gcnew RackControls::UpdateParameter(this, &DynamicPluginConfigWindow::DynamicControlObject0_UpdateParameter);
				this->Controls->Add(TempObj);

				this->ControlObjects->Add(TempObj);
			}

			this->ClientSize = System::Drawing::Size(365, (Parameters.size() * 55) - 10);
			System::String^ WindowName = gcnew System::String(AudioProcessor::GetInstance()->GetPluginName(PluginIndex).c_str());
			WindowName += L" at Slot #";
			WindowName += (PluginIndex + 1).ToString();

			this->Name = WindowName;
			this->Text = WindowName;


			this->ResumeLayout(false);
		}
	
	private:
	
		System::Void DynamicControlObject0_UpdateParameter(System::Int32 AtIndex, System::Single NewValue)
		{
			AudioProcessor::GetInstance()->UpdatePluginParameter(PluginIndex, AtIndex, NewValue);
		}

	};
}
