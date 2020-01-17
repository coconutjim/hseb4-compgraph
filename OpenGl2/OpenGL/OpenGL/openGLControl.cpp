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
#pragma warning(disable:4996)
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")

#include "common_header.h"

#include "openGLControl.h"
#include <gl/wglew.h>

#include <glm/gtc/matrix_transform.hpp>

bool COpenGLControl::bClassRegistered = false, COpenGLControl::bGlewInitialized = false;

COpenGLControl::COpenGLControl()
{
	iFPSCount = 0;
	iCurrentFPS = 0;
}

// Creates fake window and OpenGL rendering context, within which GLEW is initialized.
bool COpenGLControl::initGLEW(HINSTANCE hInstance)
{
	if(bGlewInitialized)return true;

	registerSimpleOpenGLClass(hInstance);

	HWND hWndFake = CreateWindow(SIMPLE_OPENGL_CLASS_NAME, "FAKE", WS_OVERLAPPEDWINDOW | WS_MAXIMIZE | WS_CLIPCHILDREN,
		0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
		NULL, hInstance, NULL);

	hDC = GetDC(hWndFake);

	// First, choose false pixel format
	
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;
 
	int iPixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (iPixelFormat == 0)return false;

	if(!SetPixelFormat(hDC, iPixelFormat, &pfd))return false;

	// Create the false, old style context (OpenGL 2.1 and before)

	HGLRC hRCFake = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRCFake);

	bool bResult = true;

	if(!bGlewInitialized)
	{
		if(glewInit() != GLEW_OK)
		{
			MessageBox(*hWnd, "Couldn't initialize GLEW!", "Fatal Error", MB_ICONERROR);
			bResult = false;
		}
		bGlewInitialized = true;
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRCFake);
	DestroyWindow(hWndFake);

	return bResult;
}

// Initializes OpenGL rendering context of specified version.If succeeds, returns true.
// hInstance - application instance
// a_hWnd - window to init OpenGL into
// a_initScene - pointer to init function
// a_renderScene - pointer to render function
// a_releaseScene - optional parameter of release function
bool COpenGLControl::initOpenGL(HINSTANCE hInstance, HWND* a_hWnd, void (*a_initScene)(LPVOID), void (*a_renderScene)(LPVOID), void(*a_releaseScene)(LPVOID), LPVOID lpParam)
{
	if(!initGLEW(hInstance))return false;

	hWnd = a_hWnd;
	hDC = GetDC(*hWnd);

	bool bError = false;
	PIXELFORMATDESCRIPTOR pfd;

	if(WGLEW_ARB_create_context && WGLEW_ARB_pixel_format)
	{
		const int iPixelFormatAttribList[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			0 // End of attributes list
		};
		int iContextAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB, 0,
			0 // End of attributes list
		};

		int iPixelFormat, iNumFormats;
		wglChoosePixelFormatARB(hDC, iPixelFormatAttribList, NULL, 1, &iPixelFormat, (UINT*)&iNumFormats);

		// PFD seems to be only redundant parameter now
		if(!SetPixelFormat(hDC, iPixelFormat, &pfd))return false;

		hRC = wglCreateContextAttribsARB(hDC, 0, iContextAttribs);
		// If everything went OK
		if(hRC) wglMakeCurrent(hDC, hRC);
		else bError = true;

	}
	else bError = true;
	
	if(bError)
	{
		// Generate error messages
		char sErrorMessage[255], sErrorTitle[255];
		sprintf(sErrorMessage, "OpenGL %d.%d is not supported! Please download latest GPU drivers!", 3, 3);
		sprintf(sErrorTitle, "OpenGL %d.%d Not Supported", 3, 3);
		MessageBox(*hWnd, sErrorMessage, sErrorTitle, MB_ICONINFORMATION);
		return false;
	}

	renderScene = a_renderScene;
	initScene = a_initScene;
	releaseScene = a_releaseScene;

	if(initScene != NULL)initScene(lpParam);

	return true;
}

// Resizes viewport to full window.
void COpenGLControl::resizeOpenGLViewportFull()
{
	if(hWnd == NULL)return;
	RECT rRect; GetClientRect(*hWnd, &rRect);
	glViewport(0, 0, rRect.right, rRect.bottom);
}

// Calculates projection matrix.
// fFOV - field of view angle
// fAspectRatio - aspect ration of width / height
// fNear, fFar - distance of near and far clipping plane
void COpenGLControl::setProjection3D(float fFOV, float fAspectRatio, float fNear, float fFar)
{
	mProjection = glm::perspective(fFOV, fAspectRatio, fNear, fFar);
}

// Retrieves pointer to projection matrix
glm::mat4* COpenGLControl::getProjectionMatrix()
{
	return &mProjection;
}

// Registers simple OpenGL window class.
// hInstance - application instance
void COpenGLControl::registerSimpleOpenGLClass(HINSTANCE hInstance)
{
	if(bClassRegistered)return;
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style =  CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	wc.lpfnWndProc = (WNDPROC) msgHandlerSimpleOpenGLClass;
	wc.cbClsExtra = 0; wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_MENUBAR+1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = SIMPLE_OPENGL_CLASS_NAME;

	RegisterClassEx(&wc);

	bClassRegistered = true;
}

// Unregisters simple OpenGL window class.
// hInstance - application instance
void COpenGLControl::unregisterSimpleOpenGLClass(HINSTANCE hInstance)
{
	if(bClassRegistered)
	{
		UnregisterClass(SIMPLE_OPENGL_CLASS_NAME, hInstance);
		bClassRegistered = false;
	}
}

// Handles messages from windows that use simple OpenGL class.
LRESULT CALLBACK msgHandlerSimpleOpenGLClass(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	switch(uiMsg)
	{
		case WM_PAINT:									
			BeginPaint(hWnd, &ps);							
			EndPaint(hWnd, &ps);					
			break;

		default:
			return DefWindowProc(hWnd, uiMsg, wParam, lParam); // Default window procedure
	}
	return 0;
}

// Swaps back and front buffer.
void COpenGLControl::swapBuffers()
{
	SwapBuffers(hDC);
}

// Makes current device and OpenGL rendering context to those associated with OpenGL control.
void COpenGLControl::makeCurrent()
{
	wglMakeCurrent(hDC, hRC);
}

// Calls previously set render function.
// lpParam - pointer to whatever you want
void COpenGLControl::render(LPVOID lpParam)
{
	clock_t tCurrent = clock();
	if( (tCurrent-tLastSecond) >= CLOCKS_PER_SEC)
	{
		tLastSecond += CLOCKS_PER_SEC;
		iFPSCount = iCurrentFPS;
		iCurrentFPS = 0;
	}
	if(renderScene)renderScene(lpParam);
	iCurrentFPS++;
}

// Returns FPS count in last second.
int COpenGLControl::getFPS()
{
	return iFPSCount;
}

// Calls previously set release function and deletes rendering context.
// lpParam - pointer to whatever you want
void COpenGLControl::releaseOpenGLControl(LPVOID lpParam)
{
	if(releaseScene)releaseScene(lpParam);

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(*hWnd, hDC);

	hWnd = NULL;
}

// Sets vertical synchronization
// bEnabled - whether to enable V-Sync
bool COpenGLControl::setVerticalSynchronization(bool bEnabled)
{
	if(!wglSwapIntervalEXT)return false;
	if(bEnabled)wglSwapIntervalEXT(1);
	else wglSwapIntervalEXT(0);
	return true;
}