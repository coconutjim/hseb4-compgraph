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
	Семинар 7. Z-буфер
	Среда разработки: Visual Studio 2013
	Дата: 16.11.2015
	Реализованы алгоритм z-буфера, отрисовка самого z-буфера и плоская закраска объектов.
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

			// Creating bitmap for figures
			bitmapFigu = gcnew Bitmap(pictureBoxFigure->Width, pictureBoxFigure->Height);
			pictureBoxFigure->Image = bitmapFigu;

			// Creating bitmap for z-buffer
			bitmapZBuff = gcnew Bitmap(pictureBoxZBuffer->Width, pictureBoxZBuffer->Height);
			pictureBoxZBuffer->Image = bitmapZBuff;


			// initializing colors
			colorDialogBg->Color = Color::White;
			colorDialogTor1->Color = Color::Red;
			colorDialogTor2->Color = Color::Blue;
			colorDialogTor3->Color = Color::Green;

			// getting start coordinates
			x0 = pictureBoxFigure->Width / 2;
			y0 = pictureBoxFigure->Height / 2;
			z0 = 0;

			// creating initial matrices
			initializeMatrices();
			matrixCurrProj = matrixOrtProj;

			trackBarDeltaScale->Value = 19;
			pressedX = pressedY = 0;
			
			// preparing scene
			prepareScene();

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

			if (bitmapFigu) {
				delete bitmapFigu;
			}

			if (bitmapZBuff) {
				delete bitmapZBuff;
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
		/// State (what figure to change). 0 -sphere, 1 - tor1, 2 - tor2
		/// </summary>
		int state;

		/// <summary>
		/// Bitmap to draw in.
		/// </summary>
		Bitmap^ bitmapFigu;

		/// <summary>
		/// Bitmap for z-buffer.
		/// </summary>
		Bitmap^ bitmapZBuff;

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
		/// Z-buffer
		/// </summary>
		array<double, 2>^ zBuffer;

		/// <summary>
		/// Sphere vertex matrix.
		/// </summary>
		array<double, 2>^ sphereMatrixVert;


		/// <summary>
		/// Sphere face matrix.
		/// </summary>
		array<int, 2>^ sphereMatrixFace;

		/// <summary>
		/// Tor vertex matrix.
		/// </summary>
		array<double, 2>^ torMatrixVert;

		/// <summary>
		/// Vertex matrix for first tor.
		/// </summary>
		array<double, 2>^ tor1MatrixVert;

		/// <summary>
		/// Vertex matrix for second tor.
		/// </summary>
		array<double, 2>^ tor2MatrixVert;

		/// <summary>
		/// Vertex matrix for third tor
		/// </summary>
		array<double, 2>^ tor3MatrixVert;

		/// <summary>
		/// Tor face matrix.
		/// </summary>
		array<int, 2>^ torMatrixFace;


	private: System::Windows::Forms::RadioButton^  radioButtonX;
	private: System::Windows::Forms::RadioButton^  radioButtonY;





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







private: System::Windows::Forms::MenuStrip^  menuStrip1;
private: System::Windows::Forms::ToolStripMenuItem^  оПрограммеToolStripMenuItem;

private: System::Windows::Forms::RadioButton^  radioButtonAll;




private: System::Windows::Forms::ColorDialog^  colorDialogBg;
private: System::Windows::Forms::ColorDialog^  colorDialogTor1;
private: System::Windows::Forms::ColorDialog^  colorDialogTor2;



















private: System::Windows::Forms::Button^  buttonNewScene;

private: System::Windows::Forms::Button^  buttonChangeTor1;
private: System::Windows::Forms::Button^  buttonChangeTor2;
private: System::Windows::Forms::PictureBox^  pictureBoxZBuffer;
private: System::Windows::Forms::Button^  buttonChangeTor3;
private: System::Windows::Forms::ToolStripMenuItem^  цветаToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  фонToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  тор1ToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  тор2ToolStripMenuItem;

private: System::Windows::Forms::ColorDialog^  colorDialogTor3;
private: System::Windows::Forms::ToolStripMenuItem^  тор3ToolStripMenuItem;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  labelWhatTor;



















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
		/// Prepares scene
		/// </summary>
		void prepareScene();

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
		void drawFigure(array<double, 2>^ matrixVert, array<int, 2>^ matrixFace, Color^ color);

		/// <summary>
		/// Defines color for the current face.
		/// </summary>
		Color^ defineColorForFace(int index, array<double, 2>^ matrixVert, array<int, 2>^ matrixFace, Color^ color);

		/// <summary>
		/// Calculates vector composition.
		/// </summary>
		void calculateVectorComposition(double x1, double y1, double z1,
			double x2, double y2, double z2,
			double x3, double y3, double z3,
			double& xRes, double& yRes, double& zRes);

		/// <summary>
		/// Changes point location.
		/// </summary>
		void changePointLocation(double& x1, double& y1, double& z1,
			double& x2, double& y2, double& z2,
			double& x3, double& y3, double& z3);

		/// <summary>
		/// Swaps two doubles.
		/// </summary>
		void swap(double& x, double& y);

		/// <summary>
		/// Draws scene.
		/// </summary>
		void drawScene();

		/// <summary>
		/// Clears picture box.
		/// </summary>
		void clearPictureBox(PictureBox^ pb, Color^ color);


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
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->фонToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->тор1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->тор2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->тор3ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->radioButtonAll = (gcnew System::Windows::Forms::RadioButton());
			this->colorDialogBg = (gcnew System::Windows::Forms::ColorDialog());
			this->colorDialogTor1 = (gcnew System::Windows::Forms::ColorDialog());
			this->colorDialogTor2 = (gcnew System::Windows::Forms::ColorDialog());
			this->buttonNewScene = (gcnew System::Windows::Forms::Button());
			this->buttonChangeTor1 = (gcnew System::Windows::Forms::Button());
			this->buttonChangeTor2 = (gcnew System::Windows::Forms::Button());
			this->pictureBoxZBuffer = (gcnew System::Windows::Forms::PictureBox());
			this->buttonChangeTor3 = (gcnew System::Windows::Forms::Button());
			this->colorDialogTor3 = (gcnew System::Windows::Forms::ColorDialog());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->labelWhatTor = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxFigure))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarDeltaScale))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxZBuffer))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBoxFigure
			// 
			this->pictureBoxFigure->BackColor = System::Drawing::Color::White;
			this->pictureBoxFigure->Location = System::Drawing::Point(12, 35);
			this->pictureBoxFigure->Name = L"pictureBoxFigure";
			this->pictureBoxFigure->Size = System::Drawing::Size(375, 375);
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
			this->radioButtonX->Location = System::Drawing::Point(440, 97);
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
			this->radioButtonY->Location = System::Drawing::Point(478, 97);
			this->radioButtonY->Name = L"radioButtonY";
			this->radioButtonY->Size = System::Drawing::Size(32, 17);
			this->radioButtonY->TabIndex = 3;
			this->radioButtonY->TabStop = true;
			this->radioButtonY->Text = L"Y";
			this->radioButtonY->UseVisualStyleBackColor = true;
			// 
			// trackBarDeltaScale
			// 
			this->trackBarDeltaScale->Location = System::Drawing::Point(527, 130);
			this->trackBarDeltaScale->Maximum = 20;
			this->trackBarDeltaScale->Name = L"trackBarDeltaScale";
			this->trackBarDeltaScale->Size = System::Drawing::Size(104, 45);
			this->trackBarDeltaScale->TabIndex = 7;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(482, 63);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(60, 29);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Ось";
			// 
			// radioButtonZ
			// 
			this->radioButtonZ->AutoSize = true;
			this->radioButtonZ->Location = System::Drawing::Point(516, 97);
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
			this->label2->Location = System::Drawing::Point(402, 139);
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
			this->label3->Location = System::Drawing::Point(478, 187);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(71, 24);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Сдвиг";
			// 
			// buttonMoveBack
			// 
			this->buttonMoveBack->Location = System::Drawing::Point(402, 218);
			this->buttonMoveBack->Name = L"buttonMoveBack";
			this->buttonMoveBack->Size = System::Drawing::Size(105, 23);
			this->buttonMoveBack->TabIndex = 9;
			this->buttonMoveBack->Text = L"Назад";
			this->buttonMoveBack->UseVisualStyleBackColor = true;
			this->buttonMoveBack->Click += gcnew System::EventHandler(this, &FiguForm::buttonMoveBack_Click);
			// 
			// buttonMoveForw
			// 
			this->buttonMoveForw->Location = System::Drawing::Point(526, 218);
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
			this->label4->Location = System::Drawing::Point(462, 256);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(108, 24);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Вращение";
			// 
			// buttonCW
			// 
			this->buttonCW->Location = System::Drawing::Point(525, 285);
			this->buttonCW->Name = L"buttonCW";
			this->buttonCW->Size = System::Drawing::Size(105, 23);
			this->buttonCW->TabIndex = 13;
			this->buttonCW->Text = L"По часовой";
			this->buttonCW->UseVisualStyleBackColor = true;
			this->buttonCW->Click += gcnew System::EventHandler(this, &FiguForm::buttonCW_Click);
			// 
			// buttonCCW
			// 
			this->buttonCCW->Location = System::Drawing::Point(405, 285);
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
			this->label5->Location = System::Drawing::Point(466, 324);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(98, 24);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Масштаб";
			// 
			// buttonScaleSmall
			// 
			this->buttonScaleSmall->Location = System::Drawing::Point(405, 355);
			this->buttonScaleSmall->Name = L"buttonScaleSmall";
			this->buttonScaleSmall->Size = System::Drawing::Size(105, 23);
			this->buttonScaleSmall->TabIndex = 15;
			this->buttonScaleSmall->Text = L"Меньше";
			this->buttonScaleSmall->UseVisualStyleBackColor = true;
			this->buttonScaleSmall->Click += gcnew System::EventHandler(this, &FiguForm::buttonScaleSmall_Click);
			// 
			// buttonScaleBig
			// 
			this->buttonScaleBig->Location = System::Drawing::Point(525, 355);
			this->buttonScaleBig->Name = L"buttonScaleBig";
			this->buttonScaleBig->Size = System::Drawing::Size(105, 23);
			this->buttonScaleBig->TabIndex = 16;
			this->buttonScaleBig->Text = L"Больше";
			this->buttonScaleBig->UseVisualStyleBackColor = true;
			this->buttonScaleBig->Click += gcnew System::EventHandler(this, &FiguForm::buttonScaleBig_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->оПрограммеToolStripMenuItem,
					this->цветаToolStripMenuItem
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
			// цветаToolStripMenuItem
			// 
			this->цветаToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->фонToolStripMenuItem,
					this->тор1ToolStripMenuItem, this->тор2ToolStripMenuItem, this->тор3ToolStripMenuItem
			});
			this->цветаToolStripMenuItem->Name = L"цветаToolStripMenuItem";
			this->цветаToolStripMenuItem->Size = System::Drawing::Size(51, 20);
			this->цветаToolStripMenuItem->Text = L"Цвета";
			// 
			// фонToolStripMenuItem
			// 
			this->фонToolStripMenuItem->Name = L"фонToolStripMenuItem";
			this->фонToolStripMenuItem->Size = System::Drawing::Size(104, 22);
			this->фонToolStripMenuItem->Text = L"Фон";
			this->фонToolStripMenuItem->Click += gcnew System::EventHandler(this, &FiguForm::фонToolStripMenuItem_Click);
			// 
			// тор1ToolStripMenuItem
			// 
			this->тор1ToolStripMenuItem->Name = L"тор1ToolStripMenuItem";
			this->тор1ToolStripMenuItem->Size = System::Drawing::Size(104, 22);
			this->тор1ToolStripMenuItem->Text = L"Тор 1";
			this->тор1ToolStripMenuItem->Click += gcnew System::EventHandler(this, &FiguForm::тор1ToolStripMenuItem_Click);
			// 
			// тор2ToolStripMenuItem
			// 
			this->тор2ToolStripMenuItem->Name = L"тор2ToolStripMenuItem";
			this->тор2ToolStripMenuItem->Size = System::Drawing::Size(104, 22);
			this->тор2ToolStripMenuItem->Text = L"Тор 2";
			this->тор2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &FiguForm::тор2ToolStripMenuItem_Click);
			// 
			// тор3ToolStripMenuItem
			// 
			this->тор3ToolStripMenuItem->Name = L"тор3ToolStripMenuItem";
			this->тор3ToolStripMenuItem->Size = System::Drawing::Size(104, 22);
			this->тор3ToolStripMenuItem->Text = L"Тор 3";
			this->тор3ToolStripMenuItem->Click += gcnew System::EventHandler(this, &FiguForm::тор3ToolStripMenuItem_Click);
			// 
			// radioButtonAll
			// 
			this->radioButtonAll->AutoSize = true;
			this->radioButtonAll->Location = System::Drawing::Point(554, 97);
			this->radioButtonAll->Name = L"radioButtonAll";
			this->radioButtonAll->Size = System::Drawing::Size(44, 17);
			this->radioButtonAll->TabIndex = 5;
			this->radioButtonAll->TabStop = true;
			this->radioButtonAll->Text = L"Все";
			this->radioButtonAll->UseVisualStyleBackColor = true;
			// 
			// buttonNewScene
			// 
			this->buttonNewScene->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonNewScene->Location = System::Drawing::Point(226, 458);
			this->buttonNewScene->Name = L"buttonNewScene";
			this->buttonNewScene->Size = System::Drawing::Size(172, 38);
			this->buttonNewScene->TabIndex = 43;
			this->buttonNewScene->Text = L"Новая сцена";
			this->buttonNewScene->UseVisualStyleBackColor = true;
			this->buttonNewScene->Click += gcnew System::EventHandler(this, &FiguForm::buttonNewScene_Click);
			// 
			// buttonChangeTor1
			// 
			this->buttonChangeTor1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonChangeTor1->Location = System::Drawing::Point(433, 423);
			this->buttonChangeTor1->Name = L"buttonChangeTor1";
			this->buttonChangeTor1->Size = System::Drawing::Size(172, 33);
			this->buttonChangeTor1->TabIndex = 45;
			this->buttonChangeTor1->Text = L"Изменять первый тор";
			this->buttonChangeTor1->UseVisualStyleBackColor = true;
			this->buttonChangeTor1->Click += gcnew System::EventHandler(this, &FiguForm::buttonChangeTor1_Click);
			// 
			// buttonChangeTor2
			// 
			this->buttonChangeTor2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonChangeTor2->Location = System::Drawing::Point(433, 461);
			this->buttonChangeTor2->Name = L"buttonChangeTor2";
			this->buttonChangeTor2->Size = System::Drawing::Size(172, 33);
			this->buttonChangeTor2->TabIndex = 46;
			this->buttonChangeTor2->Text = L"Изменять второй тор";
			this->buttonChangeTor2->UseVisualStyleBackColor = true;
			this->buttonChangeTor2->Click += gcnew System::EventHandler(this, &FiguForm::buttonChangeTor2_Click);
			// 
			// pictureBoxZBuffer
			// 
			this->pictureBoxZBuffer->BackColor = System::Drawing::Color::White;
			this->pictureBoxZBuffer->Location = System::Drawing::Point(649, 35);
			this->pictureBoxZBuffer->Name = L"pictureBoxZBuffer";
			this->pictureBoxZBuffer->Size = System::Drawing::Size(375, 375);
			this->pictureBoxZBuffer->TabIndex = 47;
			this->pictureBoxZBuffer->TabStop = false;
			// 
			// buttonChangeTor3
			// 
			this->buttonChangeTor3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonChangeTor3->Location = System::Drawing::Point(433, 499);
			this->buttonChangeTor3->Name = L"buttonChangeTor3";
			this->buttonChangeTor3->Size = System::Drawing::Size(172, 33);
			this->buttonChangeTor3->TabIndex = 48;
			this->buttonChangeTor3->Text = L"Изменять третий тор";
			this->buttonChangeTor3->UseVisualStyleBackColor = true;
			this->buttonChangeTor3->Click += gcnew System::EventHandler(this, &FiguForm::buttonChangeTor3_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(797, 413);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(74, 18);
			this->label6->TabIndex = 49;
			this->label6->Text = L"Z-буфер";
			// 
			// labelWhatTor
			// 
			this->labelWhatTor->AutoSize = true;
			this->labelWhatTor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelWhatTor->Location = System::Drawing::Point(132, 413);
			this->labelWhatTor->Name = L"labelWhatTor";
			this->labelWhatTor->Size = System::Drawing::Size(135, 18);
			this->labelWhatTor->TabIndex = 50;
			this->labelWhatTor->Text = L"Изменяем тор 1";
			// 
			// FiguForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::SeaGreen;
			this->ClientSize = System::Drawing::Size(1037, 545);
			this->Controls->Add(this->labelWhatTor);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->buttonChangeTor3);
			this->Controls->Add(this->pictureBoxZBuffer);
			this->Controls->Add(this->buttonChangeTor2);
			this->Controls->Add(this->buttonChangeTor1);
			this->Controls->Add(this->buttonNewScene);
			this->Controls->Add(this->radioButtonAll);
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
			this->Text = L"Z-буфер";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxFigure))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarDeltaScale))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxZBuffer))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void buttonMoveBack_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 0;
	double deltaY = 0;
	double deltaZ = 0;

	decrementDeltas(deltaX, deltaY, deltaZ, trackBarDeltaScale->Value); // decrementing the current delta
	switch (state) {
	case 0: {
		tor3MatrixVert = matrixComposition(tor3MatrixVert, formMoveMatrix(deltaX, deltaY, deltaZ)); // moving
		break;
	}
	case 1: {
		tor1MatrixVert = matrixComposition(tor1MatrixVert, formMoveMatrix(deltaX, deltaY, deltaZ)); // moving
		break;
	}
	case 2: {
		tor2MatrixVert = matrixComposition(tor2MatrixVert, formMoveMatrix(deltaX, deltaY, deltaZ)); // moving
		break;
	}
	default:
		break;
	}
	drawScene(); // drawing
}
private: System::Void buttonMoveForw_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 0;
	double deltaY = 0;
	double deltaZ = 0;

	incrementDeltas(deltaX, deltaY, deltaZ, trackBarDeltaScale->Value); // incrementing the current delta

	switch (state) {
	case 0: {
		tor3MatrixVert = matrixComposition(tor3MatrixVert, formMoveMatrix(deltaX, deltaY, deltaZ)); // moving
		break;
	}
	case 1: {
		tor1MatrixVert = matrixComposition(tor1MatrixVert, formMoveMatrix(deltaX, deltaY, deltaZ)); // moving
		break;
	}
	case 2: {
		tor2MatrixVert = matrixComposition(tor2MatrixVert, formMoveMatrix(deltaX, deltaY, deltaZ)); // moving
		break;
	}
	default:
		break;
	}

	drawScene(); // drawing
}
private: System::Void buttonCCW_Click(System::Object^  sender, System::EventArgs^  e) {
	switch (state) {
	case 0: {
		tor3MatrixVert = matrixComposition(tor3MatrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
		break;
	}
	case 1: {
		tor1MatrixVert = matrixComposition(tor1MatrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
		break;
	}
	case 2: {
		tor2MatrixVert = matrixComposition(tor2MatrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
		break;
	}
	default:
		break;
	}
	
	double deltaX = 0;
	double deltaY = 0;
	double deltaZ = 0;

	decrementDeltas(deltaX, deltaY, deltaZ, (double)trackBarDeltaScale->Value / 20); // decrementing the current delta

	if (deltaX != 0) { // if was X-rotation
		switch (state) {
		case 0: {
			tor3MatrixVert = matrixComposition(tor3MatrixVert, formXRotateMatrix(deltaX)); // rotating X
			break;
		}
		case 1: {
			tor1MatrixVert = matrixComposition(tor1MatrixVert, formXRotateMatrix(deltaX)); // rotating X
			break;
		}
		case 2: {
			tor2MatrixVert = matrixComposition(tor2MatrixVert, formXRotateMatrix(deltaX)); // rotating X
			break;
		}
		default:
			break;
		}
	}

	if (deltaY != 0) { // if was Y-rotation
		switch (state) {
		case 0: {
			tor3MatrixVert = matrixComposition(tor3MatrixVert, formYRotateMatrix(deltaY)); // rotating Y
			break;
		}
		case 1: {
			tor1MatrixVert = matrixComposition(tor1MatrixVert, formYRotateMatrix(deltaY)); // rotating Y
			break;
		}
		case 2: {
			tor2MatrixVert = matrixComposition(tor2MatrixVert, formYRotateMatrix(deltaY)); // rotating Y
			break;
		}
		default:
			break;
		}
	}

	if (deltaZ != 0) { // if was Z-rotation
		switch (state) {
		case 0: {
			tor3MatrixVert = matrixComposition(tor3MatrixVert, formZRotateMatrix(deltaZ)); // rotating Z
			break;
		}
		case 1: {
			tor1MatrixVert = matrixComposition(tor1MatrixVert, formZRotateMatrix(deltaZ)); // rotating Z
			break;
		}
		case 2: {
			tor2MatrixVert = matrixComposition(tor2MatrixVert, formZRotateMatrix(deltaZ)); // rotating Z
			break;
		}
		default:
			break;
		}
	}

	switch (state) {
	case 0: {
		tor3MatrixVert = matrixComposition(tor3MatrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
		break;
	}
	case 1: {
		tor1MatrixVert = matrixComposition(tor1MatrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
		break;
	}
	case 2: {
		tor2MatrixVert = matrixComposition(tor2MatrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
		break;
	}
	default:
		break;
	}

	drawScene(); // drawing
}
private: System::Void buttonCW_Click(System::Object^  sender, System::EventArgs^  e) {

	switch (state) {
	case 0: {
		tor3MatrixVert = matrixComposition(tor3MatrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
		break;
	}
	case 1: {
		tor1MatrixVert = matrixComposition(tor1MatrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
		break;
	}
	case 2: {
		tor2MatrixVert = matrixComposition(tor2MatrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
		break;
	}
	default:
		break;
	}

	double deltaX = 0;
	double deltaY = 0;
	double deltaZ = 0;

	incrementDeltas(deltaX, deltaY, deltaZ, (double)trackBarDeltaScale->Value / 20); // incrementing the current delta

	if (deltaX != 0) { // if was X-rotation
		switch (state) {
		case 0: {
			tor3MatrixVert = matrixComposition(tor3MatrixVert, formXRotateMatrix(deltaX)); // rotating X
			break;
		}
		case 1: {
			tor1MatrixVert = matrixComposition(tor1MatrixVert, formXRotateMatrix(deltaX)); // rotating X
			break;
		}
		case 2: {
			tor2MatrixVert = matrixComposition(tor2MatrixVert, formXRotateMatrix(deltaX)); // rotating X
			break;
		}
		default:
			break;
		}
	}

	if (deltaY != 0) { // if was Y-rotation
		switch (state) {
		case 0: {
			tor3MatrixVert = matrixComposition(tor3MatrixVert, formYRotateMatrix(deltaY)); // rotating Y
			break;
		}
		case 1: {
			tor1MatrixVert = matrixComposition(tor1MatrixVert, formYRotateMatrix(deltaY)); // rotating Y
			break;
		}
		case 2: {
			tor2MatrixVert = matrixComposition(tor2MatrixVert, formYRotateMatrix(deltaY)); // rotating Y
			break;
		}
		default:
			break;
		}
	}

	if (deltaZ != 0) { // if was Z-rotation
		switch (state) {
		case 0: {
			tor3MatrixVert = matrixComposition(tor3MatrixVert, formZRotateMatrix(deltaZ)); // rotating Z
			break;
		}
		case 1: {
			tor1MatrixVert = matrixComposition(tor1MatrixVert, formZRotateMatrix(deltaZ)); // rotating Z
			break;
		}
		case 2: {
			tor2MatrixVert = matrixComposition(tor2MatrixVert, formZRotateMatrix(deltaZ)); // rotating Z
			break;
		}
		default:
			break;
		}
	}

	switch (state) {
	case 0: {
		tor3MatrixVert = matrixComposition(tor3MatrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
		break;
	}
	case 1: {
		tor1MatrixVert = matrixComposition(tor1MatrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
		break;
	}
	case 2: {
		tor2MatrixVert = matrixComposition(tor2MatrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
		break;
	}
	default:
		break;
	}

	drawScene(); // drawing
}
private: System::Void buttonScaleSmall_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 1;
	double deltaY = 1;
	double deltaZ = 1;

	decrementDeltas(deltaX, deltaY, deltaZ, (double)trackBarDeltaScale->Value / 30); // decrementing the current delta

	switch (state) {
	case 0: {
		tor3MatrixVert = matrixComposition(tor3MatrixVert, formScaleMatrix(deltaX, deltaY, deltaZ, 1)); // scaling
		break;
	}
	case 1: {
		tor1MatrixVert = matrixComposition(tor1MatrixVert, formScaleMatrix(deltaX, deltaY, deltaZ, 1)); // scaling
		break;
	}
	case 2: {
		tor2MatrixVert = matrixComposition(tor2MatrixVert, formScaleMatrix(deltaX, deltaY, deltaZ, 1)); // scaling
		break;
	}
	default:
		break;
	}

	drawScene(); // drawing
}
private: System::Void buttonScaleBig_Click(System::Object^  sender, System::EventArgs^  e) {
	double deltaX = 1;
	double deltaY = 1;
	double deltaZ = 1;

	incrementDeltas(deltaX, deltaY, deltaZ, (double)trackBarDeltaScale->Value / 30); // incrementing the current delta

	switch (state) {
	case 0: {
		tor3MatrixVert = matrixComposition(tor3MatrixVert, formScaleMatrix(deltaX, deltaY, deltaZ, 1)); // scaling
		break;
	}
	case 1: {
		tor1MatrixVert = matrixComposition(tor1MatrixVert, formScaleMatrix(deltaX, deltaY, deltaZ, 1)); // scaling
		break;
	}
	case 2: {
		tor2MatrixVert = matrixComposition(tor2MatrixVert, formScaleMatrix(deltaX, deltaY, deltaZ, 1)); // scaling
		break;
	}
	default:
		break;
	}

	drawScene(); // drawing
}
private: System::Void pictureBoxFigure_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	// saving coords
	pressedX = e->X;
	pressedY = e->Y;
}
private: System::Void pictureBoxFigure_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == Windows::Forms::MouseButtons::Right) { // right - moving
		switch (state) {
		case 0: {
			tor3MatrixVert = matrixComposition(tor3MatrixVert, formMoveMatrix(e->X - pressedX, e->Y - pressedY, 0)); // moving
			break;
		}
		case 1: {
			tor1MatrixVert = matrixComposition(tor1MatrixVert, formMoveMatrix(e->X - pressedX, e->Y - pressedY, 0)); // moving
			break;
		}
		case 2: {
			tor2MatrixVert = matrixComposition(tor2MatrixVert, formMoveMatrix(e->X - pressedX, e->Y - pressedY, 0)); // moving
			break;
		}
		default:
			break;
		}
		drawScene(); // drawing
	}
	if (e->Button == Windows::Forms::MouseButtons::Left) { // left - rotating

		switch (state) {
		case 0: {
			tor3MatrixVert = matrixComposition(tor3MatrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
			break;
		}
		case 1: {
			tor1MatrixVert = matrixComposition(tor1MatrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
			break;
		}
		case 2: {
			tor2MatrixVert = matrixComposition(tor2MatrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0)); // moving
			break;
		}
		default:
			break;
		}
		if (e->X - pressedX != 0) { // if x changed
			switch (state) {
			case 0: {
				tor3MatrixVert = matrixComposition(tor3MatrixVert, formYRotateMatrix((e->X - pressedX) / 100.0)); // rotating x
				break;
			}
			case 1: {
				tor1MatrixVert = matrixComposition(tor1MatrixVert, formYRotateMatrix((e->X - pressedX) / 100.0)); // rotating x
				break;
			}
			case 2: {
				tor2MatrixVert = matrixComposition(tor2MatrixVert, formYRotateMatrix((e->X - pressedX) / 100.0)); // rotating x
				break;
			}
			default:
				break;
			}
		}
		if (e->Y - pressedY != 0) { // if y changed
			switch (state) {
			case 0: {
				tor3MatrixVert = matrixComposition(tor3MatrixVert, formXRotateMatrix((e->Y - pressedY) / 100.0)); // rotating y
				break;
			}
			case 1: {
				tor1MatrixVert = matrixComposition(tor1MatrixVert, formXRotateMatrix((e->Y - pressedY) / 100.0)); // rotating y
				break;
			}
			case 2: {
				tor2MatrixVert = matrixComposition(tor2MatrixVert, formXRotateMatrix((e->Y - pressedY) / 100.0)); // rotating y
				break;
			}
			default:
				break;
			}
		}

		switch (state) {
		case 0: {
			tor3MatrixVert = matrixComposition(tor3MatrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
			break;
		}
		case 1: {
			tor1MatrixVert = matrixComposition(tor1MatrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
			break;
		}
		case 2: {
			tor2MatrixVert = matrixComposition(tor2MatrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0)); // moving
			break;
		}
		default:
			break;
		}
		drawScene();
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
	switch (state) {
	case 0: {
		tor3MatrixVert = matrixComposition(tor3MatrixVert, formScaleMatrix(deltaScale, deltaScale, deltaScale, 1)); // scaling
		break;
	}
	case 1: {
		tor1MatrixVert = matrixComposition(tor1MatrixVert, formScaleMatrix(deltaScale, deltaScale, deltaScale, 1)); // scaling
		break;
	}
	case 2: {
		tor2MatrixVert = matrixComposition(tor2MatrixVert, formScaleMatrix(deltaScale, deltaScale, deltaScale, 1)); // scaling
		break;
	}
	default:
		break;
	}

	drawScene(); // drawing
}
private: System::Void buttonNewScene_Click(System::Object^  sender, System::EventArgs^  e) {
	prepareScene();
}
private: System::Void buttonChangeTor1_Click(System::Object^  sender, System::EventArgs^  e) {
	state = 1;
	labelWhatTor->Text = "Изменяем тор 1";
}
private: System::Void buttonChangeTor2_Click(System::Object^  sender, System::EventArgs^  e) {
	state = 2;
	labelWhatTor->Text = "Изменяем тор 2";
}
private: System::Void buttonChangeTor3_Click(System::Object^  sender, System::EventArgs^  e) {
	state = 0;
	labelWhatTor->Text = "Изменяем тор 3";
}
private: System::Void фонToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogBg->Color; // saving old color
	colorDialogBg->ShowDialog();
	if (colorDialogBg->Color.ToArgb() == colorDialogTor1->Color.ToArgb() ||
		colorDialogBg->Color.ToArgb() == colorDialogTor2->Color.ToArgb() ||
		colorDialogBg->Color.ToArgb() == colorDialogTor3->Color.ToArgb()) { // checking colors
		MessageBox::Show(this, "Одинаковые цвета фона и торов недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogBg->Color = *old; // restoring old color if colors are identical
	}
	else { // clearing all and drawin initial picture
		prepareScene();
	}
}
private: System::Void тор1ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogTor1->Color; // saving old color
	colorDialogTor1->ShowDialog();
	if (colorDialogTor1->Color.ToArgb() == colorDialogBg->Color.ToArgb() ||
		colorDialogTor1->Color.ToArgb() == colorDialogTor2->Color.ToArgb() ||
		colorDialogTor1->Color.ToArgb() == colorDialogTor3->Color.ToArgb()) { // checking colors
		MessageBox::Show(this, "Одинаковые цвета фона и торов недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogTor1->Color = *old; // restoring old color if colors are identical
	}
	else { // clearing all and drawin initial picture
		prepareScene();
	}
}
private: System::Void тор2ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogTor2->Color; // saving old color
	colorDialogTor2->ShowDialog();
	if (colorDialogTor2->Color.ToArgb() == colorDialogBg->Color.ToArgb() ||
		colorDialogTor2->Color.ToArgb() == colorDialogTor1->Color.ToArgb() ||
		colorDialogTor2->Color.ToArgb() == colorDialogTor3->Color.ToArgb()) { // checking colors
		MessageBox::Show(this, "Одинаковые цвета фона и торов недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogTor2->Color = *old; // restoring old color if colors are identical
	}
	else { // clearing all and drawin initial picture
		prepareScene();
	}
}
private: System::Void тор3ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogTor3->Color; // saving old color
	colorDialogTor3->ShowDialog();
	if (colorDialogTor3->Color.ToArgb() == colorDialogBg->Color.ToArgb() ||
		colorDialogTor3->Color.ToArgb() == colorDialogTor1->Color.ToArgb() ||
		colorDialogTor3->Color.ToArgb() == colorDialogTor2->Color.ToArgb()) { // checking colors
		MessageBox::Show(this, "Одинаковые цвета фона и торов недопустимы!",
			"Ошибка", MessageBoxButtons::OK);
		colorDialogTor3->Color = *old; // restoring old color if colors are identical
	}
	else { // clearing all and drawin initial picture
		prepareScene();
	}
}
private: System::Void оПрограммеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show(this, "Программа предназначена для демонстрации сцены из нескольких фигур с использованием алгоритма z-буфера. \n\n" +
		"1) Реализованы трансформации мышью (в основном окне рисования), а именно:\n" +
		"\tвращение - левой кнопкой мыши;\n" +
		"\tсдвиг - правой кнопкой мыши;\n" +
		"\tмасштабирование - колесиком мыши.\n\n" +
		"2) Также реализованы трансформации с помощью кнопок. \n" +
		"ВНИМАНИЕ! В отличие от операций мышью, с помощью кнопок можно осуществить трансформации " +
		"(вращение, сдвиг, масштабирование) как для ВСЕХ осей, так и для КАЖДОЙ оси. " +
		"Для этого следует выбрать параметр нужной оси (или \"Все\" для всех осей) в переключателе.\n" +
		"Для изменения величины изменения при транформациях кнопок следует изменить значение  " +
		"соответствующего ползунка. Действует только на трансформации при помощи кнопок.\n\n" +
		"3) Для выбора фигуры для трансформаций следует воспользоваться соответствующими кнопками.\n\n" +
		"4) Реализовано отображение содержимого z-буфера (справа).\n\n" +
		"5) Реализована плоская закраска. \n\n" +
		"6) В программе можно менять цвет фона окна для рисования и цвета фигур. " +
		"Для этого следует зайти в меню \"Цвета\".\n\n" +
		"Автор: Осипов Лев Игоревич, 4-й курс, группа БПИ121\n" +
		"Среда разработки: Visual Studio 2013\n" +
		"Дата: 16.11.2015", "О программе", MessageBoxButtons::OK);
}
};
}
