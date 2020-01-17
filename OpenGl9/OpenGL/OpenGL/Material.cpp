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
#include "Material.h"
// �������� ��������� �� ��������� � �� ����������
void MaterialDefault(Material &material)
{
	material.texture = 0;

	material.ambient.set(0.2f, 0.2f, 0.2f, 1.0f);
	material.diffuse.set(0.8f, 0.8f, 0.8f, 1.0f);
	material.specular.set(0.0f, 0.0f, 0.0f, 1.0f);
	material.emission.set(0.0f, 0.0f, 0.0f, 1.0f);
	material.shininess = 0.0f;
}

void MaterialSetup(GLuint program, const Material &material)
{
	TextureSetup(program, 0, "material.texture", material.texture);

	glUniform4fv(glGetUniformLocation(program, "material.ambient"), 1, material.ambient.v);
	glUniform4fv(glGetUniformLocation(program, "material.diffuse"), 1, material.diffuse.v);
	glUniform4fv(glGetUniformLocation(program, "material.specular"), 1, material.specular.v);
	glUniform4fv(glGetUniformLocation(program, "material.emission"), 1, material.emission.v);

	glUniform1fv(glGetUniformLocation(program, "material.shininess"), 1, &material.shininess);
}
