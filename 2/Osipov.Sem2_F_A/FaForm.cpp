#include "FaForm.h"
#include <algorithm>
#include <windows.h>

using namespace Filling_amputation;
using namespace System::Collections::Generic;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 1. Алгоритмы Брезенхэма
Среда разработки: Visual Studio 2013
Дата: 30.09.2015
Реализованы алгоритмы построчной заливки, обычной заливки и отсечения.
Подробнее см. в меню "О программе".
*/

void FaForm::clearPictureBox(PictureBox^ pb) {
	Graphics^ graphics = Graphics::FromImage(pb->Image); // creating graphics
	try {
		graphics->Clear(colorDialogBg->Color);
	}
	finally {
		if (graphics) {
			delete graphics;
		}
	}
	pb->Refresh();
}

void FaForm::clearAll() {
	clearPictureBox(pictureBoxF1);
	clearPictureBox(pictureBoxF2);
	clearPictureBox(pictureBoxA);
	checkBoxF1->Checked = false;
	checkBoxF2->Checked = false;
}

void FaForm::handlePolygonPainting(PictureBox^ pb, Bitmap^ bp, Point^ start, Point^ current, int x, int y) {
	Graphics^ graphics = Graphics::FromImage(pb->Image); // creating graphics
	try {
		int error = 20; // error distance
		// if it is the first point
		if (! start) {
			clearPictureBox(pb);
			start = gcnew Point(x, y);
			bp->SetPixel(x, y, colorDialogFg->Color);
		}
		else {
			// if the current point matches (or near) the start point
			if (abs(start->X - x) < error && abs(start->Y - y) < error) {
				// if polygon has more than 2 lines, end it and start the algorithm, else do nothing
				if (current) {
					graphics->DrawLine(pen, current->X, current->Y, start->X, start->Y);
					delete current;
					current = nullptr;
					delete start;
					startF1 = nullptr;
				}
			}
			else {
				if (currentF1) {
					graphics->DrawLine(pen, current->X, current->Y, x, y); // just draw a line
					delete current;
				}
				else {
					graphics->DrawLine(pen, start->X, start->Y, x, y); // just draw a line
				}
				currentF1 = gcnew Point(x, y);
			}
		}
	}
	finally {
		if (graphics) {
			delete graphics;
		}
	}
	pb->Refresh();
}

void FaForm::stringFilling(PictureBox^ pb, Bitmap^ bp, int x0, int y0, 
		Color^ fillColor, Color^ borderColor, int delay) {

	int fillArgb = fillColor->ToArgb();
	int borderArgb = borderColor->ToArgb();

	// if start point is on the border, nothing to do here
	if (bp->GetPixel(x0, y0).ToArgb() == borderArgb) {
		return;
	}

	Stack<Point>^ stack = gcnew Stack<Point>();
	stack->Push(*gcnew Point(x0, y0)); // stack initializing

	while (stack->Count > 0) {
		Point^ point = stack->Pop();

		int xLeft = point->X, xRight = point->X;
		int y = point->Y;

		bp->SetPixel(point->X, y, *fillColor); // filling the point itself

		// going left
		while (xLeft - 1 >= 0 // checking margins 
			&& bp->GetPixel(xLeft - 1, y).ToArgb() != borderArgb) {
			--xLeft; // remembering xLeft
			bp->SetPixel(xLeft, y, *fillColor); // filling
		}

		// going right
		while (xRight + 1 < bp->Width && // checking margins 
			bp->GetPixel(xRight + 1, y).ToArgb() != borderArgb) {
			++xRight; // remembering xRight
			bp->SetPixel(xRight, y, *fillColor); // filling
		}

		bool unfilledTop = false, unfilledBot = false; // flags to detect unfilled intervals
		int topArgb, botArgb;
		// checking top and bottom strings
		for (int i = xLeft; i <= xRight; ++i) {

			// if top exists
			if (y - 1 >= 0) {
				topArgb = bp->GetPixel(i, y - 1).ToArgb();
				if (topArgb == borderArgb) { // if we meet a border
					if (unfilledTop) { // if the interval existed, remember previous point
						stack->Push(*gcnew Point(i - 1, y - 1));
						unfilledTop = false;
					}
				}
				else if (topArgb != fillArgb) { // if we found an unfilled point,
					if (!unfilledTop) {
						unfilledTop = true;  // mark a new interval
					}
				}
			}

			// if bot exists
			if (y + 1 < bp->Height) {
				botArgb = bp->GetPixel(i, y + 1).ToArgb();
				if (botArgb == borderArgb) { // if we meet a border
					if (unfilledBot) { // if the interval existed, remember previous point
						stack->Push(*gcnew Point(i - 1, y + 1));
						unfilledBot = false;
					}
				}
				else if (botArgb != fillArgb) {
					if (!unfilledBot) {
						unfilledBot = true; // if we found an unfilled point, mark a new interval
					}
				}
			}
		}

		// if there were intervals, remember right points
		if (unfilledTop) {
			stack->Push(*gcnew Point(xRight, y - 1));
		}
		if (unfilledBot) {
			stack->Push(*gcnew Point(xRight, y + 1));
		}

		delete point;
		
		if (delay != 0) {
			Sleep(delay);
			pb->Refresh();
		}
	}
	pb->Refresh();
}

