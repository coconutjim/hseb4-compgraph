#include "FiguForm.h"
#include "Windows.h"

using namespace Figure;

/***
������ ��� ��������, 4-� ����, ������ ���121
������� 8. ��������
����� ����������: Visual Studio 2013
����: 26.11.2015
����������� ��������� �������, �������� �������� �� ����� � ��������� �������� ��������.
��������� ��. � ���� "� ���������".
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