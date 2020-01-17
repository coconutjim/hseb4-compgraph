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

// Support class for adding directional lights to scene.
class CDirectionalLight
{
public:
	glm::vec3 vColor; // Color of directional light
	glm::vec3 vDirection; // and its direction

	float fAmbient;
	int bOn;
	int iSkybox;

	void SetUniformData(CShaderProgram* spProgram, string sLightVarName);

	CDirectionalLight();
	CDirectionalLight(glm::vec3 a_vColor, glm::vec3 a_vDirection, int a_bOn, float a_fAmbient, int a_iSkybox);
};