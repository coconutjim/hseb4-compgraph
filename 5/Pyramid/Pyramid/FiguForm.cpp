#include "FiguForm.h"
#include <fstream>

using namespace std;
using namespace Figure;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 5. 3D моделирование-2
Среда разработки: Visual Studio 2013
Дата: 28.10.2015
Реализованы различные отображения и трансформации фигур.
Подробнее см. в меню "О программе".
*/

void FiguForm::clearPictureBox(PictureBox^ pb) {
	Graphics^ graphics = Graphics::FromImage(pb->Image); // creating graphics
	try {
		graphics->Clear(colorDialogBg->Color); // clearing
	}
	finally {
		if (graphics) {
			delete graphics;
		}
	}
	pb->Refresh();
}

void FiguForm::drawHelpLine(PictureBox^ pb) {
	Graphics^ graphics = Graphics::FromImage(pb->Image); // creating graphics
	try {
		graphics->DrawLine(gcnew Pen(colorDialogAdd->Color), 0, y0 + yOffset, pb->Width, y0 + yOffset); // draw line with y offset
	}
	finally {
		if (graphics) {
			delete graphics;
		}
	}
	pb->Refresh();
}

bool FiguForm::writeFigure(array<double, 2>^ matrix, array<int, 2>^ matrixFace) {
	ofstream fout("output.txt");

	if (!fout.is_open()) { // checking
		return false;
	}
	try {
		fout << matrix->GetLength(0) << endl; // vertexes

		for (int i = 0; i < matrix->GetLength(0); ++i) {
			fout << matrix[i, 0] << " " << matrix[i, 1] << " " << matrix[i, 2] << " " <<
				matrix[i, 3] << endl;
		}

		fout << matrixFace->GetLength(0) << endl; // faces

		for (int i = 0; i < matrixFace->GetLength(0); ++i) {
			fout << matrixFace[i, 0] << " " << matrixFace[i, 1] << " " << matrixFace[i, 2] << endl;
		}

		fout.close(); // closing
		return true;
	}
	catch (...) {
		fout.close(); // closing
		return false;
	}
}

bool FiguForm::readFigure() {
	ifstream fin("input.txt");
	
	if (!fin.is_open()) { // checking
		return false;
	}
	try {
		int N; // vertexes
		fin >> N;
		defaultMatrixVert = gcnew array<double, 2>(N, 4);

		for (int i = 0; i < N; ++i) {
			double temp;
			fin >> temp;
			defaultMatrixVert[i, 0] = temp;
			fin >> temp;
			defaultMatrixVert[i, 1] = temp;
			fin >> temp;
			defaultMatrixVert[i, 2] = temp;
			fin >> temp;
			defaultMatrixVert[i, 3] = temp;
		}

		int M; // faces
		fin >> M;
		defaultMatrixFace = gcnew array<int, 2>(M, 3);

		for (int i = 0; i < M; ++i) {
			int temp;
			fin >> temp;
			defaultMatrixFace[i, 0] = temp;
			fin >> temp;
			defaultMatrixFace[i, 1] = temp;
			fin >> temp;
			defaultMatrixFace[i, 2] = temp;
		}

		fin.close(); // closing
		return true;
	}
	catch (...) {
		fin.close(); // closing
		defaultMatrixVert = tetraMatrixVert;
		defaultMatrixFace = tetraMatrixFace;
		state = 0;
		return false;
	}
	
}

void FiguForm::incrementDeltas(double& deltaX, double& deltaY, double& deltaZ, double deltaLength) {
	/* Checking the axis and change delta */
	if (radioButtonX->Checked) {
		deltaX += deltaLength; // changing by delta length
	}
	/* Checking the axis and change delta */
	if (radioButtonY->Checked) {
		deltaY += deltaLength; // changing by delta length
	}
	/* Checking the axis and change delta */
	if (radioButtonZ->Checked) {
		deltaZ += deltaLength; // changing by delta length
	}
	/* Checking the axis and change delta */
	if (radioButtonAll->Checked) {
		deltaX += deltaLength; // changing by delta length
		deltaY += deltaLength; // changing by delta length
		deltaZ += deltaLength; // changing by delta length
	}
}

