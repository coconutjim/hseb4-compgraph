/*
������ ��� ��������
������ 14. OpenGL2
Visual Studio 2013
17.02.2016
��������� ��� �������, ��� �������������� � ���������������.
���������� ���, ��������, ������� � ��� (� ������� ����������).
����������:
1) ������������� ������ ������ ������������� - ������������� ������� ������ ���������� ����� ������ � ��������� ������:
a - �������� �����
d - �������� ������
w - �������� �����
s - �������� ����
z - �������� ������
x - �������� �����
������� ������ - �������� � ���� �������
������� ����� - �������� � ������ �������
������� ����� - ���������� ������
������� ���� - ���������� ������
�������:
���������� ���� - � + ������� �����
����� ���� ������ - t + d
2) ��������� ������ ���������� ����������� ����� - ������� r, ��� �� �������� � �� ���������� ����� ������
3) ��� �������� ������ - ����� ctrl + ������� ������ � �����, ��� �����������/��������� ������ - ����� ctrl + ������� ����� � ����
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
