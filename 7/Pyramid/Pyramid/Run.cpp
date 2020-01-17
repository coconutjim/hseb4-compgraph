#include "FiguForm.h"
#include "Windows.h"

using namespace Figure;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 7. Z-буфер
Среда разработки: Visual Studio 2013
Дата: 16.11.2015
Реализованы алгоритм z-буфера, отрисовка самого z-буфера и плоская закраска объектов.
Подробнее см. в меню "О программе".
*/


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew FiguForm);
	return 0;
}