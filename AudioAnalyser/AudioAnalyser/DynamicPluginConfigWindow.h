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

		event WindowShutdown^ OnWindowShutdown;
		bool IsOpened = false;

		DynamicPluginConfigWindow(void)
		{
			InitializeComponent();
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
	private: RackControls::DynamicControlObject^  DynamicControlObject;
	private: System::Collections::Generic::List<RackControls::DynamicControlObject^>^ ControlObjects = gcnew System::Collections::Generic::List<RackControls::DynamicControlObject^>();
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
			this->DynamicControlObject = (gcnew RackControls::DynamicControlObject());
			this->SuspendLayout();
			// 
			// DynamicControlObject
			// 
			this->DynamicControlObject->Location = System::Drawing::Point(8, 10);
			this->DynamicControlObject->Name = L"DynamicControlObject";
			this->DynamicControlObject->ParameterIndex = 0;
			this->DynamicControlObject->Size = System::Drawing::Size(350, 40);
			this->DynamicControlObject->TabIndex = 0;
			this->DynamicControlObject->Visible = false;
			this->DynamicControlObject->UpdateParameter += gcnew RackControls::UpdateParameter(this, &DynamicPluginConfigWindow::DynamicControlObject_UpdateParameter);
			// 
			// DynamicPluginConfigWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(365, 65);
			this->Controls->Add(this->DynamicControlObject);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"DynamicPluginConfigWindow";
			this->Text = L"DynamicPluginConfigWindow";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &DynamicPluginConfigWindow::DynamicPluginConfigWindow_FormClosed);
			this->ResumeLayout(false);

		}
#pragma endregion

		Int32 PluginIndex = -1;
	public:
		System::Void PopulateWithParameters(std::vector<DspPluginParameter*> Parameters, System::Int32 PluginIndex)
		{
			this->SuspendLayout();
			this->PluginIndex = PluginIndex;
			System::Int32 ParametersCount = Parameters.size();

			this->ClientSize = System::Drawing::Size(365, (ParametersCount * 40) + 6);
			System::String^ WindowName = gcnew System::String(AudioProcessor::GetInstance()->GetPluginName(PluginIndex).c_str());
			WindowName += L" at Slot #";
			WindowName += (PluginIndex + 1).ToString();

			this->Name = WindowName;
			this->Text = WindowName;

			for (int i = 0; i < ParametersCount; ++i)
			{
				RackControls::DynamicControlObject ^ TempObj = (gcnew RackControls::DynamicControlObject());
				TempObj->FeedWithParameterData(Parameters[i], i);
				TempObj->Location = System::Drawing::Point(8, 10 + (i * 40));
				TempObj->Name = L"DynamicControlObject" + i.ToString();
				TempObj->Size = System::Drawing::Size(350, 40);
				TempObj->TabIndex = 0;
				TempObj->Visible = true;
				TempObj->UpdateParameter += gcnew RackControls::UpdateParameter(this, &DynamicPluginConfigWindow::DynamicControlObject_UpdateParameter);
				this->Controls->Add(TempObj);
				this->ControlObjects->Add(TempObj);
			}

			this->ResumeLayout(false);
		}
	
	private:
	
		System::Void DynamicControlObject_UpdateParameter(System::Int32 AtIndex, System::Single NewValue)
		{
			AudioProcessor::GetInstance()->UpdatePluginParameterByIndex(PluginIndex, AtIndex, NewValue);
		}
		System::Void DynamicPluginConfigWindow_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e)
		{
			OnWindowShutdown(PluginIndex);
		}
	};
}
