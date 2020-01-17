#include "FiguForm.h"
#include <fstream>

using namespace std;
using namespace Figure;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 8. Текстуры
Среда разработки: Visual Studio 2013
Дата: 26.11.2015
Реализовано наложение текстур, загрузка текстуры из файла и изменения скорости вращений.
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
	double& x3, double& y3, double& z3,
	double& xt1, double& yt1, double& xt2,
	double& yt2, double& xt3, double& yt3) {
	// "sotring" points
	if ((y2 < y1)) {
		swap(x1, x2);
		swap(y1, y2);
		swap(z1, z2);
		swap(xt1, xt2);
		swap(yt1, yt2);
	}
	if (y3 < y2) {
		swap(x2, x3);
		swap(y2, y3);
		swap(z2, z3);
		swap(xt2, xt3);
		swap(yt2, yt3);
	}
	if (y1 < y2) {
		swap(x1, x2);
		swap(y1, y2);
		swap(z1, z2);
		swap(xt1, xt2);
		swap(yt1, yt2);
	}
}

void FiguForm::swap(double& x, double& y) {
	// swapping two values
	double temp = x;
	x = y;
	y = temp;
}

void FiguForm::drawPixel(int x, int y, double xt, double yt, Bitmap^ texture) {
	//if (xt > 1 || xt < 0 || yt > 1 || yt < 0) {
	//	return;
	//}
	xt = xt > 1 ? 1 : xt < 0 ? 0 : xt;
	yt = yt > 1 ? 1 : yt < 0 ? 0 : yt;
	xt *= texture->Width;
	yt *= texture->Height;
	xt = xt >= texture->Width ? texture->Width - 1 : xt;
	yt = yt >= texture->Height ? texture->Height - 1 : yt;
	bitmapFigu->SetPixel(x, y, texture->GetPixel(xt, yt));
}

