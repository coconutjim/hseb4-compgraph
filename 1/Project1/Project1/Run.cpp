#include "BresForm.h"
#include "Windows.h"

using namespace Project1;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 1. Алгоритмы Брезенхэма
Среда разработки: Visual Studio 2013
Дата: 23.09.2015
Реализованы алгоритмы построения отрезка, окружности и эллипса как по Брезенхэму, так и стандартными средствами.
Подробнее см. в меню "О программе".
*/

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
Application::EnableVisualStyles();
Application::SetCompatibleTextRenderingDefault(false);
Application::Run(gcnew BresForm);
return 0;
}