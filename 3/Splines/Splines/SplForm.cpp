#include "SplForm.h"

using namespace Splines;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 3. Сплайны
Среда разработки: Visual Studio 2013
Дата: 13.10.2015
Реализованы кривые Безье и Б-сплайны.
Подробнее см. в меню "О программе".
*/

void SplForm::clearPictureBox(PictureBox^ pb) {
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

void SplForm::clearAll() {
	// Calling 'clever' clearing (bitmaps and data lists)
	buttonT11Clear_Click(nullptr, nullptr);
	buttonT12Clear_Click(nullptr, nullptr);
	buttonT13Clear_Click(nullptr, nullptr);
	buttonT14Clear_Click(nullptr, nullptr);
	buttonT22Clear_Click(nullptr, nullptr);
	buttonT23Clear_Click(nullptr, nullptr);
	buttonT24Clear_Click(nullptr, nullptr);
}

int SplForm::binCoeff(int n, int k) {	
	double result = 1;
	for (int i = 1; i <= k; ++i)
		result = result * (n - k + i) / i;
	return (int)(result + 0.01);
}

Point SplForm::pointCorrection(Point current, Point previous, Point prePreviuos) {
	// finding vector
	double x = previous.X - prePreviuos.X;
	double y = previous.Y - prePreviuos.Y;
	// normalizing it
	double lengthOld = Math::Sqrt(Math::Pow(previous.X - prePreviuos.X, 2) +
		Math::Pow(previous.Y - prePreviuos.Y, 2));
	x /= lengthOld;
	y /= lengthOld;

	// finding new length (by distance to the new point)
	double lengthNew = Math::Sqrt(Math::Pow(previous.X - current.X, 2) +
		Math::Pow(previous.Y - current.Y, 2));
	// finding new point by taking vector with this distance
	return Point(previous.X + x * lengthNew, previous.Y + y * lengthNew);
}

void SplForm::drawAllSimpleCurves(PictureBox^ pb, System::Collections::Generic::List<Point>^ list) {
	for (int i = 0, k = 0; i < (list->Count - 1) / 3; ++i, k += 3) {
		drawSimpleCurve(pb, list, k, k + 3); // drawing closed curves
	}
	int mod = (list->Count - 1) % 3; // looking for the unclosed one
	drawSimpleCurve(pb, list, list->Count - mod - 1, list->Count - 1); // drawing the last one
}

void SplForm::drawSimpleCurve(PictureBox^ pb, System::Collections::Generic::List<Point>^ list, int from, int to) {
	Graphics^ graphics = Graphics::FromImage(pb->Image); // creating graphics
	try {
		int pow = to - from;
		Point prevP = list[from]; // starting
		for (double i = 0; i <= 1; i += t) {
			Point nextP = Point(0, 0);
			for (int j = 0, k = from; j < pow + 1; ++j, ++k) {
				
				// calculating binomial coeefs to simplify the formula and avoing overflows
				double offset = binCoeff(pow, j) * Math::Pow(i, j) * Math::Pow(1 - i, pow - j);

				// incrementing
				nextP.X += (list[k].X * offset);
				nextP.Y += (list[k].Y * offset);
			}
			graphics->DrawLine(pen, prevP, nextP);
			prevP = nextP; // go to next point
		}
		for each (Point point in list) {
			graphics->FillEllipse(brush, point.X - radius, point.Y - radius, radius * 2, radius * 2);
		} // draw points themselves
	}
	finally {
		if (graphics) {
			delete graphics;
		}
	}
	pb->Refresh();
}

void SplForm::drawBSpline(Graphics^ graphics, Point p0, Point p1, Point p2, Point p3) {
	double x = 0, y = 0;
	x = (p0.X + 4 * p1.X + p2.X) / 6.0; // calculating first x
	y = (p0.Y + 4 * p1.Y + p2.Y) / 6.0; // calculating first y
	Point prevP = Point(x, y);
	Point nextP;
	for (double i = t; i <= 1; i += t) {
		x = (Math::Pow((1 - i), 3) * p0.X +
			(3 * Math::Pow(i, 3) - 6 * Math::Pow(i, 2) + 4) * p1.X +
			(-3 * Math::Pow(i, 3) + 3 * Math::Pow(i, 2) + 3 * i + 1) * p2.X +
			Math::Pow(i, 3) * p3.X) / 6.0; // calculating x
		y = (Math::Pow((1 - i), 3) * p0.Y +
			(3 * Math::Pow(i, 3) - 6 * Math::Pow(i, 2) + 4) * p1.Y +
			(-3 * Math::Pow(i, 3) + 3 * Math::Pow(i, 2) + 3 * i + 1) * p2.Y +
			Math::Pow(i, 3) * p3.Y) / 6.0; // calculating y
		nextP = Point(x, y);
		graphics->DrawLine(pen, prevP, nextP); // draw
		prevP = nextP;
	}
}

void SplForm::drawAllBSplines(PictureBox^ pb, System::Collections::Generic::List<Point>^ list, bool closed) {
	Graphics^ graphics = Graphics::FromImage(pb->Image); // creating graphics
	try {
		if (list->Count >= 4) { // if we have at least 4 points to draw
			for (int k = 0; k < list->Count - 3; ++k) { // for complex splines
				drawBSpline(graphics, list[k], list[k + 1], list[k + 2], list[k + 3]); // drawing
			}
			if (closed) {
				// if closed one is needed, draw last 3 splines
				int n = list->Count;
				drawBSpline(graphics, list[n - 3], list[n - 2], list[n - 1], list[0]);
				drawBSpline(graphics, list[n - 2], list[n - 1], list[0], list[1]);
				drawBSpline(graphics, list[n - 1], list[0], list[1], list[2]);
			}
		}
		for each (Point point in list) {
			graphics->FillEllipse(brush, point.X - radius, point.Y - radius, radius * 2, radius * 2);
		} // draw points themselves
	}
	finally {
		if (graphics) {
			delete graphics;
		}
	}
	pb->Refresh();
}