void FiguForm::drawFigure(array<double, 2>^ matrixVert, array<double, 2>^ matrixVertTexture, array<int, 2>^ matrixFace, Bitmap^ texture) {
	// Through all faces
	for (int i = 0; i < matrixFace->GetLength(0); ++i) {
		// Getting vertexes
		int p1 = matrixFace[i, 0];
		int p2 = matrixFace[i, 1];
		int p3 = matrixFace[i, 2];
		double x1 = matrixVert[p1, 0], xt1 = matrixVertTexture[p1, 0];
		double y1 = matrixVert[p1, 1], yt1 = matrixVertTexture[p1, 1];
		double z1 = matrixVert[p1, 2];
		double x2 = matrixVert[p2, 0], xt2 = matrixVertTexture[p2, 0];
		double y2 = matrixVert[p2, 1], yt2 = matrixVertTexture[p2, 1];
		double z2 = matrixVert[p2, 2];
		double x3 = matrixVert[p3, 0], xt3 = matrixVertTexture[p3, 0];
		double y3 = matrixVert[p3, 1], yt3 = matrixVertTexture[p3, 1];
		double z3 = matrixVert[p3, 2];
		// correcting
		bool correction = ((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) * ((xt2 - xt1) * (yt3 - yt1) - (yt2 - yt1) * (xt3 - xt1)) < 0;
		if (correction) {
			if (xt1 < 0.5) {
				++xt1;
			}
			if (xt2 < 0.5) {
				++xt2;
			}
			if (xt3 < 0.5) {
				++xt3;
			}
		}
		// calculating coeffs
		double delta = x1 * (y2 - y3) - y1 * (x2 - x3) + (x2 * y3 - x3 * y2);
		double cA = delta == 0? 0 : ((y2 - y3) * xt1 - (xt2 - xt3) * y1 + (xt2 * y3 - xt3 * y2) ) / delta;
		double cB = delta == 0 ? 0 : ((xt2 - xt3) * x1 - (x2 - x3) * xt1 + (x2 * xt3 - x3 * xt2)) / delta;
		double cC = delta == 0 ? 0 : ((y2 * xt3 - y3 * xt2) * x1 - (x2 * xt3 - x3 * xt2) * y1 + (x2 * y3 - x3 * y2) * xt1) / delta;
		double cD = delta == 0 ? 0 : ((y2 - y3) * yt1 - (yt2 - yt3) * y1 + (yt2 * y3 - yt3 * y2)) / delta;
		double cE = delta == 0 ? 0 : ((yt2 - yt3) * x1 - (x2 - x3) * yt1 + (x2 * yt3 - x3 * yt2)) / delta;
		double cF = delta == 0 ? 0 : ((y2 * yt3 - y3 * yt2) * x1 - (x2 * yt3 - x3 * yt2) * y1 + (x2 * y3 - x3 * y2) * yt1) / delta;
		// changing points to fit it to the triangle ABC (like triangle in the presentation)
		changePointLocation(x1, y1, z1, x2, y2, z2, x3, y3, z3, xt1, yt1, xt2, yt2, xt3, yt3);
		// if first half exists
		if (y2 != y1) {
			// first half
			for (double yy1 = y2; yy1 <= y1; yy1 += 0.5) {
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
				for (double xx1 = xq; xx1 < xr; xx1 += 0.5) {
					if (xx1 < 0 || xx1 >= zBuffer->GetLength(0)) {
						continue;
					}
					// finding z-point
					double zp = zq + (zr - zq) * (xx1 - xq) / (xr - xq);
					int xxx = (int)xx1;
					int yyy = (int)yy1;
					double xxxt = cA * xx1 + cB * yy1 + cC;
					double yyyt = cD * xx1 + cE * yy1 + cF;
					// check if we can see it
					if (zp < zBuffer[xxx, yyy]) {
						// Updating buffer
						zBuffer[xxx, yyy] = zp;
						// Drawing
						if (correction && xxxt > 1) {
							drawPixel(xxx, yyy, xxxt - 1, yyyt, texture);
						}
						else {
							drawPixel(xxx, yyy, xxxt, yyyt, texture);
						}
					}
				}
			}
		}
		// if second half exists
		if (y3 == y1) {
			continue;
		}
		// second half
		for (double yy2 = y3; yy2 > y1; yy2 -= 0.5) {
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
			for (double xx2 = xq; xx2 < xr; xx2 += 0.5) {
				if (xx2 < 0 || xx2 >= zBuffer->GetLength(0)) {
					continue;
				}
				// finding z-point
				double zp = zq + (zr - zq) * (xx2 - xq) / (xr - xq);
				int xxx = (int)xx2;
				int yyy = (int)yy2;
				double xxxt = cA * xx2 + cB * yy2 + cC;
				double yyyt = cD * xx2 + cE * yy2 + cF;
				// check if we can see it
				if (zp < zBuffer[xxx, yyy]) {
					// Updating buffer
					zBuffer[xxx, yyy] = zp;
					// Drawing
					if (correction && xxxt > 1) {
						drawPixel(xxx, yyy, xxxt - 1, yyyt, texture);
					}
					else {
						drawPixel(xxx, yyy, xxxt, yyyt, texture);
					}
				}
			}
		}
	}
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

void FiguForm::prepareScene(PictureBox^ pb, Bitmap^ bp, Color^ color) {
	timer->Stop(); // stopping the timer
	// change buttond visibility
	buttonStart->Visible = false;
	buttonPause->Visible = true;
	// restoring values
	torMatrixVert = torDefaultMatrixVert;
	torCentVert = torDefaultCentVert;
	sphereMatrixVert = sphereDefaultMatrixVert;
	sphereCentVert = sphereDefaultCentVert;
	// some initiate transforming
	sphereMatrixVert = matrixComposition(sphereMatrixVert, formMoveMatrix(300, 0, 0));
	sphereCentVert = matrixComposition(sphereCentVert, formMoveMatrix(300, 0, 0));
	// drawing scene
	drawScene(pb, bp, color);
	timer->Start(); // starting the timer
}

void FiguForm::drawScene(PictureBox^ pb, Bitmap^ bp, Color^ color) {

	// Clearing
	try {
		clearPictureBox(pb, color);
	}
	catch (Exception^ e) {
		// :(
	}

	// Filling z-buffer
	for (int i = 0; i < zBuffer->GetLength(0); ++i) {
		for (int j = 0; j < zBuffer->GetLength(1); ++j) {
			zBuffer[i, j] = INT_MAX;
		}
	}

	// Drawing
	try {
		drawFigure(torMatrixVert, torMatrixVertTexture, torMatrixFace, bitmapTextureTor);
		drawFigure(sphereMatrixVert, sphereMatrixVertTexture, sphereMatrixFace, bitmapTextureSphere);
		pb->Image = bp;
	}
	catch (InvalidOperationException^ e) {
		// :(
	}
}

void FiguForm::timerAction(Object^ obj, ElapsedEventArgs^ args) {
	// Rotating tor (self axis)
	torMatrixVert = matrixComposition(torMatrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0));
	torCentVert = matrixComposition(torCentVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0));
	torMatrixVert = matrixComposition(torMatrixVert, formYRotateMatrix(speedTorSelfAxis / 15.0));
	torCentVert = matrixComposition(torCentVert, formYRotateMatrix(speedTorSelfAxis / 15.0));
	torMatrixVert = matrixComposition(torMatrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0));
	torCentVert = matrixComposition(torCentVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0));
	// Rotating sphere (self axis)
	sphereMatrixVert = matrixComposition(sphereMatrixVert, formMoveMatrix(-sphereCentVert[0, 0], -sphereCentVert[0, 1], -sphereCentVert[0, 2]));
	sphereMatrixVert = matrixComposition(sphereMatrixVert, formYRotateMatrix(speedSphereSelfAxis / 15.0));
	sphereMatrixVert = matrixComposition(sphereMatrixVert, formMoveMatrix(sphereCentVert[0, 0], sphereCentVert[0, 1], sphereCentVert[0, 2]));
	// Rotating sphere (Y axis)
	sphereMatrixVert = matrixComposition(sphereMatrixVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0));
	sphereCentVert = matrixComposition(sphereCentVert, formMoveMatrix(-pictureBoxFigure->Width / 2, -pictureBoxFigure->Height / 2, 0));
	sphereMatrixVert = matrixComposition(sphereMatrixVert, formYRotateMatrix(speedSphereYAxis / 15.0));
	sphereCentVert = matrixComposition(sphereCentVert, formYRotateMatrix(speedSphereYAxis / 15.0));
	sphereMatrixVert = matrixComposition(sphereMatrixVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0));
	sphereCentVert = matrixComposition(sphereCentVert, formMoveMatrix(pictureBoxFigure->Width / 2, pictureBoxFigure->Height / 2, 0));
	drawScene(pictureBoxFigure, bitmapFigu, colorDialogBg->Color); // drawing
}

