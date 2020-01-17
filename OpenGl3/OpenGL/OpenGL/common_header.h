/*
Осипов Лев Игоревич
Проект 14. OpenGL3
Visual Studio 2013
25.02.2016
Реализовано:
1) в существующих источниках - реализованы свитчеры солнца и текущего точечного источника (клавиши p и l соответственно)
2) реализованы три новых источника - точечный, прожектор и направленный. включение/отключение - клавиши 1, 2 и 3 соответственно
3) реализовано вращение точечного источника и прожектора. включение/отключение - клавиши 4 и 5 соответственно
4) реализовано динамическое изменение цвета созданного направленного источника. включение - отключение - клавиша 6
5) код закомментирован
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
