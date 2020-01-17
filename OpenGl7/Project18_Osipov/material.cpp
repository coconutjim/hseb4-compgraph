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

#include "material.h"

CMaterial::CMaterial()
{
	fSpecularIntensity = 1.0f;
	fSpecularPower = 32.0f;
}

CMaterial::CMaterial(float a_fSpecularIntensity, float a_fSpecularPower)
{
	fSpecularIntensity = a_fSpecularIntensity;
	fSpecularPower = a_fSpecularPower;
}

/*-----------------------------------------------

Name:	SetUniformData

Params:	spProgram - shader program
		sMaterialVarName - name of material variable

Result:	Sets all material uniform data.

/*---------------------------------------------*/

void CMaterial::SetUniformData(CShaderProgram* spProgram, string sMaterialVarName)
{
	spProgram->SetUniform(sMaterialVarName+".fSpecularIntensity", fSpecularIntensity);
	spProgram->SetUniform(sMaterialVarName+".fSpecularPower", fSpecularPower);
}