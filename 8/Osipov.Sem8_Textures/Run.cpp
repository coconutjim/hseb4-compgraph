#include "FiguForm.h"
#include "Windows.h"

using namespace Figure;

/***
Осипов Лев Игоревич, 4-й курс, группа БПИ121
Семинар 8. Текстуры
Среда разработки: Visual Studio 2013
Дата: 26.11.2015
Реализовано наложение текстур, загрузка текстуры из файла и изменения скорости вращений.
Подробнее см. в меню "О программе".
*/

[System::STAThread]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try {
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		Application::Run(gcnew FiguForm);
	}
	catch (Exception^ e) {
		// :(
	}
	return 0;
}