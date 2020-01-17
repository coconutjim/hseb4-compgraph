/*
Осипов Лев Игоревич
Проект 19. OpenGL8
Visual Studio 2013
22.03.2016
Сделано:
1) реализовано 7 дополнительных фильтров:
отражение, искажение по синусу, эффект закручивания, эффект линзы, эффект волны, контраст, бинаризация
(включение - клавиши F8, F9, F11, NUMPAD0, NUMPAD1, NUMPAD2 соответственно)
2) реализован контроль области применения фильтров - клавиши Q и E
3) реализовано управление параметрами фильтров, как существующих, так и добавленных (но не всех, конечно, некоторые не нуждаются в конфигурации)
Управление реализовано стрелками. у некоторых фильтров регулируется один параметр стрелками влево и вправо, у некоторых два, и тогда
нужно работать еще и стрелками вверх и вниз
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
4) код закомментирован
*/
#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "math/math3d.h"
#include "math/mathgl.h"
#include "OpenGL.h"

struct Camera
{
	vec3 position; //позиция камеры
	vec3 rotation;  
	mat4 projection; // матрица проецирования
};

void CameraLookAt(Camera &camera, const vec3 &position, const vec3 &center, const vec3 &up);
void CameraPerspective(Camera &camera, float fov, float aspect, float zNear, float zFar);
void CameraOrtho(Camera &camera, float left, float right,
	float bottom, float top, float zNear, float zFar);
void CameraRotate(Camera &camera, float x, float y, float z);
void CameraMove(Camera &camera, float x, float y, float z);
void CameraSetup(GLuint program, const Camera &camera, const mat4 &model);
void CameraSetupLightMatrix(GLuint program, const Camera &camera);

#endif /* CAMERA_H */
