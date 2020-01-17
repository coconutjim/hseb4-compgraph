/*
Осипов Лев Игоревич
OpenGL. Проект 16-2.
Visual Studio 2013
08.03.2016
Сделано:
1) Дом и два Дедпула по мешам, скайбокс, три источника освещения (видны на доме)
2) Фотокуб с различными картинками на всех гранях, картинки перетекают в другие (и обратно)
Перетекание осуществляется в двух режимах - автоматическом и ручном (по умолчанию автоматический)
Переключение режима перетекания - клавиша f, управление в ручном режиме - клавиши q и e
3) Обычный Дедпул и "деревянный" Дедпул
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