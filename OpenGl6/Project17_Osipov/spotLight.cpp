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

#include "spotLight.h"

CSpotLight::CSpotLight()
{
	vColor = glm::vec3(1.0f, 1.0f, 1.0f);
	vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	vDirection = glm::vec3(0.0f, 0.0f, -1.0f);

	bOn = 1;
	fConeAngle = 20.0f;
	fLinearAtt = 0.02f;
}

CSpotLight::CSpotLight(glm::vec3 a_vColor, glm::vec3 a_vPosition, glm::vec3 a_vDirection, int a_bOn, float a_fConeAngle, float a_fLinearAtt)
{
	vColor = a_vColor;
	vPosition = a_vPosition;
	vDirection = a_vDirection;
	
	bOn = a_bOn;
	fConeAngle = a_fConeAngle;
	fLinearAtt = a_fLinearAtt;
}

// Sets all spot light data.
// spProgram - shader program
// sLightVarName - name of spot light variable
void CSpotLight::SetUniformData(CShaderProgram* spProgram, string sLightVarName)
{
	spProgram->SetUniform(sLightVarName+".vColor", vColor);
	spProgram->SetUniform(sLightVarName+".vPosition", vPosition);
	spProgram->SetUniform(sLightVarName+".vDirection", vDirection);

	spProgram->SetUniform(sLightVarName+".bOn", bOn);
	spProgram->SetUniform(sLightVarName+".fConeAngle", fConeAngle);
	spProgram->SetUniform(sLightVarName+".fConeCosine", float(cos(fConeAngle*3.1415f/180.0f)));
	spProgram->SetUniform(sLightVarName+".fLinearAtt", fLinearAtt);
}

