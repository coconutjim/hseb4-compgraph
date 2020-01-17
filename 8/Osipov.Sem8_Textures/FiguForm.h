#pragma once

namespace Figure {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Timers;

	/***
	Осипов Лев Игоревич, 4-й курс, группа БПИ121
	Семинар 8. Текстуры
	Среда разработки: Visual Studio 2013
	Дата: 26.11.2015
	Реализовано наложение текстур, загрузка текстуры из файла и изменения скорости вращений.
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
			try {
				Image^ image1 = Image::FromFile("example1.png"); // loading image
				bitmapTextureTor = gcnew Bitmap(image1, image1->Size); // initializing
				Image^ image2 = Image::FromFile("example2.png"); // loading image
				bitmapTextureSphere = gcnew Bitmap(image2, image2->Size); // initializing
			}
			catch (System::IO::FileNotFoundException^ e) {
				MessageBox::Show(this, "Не найдены файлы example1.png и example2.png! Пожалуйста, удостоверьтесь, что они лежат в одной папке с программой!",
					"Ошибка", MessageBoxButtons::OK);
				Close();
			}

			// Creating bitmap for figures
			bitmapFigu = gcnew Bitmap(pictureBoxFigure->Width, pictureBoxFigure->Height);
			pictureBoxFigure->Image = bitmapFigu;

			// initializing colors
			colorDialogBg->Color = Color::White;

			// getting start coordinates
			x0 = pictureBoxFigure->Width / 2;
			y0 = pictureBoxFigure->Height / 2;
			z0 = 0;

			// creating initial matrices
			initializeMatrices(pictureBoxFigure->Width, pictureBoxFigure->Height);

			// setting default speeds of rotation and incline
			trackBarTorSelfAxis->Value = speedTorSelfAxis = 3;
			trackBarSphereSelfAxis->Value = speedSphereSelfAxis = 3;
			trackBarSphereYAxis->Value = speedSphereYAxis = 3;

			// initializing timer
			timer = gcnew System::Timers::Timer;
			timer->Elapsed += gcnew ElapsedEventHandler(this, &FiguForm::timerAction);
			timer->Interval = 1300;
			timer->Enabled = true;

			// configuring file filter in openFileDialog
			openFileDialog1->Filter = "JPEG Files (*.jpeg)|*.jpeg|PNG Files (*.png)|*.png|JPG Files (*.jpg)|*.jpg";

			// preparing scene
			prepareScene(pictureBoxFigure, bitmapFigu, colorDialogBg->Color);

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
		}
	private: System::Windows::Forms::PictureBox^  pictureBoxFigure;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		/// <summary>
		/// Speeds of rotation
		/// </summary>
		int speedTorSelfAxis;
		int speedSphereSelfAxis;
		int speedSphereYAxis;

		/// <summary>
		/// Timer to change figures.
		/// </summary>
		System::Timers::Timer^ timer;

		/// <summary>
		/// Bitmap to draw in.
		/// </summary>
		Bitmap^ bitmapFigu;

		/// <summary>
		/// Texture bitmap for tor.
		/// </summary>
		Bitmap^ bitmapTextureTor;

		/// <summary>
		/// Texture bitmap for sphere.
		/// </summary>
		Bitmap^ bitmapTextureSphere;

		/// <summary>
		/// Start coordinates.
		/// </summary>
		int x0;
		int y0;
		int z0;

		/// <summary>
		/// Z-buffer
		/// </summary>
		array<double, 2>^ zBuffer;

		/// <summary>
		/// Sphere default vertex matrix.
		/// </summary>
		array<double, 2>^ sphereDefaultMatrixVert;
		
		/// <summary>
		/// Sphere vertex matrix.
		/// </summary>
		array<double, 2>^ sphereMatrixVert;

		/// <summary>
		/// Sphere vertex texture matrix.
		/// </summary>
		array<double, 2>^ sphereMatrixVertTexture;

		/// <summary>
		/// Sphere central vertex.
		/// </summary>
		array<double, 2>^ sphereCentVert;

		/// <summary>
		/// Sphere default central vertex.
		/// </summary>
		array<double, 2>^ sphereDefaultCentVert;

		/// <summary>
		/// Sphere face matrix.
		/// </summary>
		array<int, 2>^ sphereMatrixFace;

		/// <summary>
		/// Tor default vertex matrix.
		/// </summary>
		array<double, 2>^ torDefaultMatrixVert;

		/// <summary>
		/// Tor vertex matrix.
		/// </summary>
		array<double, 2>^ torMatrixVert;

		/// <summary>
		/// Tor vertex texture matrix.
		/// </summary>
		array<double, 2>^ torMatrixVertTexture;

		/// <summary>
		/// Tor central vertex.
		/// </summary>
		array<double, 2>^ torCentVert;

		/// <summary>
		/// Tor default central vertex.
		/// </summary>
		array<double, 2>^ torDefaultCentVert;

		/// <summary>
		/// Tor face matrix.
		/// </summary>
		array<int, 2>^ torMatrixFace;

		/// <summary>
		/// Matrix of ortogonal projection
		/// </summary>
		array<double, 2>^ matrixOrtProj;

private: System::Windows::Forms::MenuStrip^  menuStrip1;
private: System::Windows::Forms::ToolStripMenuItem^  оПрограммеToolStripMenuItem;
private: System::Windows::Forms::ColorDialog^  colorDialogBg;
private: System::Windows::Forms::Button^  buttonNewScene;
private: System::Windows::Forms::ToolStripMenuItem^  цветаToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  фонToolStripMenuItem;
private: System::Windows::Forms::Button^  buttonPause;
private: System::Windows::Forms::Button^  buttonStart;
private: System::Windows::Forms::TrackBar^  trackBarTorSelfAxis;
private: System::Windows::Forms::TrackBar^  trackBarSphereSelfAxis;
private: System::Windows::Forms::TrackBar^  trackBarSphereYAxis;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Button^  buttonLoadTextureTor;

private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
private: System::Windows::Forms::Button^  buttonLoadTextureSphere;


private: System::Windows::Forms::Label^  label3;

		/// <summary>
		/// Returns a composition of 2 matrices.
		/// </summary>
		array<double, 2>^ matrixComposition(array<double, 2>^ m1, array<double, 2>^ m2);

		/// <summary>
		/// Initializes figure matrices.
		/// </summary>
		void initializeMatrices(int width, int height);

		/// <summary>
		/// Prepares scene
		/// </summary>
		void prepareScene(PictureBox^ pb, Bitmap^ bp, Color^ color);

		/// <summary>
		/// Draws scene.
		/// </summary>
		void drawScene(PictureBox^ pb, Bitmap^ bp, Color^ color);

		/// <summary>
		/// Timer actions.
		/// </summary>
		void timerAction(Object^ obj, ElapsedEventArgs^ args);

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
		/// Draws a figure.
		/// </summary>
		void drawFigure(array<double, 2>^ matrixVert, array<double, 2>^ matrixVertTexture, array<int, 2>^ matrixFace, Bitmap^ texture);

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
			double& x3, double& y3, double& z3,
			double& xt1, double& yt1, double& xt2, 
			double& yt2, double& xt3, double& yt3);

		/// <summary>
		/// Swaps two doubles.
		/// </summary>
		void swap(double& x, double& y);

		/// <summary>
		/// Draw a point on the texture
		/// </summary>
		void drawPixel(int x, int y, double xt, double yt, Bitmap^ texture);

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
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->фонToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->colorDialogBg = (gcnew System::Windows::Forms::ColorDialog());
			this->buttonNewScene = (gcnew System::Windows::Forms::Button());
			this->buttonPause = (gcnew System::Windows::Forms::Button());
			this->buttonStart = (gcnew System::Windows::Forms::Button());
			this->trackBarTorSelfAxis = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarSphereSelfAxis = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarSphereYAxis = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->buttonLoadTextureTor = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->buttonLoadTextureSphere = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxFigure))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarTorSelfAxis))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSphereSelfAxis))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSphereYAxis))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBoxFigure
			// 
			this->pictureBoxFigure->BackColor = System::Drawing::Color::White;
			this->pictureBoxFigure->Location = System::Drawing::Point(12, 35);
			this->pictureBoxFigure->Name = L"pictureBoxFigure";
			this->pictureBoxFigure->Size = System::Drawing::Size(955, 455);
			this->pictureBoxFigure->TabIndex = 0;
			this->pictureBoxFigure->TabStop = false;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->оПрограммеToolStripMenuItem,
					this->цветаToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(978, 24);
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
			this->цветаToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->фонToolStripMenuItem });
			this->цветаToolStripMenuItem->Name = L"цветаToolStripMenuItem";
			this->цветаToolStripMenuItem->Size = System::Drawing::Size(51, 20);
			this->цветаToolStripMenuItem->Text = L"Цвета";
			// 
			// фонToolStripMenuItem
			// 
			this->фонToolStripMenuItem->Name = L"фонToolStripMenuItem";
			this->фонToolStripMenuItem->Size = System::Drawing::Size(97, 22);
			this->фонToolStripMenuItem->Text = L"Фон";
			this->фонToolStripMenuItem->Click += gcnew System::EventHandler(this, &FiguForm::фонToolStripMenuItem_Click);
			// 
			// buttonNewScene
			// 
			this->buttonNewScene->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonNewScene->Location = System::Drawing::Point(33, 524);
			this->buttonNewScene->Name = L"buttonNewScene";
			this->buttonNewScene->Size = System::Drawing::Size(172, 38);
			this->buttonNewScene->TabIndex = 43;
			this->buttonNewScene->Text = L"Новая сцена";
			this->buttonNewScene->UseVisualStyleBackColor = true;
			this->buttonNewScene->Click += gcnew System::EventHandler(this, &FiguForm::buttonNewScene_Click);
			// 
			// buttonPause
			// 
			this->buttonPause->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonPause->Location = System::Drawing::Point(33, 571);
			this->buttonPause->Name = L"buttonPause";
			this->buttonPause->Size = System::Drawing::Size(172, 38);
			this->buttonPause->TabIndex = 44;
			this->buttonPause->Text = L"Пауза";
			this->buttonPause->UseVisualStyleBackColor = true;
			this->buttonPause->Click += gcnew System::EventHandler(this, &FiguForm::buttonPause_Click);
			// 
			// buttonStart
			// 
			this->buttonStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonStart->Location = System::Drawing::Point(33, 615);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(172, 38);
			this->buttonStart->TabIndex = 45;
			this->buttonStart->Text = L"Старт";
			this->buttonStart->UseVisualStyleBackColor = true;
			this->buttonStart->Click += gcnew System::EventHandler(this, &FiguForm::buttonStart_Click);
			// 
			// trackBarTorSelfAxis
			// 
			this->trackBarTorSelfAxis->Location = System::Drawing::Point(527, 538);
			this->trackBarTorSelfAxis->Minimum = 1;
			this->trackBarTorSelfAxis->Name = L"trackBarTorSelfAxis";
			this->trackBarTorSelfAxis->Size = System::Drawing::Size(104, 45);
			this->trackBarTorSelfAxis->TabIndex = 46;
			this->trackBarTorSelfAxis->Value = 1;
			this->trackBarTorSelfAxis->Scroll += gcnew System::EventHandler(this, &FiguForm::trackBarTorSelfAxis_Scroll);
			// 
			// trackBarSphereSelfAxis
			// 
			this->trackBarSphereSelfAxis->Location = System::Drawing::Point(527, 585);
			this->trackBarSphereSelfAxis->Minimum = 1;
			this->trackBarSphereSelfAxis->Name = L"trackBarSphereSelfAxis";
			this->trackBarSphereSelfAxis->Size = System::Drawing::Size(104, 45);
			this->trackBarSphereSelfAxis->TabIndex = 47;
			this->trackBarSphereSelfAxis->Value = 1;
			this->trackBarSphereSelfAxis->Scroll += gcnew System::EventHandler(this, &FiguForm::trackBarSphereSelfAxis_Scroll);
			// 
			// trackBarSphereYAxis
			// 
			this->trackBarSphereYAxis->Location = System::Drawing::Point(527, 629);
			this->trackBarSphereYAxis->Minimum = 1;
			this->trackBarSphereYAxis->Name = L"trackBarSphereYAxis";
			this->trackBarSphereYAxis->Size = System::Drawing::Size(104, 45);
			this->trackBarSphereYAxis->TabIndex = 48;
			this->trackBarSphereYAxis->Value = 1;
			this->trackBarSphereYAxis->Scroll += gcnew System::EventHandler(this, &FiguForm::trackBarSphereYAxis_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(269, 538);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(226, 13);
			this->label1->TabIndex = 49;
			this->label1->Text = L"Скорость вращения тора вокруг своей оси";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(269, 585);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(237, 13);
			this->label2->TabIndex = 50;
			this->label2->Text = L"Скорость вращения сферы вокруг своей оси";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(269, 629);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(217, 13);
			this->label3->TabIndex = 51;
			this->label3->Text = L"Скорость вращения сферы вокруг оси  Y";
			// 
			// buttonLoadTextureTor
			// 
			this->buttonLoadTextureTor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->buttonLoadTextureTor->Location = System::Drawing::Point(685, 508);
			this->buttonLoadTextureTor->Name = L"buttonLoadTextureTor";
			this->buttonLoadTextureTor->Size = System::Drawing::Size(258, 70);
			this->buttonLoadTextureTor->TabIndex = 52;
			this->buttonLoadTextureTor->Text = L"Загрузить текстуру из файла для тора";
			this->buttonLoadTextureTor->UseVisualStyleBackColor = true;
			this->buttonLoadTextureTor->Click += gcnew System::EventHandler(this, &FiguForm::buttonLoadTextureTor_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// buttonLoadTextureSphere
			// 
			this->buttonLoadTextureSphere->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->buttonLoadTextureSphere->Location = System::Drawing::Point(685, 585);
			this->buttonLoadTextureSphere->Name = L"buttonLoadTextureSphere";
			this->buttonLoadTextureSphere->Size = System::Drawing::Size(258, 70);
			this->buttonLoadTextureSphere->TabIndex = 53;
			this->buttonLoadTextureSphere->Text = L"Загрузить текстуру из файла для сферы";
			this->buttonLoadTextureSphere->UseVisualStyleBackColor = true;
			this->buttonLoadTextureSphere->Click += gcnew System::EventHandler(this, &FiguForm::buttonLoadTextureSphere_Click);
			// 
			// FiguForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Teal;
			this->ClientSize = System::Drawing::Size(978, 672);
			this->Controls->Add(this->buttonLoadTextureSphere);
			this->Controls->Add(this->buttonLoadTextureTor);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->trackBarSphereYAxis);
			this->Controls->Add(this->trackBarSphereSelfAxis);
			this->Controls->Add(this->trackBarTorSelfAxis);
			this->Controls->Add(this->buttonStart);
			this->Controls->Add(this->buttonPause);
			this->Controls->Add(this->buttonNewScene);
			this->Controls->Add(this->pictureBoxFigure);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"FiguForm";
			this->Text = L"Текстуры";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxFigure))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarTorSelfAxis))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSphereSelfAxis))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSphereYAxis))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void buttonNewScene_Click(System::Object^  sender, System::EventArgs^  e) {
	prepareScene(pictureBoxFigure, bitmapFigu, colorDialogBg->Color);
}
private: System::Void buttonPause_Click(System::Object^  sender, System::EventArgs^  e) {
	timer->Stop(); // stopping the timer
	// Change button visibility
	buttonPause->Visible = false;
	buttonStart->Visible = true;
}
private: System::Void buttonStart_Click(System::Object^  sender, System::EventArgs^  e) {
	timer->Start(); // starting the timer
	// Change buttond visibility
	buttonStart->Visible = false;
	buttonPause->Visible = true;
}
private: System::Void trackBarTorSelfAxis_Scroll(System::Object^  sender, System::EventArgs^  e) {
	speedTorSelfAxis = trackBarTorSelfAxis->Value; // changing speed
}
private: System::Void trackBarSphereSelfAxis_Scroll(System::Object^  sender, System::EventArgs^  e) {
	speedSphereSelfAxis = trackBarSphereSelfAxis->Value; // changing speed
}
private: System::Void trackBarSphereYAxis_Scroll(System::Object^  sender, System::EventArgs^  e) {
	speedSphereYAxis = trackBarSphereYAxis->Value; // changing speed
}
private: System::Void buttonLoadTextureTor_Click(System::Object^  sender, System::EventArgs^  e) {
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) { // opening dialog
		Image^ image = Image::FromFile(openFileDialog1->FileName); // loading image
		bitmapTextureTor = gcnew Bitmap(image, image->Size); // initializing
	}
}
private: System::Void buttonLoadTextureSphere_Click(System::Object^  sender, System::EventArgs^  e) {
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) { // opening dialog
		Image^ image = Image::FromFile(openFileDialog1->FileName); // loading image
		bitmapTextureSphere = gcnew Bitmap(image, image->Size); // initializing
	}
}
private: System::Void фонToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Color^ old = colorDialogBg->Color; // saving old color
	colorDialogBg->ShowDialog(); // showing dialog
	if (colorDialogBg->Color.ToArgb() != old->ToArgb()) { // if was changed
		prepareScene(pictureBoxFigure, bitmapFigu, colorDialogBg->Color);
	}
}
private: System::Void оПрограммеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show(this, "Программа предназначена для демонстрации наложения текстур. \n\n" +
		"1) Тор крутится в центре вокруг своей оси, сфера крутится вокруг него по оси Y и вокруг своей оси. \n\n" +
		"2) Сцену можно приостановить, продолжить воспроизведение или запустить заново.\n\n" +
		"3) Реализована загрузка текстуры из файла как для тора, так и для сферы (допустимые форматы: - .jpg, .jpeg, .png).\n\n" +
		"4) Скорость каждого из трех вращений можно менять с помощью соответствующего ползунка.\n\n" +
		"5) В программе можно менять цвет фона окна для рисования. " +
		"Для этого следует зайти в меню \"Цвета\".\n\n" +
		"Автор: Осипов Лев Игоревич, 4-й курс, группа БПИ121\n" +
		"Среда разработки: Visual Studio 2013\n" +
		"Дата: 26.11.2015", "О программе", MessageBoxButtons::OK);
}
};
}
