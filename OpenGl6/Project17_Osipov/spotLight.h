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

// Support class for adding spotlights to scene.
class CSpotLight
{
public:
	glm::vec3 vColor;
	glm::vec3 vPosition;
	glm::vec3 vDirection;

	int bOn;
	float fConeAngle;
	float fLinearAtt;

	void SetUniformData(CShaderProgram* spProgram, string sLightVarName);

	CSpotLight();
	CSpotLight(glm::vec3 a_vColor, glm::vec3 a_vPosition, glm::vec3 a_vDirection, int a_bOn, float a_fConeAngle, float a_fLinearAtt);
private:
	// This shouldn't be changed from outside
	float fConeCosine;
};