#include "FiguForm.h"
#include "Windows.h"

using namespace Figure;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 5. 3D моделирование-2
Среда разработки: Visual Studio 2013
Дата: 28.10.2015
Реализованы различные отображения и трансформации фигур.
Подробнее см. в меню "О программе".
*/


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew FiguForm);
	return 0;
}