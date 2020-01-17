/*
Осипов Лев Игоревич
Проект 14. OpenGL3
Visual Studio 2013
25.02.2016
Реализовано:
1) в существующих источниках - реализованы свитчеры солнца и текущего точечного источника (клавиши p и l соответственно)
2) реализованы три новых источника - точечный, прожектор и направленный. включение/отключение - клавиши 1, 2 и 3 соответственно
3) реализовано вращение точечного источника и прожектора. включение/отключение - клавиши 4 и 5 соответственно
4) реализовано динамическое изменение цвета созданного направленного источника. включение - отключение - клавиша 6
5) код закомментирован
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