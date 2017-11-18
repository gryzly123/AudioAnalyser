#pragma once
#include "AudioProcessor.h"

namespace AudioAnalyser
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;


	public delegate void ConvertSoundDataToImageDelegate(float*, int);
	public delegate void InterthreadDelegate();
	/// <summary>
	/// Summary for DynamicVizWindow
	/// </summary>
	public ref class DynamicVizWindow : public System::Windows::Forms::Form
	{
	public:
		DynamicVizWindow(void)
		{
			InitializeComponent();
			InitializeImage();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DynamicVizWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(13, 13);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(728, 430);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// DynamicVizWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(753, 455);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"DynamicVizWindow";
			this->Text = L"DynamicVizWindow";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		Graphics^ Img;


		Void InitializeImage()
		{
			pictureBox1->Image = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
			pictureBox1->SizeMode = PictureBoxSizeMode::Normal;
			Img = Graphics::FromImage(pictureBox1->Image);
			Img->SmoothingMode = Drawing2D::SmoothingMode::HighQuality;
			Img->Clear(Color::White);
			pictureBox1->Refresh();
			
			Conv += gcnew ConvertSoundDataToImageDelegate(this, &DynamicVizWindow::ConvertSoundDataToImage);
			GCHandle gch = GCHandle::Alloc(Conv);
			IntPtr FuncPtr = Marshal::GetFunctionPointerForDelegate(Conv);
			AudioProcessor::GetInstance()->FeedData = static_cast<PluginDataCallback>(FuncPtr.ToPointer());
		}

	public:

		
		ConvertSoundDataToImageDelegate^ Conv;
		Single* Dt;
		ArrayList Ls;
		
		Void ConvertSoundDataToImage(Single* Data, Int32 Length)
		{
			Ls.Clear();
			for(int i = 0; i < Length; ++i) Ls.Add(Data[i]);
			this->BeginInvoke(gcnew InterthreadDelegate(this, &DynamicVizWindow::UiConvertSoundDataToImage));
		}

		Void UiConvertSoundDataToImage()
		{
			//Monitor::Enter(Img);
			//Monitor::Enter(pictureBox1);
			int MaxPoints = pictureBox1->Width;
			int Range = pictureBox1->Height;

			Img->Clear(Color::White);
			Pen^ Pencil = gcnew Pen(Color::Black, 1);

			for (int i = 0; i < Ls.Count && i < MaxPoints; ++i)
			{
				//System::String^ Dbg = "Attempting to draw line from (" + i.ToString() + ", " + ((int)(Range / 2)).ToString()
				//	+ ") to (" + i.ToString() + ", " + ((int)(Range / 2 + (Single)Ls[i])).ToString() + ")";
				//MessageBox::Show(Dbg);

				Img->DrawLine(Pencil, i, (int)(Range / 2), i, (int)(Range / 2 + (200.f * (Single)Ls[i])));
			}

			pictureBox1->Refresh();
			//Monitor::Exit(Img);
			//Monitor::Exit(pictureBox1);
		}

	};
}
