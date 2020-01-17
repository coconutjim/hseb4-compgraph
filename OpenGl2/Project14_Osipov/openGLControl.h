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

#define SIMPLE_OPENGL_CLASS_NAME "simple_openGL_class_name"

// Provides convenient usage of OpenGL
class COpenGLControl
{
public:
	bool initOpenGL(HINSTANCE hInstance, HWND* a_hWnd, void (*a_initScene)(LPVOID), void (*a_renderScene)(LPVOID), void(*a_releaseScene)(LPVOID), LPVOID lpParam);
	
	void resizeOpenGLViewportFull();
	void setProjection3D(float fFOV, float fAspectRatio, float fNear, float fFar);
	glm::mat4* getProjectionMatrix();

	void render(LPVOID lpParam);
	void releaseOpenGLControl(LPVOID lpParam);

	static void registerSimpleOpenGLClass(HINSTANCE hInstance);
	static void unregisterSimpleOpenGLClass(HINSTANCE hInstance);

	void makeCurrent();
	void swapBuffers();

	bool setVerticalSynchronization(bool bEnabled);

	int getFPS();

	COpenGLControl();

private:
	bool initGLEW(HINSTANCE hInstance);

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

	void (*initScene)(LPVOID lpParam), (*renderScene)(LPVOID lpParam), (*releaseScene)(LPVOID lpParam);
};

LRESULT CALLBACK msgHandlerSimpleOpenGLClass(HWND, UINT, WPARAM, LPARAM);