void FaForm::simpleFilling(PictureBox^ pb, Bitmap^ bp, int x0, int y0, 
		Color^ fillColor, Color^ borderColor, bool delay) {
	
	int fillArgb = fillColor->ToArgb();
	int borderArgb = borderColor->ToArgb();

	// if start point is on the border, nothing to do here
	if (bp->GetPixel(x0, y0).ToArgb() == borderArgb) {
		return;
	}
	
	Stack<Point>^ stack = gcnew Stack<Point>();
	stack->Push(*gcnew Point(x0, y0)); // stack initializing

	while (stack->Count > 0) {
		Point^ point = stack->Pop();
		
		int x = point->X;
		int y = point->Y;
		
		// checking current pixel
		int currArgb = bp->GetPixel(x, y).ToArgb();
		if (currArgb != fillArgb && currArgb != borderArgb) {
			bp->SetPixel(x, y, *fillColor); // filling
		}
		// checking right pixel
		x = point->X + 1;
		y = point->Y;

		// checking margins
		if (x >= 0 && x < bp->Width && y >= 0 && y < bp->Height) {
			currArgb = bp->GetPixel(x, y).ToArgb();
			if (currArgb != fillArgb && currArgb != borderArgb) {
				stack->Push(*gcnew Point(x, y)); // see later
			}
		}

		// checking left pixel
		x = point->X - 1;
		y = point->Y;
		
		// checking margins
		if (x >= 0 && x < bp->Width && y >= 0 && y < bp->Height) {
			currArgb = bp->GetPixel(x, y).ToArgb();
			if (currArgb != fillArgb && currArgb != borderArgb) {
				stack->Push(*gcnew Point(x, y)); // see later
			}
		}

		// checking bottom pixel
		x = point->X;
		y = point->Y + 1;
		
		// checking margins
		if (x >= 0 && x < bp->Width && y >= 0 && y < bp->Height) {
			currArgb = bp->GetPixel(x, y).ToArgb();
			if (currArgb != fillArgb && currArgb != borderArgb) {
				stack->Push(*gcnew Point(x, y)); // see later
			}
		}

		// checking top pixel
		x = point->X;
		y = point->Y - 1;
		
		// checking margins
		if (x >= 0 && x < bp->Width && y >= 0 && y < bp->Height) {
			currArgb = bp->GetPixel(x, y).ToArgb();
			if (currArgb != fillArgb && currArgb != borderArgb) {
				stack->Push(*gcnew Point(x, y)); // see later
			}
		}

		// checking bottom pixel
		x = point->X;
		y = point->Y + 1;

		// checking margins
		if (x >= 0 && x < bp->Width && y >= 0 && y < bp->Height) {
			currArgb = bp->GetPixel(x, y).ToArgb();
			if (currArgb != fillArgb && currArgb != borderArgb) {
				stack->Push(*gcnew Point(x, y)); // see later
			}
		}
		delete point;
		
		if (delay) {
			pb->Refresh();
		}
	}
	pb->Refresh();
}

// for defining the position
int left = 1;
int right = 2;
int bot = 4;
int top = 8;

int FaForm::classify(int x0, int y0, int x1, int y1, Point^ point) {
	int result = 0;
	int x = point->X, y = point->Y;
	if (x < x0) {
		result += left;
	}
	else if (x > x1) {
		result += right;
	}
	if (y < y0) {
		result += bot;
	}
	else if (y > y1) {
		result += top;
	}
	return result;
}

bool FaForm::amputation(int x0, int y0, int x1, int y1, Point^ start, Point^ end) {
	int st, en;
	Point^ temp;
	int t;

	// finding points
	st = classify(x0, y0, x1, y1, start);
	en = classify(x0, y0, x1, y1, end);

	while (st | en) {
		// if both are out of rect
		if (st & en) {
			return false;
		}

		// the one that is outside
		if (st) {
			t = st;
			temp = start;
		}
		else {
			t = en;
			temp = end;
		}
		// checking left
		if (t & left) {
			temp->Y += (start->Y - end->Y) * (x0 - temp->X) / (start->X - end->X);
			temp->X = x0;
		}
		// checking right
		else if (t & right) {
			temp->Y += (start->Y - end->Y) * (x1 - temp->X) / (start->X - end->X);
			temp->X = x1;
		}
		// checking bot
		else if (t & bot) {
			temp->X += (start->X - end->X) * (y0 - temp->Y) / (start->Y - end->Y);
			temp->Y = y0;
		}
		// checking top
		else if (t & top) {
			temp->X += (start->X - end->X) * (y1 - temp->Y) / (start->Y - end->Y);
			temp->Y = y1;
		}

		// counting
		if (t == st) {
			start = temp;
			st = classify(x0, y0, x1, y1, start);
		}
		else {
			end = temp;
			en = classify(x0, y0, x1, y1, end);
		}

	}
	return true;
}



