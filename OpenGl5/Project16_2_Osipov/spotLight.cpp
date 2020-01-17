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

