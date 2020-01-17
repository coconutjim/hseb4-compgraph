/*
Осипов Лев Игоревич
OpenGL. Проект 16.
Visual Studio 2013
06.03.2016
Сделано:
1) Объекты сгенерированы раличными способами (куб - индексно, торы - процедурно, Дедпулы и Тор - используя меши)
2) Реализовано три дополнительных источников освещения - белый направленный, синий точечный и красный прожектор (последние 2 видны слева от торов)
3) Встроен собственный скайбокс
4) Реализовано три типа тумана (перелючение - клавиша f) и регулирование его параметров стрелками
5) Реализовано много объектов с движением в рамках композиции "Деревня Дедпулов, которую охраняет Тор"
Код закомментирован.
*/
#pragma once

#include "openGLControl.h"

// Windows stuff for creating window and Windows message handling.
class COpenGLWinApp
{
public:
	HWND hWnd; // Handle to application window
	COpenGLControl oglControl; // OpenGL Control

	void ResetTimer();
	void UpdateTimer();
	float sof(float fVal);

	bool InitializeApp(string a_sAppName);
	void RegisterAppClass(HINSTANCE hAppInstance);
	bool CreateAppWindow(string sTitle);
	
	void AppBody();
	void Shutdown();

	HINSTANCE GetInstance();

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
	int Key(int iKey);
	int Onekey(int iKey);
	extern char kp[256];
}

extern COpenGLWinApp appMain;

void InitScene(LPVOID), RenderScene(LPVOID), ReleaseScene(LPVOID);