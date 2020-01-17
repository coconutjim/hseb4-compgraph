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