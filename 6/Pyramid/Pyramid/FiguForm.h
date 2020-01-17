#pragma once

namespace Figure {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/***
	Осипов Лев Игоревич, 4-й курс, группа БПИ121
	Семинар 6. Алгоритм Робертса
	Среда разработки: Visual Studio 2013
	Дата: 05.11.2015
	Реализованы различные отображения и трансформации фигур, а также алгоритм Робертса для каждой из них.
	Подробнее см. в меню "О программе".
	*/

	/// <summary>
	/// Summary for FiguForm
	/// </summary>
	public ref class FiguForm : public System::Windows::Forms::Form
	{
	public:
		FiguForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			// Creating bitmap
			bitmapFigu = gcnew Bitmap(pictureBoxFigure->Width, pictureBoxFigure->Height);
			pictureBoxFigure->Image = bitmapFigu;


			// initializing colors
			colorDialogBg->Color = Color::White;
			colorDialogFg->Color = Color::Blue;
			colorDialogAdd->Color = Color::Green;
			pen = gcnew Pen(Color::Blue);
			clearPictureBox(pictureBoxFigure);

			// getting start coordinates
			x0 = pictureBoxFigure->Width / 2;
			y0 = pictureBoxFigure->Height / 2;
			z0 = 0;

			yOffset = -100;

			// creating initial matrices
			initializeMatrices();
			labelProjType->Text = "Ортогональная проекция";
			matrixCurrProj = matrixOrtProj;

			trackBarDeltaScale->Value = 3;
			textBoxZ0->Text = "-100";
			pressedX = pressedY = 0;
			
			// draws initial figure
			drawInitialFigure();

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FiguForm()
		{
			if (components)
			{
				delete components;
			}

			if (pen) {
				delete pen;
			}

			if (bitmapFigu) {
				delete bitmapFigu;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBoxFigure;
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
		Bitmap^ bitmapFigu;

		/// <summary>
		/// Start coordinates.
		/// </summary>
		int x0;
		int y0;
		int z0;

		/// <summary>
		/// Y offset to demonstrate rotation.
		/// </summary>
		int yOffset;

		/// <summary>
		/// Pressed point coordinates.
		/// </summary>
		int pressedX;
		int pressedY;

		int state;

		/// <summary>
		/// Default vertex matrix.
		/// </summary>
		array<double, 2> ^defaultMatrixVert;

		/// <summary>
		/// Default face matrix.
		/// </summary>
		array<int, 2> ^defaultMatrixFace;

		/// <summary>
		/// Tetra vertex matrix.
		/// </summary>
		array<double, 2> ^tetraMatrixVert;

		/// <summary>
		/// Tetra face matrix.
		/// </summary>
		array<int, 2> ^tetraMatrixFace;

		/// <summary>
		/// Octa vertex matrix.
		/// </summary>
		array<double, 2> ^octaMatrixVert;

		/// <summary>
		/// Octa face matrix.
		/// </summary>
		array<int, 2> ^octaMatrixFace;


		/// <summary>
		/// Ico vertex matrix.
		/// </summary>
		array<double, 2> ^icoMatrixVert;

		/// <summary>
		/// Ico face matrix.
		/// </summary>
		array<int, 2> ^icoMatrixFace;

		/// <summary>
		/// Sphere vertex matrix.
		/// </summary>
		array<double, 2> ^sphereMatrixVert;

		/// <summary>
		/// Sphere face matrix.
		/// </summary>
		array<int, 2> ^sphereMatrixFace;

		/// <summary>
		/// Fruit vertex matrix.
		/// </summary>
		array<double, 2> ^fruitMatrixVert;

		/// <summary>
		/// Fruit face matrix.
		/// </summary>
		array<int, 2> ^fruitMatrixFace;

		/// <summary>
		/// Ellipsoid vertex matrix.
		/// </summary>
		array<double, 2> ^ellMatrixVert;

		/// <summary>
		/// Ellipsoid face matrix.
		/// </summary>
		array<int, 2> ^ellMatrixFace;

		/// <summary>
		/// Cube vertex matrix.
		/// </summary>
		array<double, 2> ^cubeMatrixVert;

		/// <summary>
		/// Cube face matrix.
		/// </summary>
		array<int, 2> ^cubeMatrixFace;


		/// <summary>
		/// Current vertex matrix.
		/// </summary>
		array<double, 2> ^matrixVert;
	private: System::Windows::Forms::RadioButton^  radioButtonX;
	private: System::Windows::Forms::RadioButton^  radioButtonY;



		/// <summary>
		/// Current face matrix.
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
private: System::Windows::Forms::Button^  buttonNewTetra;

private: System::Windows::Forms::ToolStripMenuItem^  цветФонаToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  цветФигурыToolStripMenuItem;
private: System::Windows::Forms::ColorDialog^  colorDialogBg;
private: System::Windows::Forms::ColorDialog^  colorDialogFg;
private: System::Windows::Forms::Button^  buttonMovRot;
private: System::Windows::Forms::Button^  buttonRotMov;
private: System::Windows::Forms::Button^  buttonDemo;
private: System::Windows::Forms::ToolStripMenuItem^  дополнительныйЦветToolStripMenuItem;
private: System::Windows::Forms::ColorDialog^  colorDialogAdd;
private: System::Windows::Forms::Button^  buttonNewOcta;
private: System::Windows::Forms::Button^  buttonNewSphere;
private: System::Windows::Forms::Button^  buttonNewFruit;


private: System::Windows::Forms::Button^  buttonNewIco;
private: System::Windows::Forms::Button^  buttonLoad;
private: System::Windows::Forms::Button^  buttonSave;
private: System::Windows::Forms::Button^  buttonNewEll;
private: System::Windows::Forms::Button^  buttonCCW_Par;
private: System::Windows::Forms::Button^  buttonCW_Par;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Button^  buttonFrontProj;
private: System::Windows::Forms::Button^  buttonUpProj;
private: System::Windows::Forms::Button^  buttonSideProj;
private: System::Windows::Forms::Button^  buttonNewCube;










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
		/// Draws initial Figure
		/// </summary>
		void drawInitialFigure();

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
		/// Draws a Figure.
		/// </summary>
		void drawFigure(PictureBox^ pb, array<double, 2>^ matrix, array<int, 2>^ matrixFace);

		/// <summary>
		/// Clears picture box.
		/// </summary>
		void clearPictureBox(PictureBox^ pb);

		/// <summary>
		/// Reads figure from file.
		/// </summary>
		bool readFigure();

		/// <summary>
		/// Writes figure to file.
		/// </summary>
		bool writeFigure(array<double, 2>^ matrix, array<int, 2>^ matrixFace);

		/// <summary>
		/// Draws help line
		/// </summary>
		void drawHelpLine(PictureBox^ pb);

		/// <summary>
		/// Forms shape flags (defines what flags we need to draw)
		/// </summary>
		array<bool>^ formFaceFlags(array<double, 2>^ matrixVert, array<int, 2>^ matrixFace);

		/// <summary>
		/// Calculates plane coeffs
		/// </summary>
		void calculatePlaneCoeffs(double x1, double y1, double z1, 
			double x2, double y2, double z2, 
			double x3, double y3, double z3,
			double& a, double& b, double& c, double& d);



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBoxFigure = (gcnew System::Windows::Forms::PictureBox());
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
			this->buttonNewTetra = (gcnew System::Windows::Forms::Button());
			this->colorDialogBg = (gcnew System::Windows::Forms::ColorDialog());
			this->colorDialogFg = (gcnew System::Windows::Forms::ColorDialog());
			this->buttonMovRot = (gcnew System::Windows::Forms::Button());
			this->buttonRotMov = (gcnew System::Windows::Forms::Button());
			this->buttonDemo = (gcnew System::Windows::Forms::Button());
			this->colorDialogAdd = (gcnew System::Windows::Forms::ColorDialog());
			this->buttonNewOcta = (gcnew System::Windows::Forms::Button());
			this->buttonNewSphere = (gcnew System::Windows::Forms::Button());
			this->buttonNewFruit = (gcnew System::Windows::Forms::Button());
			this->buttonNewIco = (gcnew System::Windows::Forms::Button());
			this->buttonLoad = (gcnew System::Windows::Forms::Button());
			this->buttonSave = (gcnew System::Windows::Forms::Button());
			this->buttonNewEll = (gcnew System::Windows::Forms::Button());
			this->buttonCCW_Par = (gcnew System::Windows::Forms::Button());
			this->buttonCW_Par = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->buttonFrontProj = (gcnew System::Windows::Forms::Button());
			this->buttonUpProj = (gcnew System::Windows::Forms::Button());
			this->buttonSideProj = (gcnew System::Windows::Forms::Button());
			this->buttonNewCube = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxFigure))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarDeltaScale))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBoxFigure
			// 
			this->pictureBoxFigure->BackColor = System::Drawing::Color::White;
			this->pictureBoxFigure->Location = System::Drawing::Point(12, 35);
			this->pictureBoxFigure->Name = L"pictureBoxFigure";
			this->pictureBoxFigure->Size = System::Drawing::Size(555, 555);
			this->pictureBoxFigure->TabIndex = 0;
			this->pictureBoxFigure->TabStop = false;
			this->pictureBoxFigure->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &FiguForm::pictureBoxFigure_MouseDown);
			this->pictureBoxFigure->MouseEnter += gcnew System::EventHandler(this, &FiguForm::pictureBoxFigure_MouseEnter);
			this->pictureBoxFigure->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &FiguForm::pictureBoxFigure_MouseMove);
			this->pictureBoxFigure->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &FiguForm::pictureBoxFigure_MouseWheel);
			// 
			// radioButtonX
			// 
			this->radioButtonX->AutoSize = true;
			this->radioButtonX->Location = System::Drawing::Point(623, 83);
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
			this->radioButtonY->Location = System::Drawing::Point(661, 83);
			this->radioButtonY->Name = L"radioButtonY";
			this->radioButtonY->Size = System::Drawing::Size(32, 17);
			this->radioButtonY->TabIndex = 3;
			this->radioButtonY->TabStop = true;
			this->radioButtonY->Text = L"Y";
			this->radioButtonY->UseVisualStyleBackColor = true;
			// 
			// trackBarDeltaScale
			// 
			this->trackBarDeltaScale->Location = System::Drawing::Point(710, 116);
			this->trackBarDeltaScale->Name = L"trackBarDeltaScale";
			this->trackBarDeltaScale->Size = System::Drawing::Size(104, 45);
			this->trackBarDeltaScale->TabIndex = 7;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(665, 49);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(60, 29);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Ось";
			// 
			// radioButtonZ
			// 
			this->radioButtonZ->AutoSize = true;
			this->radioButtonZ->Location = System::Drawing::Point(699, 83);
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
			this->label2->Location = System::Drawing::Point(585, 125);
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
			this->label3->Location = System::Drawing::Point(661, 173);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(71, 24);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Сдвиг";
			// 
			// buttonMoveBack
			// 
			this->buttonMoveBack->Location = System::Drawing::Point(585, 204);
			this->buttonMoveBack->Name = L"buttonMoveBack";
			this->buttonMoveBack->Size = System::Drawing::Size(105, 23);
			this->buttonMoveBack->TabIndex = 9;
			this->buttonMoveBack->Text = L"Назад";
			this->buttonMoveBack->UseVisualStyleBackColor = true;
			this->buttonMoveBack->Click += gcnew System::EventHandler(this, &FiguForm::buttonMoveBack_Click);
			// 
			// buttonMoveForw
			// 
			this->buttonMoveForw->Location = System::Drawing::Point(709, 204);
			this->buttonMoveForw->Name = L"buttonMoveForw";
			this->buttonMoveForw->Size = System::Drawing::Size(105, 23);
			this->buttonMoveForw->TabIndex = 10;
			this->buttonMoveForw->Text = L"Вперед";
			this->buttonMoveForw->UseVisualStyleBackColor = true;
			this->buttonMoveForw->Click += gcnew System::EventHandler(this, &FiguForm::buttonMoveForw_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(645, 242);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(108, 24);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Вращение";
			// 
			// buttonCW
			// 
			this->buttonCW->Location = System::Drawing::Point(708, 271);
			this->buttonCW->Name = L"buttonCW";
			this->buttonCW->Size = System::Drawing::Size(105, 23);
			this->buttonCW->TabIndex = 13;
			this->buttonCW->Text = L"По часовой";
			this->buttonCW->UseVisualStyleBackColor = true;
			this->buttonCW->Click += gcnew System::EventHandler(this, &FiguForm::buttonCW_Click);
			// 
			// buttonCCW
			// 
			this->buttonCCW->Location = System::Drawing::Point(588, 271);
			this->buttonCCW->Name = L"buttonCCW";
			this->buttonCCW->Size = System::Drawing::Size(105, 23);
			this->buttonCCW->TabIndex = 12;
			this->buttonCCW->Text = L"Против часовой";
			this->buttonCCW->UseVisualStyleBackColor = true;
			this->buttonCCW->Click += gcnew System::EventHandler(this, &FiguForm::buttonCCW_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(649, 310);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(98, 24);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Масштаб";
			// 
			// buttonScaleSmall
			// 
			this->buttonScaleSmall->Location = System::Drawing::Point(588, 341);
			this->buttonScaleSmall->Name = L"buttonScaleSmall";
			this->buttonScaleSmall->Size = System::Drawing::Size(105, 23);
			this->buttonScaleSmall->TabIndex = 15;
			this->buttonScaleSmall->Text = L"Меньше";
			this->buttonScaleSmall->UseVisualStyleBackColor = true;
			this->buttonScaleSmall->Click += gcnew System::EventHandler(this, &FiguForm::buttonScaleSmall_Click);
			// 
			// buttonScaleBig
			// 
			this->buttonScaleBig->Location = System::Drawing::Point(708, 341);
			this->buttonScaleBig->Name = L"buttonScaleBig";
			this->buttonScaleBig->Size = System::Drawing::Size(105, 23);
			this->buttonScaleBig->TabIndex = 16;
			this->buttonScaleBig->Text = L"Больше";
			this->buttonScaleBig->UseVisualStyleBackColor = true;
			this->buttonScaleBig->Click += gcnew System::EventHandler(this, &FiguForm::buttonScaleBig_Click);
			// 
			// buttonOrtProj
			// 
			this->buttonOrtProj->Location = System::Drawing::Point(585, 482);
			this->buttonOrtProj->Name = L"buttonOrtProj";
			this->buttonOrtProj->Size = System::Drawing::Size(183, 23);
			this->buttonOrtProj->TabIndex = 17;
			this->buttonOrtProj->Text = L"Ортогональная проекция";
			this->buttonOrtProj->UseVisualStyleBackColor = true;
			this->buttonOrtProj->Visible = false;
			this->buttonOrtProj->Click += gcnew System::EventHandler(this, &FiguForm::buttonOrtProj_Click);
			// 
			// buttonCentProj
			// 
			this->buttonCentProj->Location = System::Drawing::Point(585, 511);
			this->buttonCentProj->Name = L"buttonCentProj";
			this->buttonCentProj->Size = System::Drawing::Size(183, 23);
			this->buttonCentProj->TabIndex = 18;
			this->buttonCentProj->Text = L"Центральная проекция, z0:";
			this->buttonCentProj->UseVisualStyleBackColor = true;
			this->buttonCentProj->Visible = false;
			this->buttonCentProj->Click += gcnew System::EventHandler(this, &FiguForm::buttonCentProj_Click);
			// 
			// labelProjType
			// 
			this->labelProjType->AutoSize = true;
			this->labelProjType->Location = System::Drawing::Point(221, 595);
			this->labelProjType->Name = L"labelProjType";
			this->labelProjType->Size = System::Drawing::Size(136, 13);
			this->labelProjType->TabIndex = 20;
			this->labelProjType->Text = L"Ортогональная проекция";
			// 
			// textBoxZ0
			// 
			this->textBoxZ0->Location = System::Drawing::Point(773, 511);
			this->textBoxZ0->Name = L"textBoxZ0";
			this->textBoxZ0->Size = System::Drawing::Size(40, 20);
			this->textBoxZ0->TabIndex = 19;
			this->textBoxZ0->Visible = false;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->оПрограммеToolStripMenuItem,
					this->настройкиToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1037, 24);
			this->menuStrip1->TabIndex = 20;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(94, 20);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
			this->оПрограммеToolStripMenuItem->Click += gcnew System::EventHandler(this, &FiguForm::оПрограммеToolStripMenuItem_Click);
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
			this->цветФонаToolStripMenuItem->Click += gcnew System::EventHandler(this, &FiguForm::цветФонаToolStripMenuItem_Click);
			// 
			// цветФигурыToolStripMenuItem
			// 
			this->цветФигурыToolStripMenuItem->Name = L"цветФигурыToolStripMenuItem";
			this->цветФигурыToolStripMenuItem->Size = System::Drawing::Size(198, 22);
			this->цветФигурыToolStripMenuItem->Text = L"Цвет фигуры";
			this->цветФигурыToolStripMenuItem->Click += gcnew System::EventHandler(this, &FiguForm::цветФигурыToolStripMenuItem_Click);
			// 
			// дополнительныйЦветToolStripMenuItem
			// 
			this->дополнительныйЦветToolStripMenuItem->Name = L"дополнительныйЦветToolStripMenuItem";
			this->дополнительныйЦветToolStripMenuItem->Size = System::Drawing::Size(198, 22);
			this->дополнительныйЦветToolStripMenuItem->Text = L"Дополнительный цвет";
			this->дополнительныйЦветToolStripMenuItem->Click += gcnew System::EventHandler(this, &FiguForm::дополнительныйЦветToolStripMenuItem_Click);
			// 
			// radioButtonAll
			// 
			this->radioButtonAll->AutoSize = true;
			this->radioButtonAll->Location = System::Drawing::Point(737, 83);
			this->radioButtonAll->Name = L"radioButtonAll";
			this->radioButtonAll->Size = System::Drawing::Size(44, 17);
			this->radioButtonAll->TabIndex = 5;
			this->radioButtonAll->TabStop = true;
			this->radioButtonAll->Text = L"Все";
			this->radioButtonAll->UseVisualStyleBackColor = true;
			// 
			// buttonNewTetra
			// 
			this->buttonNewTetra->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonNewTetra->Location = System::Drawing::Point(860, 35);
			this->buttonNewTetra->Name = L"buttonNewTetra";
			this->buttonNewTetra->Size = System::Drawing::Size(172, 34);
			this->buttonNewTetra->TabIndex = 21;
			this->buttonNewTetra->Text = L"Новый тетраэдр";
			this->buttonNewTetra->UseVisualStyleBackColor = true;
			this->buttonNewTetra->Click += gcnew System::EventHandler(this, &FiguForm::buttonNewTetra_Click);
			// 
			// buttonMovRot
			// 
			this->buttonMovRot->Location = System::Drawing::Point(408, 623);
			this->buttonMovRot->Name = L"buttonMovRot";
			this->buttonMovRot->Size = System::Drawing::Size(143, 23);
			this->buttonMovRot->TabIndex = 22;
			this->buttonMovRot->Text = L"Сдвиг + вращение";
			this->buttonMovRot->UseVisualStyleBackColor = true;
			this->buttonMovRot->Click += gcnew System::EventHandler(this, &FiguForm::buttonMovRot_Click);
			// 
			// buttonRotMov
			// 
			this->buttonRotMov->Location = System::Drawing::Point(408, 595);
			this->buttonRotMov->Name = L"buttonRotMov";
			this->buttonRotMov->Size = System::Drawing::Size(143, 23);
			this->buttonRotMov->TabIndex = 23;
			this->buttonRotMov->Text = L"Вращение + сдвиг";
			this->buttonRotMov->UseVisualStyleBackColor = true;
			this->buttonRotMov->Click += gcnew System::EventHandler(this, &FiguForm::buttonRotMov_Click);
			// 
			// buttonDemo
			// 
			this->buttonDemo->Location = System::Drawing::Point(408, 652);
			this->buttonDemo->Name = L"buttonDemo";
			this->buttonDemo->Size = System::Drawing::Size(143, 23);
			this->buttonDemo->TabIndex = 24;
			this->buttonDemo->Text = L"Одновременно";
			this->buttonDemo->UseVisualStyleBackColor = true;
			this->buttonDemo->Click += gcnew System::EventHandler(this, &FiguForm::buttonDemo_Click);
			// 
			// buttonNewOcta
			// 
			this->buttonNewOcta->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonNewOcta->Location = System::Drawing::Point(860, 75);
			this->buttonNewOcta->Name = L"buttonNewOcta";
			this->buttonNewOcta->Size = System::Drawing::Size(172, 34);
			this->buttonNewOcta->TabIndex = 25;
			this->buttonNewOcta->Text = L"Новый октаэдр";
			this->buttonNewOcta->UseVisualStyleBackColor = true;
			this->buttonNewOcta->Click += gcnew System::EventHandler(this, &FiguForm::buttonNewOcta_Click);
			// 
			// buttonNewSphere
			// 
			this->buttonNewSphere->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonNewSphere->Location = System::Drawing::Point(860, 156);
			this->buttonNewSphere->Name = L"buttonNewSphere";
			this->buttonNewSphere->Size = System::Drawing::Size(172, 34);
			this->buttonNewSphere->TabIndex = 26;
			this->buttonNewSphere->Text = L"Новая сфера";
			this->buttonNewSphere->UseVisualStyleBackColor = true;
			this->buttonNewSphere->Click += gcnew System::EventHandler(this, &FiguForm::buttonNewSphere_Click);
			// 
			// buttonNewFruit
			// 
			this->buttonNewFruit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonNewFruit->Location = System::Drawing::Point(860, 236);
			this->buttonNewFruit->Name = L"buttonNewFruit";
			this->buttonNewFruit->Size = System::Drawing::Size(172, 34);
			this->buttonNewFruit->TabIndex = 27;
			this->buttonNewFruit->Text = L"Новый фрукт";
			this->buttonNewFruit->UseVisualStyleBackColor = true;
			this->buttonNewFruit->Click += gcnew System::EventHandler(this, &FiguForm::buttonNewFruit_Click);
			// 
			// buttonNewIco
			// 
			this->buttonNewIco->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonNewIco->Location = System::Drawing::Point(860, 116);
			this->buttonNewIco->Name = L"buttonNewIco";
			this->buttonNewIco->Size = System::Drawing::Size(172, 34);
			this->buttonNewIco->TabIndex = 30;
			this->buttonNewIco->Text = L"Новый икосаэдр";
			this->buttonNewIco->UseVisualStyleBackColor = true;
			this->buttonNewIco->Click += gcnew System::EventHandler(this, &FiguForm::buttonNewIco_Click);
			// 
			// buttonLoad
			// 
			this->buttonLoad->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonLoad->Location = System::Drawing::Point(860, 554);
			this->buttonLoad->Name = L"buttonLoad";
			this->buttonLoad->Size = System::Drawing::Size(172, 54);
			this->buttonLoad->TabIndex = 31;
			this->buttonLoad->Text = L"Загрузить фигуру из файла";
			this->buttonLoad->UseVisualStyleBackColor = true;
			this->buttonLoad->Click += gcnew System::EventHandler(this, &FiguForm::buttonLoad_Click);
			// 
			// buttonSave
			// 
			this->buttonSave->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonSave->Location = System::Drawing::Point(860, 615);
			this->buttonSave->Name = L"buttonSave";
			this->buttonSave->Size = System::Drawing::Size(172, 54);
			this->buttonSave->TabIndex = 32;
			this->buttonSave->Text = L"Сохранить фигуру в файл";
			this->buttonSave->UseVisualStyleBackColor = true;
			this->buttonSave->Click += gcnew System::EventHandler(this, &FiguForm::buttonSave_Click);
			// 
			// buttonNewEll
			// 
			this->buttonNewEll->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonNewEll->Location = System::Drawing::Point(860, 196);
			this->buttonNewEll->Name = L"buttonNewEll";
			this->buttonNewEll->Size = System::Drawing::Size(172, 34);
			this->buttonNewEll->TabIndex = 33;
			this->buttonNewEll->Text = L"Новый эллипсоид";
			this->buttonNewEll->UseVisualStyleBackColor = true;
			this->buttonNewEll->Click += gcnew System::EventHandler(this, &FiguForm::buttonNewEll_Click);
			// 
			// buttonCCW_Par
			// 
			this->buttonCCW_Par->Location = System::Drawing::Point(588, 597);
			this->buttonCCW_Par->Name = L"buttonCCW_Par";
			this->buttonCCW_Par->Size = System::Drawing::Size(105, 23);
			this->buttonCCW_Par->TabIndex = 34;
			this->buttonCCW_Par->Text = L"Против часовой";
			this->buttonCCW_Par->UseVisualStyleBackColor = true;
			this->buttonCCW_Par->Click += gcnew System::EventHandler(this, &FiguForm::buttonCCW_Par_Click);
			// 
			// buttonCW_Par
			// 
			this->buttonCW_Par->Location = System::Drawing::Point(708, 597);
			this->buttonCW_Par->Name = L"buttonCW_Par";
			this->buttonCW_Par->Size = System::Drawing::Size(105, 23);
			this->buttonCW_Par->TabIndex = 35;
			this->buttonCW_Par->Text = L"По часовой";
			this->buttonCW_Par->UseVisualStyleBackColor = true;
			this->buttonCW_Par->Click += gcnew System::EventHandler(this, &FiguForm::buttonCW_Par_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(587, 554);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(232, 20);
			this->label6->TabIndex = 36;
			this->label6->Text = L"Вращение вокруг прямой, ";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(581, 574);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(250, 20);
			this->label7->TabIndex = 37;
			this->label7->Text = L"параллельной оси х (у=-100)";
			// 
			// buttonFrontProj
			// 
			this->buttonFrontProj->Location = System::Drawing::Point(585, 383);
			this->buttonFrontProj->Name = L"buttonFrontProj";
			this->buttonFrontProj->Size = System::Drawing::Size(183, 23);
			this->buttonFrontProj->TabIndex = 38;
			this->buttonFrontProj->Text = L"Вид спереди";
			this->buttonFrontProj->UseVisualStyleBackColor = true;
			this->buttonFrontProj->Click += gcnew System::EventHandler(this, &FiguForm::buttonFrontProj_Click);
			// 
			// buttonUpProj
			// 
			this->buttonUpProj->Location = System::Drawing::Point(585, 412);
			this->buttonUpProj->Name = L"buttonUpProj";
			this->buttonUpProj->Size = System::Drawing::Size(183, 23);
			this->buttonUpProj->TabIndex = 39;
			this->buttonUpProj->Text = L"Вид сверху";
			this->buttonUpProj->UseVisualStyleBackColor = true;
			this->buttonUpProj->Click += gcnew System::EventHandler(this, &FiguForm::buttonUpProj_Click);
			// 
			// buttonSideProj
			// 
			this->buttonSideProj->Location = System::Drawing::Point(585, 441);
			this->buttonSideProj->Name = L"buttonSideProj";
			this->buttonSideProj->Size = System::Drawing::Size(183, 23);
			this->buttonSideProj->TabIndex = 40;
			this->buttonSideProj->Text = L"Вид сбоку";
			this->buttonSideProj->UseVisualStyleBackColor = true;
			this->buttonSideProj->Click += gcnew System::EventHandler(this, &FiguForm::buttonSideProj_Click);
			// 
			// buttonNewCube
			// 
			this->buttonNewCube->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonNewCube->Location = System::Drawing::Point(860, 276);
			this->buttonNewCube->Name = L"buttonNewCube";
			this->buttonNewCube->Size = System::Drawing::Size(172, 34);
			this->buttonNewCube->TabIndex = 41;
			this->buttonNewCube->Text = L"Новый куб";
			this->buttonNewCube->UseVisualStyleBackColor = true;
			this->buttonNewCube->Click += gcnew System::EventHandler(this, &FiguForm::buttonNewCube_Click);
			// 
			// FiguForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::MediumPurple;
			this->ClientSize = System::Drawing::Size(1037, 677);
			this->Controls->Add(this->buttonNewCube);
			this->Controls->Add(this->buttonSideProj);
			this->Controls->Add(this->buttonUpProj);
			this->Controls->Add(this->buttonFrontProj);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->buttonCW_Par);
			this->Controls->Add(this->buttonCCW_Par);
			this->Controls->Add(this->buttonNewEll);
			this->Controls->Add(this->buttonSave);
			this->Controls->Add(this->buttonLoad);
			this->Controls->Add(this->buttonNewIco);
			this->Controls->Add(this->buttonNewFruit);
			this->Controls->Add(this->buttonNewSphere);
			this->Controls->Add(this->buttonNewOcta);
			this->Controls->Add(this->buttonDemo);
			this->Controls->Add(this->buttonRotMov);
			this->Controls->Add(this->buttonMovRot);
			this->Controls->Add(this->buttonNewTetra);
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
			this->Controls->Add(this->pictureBoxFigure);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"FiguForm";
			this->Text = L"Алгоритм Робертса";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxFigure))->EndInit();
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

	clearPictureBox(pictureBoxFigure); // clearing
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
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

	clearPictureBox(pictureBoxFigure); // clearing
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
}
private: System::Void buttonMoveBack_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 0;
	double deltaY = 0;
	double deltaZ = 0;

	decrementDeltas(deltaX, deltaY, deltaZ, trackBarDeltaScale->Value); // decrementing the current delta

	matrixVert = matrixComposition(matrixVert, formMoveMatrix(deltaX, deltaY, deltaZ)); // moving

	clearPictureBox(pictureBoxFigure); // clearing
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
}
private: System::Void buttonMoveForw_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 0;
	double deltaY = 0;
	double deltaZ = 0;

	incrementDeltas(deltaX, deltaY, deltaZ, trackBarDeltaScale->Value); // incrementing the current delta

	matrixVert = matrixComposition(matrixVert, formMoveMatrix(deltaX, deltaY, deltaZ)); // moving

	clearPictureBox(pictureBoxFigure); // clearing
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
}
private: System::Void buttonCCW_Click(System::Object^  sender, System::EventArgs^  e) {
	
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
	
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

	matrixVert = matrixComposition(matrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving

	clearPictureBox(pictureBoxFigure); // clearing
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
}
private: System::Void buttonCW_Click(System::Object^  sender, System::EventArgs^  e) {

	matrixVert = matrixComposition(matrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving

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

	matrixVert = matrixComposition(matrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving

	clearPictureBox(pictureBoxFigure); // clearing
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
}
private: System::Void buttonScaleSmall_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 1;
	double deltaY = 1;
	double deltaZ = 1;

	decrementDeltas(deltaX, deltaY, deltaZ, (double)trackBarDeltaScale->Value / 20); // decrementing the current delta

	matrixVert = matrixComposition(matrixVert, formScaleMatrix(deltaX, deltaY, deltaZ, 1)); // scaling

	clearPictureBox(pictureBoxFigure); // clearing
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
}
private: System::Void buttonScaleBig_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 1;
	double deltaY = 1;
	double deltaZ = 1;

	incrementDeltas(deltaX, deltaY, deltaZ, (double)trackBarDeltaScale->Value / 20); // incrementing the current delta

	matrixVert = matrixComposition(matrixVert, formScaleMatrix(deltaX, deltaY, deltaZ, 1)); // scaling

	clearPictureBox(pictureBoxFigure); // clearing
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
}
private: System::Void buttonMovRot_Click(System::Object^  sender, System::EventArgs^  e) {
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(3, 0, 0)); // moving
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
	matrixVert = matrixComposition(matrixVert, formYRotateMatrix(0.3)); // rotating
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
	clearPictureBox(pictureBoxFigure); // clearing
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
}
private: System::Void buttonRotMov_Click(System::Object^  sender, System::EventArgs^  e) {
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
	matrixVert = matrixComposition(matrixVert, formYRotateMatrix(0.3)); // rotating
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(3, 0, 0)); // moving
	clearPictureBox(pictureBoxFigure); // clearing
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
}
private: System::Void buttonDemo_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxFigure); // clearing
	
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(3, 0, 0)); // moving
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
	matrixVert = matrixComposition(matrixVert, formYRotateMatrix(0.3)); // rotating
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing 1
	
	array<double, 2>^ matrixCopy = gcnew array<double, 2>(matrixVert->GetLength(0), matrixVert->GetLength(1));
	Array::Copy(matrixVert, 0, matrixCopy, 0, matrixVert->GetLength(0) * matrixVert->GetLength(1)); // copying 
	pen = gcnew Pen(colorDialogAdd->Color); // changing color
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
	matrixCopy = matrixComposition(matrixCopy, formYRotateMatrix(0.3)); // rotating
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
	matrixCopy = matrixComposition(matrixCopy, formMoveMatrix(3, 0, 0)); // moving
	drawFigure(pictureBoxFigure, matrixCopy, matrixFace); // drawing 2
	
	pen = gcnew Pen(colorDialogFg->Color); // restoring color
}
private: System::Void pictureBoxFigure_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	// saving coords
	pressedX = e->X;
	pressedY = e->Y;
}
private: System::Void pictureBoxFigure_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == Windows::Forms::MouseButtons::Right) { // right - moving
		matrixVert = matrixComposition(matrixVert, formMoveMatrix(e->X - pressedX, e->Y-pressedY, 0)); // moving
		clearPictureBox(pictureBoxFigure); // clearing
		drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
	}
	if (e->Button == Windows::Forms::MouseButtons::Left) { // left - rotating

		matrixVert = matrixComposition(matrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving

		if (e->X - pressedX != 0) { // if x changed
			matrixVert = matrixComposition(matrixVert, formYRotateMatrix((e->X - pressedX) / 100.0)); // rotating x
		}
		if (e->Y - pressedY != 0) { // if y changed
			matrixVert = matrixComposition(matrixVert, formXRotateMatrix((e->Y - pressedY) / 100.0)); // rotating y
		}

		matrixVert = matrixComposition(matrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
		
		clearPictureBox(pictureBoxFigure); // clearing
		drawFigure(pictureBoxFigure, matrixVert, matrixFace);
	}
	// saving coords
	pressedX = e->X;
	pressedY = e->Y;
}
private: System::Void pictureBoxFigure_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
	pictureBoxFigure->Focus();
}
private: System::Void pictureBoxFigure_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
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

	clearPictureBox(pictureBoxFigure); // clearing
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
}
private: System::Void buttonNewTetra_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxFigure); // clearing
	defaultMatrixVert = tetraMatrixVert; // setting tetra
	defaultMatrixFace = tetraMatrixFace; // setting tetra
	state = 0;
	// draws initial figure
	drawInitialFigure();
}
private: System::Void buttonNewOcta_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxFigure); // clearing
	defaultMatrixVert = octaMatrixVert; // setting octa
	defaultMatrixFace = octaMatrixFace; // setting octa
	state = -1;
	// draws initial figure
	drawInitialFigure();
}
private: System::Void buttonNewIco_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxFigure); // clearing
	defaultMatrixVert = icoMatrixVert; // setting ico
	defaultMatrixFace = icoMatrixFace; // setting ico
	state = 1;
	// draws initial figure
	drawInitialFigure();
}
private: System::Void buttonNewSphere_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxFigure); // clearing
	defaultMatrixVert = sphereMatrixVert; // setting sphere
	defaultMatrixFace = sphereMatrixFace; // setting sphere
	state = -1;
	// draws initial figure
	drawInitialFigure();
}
private: System::Void buttonNewFruit_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxFigure); // clearing
	defaultMatrixVert = fruitMatrixVert; // setting fruit
	defaultMatrixFace = fruitMatrixFace; // setting fruit
	state = -1;
	// draws initial figure
	drawInitialFigure();
}
private: System::Void buttonNewEll_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxFigure); // clearing
	defaultMatrixVert = ellMatrixVert; // setting ellipsoid
	defaultMatrixFace = ellMatrixFace; // setting ellipsoid
	state = -1;
	// draws initial figure
	drawInitialFigure();
}
private: System::Void buttonNewCube_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxFigure); // clearing
	defaultMatrixVert = cubeMatrixVert; // setting tor
	defaultMatrixFace = cubeMatrixFace; // setting tor
	state = -1;
	// draws initial figure
	drawInitialFigure();
}
private: System::Void buttonLoad_Click(System::Object^  sender, System::EventArgs^  e) {
	if (readFigure()) { // reading
		clearPictureBox(pictureBoxFigure); // clearing
		// draws initial figure
		drawInitialFigure();
	}
	else {
		MessageBox::Show(this, "Файл input.txt не найден или содержит неверную информацию!", "Ошибка", MessageBoxButtons::OK);
	}
}
private: System::Void buttonSave_Click(System::Object^  sender, System::EventArgs^  e) {
	if (writeFigure(matrixVert, matrixFace)) { // writing
		MessageBox::Show(this, "Фигура успешно сохранена в файл output.txt!", "ОК", MessageBoxButtons::OK);
	}
	else {
		MessageBox::Show(this, "Ошибка при записи в файл!", "Ошибка", MessageBoxButtons::OK);
	}
}
private: System::Void buttonCCW_Par_Click(System::Object^  sender, System::EventArgs^  e) {
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -(pictureBoxFigure->Height / 2 + yOffset), 0)); // moving
	matrixVert = matrixComposition(matrixVert, formXRotateMatrix(-0.3)); // rotating
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2 + yOffset, 0)); // moving
	clearPictureBox(pictureBoxFigure); // clearing
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
	drawHelpLine(pictureBoxFigure); //draw line
}
private: System::Void buttonCW_Par_Click(System::Object^  sender, System::EventArgs^  e) {
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -(pictureBoxFigure->Height / 2 + yOffset), 0)); // moving
	matrixVert = matrixComposition(matrixVert, formXRotateMatrix(0.3)); // rotating
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2 + yOffset, 0)); // moving
	clearPictureBox(pictureBoxFigure); // clearing
	drawFigure(pictureBoxFigure, matrixVert, matrixFace); // drawing
	drawHelpLine(pictureBoxFigure); //draw line
}
private: System::Void buttonFrontProj_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxFigure); // clearing

	// restoring values
	matrixVert = defaultMatrixVert;
	matrixFace = defaultMatrixFace;
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
	if (state == 0) { // differently created figures need different rotation. tetra now
		matrixVert = matrixComposition(matrixVert, formXRotateMatrix(-Math::PI / 2)); // rotating X
	}
	else if (state == 1) { // ico

	}
	else { // default
		matrixVert = matrixComposition(matrixVert, formXRotateMatrix(Math::PI / 2)); // rotating X
	}
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
	// drawing start Figure
	drawFigure(pictureBoxFigure, matrixVert, matrixFace);
}
private: System::Void buttonUpProj_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxFigure); // clearing

	// restoring values
	matrixVert = defaultMatrixVert;
	matrixFace = defaultMatrixFace;
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
	if (state == 0) { // differently created figures need different rotation. tetra now
	}
	else if (state == 1) { // ico
		matrixVert = matrixComposition(matrixVert, formXRotateMatrix(Math::PI / 2)); // rotating X
	}
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
	drawFigure(pictureBoxFigure, matrixVert, matrixFace);
}
private: System::Void buttonSideProj_Click(System::Object^  sender, System::EventArgs^  e) {
	clearPictureBox(pictureBoxFigure); // clearing

	// restoring values
	matrixVert = defaultMatrixVert;
	matrixFace = defaultMatrixFace;
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
	if (state == 0) { // differently created figures need different rotation. tetra now
		matrixVert = matrixComposition(matrixVert, formXRotateMatrix(-Math::PI / 2)); // rotating X
		matrixVert = matrixComposition(matrixVert, formYRotateMatrix(Math::PI / 2)); // rotating Y
	}
	else if (state == 1) { // ico
		matrixVert = matrixComposition(matrixVert, formYRotateMatrix(Math::PI / 2)); // rotating Y
	}
	else { // default
		matrixVert = matrixComposition(matrixVert, formXRotateMatrix(Math::PI / 2)); // rotating X
		matrixVert = matrixComposition(matrixVert, formYRotateMatrix(Math::PI / 2)); // rotating Y
	}
	matrixVert = matrixComposition(matrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
	// drawing start Figure
	drawFigure(pictureBoxFigure, matrixVert, matrixFace);
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
		clearPictureBox(pictureBoxFigure); // clearing
		delete old;

		// draws initial figure
		drawInitialFigure();
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
		clearPictureBox(pictureBoxFigure);
		pen = gcnew Pen(colorDialogFg->Color); // clearing
		delete old;

		// draws initial figure
		drawInitialFigure();
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
		clearPictureBox(pictureBoxFigure);
		delete old;

		// draws initial figure
		drawInitialFigure();
	}
}
private: System::Void оПрограммеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show(this, "Программа предназначена для демонстрации различных фигур и их трансформаций. Также для каждой из фигур реализован алгоритм Робертса.\n\n" +
		"1) Реализованы такие фигуры, как: \n" +
		"\tтетраэдр, октаэдр, икосаэдр;\n" +
		"\tсфера, эллипсоид, фрукт;\n" +
		"\tкуб (такие грани у куба были выбраны не случайно)\n\n" +
		"2) Реализованы трансформации мышью, а именно:\n" +
		"\tвращение - левой кнопкой мыши;\n" +
		"\tсдвиг - правой кнопкой мыши;\n" +
		"\tмасштабирование - колесиком мыши.\n\n" +
		"3) Также реализованы трансформации с помощью кнопок. \n" +
		"ВНИМАНИЕ! В отличие от операций мышью, с помощью кнопок можно осуществить трансформации " +
		"(вращение, сдвиг, масштабирование) как для ВСЕХ осей, так и для КАЖДОЙ оси. " +
		"Для этого следует выбрать параметр нужной оси (или \"Все\" для всех осей) в переключателе.\n" +
		"Для изменения величины изменения при транформациях кнопок следует изменить значение  " +
		"соответствующего ползунка. Действует только на трансформации при помощи кнопок.\n\n" +
		"4) Как и в прошлый раз, реализованы комплексные операции (сдвиг+вращение, вращение+сдвиг, одновременный режим).\n\n" +
		"5) Реализовано вращение вокруг оси, параллельной оси х (ось при вращении выделяется дополнительным цветом).\n\n" + 
		"6) Реализованы ортографические проекции (вид спереди, вид сверху, вид сбоку).\n\n" +
		"7) В программе можно менять цвет фона окон для рисования, цвет рисования фигур и " +
		"дополнительный цвет (для отрисовки альтернативной фигуры в демонстрации и линии вращения, параллельной оси х). " +
		"Для этого следует зайти в меню \"Настройки\".\n\n" +
		"8) Реализована запись фигуры в файл output.txt и чтение фигуры из файла input.txt. Для этого следует воспользоваться соответствующими кнопками.\n\n"
		"Автор: Осипов Лев Игоревич, 4-й курс, группа БПИ121\n" +
		"Среда разработки: Visual Studio 2013\n" +
		"Дата: 05.11.2015", "О программе", MessageBoxButtons::OK);

}
};
}
