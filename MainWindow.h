#pragma once

#include "TranslateInterface.h"

namespace PWTranslator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: TranslateInterface* translator;
	internal: System::Windows::Forms::Label^ label7;
	private:
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(759, 8);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(78, 20);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Обзор...";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainWindow::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(350, 8);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(403, 20);
			this->textBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(332, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Путь до папки interface, которую надо перевести";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->label2->Location = System::Drawing::Point(12, 41);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(314, 16);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Путь до папки interface, откуда брать перевод";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(350, 40);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(403, 20);
			this->textBox2->TabIndex = 4;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(760, 41);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(78, 20);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Обзор...";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainWindow::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(760, 106);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(78, 20);
			this->button3->TabIndex = 11;
			this->button3->Text = L"Обзор...";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainWindow::button3_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(350, 105);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(403, 20);
			this->textBox3->TabIndex = 10;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->label3->Location = System::Drawing::Point(12, 106);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(297, 16);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Путь до папки config, откуда брать перевод";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->label4->Location = System::Drawing::Point(12, 74);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(315, 16);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Путь до папки config, которую надо перевести";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(350, 73);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(403, 20);
			this->textBox4->TabIndex = 7;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(759, 73);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(78, 20);
			this->button4->TabIndex = 6;
			this->button4->Text = L"Обзор...";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainWindow::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(760, 135);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(78, 20);
			this->button5->TabIndex = 14;
			this->button5->Text = L"Обзор...";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MainWindow::button5_Click);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(350, 134);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(403, 20);
			this->textBox5->TabIndex = 13;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->label5->Location = System::Drawing::Point(12, 135);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(215, 16);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Папка для сохранения interface";
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(760, 165);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(78, 20);
			this->button6->TabIndex = 17;
			this->button6->Text = L"Обзор...";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MainWindow::button6_Click);
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(350, 164);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(403, 20);
			this->textBox6->TabIndex = 16;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->label6->Location = System::Drawing::Point(12, 165);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(198, 16);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Папка для сохранения config";
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(15, 199);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(346, 33);
			this->button7->TabIndex = 18;
			this->button7->Text = L"Перевести interface";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MainWindow::button7_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(491, 199);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(346, 33);
			this->button8->TabIndex = 19;
			this->button8->Text = L"Перевести config";
			this->button8->UseVisualStyleBackColor = true;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(15, 276);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(823, 33);
			this->progressBar1->TabIndex = 20;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(12, 255);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(0, 18);
			this->label7->TabIndex = 21;
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(850, 321);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MainWindow";
			this->Text = L"PW Translator";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ fileName = folderBrowserDialog1->SelectedPath;
			textBox1->Text = fileName;
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ fileName = folderBrowserDialog1->SelectedPath;
			textBox2->Text = fileName;
		}
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ fileName = folderBrowserDialog1->SelectedPath;
			textBox3->Text = fileName;
		}
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ fileName = folderBrowserDialog1->SelectedPath;
			textBox4->Text = fileName;
		}
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ fileName = folderBrowserDialog1->SelectedPath;
			textBox5->Text = fileName;
		}
	}
	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ fileName = folderBrowserDialog1->SelectedPath;
			textBox6->Text = fileName;
		}
	}
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
		this->translator = new TranslateInterface(this->textBox1->Text, this->textBox2->Text, this->textBox5->Text);
		vector<wstring> files = this->translator->getAllFiles();
		wstring progress = L"Progress: 0/" + to_wstring(files.size());
		this->label7->Text = gcnew String(progress.c_str());
		this->progressBar1->Maximum = files.size();
		for (int index = 0; index < files.size(); index++)
		{
			this->translator->translateFile(files[index]);
			progress = L"Progress: " + to_wstring(index) + L"/" + to_wstring(files.size());
			this->label7->Text = gcnew String(progress.c_str());
			this->label7->Update();
			this->progressBar1->Increment(1);
		}
		progress = L"Progress: " + to_wstring(files.size()) + L"/" + to_wstring(files.size()) + L"  Completed!";
		this->label7->Text = gcnew String(progress.c_str()); 
		this->progressBar1->Increment(1);
	}
	};
}
