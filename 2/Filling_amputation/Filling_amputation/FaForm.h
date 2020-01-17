#pragma once

#include <algorithm>

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 1. Алгоритмы Брезенхэма
Среда разработки: Visual Studio 2013
Дата: 30.09.2015
Реализованы алгоритмы построчной заливки, обычной заливки и отсечения.
Подробнее см. в меню "О программе".
*/


namespace Filling_amputation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FaForm
	/// </summary>
	public ref class FaForm : public System::Windows::Forms::Form
	{
	public:
		FaForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			bitmapF1 = gcnew Bitmap(pictureBoxF1->Width, pictureBoxF1->Height);
			pictureBoxF1->Image = bitmapF1;
			bitmapF2 = gcnew Bitmap(pictureBoxF2->Width, pictureBoxF2->Height);
			pictureBoxF2->Image = bitmapF2;
			bitmapA = gcnew Bitmap(pictureBoxA->Width, pictureBoxA->Height);
			pictureBoxA->Image = bitmapA;
			colorDialogBg->Color = Color::White;
			colorDialogFg->Color = Color::Black;
			colorDialogFilling->Color = Color::Blue;
			pen = gcnew Pen(Color::Black);
			pictureBoxA->Cursor = Cursors::Cross;
			delay = 15;
			x = y = 0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FaForm()
		{
			if (components)
			{
				delete components;
			}

			if (pen) {
				delete pen;
			}

			if (bitmapF1)
			{
				delete bitmapF1;
			}

			if (bitmapF2)
			{
				delete bitmapF2;
			}

			if (bitmapA)
			{
				delete bitmapA;
			}

			if (startF1) {
				delete startF1;
			}

			if (currentF1) {
				delete currentF1;
			}

			if (startF2) {
				delete startF2;
			}

			if (currentF2) {
				delete currentF2;
			}
			if (startA) {
				delete startA;
			}
			if (endA) {
				delete endA;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBoxF1;
	protected:

	private: System::Windows::Forms::MenuStrip^  menuStrip1;






	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

	private: System::Windows::Forms::ColorDialog^  colorDialogBg;
	private: System::Windows::Forms::ColorDialog^  colorDialogFg;
	private: System::Windows::Forms::PictureBox^  pictureBoxF2;
	private: System::Windows::Forms::PictureBox^  pictureBoxA;

		/// <summary>
		/// Pen to draw.
		/// </summary>
		Pen^ pen;

		/// <summary>
		/// Delay.
		/// </summary>
		int delay;

		/// <summary>
		/// Bitmap for first filling to draw in.
		/// </summary>
		Bitmap^ bitmapF1;

		/// <summary>
		/// Bitmap for second filling to draw in.
		/// </summary>
		Bitmap^ bitmapF2;

		/// <summary>
		/// Bitmap for amputation to draw in.
		/// </summary>
		Bitmap^ bitmapA;

		/// <summary>
		/// Start polygon point of first filling.
		/// </summary>
		Point^ startF1;

		/// <summary>
		/// Current polygon point of first filling.
		/// </summary>
		Point^ currentF1;


private: System::Windows::Forms::Button^  buttonClearF1;
private: System::Windows::Forms::Button^  buttonClearF2;
private: System::Windows::Forms::Button^  buttonClearA;

		/// <summary>
		/// Start polygon point of second filling.
		/// </summary>
		Point^ startF2;
private: System::Windows::Forms::CheckBox^  checkBoxF1;
private: System::Windows::Forms::CheckBox^  checkBoxF2;
private: System::Windows::Forms::CheckBox^  checkBoxDelay1;
private: System::Windows::Forms::CheckBox^  checkBoxDelay2;
private: System::Windows::Forms::ToolStripMenuItem^  оПрограммеToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  настройкиToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  цветФонаToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  цветПераИГраницToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  цветЗаливкиToolStripMenuItem;
private: System::Windows::Forms::ColorDialog^  colorDialogFilling;



private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  label3;


		int x, y;

		/// <summary>
		/// Current polygon point of second filling.
		/// </summary>
		Point^ currentF2;

		/// <summary>
		/// Start segment point.
		/// </summary>
		Point^ startA;

		/// <summary>
		/// Start segment point.
		/// </summary>
		Point^ endA;

		/// <summary>
		/// Clears picture box.
		/// </summary>
		void clearPictureBox(PictureBox^ pb);

		/// <summary>
		/// Clears all picture boxes.
		/// </summary>
		void clearAll();

		/// <summary>
		/// Handles polygon painting.
		/// </summary>
		void handlePolygonPainting(PictureBox^ pb, Bitmap^ bp, Point^ start, Point^ current, int x, int y);

		/// <summary>
		/// Does string filling.
		/// </summary>
		void stringFilling(PictureBox^ pb, Bitmap^ bp, int x0, int y0, Color^ fillColor, Color^ borderColor, int delay);

		/// <summary>
		/// Does simple filling.
		/// </summary>
		void simpleFilling(PictureBox^ pb, Bitmap^ bp, int x0, int y0, Color^ fillColor, Color^ borderColor, bool delay);


		/// <summary>
		/// Classifies the point site.
		/// </summary>
		int classify(int x0, int y0, int x1, int y1, Point^ point);


		/// <summary>
		/// Does amputation.
		/// </summary>
		bool amputation(int x0, int y0, int x1, int y1, Point^ start, Point^ end);



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBoxF1 = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->настройкиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветФонаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветПераИГраницToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветЗаливкиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->colorDialogBg = (gcnew System::Windows::Forms::ColorDialog());
			this->colorDialogFg = (gcnew System::Windows::Forms::ColorDialog());
			this->pictureBoxF2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxA = (gcnew System::Windows::Forms::PictureBox());
			this->buttonClearF1 = (gcnew System::Windows::Forms::Button());
			this->buttonClearF2 = (gcnew System::Windows::Forms::Button());
			this->buttonClearA = (gcnew System::Windows::Forms::Button());
			this->checkBoxF1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxF2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxDelay1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxDelay2 = (gcnew System::Windows::Forms::CheckBox());
			this->colorDialogFilling = (gcnew System::Windows::Forms::ColorDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxF1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxF2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxA))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBoxF1
			// 
			this->pictureBoxF1->BackColor = System::Drawing::Color::White;
			this->pictureBoxF1->Location = System::Drawing::Point(12, 70);
			this->pictureBoxF1->Name = L"pictureBoxF1";
			this->pictureBoxF1->Size = System::Drawing::Size(245, 245);
			this->pictureBoxF1->TabIndex = 0;
			this->pictureBoxF1->TabStop = false;
			this->pictureBoxF1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &FaForm::pictureBoxF1_MouseClick);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->оПрограммеToolStripMenuItem,
					this->настройкиToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(814, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(94, 20);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
			this->оПрограммеToolStripMenuItem->Click += gcnew System::EventHandler(this, &FaForm::оПрограммеToolStripMenuItem_Click);
			// 
			// настройкиToolStripMenuItem
			// 
			this->настройкиToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->цветФонаToolStripMenuItem,
					this->цветПераИГраницToolStripMenuItem, this->цветЗаливкиToolStripMenuItem
			});
			this->настройкиToolStripMenuItem->Name = L"настройкиToolStripMenuItem";
			this->настройкиToolStripMenuItem->Size = System::Drawing::Size(79, 20);
			this->настройкиToolStripMenuItem->Text = L"Настройки";
			// 
			// цветФонаToolStripMenuItem
			// 
			this->цветФонаToolStripMenuItem->Name = L"цветФонаToolStripMenuItem";
			this->цветФонаToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->цветФонаToolStripMenuItem->Text = L"Цвет фона";
			this->цветФонаToolStripMenuItem->Click += gcnew System::EventHandler(this, &FaForm::цветФонаToolStripMenuItem_Click);
			// 
			// цветПераИГраницToolStripMenuItem
			// 
			this->цветПераИГраницToolStripMenuItem->Name = L"цветПераИГраницToolStripMenuItem";
			this->цветПераИГраницToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->цветПераИГраницToolStripMenuItem->Text = L"Цвет пера и границ";
			this->цветПераИГраницToolStripMenuItem->Click += gcnew System::EventHandler(this, &FaForm::цветПераИГраницToolStripMenuItem_Click);
			// 
			// цветЗаливкиToolStripMenuItem
			// 
			this->цветЗаливкиToolStripMenuItem->Name = L"цветЗаливкиToolStripMenuItem";
			this->цветЗаливкиToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->цветЗаливкиToolStripMenuItem->Text = L"Цвет заливки";
			this->цветЗаливкиToolStripMenuItem->Click += gcnew System::EventHandler(this, &FaForm::цветЗаливкиToolStripMenuItem_Click);
			// 
			// pictureBoxF2
			// 
			this->pictureBoxF2->BackColor = System::Drawing::Color::White;
			this->pictureBoxF2->Location = System::Drawing::Point(283, 70);
			this->pictureBoxF2->Name = L"pictureBoxF2";
			this->pictureBoxF2->Size = System::Drawing::Size(245, 245);
			this->pictureBoxF2->TabIndex = 2;
			this->pictureBoxF2->TabStop = false;
			this->pictureBoxF2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &FaForm::pictureBoxF2_MouseClick);
			// 
			// pictureBoxA
			// 
			this->pictureBoxA->BackColor = System::Drawing::Color::White;
			this->pictureBoxA->Location = System::Drawing::Point(555, 70);
			this->pictureBoxA->Name = L"pictureBoxA";
			this->pictureBoxA->Size = System::Drawing::Size(245, 245);
			this->pictureBoxA->TabIndex = 3;
			this->pictureBoxA->TabStop = false;
			this->pictureBoxA->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &FaForm::pictureBoxA_MouseDown);
			this->pictureBoxA->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &FaForm::pictureBoxA_MouseMove);
			// 
			// buttonClearF1
			// 
			this->buttonClearF1->Location = System::Drawing::Point(90, 324);
			this->buttonClearF1->Name = L"buttonClearF1";
			this->buttonClearF1->Size = System::Drawing::Size(75, 23);
			this->buttonClearF1->TabIndex = 4;
			this->buttonClearF1->Text = L"Очистить";
			this->buttonClearF1->UseVisualStyleBackColor = true;
			this->buttonClearF1->Click += gcnew System::EventHandler(this, &FaForm::buttonClearF1_Click);
			// 
			// buttonClearF2
			// 
			this->buttonClearF2->Location = System::Drawing::Point(370, 324);
			this->buttonClearF2->Name = L"buttonClearF2";
			this->buttonClearF2->Size = System::Drawing::Size(75, 23);
			this->buttonClearF2->TabIndex = 5;
			this->buttonClearF2->Text = L"Очистить";
			this->buttonClearF2->UseVisualStyleBackColor = true;
			this->buttonClearF2->Click += gcnew System::EventHandler(this, &FaForm::buttonClearF2_Click);
			// 
			// buttonClearA
			// 
			this->buttonClearA->Location = System::Drawing::Point(647, 324);
			this->buttonClearA->Name = L"buttonClearA";
			this->buttonClearA->Size = System::Drawing::Size(75, 23);
			this->buttonClearA->TabIndex = 6;
			this->buttonClearA->Text = L"Очистить";
			this->buttonClearA->UseVisualStyleBackColor = true;
			this->buttonClearA->Click += gcnew System::EventHandler(this, &FaForm::buttonClearA_Click);
			// 
			// checkBoxF1
			// 
			this->checkBoxF1->AutoSize = true;
			this->checkBoxF1->Location = System::Drawing::Point(90, 354);
			this->checkBoxF1->Name = L"checkBoxF1";
			this->checkBoxF1->Size = System::Drawing::Size(106, 17);
			this->checkBoxF1->TabIndex = 7;
			this->checkBoxF1->Text = L"Режим заливки";
			this->checkBoxF1->UseVisualStyleBackColor = true;
			this->checkBoxF1->CheckedChanged += gcnew System::EventHandler(this, &FaForm::checkBoxF1_CheckedChanged);
			// 
			// checkBoxF2
			// 
			this->checkBoxF2->AutoSize = true;
			this->checkBoxF2->Location = System::Drawing::Point(370, 354);
			this->checkBoxF2->Name = L"checkBoxF2";
			this->checkBoxF2->Size = System::Drawing::Size(106, 17);
			this->checkBoxF2->TabIndex = 8;
			this->checkBoxF2->Text = L"Режим заливки";
			this->checkBoxF2->UseVisualStyleBackColor = true;
			this->checkBoxF2->CheckedChanged += gcnew System::EventHandler(this, &FaForm::checkBoxF2_CheckedChanged);
			// 
			// checkBoxDelay1
			// 
			this->checkBoxDelay1->AutoSize = true;
			this->checkBoxDelay1->Enabled = false;
			this->checkBoxDelay1->Location = System::Drawing::Point(90, 377);
			this->checkBoxDelay1->Name = L"checkBoxDelay1";
			this->checkBoxDelay1->Size = System::Drawing::Size(77, 17);
			this->checkBoxDelay1->TabIndex = 9;
			this->checkBoxDelay1->Text = L"Задержка";
			this->checkBoxDelay1->UseVisualStyleBackColor = true;
			// 
			// checkBoxDelay2
			// 
			this->checkBoxDelay2->AutoSize = true;
			this->checkBoxDelay2->Enabled = false;
			this->checkBoxDelay2->Location = System::Drawing::Point(370, 377);
			this->checkBoxDelay2->Name = L"checkBoxDelay2";
			this->checkBoxDelay2->Size = System::Drawing::Size(77, 17);
			this->checkBoxDelay2->TabIndex = 10;
			this->checkBoxDelay2->Text = L"Задержка";
			this->checkBoxDelay2->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(615, 354);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(140, 23);
			this->button1->TabIndex = 14;
			this->button1->Text = L"Сгенерировать отрезки";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &FaForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(80, 51);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(112, 13);
			this->label1->TabIndex = 15;
			this->label1->Text = L"Построчная заливка";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(350, 51);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(97, 13);
			this->label2->TabIndex = 16;
			this->label2->Text = L"Обычная заливка";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(644, 51);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(61, 13);
			this->label3->TabIndex = 17;
			this->label3->Text = L"Отсечение";
			// 
			// FaForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(814, 402);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->checkBoxDelay2);
			this->Controls->Add(this->checkBoxDelay1);
			this->Controls->Add(this->checkBoxF2);
			this->Controls->Add(this->checkBoxF1);
			this->Controls->Add(this->buttonClearA);
			this->Controls->Add(this->buttonClearF2);
			this->Controls->Add(this->buttonClearF1);
			this->Controls->Add(this->pictureBoxA);
			this->Controls->Add(this->pictureBoxF2);
			this->Controls->Add(this->pictureBoxF1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"FaForm";
			this->Text = L"Заливки и отсечение";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxF1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxF2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxA))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void buttonClearF1_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxF1);
	delete startF1;
	startF1 = nullptr;
	delete currentF1;
	currentF1 = nullptr;
}
private: System::Void buttonClearF2_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxF2);
	delete startF2;
	startF2 = nullptr;
	delete currentF2;
	currentF2 = nullptr;
}
private: System::Void buttonClearA_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxA);
	delete startA;
	startA = nullptr;
	delete endA;
	endA = nullptr;
}

