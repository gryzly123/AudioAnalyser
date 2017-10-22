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
	private: System::Windows::Forms::ImageList^  Images41by16;
	private: System::Windows::Forms::ImageList^  Images16by16;



	private: System::Windows::Forms::ContextMenuStrip^  PluginList;
	private: System::Windows::Forms::ToolStripTextBox^  TextboxGenerators;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugSineOscillator;


	private: System::Windows::Forms::ToolStripMenuItem^  PlugNoise;
	private: System::Windows::Forms::ToolStripSeparator^  Separator1;
	private: System::Windows::Forms::ToolStripTextBox^  TextboxAnalysers;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugOscilloscope;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugSpectrum;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugSpectrogram;
	private: System::Windows::Forms::ToolStripSeparator^  Separator2;
	private: System::Windows::Forms::ToolStripTextBox^  TextboxEffects;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugGain;












	private: System::Windows::Forms::ToolStripMenuItem^  PlugStereoSeparation;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugDecimation;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugDelay;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugBitcrush;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugLPF;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugHPF;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugNullPlugin;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugSawOscillator;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugSquareOscillator;






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
			this->Images41by16 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->ButtonBypass = (gcnew System::Windows::Forms::Button());
			this->ButtonVis = (gcnew System::Windows::Forms::Button());
			this->ButtonConfig = (gcnew System::Windows::Forms::Button());
			this->ButtonFlipDown = (gcnew System::Windows::Forms::Button());
			this->Images16by16 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->ButtonSwap = (gcnew System::Windows::Forms::Button());
			this->ButtonFlipUp = (gcnew System::Windows::Forms::Button());
			this->TrackbarMixdown = (gcnew System::Windows::Forms::TrackBar());
			this->PluginList = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->PlugNullPlugin = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TextboxGenerators = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->PlugSineOscillator = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugNoise = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Separator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->TextboxAnalysers = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->PlugOscilloscope = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugSpectrum = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugSpectrogram = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Separator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->TextboxEffects = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->PlugGain = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugBitcrush = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugDecimation = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugStereoSeparation = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugDelay = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugLPF = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugHPF = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugSawOscillator = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugSquareOscillator = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->ButtonSolo->ImageList = this->Images41by16;
			this->ButtonSolo->Location = System::Drawing::Point(116, 33);
			this->ButtonSolo->Margin = System::Windows::Forms::Padding(2);
			this->ButtonSolo->Name = L"ButtonSolo";
			this->ButtonSolo->Size = System::Drawing::Size(50, 18);
			this->ButtonSolo->TabIndex = 12;
			this->ButtonSolo->UseVisualStyleBackColor = true;
			// 
			// Images41by16
			// 
			this->Images41by16->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"Images41by16.ImageStream")));
			this->Images41by16->TransparentColor = System::Drawing::Color::Transparent;
			this->Images41by16->Images->SetKeyName(0, L"Config.png");
			this->Images41by16->Images->SetKeyName(1, L"Vis.png");
			this->Images41by16->Images->SetKeyName(2, L"Mute.png");
			this->Images41by16->Images->SetKeyName(3, L"Solo.png");
			// 
			// ButtonBypass
			// 
			this->ButtonBypass->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonBypass->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonBypass->ImageIndex = 2;
			this->ButtonBypass->ImageList = this->Images41by16;
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
			this->ButtonVis->ImageList = this->Images41by16;
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
			this->ButtonConfig->ImageList = this->Images41by16;
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
			this->ButtonFlipDown->ImageList = this->Images16by16;
			this->ButtonFlipDown->Location = System::Drawing::Point(6, 33);
			this->ButtonFlipDown->Margin = System::Windows::Forms::Padding(2);
			this->ButtonFlipDown->Name = L"ButtonFlipDown";
			this->ButtonFlipDown->Size = System::Drawing::Size(28, 18);
			this->ButtonFlipDown->TabIndex = 8;
			this->ButtonFlipDown->UseVisualStyleBackColor = true;
			// 
			// Images16by16
			// 
			this->Images16by16->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"Images16by16.ImageStream")));
			this->Images16by16->TransparentColor = System::Drawing::Color::Transparent;
			this->Images16by16->Images->SetKeyName(0, L"Up.png");
			this->Images16by16->Images->SetKeyName(1, L"Down.png");
			this->Images16by16->Images->SetKeyName(2, L"Item.png");
			// 
			// ButtonSwap
			// 
			this->ButtonSwap->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonSwap->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->ButtonSwap->ImageIndex = 2;
			this->ButtonSwap->ImageList = this->Images16by16;
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
			this->ButtonFlipUp->ImageList = this->Images16by16;
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
			this->PluginList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(20) {
				this->PlugNullPlugin, this->TextboxGenerators,
					this->PlugSineOscillator, this->PlugSawOscillator, this->PlugSquareOscillator, this->PlugNoise, this->Separator1, this->TextboxAnalysers,
					this->PlugOscilloscope, this->PlugSpectrum, this->PlugSpectrogram, this->Separator2, this->TextboxEffects, this->PlugGain, this->PlugBitcrush,
					this->PlugDecimation, this->PlugStereoSeparation, this->PlugDelay, this->PlugLPF, this->PlugHPF
			});
			this->PluginList->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->PluginList->Name = L"PluginList";
			this->PluginList->Size = System::Drawing::Size(167, 413);
			// 
			// PlugNullPlugin
			// 
			this->PlugNullPlugin->Name = L"PlugNullPlugin";
			this->PlugNullPlugin->Size = System::Drawing::Size(166, 22);
			this->PlugNullPlugin->Text = L"None";
			// 
			// TextboxGenerators
			// 
			this->TextboxGenerators->BackColor = System::Drawing::Color::White;
			this->TextboxGenerators->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TextboxGenerators->Enabled = false;
			this->TextboxGenerators->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->TextboxGenerators->Name = L"TextboxGenerators";
			this->TextboxGenerators->Size = System::Drawing::Size(100, 13);
			this->TextboxGenerators->Text = L"Generators";
			// 
			// PlugSineOscillator
			// 
			this->PlugSineOscillator->Name = L"PlugSineOscillator";
			this->PlugSineOscillator->Size = System::Drawing::Size(166, 22);
			this->PlugSineOscillator->Text = L"Sine wave";
			// 
			// PlugNoise
			// 
			this->PlugNoise->Name = L"PlugNoise";
			this->PlugNoise->Size = System::Drawing::Size(166, 22);
			this->PlugNoise->Text = L"White noise";
			// 
			// Separator1
			// 
			this->Separator1->Name = L"Separator1";
			this->Separator1->Size = System::Drawing::Size(163, 6);
			// 
			// TextboxAnalysers
			// 
			this->TextboxAnalysers->BackColor = System::Drawing::Color::White;
			this->TextboxAnalysers->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TextboxAnalysers->Enabled = false;
			this->TextboxAnalysers->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->TextboxAnalysers->Name = L"TextboxAnalysers";
			this->TextboxAnalysers->Size = System::Drawing::Size(100, 13);
			this->TextboxAnalysers->Text = L"Analysers";
			// 
			// PlugOscilloscope
			// 
			this->PlugOscilloscope->Name = L"PlugOscilloscope";
			this->PlugOscilloscope->Size = System::Drawing::Size(166, 22);
			this->PlugOscilloscope->Text = L"Oscilloscope";
			// 
			// PlugSpectrum
			// 
			this->PlugSpectrum->Name = L"PlugSpectrum";
			this->PlugSpectrum->Size = System::Drawing::Size(166, 22);
			this->PlugSpectrum->Text = L"Spectrum";
			// 
			// PlugSpectrogram
			// 
			this->PlugSpectrogram->Name = L"PlugSpectrogram";
			this->PlugSpectrogram->Size = System::Drawing::Size(166, 22);
			this->PlugSpectrogram->Text = L"Spectrogram";
			// 
			// Separator2
			// 
			this->Separator2->Name = L"Separator2";
			this->Separator2->Size = System::Drawing::Size(163, 6);
			// 
			// TextboxEffects
			// 
			this->TextboxEffects->BackColor = System::Drawing::Color::White;
			this->TextboxEffects->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TextboxEffects->Enabled = false;
			this->TextboxEffects->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->TextboxEffects->Name = L"TextboxEffects";
			this->TextboxEffects->Size = System::Drawing::Size(100, 13);
			this->TextboxEffects->Text = L"Effects";
			// 
			// PlugGain
			// 
			this->PlugGain->Name = L"PlugGain";
			this->PlugGain->Size = System::Drawing::Size(166, 22);
			this->PlugGain->Text = L"Gain";
			// 
			// PlugBitcrush
			// 
			this->PlugBitcrush->Name = L"PlugBitcrush";
			this->PlugBitcrush->Size = System::Drawing::Size(166, 22);
			this->PlugBitcrush->Text = L"Bitcrush";
			// 
			// PlugDecimation
			// 
			this->PlugDecimation->Name = L"PlugDecimation";
			this->PlugDecimation->Size = System::Drawing::Size(166, 22);
			this->PlugDecimation->Text = L"Decimation";
			// 
			// PlugStereoSeparation
			// 
			this->PlugStereoSeparation->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PlugStereoSeparation->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->PlugStereoSeparation->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->PlugStereoSeparation->Name = L"PlugStereoSeparation";
			this->PlugStereoSeparation->Size = System::Drawing::Size(166, 22);
			this->PlugStereoSeparation->Text = L"Stereo Separation";
			this->PlugStereoSeparation->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			// 
			// PlugDelay
			// 
			this->PlugDelay->Name = L"PlugDelay";
			this->PlugDelay->Size = System::Drawing::Size(166, 22);
			this->PlugDelay->Text = L"Delay";
			// 
			// PlugLPF
			// 
			this->PlugLPF->Name = L"PlugLPF";
			this->PlugLPF->Size = System::Drawing::Size(166, 22);
			this->PlugLPF->Text = L"Low Pass Filter";
			// 
			// PlugHPF
			// 
			this->PlugHPF->Name = L"PlugHPF";
			this->PlugHPF->Size = System::Drawing::Size(166, 22);
			this->PlugHPF->Text = L"High Pass Filter";
			// 
			// PlugSawOscillator
			// 
			this->PlugSawOscillator->Name = L"PlugSawOscillator";
			this->PlugSawOscillator->Size = System::Drawing::Size(166, 22);
			this->PlugSawOscillator->Text = L"Saw wave";
			// 
			// PlugSquareOscillator
			// 
			this->PlugSquareOscillator->Name = L"PlugSquareOscillator";
			this->PlugSquareOscillator->Size = System::Drawing::Size(166, 22);
			this->PlugSquareOscillator->Text = L"Square wave";
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
