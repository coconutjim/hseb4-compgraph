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
#include "common_header.h"

#include "dirLight.h"

CDirectionalLight::CDirectionalLight()
{
	vColor = glm::vec3(1.0f, 1.0f, 1.0f);
	vDirection = glm::vec3(0.0f, -1.0f, 0.0f);

	fAmbient = 0.25f;
}
CDirectionalLight::CDirectionalLight(glm::vec3 a_vColor, glm::vec3 a_vDirection, float a_fAmbient)
{
	vColor = a_vColor;
	vDirection = a_vDirection;

	fAmbient = a_fAmbient;
}

// Sets all directional light data.
// spProgram - shader program
// sLightVarName - name of directional light variable
void CDirectionalLight::SetUniformData(CShaderProgram *spProgram, std::string sLightVarName)
{
	spProgram->SetUniform(sLightVarName+".vColor", vColor);
	spProgram->SetUniform(sLightVarName+".vDirection", vDirection);

	spProgram->SetUniform(sLightVarName+".fAmbient", fAmbient);
}