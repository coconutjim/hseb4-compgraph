/*
������ ��� ��������
������ 18. OpenGL7
Visual Studio 2013
20.03.2016
�������:
1) �� ����� ��������� ������� - ���, ������ � 3 �������
2) � ���� �������� ����� ���������� �������
3) ����� ������������ ������� ������, ��������� ��� 3 �������������� ������� (��� ���������). ��� ����� ������ ���������,
������� ��������� �����
4) ��������� ������������ ������� ������ ��������� �� ����� � ���������� � ������� ������ (������� ���������� ��. �� �����)
5) ����� �������� �������� �������� ������� (������� ���������� ��. �� �����)
6) ��� ���������� �� ���������� � �� ������ ��������� �������� �� �����
7) ��� ���������������
*/
#pragma once

#include "shaders.h"

/********************************

Class:		CMaterial

Purpose:	Support class for handling materials
			in the scene.

********************************/

class CMaterial
{
public:
	float fSpecularIntensity;
	float fSpecularPower;

	void SetUniformData(CShaderProgram* spProgram, string sMaterialVarName);

	CMaterial();
	CMaterial(float a_fSpecularIntensity, float a_fSpecularPower);
};