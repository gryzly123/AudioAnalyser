#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
//using namespace System


namespace RackControls {

	delegate void OnVolumeMixChanged(int, float);
	delegate void OnNewPluginRequested(int, String^);
	delegate void OnConfigWindowRequested(int);
	delegate void OnVisWindowRequested(int);
	delegate void OnBypassRequested(int);
	delegate void OnSoloRequested(int);

	/// <summary>
	/// Kontrolka WinForms do obs³ugi slotów DSP.
	/// </summary>
	public ref class RackItem : public System::Windows::Forms::UserControl
	{
	public:

		property int RackItemId;
		property int MixVolume;

		RackItem(void)
		{
			InitializeComponent();
		}

	protected:
		~RackItem()
		{
			if (components) delete components;
		}
	private: System::Windows::Forms::GroupBox^  GroupboxPlugin;
	protected:


	private: System::Windows::Forms::TrackBar^  TrackbarMixdown;

	private: System::Windows::Forms::Label^  CurrentPluginName;
	private: System::Windows::Forms::Button^  ButtonSolo;

	private: System::Windows::Forms::Button^  ButtonBypass;


	private: System::Windows::Forms::Button^  ButtonVis;

	private: System::Windows::Forms::Button^  ButtonConfig;

	private: System::Windows::Forms::Button^  ButtonFlipDown;
	private: System::Windows::Forms::Button^  ButtonSwap;


	private: System::Windows::Forms::Button^  ButtonFlipUp;

	private: System::Windows::Forms::ImageList^  imageList2;
	private: System::Windows::Forms::ImageList^  imageList1;
	private: System::Windows::Forms::ContextMenuStrip^  PluginList;
	private: System::Windows::Forms::ToolStripTextBox^  TextboxGen;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem3;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem4;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem9;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox2;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem5;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem6;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem7;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem8;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem10;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem11;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem12;
	private: System::ComponentModel::IContainer^  components;

	public: event OnVolumeMixChanged	  ^ VolumeMixChanged;
	public: event OnNewPluginRequested	  ^ NewPluginRequested;
	public: event OnConfigWindowRequested ^ ConfigWindowRequested;
	public: event OnVisWindowRequested	  ^ VisWindowRequested;
	public: event OnBypassRequested		  ^ BypassRequested;
	public: event OnSoloRequested		  ^ SoloRequested;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(RackItem::typeid));
			this->GroupboxPlugin = (gcnew System::Windows::Forms::GroupBox());
			this->CurrentPluginName = (gcnew System::Windows::Forms::Label());
			this->ButtonSolo = (gcnew System::Windows::Forms::Button());
			this->imageList2 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->ButtonBypass = (gcnew System::Windows::Forms::Button());
			this->ButtonVis = (gcnew System::Windows::Forms::Button());
			this->ButtonConfig = (gcnew System::Windows::Forms::Button());
			this->ButtonFlipDown = (gcnew System::Windows::Forms::Button());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->ButtonSwap = (gcnew System::Windows::Forms::Button());
			this->ButtonFlipUp = (gcnew System::Windows::Forms::Button());
			this->TrackbarMixdown = (gcnew System::Windows::Forms::TrackBar());
			this->PluginList = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->TextboxGen = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripTextBox1 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem9 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripTextBox2 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripMenuItem6 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem7 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem8 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem10 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem11 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem12 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->GroupboxPlugin->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackbarMixdown))->BeginInit();
			this->PluginList->SuspendLayout();
			this->SuspendLayout();
			// 
			// GroupboxPlugin
			// 
			this->GroupboxPlugin->Controls->Add(this->CurrentPluginName);
			this->GroupboxPlugin->Controls->Add(this->ButtonSolo);
			this->GroupboxPlugin->Controls->Add(this->ButtonBypass);
			this->GroupboxPlugin->Controls->Add(this->ButtonVis);
			this->GroupboxPlugin->Controls->Add(this->ButtonConfig);
			this->GroupboxPlugin->Controls->Add(this->ButtonFlipDown);
			this->GroupboxPlugin->Controls->Add(this->ButtonSwap);
			this->GroupboxPlugin->Controls->Add(this->ButtonFlipUp);
			this->GroupboxPlugin->Controls->Add(this->TrackbarMixdown);
			this->GroupboxPlugin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->GroupboxPlugin->Location = System::Drawing::Point(0, 0);
			this->GroupboxPlugin->Margin = System::Windows::Forms::Padding(0);
			this->GroupboxPlugin->Name = L"GroupboxPlugin";
			this->GroupboxPlugin->Size = System::Drawing::Size(404, 61);
			this->GroupboxPlugin->TabIndex = 0;
			this->GroupboxPlugin->TabStop = false;
			// 
			// CurrentPluginName
			// 
			this->CurrentPluginName->Font = (gcnew System::Drawing::Font(L"Segoe UI Light", 16));
			this->CurrentPluginName->Location = System::Drawing::Point(201, 12);
			this->CurrentPluginName->Name = L"CurrentPluginName";
			this->CurrentPluginName->Size = System::Drawing::Size(198, 38);
			this->CurrentPluginName->TabIndex = 13;
			this->CurrentPluginName->Text = L"(none)";
			this->CurrentPluginName->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// ButtonSolo
			// 
			this->ButtonSolo->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonSolo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonSolo->ImageIndex = 3;
			this->ButtonSolo->ImageList = this->imageList2;
			this->ButtonSolo->Location = System::Drawing::Point(116, 33);
			this->ButtonSolo->Margin = System::Windows::Forms::Padding(2);
			this->ButtonSolo->Name = L"ButtonSolo";
			this->ButtonSolo->Size = System::Drawing::Size(50, 18);
			this->ButtonSolo->TabIndex = 12;
			this->ButtonSolo->UseVisualStyleBackColor = true;
			// 
			// imageList2
			// 
			this->imageList2->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList2.ImageStream")));
			this->imageList2->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList2->Images->SetKeyName(0, L"Config.png");
			this->imageList2->Images->SetKeyName(1, L"Vis.png");
			this->imageList2->Images->SetKeyName(2, L"Mute.png");
			this->imageList2->Images->SetKeyName(3, L"Solo.png");
			// 
			// ButtonBypass
			// 
			this->ButtonBypass->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonBypass->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonBypass->ImageIndex = 2;
			this->ButtonBypass->ImageList = this->imageList2;
			this->ButtonBypass->Location = System::Drawing::Point(64, 33);
			this->ButtonBypass->Margin = System::Windows::Forms::Padding(2);
			this->ButtonBypass->Name = L"ButtonBypass";
			this->ButtonBypass->Size = System::Drawing::Size(50, 18);
			this->ButtonBypass->TabIndex = 11;
			this->ButtonBypass->UseVisualStyleBackColor = true;
			// 
			// ButtonVis
			// 
			this->ButtonVis->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonVis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonVis->ImageIndex = 1;
			this->ButtonVis->ImageList = this->imageList2;
			this->ButtonVis->Location = System::Drawing::Point(116, 13);
			this->ButtonVis->Margin = System::Windows::Forms::Padding(2);
			this->ButtonVis->Name = L"ButtonVis";
			this->ButtonVis->Size = System::Drawing::Size(50, 18);
			this->ButtonVis->TabIndex = 10;
			this->ButtonVis->UseVisualStyleBackColor = true;
			// 
			// ButtonConfig
			// 
			this->ButtonConfig->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonConfig->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonConfig->ImageKey = L"Config.png";
			this->ButtonConfig->ImageList = this->imageList2;
			this->ButtonConfig->Location = System::Drawing::Point(64, 13);
			this->ButtonConfig->Margin = System::Windows::Forms::Padding(2);
			this->ButtonConfig->Name = L"ButtonConfig";
			this->ButtonConfig->Size = System::Drawing::Size(50, 18);
			this->ButtonConfig->TabIndex = 9;
			this->ButtonConfig->UseVisualStyleBackColor = true;
			// 
			// ButtonFlipDown
			// 
			this->ButtonFlipDown->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonFlipDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonFlipDown->ImageIndex = 1;
			this->ButtonFlipDown->ImageList = this->imageList1;
			this->ButtonFlipDown->Location = System::Drawing::Point(6, 33);
			this->ButtonFlipDown->Margin = System::Windows::Forms::Padding(2);
			this->ButtonFlipDown->Name = L"ButtonFlipDown";
			this->ButtonFlipDown->Size = System::Drawing::Size(28, 18);
			this->ButtonFlipDown->TabIndex = 8;
			this->ButtonFlipDown->UseVisualStyleBackColor = true;
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList1->Images->SetKeyName(0, L"Up.png");
			this->imageList1->Images->SetKeyName(1, L"Down.png");
			this->imageList1->Images->SetKeyName(2, L"Item.png");
			// 
			// ButtonSwap
			// 
			this->ButtonSwap->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonSwap->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonSwap->ImageIndex = 2;
			this->ButtonSwap->ImageList = this->imageList1;
			this->ButtonSwap->Location = System::Drawing::Point(36, 13);
			this->ButtonSwap->Margin = System::Windows::Forms::Padding(2);
			this->ButtonSwap->Name = L"ButtonSwap";
			this->ButtonSwap->Size = System::Drawing::Size(26, 38);
			this->ButtonSwap->TabIndex = 7;
			this->ButtonSwap->UseVisualStyleBackColor = true;
			this->ButtonSwap->Click += gcnew System::EventHandler(this, &RackItem::ButtonSwap_Click);
			// 
			// ButtonFlipUp
			// 
			this->ButtonFlipUp->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonFlipUp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonFlipUp->ImageIndex = 0;
			this->ButtonFlipUp->ImageList = this->imageList1;
			this->ButtonFlipUp->Location = System::Drawing::Point(6, 13);
			this->ButtonFlipUp->Margin = System::Windows::Forms::Padding(2);
			this->ButtonFlipUp->Name = L"ButtonFlipUp";
			this->ButtonFlipUp->Size = System::Drawing::Size(28, 18);
			this->ButtonFlipUp->TabIndex = 6;
			this->ButtonFlipUp->UseVisualStyleBackColor = true;
			// 
			// TrackbarMixdown
			// 
			this->TrackbarMixdown->LargeChange = 4;
			this->TrackbarMixdown->Location = System::Drawing::Point(168, 8);
			this->TrackbarMixdown->Margin = System::Windows::Forms::Padding(0);
			this->TrackbarMixdown->Maximum = 127;
			this->TrackbarMixdown->Name = L"TrackbarMixdown";
			this->TrackbarMixdown->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->TrackbarMixdown->Size = System::Drawing::Size(45, 50);
			this->TrackbarMixdown->TabIndex = 4;
			this->TrackbarMixdown->TickFrequency = 16;
			this->TrackbarMixdown->Value = 127;
			// 
			// PluginList
			// 
			this->PluginList->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PluginList->ImageScalingSize = System::Drawing::Size(0, 16);
			this->PluginList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(17) {
				this->TextboxGen, this->toolStripMenuItem1,
					this->toolStripMenuItem2, this->toolStripSeparator1, this->toolStripTextBox1, this->toolStripMenuItem3, this->toolStripMenuItem4,
					this->toolStripMenuItem9, this->toolStripSeparator2, this->toolStripTextBox2, this->toolStripMenuItem6, this->toolStripMenuItem5,
					this->toolStripMenuItem7, this->toolStripMenuItem8, this->toolStripMenuItem10, this->toolStripMenuItem11, this->toolStripMenuItem12
			});
			this->PluginList->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->PluginList->Name = L"PluginList";
			this->PluginList->Size = System::Drawing::Size(167, 347);
			// 
			// TextboxGen
			// 
			this->TextboxGen->BackColor = System::Drawing::Color::White;
			this->TextboxGen->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TextboxGen->Enabled = false;
			this->TextboxGen->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->TextboxGen->Name = L"TextboxGen";
			this->TextboxGen->Size = System::Drawing::Size(100, 13);
			this->TextboxGen->Text = L"Noise generators";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(166, 22);
			this->toolStripMenuItem1->Text = L"Oscillator";
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(166, 22);
			this->toolStripMenuItem2->Text = L"Noise";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(163, 6);
			// 
			// toolStripTextBox1
			// 
			this->toolStripTextBox1->BackColor = System::Drawing::Color::White;
			this->toolStripTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->toolStripTextBox1->Enabled = false;
			this->toolStripTextBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->toolStripTextBox1->Name = L"toolStripTextBox1";
			this->toolStripTextBox1->Size = System::Drawing::Size(100, 13);
			this->toolStripTextBox1->Text = L"Analysers";
			// 
			// toolStripMenuItem3
			// 
			this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
			this->toolStripMenuItem3->Size = System::Drawing::Size(166, 22);
			this->toolStripMenuItem3->Text = L"Oscilloscope";
			// 
			// toolStripMenuItem4
			// 
			this->toolStripMenuItem4->Name = L"toolStripMenuItem4";
			this->toolStripMenuItem4->Size = System::Drawing::Size(166, 22);
			this->toolStripMenuItem4->Text = L"Spectrum";
			// 
			// toolStripMenuItem9
			// 
			this->toolStripMenuItem9->Name = L"toolStripMenuItem9";
			this->toolStripMenuItem9->Size = System::Drawing::Size(166, 22);
			this->toolStripMenuItem9->Text = L"Spectrogram";
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(163, 6);
			// 
			// toolStripTextBox2
			// 
			this->toolStripTextBox2->BackColor = System::Drawing::Color::White;
			this->toolStripTextBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->toolStripTextBox2->Enabled = false;
			this->toolStripTextBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->toolStripTextBox2->Name = L"toolStripTextBox2";
			this->toolStripTextBox2->Size = System::Drawing::Size(100, 13);
			this->toolStripTextBox2->Text = L"Effects";
			// 
			// toolStripMenuItem6
			// 
			this->toolStripMenuItem6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->toolStripMenuItem6->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripMenuItem6->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripMenuItem6->Name = L"toolStripMenuItem6";
			this->toolStripMenuItem6->Size = System::Drawing::Size(166, 22);
			this->toolStripMenuItem6->Text = L"Stereo Separation";
			this->toolStripMenuItem6->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			// 
			// toolStripMenuItem5
			// 
			this->toolStripMenuItem5->Name = L"toolStripMenuItem5";
			this->toolStripMenuItem5->Size = System::Drawing::Size(166, 22);
			this->toolStripMenuItem5->Text = L"Gain";
			// 
			// toolStripMenuItem7
			// 
			this->toolStripMenuItem7->Name = L"toolStripMenuItem7";
			this->toolStripMenuItem7->Size = System::Drawing::Size(166, 22);
			this->toolStripMenuItem7->Text = L"Decimation";
			// 
			// toolStripMenuItem8
			// 
			this->toolStripMenuItem8->Name = L"toolStripMenuItem8";
			this->toolStripMenuItem8->Size = System::Drawing::Size(166, 22);
			this->toolStripMenuItem8->Text = L"Delay";
			// 
			// toolStripMenuItem10
			// 
			this->toolStripMenuItem10->Name = L"toolStripMenuItem10";
			this->toolStripMenuItem10->Size = System::Drawing::Size(166, 22);
			this->toolStripMenuItem10->Text = L"Bitcrush";
			// 
			// toolStripMenuItem11
			// 
			this->toolStripMenuItem11->Name = L"toolStripMenuItem11";
			this->toolStripMenuItem11->Size = System::Drawing::Size(166, 22);
			this->toolStripMenuItem11->Text = L"Low Pass Filter";
			// 
			// toolStripMenuItem12
			// 
			this->toolStripMenuItem12->Name = L"toolStripMenuItem12";
			this->toolStripMenuItem12->Size = System::Drawing::Size(166, 22);
			this->toolStripMenuItem12->Text = L"High Pass Filter";
			// 
			// RackItem
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->GroupboxPlugin);
			this->Name = L"RackItem";
			this->Size = System::Drawing::Size(406, 61);
			this->GroupboxPlugin->ResumeLayout(false);
			this->GroupboxPlugin->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackbarMixdown))->EndInit();
			this->PluginList->ResumeLayout(false);
			this->PluginList->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void ButtonSwap_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Button^ ButtonRef = (cli::safe_cast<System::Windows::Forms::Button^>(sender));
		System::Drawing::Point ButtonLocation = ButtonRef->Location;
		
		PluginList->Show();
		PluginList->Location = MousePosition;
	}
};
}