private: System::Void pictureBoxF1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (checkBoxF1->Checked) {
		stringFilling(pictureBoxF1, bitmapF1, e->X, e->Y, 
			colorDialogFilling->Color, colorDialogFg->Color, checkBoxDelay1->Checked ? 15 : 0);
	}
	else {
		Graphics^ graphics = Graphics::FromImage(pictureBoxF1->Image); // creating graphics
		try {
			int error = 20; // error distance
			// if it is the first point
			if (!startF1) {
				startF1 = gcnew Point(e->X, e->Y);
				bitmapF1->SetPixel(e->X, e->Y, colorDialogFg->Color);
			}
			else {
				// if the current point matches (or near) the start point
				if (abs(startF1->X - e->X) < error && abs(startF1->Y - e->Y) < error) {
					// if polygon has more than 2 lines, end it
					if (currentF1) {
						graphics->DrawLine(pen, currentF1->X, currentF1->Y, startF1->X, startF1->Y);
						currentF1 = nullptr;
						startF1 = nullptr;
					}
				}
				else {
					if (currentF1) {
						graphics->DrawLine(pen, currentF1->X, currentF1->Y, e->X, e->Y); // just draw a line
						currentF1 = nullptr;
					}
					else {
						graphics->DrawLine(pen, startF1->X, startF1->Y, e->X, e->Y); // just draw a line
					}
					currentF1 = gcnew Point(e->X, e->Y);
				}
			}
		}
		finally {
			if (graphics) {
				delete graphics;
			}
		}
		pictureBoxF1->Refresh();
	}
}
private: System::Void pictureBoxF2_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (checkBoxF2->Checked) {
		simpleFilling(pictureBoxF2, bitmapF2, e->X, e->Y, 
			colorDialogFilling->Color, colorDialogFg->Color, checkBoxDelay2->Checked);
	}
	else {
		Graphics^ graphics = Graphics::FromImage(pictureBoxF2->Image); // creating graphics
		try {
			int error = 20; // error distance
			// if it is the first point
			if (!startF2) {
				startF2 = gcnew Point(e->X, e->Y);
				bitmapF2->SetPixel(e->X, e->Y, colorDialogFg->Color);
			}
			else {
				// if the current point matches (or near) the start point
				if (abs(startF2->X - e->X) < error && abs(startF2->Y - e->Y) < error) {
					// if polygon has more than 2 lines, end it
					if (currentF2) {
						graphics->DrawLine(pen, currentF2->X, currentF2->Y, startF2->X, startF2->Y);
						currentF2 = nullptr;
						startF2 = nullptr;
					}
				}
				else {
					if (currentF2) {
						graphics->DrawLine(pen, currentF2->X, currentF2->Y, e->X, e->Y); // just draw a line
						currentF2 = nullptr;
					}
					else {
						graphics->DrawLine(pen, startF2->X, startF2->Y, e->X, e->Y); // just draw a line
					}
					currentF2 = gcnew Point(e->X, e->Y);
				}
			}
		}
		finally {
			if (graphics) {
				delete graphics;
			}
		}
		pictureBoxF2->Refresh();
	}
}
private: System::Void checkBoxF1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	checkBoxDelay1->Enabled = checkBoxF1->Checked;
	pictureBoxF1->Cursor = checkBoxF1->Checked ? Cursors::Hand : Cursors::Default;
}
private: System::Void checkBoxF2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	checkBoxDelay2->Enabled = checkBoxF2->Checked;
	pictureBoxF2->Cursor = checkBoxF2->Checked ? Cursors::Hand : Cursors::Default;
}
private: System::Void цветФонаToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogBg->Color;
	colorDialogBg->ShowDialog();
	if (colorDialogBg->Color.ToArgb() == colorDialogFg->Color.ToArgb() ||
		colorDialogBg->Color.ToArgb() == colorDialogFilling->Color.ToArgb()) {
		MessageBox::Show(this, "Одинаковые цвета фона/заливки/границ (любые 2 из 3) недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogBg->Color = *old;
	}
	else {
		clearAll();
		delete old;
	}
}
private: System::Void цветПераИГраницToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogFg->Color;
	colorDialogFg->ShowDialog();
	if (colorDialogFg->Color.ToArgb() == colorDialogBg->Color.ToArgb() ||
		colorDialogFg->Color.ToArgb() == colorDialogFilling->Color.ToArgb()) {
		MessageBox::Show(this, "Одинаковые цвета фона/заливки/границ (любые 2 из 3) недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogFg->Color = *old;
	}
	else {
		clearAll();
		pen = gcnew Pen(colorDialogFg->Color);
		delete old;
	}
}
private: System::Void цветЗаливкиToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogFilling->Color;
	colorDialogFilling->ShowDialog();
	if (colorDialogFilling->Color.ToArgb() == colorDialogBg->Color.ToArgb() ||
		colorDialogFilling->Color.ToArgb() == colorDialogFg->Color.ToArgb()) {
		MessageBox::Show(this, "Одинаковые цвета фона/заливки/границ (любые 2 из 3) недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogFilling->Color = *old;
	}
	else {
		clearAll();
		delete old;
	}
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxA);
	if (!(startA && endA)) {
		MessageBox::Show(this, "Сначала задайте рамки отсечения!",
			"Ошибка", MessageBoxButtons::OK);
	}
	else {
		Graphics^ graphics = Graphics::FromImage(pictureBoxA->Image);
		try {
			graphics->DrawRectangle(pen, startA->X, startA->Y, endA->X - startA->X, endA->Y - startA->Y);
			for (int i = 0; i < 100; ++i) {
				Point^ start = gcnew Point(rand() % pictureBoxA->Width, rand() % pictureBoxA->Height);
				Point^ end = gcnew Point(rand() % pictureBoxA->Width, rand() % pictureBoxA->Height);
				if (amputation(startA->X, startA->Y, endA->X, endA->Y, start, end)) {
					graphics->DrawLine(pen, *start, *end);
				}
			}
		}
		finally {
			if (graphics) {
				delete graphics;
			}
		}
		pictureBoxA->Refresh();
	}
}
private: System::Void pictureBoxA_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	x = e->X;
	y = e->Y;
}
private: System::Void pictureBoxA_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (x == e->X || y == e->Y) {
			return;
		}
		Graphics^ graphics = Graphics::FromImage(bitmapA);
		try {
			graphics->Clear(colorDialogBg->Color);

			int width = abs(x - e->X);
			int height = abs(y - e->Y);
			int xx, yy;

			if (x > e->X) {
				xx = e->X;
			}
			else {
				xx = x;
			}

			if (y > e->Y) {
				yy = e->Y;
			}
			else {
				yy = y;
			}
			if (startA) {
				delete startA;
				startA = nullptr;
			}
			if (endA) {
				delete endA;
				endA = nullptr;
			}
			startA = gcnew Point(xx, yy);
			endA = gcnew Point(xx + width, yy + height);
			graphics->DrawRectangle(pen, xx, yy, width, height);
		}
		finally {
			if (graphics)
				delete graphics;
		}
		pictureBoxA->Refresh();
	}
}
private: System::Void оПрограммеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show(this, "Программа предназначена для демонстрации алгоритмов заливки (реализованы построчная и обычная заливки) и отсечения.\n\n" +
		"1) Для рисования фигуры для заливки кликните по области для рисования левой кнопкой мыши для того, " +
		"чтобы нарисовать точку. Далее, кликами левой кнопкой мыши нарисуйте фигуру для заливки "+
		"(с помощью замкнутой ломаной можно изобразить многоугольник.) После этого переключитесь в режим заливки "+
		"и нажмите на область, которую Вы хотите закрасить.\n\n" +
		"2) Для визуализации алгоритмов заливки поставьте галочку \"Задержка\" в режиме заливки.\n\n" +
		"3) Для запуска алгоритма отсечения определите область для отсечения, нажав в области рисования левую кнопку мыши, " +
		"и, не отпуская мышь, нарисуйте прямоугольник нужного размера. После этого Вы можете наблюдать за отсеченным отрезками, нажимая кнопку " +
		"\"Сгенерировать отрезки\" (они рисуются на всю область, но сразу же отсекаются).\n\n" +
		"4) Для очистки областей для рисования Вы можете воспользоваться соответствующими кнопками рядом с ними.\n\n" +
		"5) Также в программе можно менять цвет фона окон для рисования, цвет пера/границ и цвет заливки. Для этого следует зайти в меню \"Настройки\"\n\n"
		"Автор: Осипов Лев Игоревич, 4-й курс, группа БПИ121\n" +
		"Среда разработки: Visual Studio 2013\n" +
		"Дата: 30.09.2015", "О программе", MessageBoxButtons::OK);
}
};
}
