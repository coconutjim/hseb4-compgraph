/*
������ ��� ��������
������ 14. OpenGL3
Visual Studio 2013
25.02.2016
�����������:
1) � ������������ ���������� - ����������� �������� ������ � �������� ��������� ��������� (������� p � l ��������������)
2) ����������� ��� ����� ��������� - ��������, ��������� � ������������. ���������/���������� - ������� 1, 2 � 3 ��������������
3) ����������� �������� ��������� ��������� � ����������. ���������/���������� - ������� 4 � 5 ��������������
4) ����������� ������������ ��������� ����� ���������� ������������� ���������. ��������� - ���������� - ������� 6
5) ��� ���������������
*/
#include "common_header.h"

#include "pointLight.h"

CPointLight::CPointLight()
{
	vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	vColor = glm::vec3(1.0f, 1.0f, 1.0f);

	fAmbient = 0.1f;

	fConstantAtt = 0.3f;
	fLinearAtt = 0.007f;
	fExpAtt = 0.00008f;
}

CPointLight::CPointLight(glm::vec3 a_vColor, glm::vec3 a_vPosition, int a_bOn, float a_fAmbient, float a_fConstantAtt, float a_fLinearAtt, float a_fExpAtt)
{
	vColor = a_vColor;
	vPosition = a_vPosition;

	bOn = a_bOn;
	fAmbient = a_fAmbient;
	
	fConstantAtt = a_fConstantAtt;
	fLinearAtt = a_fLinearAtt;
	fExpAtt = a_fExpAtt;
}

// Sets all point light data.
// spProgram - shader program
// sLightVarName - name of point light variable
void CPointLight::SetUniformData(CShaderProgram* spProgram, string sLightVarName)
{
	spProgram->SetUniform(sLightVarName+".vColor", vColor);
	spProgram->SetUniform(sLightVarName+".vPosition", vPosition);

	spProgram->SetUniform(sLightVarName + ".bOn", bOn);
	spProgram->SetUniform(sLightVarName+".fAmbient", fAmbient);
	
	spProgram->SetUniform(sLightVarName+".fConstantAtt", fConstantAtt);
	spProgram->SetUniform(sLightVarName+".fLinearAtt", fLinearAtt);
	spProgram->SetUniform(sLightVarName+".fExpAtt", fExpAtt);
}

