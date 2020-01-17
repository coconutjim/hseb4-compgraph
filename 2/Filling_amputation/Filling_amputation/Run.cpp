#include "FaForm.h"
#include "Windows.h"

using namespace Filling_amputation;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 1. Алгоритмы Брезенхэма
Среда разработки: Visual Studio 2013
Дата: 30.09.2015
Реализованы алгоритмы построчной заливки, обычной заливки и отсечения.
Подробнее см. в меню "О программе".
*/

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew FaForm);
	return 0;
}