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
#include "common_header.h"

#include "dirLight.h"

CDirectionalLight::CDirectionalLight()
{
	vColor = glm::vec3(1.0f, 1.0f, 1.0f);
	vDirection = glm::vec3(0.0f, -1.0f, 0.0f);

	fAmbient = 0.25f;
	iSkybox = 0;
}

CDirectionalLight::CDirectionalLight(glm::vec3 a_vColor, glm::vec3 a_vDirection, float a_fAmbient, int a_iSkybox)
{
	vColor = a_vColor;
	vDirection = a_vDirection;

	fAmbient = a_fAmbient;
	iSkybox = a_iSkybox;
}

/*-----------------------------------------------

Name:	SetUniformData

Params:	spProgram - shader program
		sLightVarName - name of directional light variable

Result:	Sets all directional light data.

/*---------------------------------------------*/

void CDirectionalLight::SetUniformData(CShaderProgram *spProgram, std::string sLightVarName)
{
	spProgram->SetUniform(sLightVarName+".vColor", vColor);
	spProgram->SetUniform(sLightVarName+".vDirection", vDirection);

	spProgram->SetUniform(sLightVarName+".fAmbient", fAmbient);
	spProgram->SetUniform(sLightVarName+".iSkybox", iSkybox);
}