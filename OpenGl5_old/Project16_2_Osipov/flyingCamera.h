/*
Осипов Лев Игоревич
OpenGL. Проект 16-2.
Visual Studio 2013
08.03.2016
Сделано:
1) Дом и два Дедпула по мешам, скайбокс, три источника освещения (видны на доме)
2) Фотокуб с различными картинками на всех гранях, картинки перетекают в другие (и обратно)
Перетекание осуществляется в двух режимах - автоматическом и ручном (по умолчанию автоматический)
Переключение режима перетекания - клавиша f, управление в ручном режиме - клавиши q и e
3) Обычный Дедпул и "деревянный" Дедпул
Код закомментирован.
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
