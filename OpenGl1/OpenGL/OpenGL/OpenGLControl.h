/*
Осипов Лев Игоревич
Проект 13.
Visual Studio 2013
04.02.2016
Сделано:
1) Изменен цвет окна
2) Треугольник и четырехугольник перемещены в правый нижний край
3) Реализована радуга
4) Реализован контур пятиконечной звезды
5) Реализованы две шестиконечные звезды
6) Реализован переключатель между пятиконечной звездой
и шестиконечными звездами. Для переключения следует нажать клавишу s
7) Код в RenderScene.cpp декомпозирован и закомментирован
*/
#pragma once

#define SIMPLE_OPENGL_CLASS_NAME "Simple_openGL_class"

//Provides convenient usage of OpenGL
class COpenGLControl
{
public:
	bool InitOpenGL(HINSTANCE hInstance, HWND* a_hWnd, void (*a_InitScene)(LPVOID), void (*a_RenderScene)(LPVOID), void(*a_ReleaseScene)(LPVOID), LPVOID lpParam);
	
	void ResizeOpenGLViewportFull();

	void Render(LPVOID lpParam);
	void ReleaseOpenGLControl(LPVOID lpParam);

	static void RegisterSimpleOpenGLClass(HINSTANCE hInstance);
	static void UnregisterSimpleOpenGLClass(HINSTANCE hInstance);

	bool isShowStars();
	void setShowStars(bool show);

	void MakeCurrent();
	void SwapBuffersM();

private:
	bool InitGLEW(HINSTANCE hInstance);

	HDC hDC;
	HWND* hWnd;
	HGLRC hRC;
	static bool bClassRegistered;
	static bool bGlewInitialized;
	bool showStars; // if we need to show stars

	void (*InitScene)(LPVOID lpParam), (*RenderScene)(LPVOID lpParam), (*ReleaseScene)(LPVOID lpParam);
};

LRESULT CALLBACK MsgHandlerSimpleOpenGLClass(HWND, UINT, WPARAM, LPARAM);