#include "FiguForm.h"
#include "Windows.h"

using namespace Figure;

/***
������ ��� ��������, 4-� ����, ������ ���121
������� 7. Z-�����
����� ����������: Visual Studio 2013
����: 16.11.2015
����������� �������� z-������, ��������� ������ z-������ � ������� �������� ��������.
��������� ��. � ���� "� ���������".
*/


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew FiguForm);
	return 0;
}