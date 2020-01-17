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
#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "math/math3d.h"
#include "math/mathgl.h"
#include "OpenGL.h"

struct Camera
{
	vec3 position; //������� ������
	vec3 rotation;  
	mat4 projection; // ������� �������������
};

void CameraLookAt(Camera &camera, const vec3 &position, const vec3 &center, const vec3 &up);
void CameraPerspective(Camera &camera, float fov, float aspect, float zNear, float zFar);
void CameraOrtho(Camera &camera, float left, float right,
	float bottom, float top, float zNear, float zFar);
void CameraRotate(Camera &camera, float x, float y, float z);
void CameraMove(Camera &camera, float x, float y, float z);
void CameraSetup(GLuint program, const Camera &camera, const mat4 &model);
void CameraSetupLightMatrix(GLuint program, const Camera &camera);

#endif /* CAMERA_H */
