/*
Осипов Лев Игоревич
Проект 14. OpenGL3
Visual Studio 2013
25.02.2016
Реализовано:
1) в существующих источниках - реализованы свитчеры солнца и текущего точечного источника (клавиши p и l соответственно)
2) реализованы три новых источника - точечный, прожектор и направленный. включение/отключение - клавиши 1, 2 и 3 соответственно
3) реализовано вращение точечного источника и прожектора. включение/отключение - клавиши 4 и 5 соответственно
4) реализовано динамическое изменение цвета созданного направленного источника. включение - отключение - клавиша 6
5) код закомментирован
*/
#include "common_header.h"

#include "dirLight.h"

CDirectionalLight::CDirectionalLight()
{
	vColor = glm::vec3(1.0f, 1.0f, 1.0f);
	vDirection = glm::vec3(0.0f, -1.0f, 0.0f);

	fAmbient = 0.25f;
}
CDirectionalLight::CDirectionalLight(glm::vec3 a_vColor, glm::vec3 a_vDirection, int a_bOn, float a_fAmbient)
{
	vColor = a_vColor;
	vDirection = a_vDirection;
	bOn = a_bOn;

	fAmbient = a_fAmbient;
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
}