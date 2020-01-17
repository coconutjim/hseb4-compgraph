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