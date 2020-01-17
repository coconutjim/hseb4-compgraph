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