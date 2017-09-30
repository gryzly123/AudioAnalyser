#include "AudioGrabber.h"
#pragma once

namespace first_clr {

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
			//
			//TODO: Add the constructor code here
			//
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
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  Btn_StartGrabbing;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ImageList^  imageList1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: first_clr::RackItem^  rackItem1;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->Btn_StartGrabbing = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->rackItem1 = (gcnew first_clr::RackItem());
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(12, 58);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(260, 21);
			this->comboBox1->TabIndex = 0;
			// 
			// Btn_StartGrabbing
			// 
			this->Btn_StartGrabbing->Location = System::Drawing::Point(145, 85);
			this->Btn_StartGrabbing->Name = L"Btn_StartGrabbing";
			this->Btn_StartGrabbing->Size = System::Drawing::Size(127, 23);
			this->Btn_StartGrabbing->TabIndex = 1;
			this->Btn_StartGrabbing->Text = L"Start Grabbing";
			this->Btn_StartGrabbing->UseVisualStyleBackColor = true;
			this->Btn_StartGrabbing->Click += gcnew System::EventHandler(this, &MainWindow::Btn_StartGrabbing_Click);
			// 
			// button1
			// 
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button1->ImageIndex = 10;
			this->button1->ImageList = this->imageList1;
			this->button1->Location = System::Drawing::Point(58, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(40, 40);
			this->button1->TabIndex = 2;
			this->button1->UseVisualStyleBackColor = true;
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList1->Images->SetKeyName(0, L"appbar.arrow.corner.up.right.png");
			this->imageList1->Images->SetKeyName(1, L"appbar.arrow.down.png");
			this->imageList1->Images->SetKeyName(2, L"appbar.arrow.up.png");
			this->imageList1->Images->SetKeyName(3, L"appbar.cell.down.png");
			this->imageList1->Images->SetKeyName(4, L"appbar.cog.png");
			this->imageList1->Images->SetKeyName(5, L"appbar.control.pause.png");
			this->imageList1->Images->SetKeyName(6, L"appbar.control.play.live.png");
			this->imageList1->Images->SetKeyName(7, L"appbar.control.play.png");
			this->imageList1->Images->SetKeyName(8, L"appbar.control.stop.png");
			this->imageList1->Images->SetKeyName(9, L"appbar.draw.pixel.fill.grid.png");
			this->imageList1->Images->SetKeyName(10, L"appbar.folder.open.png");
			this->imageList1->Images->SetKeyName(11, L"appbar.page.new.png");
			this->imageList1->Images->SetKeyName(12, L"appbar.save.png");
			this->imageList1->Images->SetKeyName(13, L"appbar.sound.3.png");
			this->imageList1->Images->SetKeyName(14, L"appbar.sound.mute.png");
			// 
			// button2
			// 
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button2->ImageIndex = 11;
			this->button2->ImageList = this->imageList1;
			this->button2->Location = System::Drawing::Point(12, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(40, 40);
			this->button2->TabIndex = 3;
			this->button2->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button3->ImageIndex = 12;
			this->button3->ImageList = this->imageList1;
			this->button3->Location = System::Drawing::Point(104, 12);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(40, 40);
			this->button3->TabIndex = 4;
			this->button3->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button4->ImageIndex = 12;
			this->button4->ImageList = this->imageList1;
			this->button4->Location = System::Drawing::Point(232, 12);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(40, 40);
			this->button4->TabIndex = 5;
			this->button4->UseVisualStyleBackColor = true;
			// 
			// button5
			// 
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button5->ImageIndex = 9;
			this->button5->ImageList = this->imageList1;
			this->button5->Location = System::Drawing::Point(186, 12);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(40, 40);
			this->button5->TabIndex = 6;
			this->button5->UseVisualStyleBackColor = true;
			// 
			// rackItem1
			// 
			this->rackItem1->Location = System::Drawing::Point(12, 111);
			this->rackItem1->Margin = System::Windows::Forms::Padding(0);
			this->rackItem1->Name = L"rackItem1";
			this->rackItem1->Size = System::Drawing::Size(260, 94);
			this->rackItem1->TabIndex = 7;
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->rackItem1);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->Btn_StartGrabbing);
			this->Controls->Add(this->comboBox1);
			this->Name = L"MainWindow";
			this->Text = L"MainWindow";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Btn_StartGrabbing_Click(System::Object^  sender, System::EventArgs^  e)
	{
		AudioGrabber::GetAudioGrabber();
	}

	};
}
