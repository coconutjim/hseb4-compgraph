/*
Осипов Лев Игоревич
Проект 18. OpenGL7
Visual Studio 2013
20.03.2016
Сделано:
1) на сцену добавлены объекты - дом, сундук и 3 Дедпула
2) у всех объектов можно посмотреть нормали
3) кроме существующей системы частиц, добавлено еще 3 дополнительных системы (под Дедпулами). Они имеют разные параметры,
средняя имитирует пламя
4) параметры существующей системы частиц выводятся на сцену и изменяются с помощью клавиш (клавиши управления см. на сцене)
5) можно изменить скорость вращения объекта (клавиши управления см. на сцене)
6) вся информация об управлении и об авторе программе вынесена на сцену
7) код закомментирован
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

CDirectionalLight::CDirectionalLight(glm::vec3 a_vColor, glm::vec3 a_vDirection, float a_fAmbient, int a_iSkybox)
{
	vColor = a_vColor;
	vDirection = a_vDirection;

	fAmbient = a_fAmbient;
	iSkybox = a_iSkybox;
}

/*-----------------------------------------------

Name:	SetUniformData

Params:	spProgram - shader program
		sLightVarName - name of directional light variable

Result:	Sets all directional light data.

/*---------------------------------------------*/

void CDirectionalLight::SetUniformData(CShaderProgram *spProgram, std::string sLightVarName)
{
	spProgram->SetUniform(sLightVarName+".vColor", vColor);
	spProgram->SetUniform(sLightVarName+".vDirection", vDirection);

	spProgram->SetUniform(sLightVarName+".fAmbient", fAmbient);
	spProgram->SetUniform(sLightVarName+".iSkybox", iSkybox);
}