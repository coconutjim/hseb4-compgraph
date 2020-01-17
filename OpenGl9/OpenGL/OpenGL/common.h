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
#ifndef COMMON_H
#define COMMON_H

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <cassert>
#include <cmath>
#include <ctime>

#define VERT_POSITION  0
#define VERT_TEXCOORD  1
#define VERT_NORMAL    2

#define FRAG_OUTPUT0   0

#define TEXTURE_COLOR  0
#define TEXTURE_DEPTH  1

#define GL_OFFSET(x) ((const GLvoid*)(x))

typedef float float2[2];
typedef float float3[3];
typedef float float4[4];

#if defined(_MSC_VER)
typedef __int8           int8_t;
typedef unsigned __int8  uint8_t;
typedef __int16          int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32          int32_t;
typedef unsigned __int32 uint32_t;

#define snprintf _snprintf

#elif defined(__MINGW32__)
#include <stdint.h>

#else
#error You must compile this code with MSVC or MinGW!
#endif

#include "Logger.h"

// загрузка файла целиком в память
bool LoadFile(const char *fileName, bool binary, uint8_t **buffer, uint32_t *size);

#endif /* COMMON_H */
