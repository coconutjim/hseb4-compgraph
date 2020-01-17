#pragma once

#include <algorithm>

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 3. Сплайны
Среда разработки: Visual Studio 2013
Дата: 13.10.2015
Реализованы кривые Безье и Б-сплайны.
Подробнее см. в меню "О программе".
*/

namespace Splines {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SplForm
	/// </summary>
	public ref class SplForm : public System::Windows::Forms::Form
	{
	public:
		SplForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			// Creating bitmaps
			bitmapT11 = gcnew Bitmap(pictureBoxT11->Width, pictureBoxT11->Height);
			pictureBoxT11->Image = bitmapT11;
			bitmapT12 = gcnew Bitmap(pictureBoxT12->Width, pictureBoxT12->Height);
			pictureBoxT12->Image = bitmapT12;
			bitmapT13 = gcnew Bitmap(pictureBoxT13->Width, pictureBoxT13->Height);
			pictureBoxT13->Image = bitmapT13;
			bitmapT14 = gcnew Bitmap(pictureBoxT14->Width, pictureBoxT14->Height);
			pictureBoxT14->Image = bitmapT14;
			bitmapT22 = gcnew Bitmap(pictureBoxT22->Width, pictureBoxT22->Height);
			pictureBoxT22->Image = bitmapT22;
			bitmapT23 = gcnew Bitmap(pictureBoxT23->Width, pictureBoxT23->Height);
			pictureBoxT23->Image = bitmapT23;
			bitmapT24 = gcnew Bitmap(pictureBoxT24->Width, pictureBoxT24->Height);
			pictureBoxT24->Image = bitmapT24;

			// Initializing colors
			colorDialogBg->Color = Color::White;
			colorDialogFg->Color = Color::Black;
			colorDialogSPC->Color = Color::Red;
			colorDialogSLC->Color = Color::Blue;
			pen = gcnew Pen(Color::Black);
			pen2 = gcnew Pen(Color::Blue);
			brush = gcnew SolidBrush(Color::Red);
			brush2 = gcnew SolidBrush(Color::Black);

			// Initializing lists
			listT11 = gcnew System::Collections::Generic::List < Point> ();
			listT12 = gcnew System::Collections::Generic::List < Point>();
			listT13 = gcnew System::Collections::Generic::List < Point>();
			listT14 = gcnew System::Collections::Generic::List < Point>();
			listT22 = gcnew System::Collections::Generic::List < Point>();
			listT23 = gcnew System::Collections::Generic::List < Point>();
			listT24 = gcnew System::Collections::Generic::List < Point>();

			// Initializing points
			pointIndexT11 = -1;
			pointIndexT12 = -1;
			pointIndexT13 = -1;
			pointIndexT14 = -1;
			pointIndexT22 = -1;
			pointIndexT23 = -1;
			pointIndexT24 = -1;

			curveT14Closed = false;
			curveT24Closed = false;

			t = 0.01;
			error = 5;
			radius = 2;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SplForm()
		{
			if (components)
			{
				delete components;
			}

			if (pen) {
				delete pen;
			}

			if (pen2) {
				delete pen2;
			}

			if (brush) {
				delete brush;
			}

			if (bitmapT11) {
				delete bitmapT11;
			}

			if (bitmapT12) {
				delete bitmapT12;
			}

			if (bitmapT13) {
				delete bitmapT13;
			}

			if (bitmapT14) {
				delete bitmapT14;
			}

			if (bitmapT22) {
				delete bitmapT22;
			}

			if (bitmapT23) {
				delete bitmapT23;
			}

			if (bitmapT24) {
				delete bitmapT24;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBoxT11;
	protected:
	private: System::Windows::Forms::PictureBox^  pictureBoxT12;
	private: System::Windows::Forms::PictureBox^  pictureBoxT13;
	private: System::Windows::Forms::PictureBox^  pictureBoxT14;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ColorDialog^  colorDialogBg;
	private: System::Windows::Forms::ColorDialog^  colorDialogFg;


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  buttonT11Clear;
	private: System::Windows::Forms::Button^  buttonT12Clear;
	private: System::Windows::Forms::Button^  buttonT13Clear;
	private: System::Windows::Forms::Button^  buttonT14Clear;
	private: System::Windows::Forms::Button^  buttonT14Close;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		/// <summary>
		/// Error for pickiing point to move it.
		/// </summary>
		int error;

		/// <summary>
		/// Radius of support point.
		/// </summary>
		int radius;

		/// <summary>
		/// Step of algorithm.
		/// </summary>
		double t;

		/// <summary>
		/// Pen to draw common lines.
		/// </summary>
		Pen^ pen;

		/// <summary>
		/// Pen to draw demonstrative lines.
		/// </summary>
		Pen^ pen2;

		/// <summary>
		/// Brush to fill.
		/// </summary>
		Brush^ brush;

		/// <summary>
		/// Brush for splines.
		/// </summary>
		Brush^ brush2;

		/// <summary>
		/// Lists for holding points.
		/// </summary>
		System::Collections::Generic::List < Point > ^ listT11;
		System::Collections::Generic::List < Point > ^ listT12;
		System::Collections::Generic::List < Point > ^ listT13;
		System::Collections::Generic::List < Point > ^ listT14;
		System::Collections::Generic::List < Point > ^ listT22;
		System::Collections::Generic::List < Point > ^ listT23;
		System::Collections::Generic::List < Point > ^ listT24;

		/// <summary>
		/// Indices to remember moving point.
		/// </summary>
		int pointIndexT11;
		int pointIndexT12;
		int pointIndexT13;
		int pointIndexT14;
		int pointIndexT22;
		int pointIndexT23;
		int pointIndexT24;

		/// <summary>
		/// If the curve is closed.
		/// </summary>
		bool curveT14Closed;
		bool curveT24Closed;

		/// <summary>
		/// Bitmap to draw in.
		/// </summary>
		Bitmap^ bitmapT11;
		Bitmap^ bitmapT12;
		Bitmap^ bitmapT13;
	private: System::Windows::Forms::ToolStripMenuItem^  оПрограммеToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  настройкиToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  цветФонаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  цветПераToolStripMenuItem;
private: System::Windows::Forms::ColorDialog^  colorDialogSPC;
private: System::Windows::Forms::ToolStripMenuItem^  цветОпорныхТочекToolStripMenuItem;
private: System::Windows::Forms::ColorDialog^  colorDialogSLC;
private: System::Windows::Forms::ToolStripMenuItem^  цветПоказательнойЛинииToolStripMenuItem;
private: System::Windows::Forms::PictureBox^  pictureBoxT22;
private: System::Windows::Forms::Button^  buttonT22Clear;
private: System::Windows::Forms::PictureBox^  pictureBoxT23;

private: System::Windows::Forms::PictureBox^  pictureBoxT24;
private: System::Windows::Forms::Button^  buttonT24Clear;
private: System::Windows::Forms::Button^  buttonT24Close;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::Label^  label9;
		 Bitmap^ bitmapT14;
		 Bitmap^ bitmapT22;
		 Bitmap^ bitmapT23;
private: System::Windows::Forms::Button^  buttonT23Clear;


		 Bitmap^ bitmapT24;


		/// <summary>
		/// Clears picture box.
		/// </summary>
		void clearPictureBox(PictureBox^ pb);

		/// <summary>
		/// Clears all picture boxes.
		/// </summary>
		void clearAll();

		/// <summary>
		/// Calculates the binomial coefficient (to make the formula simple).
		/// </summary>
		int SplForm::binCoeff(int n, int k);

		/// <summary>
		/// Correct a point to put it on the line
		/// </summary>
		Point pointCorrection(Point current, Point previous, Point prePreviuos);
		
		/// <summary>
		/// Draw all simple cubic curves from the list.
		/// </summary>
		void drawAllSimpleCurves(PictureBox^ pb, System::Collections::Generic::List<Point>^ list);
		
		/// <summary>
		/// Draw simple curve based on any amount of points.
		/// </summary>
		void drawSimpleCurve(PictureBox^ pb, System::Collections::Generic::List<Point>^ list, int from, int to);
		
		/// <summary>
		/// Draw all B-spline curves from the list.
		/// </summary>
		void drawAllBSplines(PictureBox^ pb, System::Collections::Generic::List<Point>^ list, bool closed);

		/// <summary>
		/// Draw one B-spline curve.
		/// </summary>
		void drawBSpline(Graphics^ graphics, Point p0, Point p1, Point p2, Point p3);


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBoxT11 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxT12 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxT13 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxT14 = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->настройкиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветФонаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветПераToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветОпорныхТочекToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветПоказательнойЛинииToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->colorDialogBg = (gcnew System::Windows::Forms::ColorDialog());
			this->colorDialogFg = (gcnew System::Windows::Forms::ColorDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->buttonT11Clear = (gcnew System::Windows::Forms::Button());
			this->buttonT12Clear = (gcnew System::Windows::Forms::Button());
			this->buttonT13Clear = (gcnew System::Windows::Forms::Button());
			this->buttonT14Clear = (gcnew System::Windows::Forms::Button());
			this->buttonT14Close = (gcnew System::Windows::Forms::Button());
			this->colorDialogSPC = (gcnew System::Windows::Forms::ColorDialog());
			this->colorDialogSLC = (gcnew System::Windows::Forms::ColorDialog());
			this->pictureBoxT22 = (gcnew System::Windows::Forms::PictureBox());
			this->buttonT22Clear = (gcnew System::Windows::Forms::Button());
			this->pictureBoxT23 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxT24 = (gcnew System::Windows::Forms::PictureBox());
			this->buttonT24Clear = (gcnew System::Windows::Forms::Button());
			this->buttonT24Close = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->buttonT23Clear = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT14))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT22))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT23))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT24))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBoxT11
			// 
			this->pictureBoxT11->BackColor = System::Drawing::Color::White;
			this->pictureBoxT11->Location = System::Drawing::Point(12, 84);
			this->pictureBoxT11->Name = L"pictureBoxT11";
			this->pictureBoxT11->Size = System::Drawing::Size(222, 222);
			this->pictureBoxT11->TabIndex = 0;
			this->pictureBoxT11->TabStop = false;
			this->pictureBoxT11->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT11_MouseDown);
			this->pictureBoxT11->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT11_MouseMove);
			this->pictureBoxT11->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT11_MouseUp);
			// 
			// pictureBoxT12
			// 
			this->pictureBoxT12->BackColor = System::Drawing::Color::White;
			this->pictureBoxT12->Location = System::Drawing::Point(256, 84);
			this->pictureBoxT12->Name = L"pictureBoxT12";
			this->pictureBoxT12->Size = System::Drawing::Size(222, 222);
			this->pictureBoxT12->TabIndex = 1;
			this->pictureBoxT12->TabStop = false;
			this->pictureBoxT12->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT12_MouseDown);
			this->pictureBoxT12->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT12_MouseMove);
			this->pictureBoxT12->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT12_MouseUp);
			// 
			// pictureBoxT13
			// 
			this->pictureBoxT13->BackColor = System::Drawing::Color::White;
			this->pictureBoxT13->Location = System::Drawing::Point(502, 84);
			this->pictureBoxT13->Name = L"pictureBoxT13";
			this->pictureBoxT13->Size = System::Drawing::Size(222, 222);
			this->pictureBoxT13->TabIndex = 2;
			this->pictureBoxT13->TabStop = false;
			this->pictureBoxT13->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT13_MouseDown);
			this->pictureBoxT13->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT13_MouseMove);
			this->pictureBoxT13->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT13_MouseUp);
			// 
			// pictureBoxT14
			// 
			this->pictureBoxT14->BackColor = System::Drawing::Color::White;
			this->pictureBoxT14->Location = System::Drawing::Point(747, 82);
			this->pictureBoxT14->Name = L"pictureBoxT14";
			this->pictureBoxT14->Size = System::Drawing::Size(222, 222);
			this->pictureBoxT14->TabIndex = 3;
			this->pictureBoxT14->TabStop = false;
			this->pictureBoxT14->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT14_MouseDown);
			this->pictureBoxT14->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT14_MouseMove);
			this->pictureBoxT14->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT14_MouseUp);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->оПрограммеToolStripMenuItem,
					this->настройкиToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(981, 24);
			this->menuStrip1->TabIndex = 4;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(94, 20);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
			this->оПрограммеToolStripMenuItem->Click += gcnew System::EventHandler(this, &SplForm::оПрограммеToolStripMenuItem_Click);
			// 
			// настройкиToolStripMenuItem
			// 
			this->настройкиToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->цветФонаToolStripMenuItem,
					this->цветПераToolStripMenuItem, this->цветОпорныхТочекToolStripMenuItem, this->цветПоказательнойЛинииToolStripMenuItem
			});
			this->настройкиToolStripMenuItem->Name = L"настройкиToolStripMenuItem";
			this->настройкиToolStripMenuItem->Size = System::Drawing::Size(79, 20);
			this->настройкиToolStripMenuItem->Text = L"Настройки";
			// 
			// цветФонаToolStripMenuItem
			// 
			this->цветФонаToolStripMenuItem->Name = L"цветФонаToolStripMenuItem";
			this->цветФонаToolStripMenuItem->Size = System::Drawing::Size(223, 22);
			this->цветФонаToolStripMenuItem->Text = L"Цвет фона";
			this->цветФонаToolStripMenuItem->Click += gcnew System::EventHandler(this, &SplForm::цветФонаToolStripMenuItem_Click);
			// 
			// цветПераToolStripMenuItem
			// 
			this->цветПераToolStripMenuItem->Name = L"цветПераToolStripMenuItem";
			this->цветПераToolStripMenuItem->Size = System::Drawing::Size(223, 22);
			this->цветПераToolStripMenuItem->Text = L"Цвет пера";
			this->цветПераToolStripMenuItem->Click += gcnew System::EventHandler(this, &SplForm::цветПераToolStripMenuItem_Click);
			// 
			// цветОпорныхТочекToolStripMenuItem
			// 
			this->цветОпорныхТочекToolStripMenuItem->Name = L"цветОпорныхТочекToolStripMenuItem";
			this->цветОпорныхТочекToolStripMenuItem->Size = System::Drawing::Size(223, 22);
			this->цветОпорныхТочекToolStripMenuItem->Text = L"Цвет опорных точек";
			this->цветОпорныхТочекToolStripMenuItem->Click += gcnew System::EventHandler(this, &SplForm::цветОпорныхТочекToolStripMenuItem_Click);
			// 
			// цветПоказательнойЛинииToolStripMenuItem
			// 
			this->цветПоказательнойЛинииToolStripMenuItem->Name = L"цветПоказательнойЛинииToolStripMenuItem";
			this->цветПоказательнойЛинииToolStripMenuItem->Size = System::Drawing::Size(223, 22);
			this->цветПоказательнойЛинииToolStripMenuItem->Text = L"Цвет показательной линии";
			this->цветПоказательнойЛинииToolStripMenuItem->Click += gcnew System::EventHandler(this, &SplForm::цветПоказательнойЛинииToolStripMenuItem_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(417, 35);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(140, 24);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Кривые Безье";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(57, 66);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(128, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Произвольный порядок";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(334, 66);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(67, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"3-й порядок";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(582, 68);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(61, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Составная";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(805, 68);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(118, 13);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Составная замкнутая";
			// 
			// buttonT11Clear
			// 
			this->buttonT11Clear->Location = System::Drawing::Point(82, 312);
			this->buttonT11Clear->Name = L"buttonT11Clear";
			this->buttonT11Clear->Size = System::Drawing::Size(75, 23);
			this->buttonT11Clear->TabIndex = 11;
			this->buttonT11Clear->Text = L"Очистить";
			this->buttonT11Clear->UseVisualStyleBackColor = true;
			this->buttonT11Clear->Click += gcnew System::EventHandler(this, &SplForm::buttonT11Clear_Click);
			// 
			// buttonT12Clear
			// 
			this->buttonT12Clear->Location = System::Drawing::Point(330, 312);
			this->buttonT12Clear->Name = L"buttonT12Clear";
			this->buttonT12Clear->Size = System::Drawing::Size(75, 23);
			this->buttonT12Clear->TabIndex = 12;
			this->buttonT12Clear->Text = L"Очистить";
			this->buttonT12Clear->UseVisualStyleBackColor = true;
			this->buttonT12Clear->Click += gcnew System::EventHandler(this, &SplForm::buttonT12Clear_Click);
			// 
			// buttonT13Clear
			// 
			this->buttonT13Clear->Location = System::Drawing::Point(578, 312);
			this->buttonT13Clear->Name = L"buttonT13Clear";
			this->buttonT13Clear->Size = System::Drawing::Size(75, 23);
			this->buttonT13Clear->TabIndex = 13;
			this->buttonT13Clear->Text = L"Очистить";
			this->buttonT13Clear->UseVisualStyleBackColor = true;
			this->buttonT13Clear->Click += gcnew System::EventHandler(this, &SplForm::buttonT13Clear_Click);
			// 
			// buttonT14Clear
			// 
			this->buttonT14Clear->Location = System::Drawing::Point(779, 312);
			this->buttonT14Clear->Name = L"buttonT14Clear";
			this->buttonT14Clear->Size = System::Drawing::Size(75, 23);
			this->buttonT14Clear->TabIndex = 14;
			this->buttonT14Clear->Text = L"Очистить";
			this->buttonT14Clear->UseVisualStyleBackColor = true;
			this->buttonT14Clear->Click += gcnew System::EventHandler(this, &SplForm::buttonT14Clear_Click);
			// 
			// buttonT14Close
			// 
			this->buttonT14Close->Enabled = false;
			this->buttonT14Close->Location = System::Drawing::Point(860, 312);
			this->buttonT14Close->Name = L"buttonT14Close";
			this->buttonT14Close->Size = System::Drawing::Size(75, 23);
			this->buttonT14Close->TabIndex = 15;
			this->buttonT14Close->Text = L"Замкнуть";
			this->buttonT14Close->UseVisualStyleBackColor = true;
			this->buttonT14Close->Click += gcnew System::EventHandler(this, &SplForm::buttonT14Close_Click);
			// 
			// pictureBoxT22
			// 
			this->pictureBoxT22->BackColor = System::Drawing::Color::White;
			this->pictureBoxT22->Location = System::Drawing::Point(119, 396);
			this->pictureBoxT22->Name = L"pictureBoxT22";
			this->pictureBoxT22->Size = System::Drawing::Size(222, 222);
			this->pictureBoxT22->TabIndex = 16;
			this->pictureBoxT22->TabStop = false;
			this->pictureBoxT22->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT22_MouseDown);
			this->pictureBoxT22->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT22_MouseMove);
			this->pictureBoxT22->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT22_MouseUp);
			// 
			// buttonT22Clear
			// 
			this->buttonT22Clear->Location = System::Drawing::Point(198, 624);
			this->buttonT22Clear->Name = L"buttonT22Clear";
			this->buttonT22Clear->Size = System::Drawing::Size(75, 23);
			this->buttonT22Clear->TabIndex = 17;
			this->buttonT22Clear->Text = L"Очистить";
			this->buttonT22Clear->UseVisualStyleBackColor = true;
			this->buttonT22Clear->Click += gcnew System::EventHandler(this, &SplForm::buttonT22Clear_Click);
			// 
			// pictureBoxT23
			// 
			this->pictureBoxT23->BackColor = System::Drawing::Color::White;
			this->pictureBoxT23->Location = System::Drawing::Point(374, 396);
			this->pictureBoxT23->Name = L"pictureBoxT23";
			this->pictureBoxT23->Size = System::Drawing::Size(222, 222);
			this->pictureBoxT23->TabIndex = 18;
			this->pictureBoxT23->TabStop = false;
			this->pictureBoxT23->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT23_MouseDown);
			this->pictureBoxT23->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT23_MouseMove);
			this->pictureBoxT23->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT23_MouseUp);
			// 
			// pictureBoxT24
			// 
			this->pictureBoxT24->BackColor = System::Drawing::Color::White;
			this->pictureBoxT24->Location = System::Drawing::Point(627, 396);
			this->pictureBoxT24->Name = L"pictureBoxT24";
			this->pictureBoxT24->Size = System::Drawing::Size(222, 222);
			this->pictureBoxT24->TabIndex = 20;
			this->pictureBoxT24->TabStop = false;
			this->pictureBoxT24->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT24_MouseDown);
			this->pictureBoxT24->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT24_MouseMove);
			this->pictureBoxT24->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SplForm::pictureBoxT24_MouseUp);
			// 
			// buttonT24Clear
			// 
			this->buttonT24Clear->Location = System::Drawing::Point(661, 624);
			this->buttonT24Clear->Name = L"buttonT24Clear";
			this->buttonT24Clear->Size = System::Drawing::Size(75, 23);
			this->buttonT24Clear->TabIndex = 21;
			this->buttonT24Clear->Text = L"Очистить";
			this->buttonT24Clear->UseVisualStyleBackColor = true;
			this->buttonT24Clear->Click += gcnew System::EventHandler(this, &SplForm::buttonT24Clear_Click);
			// 
			// buttonT24Close
			// 
			this->buttonT24Close->Enabled = false;
			this->buttonT24Close->Location = System::Drawing::Point(743, 624);
			this->buttonT24Close->Name = L"buttonT24Close";
			this->buttonT24Close->Size = System::Drawing::Size(75, 23);
			this->buttonT24Close->TabIndex = 22;
			this->buttonT24Close->Text = L"Замкнуть";
			this->buttonT24Close->UseVisualStyleBackColor = true;
			this->buttonT24Close->Click += gcnew System::EventHandler(this, &SplForm::buttonT24Close_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(388, 351);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(209, 24);
			this->label6->TabIndex = 23;
			this->label6->Text = L"Б-сплайновые кривые";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(200, 378);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(73, 13);
			this->label7->TabIndex = 24;
			this->label7->Text = L"3-ий порядок";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(459, 379);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(61, 13);
			this->label8->TabIndex = 25;
			this->label8->Text = L"Составная";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(679, 380);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(118, 13);
			this->label9->TabIndex = 26;
			this->label9->Text = L"Составная замкнутая";
			// 
			// buttonT23Clear
			// 
			this->buttonT23Clear->Location = System::Drawing::Point(445, 624);
			this->buttonT23Clear->Name = L"buttonT23Clear";
			this->buttonT23Clear->Size = System::Drawing::Size(75, 23);
			this->buttonT23Clear->TabIndex = 27;
			this->buttonT23Clear->Text = L"Очистить";
			this->buttonT23Clear->UseVisualStyleBackColor = true;
			this->buttonT23Clear->Click += gcnew System::EventHandler(this, &SplForm::buttonT23Clear_Click);
			// 
			// SplForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(981, 659);
			this->Controls->Add(this->buttonT23Clear);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->buttonT24Close);
			this->Controls->Add(this->buttonT24Clear);
			this->Controls->Add(this->pictureBoxT24);
			this->Controls->Add(this->pictureBoxT23);
			this->Controls->Add(this->buttonT22Clear);
			this->Controls->Add(this->pictureBoxT22);
			this->Controls->Add(this->buttonT14Close);
			this->Controls->Add(this->buttonT14Clear);
			this->Controls->Add(this->buttonT13Clear);
			this->Controls->Add(this->buttonT12Clear);
			this->Controls->Add(this->buttonT11Clear);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBoxT14);
			this->Controls->Add(this->pictureBoxT13);
			this->Controls->Add(this->pictureBoxT12);
			this->Controls->Add(this->pictureBoxT11);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"SplForm";
			this->Text = L"Кривые Безье и Б-сплайны";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT14))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT22))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT23))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxT24))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void buttonT11Clear_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxT11);
	listT11->Clear();
	pointIndexT11 = -1;
}
private: System::Void pictureBoxT11_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	int x = e->X, y = e->Y; // coordinates
	int i = 0;
	bool moving = false; // flag to determinate what we are doing now
	for each (Point point in listT11) {
		if (abs(point.X - x) < error && abs(point.Y - y) < error) {
			pointIndexT11 = i; // remembering point to move
			if (!moving) {
				moving = true;
			}
		}
		++i;
	}

	if (!moving) {
		// if we are not moving existing points, we create a new one
		listT11->Add(Point(x, y));
		// and draw it
		if (listT11->Count > 1) { // if we have enough points
			clearPictureBox(pictureBoxT11);
			drawSimpleCurve(pictureBoxT11, listT11, 0, listT11->Count - 1); // drawing curve
		}
		else { // draw first point
			Graphics^ graphics = Graphics::FromImage(pictureBoxT11->Image); // creating graphics
			try {
				graphics->FillEllipse(brush, x - radius, y - radius, radius * 2, radius * 2); // draw
			}
			finally {
				if (graphics) {
					delete graphics;
				}
			}
			pictureBoxT11->Refresh();
		}
	}
}
private: System::Void pictureBoxT11_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (pointIndexT11 != -1) {
			clearPictureBox(pictureBoxT11); // clearing only the image
			listT11[pointIndexT11] = Point(e->X, e->Y); // moving point
			drawSimpleCurve(pictureBoxT11, listT11, 0, listT11->Count - 1); // drawing curve
		}
	}
}
private: System::Void pictureBoxT11_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (pointIndexT11 != -1) {
		pointIndexT11 = -1;
	}
}
private: System::Void buttonT12Clear_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxT12);
	listT12->Clear();
	pointIndexT12 = -1;
}
private: System::Void pictureBoxT12_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	int x = e->X, y = e->Y; // coordinates
	int i = 0;
	bool moving = false; // flag to determinate what we are doing now
	for each (Point point in listT12) {
		if (abs(point.X - x) < error && abs(point.Y - y) < error) {
			pointIndexT12 = i; // remembering point to move
			if (!moving) {
				moving = true;
			}
		}
		++i;
	}

	if (!moving) {
		if (listT12->Count == 4) { // if we have a full curve, start a new one
			buttonT12Clear_Click(nullptr, nullptr); // clearing old
			listT12->Add(Point(x, y)); // adding first point
			Graphics^ graphics = Graphics::FromImage(pictureBoxT12->Image); // creating graphics
			try {
				graphics->FillEllipse(brush, x - radius, y - radius, radius * 2, radius * 2); // draw first point
			}
			finally {
				if (graphics) {
					delete graphics;
				}
			}
			pictureBoxT12->Refresh();
		}
		else {
			// if we are not moving existing points, we create a new one
			listT12->Add(Point(x, y));
			// and draw it
			if (listT12->Count > 1) { // if we have enough points
				clearPictureBox(pictureBoxT12);
				drawSimpleCurve(pictureBoxT12, listT12, 0, listT12->Count - 1); // drawing curve
			}
			else { // draw first point
				Graphics^ graphics = Graphics::FromImage(pictureBoxT12->Image); // creating graphics
				try {
					graphics->FillEllipse(brush, x - radius, y - radius, radius * 2, radius * 2); // draw
				}
				finally {
					if (graphics) {
						delete graphics;
					}
				}
				pictureBoxT12->Refresh();
			}
		}
	}
}
private: System::Void pictureBoxT12_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (pointIndexT12 != -1) {
			clearPictureBox(pictureBoxT12); // clearing only the image
			listT12[pointIndexT12] = Point(e->X, e->Y); // moving point
			drawSimpleCurve(pictureBoxT12, listT12, 0, listT12->Count - 1); // drawing curve
		}
	}
}
private: System::Void pictureBoxT12_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (pointIndexT12 != -1) {
		pointIndexT12 = -1;
	}
}
private: System::Void buttonT13Clear_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxT13);
	listT13->Clear();
	pointIndexT13 = -1;
}
private: System::Void pictureBoxT13_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	int x = e->X, y = e->Y; // coordinates
	int i = 0;
	bool moving = false; // flag to determinate what we are doing now
	for each (Point point in listT13) {
		if (abs(point.X - x) < error && abs(point.Y - y) < error) {
			pointIndexT13 = i; // remembering point to move
			if (!moving) {
				moving = true;
			}
		}
		++i;
	}

	if (!moving) {
		if (listT13->Count > 1 && (listT13->Count - 1) % 3 == 0) { // if we have the last curve closed, we need to correct the new point
			listT13->Add(pointCorrection(Point(x, y), listT13[listT13->Count - 1], 
				listT13[listT13->Count - 2])); // adding corrected point
			clearPictureBox(pictureBoxT13); // clearing only the image

			Graphics^ graphics = Graphics::FromImage(pictureBoxT13->Image); // creating graphics
			try {
				// draw line to show the curve rule
				graphics->DrawLine(pen2, listT13[listT13->Count - 1], listT13[listT13->Count - 3]); 
			}
			finally {
				if (graphics) {
					delete graphics;
				}
			}

			drawAllSimpleCurves(pictureBoxT13, listT13); // drawing
		}
		else {
			// if we are not moving existing points, we create a new one
			listT13->Add(Point(x, y));
			// and draw it
			clearPictureBox(pictureBoxT13); // clearing only the image
			drawAllSimpleCurves(pictureBoxT13, listT13); // drawing
		}
	}
}
private: System::Void pictureBoxT13_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (pointIndexT13 != -1) {
			clearPictureBox(pictureBoxT13); // clearing only the image
			listT13[pointIndexT13] = Point(e->X, e->Y); // moving point
			drawAllSimpleCurves(pictureBoxT13, listT13); // drawing curve
		}
	}
}
private: System::Void pictureBoxT13_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (pointIndexT13 != -1) {
		pointIndexT13 = -1;
	}
}
private: System::Void buttonT14Clear_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxT14);
	listT14->Clear();
	pointIndexT14 = -1;
	buttonT14Close->Enabled = false;
	curveT14Closed = false;
}
private: System::Void pictureBoxT14_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	int x = e->X, y = e->Y; // coordinates
	int i = 0;
	bool moving = false; // flag to determinate what we are doing now
	for each (Point point in listT14) {
		if (abs(point.X - x) < error && abs(point.Y - y) < error) {
			pointIndexT14 = i; // remembering point to move
			if (!moving) {
				moving = true;
			}
		}
		++i;
	}

	if (!moving) {
		if (curveT14Closed) { // if was closed, clear and get ready to draw a new one
			buttonT14Clear_Click(nullptr, nullptr);
		}
		if (listT14->Count > 1 && (listT14->Count - 1) % 3 == 0) { // if we have the last curve closed, we need to correct the new point
			listT14->Add(pointCorrection(Point(x, y), listT14[listT14->Count - 1],
				listT14[listT14->Count - 2])); // adding corrected point
			clearPictureBox(pictureBoxT14); // clearing only the image

			Graphics^ graphics = Graphics::FromImage(pictureBoxT14->Image); // creating graphics
			try {
				// draw line to show the curve rule
				graphics->DrawLine(pen2, listT14[listT14->Count - 1], listT14[listT14->Count - 3]);
			}
			finally {
				if (graphics) {
					delete graphics;
				}
			}

			drawAllSimpleCurves(pictureBoxT14, listT14); // drawing
			buttonT14Close->Enabled = false;
		}
		else {
			// if we are not moving existing points, we create a new one
			listT14->Add(Point(x, y));
			// and draw it
			clearPictureBox(pictureBoxT14); // clearing only the image
			drawAllSimpleCurves(pictureBoxT14, listT14); // drawing
			if (listT14->Count > 3 && listT14->Count % 3 == 0) { 
				// if one point remaining to close the curve, enable close button
				buttonT14Close->Enabled = true;
			}
			else {
				buttonT14Close->Enabled = false;
			}
		}
	}
}
private: System::Void pictureBoxT14_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (pointIndexT14 != -1) {
			clearPictureBox(pictureBoxT14); // clearing only the image
			listT14[pointIndexT14] = Point(e->X, e->Y); // moving point
			drawAllSimpleCurves(pictureBoxT14, listT14); // drawing curve
		}
	}
}
private: System::Void pictureBoxT14_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (pointIndexT14 != -1) {
		pointIndexT14 = -1;
	}
}
private: System::Void buttonT14Close_Click(System::Object^  sender, System::EventArgs^  e) {
	// closing
	clearPictureBox(pictureBoxT14); // clearing image only
	listT14[listT14->Count - 1] = (pointCorrection(listT14[listT14->Count - 1],
		listT14[0], listT14[1])); // correcting last point
	listT14->Add(Point(listT14[0].X, listT14[0].Y)); // adding first point
	drawAllSimpleCurves(pictureBoxT14, listT14); // drawing
	buttonT14Close->Enabled = false;
	curveT14Closed = true;
}
private: System::Void buttonT22Clear_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxT22);
	listT22->Clear();
	pointIndexT22 = -1;
}
private: System::Void pictureBoxT22_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	int x = e->X, y = e->Y; // coordinates
	int i = 0;
	bool moving = false; // flag to determinate what we are doing now
	for each (Point point in listT22) {
		if (abs(point.X - x) < error && abs(point.Y - y) < error) {
			pointIndexT22 = i; // remembering point to move
			if (!moving) {
				moving = true;
			}
		}
		++i;
	}

	if (!moving) {
		if (listT22->Count == 4) { // if we already have a full spline
			buttonT22Clear_Click(nullptr, nullptr); // clearing all
		}
		listT22->Add(Point(x, y)); // adding point
		drawAllBSplines(pictureBoxT22, listT22, false); // draw spline
	}
}
private: System::Void pictureBoxT22_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (pointIndexT22 != -1) {
			clearPictureBox(pictureBoxT22); // clearing only the image
			listT22[pointIndexT22] = Point(e->X, e->Y); // moving point
			drawAllBSplines(pictureBoxT22, listT22, false); // drawing curve
		}
	}
}
private: System::Void pictureBoxT22_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (pointIndexT22 != -1) {
		pointIndexT22 = -1;
	}
}
private: System::Void buttonT23Clear_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxT23);
	listT23->Clear();
	pointIndexT23 = -1;
}
private: System::Void pictureBoxT23_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	int x = e->X, y = e->Y; // coordinates
	int i = 0;
	bool moving = false; // flag to determinate what we are doing now
	for each (Point point in listT23) {
		if (abs(point.X - x) < error && abs(point.Y - y) < error) {
			pointIndexT23 = i; // remembering point to move
			if (!moving) {
				moving = true;
			}
		}
		++i;
	}
	
	if (!moving) {
		listT23->Add(Point(x, y)); // adding point
		drawAllBSplines(pictureBoxT23, listT23, false); // draw spline
	}
}
private: System::Void pictureBoxT23_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (pointIndexT23 != -1) {
			clearPictureBox(pictureBoxT23); // clearing only the image
			listT23[pointIndexT23] = Point(e->X, e->Y); // moving point
			drawAllBSplines(pictureBoxT23, listT23, false); // drawing curve
		}
	}
}
private: System::Void pictureBoxT23_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (pointIndexT23 != -1) {
		pointIndexT23 = -1;
	}
}
private: System::Void buttonT24Clear_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxT24);
	listT24->Clear();
	pointIndexT24 = -1;
	curveT24Closed = false;
}
private: System::Void pictureBoxT24_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	int x = e->X, y = e->Y; // coordinates
	int i = 0;
	bool moving = false; // flag to determinate what we are doing now
	for each (Point point in listT24) {
		if (abs(point.X - x) < error && abs(point.Y - y) < error) {
			pointIndexT24 = i; // remembering point to move
			if (!moving) {
				moving = true;
			}
		}
		++i;
	}

	if (!moving) {
		if (curveT24Closed == true) { // if was closed
			buttonT24Clear_Click(nullptr, nullptr); // clearing all
		}
		listT24->Add(Point(x, y)); // adding point
		if (listT24->Count >= 4 && !buttonT24Close->Enabled) {
			buttonT24Close->Enabled = true;
		}
		drawAllBSplines(pictureBoxT24, listT24, curveT24Closed); // draw spline
	}
}
private: System::Void pictureBoxT24_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (pointIndexT24 != -1) {
			clearPictureBox(pictureBoxT24); // clearing only the image
			listT24[pointIndexT24] = Point(e->X, e->Y); // moving point
			drawAllBSplines(pictureBoxT24, listT24, curveT24Closed); // drawing curve
		}
	}
}
private: System::Void pictureBoxT24_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (pointIndexT24 != -1) {
		pointIndexT24 = -1;
	}
}
private: System::Void buttonT24Close_Click(System::Object^  sender, System::EventArgs^  e) {
	// closing
	clearPictureBox(pictureBoxT24); // clearing image only
	drawAllBSplines(pictureBoxT24, listT24, true); // drawing
	buttonT24Close->Enabled = false;
	curveT24Closed = true;
}
private: System::Void цветФонаToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogBg->Color; // saving old color
	colorDialogBg->ShowDialog();
	if (colorDialogBg->Color.ToArgb() == colorDialogFg->Color.ToArgb() // checking colors
		&& colorDialogBg->Color.ToArgb() == colorDialogSPC->Color.ToArgb()
		&& colorDialogBg->Color.ToArgb() == colorDialogSLC->Color.ToArgb()) {
		MessageBox::Show(this, "Одинаковые цвета фона, пера и опорных точек и показательной линии недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogBg->Color = *old; // restoring old color if colors are identical
	}
	else { // clearing all
		clearAll();
		delete old;
	}
}
private: System::Void цветПераToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogFg->Color; // saving old color
	colorDialogFg->ShowDialog();
	if (colorDialogFg->Color.ToArgb() == colorDialogBg->Color.ToArgb() // checking colors
		&& colorDialogFg->Color.ToArgb() == colorDialogSPC->Color.ToArgb()
		&& colorDialogFg->Color.ToArgb() == colorDialogSLC->Color.ToArgb()) {
		MessageBox::Show(this, "Одинаковые цвета фона, пера и опорных точек и показательной линии недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogFg->Color = *old; // restoring old color if colors are identical
	}
	else { // clearing all
		clearAll();
		pen = gcnew Pen(colorDialogFg->Color);
		brush2 = gcnew SolidBrush(colorDialogFg->Color);
		delete old;
	}
}

