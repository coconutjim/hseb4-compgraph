#include "PyrForm.h"
#include "Windows.h"

using namespace Pyramid;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 4. 3D моделирование
Среда разработки: Visual Studio 2013
Дата: 19.10.2015
Реализованы различные отображения и трансформации пирамиды.
Подробнее см. в меню "О программе".
*/

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew PyrForm);
	return 0;
}