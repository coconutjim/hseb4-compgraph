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
#include "common_header.h"

#include "dirLight.h"

CDirectionalLight::CDirectionalLight()
{
	vColor = glm::vec3(1.0f, 1.0f, 1.0f);
	vDirection = glm::vec3(0.0f, -1.0f, 0.0f);

	fAmbient = 0.25f;
	iSkybox = 0;
}
CDirectionalLight::CDirectionalLight(glm::vec3 a_vColor, glm::vec3 a_vDirection, int a_bOn, float a_fAmbient, int a_iSkybox)
{
	vColor = a_vColor;
	vDirection = a_vDirection;
	bOn = a_bOn;

	fAmbient = a_fAmbient;
	iSkybox = a_iSkybox;
}

// Sets all directional light data.
// spProgram - shader program
// sLightVarName - name of directional light variable
void CDirectionalLight::SetUniformData(CShaderProgram *spProgram, std::string sLightVarName)
{
	spProgram->SetUniform(sLightVarName+".vColor", vColor);
	spProgram->SetUniform(sLightVarName+".vDirection", vDirection);
	spProgram->SetUniform(sLightVarName + ".bOn", bOn);

	spProgram->SetUniform(sLightVarName+".fAmbient", fAmbient);
	spProgram->SetUniform(sLightVarName + ".iSkybox", iSkybox);
}