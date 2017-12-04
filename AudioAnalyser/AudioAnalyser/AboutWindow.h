#pragma once

namespace AudioAnalyser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AboutWindow
	/// </summary>
	public ref class AboutWindow : public System::Windows::Forms::Form
	{
	public:
		AboutWindow(void)
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
		~AboutWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::PictureBox^  AppLogo;
	private: System::Windows::Forms::Label^  StaticLabelProductName;
	private: System::Windows::Forms::Label^  StaticLabelProductVersion;
	private: System::Windows::Forms::Label^  StaticLabelProductAuthor1;
	private: System::Windows::Forms::Label^  StaticLabelProductAuthor2;
	private: System::Windows::Forms::Label^  StaticLabelProductAuthor3;
	private: System::Windows::Forms::Label^  StaticLabelProductRelease;
	private: System::Windows::Forms::Button^  ButtonClose;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(AboutWindow::typeid));
			this->AppLogo = (gcnew System::Windows::Forms::PictureBox());
			this->StaticLabelProductName = (gcnew System::Windows::Forms::Label());
			this->StaticLabelProductVersion = (gcnew System::Windows::Forms::Label());
			this->StaticLabelProductAuthor1 = (gcnew System::Windows::Forms::Label());
			this->StaticLabelProductAuthor2 = (gcnew System::Windows::Forms::Label());
			this->StaticLabelProductAuthor3 = (gcnew System::Windows::Forms::Label());
			this->StaticLabelProductRelease = (gcnew System::Windows::Forms::Label());
			this->ButtonClose = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AppLogo))->BeginInit();
			this->SuspendLayout();
			// 
			// AppLogo
			// 
			this->AppLogo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->AppLogo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"AppLogo.Image")));
			this->AppLogo->Location = System::Drawing::Point(18, 16);
			this->AppLogo->Name = L"AppLogo";
			this->AppLogo->Size = System::Drawing::Size(130, 130);
			this->AppLogo->TabIndex = 0;
			this->AppLogo->TabStop = false;
			// 
			// StaticLabelProductName
			// 
			this->StaticLabelProductName->AutoSize = true;
			this->StaticLabelProductName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 22, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->StaticLabelProductName->Location = System::Drawing::Point(159, 16);
			this->StaticLabelProductName->Name = L"StaticLabelProductName";
			this->StaticLabelProductName->Size = System::Drawing::Size(209, 41);
			this->StaticLabelProductName->TabIndex = 1;
			this->StaticLabelProductName->Text = L"AudioAnalyser";
			// 
			// StaticLabelProductVersion
			// 
			this->StaticLabelProductVersion->AutoSize = true;
			this->StaticLabelProductVersion->Location = System::Drawing::Point(363, 37);
			this->StaticLabelProductVersion->Name = L"StaticLabelProductVersion";
			this->StaticLabelProductVersion->Size = System::Drawing::Size(31, 13);
			this->StaticLabelProductVersion->TabIndex = 2;
			this->StaticLabelProductVersion->Text = L"v 1.0";
			// 
			// StaticLabelProductAuthor1
			// 
			this->StaticLabelProductAuthor1->AutoSize = true;
			this->StaticLabelProductAuthor1->Location = System::Drawing::Point(163, 62);
			this->StaticLabelProductAuthor1->Name = L"StaticLabelProductAuthor1";
			this->StaticLabelProductAuthor1->Size = System::Drawing::Size(109, 13);
			this->StaticLabelProductAuthor1->TabIndex = 3;
			this->StaticLabelProductAuthor1->Text = L"Krzysztof NiedŸwiecki";
			// 
			// StaticLabelProductAuthor2
			// 
			this->StaticLabelProductAuthor2->AutoSize = true;
			this->StaticLabelProductAuthor2->Location = System::Drawing::Point(164, 78);
			this->StaticLabelProductAuthor2->Name = L"StaticLabelProductAuthor2";
			this->StaticLabelProductAuthor2->Size = System::Drawing::Size(138, 13);
			this->StaticLabelProductAuthor2->TabIndex = 4;
			this->StaticLabelProductAuthor2->Text = L"k.niedzwiecki@hotmail.com";
			// 
			// StaticLabelProductAuthor3
			// 
			this->StaticLabelProductAuthor3->AutoSize = true;
			this->StaticLabelProductAuthor3->Location = System::Drawing::Point(163, 100);
			this->StaticLabelProductAuthor3->Name = L"StaticLabelProductAuthor3";
			this->StaticLabelProductAuthor3->Size = System::Drawing::Size(153, 13);
			this->StaticLabelProductAuthor3->TabIndex = 5;
			this->StaticLabelProductAuthor3->Text = L"Maritime University of Szczecin";
			// 
			// StaticLabelProductRelease
			// 
			this->StaticLabelProductRelease->AutoSize = true;
			this->StaticLabelProductRelease->Location = System::Drawing::Point(163, 116);
			this->StaticLabelProductRelease->Name = L"StaticLabelProductRelease";
			this->StaticLabelProductRelease->Size = System::Drawing::Size(64, 13);
			this->StaticLabelProductRelease->TabIndex = 6;
			this->StaticLabelProductRelease->Text = L"2017 - 2018";
			// 
			// ButtonClose
			// 
			this->ButtonClose->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->ButtonClose->Location = System::Drawing::Point(330, 123);
			this->ButtonClose->Name = L"ButtonClose";
			this->ButtonClose->Size = System::Drawing::Size(75, 23);
			this->ButtonClose->TabIndex = 7;
			this->ButtonClose->Text = L"Close";
			this->ButtonClose->UseVisualStyleBackColor = true;
			// 
			// AboutWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->ButtonClose;
			this->ClientSize = System::Drawing::Size(420, 158);
			this->Controls->Add(this->ButtonClose);
			this->Controls->Add(this->StaticLabelProductRelease);
			this->Controls->Add(this->StaticLabelProductAuthor3);
			this->Controls->Add(this->StaticLabelProductAuthor2);
			this->Controls->Add(this->StaticLabelProductAuthor1);
			this->Controls->Add(this->StaticLabelProductVersion);
			this->Controls->Add(this->StaticLabelProductName);
			this->Controls->Add(this->AppLogo);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"AboutWindow";
			this->Text = L"About AudioAnalyser";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AppLogo))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
