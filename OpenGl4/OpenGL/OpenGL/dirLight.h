/*
������ ��� ��������
OpenGL. ������ 16.
Visual Studio 2013
06.03.2016
�������:
1) ������� ������������� ��������� ��������� (��� - ��������, ���� - ����������, ������� � ��� - ��������� ����)
2) ����������� ��� �������������� ���������� ��������� - ����� ������������, ����� �������� � ������� ��������� (��������� 2 ����� ����� �� �����)
3) ������� ����������� ��������
4) ����������� ��� ���� ������ (����������� - ������� f) � ������������� ��� ���������� ���������
5) ����������� ����� �������� � ��������� � ������ ���������� "������� ��������, ������� �������� ���"
��� ���������������.
*/
#pragma once

#include "shaders.h"

// Support class for adding directional lights to scene.
class CDirectionalLight
{
public:
	glm::vec3 vColor; // Color of directional light
	glm::vec3 vDirection; // and its direction

	float fAmbient;

	void SetUniformData(CShaderProgram* spProgram, string sLightVarName);

	CDirectionalLight();
	CDirectionalLight(glm::vec3 a_vColor, glm::vec3 a_vDirection, float a_fAmbient);
};