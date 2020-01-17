/*
Осипов Лев Игоревич
Проект 17. OpenGL6
Visual Studio 2013
20.03.2016
Сделано:
1) добавлены 4 Дедпула (и реализованы тени к ним)
2) добавлена возможность включения/отключения направленного источника света (клавиша Е)
3) добавлены 3 новых точечных источника света
4) реалзиовано включение/выключение точечных источников - клавиши 1, 2 и 3 соответственно
5) код закомментирован
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

	void SetMovingKeys(int a_iForw, int a_iBack, int a_iLeft, int a_iRight, int a_iUp);
	void ResetMouse();

	// Functions that get viewing angles
	float GetAngleX(), GetAngleY();

	// Constructors
	CFlyingCamera();
	CFlyingCamera(glm::vec3 a_vEye, glm::vec3 a_vView, glm::vec3 a_vUp, float a_fSpeed, float a_fSensitivity);

private:
	POINT pCur; // For mosue rotation
	int iForw, iBack, iLeft, iRight, iUp;
};
