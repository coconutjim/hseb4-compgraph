#include "FaForm.h"
#include "Windows.h"

using namespace Filling_amputation;

/***
������ ��� ��������, 4-� ����, ������ ���121
������� 1. ��������� ����������
����� ����������: Visual Studio 2013
����: 30.09.2015
����������� ��������� ���������� �������, ������� ������� � ���������.
��������� ��. � ���� "� ���������".
*/

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew FaForm);
	return 0;
}