/*
������ ��� ��������
������ 17. OpenGL6
Visual Studio 2013
20.03.2016
�������:
1) ��������� 4 ������� (� ����������� ���� � ���)
2) ��������� ����������� ���������/���������� ������������� ��������� ����� (������� �)
3) ��������� 3 ����� �������� ��������� �����
4) ����������� ���������/���������� �������� ���������� - ������� 1, 2 � 3 ��������������
5) ��� ���������������
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
