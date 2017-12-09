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
	/// Dynamiczne okno wizualizacji dla pluginów z jej obs³ug¹
	/// (flaga DspPlugin::HasVisualization ustawiona na HAS_VIZ).
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
	private: System::Windows::Forms::Timer^  RefreshTimer;
	private: System::Windows::Forms::ContextMenuStrip^  SettingsContext;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItemToggleMuted;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItemRefreshRateList;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItemRefresh10;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItemRefresh16;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItemRefresh25;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItemRefresh33;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItemRefresh50;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItemRefresh100;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItemSaveImage;
	private: System::Windows::Forms::SaveFileDialog^  SaveImageDialog;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::IContainer^  components;

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
			this->SettingsContext = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->MenuItemToggleMuted = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItemRefreshRateList = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItemRefresh10 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItemRefresh16 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItemRefresh25 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItemRefresh33 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItemRefresh50 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItemRefresh100 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItemSaveImage = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SaveImageDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureTarget))->BeginInit();
			this->SettingsContext->SuspendLayout();
			this->SuspendLayout();
			// 
			// PictureTarget
			// 
			this->PictureTarget->Location = System::Drawing::Point(0, 0);
			this->PictureTarget->Name = L"PictureTarget";
			this->PictureTarget->Size = System::Drawing::Size(484, 461);
			this->PictureTarget->TabIndex = 0;
			this->PictureTarget->TabStop = false;
			this->PictureTarget->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &DynamicPluginVizWindow::PictureTarget_Click);
			// 
			// RefreshTimer
			// 
			this->RefreshTimer->Enabled = true;
			this->RefreshTimer->Interval = 16;
			this->RefreshTimer->Tick += gcnew System::EventHandler(this, &DynamicPluginVizWindow::ImageTick);
			// 
			// SettingsContext
			// 
			this->SettingsContext->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->MenuItemToggleMuted,
					this->MenuItemRefreshRateList, this->MenuItemSaveImage
			});
			this->SettingsContext->Name = L"SettingsContext";
			this->SettingsContext->Size = System::Drawing::Size(153, 70);
			// 
			// MenuItemToggleMuted
			// 
			this->MenuItemToggleMuted->Name = L"MenuItemToggleMuted";
			this->MenuItemToggleMuted->Size = System::Drawing::Size(152, 22);
			this->MenuItemToggleMuted->Text = L"Pause/Resume";
			this->MenuItemToggleMuted->Click += gcnew System::EventHandler(this, &DynamicPluginVizWindow::MenuItemToggleMuted_Click);
			// 
			// MenuItemRefreshRateList
			// 
			this->MenuItemRefreshRateList->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->MenuItemRefresh10,
					this->MenuItemRefresh16, this->MenuItemRefresh25, this->MenuItemRefresh33, this->MenuItemRefresh50, this->MenuItemRefresh100
			});
			this->MenuItemRefreshRateList->Name = L"MenuItemRefreshRateList";
			this->MenuItemRefreshRateList->Size = System::Drawing::Size(152, 22);
			this->MenuItemRefreshRateList->Text = L"Refresh rate";
			// 
			// MenuItemRefresh10
			// 
			this->MenuItemRefresh10->Name = L"MenuItemRefresh10";
			this->MenuItemRefresh10->Size = System::Drawing::Size(108, 22);
			this->MenuItemRefresh10->Text = L"10ms";
			this->MenuItemRefresh10->Click += gcnew System::EventHandler(this, &DynamicPluginVizWindow::RequestChangeRefreshRate_Click);
			// 
			// MenuItemRefresh16
			// 
			this->MenuItemRefresh16->Name = L"MenuItemRefresh16";
			this->MenuItemRefresh16->Size = System::Drawing::Size(108, 22);
			this->MenuItemRefresh16->Text = L"16ms";
			this->MenuItemRefresh16->Click += gcnew System::EventHandler(this, &DynamicPluginVizWindow::RequestChangeRefreshRate_Click);
			// 
			// MenuItemRefresh25
			// 
			this->MenuItemRefresh25->Name = L"MenuItemRefresh25";
			this->MenuItemRefresh25->Size = System::Drawing::Size(108, 22);
			this->MenuItemRefresh25->Text = L"25ms";
			this->MenuItemRefresh25->Click += gcnew System::EventHandler(this, &DynamicPluginVizWindow::RequestChangeRefreshRate_Click);
			// 
			// MenuItemRefresh33
			// 
			this->MenuItemRefresh33->Name = L"MenuItemRefresh33";
			this->MenuItemRefresh33->Size = System::Drawing::Size(108, 22);
			this->MenuItemRefresh33->Text = L"33ms";
			this->MenuItemRefresh33->Click += gcnew System::EventHandler(this, &DynamicPluginVizWindow::RequestChangeRefreshRate_Click);
			// 
			// MenuItemRefresh50
			// 
			this->MenuItemRefresh50->Name = L"MenuItemRefresh50";
			this->MenuItemRefresh50->Size = System::Drawing::Size(108, 22);
			this->MenuItemRefresh50->Text = L"50ms";
			this->MenuItemRefresh50->Click += gcnew System::EventHandler(this, &DynamicPluginVizWindow::RequestChangeRefreshRate_Click);
			// 
			// MenuItemRefresh100
			// 
			this->MenuItemRefresh100->Name = L"MenuItemRefresh100";
			this->MenuItemRefresh100->Size = System::Drawing::Size(108, 22);
			this->MenuItemRefresh100->Text = L"100ms";
			this->MenuItemRefresh100->Click += gcnew System::EventHandler(this, &DynamicPluginVizWindow::RequestChangeRefreshRate_Click);
			// 
			// MenuItemSaveImage
			// 
			this->MenuItemSaveImage->Name = L"MenuItemSaveImage";
			this->MenuItemSaveImage->Size = System::Drawing::Size(152, 22);
			this->MenuItemSaveImage->Text = L"Save as BMP";
			this->MenuItemSaveImage->Click += gcnew System::EventHandler(this, &DynamicPluginVizWindow::MenuItemSaveImage_Click);
			// 
			// SaveImageDialog
			// 
			this->SaveImageDialog->DefaultExt = L"bmp";
			this->SaveImageDialog->FileName = L"SavedImage.bmp";
			this->SaveImageDialog->Filter = L"Bitmap (*.bmp)|*.bmp";
			this->SaveImageDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &DynamicPluginVizWindow::SaveImageDialog_FileOk);
			// 
			// DynamicPluginVizWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(484, 461);
			this->Controls->Add(this->PictureTarget);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(900, 900);
			this->MinimumSize = System::Drawing::Size(220, 220);
			this->Name = L"DynamicPluginVizWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"DynamicPluginVizWindow";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &DynamicPluginVizWindow::DynamicPluginVizWindow_FormClosed);
			this->Resize += gcnew System::EventHandler(this, &DynamicPluginVizWindow::DynamicPluginVizWindow_Resize);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureTarget))->EndInit();
			this->SettingsContext->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	public:
		bool IsOpened = false;
		Void SetIndex(Int32 NewIndex) { PluginIndex = NewIndex; }

	private:
		Int32 PluginIndex = -1;
		bool IsFirstFrameDrawn = false;
		Graphics^ Img;
		Bitmap^ ImgPtr;

		Void ReinitializePicture()
		{
			ImgPtr = gcnew Bitmap(PictureTarget->Width, PictureTarget->Height);
			PictureTarget->Image = ImgPtr;
			PictureTarget->SizeMode = PictureBoxSizeMode::Normal;
			Img = Graphics::FromImage(PictureTarget->Image);
			Img->SmoothingMode = Drawing2D::SmoothingMode::None;
			Img->Clear(Color::White);
			PictureTarget->Refresh();
			IsFirstFrameDrawn = false;
		}

		System::Void ImageTick(System::Object^  sender, System::EventArgs^  e)
		{
			if (PluginIndex < 0) return;
			AudioProcessor::GetInstance()->AskPluginForRedraw(PluginIndex, Img, ImgPtr, PictureTarget->Width, PictureTarget->Height, IsFirstFrameDrawn);
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
		System::Void PictureTarget_Click(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			if (e->Button != System::Windows::Forms::MouseButtons::Right) return;
			SettingsContext->Show();
			SettingsContext->Location = MousePosition;
		}
		System::Void RequestChangeRefreshRate_Click(System::Object^  sender, System::EventArgs^  e)
		{
			ToolStripMenuItem^ Item = (cli::safe_cast<ToolStripMenuItem^>(sender));
			if (Item == MenuItemRefresh10) { RefreshTimer->Interval = 10;  return; }
			if (Item == MenuItemRefresh16) { RefreshTimer->Interval = 15;  return; }
			if (Item == MenuItemRefresh25) { RefreshTimer->Interval = 25;  return; }
			if (Item == MenuItemRefresh33) { RefreshTimer->Interval = 32;  return; }
			if (Item == MenuItemRefresh50) { RefreshTimer->Interval = 50;  return; }
			if (Item == MenuItemRefresh100) { RefreshTimer->Interval = 100; return; }
		}
		System::Void MenuItemToggleMuted_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (RefreshTimer->Enabled) RefreshTimer->Stop();
			else RefreshTimer->Start();
		}
		System::Void MenuItemSaveImage_Click(System::Object^  sender, System::EventArgs^  e)
		{
			SaveImageDialog->ShowDialog();
		}
		System::Void SaveImageDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
		{
			try
			{
				PictureTarget->Image->Save(SaveImageDialog->FileName, Imaging::ImageFormat::Bmp);

			}
			catch (Exception^ e)
			{
				Utilities::ShowMessagebox("Could not save file. Error: " + e->ToString());
			}
		}
	};
}
