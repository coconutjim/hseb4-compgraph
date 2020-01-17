/*
������ ��� ��������
������ 19. OpenGL8
Visual Studio 2013
22.03.2016
�������:
1) ����������� 7 �������������� ��������:
���������, ��������� �� ������, ������ ������������, ������ �����, ������ �����, ��������, �����������
(��������� - ������� F8, F9, F11, NUMPAD0, NUMPAD1, NUMPAD2 ��������������)
2) ���������� �������� ������� ���������� �������� - ������� Q � E
3) ����������� ���������� ����������� ��������, ��� ������������, ��� � ����������� (�� �� ����, �������, ��������� �� ��������� � ������������)
���������� ����������� ���������. � ��������� �������� ������������ ���� �������� ��������� ����� � ������, � ��������� ���, � �����
����� �������� ��� � ��������� ����� � ����
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
4) ��� ���������������
*/
#ifndef MESH_H
#define MESH_H
// �������� 3D �������
#include "common.h"
#include "math/math3d.h"
#include "math/mathgl.h"
#include "OpenGL.h"

struct Mesh
{
	GLuint   vao, vbo[2];
	uint32_t vcount, icount;

	vec3 position;
	mat3 rotation;
};

void MeshCreateQuad(Mesh &mesh, const vec3 &position, float size);
void MeshCreatePlane(Mesh &mesh, const vec3 &position, float size);
void MeshCreateCube(Mesh &mesh, const vec3 &position, float size);
void MeshCreateSphere(Mesh &mesh, const vec3 &position, float size);
void MeshCreateTorus(Mesh &mesh, const vec3 &position, float size);

const mat4 MeshGetModelMatrix(const Mesh &mesh);

void MeshRender(const Mesh &mesh);
void MeshDestroy(Mesh &mesh);

#endif /* MESH_H */
