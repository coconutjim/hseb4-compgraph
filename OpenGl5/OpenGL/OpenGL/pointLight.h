/*
������ ��� ��������
OpenGL. ������ 16-2.
Visual Studio 2013
23.03.2016
�������:
1) ��� � ��� ������� �� �����, ��������, ��� ��������� ��������� (����� �� ����)
2) ������� � ���������� ���������� �� ���� ������, �������� ���������� � ������ (� �������)
����������� �������������� � ���� ������� - �������������� � ������ (�� ��������� ��������������)
������������ ������ ����������� - ������� f, ���������� � ������ ������ - ������� q � e
3) ��� ������� ����������� ��-�������:
	1. ������ ������ - ������ ������.
	2. ������ ������ ���������� � ���������� (��� ����� ������ �� �������).
		����������� ���������� ����������: ������� ����� � ������ - ������� ���������, ������� ���� � ����� - "����" ���������
	3. ������ ������ - ��� ������ ������ � ���������� ��������� (��������� � mtl ������ ��������)
��� ���������������.
*/
#pragma once

#include "shaders.h"

// Support class for adding point lights to scene.
class CPointLight
{
public:
	glm::vec3 vColor; // Color of point light
	glm::vec3 vPosition; // and position

	int bOn;

	float fAmbient;

	float fConstantAtt;
	float fLinearAtt;
	float fExpAtt;

	void SetUniformData(CShaderProgram* spProgram, string sLightVarName);

	CPointLight();
	CPointLight(glm::vec3 a_vColor, glm::vec3 a_vPosition, float a_fAmbient, float a_fConstantAtt, float a_fLinearAtt, float a_fExpAtt);
};