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

class CFlyingCamera
{
public:
	glm::vec3 vEye, vView, vUp;
	float fSpeed;
	float fSensitivity; // How many degrees to rotate per pixel moved by mouse (nice value is 0.10)

	// Main functions
	void RotateWithMouse();
	void Update();
	glm::mat4 Look();

	void SetMovingKeys(int a_iForw, int a_iBack, int a_iLeft, int a_iRight);
	void ResetMouse();

	// Functions that get viewing angles
	float GetAngleX(), GetAngleY();

	// Constructors
	CFlyingCamera();
	CFlyingCamera(glm::vec3 a_vEye, glm::vec3 a_vView, glm::vec3 a_vUp, float a_fSpeed, float a_fSensitivity);

private:
	POINT pCur; // For mosue rotation
	int iForw, iBack, iLeft, iRight;
};