void FiguForm::initializeMatrices(int width, int height) {

	// Initializing z-buffer
	zBuffer = gcnew array<double, 2>(width, height);


#pragma region sphere

	// Initializing vertexes 
	int part = 10; // partition
	sphereDefaultMatrixVert = gcnew array<double, 2>(2 * (part + 1) * part, 4);
	double R = 140; // radius
	double t = Math::PI / part; // step
	int i = 0;
	double xAv = 0, yAv = 0, zAv = 0;
	for (int i1 = 0; i1 < part + 1; ++i1) {
		for (int i2 = 0; i2 < 2 * part; ++i2) { // filling
			double k1 = i1 * t, k2 = i2 * t;
			sphereDefaultMatrixVert[i, 0] = x0 + R * Math::Sin(k1) * Math::Cos(k2); // calc x
			xAv += sphereDefaultMatrixVert[i, 0];
			sphereDefaultMatrixVert[i, 1] = y0 + R * Math::Cos(k1) * Math::Cos(k2); // calc y
			yAv += sphereDefaultMatrixVert[i, 1];
			sphereDefaultMatrixVert[i, 2] = z0 + R * Math::Sin(k2); // calc z
			zAv += sphereDefaultMatrixVert[i, 2];
			sphereDefaultMatrixVert[i, 3] = 1;
			++i;
		}
	}
	xAv /= sphereDefaultMatrixVert->GetLength(0);
	yAv /= sphereDefaultMatrixVert->GetLength(0);
	zAv /= sphereDefaultMatrixVert->GetLength(0);
	// Filling cent vertex
	sphereDefaultCentVert = gcnew array<double, 2>(1, 4);
	sphereDefaultCentVert[0, 0] = xAv;
	sphereDefaultCentVert[0, 1] = yAv;
	sphereDefaultCentVert[0, 2] = zAv;
	sphereDefaultCentVert[0, 3] = 1;

	// Initializing texture matrix
	sphereMatrixVertTexture = gcnew array<double, 2>(sphereDefaultMatrixVert->GetLength(0), 2);
	i = 0;
	for (; i < sphereDefaultMatrixVert->GetLength(0); ++i) {
		// finding vector to center
		double xVect = xAv - sphereDefaultMatrixVert[i, 0];
		double yVect = yAv - sphereDefaultMatrixVert[i, 1];
		double zVect = zAv - sphereDefaultMatrixVert[i, 2];
		// norming
		double length = Math::Sqrt(xVect * xVect + yVect * yVect + zVect * zVect);
		xVect /= length;
		yVect /= length;
		zVect /= length;
		// calculating
		sphereMatrixVertTexture[i, 0] = 0.5 + Math::Atan2(zVect, xVect) / (2 * Math::PI);
		sphereMatrixVertTexture[i, 1] = 0.5 - Math::Asin(yVect) / Math::PI;
	}

	// Initializing faces
	sphereMatrixFace = gcnew array<int, 2>(2 * (sphereDefaultMatrixVert->GetLength(0) - 2 * part - 1), 3);
	i = 0;
	for (; i < sphereDefaultMatrixVert->GetLength(0) - 2 * part - 1; ++i) {

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
	part = 40; // partition
	torDefaultMatrixVert = gcnew array<double, 2>(4 * (part + 1) * part, 4);
	R = 70; // radius
	double Rspiral = R;
	double r = 35;
	t = Math::PI / part; // step
	i = 0;
	xAv = 0;
	yAv = 0;
	zAv = 0;
	for (int i1 = 0; i1 < 2 * part + 2; ++i1) {
		for (int i2 = 0; i2 < 2 * part; ++i2) { // filling
			double k1 = i1 * t, k2 = i2 * t;
			Rspiral = k2 * 40;
			torDefaultMatrixVert[i, 0] = x0 + (R + r * Math::Cos(k1)) * Math::Cos(k2); // calc x
			xAv += torDefaultMatrixVert[i, 0];
			torDefaultMatrixVert[i, 1] = y0 + (R + r * Math::Cos(k1)) * Math::Sin(k2); // calc y
			yAv += torDefaultMatrixVert[i, 1];
			torDefaultMatrixVert[i, 2] = z0 + r * Math::Sin(k1); // calc z
			zAv += torDefaultMatrixVert[i, 2];
			torDefaultMatrixVert[i, 3] = 1;
			++i;
		}
	}
	xAv /= torDefaultMatrixVert->GetLength(0);
	yAv /= torDefaultMatrixVert->GetLength(0);
	zAv /= torDefaultMatrixVert->GetLength(0);
	// Filling cent vertex
	torDefaultCentVert = gcnew array<double, 2>(1, 4);
	torDefaultCentVert[0, 0] = xAv;
	torDefaultCentVert[0, 1] = yAv;
	torDefaultCentVert[0, 2] = zAv;
	torDefaultCentVert[0, 3] = 1;

	// Initializing texture matrix
	torMatrixVertTexture = gcnew array<double, 2>(torDefaultMatrixVert->GetLength(0), 2);
	i = 0;
	for (; i < torDefaultMatrixVert->GetLength(0); ++i) {
		// finding vector to center
		double xVect = xAv - torDefaultMatrixVert[i, 0];
		double yVect = yAv - torDefaultMatrixVert[i, 1];
		double zVect = zAv - torDefaultMatrixVert[i, 2];
		// norming
		double length = Math::Sqrt(xVect * xVect + yVect * yVect + zVect * zVect);
		xVect /= length;
		yVect /= length;
		zVect /= length;
		// calculating
		torMatrixVertTexture[i, 0] = 0.5 + Math::Atan2(zVect, xVect) / (2 * Math::PI);
		torMatrixVertTexture[i, 1] = 0.5 - Math::Asin(yVect) / Math::PI;
	}

	// Initializing faces 
	torMatrixFace = gcnew array<int, 2>(2 * (torDefaultMatrixVert->GetLength(0) - 2 * part - 1), 3);
	i = 0;
	for (; i < torDefaultMatrixVert->GetLength(0) - 2 * part - 1; ++i) {
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

	// Initializing projection matrix
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
