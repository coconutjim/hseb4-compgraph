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

// Support class for adding point lights to scene.
class CPointLight
{
public:
	glm::vec3 vColor; // Color of point light
	glm::vec3 vPosition; // and position

	int bOn;

	float fAmbient;

	float fConstantAtt;
	float fLinearAtt;
	float fExpAtt;

	void SetUniformData(CShaderProgram* spProgram, string sLightVarName);

	CPointLight();
	CPointLight(glm::vec3 a_vColor, glm::vec3 a_vPosition, float a_fAmbient, float a_fConstantAtt, float a_fLinearAtt, float a_fExpAtt);
};