void FiguForm::decrementDeltas(double& deltaX, double& deltaY, double& deltaZ, double deltaLength) {
	/* Checking the axis and change delta */
	if (radioButtonX->Checked) {
		deltaX -= deltaLength; // changing by delta length
	}
	/* Checking the axis and change delta */
	if (radioButtonY->Checked) {
		deltaY -= deltaLength; // changing by delta length
	}
	/* Checking the axis and change delta */
	if (radioButtonZ->Checked) {
		deltaZ -= deltaLength; // changing by delta length
	}
	/* Checking the axis and change delta */
	if (radioButtonAll->Checked) {
		deltaX -= deltaLength; // changing by delta length
		deltaY -= deltaLength; // changing by delta length
		deltaZ -= deltaLength; // changing by delta length
	}
}

void FiguForm::drawFigure(PictureBox^ pb, array<double, 2>^ matrix, array<int, 2>^ matrixFace) {
	Graphics^ graphics = Graphics::FromImage(pb->Image); // creating graphics
	try {
		/*for (int i = 0; i < matrix->GetLength(0); ++i) {
			int x0 = matrix[i, 0] / matrix[i, 3], y0 = matrix[i, 1] / matrix[i, 3];
			graphics->DrawRectangle(pen, x0, y0, 1, 1);
		}*/
		for (int i = 0; i < matrixFace->GetLength(0); ++i) {
			int i0 = matrixFace[i, 0], i1 = matrixFace[i, 1], i2 = matrixFace[i, 2]; // getting vertexes
			/* Getting coords */
			int x0 = matrix[i0, 0] / matrix[i0, 3], y0 = matrix[i0, 1] / matrix[i0, 3];
			int x1 = matrix[i1, 0] / matrix[i1, 3], y1 = matrix[i1, 1] / matrix[i1, 3];
			int x2 = matrix[i2, 0] / matrix[i2, 3], y2 = matrix[i2, 1] / matrix[i2, 3];
			/* Drawing */
			graphics->DrawLine(pen, x0, y0, x1, y1);
			graphics->DrawLine(pen, x1, y1, x2, y2);
			graphics->DrawLine(pen, x2, y2, x0, y0);
		}	
	}
	finally {
		if (graphics) {
			delete graphics;
		}
	}
	pb->Refresh();
}

array<double, 2>^ FiguForm::matrixComposition(array<double, 2>^ m1, array<double, 2>^ m2) {
	array<double, 2>^ result = gcnew array<double, 2>(m1->GetLength(0), m2->GetLength(1));
	
	for (int i = 0; i < m1->GetLength(0); ++i) {
		for (int j = 0; j < m2->GetLength(1); ++j) {
			result[i, j] = 0; // filling by zeros
		}
	}


	for (int i = 0; i < m1->GetLength(0); ++i) {
		for (int j = 0; j < m2->GetLength(1); ++j) {
			for (int k = 0; k < m1->GetLength(1); ++k) {
				result[i, j] += m1[i, k] * m2[k, j]; // composing by rows
			}
		}
	}
	return result;
}

array<double, 2>^ FiguForm::formMoveMatrix(double deltaX, double deltaY, double deltaZ) {
	array<double, 2>^ result = gcnew array<double, 2>(4, 4); // creating

	// filling
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				result[i, j] = 1; // 1 on diag
			}
			else {
				result[i, j] = 0; // zero otherwise
			}
		}
	}

	/* Deltas */
	result[3, 0] = deltaX;
	result[3, 1] = deltaY;
	result[3, 2] = deltaZ;

	return result;
}

array<double, 2>^ FiguForm::formXRotateMatrix(double deltaRadX) {
	array<double, 2>^ result = gcnew array<double, 2>(4, 4); // creating

	// filling by zeros
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result[i, j] = 0;
		}
	}

	result[0, 0] = 1;
	result[3, 3] = 1;
	/* Deltas */
	result[1, 1] = Math::Cos(deltaRadX);
	result[2, 2] = Math::Cos(deltaRadX);
	result[1, 2] = Math::Sin(deltaRadX);
	result[2, 1] = - Math::Sin(deltaRadX);

	return result;
}

