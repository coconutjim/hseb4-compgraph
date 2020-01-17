#include "PyrForm.h"

using namespace Pyramid;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 4. 3D моделирование
Среда разработки: Visual Studio 2013
Дата: 19.10.2015
Реализованы различные отображения и трансформации пирамиды.
Подробнее см. в меню "О программе".
*/

void PyrForm::clearPictureBox(PictureBox^ pb) {
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

void PyrForm::incrementDeltas(double& deltaX, double& deltaY, double& deltaZ, double deltaLength) {
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

void PyrForm::decrementDeltas(double& deltaX, double& deltaY, double& deltaZ, double deltaLength) {
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

void PyrForm::drawPyramid(PictureBox^ pb, array<double, 2>^ matrix, array<int, 2>^ matrixFace) {
	Graphics^ graphics = Graphics::FromImage(pb->Image); // creating graphics
	try {
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

array<double, 2>^ PyrForm::matrixComposition(array<double, 2>^ m1, array<double, 2>^ m2) {
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

array<double, 2>^ PyrForm::formMoveMatrix(double deltaX, double deltaY, double deltaZ) {
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

array<double, 2>^ PyrForm::formXRotateMatrix(double deltaRadX) {
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

array<double, 2>^ PyrForm::formYRotateMatrix(double deltaRadY) {
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

array<double, 2>^ PyrForm::formZRotateMatrix(double deltaRadZ) {
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

array<double, 2>^ PyrForm::formScaleMatrix(double deltaScaleX, double deltaScaleY, double deltaScaleZ, double generalScale) {
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


void PyrForm::initializeMatrices() {

	/* Initializing vertexes  */
	matrixVert = gcnew array<double, 2>(4, 4);
	restoreVertexMatrix();

	/* Initializing faces */
	matrixFace = gcnew array<int, 2>(4, 3);

	matrixFace[0, 0] = 0;
	matrixFace[0, 1] = 1;
	matrixFace[0, 2] = 2;

	matrixFace[1, 0] = 0;
	matrixFace[1, 1] = 1;
	matrixFace[1, 2] = 3;

	matrixFace[2, 0] = 0;
	matrixFace[2, 1] = 2;
	matrixFace[2, 2] = 3;

	matrixFace[3, 0] = 1;
	matrixFace[3, 1] = 2;
	matrixFace[3, 2] = 3;

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

void PyrForm::restoreVertexMatrix() {
	for (int i = 0; i < matrixVert->GetLength(0); ++i) {
		matrixVert[i, 3] = 1;
	}

	matrixVert[0, 0] = x0;
	matrixVert[0, 1] = y0;
	matrixVert[0, 2] = z0;

	matrixVert[1, 0] = x0 + 100;
	matrixVert[1, 1] = y0;
	matrixVert[1, 2] = z0;

	matrixVert[2, 0] = x0 + 70;
	matrixVert[2, 1] = y0 + 30;
	matrixVert[2, 2] = z0;

	matrixVert[3, 0] = x0 + 50;
	matrixVert[3, 1] = y0;
	matrixVert[3, 2] = z0 + 150;
}

void PyrForm::drawInitialPyramid() {
	// restoring values
	restoreVertexMatrix();
	// some initial transforming
	matrixVert = matrixComposition(matrixVert, formXRotateMatrix(0.3)); // rotating X
	// drawing start figure
	drawPyramid(pictureBoxPyr, matrixComposition(matrixVert, matrixCurrProj), matrixFace);
}
