/*
Осипов Лев Игоревич
Проект 19. OpenGL8
Visual Studio 2013
24.03.2016
Сделано:
1) реализовано 7 дополнительных фильтров:
отражение, искажение по синусу, эффект закручивания, эффект линзы, эффект волны, контраст, бинаризация
(включение - клавиши F8, F9, F11, NUMPAD0, NUMPAD1, NUMPAD2 соответственно)
2) Реализован Canny - NUMPAD3
3) реализован контроль области применения фильтров - клавиши Q и E
4) реализовано управление параметрами фильтров, как существующих, так и добавленных (но не всех, конечно, некоторые не нуждаются в конфигурации)
Управление реализовано стрелками. у некоторых фильтров регулируется один параметр стрелками влево и вправо, у некоторых два, и тогда
нужно работать еще и стрелками вверх и вниз, а у Canny еще больше нюансов
Список регулируемых фильтров:
	1. F5 - размытие - стрелки влево и вправо
	2. F6 - рельеф - стрелки влево и вправо
	3. F7 - абберация - стрелки влево и вправо
	3. F9 - искажение по синусу - стрелки влево и вправо
	4. F10 - закручивание - стрелки влево и вправо (радиус) и стрелки вверх и вниз (угол)
	5. F11 - линза - стрелки влево и вправо (радиус) и стрелки вверх и вниз (увеличение)
	6. NUMPAD0 - волна - стрелки влево и вправо (длина волны) и стрелки вверх и вниз (смещение)
	7. NUMPAD1 - контрастность - стрелки влево и вправо
	8. NUMPAD2 - бинаризация - стрелки влево и вправо
	9. NUMPAD3 - Canny - стрелки влево и вправо (степень размытия по Гауссу), стрелки вверх и вниз (контроль пороговой фильтрации).
		Также клавишей С можно контролировать этапы применения фильтра Canny - либо полный фильтр, либо только Гаусс с обесцвечиванием (без Собеля)
5) код закомментирован
*/
#include "Light.h"
// все типы источников освещения
void LightDefault(Light &light, LightType type)
{
	light.type = type;

	light.ambient.set(0.0f, 0.0f, 0.0f, 1.0f);
	light.diffuse.set(1.0f, 1.0f, 1.0f, 1.0f);
	light.specular.set(1.0f, 1.0f, 1.0f, 1.0f);
	light.position.set(0.0f, 0.0f, 1.0f, 0.0f);
	light.attenuation.set(1.0f, 0.0f, 0.0f);
	light.spotDirection.set(0.0f, 0.0f, -1.0f);
	light.spotExponent = 0.0f;
	light.spotCosCutoff = -1.0f; // cos 180 градусов == -1
}

void LightSetup(GLuint program, const Light &light)
{
	glUniform4fv(glGetUniformLocation(program, "light.ambient"), 1, light.ambient.v);
	glUniform4fv(glGetUniformLocation(program, "light.diffuse"), 1, light.diffuse.v);
	glUniform4fv(glGetUniformLocation(program, "light.specular"), 1, light.specular.v);
	glUniform4fv(glGetUniformLocation(program, "light.position"), 1, light.position.v);

	glUniform3fv(glGetUniformLocation(program, "light.attenuation"), 1, light.attenuation.v);
	glUniform3fv(glGetUniformLocation(program, "light.spotDirection"), 1, light.spotDirection.v);

	glUniform1fv(glGetUniformLocation(program, "light.spotExponent"), 1, &light.spotExponent);
	glUniform1fv(glGetUniformLocation(program, "light.spotCosCutoff"), 1, &light.spotCosCutoff);
}
