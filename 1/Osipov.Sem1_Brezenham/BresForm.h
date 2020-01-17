#pragma once
#include <cmath>

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 1. Алгоритмы Брезенхэма
Среда разработки: Visual Studio 2013
Дата: 23.09.2015
Реализованы алгоритмы построения отрезка, окружности и эллипса как по Брезенхэму, так и стандартными средствами.
Подробнее см. в меню "О программе".
*/

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for BresForm
	/// </summary>
	public ref class BresForm : public System::Windows::Forms::Form
	{
	public:
		BresForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			x = y = 0;
			bp1 = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
			pictureBox1->Image = bp1;
			bp2 = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
			pictureBox2->Image = bp2;
			bp3 = gcnew Bitmap(pictureBox3->Width, pictureBox3->Height);
			pictureBox3->Image = bp3;
			bp4 = gcnew Bitmap(pictureBox4->Width, pictureBox4->Height);
			pictureBox4->Image = bp4;
			bp5 = gcnew Bitmap(pictureBox5->Width, pictureBox5->Height);
			pictureBox5->Image = bp5;
			bp6 = gcnew Bitmap(pictureBox6->Width, pictureBox6->Height);
			pictureBox6->Image = bp6;
			colorDialog1->Color = Color::White; // background color
			colorDialog2->Color = Color::Blue; // foreground color
			pen = gcnew Pen(Color::Blue);
			brush = gcnew SolidBrush(Color::Blue);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~BresForm()
		{
			if (components)
			{
				delete components;
			}
			if (bp1) {
				delete bp1;
			}
			if (bp2) {
				delete bp2;
			}
			if (bp3) {
				delete bp3;
			}
			if (bp4) {
				delete bp4;
			}
			if (bp5) {
				delete bp5;
			}
			if (bp6) {
				delete bp6;
			}
			if (pen) {
				delete pen;
			}
			if (brush) {
				delete brush;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  оПрограммеToolStripMenuItem;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		/// <summary>
		/// Bitmaps to draw in.
		/// </summary>
		Bitmap^ bp1;
		Bitmap^ bp2;
		Bitmap^ bp3;
		Bitmap^ bp4;
		Bitmap^ bp5;
		Bitmap^ bp6;

		/// <summary>
		/// Pen to draw.
		/// </summary>
		Pen^ pen;

		/// <summary>
		/// Brush to draw.
		/// </summary>
		Brush^ brush;

		/// <summary>
		/// Current pressed points
		/// </summary>
		int x;
		int y;


	private: System::Windows::Forms::ToolStripMenuItem^  настройкиToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  цветФонаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  цветПераToolStripMenuItem;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::ColorDialog^  colorDialog2;


		/// <summary>
		/// Draws a point.
		/// </summary>
		void drawPoint(int x, int y, Graphics^ graphics);

		/// <summary>
		/// Draws 4 points for Bres circles and ellipses.
		/// </summary>
		void quadroDraw(int x, int y, int x1, int y1, Graphics^ graphics);

		/// <summary>
		/// Clears picture box.
		/// </summary>
		void clearPictureBox(PictureBox^ pb);

		/// <summary>
		/// Clears all picture boxes.
		/// </summary>
		void clearAll();

		/// <summary>
		/// Draws a segment with Bres algorithm 
		/// </summary>
		void bresSegment(int x1, int y1, int x2, int y2, Graphics^ graphics);

		/// <summary>
		/// Draws a circle with Bres algorithm 
		/// </summary>
		void bresCircle(int x1, int y1, int r, Graphics^ graphics);

		/// <summary>
		/// Draws an ellipse with Bres algorithm 
		/// </summary>
		void bresEllipse(int x1, int y1, int width, int height, Graphics^ graphics);

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->настройкиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветФонаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветПераToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->colorDialog2 = (gcnew System::Windows::Forms::ColorDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->Location = System::Drawing::Point(24, 55);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(201, 188);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BresForm::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &BresForm::pictureBox1_MouseMove);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::White;
			this->pictureBox2->Location = System::Drawing::Point(264, 55);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(198, 188);
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BresForm::pictureBox2_MouseDown);
			this->pictureBox2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &BresForm::pictureBox2_MouseMove);
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::White;
			this->pictureBox3->Location = System::Drawing::Point(500, 55);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(193, 188);
			this->pictureBox3->TabIndex = 2;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BresForm::pictureBox3_MouseDown);
			this->pictureBox3->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &BresForm::pictureBox3_MouseMove);
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::Color::White;
			this->pictureBox4->Location = System::Drawing::Point(24, 272);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(201, 188);
			this->pictureBox4->TabIndex = 3;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BresForm::pictureBox4_MouseDown);
			this->pictureBox4->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &BresForm::pictureBox4_MouseMove);
			// 
			// pictureBox5
			// 
			this->pictureBox5->BackColor = System::Drawing::Color::White;
			this->pictureBox5->Location = System::Drawing::Point(264, 275);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(198, 185);
			this->pictureBox5->TabIndex = 4;
			this->pictureBox5->TabStop = false;
			this->pictureBox5->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BresForm::pictureBox5_MouseDown);
			this->pictureBox5->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &BresForm::pictureBox5_MouseMove);
			// 
			// pictureBox6
			// 
			this->pictureBox6->BackColor = System::Drawing::Color::White;
			this->pictureBox6->Location = System::Drawing::Point(500, 272);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(193, 188);
			this->pictureBox6->TabIndex = 5;
			this->pictureBox6->TabStop = false;
			this->pictureBox6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &BresForm::pictureBox6_MouseDown);
			this->pictureBox6->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &BresForm::pictureBox6_MouseMove);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->оПрограммеToolStripMenuItem,
					this->настройкиToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(705, 24);
			this->menuStrip1->TabIndex = 6;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(94, 20);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
			this->оПрограммеToolStripMenuItem->Click += gcnew System::EventHandler(this, &BresForm::оПрограммеToolStripMenuItem_Click);
			// 
			// настройкиToolStripMenuItem
			// 
			this->настройкиToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->цветФонаToolStripMenuItem,
					this->цветПераToolStripMenuItem
			});
			this->настройкиToolStripMenuItem->Name = L"настройкиToolStripMenuItem";
			this->настройкиToolStripMenuItem->Size = System::Drawing::Size(79, 20);
			this->настройкиToolStripMenuItem->Text = L"Настройки";
			// 
			// цветФонаToolStripMenuItem
			// 
			this->цветФонаToolStripMenuItem->Name = L"цветФонаToolStripMenuItem";
			this->цветФонаToolStripMenuItem->Size = System::Drawing::Size(132, 22);
			this->цветФонаToolStripMenuItem->Text = L"Цвет фона";
			this->цветФонаToolStripMenuItem->Click += gcnew System::EventHandler(this, &BresForm::цветФонаToolStripMenuItem_Click);
			// 
			// цветПераToolStripMenuItem
			// 
			this->цветПераToolStripMenuItem->Name = L"цветПераToolStripMenuItem";
			this->цветПераToolStripMenuItem->Size = System::Drawing::Size(132, 22);
			this->цветПераToolStripMenuItem->Text = L"Цвет пера";
			this->цветПераToolStripMenuItem->Click += gcnew System::EventHandler(this, &BresForm::цветПераToolStripMenuItem_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(65, 39);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(115, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Отрезок (Брезенхэм)";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(295, 39);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(134, 13);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Окружность (Брезенхэм)";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(542, 39);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(109, 13);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Эллипс (Брезенхэм)";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(76, 256);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(93, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Отрезок (Default)";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(306, 256);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(112, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Окружность (Default)";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(551, 256);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(87, 13);
			this->label6->TabIndex = 12;
			this->label6->Text = L"Эллипс (Default)";
			// 
			// BresForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(705, 475);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"BresForm";
			this->Text = L"Алгоритмы Брезенхэма";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void оПрограммеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show(this, "Алгоритмы Брезенхэма.\n" +
		"Программа предназначена для рисования отрезков, окружностей и эллипсов " +
		"по алгоритмам Брезенхэма, а также с помощью стандартных средств (Default).\n" +
		"Для репрезентативности для каждой фигуры было уделено свое окно.\n" +
		"Для создания фигуры следует нажать в окне рисования левой клавишей мыши и, двигая мышью," +
		"начертить фигуру нужного размера.\n" +
		"Особое внимание было уделено рисованию окружностей и эллипсов в динамике.\n" +
		"Также в программе можно менять цвет фона окон для рисования и цвет пера. Для этого следует зайти в меню \"Настройки\"\n" +
		"Автор: Осипов Лев Игоревич, 4-й курс, группа БПИ121\n" +
		"Среда разработки: Visual Studio 2013\n" +
		"Дата: 23.09.2015", "О программе", MessageBoxButtons::OK);
}
private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	x = e->X;
	y = e->Y;
}
private: System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (x == e->X && y == e->Y) {
			return;
		}
		Graphics^ graphics = Graphics::FromImage(bp1); // creating graphics
		try {
			graphics->Clear(colorDialog1->Color); // clearing

			bresSegment(x, y, e->X, e->Y, graphics); // drawing a Bres segment
		}
		finally {
			if (graphics)
				delete graphics; // cleaning memory
		}
		pictureBox1->Refresh();
	}
}
private: System::Void pictureBox2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	x = e->X;
	y = e->Y;
}
private: System::Void pictureBox2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (x == e->X || y == e->Y) {
			return;
		}
		Graphics^ graphics = Graphics::FromImage(bp2); // creating graphics
		try {
			graphics->Clear(colorDialog1->Color); // clearing

			/** Processing center and radius to make the drawing comfortable */
			int xx, yy, r;
			
			if (abs(x - e->X) > abs(y - e->Y)) {
				r = abs(y - e->Y) / 2;
			}
			else {
				r = abs(x - e->X) / 2;
			}

			if (r == 0) {
				return;
			}
			
			int offsetX = abs(x - e->X) / 2 < r ? abs(x - e->X) / 2 : r;
			if (x > e->X) {
				xx = x - offsetX;
			}
			else {
				xx = x + offsetX;
			}
			
			int offsetY = abs(y - e->Y) / 2 < r ? abs(y - e->Y) / 2 : r;
			if (y > e->Y) {
				yy = y - offsetY;
			}
			else {
				yy = y + offsetY;
			}
			

			bresCircle(xx, yy, r, graphics); // drawing a Bres circle
		}
		finally {
			if (graphics)
				delete graphics; // cleaning memory
		}
		pictureBox2->Refresh();
	}
}
private: System::Void pictureBox3_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	x = e->X;
	y = e->Y;
}
private: System::Void pictureBox3_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (x == e->X || y == e->Y) {
			return;
		}
		Graphics^ graphics = Graphics::FromImage(bp3); // creating graphics
		try {
			graphics->Clear(colorDialog1->Color); // clearing

			/** Processing center, width and height to make the drawing comfortable */
			int width = abs(x - e->X) / 2;
			int height = abs(y - e->Y) / 2;
			if (width == 0 || height == 0) {
				return;
			}
			int xx, yy;

			if (x > e->X) {
				xx = e->X + abs(x - e->X) / 2;
			}
			else {
				xx = x + abs(x - e->X) / 2;
			}

			if (y > e->Y) {
				yy = e->Y + abs(y - e->Y) / 2;
			}
			else {
				yy = y + abs(y - e->Y) / 2;
			}


			bresEllipse(xx, yy, width, height, graphics); // drawing a Bres ellipse
		}
		finally {
			if (graphics)
				delete graphics; // cleaning memory
		}
		pictureBox3->Refresh();
	}
}
private: System::Void pictureBox4_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	x = e->X;
	y = e->Y;
}
private: System::Void pictureBox4_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (x == e->X && y == e->Y) {
			return;
		}
		Graphics^ graphics = Graphics::FromImage(bp4); // creating graphics
		try {
			graphics->Clear(colorDialog1->Color); // clearing

			graphics->DrawLine(pen, x, y, e->X, e->Y); // drawing a simple line
		}
		finally {
			if (graphics)
				delete graphics; // cleaning memory
		}
		pictureBox4->Refresh();
	}
}
private: System::Void pictureBox5_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	x = e->X;
	y = e->Y;
}
private: System::Void pictureBox5_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (x == e->X || y == e->Y) {
			return;
		}
		Graphics^ graphics = Graphics::FromImage(bp5); // creating graphics
		try {
			graphics->Clear(colorDialog1->Color); // clearing

			/** Processing center and radius to make the drawing comfortable */
			int xx, yy, r;

			bool xMore = false;
			if (abs(x - e->X) > abs(y - e->Y)) {
				r = abs(y - e->Y);
				xMore = true;
			}
			else {
				r = abs(x - e->X);
			}

			if (x > e->X) {
				xx = e->X;
				if (xMore) {
					xx = x - r;
				}
			}
			else {
				xx = x;
			}

			if (y > e->Y) {
				yy = e->Y;
				if (! xMore) {
					yy = y - r;
				}
			}
			else {
				yy = y;
			}

			graphics->DrawEllipse(pen, xx, yy, r, r); // drawing a simple circle
		}
		finally {
			if (graphics)
				delete graphics; // cleaning memory
		}
		pictureBox5->Refresh();
	}
}
private: System::Void pictureBox6_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	x = e->X;
	y = e->Y;
}
private: System::Void pictureBox6_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (x == e->X || y == e->Y) {
			return;
		}
		Graphics^ graphics = Graphics::FromImage(bp6); // creating graphics
		try {
			graphics->Clear(colorDialog1->Color); // clearing

			/** Processing center, width and height to make the drawing comfortable */
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

			graphics->DrawEllipse(pen, xx, yy, width, height); // drawing a simple ellipse
		}
		finally {
			if (graphics)
				delete graphics; // cleaning memory
		}
		pictureBox6->Refresh();
	}
}
private: System::Void цветФонаToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	colorDialog1->ShowDialog();
	clearAll();
}
private: System::Void цветПераToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	colorDialog2->ShowDialog();
	clearAll();
	pen = gcnew Pen(colorDialog2->Color);
	brush = gcnew SolidBrush(colorDialog2->Color);
}
};
}
