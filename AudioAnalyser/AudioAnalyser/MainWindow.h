#include "AudioGrabber.h"
#pragma once

namespace AudioAnalyser {

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



	private: System::Windows::Forms::ImageList^  imageList1;
	private: System::Windows::Forms::Button^  button2;



	private: RackControls::RackItem^  rackItem1;
	private: System::Windows::Forms::ImageList^  imageList2;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::ComboBox^  comboBox5;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::ComboBox^  comboBox4;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Label^  label8;
	private: RackControls::RackItem^  rackItem2;
	private: RackControls::RackItem^  rackItem3;
	private: RackControls::RackItem^  rackItem4;
	private: RackControls::RackItem^  rackItem5;
	private: RackControls::RackItem^  rackItem6;
	private: RackControls::RackItem^  rackItem7;
	private: RackControls::RackItem^  rackItem8;



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
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->imageList2 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox5 = (gcnew System::Windows::Forms::ComboBox());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->rackItem8 = (gcnew RackControls::RackItem());
			this->rackItem7 = (gcnew RackControls::RackItem());
			this->rackItem6 = (gcnew RackControls::RackItem());
			this->rackItem5 = (gcnew RackControls::RackItem());
			this->rackItem4 = (gcnew RackControls::RackItem());
			this->rackItem3 = (gcnew RackControls::RackItem());
			this->rackItem2 = (gcnew RackControls::RackItem());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->SuspendLayout();
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
			this->button2->ImageIndex = 0;
			this->button2->ImageList = this->imageList2;
			this->button2->Location = System::Drawing::Point(12, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(40, 40);
			this->button2->TabIndex = 3;
			this->button2->UseVisualStyleBackColor = true;
			// 
			// imageList2
			// 
			this->imageList2->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList2.ImageStream")));
			this->imageList2->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList2->Images->SetKeyName(0, L"Icons-01.png");
			this->imageList2->Images->SetKeyName(1, L"Icons-03.png");
			this->imageList2->Images->SetKeyName(2, L"Icons-05.png");
			this->imageList2->Images->SetKeyName(3, L"Icons-04.png");
			this->imageList2->Images->SetKeyName(4, L"Icons-07.png");
			this->imageList2->Images->SetKeyName(5, L"Icons-08.png");
			this->imageList2->Images->SetKeyName(6, L"Icons-15.png");
			this->imageList2->Images->SetKeyName(7, L"Icons-16.png");
			this->imageList2->Images->SetKeyName(8, L"Icons-17.png");
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->comboBox2);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->button4);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(12, 58);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(317, 86);
			this->groupBox1->TabIndex = 8;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Input (stream)";
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(92, 48);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(165, 21);
			this->comboBox2->TabIndex = 3;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(92, 23);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(165, 21);
			this->comboBox1->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 51);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(63, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Sample rate";
			// 
			// button4
			// 
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button4->ImageIndex = 3;
			this->button4->ImageList = this->imageList2;
			this->button4->Location = System::Drawing::Point(263, 23);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(48, 46);
			this->button4->TabIndex = 11;
			this->button4->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(75, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Stream source";
			// 
			// button1
			// 
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button1->ImageIndex = 1;
			this->button1->ImageList = this->imageList2;
			this->button1->Location = System::Drawing::Point(58, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(40, 40);
			this->button1->TabIndex = 9;
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button3->ImageIndex = 2;
			this->button3->ImageList = this->imageList2;
			this->button3->Location = System::Drawing::Point(104, 12);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(40, 40);
			this->button3->TabIndex = 10;
			this->button3->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->trackBar1);
			this->groupBox2->Controls->Add(this->button9);
			this->groupBox2->Controls->Add(this->textBox1);
			this->groupBox2->Controls->Add(this->button8);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Location = System::Drawing::Point(12, 150);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(317, 100);
			this->groupBox2->TabIndex = 12;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Input (file)";
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(263, 72);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(48, 22);
			this->label3->TabIndex = 12;
			this->label3->Text = L"00:00";
			this->label3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(9, 49);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(248, 45);
			this->trackBar1->TabIndex = 15;
			// 
			// button9
			// 
			this->button9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button9->ImageIndex = 6;
			this->button9->Location = System::Drawing::Point(227, 23);
			this->button9->Margin = System::Windows::Forms::Padding(0);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(30, 20);
			this->button9->TabIndex = 16;
			this->button9->Text = L"...";
			this->button9->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->button9->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(92, 23);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(132, 20);
			this->textBox1->TabIndex = 16;
			// 
			// button8
			// 
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button8->ImageIndex = 4;
			this->button8->ImageList = this->imageList2;
			this->button8->Location = System::Drawing::Point(263, 23);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(48, 46);
			this->button8->TabIndex = 11;
			this->button8->UseVisualStyleBackColor = true;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 26);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(75, 13);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Stream source";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->comboBox5);
			this->groupBox3->Controls->Add(this->button10);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Controls->Add(this->textBox2);
			this->groupBox3->Controls->Add(this->button11);
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Location = System::Drawing::Point(12, 348);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(317, 85);
			this->groupBox3->TabIndex = 14;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Output (file)";
			// 
			// comboBox5
			// 
			this->comboBox5->FormattingEnabled = true;
			this->comboBox5->Location = System::Drawing::Point(92, 48);
			this->comboBox5->Name = L"comboBox5";
			this->comboBox5->Size = System::Drawing::Size(165, 21);
			this->comboBox5->TabIndex = 13;
			// 
			// button10
			// 
			this->button10->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button10->ImageIndex = 6;
			this->button10->Location = System::Drawing::Point(227, 23);
			this->button10->Margin = System::Windows::Forms::Padding(0);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(30, 20);
			this->button10->TabIndex = 16;
			this->button10->Text = L"...";
			this->button10->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->button10->UseVisualStyleBackColor = true;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 51);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(63, 13);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Sample rate";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(92, 23);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(132, 20);
			this->textBox2->TabIndex = 16;
			// 
			// button11
			// 
			this->button11->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button11->ImageIndex = 6;
			this->button11->ImageList = this->imageList2;
			this->button11->Location = System::Drawing::Point(263, 23);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(48, 46);
			this->button11->TabIndex = 11;
			this->button11->UseVisualStyleBackColor = true;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 26);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(75, 13);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Stream source";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->comboBox3);
			this->groupBox4->Controls->Add(this->comboBox4);
			this->groupBox4->Controls->Add(this->label7);
			this->groupBox4->Controls->Add(this->button12);
			this->groupBox4->Controls->Add(this->label8);
			this->groupBox4->Location = System::Drawing::Point(12, 256);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(317, 86);
			this->groupBox4->TabIndex = 13;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Output (stream)";
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Location = System::Drawing::Point(92, 48);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(165, 21);
			this->comboBox3->TabIndex = 3;
			// 
			// comboBox4
			// 
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Location = System::Drawing::Point(92, 23);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(165, 21);
			this->comboBox4->TabIndex = 2;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 51);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(63, 13);
			this->label7->TabIndex = 1;
			this->label7->Text = L"Sample rate";
			// 
			// button12
			// 
			this->button12->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button12->ImageIndex = 8;
			this->button12->ImageList = this->imageList2;
			this->button12->Location = System::Drawing::Point(263, 23);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(48, 46);
			this->button12->TabIndex = 11;
			this->button12->UseVisualStyleBackColor = true;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(6, 26);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(73, 13);
			this->label8->TabIndex = 0;
			this->label8->Text = L"Target source";
			// 
			// rackItem8
			// 
			this->rackItem8->Location = System::Drawing::Point(352, 372);
			this->rackItem8->Name = L"rackItem8";
			this->rackItem8->RackItemId = 0;
			this->rackItem8->Size = System::Drawing::Size(407, 61);
			this->rackItem8->TabIndex = 21;
			// 
			// rackItem7
			// 
			this->rackItem7->Location = System::Drawing::Point(352, 311);
			this->rackItem7->Name = L"rackItem7";
			this->rackItem7->RackItemId = 0;
			this->rackItem7->Size = System::Drawing::Size(407, 61);
			this->rackItem7->TabIndex = 20;
			// 
			// rackItem6
			// 
			this->rackItem6->Location = System::Drawing::Point(352, 250);
			this->rackItem6->Name = L"rackItem6";
			this->rackItem6->RackItemId = 0;
			this->rackItem6->Size = System::Drawing::Size(407, 61);
			this->rackItem6->TabIndex = 19;
			// 
			// rackItem5
			// 
			this->rackItem5->Location = System::Drawing::Point(352, 189);
			this->rackItem5->Name = L"rackItem5";
			this->rackItem5->RackItemId = 0;
			this->rackItem5->Size = System::Drawing::Size(407, 61);
			this->rackItem5->TabIndex = 18;
			// 
			// rackItem4
			// 
			this->rackItem4->Location = System::Drawing::Point(352, 128);
			this->rackItem4->Name = L"rackItem4";
			this->rackItem4->RackItemId = 0;
			this->rackItem4->Size = System::Drawing::Size(407, 61);
			this->rackItem4->TabIndex = 17;
			// 
			// rackItem3
			// 
			this->rackItem3->Location = System::Drawing::Point(352, 67);
			this->rackItem3->Name = L"rackItem3";
			this->rackItem3->RackItemId = 0;
			this->rackItem3->Size = System::Drawing::Size(407, 61);
			this->rackItem3->TabIndex = 16;
			// 
			// rackItem2
			// 
			this->rackItem2->Location = System::Drawing::Point(352, 6);
			this->rackItem2->Name = L"rackItem2";
			this->rackItem2->RackItemId = 0;
			this->rackItem2->Size = System::Drawing::Size(407, 61);
			this->rackItem2->TabIndex = 15;
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(762, 444);
			this->Controls->Add(this->rackItem8);
			this->Controls->Add(this->rackItem7);
			this->Controls->Add(this->rackItem6);
			this->Controls->Add(this->rackItem5);
			this->Controls->Add(this->rackItem4);
			this->Controls->Add(this->rackItem3);
			this->Controls->Add(this->rackItem2);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button2);
			this->Name = L"MainWindow";
			this->Text = L"32;32";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Btn_StartGrabbing_Click(System::Object^  sender, System::EventArgs^  e)
	{
		AudioGrabber::GetAudioGrabber();
	}

	};
}
