#include "SplForm.h"
#include "Windows.h"

using namespace Splines;

/***
������ ��� ��������, 4-� ����, ������ ���121
������� 3. �������
����� ����������: Visual Studio 2013
����: 13.10.2015
����������� ������ ����� � �-�������.
��������� ��. � ���� "� ���������".
*/

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew SplForm);
	return 0;
}