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

// Support class for adding spotlights to scene.
class CSpotLight
{
public:
	glm::vec3 vColor;
	glm::vec3 vPosition;
	glm::vec3 vDirection;

	int bOn;
	float fConeAngle;
	float fLinearAtt;

	void SetUniformData(CShaderProgram* spProgram, string sLightVarName);

	CSpotLight();
	CSpotLight(glm::vec3 a_vColor, glm::vec3 a_vPosition, glm::vec3 a_vDirection, int a_bOn, float a_fConeAngle, float a_fLinearAtt);
private:
	// This shouldn't be changed from outside
	float fConeCosine;
};