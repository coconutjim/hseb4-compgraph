/*
������ ��� ��������
OpenGL. ������ 16-2.
Visual Studio 2013
08.03.2016
�������:
1) ��� � ��� ������� �� �����, ��������, ��� ��������� ��������� (����� �� ����)
2) ������� � ���������� ���������� �� ���� ������, �������� ���������� � ������ (� �������)
����������� �������������� � ���� ������� - �������������� � ������ (�� ��������� ��������������)
������������ ������ ����������� - ������� f, ���������� � ������ ������ - ������� q � e
3) ������� ������ � "����������" ������
��� ���������������.
*/
#pragma once

#include "vertexBufferObject.h"

extern glm::vec3 vCubeVertices[36];
extern glm::vec3 vCubeVertices2[24];
extern unsigned int iCubeindices[36];
extern glm::vec2 vCubeTexCoords[6];
extern glm::vec3 vCubeNormals[6];
extern glm::vec3 vGround[6];

int GenerateTorus(CVertexBufferObject &vboDest, float fRadius, float fTubeRadius, int iSubDivAround, int iSubDivTube);
int GenerateCylinder(CVertexBufferObject &vboDest, float fRadius, float fHeight, int iSubDivAround, float fMapU = 1.0f, float fMapV = 1.0f);
void AddSceneObjects(CVertexBufferObject& vboDest);
void AddCube(CVertexBufferObject& vboDest);
extern int iTorusFaces, iTorusFaces2;
extern int iCylinderFaces;