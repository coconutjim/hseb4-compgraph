#include "FiguForm.h"
#include "Windows.h"

using namespace Figure;

/***
������ ��� ��������, 4-� ����, ������ ���121
������� 5. 3D �������������-2
����� ����������: Visual Studio 2013
����: 28.10.2015
����������� ��������� ����������� � ������������� �����.
��������� ��. � ���� "� ���������".
*/


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew FiguForm);
	return 0;
}