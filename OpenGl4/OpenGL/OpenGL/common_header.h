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
// Header files of frequent usage

#include <ctime>
#include <windows.h>

#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <set>

using namespace std;

#include <gl/glew.h>
#include <glm/glm.hpp>

// Some useful defines

#define FOR(q,n) for(int q=0;q<n;q++)
#define SFOR(q,s,e) for(int q=s;q<=e;q++)
#define RFOR(q,n) for(int q=n;q>=0;q--)
#define RSFOR(q,s,e) for(int q=s;q>=e;q--)

#define ESZ(elem) (int)elem.size()
