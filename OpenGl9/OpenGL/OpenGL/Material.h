/*
������ ��� ��������
������ 19. OpenGL8
Visual Studio 2013
24.03.2016
�������:
1) ����������� 7 �������������� ��������:
���������, ��������� �� ������, ������ ������������, ������ �����, ������ �����, ��������, �����������
(��������� - ������� F8, F9, F11, NUMPAD0, NUMPAD1, NUMPAD2 ��������������)
2) ���������� Canny - NUMPAD3
3) ���������� �������� ������� ���������� �������� - ������� Q � E
4) ����������� ���������� ����������� ��������, ��� ������������, ��� � ����������� (�� �� ����, �������, ��������� �� ��������� � ������������)
���������� ����������� ���������. � ��������� �������� ������������ ���� �������� ��������� ����� � ������, � ��������� ���, � �����
����� �������� ��� � ��������� ����� � ����, � � Canny ��� ������ �������
������ ������������ ��������:
	1. F5 - �������� - ������� ����� � ������
	2. F6 - ������ - ������� ����� � ������
	3. F7 - ��������� - ������� ����� � ������
	3. F9 - ��������� �� ������ - ������� ����� � ������
	4. F10 - ������������ - ������� ����� � ������ (������) � ������� ����� � ���� (����)
	5. F11 - ����� - ������� ����� � ������ (������) � ������� ����� � ���� (����������)
	6. NUMPAD0 - ����� - ������� ����� � ������ (����� �����) � ������� ����� � ���� (��������)
	7. NUMPAD1 - ������������� - ������� ����� � ������
	8. NUMPAD2 - ����������� - ������� ����� � ������
	9. NUMPAD3 - Canny - ������� ����� � ������ (������� �������� �� ������), ������� ����� � ���� (�������� ��������� ����������).
		����� �������� � ����� �������������� ����� ���������� ������� Canny - ���� ������ ������, ���� ������ ����� � ��������������� (��� ������)
5) ��� ���������������
*/
#ifndef MATERIAL_H
#define MATERIAL_H
// �������������� ���������
#include "common.h"
#include "math/math3d.h"
#include "OpenGL.h"
#include "Texture.h"

struct Material
{
	GLuint texture;

	vec4  ambient;
	vec4  diffuse;
	vec4  specular;
	vec4  emission;
	float shininess;
};

void MaterialDefault(Material &material);
void MaterialSetup(GLuint program, const Material &material);

#endif /* MATERIAL_H */
