#include "SplForm.h"
#include "Windows.h"

using namespace Splines;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 3. Сплайны
Среда разработки: Visual Studio 2013
Дата: 13.10.2015
Реализованы кривые Безье и Б-сплайны.
Подробнее см. в меню "О программе".
*/

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew SplForm);
	return 0;
}