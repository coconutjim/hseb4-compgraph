/*
������ ��� ��������
������ 13.
Visual Studio 2013
04.02.2016
�������:
1) ������� ���� ����
2) ����������� � ��������������� ���������� � ������ ������ ����
3) ����������� ������
4) ���������� ������ ������������ ������
5) ����������� ��� ������������� ������
6) ���������� ������������� ����� ������������ �������
� �������������� ��������. ��� ������������ ������� ������ ������� s
7) ��� � RenderScene.cpp �������������� � ���������������
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