#pragma once
#include <sstream>
#include <fstream>
#include <thread>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
 

namespace BenchmarkApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class ProgressForm : public System::Windows::Forms::Form
	{
	public:
		
		ProgressForm(bool cpu_active, bool network_active, bool file_active)
		{
			
			std::string infoString = info();
			managedInfoString = gcnew String(infoString.c_str());
			InitializeComponent();
			this->cpu_active = cpu_active;
			this->network_active = network_active;
			this->file_active = file_active;
			//
			//TODO: Add the constructor code here
			//
		}
		public: delegate void UpdateProgressBarDelegate(int value);
	    
		
		std::string info();
		double cpuMeasurement();
		double networkMeasurement();
		double dataMeasurement();
		std::string networkScoreRepresentation(double networkScore) {
			std::string comment;

			if (networkScore >= 90.0f) {
				comment = "- Excellent!";
			}
			else if (networkScore >= 60.0f) {
				comment = "- Good";
			}
			else if (networkScore >= 50.0f) {
				comment = "- Average";
			}
			else if (networkScore >= 0.0000001f) {
				comment = "- Needs improvement";
			}

			std::string representation = "\nNetwork Score: " + std::to_string(networkScore) + comment;
			return representation;
		}
		std::string dataScoreRepresentation(double dataScore) {
			std::string comment;

			if (dataScore >= 90.0f) {
				comment = "- Excellent!";
			}
			else if (dataScore >= 70.0f) {
				comment = "- Good";
			}
			else if (dataScore >= 50.0f) {
				comment = "- Average";
			}
			else if (dataScore >= 0.0000001f) {
				comment = "- Needs improvement";
			}

			std::string representation = "\nData Score: " + std::to_string(dataScore) + comment;
			return representation;
		}
		std::string cpuScoreRepresentation(double cpuScore) {
			std::string comment;

			if (cpuScore >= 90.0f) {
				comment = "- Excellent!";
			}
			else if (cpuScore >= 70.0f) {
				comment = "- Good";
			}
			else if (cpuScore >= 50.0f) {
				comment = "- Average";
			}
			else if (cpuScore >= 0.0000001f) {
				comment = "- Needs improvement";
			}

			std::string representation = "\nCPU Score: " + std::to_string(cpuScore) + comment;
			return representation;
		}
	

		void UpdateProgressBar(int value)
		{
			if (progressBar1->InvokeRequired)
			{
				BeginInvoke(gcnew UpdateProgressBarDelegate(this, &ProgressForm::UpdateProgressBar), value);
			}
			else
			{
				progressBar1->Increment(value);
			}
		}
		void RunTests() {
			double dataTime = 0;
			double netTime = 0;
			double cpuTime = 0;
			if (network_active) {
				netTime=networkMeasurement();
				network_active = false;
				if (testThread != nullptr) {
					testThread->Join();
				}
				
			}
			UpdateProgressBar(20);

			if (file_active && !network_active) {
				dataTime=dataMeasurement();
				file_active = false;
				
				if (testThread != nullptr) {
					testThread->Join();
				}
				
			}
			UpdateProgressBar(35);
			if (cpu_active) {
				cpuTime=cpuMeasurement();
				if (testThread != nullptr) {
					testThread->Join();
				}

				
			}
			UpdateProgressBar(45);
			
			timer1->Stop();

			static const double NetworkWeight = 0.15;
			static const double DataWeight = 0.35;
			static const double CPUWeight = 0.5;
			double net = 0;;
			if (netTime > 0.01f)
			{
				net = (2.2f / netTime) * 100.0f;
			}
			//								     reference values
			double normalizedNetwork =  net > 99.9f ? 100.0f : net;
			double normalizedData = (dataTime / 20.0f) * 100.0f;
			double normalizedCPU = (cpuTime / 33.0f) * 100.0f;

			
			double performanceScore = (normalizedNetwork * NetworkWeight) + (normalizedData * DataWeight) + (normalizedCPU * CPUWeight);

			std::string res = "\n";
			res += networkScoreRepresentation(normalizedNetwork);
			res += dataScoreRepresentation(normalizedData);
			res += cpuScoreRepresentation(normalizedCPU);
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << performanceScore;
			std::string s = stream.str();
			res += "\nPerformance Score: " + s;// .ToString("F2");

			
			this->infoLabel->Text += gcnew String(res.c_str());
			std::ofstream outFile("Benchmark_Result.txt", std::ios::app);

			if (outFile.is_open()) {
				// Write date and time to the file
				outFile << info() << std::endl;

				outFile << res << std::endl;
			}
			button->Enabled = true;
		}

		System::String^ managedInfoString;
		bool saveData = false;
		
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ProgressForm()
		{
			if (components)
			{
				delete components;
			}
		}
	
	private: bool cpu_active = false, network_active = false, file_active = false;
	private: System::Threading::Thread^ testThread;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ infoLabel;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;


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
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->infoLabel = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->CalendarFont = (gcnew System::Drawing::Font(L"Mongolian Baiti", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->dateTimePicker1->Enabled = false;
			this->dateTimePicker1->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dateTimePicker1->Location = System::Drawing::Point(241, 19);
			this->dateTimePicker1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(483, 39);
			this->dateTimePicker1->TabIndex = 0;
			this->dateTimePicker1->ValueChanged += gcnew System::EventHandler(this, &ProgressForm::dateTimePicker1_ValueChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(535, 572);
			this->button1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(249, 70);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Exit";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ProgressForm::button1_Click);
			// 
			// button
			// 
			this->button->Location = System::Drawing::Point(165, 572);
			this->button->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button->Name = L"button";
			this->button->Size = System::Drawing::Size(249, 70);
			this->button->TabIndex = 2;
			this->button->Text = L"Save Data";
			this->button->UseVisualStyleBackColor = true;
			this->button->Click += gcnew System::EventHandler(this, &ProgressForm::button_Click);
			this->button->Enabled = false;
			// 
			// progressBar1
			// 
			this->progressBar1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->progressBar1->Location = System::Drawing::Point(165, 527);
			this->progressBar1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(619, 36);
			this->progressBar1->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(76, 531);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(85, 25);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Progress:";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(165, 571);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(249, 70);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Confirm ";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &ProgressForm::button2_Click);
			// 
			// infoLabel
			// 
			this->infoLabel->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->infoLabel->AutoSize = true;
			this->infoLabel->Location = System::Drawing::Point(236, 93);
			this->infoLabel->Name = L"infoLabel";
			this->infoLabel->Size = System::Drawing::Size(0, 25);
			this->infoLabel->TabIndex = 6;
			this->infoLabel->Text = managedInfoString;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &ProgressForm::timer1_Tick);
			// 
			// ProgressForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(942, 706);
			this->Controls->Add(this->infoLabel);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->button);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dateTimePicker1);
			this->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"ProgressForm";
			this->Text = L"Progress Window";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &ProgressForm::ProgressForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &ProgressForm::ProgressForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void dateTimePicker1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!saveData) {
			std::ofstream outFile("Benchmark_Result.txt", std::ios::app);
			outFile.close();
			std::remove("Benchmark_Result.txt");
		}
		Application::Exit();
	}
	private: System::Void ProgressForm_Load(System::Object^ sender, System::EventArgs^ e) {
		
	}

	private: System::Void ProgressForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
		Application::Exit();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		button2->Hide();
		button->Show();

		//timer1->Enabled = true;
		System::Threading::Thread^ testThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &ProgressForm::RunTests));
		testThread->Start();

		
		
		
		}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		/*if (!network_active)  UpdateProgressBar(20);

		if (!file_active)   UpdateProgressBar(35);

		if (!cpu_active)  UpdateProgressBar(45);*/
	}

	private: System::Void button_Click(System::Object^ sender, System::EventArgs^ e) {
		
		saveData = true;
		auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		struct tm* timeinfo;
		char buffer[80];

		timeinfo = localtime(&now);
		strftime(buffer, sizeof(buffer), "Benchmark date: %d/%m/%Y at %H:%M", timeinfo);

		std::string timestamp(buffer);

		std::ofstream outFile("Benchmark_Result.txt", std::ios::app);

		if (outFile.is_open()) {
			outFile << std::endl << timestamp << std::endl;

			// Close the file
			outFile.close();
		}


	
}
};
}