array<double, 2>^ FiguForm::formYRotateMatrix(double deltaRadY) {
	array<double, 2>^ result = gcnew array<double, 2>(4, 4); // creating

	// filling by zeros
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result[i, j] = 0;
		}
	}

	result[1, 1] = 1;
	result[3, 3] = 1;
	/* Deltas */
	result[0, 0] = Math::Cos(deltaRadY);
	result[2, 2] = Math::Cos(deltaRadY);
	result[0, 2] = Math::Sin(deltaRadY);
	result[2, 0] = -Math::Sin(deltaRadY);

	return result;
}

array<double, 2>^ FiguForm::formZRotateMatrix(double deltaRadZ) {
	array<double, 2>^ result = gcnew array<double, 2>(4, 4); // creating

	// filling by zeros
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result[i, j] = 0;
		}
	}

	result[2, 2] = 1;
	result[3, 3] = 1;
	/* Deltas */
	result[0, 0] = Math::Cos(deltaRadZ);
	result[1, 1] = Math::Cos(deltaRadZ);
	result[0, 1] = Math::Sin(deltaRadZ);
	result[1, 0] = -Math::Sin(deltaRadZ);

	return result;
}

array<double, 2>^ FiguForm::formScaleMatrix(double deltaScaleX, double deltaScaleY, double deltaScaleZ, double generalScale) {
	array<double, 2>^ result = gcnew array<double, 2>(4, 4); // creating

	// filling by zeros
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result[i, j] = 0;
		}
	}


	/* Deltas */
	result[0, 0] = deltaScaleX;
	result[1, 1] = deltaScaleY;
	result[2, 2] = deltaScaleZ;
	result[3, 3] = generalScale;

	return result;
}

void FiguForm::drawInitialFigure() {
	// restoring values
	matrixVert = defaultMatrixVert;
	matrixFace = defaultMatrixFace;
	// some initial transforming
	matrixVert = matrixComposition(matrixVert, formXRotateMatrix(0.3)); // rotating X
	// drawing start Figuure
	drawFigure(pictureBoxFigure, matrixComposition(matrixVert, matrixCurrProj), matrixFace);
}