private: System::Void цветОпорныхТочекToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogSPC->Color; // saving old color
	colorDialogSPC->ShowDialog();
	if (colorDialogSPC->Color.ToArgb() == colorDialogBg->Color.ToArgb() // checking colors
		&& colorDialogSPC->Color.ToArgb() == colorDialogFg->Color.ToArgb()
		&& colorDialogSPC->Color.ToArgb() == colorDialogSLC->Color.ToArgb()) {
		MessageBox::Show(this, "Одинаковые цвета фона, пера, опорных точек и показательной линии недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogSPC->Color = *old; // restoring old color if colors are identical
	}
	else { // clearing all
		clearAll();
		brush = gcnew SolidBrush(colorDialogSPC->Color);
		delete old;
	}
}

private: System::Void цветПоказательнойЛинииToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogSLC->Color; // saving old color
	colorDialogSLC->ShowDialog();
	if (colorDialogSLC->Color.ToArgb() == colorDialogBg->Color.ToArgb() // checking colors
		&& colorDialogSLC->Color.ToArgb() == colorDialogFg->Color.ToArgb()
		&& colorDialogSLC->Color.ToArgb() == colorDialogSPC->Color.ToArgb()) {
		MessageBox::Show(this, "Одинаковые цвета фона, пера, опорных точек и показательной линии недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogSLC->Color = *old; // restoring old color if colors are identical
	}
	else { // clearing all
		clearAll();
		pen2 = gcnew Pen(colorDialogSLC->Color);
		delete old;
	}
}
private: System::Void оПрограммеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show(this, "Программа предназначена для демонстрации построения кривых Безье и Б-сплайнов.\n\n" +
		"1) Для добавления опорной точки следует нажать на область рисования левой клавишей мыши.\n\n" +
		"ПРИМЕЧАНИЕ 1. В случаях, когда кривая нарисована полностью (например, элементарная кубическая " +
		"или замкнутая составная), после нажатия на область рисование начинается сначала.\n\n" +
		"ПРИМЕЧАНИЕ 2. В составных кривых Безье для соблюдения условия непрерывности точка следующей " +
		"кривой автоматически перемещается для образования прямой с двумя предыдущими точками. " +
		"Для наглядности эта прямая прорисовывается до следующего изменения кривой.\n\n" +
		"2) Для перемещения опорной точки следует нажать на точку левой клавишей мыши и, не отпуская " +
		"мышь, передвинуть точку в нужное место.\n\n" +
		"3) Для очистки областей для рисования можно воспользоваться соответствующими кнопками рядом с ними.\n\n" +
		"5) Также в программе можно менять цвет фона окон для рисования, цвет пера, цвет опорных точек " +
		"и цвет прямой для демонстрации свойств кривых. Для этого следует зайти в меню \"Настройки\".\n\n"
		"Автор: Осипов Лев Игоревич, 4-й курс, группа БПИ121\n" +
		"Среда разработки: Visual Studio 2013\n" +
		"Дата: 10.10.2015", "О программе", MessageBoxButtons::OK);

}
};
}
