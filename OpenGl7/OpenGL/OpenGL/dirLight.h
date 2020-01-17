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

#include "shaders.h"

/********************************

Class:		CDirectionalLight

Purpose:	Support class for adding
			directional lights to scene.

********************************/

class CDirectionalLight
{
public:
	glm::vec3 vColor; // Color of directional light
	glm::vec3 vDirection; // and its direction

	float fAmbient;
	int iSkybox;

	void SetUniformData(CShaderProgram* spProgram, string sLightVarName);

	CDirectionalLight();
	CDirectionalLight(glm::vec3 a_vColor, glm::vec3 a_vDirection, float a_fAmbient, int a_iSkybox);
};