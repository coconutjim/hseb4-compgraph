/*
Осипов Лев Игоревич
Проект 14. OpenGL2
Visual Studio 2013
17.02.2016
Выполнены все задания, код декомпозирован и закомментирован.
Релизованы куб, пирамида, октаэдр и тор (с разными текстурами).
Управление:
1) Трансформация каждой фигуры индивидуально - одновременное нажатие первой английской буквы фигуры и следующих клавиш:
a - движение влево
d - движение вправо
w - движение вверх
s - движение вниз
z - движение вперед
x - движение назад
стрелка вправо - вращение в одну сторону
стрелка влево - вращение в другую сторону
стрелка вверх - увеличение фигуры
стрелка вниз - уменьшение фигуры
Примеры:
увеличение куба - с + стрелка вверх
сдвиг тора вправо - t + d
2) включение режима случайного перемещения фигур - клавиша r, она же отвечает и за выключение этого режима
3) Для вращения камеры - левый ctrl + стрелки вправо и влево, для приближения/отдаления камеры - левый ctrl + стрелки вверх и вниз
*/
#pragma once

#include "openGLControl.h"

class COpenGLWinApp
{
public:
	HWND hWnd; // Handle to application window
	COpenGLControl oglControl; // OpenGL Control

	void resetTimer();
	void updateTimer();
	float sof(float fVal);

	bool initializeApp(string a_sAppName);
	void registerAppClass(HINSTANCE hAppInstance);
	bool createWindow(string sTitle);
	
	void appBody();
	void shutdown();

	HINSTANCE getInstance();

	LRESULT CALLBACK msgHandlerMain(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE hInstance; // Application's instance
	string sAppName;
	HANDLE hMutex;

	bool bAppActive; // To check if application is active (not minimized)
	clock_t tLastFrame;
	float fFrameInterval;
};

namespace Keys
{
	int key(int iKey);
	int onekey(int iKey);
	extern char kp[256];
}

extern COpenGLWinApp appMain;

void initScene(LPVOID), renderScene(LPVOID), releaseScene(LPVOID);