/*
������ ��� ��������
������ 14. OpenGL2
Visual Studio 2013
17.02.2016
��������� ��� �������, ��� �������������� � ���������������.
���������� ���, ��������, ������� � ��� (� ������� ����������).
����������:
1) ������������� ������ ������ ������������� - ������������� ������� ������ ���������� ����� ������ � ��������� ������:
a - �������� �����
d - �������� ������
w - �������� �����
s - �������� ����
z - �������� ������
x - �������� �����
������� ������ - �������� � ���� �������
������� ����� - �������� � ������ �������
������� ����� - ���������� ������
������� ���� - ���������� ������
�������:
���������� ���� - � + ������� �����
����� ���� ������ - t + d
2) ��������� ������ ���������� ����������� ����� - ������� r, ��� �� �������� � �� ���������� ����� ������
3) ��� �������� ������ - ����� ctrl + ������� ������ � �����, ��� �����������/��������� ������ - ����� ctrl + ������� ����� � ����
*/
#pragma once

// Wraps OpenGL shader loading and compiling.
class CShader
{
public:
	bool loadShader(string sFile, int a_iType);
	void deleteShader();

	bool isLoaded();
	UINT getShaderID();

	CShader();

private:
	UINT uiShader; // ID of shader
	int iType; // GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
	bool bLoaded; // Whether shader was loaded and compiled
};

// Wraps OpenGL shader program and make its usage easy.
class CShaderProgram
{
public:
	void createProgram();
	void deleteProgram();

	bool addShaderToProgram(CShader* shShader);
	bool linkProgram();

	void useProgram();

	UINT getProgramID();

	CShaderProgram();

private:
	UINT uiProgram; // ID of program
	bool bLinked; // Whether program was linked and is ready to use
};