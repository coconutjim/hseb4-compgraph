/*
Осипов Лев Игоревич
Проект 18. OpenGL7
Visual Studio 2013
20.03.2016
Сделано:
1) на сцену добавлены объекты - дом, сундук и 3 Дедпула
2) у всех объектов можно посмотреть нормали
3) кроме существующей системы частиц, добавлено еще 3 дополнительных системы (под Дедпулами). Они имеют разные параметры,
средняя имитирует пламя
4) параметры существующей системы частиц выводятся на сцену и изменяются с помощью клавиш (клавиши управления см. на сцене)
5) можно изменить скорость вращения объекта (клавиши управления см. на сцене)
6) вся информация об управлении и об авторе программе вынесена на сцену
7) код закомментирован
*/
#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "texture.h"
#include "shaders.h"
#include "vertexBufferObject.h"

/********************************

Class:		CFreeTypeFont

Purpose:	Wraps FreeType fonts and
			their usage with OpenGL.

********************************/

class CFreeTypeFont
{
public:
	bool LoadFont(string sFile, int iPXSize);
	bool LoadSystemFont(string sName, int iPXSize);

	int GetTextWidth(string sText, int iPXSize);

	void Print(string sText, int x, int y, int iPXSize = -1);
	void PrintFormatted(int x, int y, int iPXSize, char* sText, ...);

	void DeleteFont();

	void SetShaderProgram(CShaderProgram* a_shShaderProgram);

	CFreeTypeFont();
private:
	void CreateChar(int iIndex);

	CTexture tCharTextures[256];
	int iAdvX[256], iAdvY[256];
	int iBearingX[256], iBearingY[256];
	int iCharWidth[256], iCharHeight[256];
	int iLoadedPixelSize, iNewLine;

	bool bLoaded;

	UINT uiVAO;
	CVertexBufferObject vboData;

	FT_Library ftLib;
	FT_Face ftFace;
	CShaderProgram* shShaderProgram;
};
