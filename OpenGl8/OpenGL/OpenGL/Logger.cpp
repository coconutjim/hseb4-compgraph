/*
������ ��� ��������
������ 19. OpenGL8
Visual Studio 2013
22.03.2016
�������:
1) ����������� 7 �������������� ��������:
���������, ��������� �� ������, ������ ������������, ������ �����, ������ �����, ��������, �����������
(��������� - ������� F8, F9, F11, NUMPAD0, NUMPAD1, NUMPAD2 ��������������)
2) ���������� �������� ������� ���������� �������� - ������� Q � E
3) ����������� ���������� ����������� ��������, ��� ������������, ��� � ����������� (�� �� ����, �������, ��������� �� ��������� � ������������)
���������� ����������� ���������. � ��������� �������� ������������ ���� �������� ��������� ����� � ������, � ��������� ���, � �����
����� �������� ��� � ��������� ����� � ����
������ ������������ ��������:
1. F5 - �������� - ������� ����� � ������
2. F6 - ������ - ������� ����� � ������
3. F7 - ��������� - ������� ����� � ������
3. F9 - ��������� �� ������ - ������� ����� � ������
4. F10 - ������������ - ������� ����� � ������ (������) � ������� ����� � ���� (����)
5. F11 - ����� - ������� ����� � ������ (������) � ������� ����� � ���� (����������)
6. NUMPAD0 - ����� - ������� ����� � ������ (����� �����) � ������� ����� � ���� (��������)
7. NUMPAD1 - ������������� - ������� ����� � ������
8. NUMPAD2 - ����������� - ������� ����� � ������
4) ��� ���������������
*/
#include "Logger.h"

static const int LOGGER_FILENAME_MAX              = 256;
static char g_LoggerFileName[LOGGER_FILENAME_MAX] = "OpenGL_18.log";

void LoggerCreate(const char *fileName)
{
	FILE *output;

	memset(g_LoggerFileName, 0, LOGGER_FILENAME_MAX);
	strncpy(g_LoggerFileName, fileName, LOGGER_FILENAME_MAX - 1);

	if ((output = fopen(g_LoggerFileName, "w")) != NULL)
		fclose(output);
}

void LoggerDestroy()
{
	//
}

void LoggerWrite(const char *format, ...)
{
	va_list ap;
	FILE    *output;

	if ((output = fopen(g_LoggerFileName, "a+")) == NULL)
		return;

	va_start(ap, format);
	vfprintf(output, format, ap);
	va_end(ap);

	fclose(output);
}
