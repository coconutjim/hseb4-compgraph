#include "FiguForm.h"
#include <fstream>

using namespace std;
using namespace Figure;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 7. Z-буфер
Среда разработки: Visual Studio 2013
Дата: 16.11.2015
Реализованы алгоритм z-буфера, отрисовка самого z-буфера и плоская закраска объектов.
Подробнее см. в меню "О программе".
*/

void FiguForm::clearPictureBox(PictureBox^ pb, Color^ color) {
	Graphics^ graphics = Graphics::FromImage(pb->Image); // creating graphics
	try {
		graphics->Clear(*color); // clearing
	}
	finally {
		if (graphics) {
			delete graphics;
		}
	}
	pb->Refresh();
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

void FiguForm::calculateVectorComposition(double x1, double y1, double z1,
	double x2, double y2, double z2,
	double x3, double y3, double z3,
	double& xRes, double& yRes, double& zRes) {

	// Fiest vector
	double v1X = x2 - x1;
	double v1Y = y2 - y1;
	double v1Z = z2 - z1;

	// Second vector
	double v2X = x3 - x1;
	double v2Y = y3 - y1;
	double v2Z = z3 - z1;

	// Composition
	xRes = v1Y * v2Z - v1Z * v2Y;
	yRes = v1Z * v2Z - v1X * v2Z;
	zRes = v1X * v2Y - v1Y * v2X;

	// Finding length
	double length = Math::Sqrt(xRes * xRes + yRes * yRes + zRes * zRes);

	if (length != 0) {
		// Norming
		xRes /= length;
		yRes /= length;
		zRes /= length;
	}

}

Color^ FiguForm::defineColorForFace(int index, array<double, 2>^ matrixVert, array<int, 2>^ matrixFace, Color^ color) {
	// Get normal
	int p1 = matrixFace[index, 0];
	int p2 = matrixFace[index, 1];
	int p3 = matrixFace[index, 2];
	double xRes = 0, yRes = 0, zRes = 0;
	// Calculate compositoin
	calculateVectorComposition(matrixVert[p1, 0], matrixVert[p1, 1], matrixVert[p1, 2],
		matrixVert[p2, 0], matrixVert[p2, 1], matrixVert[p2, 2],
		matrixVert[p3, 0], matrixVert[p3, 1], matrixVert[p3, 2],
		xRes, yRes, zRes);

	// Finding cosinus abs via scalar composition with (0, 0, 1)
	double cosinus = Math::Abs(zRes); // simplified
	
	// Changing color
	int argb = color->ToArgb(); 
	int r = ((argb & 0x00FF0000) >> 16) * cosinus;
	int g = ((argb & 0x0000FF00) >> 8) * cosinus;
	int b = (argb & 0x000000FF) * cosinus;
	return Color::FromArgb(255, r, g, b);

}

void FiguForm::changePointLocation(double& x1, double& y1, double& z1,
	double& x2, double& y2, double& z2,
	double& x3, double& y3, double& z3) {
	// "sotring" points
	if ((y2 < y1)) {
		swap(x1, x2);
		swap(y1, y2);
		swap(z1, z2);
	}
	if (y3 < y2) {
		swap(x2, x3);
		swap(y2, y3);
		swap(z2, z3);
	}
	if (y1 < y2) {
		swap(x1, x2);
		swap(y1, y2);
		swap(z1, z2);
	}
}

void FiguForm::swap(double& x, double& y) {
	// swapping two values
	double temp = x;
	x = y;
	y = temp;
}

void FiguForm::drawFigure(array<double, 2>^ matrixVert, array<int, 2>^ matrixFace, Color^ color) {
	// Through all faces
	for (int i = 0; i < matrixFace->GetLength(0); ++i) {
		// Defining color for this vertex
		Color^ currColor = defineColorForFace(i, matrixVert, matrixFace, color);
		// Getting vertexes
		int p1 = matrixFace[i, 0];
		int p2 = matrixFace[i, 1];
		int p3 = matrixFace[i, 2];
		double x1 = matrixVert[p1, 0];
		double y1 = matrixVert[p1, 1];
		double z1 = matrixVert[p1, 2];
		double x2 = matrixVert[p2, 0];
		double y2 = matrixVert[p2, 1];
		double z2 = matrixVert[p2, 2];
		double x3 = matrixVert[p3, 0];
		double y3 = matrixVert[p3, 1];
		double z3 = matrixVert[p3, 2];
		// changing points to fit it to the triangle ABC (like triangle in the presentation)
		changePointLocation(x1, y1, z1, x2, y2, z2, x3, y3, z3);
		// if first half exists
		if (y2 != y1) {
			// first half
			for (double yy1 = y2; yy1 <= y1; yy1+=0.5) {
				if (yy1 < 0 || yy1 >= zBuffer->GetLength(1)) {
					continue;
				}
				double xq = x2 + (x1 - x2) * (yy1 - y2) / (y1 - y2);
				double xr = x2 + (x3 - x2) * (yy1 - y2) / (y3 - y2);
				double zq = z2 + (z1 - z2) * (yy1 - y2) / (y1 - y2);
				double zr = z2 + (z3 - z2) * (yy1 - y2) / (y3 - y2);
				// checking what is righter
				if (xq > xr) {
					swap(xq, xr);
				}
				for (double xx1 = xq; xx1 < xr; xx1+=0.5) {
					if (xx1 < 0 || xx1 >= zBuffer->GetLength(0)) {
						continue;
					}
					// finding z-point
					double zp = zq + (zr - zq) * (xx1 - xq) / (xr - xq);
					int xxx = (int)xx1;
					int yyy = (int)yy1;
					// check if we can see it
					if (zp < zBuffer[xxx, yyy]) {
						// Updating buffer
						zBuffer[xxx, yyy] = zp;
						// Filling bitmaps
						bitmapFigu->SetPixel(xxx, yyy, *currColor);
						int temp = (int)(90 + zp / 2);
						int value = temp < 0 ? 0 : temp > 255 ? 255 : temp;
						Color col = Color::FromArgb(255, value, value, value);
						bitmapZBuff->SetPixel(xxx, yyy, col);
					}
				}
			}
		}
		// if second half exists
		if (y3 == y1) {
			continue;
		}
		// second half
		for (double yy2 = y3; yy2 > y1; yy2-=0.5) {
			if (yy2 < 0 || yy2 >= zBuffer->GetLength(1)) {
				continue;
			}
			double xq = x3 + (x1 - x3) * (yy2 - y3) / (y1 - y3);
			double xr = x3 + (x2 - x3) * (yy2 - y3) / (y2 - y3);
			double zq = z3 + (z1 - z3) * (yy2 - y3) / (y1 - y3);
			double zr = z3 + (z2 - z3) * (yy2 - y3) / (y2 - y3);
			// checking what is righter
			if (xq > xr) {
				swap(xq, xr);
			}
			for (double xx2 = xq; xx2 < xr; xx2+=0.5) {
				if (xx2 < 0 || xx2 >= zBuffer->GetLength(0)) {
					continue;
				}
				// finding z-point
				double zp = zq + (zr - zq) * (xx2 - xq) / (xr - xq);
				int xxx = (int)xx2;
				int yyy = (int)yy2;
				// check if we can see it
				if (zp < zBuffer[xxx, yyy]) {
					// Updating buffer
					zBuffer[xxx, yyy] = zp;
					// Filling bitmaps
					bitmapFigu->SetPixel(xxx, yyy, *currColor);
					int temp = (int)(90 + zp / 2);
					int value = temp < 0 ? 0 : temp > 255 ? 255 : temp;
					Color col = Color::FromArgb(255, value, value, value);
					bitmapZBuff->SetPixel(xxx, yyy, col);
				}
			}
		}
	}
	pictureBoxFigure->Refresh();
	pictureBoxZBuffer->Refresh();
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

void FiguForm::prepareScene() {
	// restoring values
	tor1MatrixVert = torMatrixVert;
	tor2MatrixVert = torMatrixVert;
	tor3MatrixVert = torMatrixVert;
	// some initial transforming
	tor1MatrixVert = matrixComposition(tor1MatrixVert, formMoveMatrix(-100, 0, 0)); // moving X
	tor1MatrixVert = matrixComposition(tor1MatrixVert, formXRotateMatrix(-Math::PI / 8)); // rotating X
	tor2MatrixVert = matrixComposition(tor2MatrixVert, formXRotateMatrix(Math::PI / 8)); // rotating X
	tor3MatrixVert = matrixComposition(tor3MatrixVert, formMoveMatrix(100, 0, 0)); // moving X
	// what to vhange
	state = 1;
	labelWhatTor->Text = "Изменяем тор 1";
	// drawing scene
	drawScene();
}

void FiguForm::drawScene() {

	// Clearing
	clearPictureBox(pictureBoxFigure, colorDialogBg->Color); 
	clearPictureBox(pictureBoxZBuffer, Color::White);

	// Filling z-buffer
	for (int i = 0; i < zBuffer->GetLength(0); ++i) {
		for (int j = 0; j < zBuffer->GetLength(1); ++j) {
			zBuffer[i, j] = INT_MAX;
		}
	}

	// Drawing
	drawFigure(tor1MatrixVert, torMatrixFace, colorDialogTor1->Color);
	drawFigure(tor2MatrixVert, torMatrixFace, colorDialogTor2->Color);
	drawFigure(tor3MatrixVert, torMatrixFace, colorDialogTor3->Color);
}


void FiguForm::initializeMatrices() {

	// Initializing z-buffer
	zBuffer = gcnew array<double, 2>(pictureBoxFigure->Width, pictureBoxFigure->Height);


#pragma region sphere

	/* Initializing vertexes */
	int part = 10; // partition
	sphereMatrixVert = gcnew array<double, 2>(2 * (part + 1) * part, 4);
	double R = 100; // radius
	double t = Math::PI / part; // step
	int i = 0;
	double distort = (1 + 0.5 * Math::Abs(Math::Sin(Math::PI / 2))); // for distorting
	for (int i1 = 0; i1 < part + 1; ++i1) {
		for (int i2 = 0; i2 < 2 * part; ++i2) { // filling
			double k1 = i1 * t, k2 = i2 * t;
			double x = x0 + R * Math::Sin(k1) * Math::Cos(k2); // calc x
			sphereMatrixVert[i, 0] = x;

			double y = y0 + R * Math::Cos(k1) * Math::Cos(k2); // calc y
			sphereMatrixVert[i, 1] = y;
			
			double z = z0 + R * Math::Sin(k2); // calc z
			sphereMatrixVert[i, 2] = z;

			sphereMatrixVert[i, 3] = 1;
			++i;
		}
	}

	/* Initializing faces */
	sphereMatrixFace = gcnew array<int, 2>(2 * (sphereMatrixVert->GetLength(0) - 2 * part - 1), 3);
	i = 0;
	for (; i < sphereMatrixVert->GetLength(0) - 2 * part - 1; ++i) {

		int i1 = i + 2 * part;
		int i2 = i + 2 * part + 1;

		// the first one
		sphereMatrixFace[2 * i, 0] = i;
		sphereMatrixFace[2 * i, 1] = i + 1;
		sphereMatrixFace[2 * i, 2] = i1;

		// and the other one
		sphereMatrixFace[2 * i + 1, 0] = i + 1;
		sphereMatrixFace[2 * i + 1, 1] = i1;
		sphereMatrixFace[2 * i + 1, 2] = i2;
	}

#pragma endregion

#pragma region tor

	// Initializing vertexes 
	part = 10; // partition
	torMatrixVert = gcnew array<double, 2>(4 * (part + 1) * part, 4);
	R = 50; // radius
	double Rspiral = R;
	double r = 25;
	t = Math::PI / part; // step
	i = 0;
	distort = (1 + 0.5 * Math::Abs(Math::Sin(Math::PI / 2))); // for distorting
	for (int i1 = 0; i1 < 2 * part + 2; ++i1) {
		for (int i2 = 0; i2 < 2 * part; ++i2) { // filling
			double k1 = i1 * t, k2 = i2 * t;
			Rspiral = k2 * 40;
			torMatrixVert[i, 0] = x0 + (R + r * Math::Cos(k1)) * Math::Cos(k2); // calc x
			torMatrixVert[i, 1] = y0 + (R + r * Math::Cos(k1)) * Math::Sin(k2); // calc y
			torMatrixVert[i, 2] = z0 + r * Math::Sin(k1); // calc z
			torMatrixVert[i, 3] = 1;
			++i;
		}
	}

	// Initializing faces 
	torMatrixFace = gcnew array<int, 2>(2 * (torMatrixVert->GetLength(0) - 2 * part - 1), 3);
	i = 0;
	for (; i < torMatrixVert->GetLength(0) - 2 * part - 1; ++i) {
		int i1 = i + 2 * part;
		int i2 = i + 2 * part + 1;

		// the first one
		torMatrixFace[2 * i, 0] = i;
		torMatrixFace[2 * i, 1] = i + 1;
		torMatrixFace[2 * i, 2] = i1;

		// and the other one
		torMatrixFace[2 * i + 1, 0] = i + 1;
		torMatrixFace[2 * i + 1, 1] = i1;
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
}
