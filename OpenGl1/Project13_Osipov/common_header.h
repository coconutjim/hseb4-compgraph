/*
Осипов Лев Игоревич
Проект 13.
Visual Studio 2013
04.02.2016
Сделано:
1) Изменен цвет окна
2) Треугольник и четырехугольник перемещены в правый нижний край
3) Реализована радуга
4) Реализован контур пятиконечной звезды
5) Реализованы две шестиконечные звезды
6) Реализован переключатель между пятиконечной звездой
и шестиконечными звездами. Для переключения следует нажать клавишу s
7) Код в RenderScene.cpp декомпозирован и закомментирован
*/
// Header files of frequent usage

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

// Some useful defines

#define FOR(q,n) for(int q=0;q<n;q++)
#define SFOR(q,s,e) for(int q=s;q<=e;q++)
#define RFOR(q,n) for(int q=n;q>=0;q--)
#define RSFOR(q,s,e) for(int q=s;q>=e;q--)

#define ESZ(elem) (int)elem.size()
