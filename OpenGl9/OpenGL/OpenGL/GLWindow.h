/*
Осипов Лев Игоревич
Проект 19. OpenGL8
Visual Studio 2013
24.03.2016
Сделано:
1) реализовано 7 дополнительных фильтров:
отражение, искажение по синусу, эффект закручивания, эффект линзы, эффект волны, контраст, бинаризация
(включение - клавиши F8, F9, F11, NUMPAD0, NUMPAD1, NUMPAD2 соответственно)
2) Реализован Canny - NUMPAD3
3) реализован контроль области применения фильтров - клавиши Q и E
4) реализовано управление параметрами фильтров, как существующих, так и добавленных (но не всех, конечно, некоторые не нуждаются в конфигурации)
Управление реализовано стрелками. у некоторых фильтров регулируется один параметр стрелками влево и вправо, у некоторых два, и тогда
нужно работать еще и стрелками вверх и вниз, а у Canny еще больше нюансов
Список регулируемых фильтров:
	1. F5 - размытие - стрелки влево и вправо
	2. F6 - рельеф - стрелки влево и вправо
	3. F7 - абберация - стрелки влево и вправо
	3. F9 - искажение по синусу - стрелки влево и вправо
	4. F10 - закручивание - стрелки влево и вправо (радиус) и стрелки вверх и вниз (угол)
	5. F11 - линза - стрелки влево и вправо (радиус) и стрелки вверх и вниз (увеличение)
	6. NUMPAD0 - волна - стрелки влево и вправо (длина волны) и стрелки вверх и вниз (смещение)
	7. NUMPAD1 - контрастность - стрелки влево и вправо
	8. NUMPAD2 - бинаризация - стрелки влево и вправо
	9. NUMPAD3 - Canny - стрелки влево и вправо (степень размытия по Гауссу), стрелки вверх и вниз (контроль пороговой фильтрации).
		Также клавишей С можно контролировать этапы применения фильтра Canny - либо полный фильтр, либо только Гаусс с обесцвечиванием (без Собеля)
5) код закомментирован
*/
#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "common.h"
#include "OpenGL.h"

#define FIXED_TIMESTAMP 1.0e-3

#define INPUT_BUTTON_LEFT   0
#define INPUT_BUTTON_RIGHT  1
#define INPUT_BUTTON_MIDDLE 2

// структура для хранения состояния окна GLWindow
struct GLWindow
{
	// размеры окна
	int width;
	int height;

	// флаги состояние
	bool fullScreen;
	bool active;
	bool running;
};

// состояние клавиатуры и мыши
struct Input
{
	uint8_t keyState[256];
	uint8_t buttonState[3];
	int     cursorPos[2];
};

// создание окна с поддержкой OpenGL
bool GLWindowCreate(const char *title, int width, int height, bool fullScreen = false);
// уничтожение окна
void GLWindowDestroy();

// ручное изменение размера и режима окна
void GLWindowSetSize(int width, int height, bool fullScreen = false);

bool GLWindowInit(const GLWindow &window);
void GLWindowClear(const GLWindow &window);
void GLWindowRender(const GLWindow &window);
void GLWindowUpdate(const GLWindow &window, double deltaTime);
void GLWindowInput(const GLWindow &window);

// основной цикл окна, обработка оконных сообщений и вызов необходимых функций
int GLWindowMainLoop();

// проверка, нажата ли клавиша
bool InputIsKeyDown(uint8_t key);
// проверка, нажата ли клавиша одинарно
bool InputIsKeyPressed(uint8_t key);

// проверка, нажата ли кнопка мыши
bool InputIsButtonDown(uint8_t button);
// проверка, нажата ли кнопка мыши одинарно
bool InputIsButtonClick(uint8_t button);

// получить текущее положение курсора
void InputGetCursorPos(int *x, int *y);
// задать положение курсора
void InputSetCursorPos(int x, int y);

// скрыть или показать курсор
void InputShowCursor(bool visible);

#endif /* GLWINDOW_H */
