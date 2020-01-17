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

#include "pointLight.h"

CPointLight::CPointLight()
{
	vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	vColor = glm::vec3(1.0f, 1.0f, 1.0f);

	fAmbient = 0.1f;
	bOn = 1;

	fConstantAtt = 0.3f;
	fLinearAtt = 0.007f;
	fExpAtt = 0.00008f;
}

CPointLight::CPointLight(glm::vec3 a_vColor, glm::vec3 a_vPosition, float a_fAmbient, float a_fConstantAtt, float a_fLinearAtt, float a_fExpAtt)
{
	vColor = a_vColor;
	vPosition = a_vPosition;
	bOn = 1;

	fAmbient = a_fAmbient;
	
	fConstantAtt = a_fConstantAtt;
	fLinearAtt = a_fLinearAtt;
	fExpAtt = a_fExpAtt;
}

// Sets all point light data.
// spProgram - shader program
// sLightVarName - name of point light variable
void CPointLight::SetUniformData(CShaderProgram* spProgram, string sLightVarName)
{
	spProgram->SetUniform(sLightVarName+".vColor", vColor);
	spProgram->SetUniform(sLightVarName+".vPosition", vPosition);
	spProgram->SetUniform(sLightVarName + ".bOn", bOn);

	spProgram->SetUniform(sLightVarName+".fAmbient", fAmbient);
	
	spProgram->SetUniform(sLightVarName+".fConstantAtt", fConstantAtt);
	spProgram->SetUniform(sLightVarName+".fLinearAtt", fLinearAtt);
	spProgram->SetUniform(sLightVarName+".fExpAtt", fExpAtt);
}

