#pragma once
#include "ProgressForm.h"

namespace BenchmarkApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: ProgressForm^ progressForm;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::CheckBox^ checkBox1;

	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::CheckBox^ checkBox4;
	
	private: bool cpu_active = false, network_active = false, file_active = false;
	private: System::Windows::Forms::Label^ label2;


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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(356, 27);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(215, 31);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Benchmark App";
			this->label1->Click += gcnew System::EventHandler(this, &MainForm::label1_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->ColumnCount = 4;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				46.61354F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				53.38646F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				254)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				190)));
			this->tableLayoutPanel1->Controls->Add(this->checkBox1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->button1, 3, 0);
			this->tableLayoutPanel1->Controls->Add(this->button2, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->checkBox3, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->checkBox4, 2, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(97, 258);
			this->tableLayoutPanel1->MinimumSize = System::Drawing::Size(695, 137);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(695, 137);
			this->tableLayoutPanel1->TabIndex = 1;
			this->tableLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::tableLayoutPanel1_Paint);
			// 
			// checkBox1
			// 
			this->checkBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(3, 3);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(110, 62);
			this->checkBox1->TabIndex = 2;
			this->checkBox1->Text = L"CPU";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox1_CheckedChanged);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(507, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(185, 62);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Run Selected Only";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->button2->Location = System::Drawing::Point(253, 71);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(248, 63);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Start (Run All)";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// checkBox3
			// 
			this->checkBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(119, 3);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(128, 62);
			this->checkBox3->TabIndex = 4;
			this->checkBox3->Text = L"Network";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox3_CheckedChanged);
			// 
			// checkBox4
			// 
			this->checkBox4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(253, 3);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(248, 62);
			this->checkBox4->TabIndex = 5;
			this->checkBox4->Text = L"Data (Read/Write)";
			this->checkBox4->UseVisualStyleBackColor = true;
			this->checkBox4->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox4_CheckedChanged_1);
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(601, 239);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(83, 16);
			this->label2->TabIndex = 2;
			this->label2->Text = L" ";
			this->label2->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->label2->Click += gcnew System::EventHandler(this, &MainForm::label2_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(887, 459);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label2);
			this->MaximumSize = System::Drawing::Size(905, 506);
			this->MinimumSize = System::Drawing::Size(905, 47);
			this->Name = L"MainForm";
			this->Text = L"PC Benchmarking";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void tableLayoutPanel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	
		this->label2->Text = "All running ";

		progressForm = gcnew ProgressForm(true,true,true);
		progressForm->Show();

		this->Hide();
		

	}
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void checkBox3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (!network_active) network_active = true;
		else network_active = false;

		label2->Text = "Selected ";
		if (cpu_active) { this->label2->Text += "cpu "; }

		if (network_active) { this->label2->Text += "network "; }

		if (file_active) { this->label2->Text += "data "; }

		if (label2->Text->ToString() == "Selected ") { this->label2->Text += "none "; }
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (!cpu_active) cpu_active = true;
		else cpu_active = false;

		label2->Text = "Selected ";
		if (cpu_active) { this->label2->Text += "cpu "; }

		if (network_active) { this->label2->Text += "network "; }

		if (file_active) { this->label2->Text += "data "; }

		if (label2->Text->ToString() == "Selected ") { this->label2->Text += "none "; }
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		label2->Text = "Selected ";

		if (cpu_active || network_active || file_active) {
			progressForm = gcnew ProgressForm(cpu_active, network_active, file_active);

			progressForm->Show();

			this->Hide();
		}
	}
	private: System::Void checkBox4_CheckedChanged_1(System::Object^ sender, System::EventArgs^ e) {
		if (!file_active)  file_active = true; 	
		else file_active = false;

		label2->Text = "Selected ";
		if (cpu_active) { this->label2->Text += "cpu "; }

		if (network_active) { this->label2->Text += "network "; }

		if (file_active) { this->label2->Text += "data "; }

		if (label2->Text->ToString() == "Selected ") { this->label2->Text += "none "; }
		
	}


};
}
