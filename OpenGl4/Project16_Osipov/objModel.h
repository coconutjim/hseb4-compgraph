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

#include "texture.h"
#include "vertexBufferObject.h"

// Class for handling obj model files.
class CObjModel
{
public:
	bool LoadModel(string sFileName, string sMtlFileName);
	void RenderModel();
	void DeleteModel();

	int GetPolygonCount();

	CObjModel();
private:
	bool bLoaded;
	int iAttrBitField;
	int iNumFaces;

	bool LoadMaterial(string sFullMtlFileName);

	CVertexBufferObject vboModelData;
	UINT uiVAO;
	CTexture tAmbientTexture;
};