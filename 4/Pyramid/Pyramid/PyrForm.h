#pragma once

namespace Pyramid {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/***
	Осипов Лев Игоревич, 4-й курс, группа БПИ121
	Семинар 4. 3D моделирование
	Среда разработки: Visual Studio 2013
	Дата: 19.10.2015
	Реализованы различные отображения и трансформации пирамиды.
	Подробнее см. в меню "О программе".
	*/

	/// <summary>
	/// Summary for PyrForm
	/// </summary>
	public ref class PyrForm : public System::Windows::Forms::Form
	{
	public:
		PyrForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			// Creating bitmap
			bitmapPyr = gcnew Bitmap(pictureBoxPyr->Width, pictureBoxPyr->Height);
			pictureBoxPyr->Image = bitmapPyr;


			// initializing colors
			colorDialogBg->Color = Color::Gray;
			colorDialogFg->Color = Color::Blue;
			colorDialogAdd->Color = Color::Green;
			pen = gcnew Pen(Color::Blue);
			clearPictureBox(pictureBoxPyr);

			// getting start coordinates
			x0 = pictureBoxPyr->Width / 2;
			y0 = pictureBoxPyr->Height / 2;
			z0 = 0;

			// creating initial matrices
			initializeMatrices();
			labelProjType->Text = "Ортогональная проекция";
			matrixCurrProj = matrixOrtProj;

			trackBarDeltaScale->Value = 3;
			textBoxZ0->Text = "-100";
			pressedX = pressedY = 0;
			
			// draws initial figure
			drawInitialPyramid();

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PyrForm()
		{
			if (components)
			{
				delete components;
			}

			if (pen) {
				delete pen;
			}

			if (bitmapPyr) {
				delete bitmapPyr;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBoxPyr;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		/// <summary>
		/// Pen to draw common lines.
		/// </summary>
		Pen^ pen;

		/// <summary>
		/// Bitmap to draw in.
		/// </summary>
		Bitmap^ bitmapPyr;

		/// <summary>
		/// Start coordinates.
		/// </summary>
		int x0;
		int y0;
		int z0;

		/// <summary>
		/// Pressed point coordinates.
		/// </summary>
		int pressedX;
		int pressedY;

		/// <summary>
		/// Vertex matrix.
		/// </summary>
		array<double, 2> ^matrixVert;
	private: System::Windows::Forms::RadioButton^  radioButtonX;
	private: System::Windows::Forms::RadioButton^  radioButtonY;



		/// <summary>
		/// Face matrix.
		/// </summary>
		array<int, 2>^ matrixFace;

		/// <summary>
		/// Matrix of ortogonal projection
		/// </summary>
		array<double, 2>^ matrixOrtProj;
	private: System::Windows::Forms::TrackBar^  trackBarDeltaScale;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::RadioButton^  radioButtonZ;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  buttonMoveBack;
	private: System::Windows::Forms::Button^  buttonMoveForw;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  buttonCW;
	private: System::Windows::Forms::Button^  buttonCCW;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  buttonScaleSmall;
	private: System::Windows::Forms::Button^  buttonScaleBig;
private: System::Windows::Forms::Button^  buttonOrtProj;

private: System::Windows::Forms::Button^  buttonCentProj;

	private: System::Windows::Forms::Label^  labelProjType;
private: System::Windows::Forms::TextBox^  textBoxZ0;

private: System::Windows::Forms::MenuStrip^  menuStrip1;
private: System::Windows::Forms::ToolStripMenuItem^  оПрограммеToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  настройкиToolStripMenuItem;
private: System::Windows::Forms::RadioButton^  radioButtonAll;
private: System::Windows::Forms::Button^  buttonNew;
private: System::Windows::Forms::ToolStripMenuItem^  цветФонаToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  цветФигурыToolStripMenuItem;
private: System::Windows::Forms::ColorDialog^  colorDialogBg;
private: System::Windows::Forms::ColorDialog^  colorDialogFg;
private: System::Windows::Forms::Button^  buttonMovRot;
private: System::Windows::Forms::Button^  buttonRotMov;
private: System::Windows::Forms::Button^  buttonDemo;
private: System::Windows::Forms::ToolStripMenuItem^  дополнительныйЦветToolStripMenuItem;
private: System::Windows::Forms::ColorDialog^  colorDialogAdd;

		/// <summary>
		/// Matrix of current projection
		/// </summary>
		array<double, 2>^ matrixCurrProj;

		/// <summary>
		/// Returns a composition of 2 matrices.
		/// </summary>
		array<double, 2>^ matrixComposition(array<double, 2>^ m1, array<double, 2>^ m2);

		/// <summary>
		/// Initializes figure matrices.
		/// </summary>
		void initializeMatrices();

		/// <summary>
		/// Restores vertex matrix.
		/// </summary>
		void restoreVertexMatrix();

		/// <summary>
		/// Draws initial pyramid
		/// </summary>
		void drawInitialPyramid();

		/// <summary>
		/// Increment deltas depeding on operating axis.
		/// </summary>
		void incrementDeltas(double& deltaX, double& deltaY, double& deltaZ, double deltaLength);

		/// <summary>
		/// Decrement deltas depeding on operating axis
		/// </summary>
		void decrementDeltas(double& deltaX, double& deltaY, double& deltaZ, double deltaLength);

		/// <summary>
		/// Creates a matrix for moving.
		/// </summary>
		array<double, 2>^ formMoveMatrix(double deltaX, double deltaY, double deltaZ);

		/// <summary>
		/// Creates a matrix for X-rotating.
		/// </summary>
		array<double, 2>^ formXRotateMatrix(double deltaRadX);

		/// <summary>
		/// Creates a matrix for Y-rotating.
		/// </summary>
		array<double, 2>^ formYRotateMatrix(double deltaRadY);

		/// <summary>
		/// Creates a matrix for Z-rotating.
		/// </summary>
		array<double, 2>^ formZRotateMatrix(double deltaRadZ);

		/// <summary>
		/// Creates a matrix for scaling.
		/// </summary>
		array<double, 2>^ formScaleMatrix(double deltaScaleX, double deltaScaleY, double deltaScaleZ, double generalScale);

		/// <summary>
		/// Draws a pyramid.
		/// </summary>
		void drawPyramid(PictureBox^ pb, array<double, 2>^ matrix, array<int, 2>^ matrixFace);

		/// <summary>
		/// Clears picture box.
		/// </summary>
		void clearPictureBox(PictureBox^ pb);



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBoxPyr = (gcnew System::Windows::Forms::PictureBox());
			this->radioButtonX = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonY = (gcnew System::Windows::Forms::RadioButton());
			this->trackBarDeltaScale = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->radioButtonZ = (gcnew System::Windows::Forms::RadioButton());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->buttonMoveBack = (gcnew System::Windows::Forms::Button());
			this->buttonMoveForw = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->buttonCW = (gcnew System::Windows::Forms::Button());
			this->buttonCCW = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->buttonScaleSmall = (gcnew System::Windows::Forms::Button());
			this->buttonScaleBig = (gcnew System::Windows::Forms::Button());
			this->buttonOrtProj = (gcnew System::Windows::Forms::Button());
			this->buttonCentProj = (gcnew System::Windows::Forms::Button());
			this->labelProjType = (gcnew System::Windows::Forms::Label());
			this->textBoxZ0 = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->настройкиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветФонаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветФигурыToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->дополнительныйЦветToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->radioButtonAll = (gcnew System::Windows::Forms::RadioButton());
			this->buttonNew = (gcnew System::Windows::Forms::Button());
			this->colorDialogBg = (gcnew System::Windows::Forms::ColorDialog());
			this->colorDialogFg = (gcnew System::Windows::Forms::ColorDialog());
			this->buttonMovRot = (gcnew System::Windows::Forms::Button());
			this->buttonRotMov = (gcnew System::Windows::Forms::Button());
			this->buttonDemo = (gcnew System::Windows::Forms::Button());
			this->colorDialogAdd = (gcnew System::Windows::Forms::ColorDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxPyr))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarDeltaScale))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBoxPyr
			// 
			this->pictureBoxPyr->BackColor = System::Drawing::Color::White;
			this->pictureBoxPyr->Location = System::Drawing::Point(12, 35);
			this->pictureBoxPyr->Name = L"pictureBoxPyr";
			this->pictureBoxPyr->Size = System::Drawing::Size(310, 310);
			this->pictureBoxPyr->TabIndex = 0;
			this->pictureBoxPyr->TabStop = false;
			this->pictureBoxPyr->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &PyrForm::pictureBoxPyr_MouseDown);
			this->pictureBoxPyr->MouseEnter += gcnew System::EventHandler(this, &PyrForm::pictureBoxPyr_MouseEnter);
			this->pictureBoxPyr->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &PyrForm::pictureBoxPyr_MouseMove);
			this->pictureBoxPyr->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &PyrForm::pictureBoxPyr_MouseWheel);
			// 
			// radioButtonX
			// 
			this->radioButtonX->AutoSize = true;
			this->radioButtonX->Location = System::Drawing::Point(388, 64);
			this->radioButtonX->Name = L"radioButtonX";
			this->radioButtonX->Size = System::Drawing::Size(32, 17);
			this->radioButtonX->TabIndex = 2;
			this->radioButtonX->TabStop = true;
			this->radioButtonX->Text = L"X";
			this->radioButtonX->UseVisualStyleBackColor = true;
			// 
			// radioButtonY
			// 
			this->radioButtonY->AutoSize = true;
			this->radioButtonY->Location = System::Drawing::Point(426, 64);
			this->radioButtonY->Name = L"radioButtonY";
			this->radioButtonY->Size = System::Drawing::Size(32, 17);
			this->radioButtonY->TabIndex = 3;
			this->radioButtonY->TabStop = true;
			this->radioButtonY->Text = L"Y";
			this->radioButtonY->UseVisualStyleBackColor = true;
			// 
			// trackBarDeltaScale
			// 
			this->trackBarDeltaScale->Location = System::Drawing::Point(475, 97);
			this->trackBarDeltaScale->Name = L"trackBarDeltaScale";
			this->trackBarDeltaScale->Size = System::Drawing::Size(104, 45);
			this->trackBarDeltaScale->TabIndex = 7;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(430, 30);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(60, 29);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Ось";
			// 
			// radioButtonZ
			// 
			this->radioButtonZ->AutoSize = true;
			this->radioButtonZ->Location = System::Drawing::Point(464, 64);
			this->radioButtonZ->Name = L"radioButtonZ";
			this->radioButtonZ->Size = System::Drawing::Size(32, 17);
			this->radioButtonZ->TabIndex = 4;
			this->radioButtonZ->TabStop = true;
			this->radioButtonZ->Text = L"Z";
			this->radioButtonZ->UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(350, 106);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(114, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Величина изменения";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(426, 154);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(71, 24);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Сдвиг";
			// 
			// buttonMoveBack
			// 
			this->buttonMoveBack->Location = System::Drawing::Point(350, 185);
			this->buttonMoveBack->Name = L"buttonMoveBack";
			this->buttonMoveBack->Size = System::Drawing::Size(105, 23);
			this->buttonMoveBack->TabIndex = 9;
			this->buttonMoveBack->Text = L"Назад";
			this->buttonMoveBack->UseVisualStyleBackColor = true;
			this->buttonMoveBack->Click += gcnew System::EventHandler(this, &PyrForm::buttonMoveBack_Click);
			// 
			// buttonMoveForw
			// 
			this->buttonMoveForw->Location = System::Drawing::Point(474, 185);
			this->buttonMoveForw->Name = L"buttonMoveForw";
			this->buttonMoveForw->Size = System::Drawing::Size(105, 23);
			this->buttonMoveForw->TabIndex = 10;
			this->buttonMoveForw->Text = L"Вперед";
			this->buttonMoveForw->UseVisualStyleBackColor = true;
			this->buttonMoveForw->Click += gcnew System::EventHandler(this, &PyrForm::buttonMoveForw_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(410, 223);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(108, 24);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Вращение";
			// 
			// buttonCW
			// 
			this->buttonCW->Location = System::Drawing::Point(473, 252);
			this->buttonCW->Name = L"buttonCW";
			this->buttonCW->Size = System::Drawing::Size(105, 23);
			this->buttonCW->TabIndex = 13;
			this->buttonCW->Text = L"По часовой";
			this->buttonCW->UseVisualStyleBackColor = true;
			this->buttonCW->Click += gcnew System::EventHandler(this, &PyrForm::buttonCW_Click);
			// 
			// buttonCCW
			// 
			this->buttonCCW->Location = System::Drawing::Point(353, 252);
			this->buttonCCW->Name = L"buttonCCW";
			this->buttonCCW->Size = System::Drawing::Size(105, 23);
			this->buttonCCW->TabIndex = 12;
			this->buttonCCW->Text = L"Против часовой";
			this->buttonCCW->UseVisualStyleBackColor = true;
			this->buttonCCW->Click += gcnew System::EventHandler(this, &PyrForm::buttonCCW_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(414, 291);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(98, 24);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Масштаб";
			// 
			// buttonScaleSmall
			// 
			this->buttonScaleSmall->Location = System::Drawing::Point(353, 322);
			this->buttonScaleSmall->Name = L"buttonScaleSmall";
			this->buttonScaleSmall->Size = System::Drawing::Size(105, 23);
			this->buttonScaleSmall->TabIndex = 15;
			this->buttonScaleSmall->Text = L"Меньше";
			this->buttonScaleSmall->UseVisualStyleBackColor = true;
			this->buttonScaleSmall->Click += gcnew System::EventHandler(this, &PyrForm::buttonScaleSmall_Click);
			// 
			// buttonScaleBig
			// 
			this->buttonScaleBig->Location = System::Drawing::Point(473, 322);
			this->buttonScaleBig->Name = L"buttonScaleBig";
			this->buttonScaleBig->Size = System::Drawing::Size(105, 23);
			this->buttonScaleBig->TabIndex = 16;
			this->buttonScaleBig->Text = L"Больше";
			this->buttonScaleBig->UseVisualStyleBackColor = true;
			this->buttonScaleBig->Click += gcnew System::EventHandler(this, &PyrForm::buttonScaleBig_Click);
			// 
			// buttonOrtProj
			// 
			this->buttonOrtProj->Location = System::Drawing::Point(350, 391);
			this->buttonOrtProj->Name = L"buttonOrtProj";
			this->buttonOrtProj->Size = System::Drawing::Size(183, 23);
			this->buttonOrtProj->TabIndex = 17;
			this->buttonOrtProj->Text = L"Ортогональная проекция";
			this->buttonOrtProj->UseVisualStyleBackColor = true;
			this->buttonOrtProj->Click += gcnew System::EventHandler(this, &PyrForm::buttonOrtProj_Click);
			// 
			// buttonCentProj
			// 
			this->buttonCentProj->Location = System::Drawing::Point(350, 420);
			this->buttonCentProj->Name = L"buttonCentProj";
			this->buttonCentProj->Size = System::Drawing::Size(183, 23);
			this->buttonCentProj->TabIndex = 18;
			this->buttonCentProj->Text = L"Центральная проекция, z0:";
			this->buttonCentProj->UseVisualStyleBackColor = true;
			this->buttonCentProj->Click += gcnew System::EventHandler(this, &PyrForm::buttonCentProj_Click);
			// 
			// labelProjType
			// 
			this->labelProjType->AutoSize = true;
			this->labelProjType->Location = System::Drawing::Point(96, 351);
			this->labelProjType->Name = L"labelProjType";
			this->labelProjType->Size = System::Drawing::Size(136, 13);
			this->labelProjType->TabIndex = 20;
			this->labelProjType->Text = L"Ортогональная проекция";
			// 
			// textBoxZ0
			// 
			this->textBoxZ0->Location = System::Drawing::Point(539, 422);
			this->textBoxZ0->Name = L"textBoxZ0";
			this->textBoxZ0->Size = System::Drawing::Size(40, 20);
			this->textBoxZ0->TabIndex = 19;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->оПрограммеToolStripMenuItem,
					this->настройкиToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(624, 24);
			this->menuStrip1->TabIndex = 20;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(94, 20);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
			this->оПрограммеToolStripMenuItem->Click += gcnew System::EventHandler(this, &PyrForm::оПрограммеToolStripMenuItem_Click);
			// 
			// настройкиToolStripMenuItem
			// 
			this->настройкиToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->цветФонаToolStripMenuItem,
					this->цветФигурыToolStripMenuItem, this->дополнительныйЦветToolStripMenuItem
			});
			this->настройкиToolStripMenuItem->Name = L"настройкиToolStripMenuItem";
			this->настройкиToolStripMenuItem->Size = System::Drawing::Size(79, 20);
			this->настройкиToolStripMenuItem->Text = L"Настройки";
			// 
			// цветФонаToolStripMenuItem
			// 
			this->цветФонаToolStripMenuItem->Name = L"цветФонаToolStripMenuItem";
			this->цветФонаToolStripMenuItem->Size = System::Drawing::Size(198, 22);
			this->цветФонаToolStripMenuItem->Text = L"Цвет фона";
			this->цветФонаToolStripMenuItem->Click += gcnew System::EventHandler(this, &PyrForm::цветФонаToolStripMenuItem_Click);
			// 
			// цветФигурыToolStripMenuItem
			// 
			this->цветФигурыToolStripMenuItem->Name = L"цветФигурыToolStripMenuItem";
			this->цветФигурыToolStripMenuItem->Size = System::Drawing::Size(198, 22);
			this->цветФигурыToolStripMenuItem->Text = L"Цвет фигуры";
			this->цветФигурыToolStripMenuItem->Click += gcnew System::EventHandler(this, &PyrForm::цветФигурыToolStripMenuItem_Click);
			// 
			// дополнительныйЦветToolStripMenuItem
			// 
			this->дополнительныйЦветToolStripMenuItem->Name = L"дополнительныйЦветToolStripMenuItem";
			this->дополнительныйЦветToolStripMenuItem->Size = System::Drawing::Size(198, 22);
			this->дополнительныйЦветToolStripMenuItem->Text = L"Дополнительный цвет";
			this->дополнительныйЦветToolStripMenuItem->Click += gcnew System::EventHandler(this, &PyrForm::дополнительныйЦветToolStripMenuItem_Click);
			// 
			// radioButtonAll
			// 
			this->radioButtonAll->AutoSize = true;
			this->radioButtonAll->Location = System::Drawing::Point(502, 64);
			this->radioButtonAll->Name = L"radioButtonAll";
			this->radioButtonAll->Size = System::Drawing::Size(44, 17);
			this->radioButtonAll->TabIndex = 5;
			this->radioButtonAll->TabStop = true;
			this->radioButtonAll->Text = L"Все";
			this->radioButtonAll->UseVisualStyleBackColor = true;
			// 
			// buttonNew
			// 
			this->buttonNew->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonNew->Location = System::Drawing::Point(388, 459);
			this->buttonNew->Name = L"buttonNew";
			this->buttonNew->Size = System::Drawing::Size(145, 34);
			this->buttonNew->TabIndex = 21;
			this->buttonNew->Text = L"Новая фигура";
			this->buttonNew->UseVisualStyleBackColor = true;
			this->buttonNew->Click += gcnew System::EventHandler(this, &PyrForm::buttonNew_Click);
			// 
			// buttonMovRot
			// 
			this->buttonMovRot->Location = System::Drawing::Point(12, 448);
			this->buttonMovRot->Name = L"buttonMovRot";
			this->buttonMovRot->Size = System::Drawing::Size(143, 23);
			this->buttonMovRot->TabIndex = 22;
			this->buttonMovRot->Text = L"Сдвиг + вращение";
			this->buttonMovRot->UseVisualStyleBackColor = true;
			this->buttonMovRot->Click += gcnew System::EventHandler(this, &PyrForm::buttonMovRot_Click);
			// 
			// buttonRotMov
			// 
			this->buttonRotMov->Location = System::Drawing::Point(12, 419);
			this->buttonRotMov->Name = L"buttonRotMov";
			this->buttonRotMov->Size = System::Drawing::Size(143, 23);
			this->buttonRotMov->TabIndex = 23;
			this->buttonRotMov->Text = L"Вращение + сдвиг";
			this->buttonRotMov->UseVisualStyleBackColor = true;
			this->buttonRotMov->Click += gcnew System::EventHandler(this, &PyrForm::buttonRotMov_Click);
			// 
			// buttonDemo
			// 
			this->buttonDemo->Location = System::Drawing::Point(12, 477);
			this->buttonDemo->Name = L"buttonDemo";
			this->buttonDemo->Size = System::Drawing::Size(143, 23);
			this->buttonDemo->TabIndex = 24;
			this->buttonDemo->Text = L"Одновременно";
			this->buttonDemo->UseVisualStyleBackColor = true;
			this->buttonDemo->Click += gcnew System::EventHandler(this, &PyrForm::buttonDemo_Click);
			// 
			// PyrForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(624, 505);
			this->Controls->Add(this->buttonDemo);
			this->Controls->Add(this->buttonRotMov);
			this->Controls->Add(this->buttonMovRot);
			this->Controls->Add(this->buttonNew);
			this->Controls->Add(this->radioButtonAll);
			this->Controls->Add(this->textBoxZ0);
			this->Controls->Add(this->labelProjType);
			this->Controls->Add(this->buttonCentProj);
			this->Controls->Add(this->buttonOrtProj);
			this->Controls->Add(this->buttonScaleBig);
			this->Controls->Add(this->buttonScaleSmall);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->buttonCCW);
			this->Controls->Add(this->buttonCW);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->buttonMoveForw);
			this->Controls->Add(this->buttonMoveBack);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->radioButtonZ);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->trackBarDeltaScale);
			this->Controls->Add(this->radioButtonY);
			this->Controls->Add(this->radioButtonX);
			this->Controls->Add(this->pictureBoxPyr);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"PyrForm";
			this->Text = L"3D моделирование";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxPyr))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarDeltaScale))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void buttonOrtProj_Click(System::Object^  sender, System::EventArgs^  e) {
	labelProjType->Text = "Ортогональная проекция";
	matrixCurrProj = matrixOrtProj; // changing matrix

	clearPictureBox(pictureBoxPyr); // clearing
	drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace); // drawing
}
private: System::Void buttonCentProj_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ str = textBoxZ0->Text->ToString();
	int result;
	int z0;
	bool res = Int32::TryParse(str, result);
	if (!res) {
		MessageBox::Show(this, "Пожалуйста, введите целую z0!",
			"Ошибка", MessageBoxButtons::OK);
		return;
	}
	else {
		z0 = Int32::Parse(str);
	}
	matrixCurrProj = gcnew array<double, 2>(4, 4); // creating new matrix
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			matrixCurrProj[i, j] = 0; // filling it by zeros
		}
	}

	/* Filling it by values */
	matrixCurrProj[0, 0] = 1;
	matrixCurrProj[1, 1] = 1;
	matrixCurrProj[2, 3] = -1.0 / z0;
	matrixCurrProj[3, 3] = 1;
	labelProjType->Text = "Центральная проекция, z0 = " + z0;

	clearPictureBox(pictureBoxPyr); // clearing
	drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace); // drawing
}
private: System::Void buttonMoveBack_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 0;
	double deltaY = 0;
	double deltaZ = 0;

	decrementDeltas(deltaX, deltaY, deltaZ, trackBarDeltaScale->Value); // decrementing the current delta

	matrixVert = matrixComposition(matrixVert, formMoveMatrix(deltaX, deltaY, deltaZ)); // moving

	clearPictureBox(pictureBoxPyr); // clearing
	drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace); // drawing
}
private: System::Void buttonMoveForw_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 0;
	double deltaY = 0;
	double deltaZ = 0;

	incrementDeltas(deltaX, deltaY, deltaZ, trackBarDeltaScale->Value); // incrementing the current delta

	matrixVert = matrixComposition(matrixVert, formMoveMatrix(deltaX, deltaY, deltaZ)); // moving

	clearPictureBox(pictureBoxPyr); // clearing
	drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace); // drawing
}
private: System::Void buttonCCW_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 0;
	double deltaY = 0;
	double deltaZ = 0;

	decrementDeltas(deltaX, deltaY, deltaZ, (double)trackBarDeltaScale->Value / 20); // decrementing the current delta

	if (deltaX != 0) { // if was X-rotation
		matrixVert = matrixComposition(matrixVert, formXRotateMatrix(deltaX)); // rotating X
	}

	if (deltaY != 0) { // if was X-rotation
		matrixVert = matrixComposition(matrixVert, formYRotateMatrix(deltaY)); // rotating Y
	}

	if (deltaZ != 0) { // if was X-rotation
		matrixVert = matrixComposition(matrixVert, formZRotateMatrix(deltaZ)); // rotating Z
	}

	clearPictureBox(pictureBoxPyr); // clearing
	drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace); // drawing
}
private: System::Void buttonCW_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 0;
	double deltaY = 0;
	double deltaZ = 0;

	incrementDeltas(deltaX, deltaY, deltaZ, (double)trackBarDeltaScale->Value / 20); // incrementing the current delta

	if (deltaX != 0) { // if was X-rotation
		matrixVert = matrixComposition(matrixVert, formXRotateMatrix(deltaX)); // rotating X
	}

	if (deltaY != 0) { // if was X-rotation
		matrixVert = matrixComposition(matrixVert, formYRotateMatrix(deltaY)); // rotating Y
	}

	if (deltaZ != 0) { // if was X-rotation
		matrixVert = matrixComposition(matrixVert, formZRotateMatrix(deltaZ)); // rotating Z
	}

	clearPictureBox(pictureBoxPyr); // clearing
	drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace); // drawing
}
private: System::Void buttonScaleSmall_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 1;
	double deltaY = 1;
	double deltaZ = 1;

	decrementDeltas(deltaX, deltaY, deltaZ, (double)trackBarDeltaScale->Value / 20); // decrementing the current delta

	matrixVert = matrixComposition(matrixVert, formScaleMatrix(deltaX, deltaY, deltaZ, 1)); // scaling

	clearPictureBox(pictureBoxPyr); // clearing
	drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace); // drawing
}
private: System::Void buttonScaleBig_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 1;
	double deltaY = 1;
	double deltaZ = 1;

	incrementDeltas(deltaX, deltaY, deltaZ, (double)trackBarDeltaScale->Value / 20); // incrementing the current delta

	matrixVert = matrixComposition(matrixVert, formScaleMatrix(deltaX, deltaY, deltaZ, 1)); // scaling

	clearPictureBox(pictureBoxPyr); // clearing
	drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace); // drawing
}
private: System::Void buttonNew_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxPyr); // clearing
	// draws initial figure
	drawInitialPyramid();
}
private: System::Void buttonMovRot_Click(System::Object^  sender, System::EventArgs^  e) {
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(3, 0, 0)); // moving
	matrixVert = matrixComposition(matrixVert, formYRotateMatrix(0.3)); // rotating
	clearPictureBox(pictureBoxPyr); // clearing
	drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace); // drawing
}
private: System::Void buttonRotMov_Click(System::Object^  sender, System::EventArgs^  e) {
	matrixVert = matrixComposition(matrixVert, formYRotateMatrix(0.3)); // rotating
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(3, 0, 0)); // moving
	clearPictureBox(pictureBoxPyr); // clearing
	drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace); // drawing
}
private: System::Void buttonDemo_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxPyr); // clearing
	
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(3, 0, 0)); // moving
	matrixVert = matrixComposition(matrixVert, formYRotateMatrix(0.3)); // rotating
	drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace); // drawing 1
	
	array<double, 2>^ matrixCopy = gcnew array<double, 2>(matrixVert->GetLength(0), matrixVert->GetLength(1));
	Array::Copy(matrixVert, 0, matrixCopy, 0, matrixVert->GetLength(0) * matrixVert->GetLength(0)); // copying 
	pen = gcnew Pen(colorDialogAdd->Color); // changing color
	matrixCopy = matrixComposition(matrixCopy, formYRotateMatrix(0.3)); // rotating
	matrixCopy = matrixComposition(matrixCopy, formMoveMatrix(3, 0, 0)); // moving
	drawPyramid(pictureBoxPyr, matrixComposition(matrixCopy, matrixCurrProj), matrixFace); // drawing 2
	
	pen = gcnew Pen(colorDialogFg->Color); // restoring color
}
private: System::Void pictureBoxPyr_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	// saving coords
	pressedX = e->X;
	pressedY = e->Y;
}
private: System::Void pictureBoxPyr_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == Windows::Forms::MouseButtons::Right) { // right - moving
		matrixVert = matrixComposition(matrixVert, formMoveMatrix(e->X - pressedX, e->Y-pressedY, 0)); // moving
		clearPictureBox(pictureBoxPyr); // clearing
		drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace); // drawing
	}
	if (e->Button == Windows::Forms::MouseButtons::Left) { // left - rotating
		if (e->X - pressedX != 0) { // if x changed
			matrixVert = matrixComposition(matrixVert, formYRotateMatrix((e->X - pressedX) / 100.0)); // rotating x
		}
		if (e->Y - pressedY != 0) { // if y changed
			matrixVert = matrixComposition(matrixVert, formXRotateMatrix((e->Y - pressedY) / 100.0)); // rotating y
		}
		
		clearPictureBox(pictureBoxPyr); // clearing
		drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace);
	}
	// saving coords
	pressedX = e->X;
	pressedY = e->Y;
}
private: System::Void pictureBoxPyr_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
	pictureBoxPyr->Focus();
}
private: System::Void pictureBoxPyr_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	double deltaScale = 1;
	
	/* Defining delta scale (for comfortable drawing) */
	if (e->Delta > 0)
	{
		deltaScale = 1.1;
	}
	else if (e->Delta < 0)
	{
		deltaScale = 0.9;
	}

	matrixVert = matrixComposition(matrixVert, formScaleMatrix(deltaScale, deltaScale, deltaScale, 1)); // scaling

	clearPictureBox(pictureBoxPyr); // clearing
	drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace); // drawing
}
private: System::Void цветФонаToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogBg->Color; // saving old color
	colorDialogBg->ShowDialog();
	if (colorDialogBg->Color.ToArgb() == colorDialogFg->Color.ToArgb() ||
		colorDialogBg->Color.ToArgb() == colorDialogAdd->Color.ToArgb()) { // checking colors
		MessageBox::Show(this, "Одинаковые цвета (фон, фигура, дополнительный) недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogBg->Color = *old; // restoring old color if colors are identical
	}
	else { // clearing all
		clearPictureBox(pictureBoxPyr); // clearing
		delete old;

		// draws initial figure
		drawInitialPyramid();
	}
}
private: System::Void цветФигурыToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogFg->Color; // saving old color
	colorDialogFg->ShowDialog();
	if (colorDialogFg->Color.ToArgb() == colorDialogBg->Color.ToArgb() ||
		colorDialogFg->Color.ToArgb() == colorDialogAdd->Color.ToArgb()) { // checking colors
		MessageBox::Show(this, "Одинаковые цвета (фон, фигура, дополнительный) недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogFg->Color = *old; // restoring old color if colors are identical
	}
	else { // clearing all
		clearPictureBox(pictureBoxPyr);
		pen = gcnew Pen(colorDialogFg->Color); // clearing
		delete old;

		// draws initial figure
		drawInitialPyramid();
	}
}
private: System::Void дополнительныйЦветToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogAdd->Color; // saving old color
	colorDialogAdd->ShowDialog();
	if (colorDialogAdd->Color.ToArgb() == colorDialogBg->Color.ToArgb() ||
		colorDialogAdd->Color.ToArgb() == colorDialogFg->Color.ToArgb()) { // checking colors
		MessageBox::Show(this, "Одинаковые цвета (фон, фигура, дополнительный) недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogAdd->Color = *old; // restoring old color if colors are identical
	}
	else { // clearing all
		clearPictureBox(pictureBoxPyr);
		delete old;

		// draws initial figure
		drawInitialPyramid();
	}
}
private: System::Void оПрограммеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show(this, "Программа предназначена для демонстрации пирамиды и ее трансформаций.\n\n" +
		"1) Реализованы трансформации пирамиды мышью, а именно:\n" +
		"\tвращение - левой кнопкой мыши;\n" +
		"\tсдвиг - правой кнопкой мыши;\n" +
		"\tмасштабирование - колесиком мыши.\n\n" +
		"2) Также реализована трансформации пирамиды с помощью кнопок. \n" +
		"ВНИМАНИЕ! В отличие от операций мышью, с помощью кнопок можно осуществить трансформации " +
		"(вращение, сдвиг, масштабирование) как для ВСЕХ осей, так и для КАЖДОЙ оси. " +
		"Для этого следует выбрать параметр нужной оси (или \"Все\" для всех осей) в переключателе.\n" +
		"Для изменения величины изменения при транформациях кнопок следует изменить значение  " +
		"соответствующего ползунка. Действует только на трансформации при помощи кнопок.\n\n" +
		"3) Для демонстрации свойств перемножения матриц были реализованы примеры таких трансформаций, как " +
		"\"сдвиг + вращение\" и \"вращение + сдвиг\". Также реализована возможность одновременного выполнения " +
		"этих операций для демонстрации разного расположения пирамид после трансформаций. При этом пирамида, " +
		"полученная после применения операции \"вращение + сдвиг\", рисуется дополнительным цветом.\n\n" +
		"4) Реализованы ортогональная и центральная (точка z0 задается пользователем) проекции.\n\n" +
		"5) Также в программе можно менять цвет фона окон для рисования, цвет рисования пирамиды и " +
		"дополнительный цвет (для отрисовки альтернативной пирамиды в демонстрации). " +
		"Для этого следует зайти в меню \"Настройки\".\n\n"
		"Автор: Осипов Лев Игоревич, 4-й курс, группа БПИ121\n" +
		"Среда разработки: Visual Studio 2013\n" +
		"Дата: 19.10.2015", "О программе", MessageBoxButtons::OK);

}
};
}
