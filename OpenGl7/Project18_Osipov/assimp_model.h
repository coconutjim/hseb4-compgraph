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

#include "shaders.h"
#include "vertexBufferObject.h"
#include "texture.h"

class CAssimpModel
{
public:
	bool LoadModelFromFile(char* sFilePath);

	static void FinalizeVBO();
	static void BindModelsVAO();

	void RenderModel(GLenum   = GL_TRIANGLES);
	CAssimpModel();
private:
	bool bLoaded;
	static CVertexBufferObject vboModelData;
	static UINT uiVAO;
	static vector<CTexture> tTextures;
	vector<int> iMeshStartIndices;
	vector<int> iMeshSizes;
	vector<int> iMaterialIndices;
	int iNumMaterials;
};
