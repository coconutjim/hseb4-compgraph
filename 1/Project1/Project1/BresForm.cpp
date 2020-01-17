#include "BresForm.h"
#include <cmath>

using namespace Project1;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 1. Алгоритмы Брезенхэма
Среда разработки: Visual Studio 2013
Дата: 23.09.2015
Реализованы алгоритмы построения отрезка, окружности и эллипса как по Брезенхэму, так и стандартными средствами.
Подробнее см. в меню "О программе".
*/

void BresForm::clearPictureBox(PictureBox^ pb) {
	Graphics^ graphics = Graphics::FromImage(pb->Image); // creating graphics
	try {
		graphics->Clear(colorDialog1->Color);
	}
	finally {
		if (graphics) {
			delete graphics;
		}
	}
	pb->Refresh();
}

void BresForm::clearAll() {
	clearPictureBox(pictureBox1);
	clearPictureBox(pictureBox2);
	clearPictureBox(pictureBox3);
	clearPictureBox(pictureBox4);
	clearPictureBox(pictureBox5);
	clearPictureBox(pictureBox6);
}

void BresForm::drawPoint(int x, int y, Graphics^ graphics) {
	graphics->FillRectangle(brush, x, y, 1, 1);
}

void BresForm::bresSegment(int x1, int y1, int x2, int y2, Graphics^ graphics) {
	int x = x1, y = y1;
	int deltaX = abs(x2 - x1), deltaY = abs(y2 - y1);
	int s1 = (x2 - x1) >= 0 ? 1 : -1, s2 = (y2 - y1) >= 0 ? 1 : -1; // improvised sign

	bool swap = false;

	if (deltaY > deltaX) {
		int temp = deltaY;
		deltaY = deltaX;
		deltaX = temp;
		swap = true;
	}

	int error = 2 * deltaY - deltaX;

	for (int i = 0; i < deltaX; ++ i) {
		drawPoint(x, y, graphics);
		while (error >= 0) {
			if (swap) {
				x += s1;
			}
			else {
				y += s2;
			}
			error -= 2 * deltaX;
		}
		if (swap) {
			y += s2;
		}
		else {
			x += s1;
		}
		error += 2 * deltaY;
	}
}

void BresForm::quadroDraw(int x, int y, int x1, int y1, Graphics^ graphics) {
	drawPoint(x + x1, y + y1, graphics);
	drawPoint(x + x1, y1 - y, graphics);
	drawPoint(x1 - x, y + y1, graphics);
	drawPoint(x1 - x, y1 - y, graphics);
}

void BresForm::bresCircle(int x1, int y1, int r, Graphics^ graphics) {
	int x = 0, y = r;
	int delta = 1 - 2 * r;
	int lim = 0, error = 0;
	do {
		quadroDraw(x, y, x1, y1, graphics);
		if (delta < 0) {
			error = 2 * delta + 2 * y + 1;
			if (error <= 0) {
				++ x;
				delta += 2 * x + 1;
			}
			else {
				++ x;
				-- y;
				delta += 2 * x - 2 * y + 2;
			}
		}
		else {
			if (delta > 0) {
				error = 2 * delta - 2 * x - 1;
				if (error <= 0) {
					++ x;
					-- y;
					delta += 2 * x - 2 * y + 2;
				}
				else {
					-- y;
					delta += 1 - 2 * y;
				}
			}
			else {
				++ x;
				-- y;
				delta += 2 * x - 2 * y + 2;
			}
		}
	} while (y > lim);
}

void BresForm::bresEllipse(int x1, int y1, int width, int height, Graphics^ graphics) {
	int sqrWidth = width * width;
	int sqrHeight = height * height;
	int x = width, y = 0; 
	int error = width * sqrHeight;
	int xx = 0, yy = 2 * width * sqrHeight;

	while (yy >= xx) {
		quadroDraw(x, y, x1, y1, graphics);
		++ y;
		error -= 2 * sqrWidth * (y - 1);
		xx += 2 * sqrWidth;
		if (error < 0) {
			error += 2 * sqrHeight * (x - 1);
			-- x;
			yy -= 2 * sqrHeight;
		}

	}

	x = 0; 
	y = height;
	error = sqrWidth * height;
	xx = 2 * sqrWidth * height;
	yy = 0;

	while (yy <= xx) {
		quadroDraw(x, y, x1, y1, graphics);
		++ x;
		error -= 2 * sqrHeight * (x - 1);
		yy += 2 * sqrHeight;
		if (error <= 0) {
			error += 2 * sqrWidth * (y - 1);
			-- y;
			xx -= 2 * sqrWidth;
		}
	}
}
