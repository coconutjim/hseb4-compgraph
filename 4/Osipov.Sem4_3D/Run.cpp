#include "PyrForm.h"
#include "Windows.h"

using namespace Pyramid;

/***
������ ��� ��������, 4-� ����, ������ ���121
������� 4. 3D �������������
����� ����������: Visual Studio 2013
����: 19.10.2015
����������� ��������� ����������� � ������������� ��������.
��������� ��. � ���� "� ���������".
*/

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew PyrForm);
	return 0;
}