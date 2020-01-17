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

#include "texture.h"
#include "vertexBufferObject.h"

/********************************

Class:		CSkybox

Purpose:	Class for using skybox.

********************************/

class CSkybox
{
public:
	void LoadSkybox(string a_sDirectory, string a_sFront, string a_sBack, string a_sLeft, string a_sRight, string a_sTop, string a_sBottom);
	void RenderSkybox();

	void DeleteSkybox();
private:
	UINT uiVAO;
	CVertexBufferObject vboRenderData;
	CTexture tTextures[6];
	string sDirectory;
	string sFront, sBack, sLeft, sRight, sTop, sBottom;
};