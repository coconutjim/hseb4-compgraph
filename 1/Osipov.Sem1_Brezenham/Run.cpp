#include "BresForm.h"
#include "Windows.h"

using namespace Project1;

/***
������ ��� ��������, 4-� ����, ������ ���121
������� 1. ��������� ����������
����� ����������: Visual Studio 2013
����: 23.09.2015
����������� ��������� ���������� �������, ���������� � ������� ��� �� ����������, ��� � ������������ ����������.
��������� ��. � ���� "� ���������".
*/

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
Application::EnableVisualStyles();
Application::SetCompatibleTextRenderingDefault(false);
Application::Run(gcnew BresForm);
return 0;
}