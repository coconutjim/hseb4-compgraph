#include "FiguForm.h"
#include "Windows.h"

using namespace Figure;

/***
������ ��� ��������, 4-� ����, ������ ���121
������� 6. �������� ��������
����� ����������: Visual Studio 2013
����: 05.11.2015
����������� ��������� ����������� � ������������� �����, � ����� �������� �������� ��� ������ �� ���.
��������� ��. � ���� "� ���������".
*/


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew FiguForm);
	return 0;
}