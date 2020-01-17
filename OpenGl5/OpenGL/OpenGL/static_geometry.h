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
		Реализовано управление отблесками: стрелки влево и вправо - площадь отблесков, стрелки вниз и вверх - "сила" отблесков
	3. Третий Дедпул - это просто Дедпул с деревянной текстурой (подключил в mtl другую картинку)
Код закомментирован.
*/
#pragma once

#include "vertexBufferObject.h"

extern glm::vec3 vCubeVertices[36];
extern glm::vec3 vCubeVertices2[24];
extern unsigned int iCubeindices[36];
extern glm::vec2 vCubeTexCoords[6];
extern glm::vec3 vCubeNormals[6];
extern glm::vec3 vGround[6];

int GenerateTorus(CVertexBufferObject &vboDest, float fRadius, float fTubeRadius, int iSubDivAround, int iSubDivTube);
int GenerateCylinder(CVertexBufferObject &vboDest, float fRadius, float fHeight, int iSubDivAround, float fMapU = 1.0f, float fMapV = 1.0f);
void AddSceneObjects(CVertexBufferObject& vboDest);
void AddCube(CVertexBufferObject& vboDest);
extern int iTorusFaces, iTorusFaces2;
extern int iCylinderFaces;