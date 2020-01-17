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

#include "material.h"

CMaterial::CMaterial()
{
	fSpecularIntensity = 1.0f;
	fSpecularPower = 32.0f;
}

CMaterial::CMaterial(float a_fSpecularIntensity, float a_fSpecularPower)
{
	fSpecularIntensity = a_fSpecularIntensity;
	fSpecularPower = a_fSpecularPower;
}

/*-----------------------------------------------

Name:	SetUniformData

Params:	spProgram - shader program
		sMaterialVarName - name of material variable

Result:	Sets all material uniform data.

/*---------------------------------------------*/

void CMaterial::SetUniformData(CShaderProgram* spProgram, string sMaterialVarName)
{
	spProgram->SetUniform(sMaterialVarName+".fSpecularIntensity", fSpecularIntensity);
	spProgram->SetUniform(sMaterialVarName+".fSpecularPower", fSpecularPower);
}