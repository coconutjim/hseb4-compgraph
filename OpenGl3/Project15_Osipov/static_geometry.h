/*
������ ��� ��������
������ 14. OpenGL3
Visual Studio 2013
25.02.2016
�����������:
1) � ������������ ���������� - ����������� �������� ������ � �������� ��������� ��������� (������� p � l ��������������)
2) ����������� ��� ����� ��������� - ��������, ��������� � ������������. ���������/���������� - ������� 1, 2 � 3 ��������������
3) ����������� �������� ��������� ��������� � ����������. ���������/���������� - ������� 4 � 5 ��������������
4) ����������� ������������ ��������� ����� ���������� ������������� ���������. ��������� - ���������� - ������� 6
5) ��� ���������������
*/
#pragma once

#include "vertexBufferObject.h"

extern glm::vec3 vCubeVertices[36];
extern glm::vec2 vCubeTexCoords[6];
extern glm::vec3 vCubeNormals[6];
extern glm::vec3 vGround[6];

int GenerateTorus(CVertexBufferObject &vboDest, float fRadius, float fTubeRadius, int iSubDivAround, int iSubDivTube);
int GenerateCylinder(CVertexBufferObject &vboDest, float fRadius, float fHeight, int iSubDivAround, float fMapU = 1.0f, float fMapV = 1.0f);
void AddSceneObjects(CVertexBufferObject& vboDest);

extern int iTorusFaces, iTorusFaces2;