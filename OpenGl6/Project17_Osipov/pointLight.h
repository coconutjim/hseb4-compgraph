/*
������ ��� ��������
������ 17. OpenGL6
Visual Studio 2013
20.03.2016
�������:
1) ��������� 4 ������� (� ����������� ���� � ���)
2) ��������� ����������� ���������/���������� ������������� ��������� ����� (������� �)
3) ��������� 3 ����� �������� ��������� �����
4) ����������� ���������/���������� �������� ���������� - ������� 1, 2 � 3 ��������������
5) ��� ���������������
*/
#pragma once

#include "shaders.h"

// Support class for adding point lights to scene.
class CPointLight
{
public:
	glm::vec3 vColor; // Color of point light
	glm::vec3 vPosition; // and position

	float fAmbient;
	int bOn;

	float fConstantAtt;
	float fLinearAtt;
	float fExpAtt;

	void SetUniformData(CShaderProgram* spProgram, string sLightVarName);

	CPointLight();
	CPointLight(glm::vec3 a_vColor, glm::vec3 a_vPosition, float a_fAmbient, int a_bOn, float a_fConstantAtt, float a_fLinearAtt, float a_fExpAtt);
};