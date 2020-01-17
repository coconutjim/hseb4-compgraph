/*
Осипов Лев Игоревич
Проект 17. OpenGL6
Visual Studio 2013
20.03.2016
Сделано:
1) добавлены 4 Дедпула (и реализованы тени к ним)
2) добавлена возможность включения/отключения направленного источника света (клавиша Е)
3) добавлены 3 новых точечных источника света
4) реалзиовано включение/выключение точечных источников - клавиши 1, 2 и 3 соответственно
5) код закомментирован
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