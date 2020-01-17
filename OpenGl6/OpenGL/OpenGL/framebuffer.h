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

#include "texture.h"
#include "shaders.h"

// Manages framebuffer objects.
class CFramebuffer
{
public:

	bool CreateFrameBufferForDepthShadow(int a_iWidth, int a_iHeight);
	

	bool CreateFramebufferWithTexture(int a_iWidth, int a_iHeight);

	bool AddDepthBuffer();
	void BindFramebuffer(bool bSetFullViewport = true);
	void BindFramebufferShadowMap();
	
	void SetFramebufferTextureFiltering(int a_tfMagnification, int a_tfMinification);
	void BindFramebufferTexture(int iTextureUnit = 0, bool bRegenMipMaps = false);

	glm::mat4 CalculateProjectionMatrix(float fFOV, float fNear, float fFar);
	glm::mat4 CalculateOrthoMatrix();

	void DeleteFramebuffer();

	int GetWidth();
	int GetHeight();

	CFramebuffer();
private:
	int iWidth, iHeight;
	UINT uiFramebuffer;
	UINT uiDepthRenderbuffer;
	CTexture tFramebufferTex;
	UINT depthTexture;
};
