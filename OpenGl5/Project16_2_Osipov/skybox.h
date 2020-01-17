/*
Осипов Лев Игоревич
OpenGL. Проект 16-2.
Visual Studio 2013
23.03.2016
Сделано:
1) Дом и три Дедпула по мешам, скайбокс, три источника освещения (видны на доме)
2) Фотокуб с различными картинками на всех гранях, картинки перетекают в другие (и обратно)
Перетекание осуществляется в двух режимах - автоматическом и ручном (по умолчанию автоматический)
Переключение режима перетекания - клавиша f, управление в ручном режиме - клавиши q и e
3) Три Дедпула реализованы по-разному:
	1. Первый Дедпул - просто Дедпул.
	2. Второй Дедпул реализован с отблесками (как будто сделан из металла).
		Реализовано управление отблесками - стрелки влево и вправо - площадь отблесков, стрелки вниз и вверх - "сила" отблесков
	3. Третий Дедпул - это просто Дедпул с деревянной текстурой (подключил в mtl другую картинку)
Код закомментирован.
*/
#pragma once

#include "texture.h"
#include "vertexBufferObject.h"

// Class for using skybox.
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