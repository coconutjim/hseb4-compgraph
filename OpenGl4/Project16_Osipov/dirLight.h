/*
Осипов Лев Игоревич
OpenGL. Проект 16.
Visual Studio 2013
06.03.2016
Сделано:
1) Объекты сгенерированы раличными способами (куб - индексно, торы - процедурно, Дедпулы и Тор - используя меши)
2) Реализовано три дополнительных источников освещения - белый направленный, синий точечный и красный прожектор (последние 2 видны слева от торов)
3) Встроен собственный скайбокс
4) Реализовано три типа тумана (перелючение - клавиша f) и регулирование его параметров стрелками
5) Реализовано много объектов с движением в рамках композиции "Деревня Дедпулов, которую охраняет Тор"
Код закомментирован.
*/
#pragma once

#include "shaders.h"

// Support class for adding directional lights to scene.
class CDirectionalLight
{
public:
	glm::vec3 vColor; // Color of directional light
	glm::vec3 vDirection; // and its direction

	float fAmbient;

	void SetUniformData(CShaderProgram* spProgram, string sLightVarName);

	CDirectionalLight();
	CDirectionalLight(glm::vec3 a_vColor, glm::vec3 a_vDirection, float a_fAmbient);
};