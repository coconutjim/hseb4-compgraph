/*
Осипов Лев Игоревич
Проект 17. OpenGL6
Visual Studio 2013
20.03.2016
Сделано:
1) добавлены 4 Дедпула (и реализованы тени к ним)
2) добавлена возможность включения/отключения направленного источника света (клавиша Е)
3) добавлены 3 новых точечных источника света
4) реалзиовано включение/выключение точечных источников - клавиши 1, 2 и 3 соответственно
5) код закомментирован
*/
#pragma once

#include "shaders.h"

// Support class for adding point lights to scene.
class CPointLight
{
public:
	glm::vec3 vColor; // Color of point light
	glm::vec3 vPosition; // and position

	float fAmbient;
	int bOn;

	float fConstantAtt;
	float fLinearAtt;
	float fExpAtt;

	void SetUniformData(CShaderProgram* spProgram, string sLightVarName);

	CPointLight();
	CPointLight(glm::vec3 a_vColor, glm::vec3 a_vPosition, float a_fAmbient, int a_bOn, float a_fConstantAtt, float a_fLinearAtt, float a_fExpAtt);
};