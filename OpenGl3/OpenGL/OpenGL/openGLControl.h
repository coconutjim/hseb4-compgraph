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

#define SIMPLE_OPENGL_CLASS_NAME "simple_openGL_class_name"

// Provides convenient usage of OpenGL.
class COpenGLControl
{
public:
	bool InitOpenGL(HINSTANCE hInstance, HWND* a_hWnd, void (*a_ptrInitScene)(LPVOID), void (*a_ptrRenderScene)(LPVOID), void(*a_ptrReleaseScene)(LPVOID), LPVOID lpParam);
	
	void ResizeOpenGLViewportFull();
	void SetProjection3D(float fFOV, float fAspectRatio, float fNear, float fFar);

	glm::mat4* GetProjectionMatrix();

	void Render(LPVOID lpParam);
	void ReleaseOpenGLControl(LPVOID lpParam);

	static void RegisterSimpleOpenGLClass(HINSTANCE hInstance);
	static void UnregisterSimpleOpenGLClass(HINSTANCE hInstance);

	void MakeCurrent();
	void SwapBuffers();

	bool SetVerticalSynchronization(bool bEnabled);

	int GetFPS();

	int GetViewportWidth();
	int GetViewportHeight();

	COpenGLControl();

private:
	bool InitGLEW(HINSTANCE hInstance);

	HDC hDC;
	HWND* hWnd;
	HGLRC hRC;
	static bool bClassRegistered;
	static bool bGlewInitialized;

	// Used for FPS calculation
	int iFPSCount, iCurrentFPS;
	clock_t tLastSecond;

	// Matrix for perspective projection
	glm::mat4 mProjection;

	// Viewport parameters
	int iViewportWidth, iViewportHeight;

	void (*ptrInitScene)(LPVOID lpParam), (*ptrRenderScene)(LPVOID lpParam), (*ptrReleaseScene)(LPVOID lpParam);
};

LRESULT CALLBACK msgHandlerSimpleOpenGLClass(HWND, UINT, WPARAM, LPARAM);