void FiguForm::initializeMatrices() {

#pragma region tetra

	/* Initializing vertexes  */
	tetraMatrixVert = gcnew array<double, 2>(4, 4);

	// filling
	for (int i = 0; i < tetraMatrixVert->GetLength(0); ++i) {
		tetraMatrixVert[i, 3] = 1;
	}

	tetraMatrixVert[0, 0] = x0;
	tetraMatrixVert[0, 1] = y0;
	tetraMatrixVert[0, 2] = z0;

	tetraMatrixVert[1, 0] = x0 + 100;
	tetraMatrixVert[1, 1] = y0;
	tetraMatrixVert[1, 2] = z0;

	tetraMatrixVert[2, 0] = x0 + 50;
	tetraMatrixVert[2, 1] = y0 + 50 * Math::Sqrt(3);
	tetraMatrixVert[2, 2] = z0;

	tetraMatrixVert[3, 0] = x0 + 50;
	tetraMatrixVert[3, 1] = y0 + 100 * Math::Sqrt(3) / 6;
	tetraMatrixVert[3, 2] = z0 - 100 * Math::Sqrt(6) / 3;

	/* Initializing faces */
	tetraMatrixFace = gcnew array<int, 2>(4, 3);

	tetraMatrixFace[0, 0] = 0;
	tetraMatrixFace[0, 1] = 1;
	tetraMatrixFace[0, 2] = 2;

	tetraMatrixFace[1, 0] = 0;
	tetraMatrixFace[1, 1] = 1;
	tetraMatrixFace[1, 2] = 3;

	tetraMatrixFace[2, 0] = 0;
	tetraMatrixFace[2, 1] = 2;
	tetraMatrixFace[2, 2] = 3;

	tetraMatrixFace[3, 0] = 1;
	tetraMatrixFace[3, 1] = 2;
	tetraMatrixFace[3, 2] = 3;

#pragma endregion

#pragma region octa

	/* Initializing vertexes  */
	octaMatrixVert = gcnew array<double, 2>(6, 4);

	// filling
	for (int i = 0; i < octaMatrixVert->GetLength(0); ++i) {
		octaMatrixVert[i, 3] = 1;
	}

	octaMatrixVert[0, 0] = x0 + 100;
	octaMatrixVert[0, 1] = y0;
	octaMatrixVert[0, 2] = z0;

	octaMatrixVert[1, 0] = x0 + 200;
	octaMatrixVert[1, 1] = y0 + 100;
	octaMatrixVert[1, 2] = z0;

	octaMatrixVert[2, 0] = x0 + 100;
	octaMatrixVert[2, 1] = y0 + 200;
	octaMatrixVert[2, 2] = z0;

	octaMatrixVert[3, 0] = x0 ;
	octaMatrixVert[3, 1] = y0 + 100;
	octaMatrixVert[3, 2] = z0;

	octaMatrixVert[4, 0] = x0 + 100;
	octaMatrixVert[4, 1] = y0 + 100;
	octaMatrixVert[4, 2] = z0 + 100;

	octaMatrixVert[5, 0] = x0 + 100;
	octaMatrixVert[5, 1] = y0 + 100;
	octaMatrixVert[5, 2] = z0 - 100;

	/* Initializing faces */
	octaMatrixFace = gcnew array<int, 2>(8, 3);

	octaMatrixFace[0, 0] = 0;
	octaMatrixFace[0, 1] = 1;
	octaMatrixFace[0, 2] = 5;

	octaMatrixFace[1, 0] = 1;
	octaMatrixFace[1, 1] = 2;
	octaMatrixFace[1, 2] = 5;

	octaMatrixFace[2, 0] = 2;
	octaMatrixFace[2, 1] = 3;
	octaMatrixFace[2, 2] = 5;

	octaMatrixFace[3, 0] = 3;
	octaMatrixFace[3, 1] = 0;
	octaMatrixFace[3, 2] = 5;

	octaMatrixFace[4, 0] = 0;
	octaMatrixFace[4, 1] = 1;
	octaMatrixFace[4, 2] = 4;

	octaMatrixFace[5, 0] = 1;
	octaMatrixFace[5, 1] = 2;
	octaMatrixFace[5, 2] = 4;

	octaMatrixFace[6, 0] = 2;
	octaMatrixFace[6, 1] = 3;
	octaMatrixFace[6, 2] = 4;

	octaMatrixFace[7, 0] = 3;
	octaMatrixFace[7, 1] = 0;
	octaMatrixFace[7, 2] = 4;

#pragma endregion

#pragma region ico

	/* Initializing vertexes */
	icoMatrixVert = gcnew array<double, 2>(12, 4);
	double rad = 100;
	icoMatrixVert[0, 0] = x0;
	icoMatrixVert[0, 1] = y0 - rad * (Math::Sqrt(5)/2.0 - 0.5);
	icoMatrixVert[0, 2] = z0;
	icoMatrixVert[0, 3] = 1;

	double s = Math::PI / 5; // step
	for (int i = 1; i < 11; ++i) {
		icoMatrixVert[i, 0] = x0 + rad * Math::Sin(i * s);
		icoMatrixVert[i, 1] = i % 2 != 0 ? y0 : y0 + rad;
		icoMatrixVert[i, 2] = z0 + rad * Math::Cos(i * s);
		icoMatrixVert[i, 3] = 1;
	}

	icoMatrixVert[11, 0] = x0;
	icoMatrixVert[11, 1] = y0 + rad + rad * (Math::Sqrt(5) / 2.0 - 0.5);
	icoMatrixVert[11, 2] = z0;
	icoMatrixVert[11, 3] = 1;
	
	/* Initializing faces */
	icoMatrixFace = gcnew array<int, 2>(28, 3);
	
	for (int i = 0; i < 5; ++i) { // top
		icoMatrixFace[i, 0] = 0;
		icoMatrixFace[i, 1] = 2 * i + 1;
		icoMatrixFace[i, 2] = (2 * i + 3) % 10;
	}

	for (int k = 5; k < 10; ++k) { // bottom
		int i = k - 5;
		icoMatrixFace[k, 0] = 11;
		icoMatrixFace[k, 1] = (2 * i + 3) % 10 + 1;
		icoMatrixFace[k, 2] = 2 * i + 2;
	}

	for (int k = 10; k < 18; ++k) { 
		int i = k - 9;
		icoMatrixFace[k, 0] = i % 2 == 0 ? i : i + 1;
		icoMatrixFace[k, 1] = i % 2 == 0 ? i + 1: i;
		icoMatrixFace[k, 2] = i + 1;
	}

	icoMatrixFace[18, 0] = 9;
	icoMatrixFace[18, 1] = 10;
	icoMatrixFace[18, 2] = 1;

	icoMatrixFace[19, 0] = 1;
	icoMatrixFace[19, 1] = 10;
	icoMatrixFace[19, 2] = 2;



#pragma endregion

#pragma region sphere, fruit and ellipsoid

	/* Initializing vertexes */
	int part = 10; // partition
	sphereMatrixVert = gcnew array<double, 2>(2 * (part + 1) * part, 4);
	fruitMatrixVert = gcnew array<double, 2>(2 * (part + 1) * part, 4);
	ellMatrixVert = gcnew array<double, 2>(2 * (part + 1) * part, 4);
	double R = 100; // radius
	double t = Math::PI / part; // step
	int i = 0;
	double distort = (1 + 0.5 * Math::Abs(Math::Sin(Math::PI / 2))); // for distorting
	for (int i1 = 0; i1 < part + 1; ++i1) {
		for (int i2 = 0; i2 < 2 * part; ++i2) { // filling
			double k1 = i1 * t, k2 = i2 * t;
			double x = x0 + R * Math::Sin(k1) * Math::Cos(k2); // calc x
			sphereMatrixVert[i, 0] = x;
			fruitMatrixVert[i, 0] = x;
			ellMatrixVert[i, 0] = x;

			double y = y0 + R * Math::Cos(k1) * Math::Cos(k2); // calc y
			sphereMatrixVert[i, 1] = y;
			fruitMatrixVert[i, 1] = y;
			ellMatrixVert[i, 1] = y;
			
			double z = z0 + R * Math::Sin(k2); // calc z
			sphereMatrixVert[i, 2] = z;
			fruitMatrixVert[i, 2] = z <= R / 2 ? z : z + 2.5 * R * (z / R - 0.5) * (z / R - 0.5); // distorting
			ellMatrixVert[i, 2] = 2 * z;

			sphereMatrixVert[i, 3] = 1;
			fruitMatrixVert[i, 3] = 1;
			ellMatrixVert[i, 3] = 1;
			++i;
		}
	}

	/* Initializing faces */
	sphereMatrixFace = gcnew array<int, 2>(2 * (sphereMatrixVert->GetLength(0) - 2 * part - 1), 3);
	fruitMatrixFace = gcnew array<int, 2>(2 * (sphereMatrixVert->GetLength(0) - 2 * part - 1), 3);
	ellMatrixFace = gcnew array<int, 2>(2 * (sphereMatrixVert->GetLength(0) - 2 * part - 1), 3);
	i = 0;
	for (; i < sphereMatrixVert->GetLength(0) - 2 * part - 1; ++i) {

		int i1 = i + 2 * part;
		int i2 = i + 2 * part + 1;

		// the first one
		fruitMatrixFace[2 * i, 0] = i;
		sphereMatrixFace[2 * i, 0] = i;
		ellMatrixFace[2 * i, 0] = i;
		fruitMatrixFace[2 * i, 1] = i + 1;
		sphereMatrixFace[2 * i, 1] = i + 1;
		ellMatrixFace[2 * i, 1] = i + 1;
		fruitMatrixFace[2 * i, 2] = i1;
		sphereMatrixFace[2 * i, 2] = i1;
		ellMatrixFace[2 * i, 2] = i1;

		// and the other one
		fruitMatrixFace[2 * i + 1, 0] = i + 1;
		sphereMatrixFace[2 * i + 1, 0] = i + 1;
		ellMatrixFace[2 * i + 1, 0] = i + 1;
		fruitMatrixFace[2 * i + 1, 1] = i1;
		sphereMatrixFace[2 * i + 1, 1] = i1;
		ellMatrixFace[2 * i + 1, 1] = i1;
		fruitMatrixFace[2 * i + 1, 2] = i2;
		sphereMatrixFace[2 * i + 1, 2] = i2;
		ellMatrixFace[2 * i + 1, 2] = i2;
	}

#pragma endregion

#pragma region tor and spiral

	/* Initializing vertexes */
	part = 10; // partition
	torMatrixVert = gcnew array<double, 2>(4 * (part + 1) * part, 4);
	spiralMatrixVert = gcnew array<double, 2>(4 * (part + 1) * part, 4);
	R = 100; // radius
	double Rspiral = R;
	double r = 50;
	t = Math::PI / part; // step
	i = 0;
	distort = (1 + 0.5 * Math::Abs(Math::Sin(Math::PI / 2))); // for distorting
	for (int i1 = 0; i1 < 2 * part + 2; ++i1) {
		for (int i2 = 0; i2 < 2 * part; ++i2) { // filling
			double k1 = i1 * t, k2 = i2 * t;
			Rspiral = k2 * 40;
			torMatrixVert[i, 0] = x0 + (R + r * Math::Cos(k1)) * Math::Cos(k2); // calc x
			spiralMatrixVert[i, 0] = x0 + (Rspiral + r * Math::Cos(k1)) * Math::Cos(k2); // calc x for spiral

			torMatrixVert[i, 1] = y0 + (R + r * Math::Cos(k1)) * Math::Sin(k2); // calc y
			spiralMatrixVert[i, 1] = y0 + (Rspiral + r * Math::Cos(k1)) * Math::Sin(k2); // calc y for spiral

			torMatrixVert[i, 2] = z0 + r * Math::Sin(k1); // calc z
			spiralMatrixVert[i, 2] = z0 + r * Math::Sin(k1); // calc zfor spiral

			torMatrixVert[i, 3] = 1;
			spiralMatrixVert[i, 3] = 1;
			++i;
		}
	}

	/* Initializing faces */
	torMatrixFace = gcnew array<int, 2>(2 * (torMatrixVert->GetLength(0) - 2 * part - 1), 3);
	spiralMatrixFace = gcnew array<int, 2>(2 * (torMatrixVert->GetLength(0) - 2 * part - 1), 3);
	i = 0;
	for (; i < torMatrixVert->GetLength(0) - 2 * part - 1; ++i) {
		int i1 = i + 2 * part;
		int i2 = i + 2 * part + 1;

		// the first one
		spiralMatrixFace[2 * i, 0] = i;
		torMatrixFace[2 * i, 0] = i;
		spiralMatrixFace[2 * i, 1] = i + 1;
		torMatrixFace[2 * i, 1] = i + 1;
		spiralMatrixFace[2 * i, 2] = i1;
		torMatrixFace[2 * i, 2] = i1;

		// and the other one
		spiralMatrixFace[2 * i + 1, 0] = i + 1;
		torMatrixFace[2 * i + 1, 0] = i + 1;
		spiralMatrixFace[2 * i + 1, 1] = i1;
		torMatrixFace[2 * i + 1, 1] = i1;
		spiralMatrixFace[2 * i + 1, 2] = i2;
		torMatrixFace[2 * i + 1, 2] = i2;
	}

#pragma endregion

	/* Initializing projection matrices */
	matrixOrtProj = gcnew array<double, 2>(4, 4);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			matrixOrtProj[i, j] = 0; // filling by zeros
		}
	}

	matrixOrtProj[0, 0] = 1;
	matrixOrtProj[1, 1] = 1;
	matrixOrtProj[3, 3] = 1;

	defaultMatrixVert = tetraMatrixVert;
	defaultMatrixFace = tetraMatrixFace;
	state = 0;
}
