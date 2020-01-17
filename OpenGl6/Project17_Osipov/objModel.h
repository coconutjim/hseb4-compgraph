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