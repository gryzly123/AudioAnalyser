#pragma once
#include "RackItemContents.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace RackControls
{
	public delegate System::Void OnVolumeMixChanged(Int32, Single);
	public delegate System::Void OnNewPluginRequested(Int32, String^);
	public delegate System::Void OnConfigWindowRequested(Int32);
	public delegate System::Void OnVisWindowRequested(Int32);
	public delegate System::Void OnBypassRequested(Int32);
	public delegate System::Void OnSoloRequested(Int32);
	public delegate System::Void OnSwapRequested(Int32, Boolean IsDownwards);

	/// <summary>
	/// Kontrolka WinForms do obs³ugi slotów DSP.
	/// </summary>
	public ref class RackItem : public System::Windows::Forms::UserControl
	{
	public:

		property System::Int32 RackItemId;
		property System::Int32 MixVolume;
		property System::Boolean LastRackItem;

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
	private: System::Windows::Forms::ToolStripTextBox^  TextboxEffects1;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugGain;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugStereoMerger;

	private: System::Windows::Forms::ToolStripMenuItem^  PlugDecimation;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugDelay;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugBitcrush;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugLpfAvg;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugHpf;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugNullPlugin;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugSawOscillator;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugSquareOscillator;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugRetriggerSimple;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugLpfSinc;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugBpf;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugStereoToMs;
	private: System::Windows::Forms::ToolStripTextBox^  TextboxEffects2;
	private: System::Windows::Forms::ToolStripTextBox^  TextboxEffects3;
	private: System::Windows::Forms::ToolStripTextBox^  TextboxEffects4;
	private: System::Windows::Forms::ToolStripTextBox^  TextboxEffects5;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugRetrigger;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugReverserSimple;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugReverser;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugParameters;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugClip;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugPhaseInverter;
	private: System::Windows::Forms::ToolStripMenuItem^  PlugPanner;

	private: System::ComponentModel::IContainer^  components;
	public: event OnVolumeMixChanged	  ^ VolumeMixChanged;
	public: event OnNewPluginRequested	  ^ NewPluginRequested;
	public: event OnConfigWindowRequested ^ ConfigWindowRequested;
	public: event OnVisWindowRequested	  ^ VisWindowRequested;
	public: event OnBypassRequested		  ^ BypassRequested;
	public: event OnSoloRequested		  ^ SoloRequested;
	public: event OnSwapRequested		  ^ SwapRequested;

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
			this->PlugSawOscillator = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugSquareOscillator = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugNoise = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Separator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->TextboxAnalysers = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->PlugOscilloscope = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugSpectrum = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugSpectrogram = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugParameters = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Separator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->TextboxEffects1 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->PlugGain = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugClip = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugPhaseInverter = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TextboxEffects2 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->PlugBitcrush = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugDecimation = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TextboxEffects3 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->PlugPanner = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugStereoMerger = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugStereoToMs = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TextboxEffects4 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->PlugLpfAvg = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugLpfSinc = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugHpf = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugBpf = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TextboxEffects5 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->PlugDelay = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugRetriggerSimple = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugRetrigger = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugReverserSimple = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PlugReverser = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->ButtonSolo->Click += gcnew System::EventHandler(this, &RackItem::ButtonSolo_Click);
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
			this->ButtonBypass->BackColor = System::Drawing::SystemColors::Control;
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
			this->ButtonBypass->UseVisualStyleBackColor = false;
			this->ButtonBypass->Click += gcnew System::EventHandler(this, &RackItem::ButtonBypass_Click);
			// 
			// ButtonVis
			// 
			this->ButtonVis->Enabled = false;
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
			this->ButtonVis->Click += gcnew System::EventHandler(this, &RackItem::ButtonVis_Click);
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
			this->ButtonConfig->Click += gcnew System::EventHandler(this, &RackItem::ButtonConfig_Click);
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
			this->ButtonFlipDown->Click += gcnew System::EventHandler(this, &RackItem::ButtonFlipDown_Click);
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
			this->ButtonFlipUp->Click += gcnew System::EventHandler(this, &RackItem::ButtonFlipUp_Click);
			// 
			// TrackbarMixdown
			// 
			this->TrackbarMixdown->LargeChange = 4;
			this->TrackbarMixdown->Location = System::Drawing::Point(168, 8);
			this->TrackbarMixdown->Margin = System::Windows::Forms::Padding(0);
			this->TrackbarMixdown->Maximum = 100;
			this->TrackbarMixdown->Name = L"TrackbarMixdown";
			this->TrackbarMixdown->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->TrackbarMixdown->Size = System::Drawing::Size(45, 50);
			this->TrackbarMixdown->TabIndex = 4;
			this->TrackbarMixdown->TickFrequency = 16;
			this->TrackbarMixdown->Value = 100;
			this->TrackbarMixdown->Scroll += gcnew System::EventHandler(this, &RackItem::TrackbarMixdown_Scroll);
			// 
			// PluginList
			// 
			this->PluginList->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PluginList->ImageScalingSize = System::Drawing::Size(0, 16);
			this->PluginList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(35) {
				this->PlugNullPlugin, this->TextboxGenerators,
					this->PlugSineOscillator, this->PlugSawOscillator, this->PlugSquareOscillator, this->PlugNoise, this->Separator1, this->TextboxAnalysers,
					this->PlugOscilloscope, this->PlugSpectrum, this->PlugSpectrogram, this->PlugParameters, this->Separator2, this->TextboxEffects1,
					this->PlugGain, this->PlugClip, this->PlugPhaseInverter, this->TextboxEffects2, this->PlugBitcrush, this->PlugDecimation, this->TextboxEffects3,
					this->PlugPanner, this->PlugStereoMerger, this->PlugStereoToMs, this->TextboxEffects4, this->PlugLpfAvg, this->PlugLpfSinc, this->PlugHpf,
					this->PlugBpf, this->TextboxEffects5, this->PlugDelay, this->PlugRetriggerSimple, this->PlugRetrigger, this->PlugReverserSimple,
					this->PlugReverser
			});
			this->PluginList->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->PluginList->Name = L"PluginList";
			this->PluginList->Size = System::Drawing::Size(189, 715);
			// 
			// PlugNullPlugin
			// 
			this->PlugNullPlugin->Name = L"PlugNullPlugin";
			this->PlugNullPlugin->Size = System::Drawing::Size(188, 22);
			this->PlugNullPlugin->Text = L"None";
			this->PlugNullPlugin->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
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
			this->PlugSineOscillator->Size = System::Drawing::Size(188, 22);
			this->PlugSineOscillator->Text = L"Sine Wave";
			this->PlugSineOscillator->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugSawOscillator
			// 
			this->PlugSawOscillator->Name = L"PlugSawOscillator";
			this->PlugSawOscillator->Size = System::Drawing::Size(188, 22);
			this->PlugSawOscillator->Text = L"Saw Wave";
			this->PlugSawOscillator->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugSquareOscillator
			// 
			this->PlugSquareOscillator->Name = L"PlugSquareOscillator";
			this->PlugSquareOscillator->Size = System::Drawing::Size(188, 22);
			this->PlugSquareOscillator->Text = L"Square Wave";
			this->PlugSquareOscillator->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugNoise
			// 
			this->PlugNoise->Name = L"PlugNoise";
			this->PlugNoise->Size = System::Drawing::Size(188, 22);
			this->PlugNoise->Text = L"White noise";
			this->PlugNoise->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// Separator1
			// 
			this->Separator1->Name = L"Separator1";
			this->Separator1->Size = System::Drawing::Size(185, 6);
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
			this->PlugOscilloscope->Size = System::Drawing::Size(188, 22);
			this->PlugOscilloscope->Text = L"Oscilloscope";
			this->PlugOscilloscope->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugSpectrum
			// 
			this->PlugSpectrum->Name = L"PlugSpectrum";
			this->PlugSpectrum->Size = System::Drawing::Size(188, 22);
			this->PlugSpectrum->Text = L"Spectrum";
			this->PlugSpectrum->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugSpectrogram
			// 
			this->PlugSpectrogram->Name = L"PlugSpectrogram";
			this->PlugSpectrogram->Size = System::Drawing::Size(188, 22);
			this->PlugSpectrogram->Text = L"Spectrogram";
			this->PlugSpectrogram->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugParameters
			// 
			this->PlugParameters->Name = L"PlugParameters";
			this->PlugParameters->Size = System::Drawing::Size(188, 22);
			this->PlugParameters->Text = L"Signal Parameters";
			this->PlugParameters->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// Separator2
			// 
			this->Separator2->Name = L"Separator2";
			this->Separator2->Size = System::Drawing::Size(185, 6);
			// 
			// TextboxEffects1
			// 
			this->TextboxEffects1->BackColor = System::Drawing::Color::White;
			this->TextboxEffects1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TextboxEffects1->Enabled = false;
			this->TextboxEffects1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->TextboxEffects1->Name = L"TextboxEffects1";
			this->TextboxEffects1->Size = System::Drawing::Size(100, 13);
			this->TextboxEffects1->Text = L"Volume processors";
			// 
			// PlugGain
			// 
			this->PlugGain->Name = L"PlugGain";
			this->PlugGain->Size = System::Drawing::Size(188, 22);
			this->PlugGain->Text = L"Gain";
			this->PlugGain->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugClip
			// 
			this->PlugClip->Name = L"PlugClip";
			this->PlugClip->Size = System::Drawing::Size(188, 22);
			this->PlugClip->Text = L"Clip";
			this->PlugClip->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugPhaseInverter
			// 
			this->PlugPhaseInverter->Name = L"PlugPhaseInverter";
			this->PlugPhaseInverter->Size = System::Drawing::Size(188, 22);
			this->PlugPhaseInverter->Text = L"Phase Inverter";
			this->PlugPhaseInverter->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// TextboxEffects2
			// 
			this->TextboxEffects2->BackColor = System::Drawing::Color::White;
			this->TextboxEffects2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TextboxEffects2->Enabled = false;
			this->TextboxEffects2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->TextboxEffects2->Name = L"TextboxEffects2";
			this->TextboxEffects2->Size = System::Drawing::Size(100, 13);
			this->TextboxEffects2->Text = L"Downsamplers";
			// 
			// PlugBitcrush
			// 
			this->PlugBitcrush->Name = L"PlugBitcrush";
			this->PlugBitcrush->Size = System::Drawing::Size(188, 22);
			this->PlugBitcrush->Text = L"Bitcrusher";
			this->PlugBitcrush->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugDecimation
			// 
			this->PlugDecimation->Name = L"PlugDecimation";
			this->PlugDecimation->Size = System::Drawing::Size(188, 22);
			this->PlugDecimation->Text = L"Decimator";
			this->PlugDecimation->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// TextboxEffects3
			// 
			this->TextboxEffects3->BackColor = System::Drawing::Color::White;
			this->TextboxEffects3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TextboxEffects3->Enabled = false;
			this->TextboxEffects3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->TextboxEffects3->Name = L"TextboxEffects3";
			this->TextboxEffects3->Size = System::Drawing::Size(100, 13);
			this->TextboxEffects3->Text = L"Stereo processors";
			// 
			// PlugPanner
			// 
			this->PlugPanner->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PlugPanner->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->PlugPanner->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->PlugPanner->Name = L"PlugPanner";
			this->PlugPanner->Size = System::Drawing::Size(188, 22);
			this->PlugPanner->Text = L"Panner";
			this->PlugPanner->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			this->PlugPanner->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugStereoMerger
			// 
			this->PlugStereoMerger->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PlugStereoMerger->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->PlugStereoMerger->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->PlugStereoMerger->Name = L"PlugStereoMerger";
			this->PlugStereoMerger->Size = System::Drawing::Size(188, 22);
			this->PlugStereoMerger->Text = L"Stereo Merger";
			this->PlugStereoMerger->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			this->PlugStereoMerger->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugStereoToMs
			// 
			this->PlugStereoToMs->Name = L"PlugStereoToMs";
			this->PlugStereoToMs->Size = System::Drawing::Size(188, 22);
			this->PlugStereoToMs->Text = L"Stereo to Mid-Side";
			this->PlugStereoToMs->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// TextboxEffects4
			// 
			this->TextboxEffects4->BackColor = System::Drawing::Color::White;
			this->TextboxEffects4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TextboxEffects4->Enabled = false;
			this->TextboxEffects4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->TextboxEffects4->Name = L"TextboxEffects4";
			this->TextboxEffects4->Size = System::Drawing::Size(100, 13);
			this->TextboxEffects4->Text = L"Filters";
			// 
			// PlugLpfAvg
			// 
			this->PlugLpfAvg->Name = L"PlugLpfAvg";
			this->PlugLpfAvg->Size = System::Drawing::Size(188, 22);
			this->PlugLpfAvg->Text = L"Low Pass Filter (avg)";
			this->PlugLpfAvg->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugLpfSinc
			// 
			this->PlugLpfSinc->Name = L"PlugLpfSinc";
			this->PlugLpfSinc->Size = System::Drawing::Size(188, 22);
			this->PlugLpfSinc->Text = L"Low Pass Filter (sinc)";
			this->PlugLpfSinc->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugHpf
			// 
			this->PlugHpf->Name = L"PlugHpf";
			this->PlugHpf->Size = System::Drawing::Size(188, 22);
			this->PlugHpf->Text = L"High Pass Filter (sinc)";
			this->PlugHpf->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugBpf
			// 
			this->PlugBpf->Name = L"PlugBpf";
			this->PlugBpf->Size = System::Drawing::Size(188, 22);
			this->PlugBpf->Text = L"Band Pass Filter (sinc)";
			this->PlugBpf->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// TextboxEffects5
			// 
			this->TextboxEffects5->BackColor = System::Drawing::Color::White;
			this->TextboxEffects5->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TextboxEffects5->Enabled = false;
			this->TextboxEffects5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7, System::Drawing::FontStyle::Bold));
			this->TextboxEffects5->Name = L"TextboxEffects5";
			this->TextboxEffects5->Size = System::Drawing::Size(100, 13);
			this->TextboxEffects5->Text = L"Time manipulators";
			// 
			// PlugDelay
			// 
			this->PlugDelay->Name = L"PlugDelay";
			this->PlugDelay->Size = System::Drawing::Size(188, 22);
			this->PlugDelay->Text = L"Delay";
			this->PlugDelay->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugRetriggerSimple
			// 
			this->PlugRetriggerSimple->Name = L"PlugRetriggerSimple";
			this->PlugRetriggerSimple->Size = System::Drawing::Size(188, 22);
			this->PlugRetriggerSimple->Text = L"Retrigger (Simple)";
			this->PlugRetriggerSimple->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugRetrigger
			// 
			this->PlugRetrigger->Name = L"PlugRetrigger";
			this->PlugRetrigger->Size = System::Drawing::Size(188, 22);
			this->PlugRetrigger->Text = L"Retrigger";
			this->PlugRetrigger->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugReverserSimple
			// 
			this->PlugReverserSimple->Name = L"PlugReverserSimple";
			this->PlugReverserSimple->Size = System::Drawing::Size(188, 22);
			this->PlugReverserSimple->Text = L"Reverser (Simple)";
			this->PlugReverserSimple->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
			// 
			// PlugReverser
			// 
			this->PlugReverser->Name = L"PlugReverser";
			this->PlugReverser->Size = System::Drawing::Size(188, 22);
			this->PlugReverser->Text = L"Reverser";
			this->PlugReverser->Click += gcnew System::EventHandler(this, &RackItem::SetNewPlugin);
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

	public:
		RackItemContents^ Content = gcnew RackItemContents();
	
		//Aktualizacja zawartoœci RackItemu przez MainWindow
		System::Void UpdateForm()
		{
			CurrentPluginName->Text = gcnew System::String(Content->CurrentPluginName);
			TrackbarMixdown->Value = Content->DryWetMix * 100.0f;
			ButtonConfig->Enabled = Content->HasConfigWindow;
			ButtonVis->Enabled = Content->HasVisWindow;
			ButtonSolo->Enabled = !Content->IsNullPlugin;
			ButtonBypass->Enabled = !Content->IsNullPlugin;
			ButtonBypass->BackColor = (Content->IsBypassed && !Content->IsNullPlugin) ? System::Drawing::Color::Pink : System::Drawing::SystemColors::Control;


			if (RackItemId == 0) ButtonFlipUp->Enabled = false;
			if (LastRackItem)  ButtonFlipDown->Enabled = false;
		}
		System::Void SetContents(RackItemContents^ NewContents) { Content = NewContents; }
		System::Void UpdateVolumeMixStatus(System::Single NewVolumeMix)
		{
			TrackbarMixdown->Value = NewVolumeMix * 100.0f;
		}

	private:
	
		//Interfejs RackItem
		System::Void ButtonSwap_Click(System::Object^  sender, System::EventArgs^  e)
		{
			Button^ ButtonRef = (cli::safe_cast<System::Windows::Forms::Button^>(sender));
			System::Drawing::Point ButtonLocation = ButtonRef->Location;
			
			PluginList->Show();
			PluginList->Location = MousePosition;
		}
		System::Void ButtonConfig_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->ConfigWindowRequested(RackItemId);
		}
		System::Void TrackbarMixdown_Scroll(System::Object^  sender, System::EventArgs^  e)
		{
			VolumeMixChanged(RackItemId, (float)TrackbarMixdown->Value / 100.0f);
		}
		System::Void ButtonFlipUp_Click(System::Object^  sender, System::EventArgs^  e)
		{
			SwapRequested(RackItemId, false);
		}
		System::Void ButtonFlipDown_Click(System::Object^  sender, System::EventArgs^  e)
		{
			SwapRequested(RackItemId, true);
		}
		System::Void ButtonVis_Click(System::Object^  sender, System::EventArgs^  e)
		{
			VisWindowRequested(RackItemId);
		}
		System::Void ButtonBypass_Click(System::Object^  sender, System::EventArgs^  e)
		{
			BypassRequested(RackItemId);
		}
		System::Void ButtonSolo_Click(System::Object^  sender, System::EventArgs^  e)
		{
			SoloRequested(RackItemId);
		}
		System::Void SetNewPlugin(System::Object^  sender, System::EventArgs^  e)
		{
			System::Windows::Forms::ToolStripMenuItem^  SelectedToolstrip = (System::Windows::Forms::ToolStripMenuItem^)sender;
			System::String^ PluginName = SelectedToolstrip->Text;
			NewPluginRequested(RackItemId, PluginName);
		}
	};
}
