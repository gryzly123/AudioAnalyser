#pragma once
#include "AudioProcessor.h"

namespace AudioAnalyser
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Data;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;

	public delegate void ConvertSoundDataToImageDelegate(float*, int);
	public delegate void InterthreadDelegate();

	/// <summary>
	/// Summary for DynamicPluginVizWindow
	/// </summary>
	public ref class DynamicPluginVizWindow : public System::Windows::Forms::Form
	{


	public:
		event WindowShutdown^ OnWindowShutdown;

		DynamicPluginVizWindow(void)
		{
			InitializeComponent();
			ReinitializePicture();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DynamicPluginVizWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  PictureTarget;
	protected:

	private: System::Windows::Forms::Timer^  RefreshTimer;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(DynamicPluginVizWindow::typeid));
			this->PictureTarget = (gcnew System::Windows::Forms::PictureBox());
			this->RefreshTimer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureTarget))->BeginInit();
			this->SuspendLayout();
			// 
			// PictureTarget
			// 
			this->PictureTarget->Location = System::Drawing::Point(0, 0);
			this->PictureTarget->Name = L"PictureTarget";
			this->PictureTarget->Size = System::Drawing::Size(484, 461);
			this->PictureTarget->TabIndex = 0;
			this->PictureTarget->TabStop = false;
			// 
			// RefreshTimer
			// 
			this->RefreshTimer->Enabled = true;
			this->RefreshTimer->Interval = 15;
			this->RefreshTimer->Tick += gcnew System::EventHandler(this, &DynamicPluginVizWindow::ImageTick);
			// 
			// DynamicPluginVizWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(484, 461);
			this->Controls->Add(this->PictureTarget);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(900, 900);
			this->MinimumSize = System::Drawing::Size(100, 100);
			this->Name = L"DynamicPluginVizWindow";
			this->Text = L"DynamicPluginVizWindow";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &DynamicPluginVizWindow::DynamicPluginVizWindow_FormClosed);
			this->Resize += gcnew System::EventHandler(this, &DynamicPluginVizWindow::DynamicPluginVizWindow_Resize);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureTarget))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		Int32 PluginIndex = -1;
		bool IsFirstFrameDrawn = false;
		Graphics^ Img;

		Void ReinitializePicture()
		{
			PictureTarget->Image = gcnew Bitmap(PictureTarget->Width, PictureTarget->Height);
			PictureTarget->SizeMode = PictureBoxSizeMode::Normal;
			Img = Graphics::FromImage(PictureTarget->Image);
			Img->SmoothingMode = Drawing2D::SmoothingMode::None;
			Img->Clear(Color::White);
			PictureTarget->Refresh();
			IsFirstFrameDrawn = false;
		}

		Void UiConvertSoundDataToImage()
		{
			////Monitor::Enter(Img);
			////Monitor::Enter(PictureTarget);
			//
			//int MaxPoints = PictureTarget->Width;
			//int Range = PictureTarget->Height;
			//
			//Img->Clear(Color::White);
			//Pen^ Pencil = gcnew Pen(Color::Black, 1);
			//
			//System::Threading::Monitor::Enter(Ls);
			//for (int i = 1; i < Ls->arr.Count && i < MaxPoints; ++i)
			//{
			//	//System::String^ Dbg = "Attempting to draw line from (" + i.ToString() + ", " + ((int)(Range / 2)).ToString()
			//	//	+ ") to (" + i.ToString() + ", " + ((int)(Range / 2 + (Single)Ls[i])).ToString() + ")";
			//	//MessageBox::Show(Dbg);
			//
			//	int y1 = (int)(Range / 2 + (200.f * (Single)Ls->arr[i - 1]));
			//	int y2 = (int)(Range / 2 + (200.f * (Single)Ls->arr[i]));
			//	if (y1 == y2) y2++;
			//	Img->DrawLine(Pencil, i, y1, i, y2);
			//}
			//System::Threading::Monitor::Exit(Ls);
			//
			//PictureTarget->Refresh();
			////Monitor::Exit(Img);
			////Monitor::Exit(PictureTarget);
		}

		System::Void ImageTick(System::Object^  sender, System::EventArgs^  e)
		{
			if (PluginIndex < 0) return;
			AudioProcessor::GetInstance()->AskPluginForRedraw(PluginIndex, Img, PictureTarget->Width, PictureTarget->Height, IsFirstFrameDrawn);
			PictureTarget->Refresh();
			IsFirstFrameDrawn = true;
		}

		System::Void DynamicPluginVizWindow_Resize(System::Object^  sender, System::EventArgs^  e)
		{
			System::Drawing::Size NewPictureSize = this->Size;
			NewPictureSize.Width -= 16;
			NewPictureSize.Height -= 39;
			PictureTarget->Size = NewPictureSize;
			ReinitializePicture();
		}
		System::Void DynamicPluginVizWindow_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e)
		{
			OnWindowShutdown(PluginIndex);
		}

	public:
		bool IsOpened = false;
		Void SetIndex(Int32 NewIndex) { PluginIndex = NewIndex; }
	};
}
