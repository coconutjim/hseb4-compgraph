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
#include "common_header.h"

#include "framebuffer.h"

#include <glm/gtc/matrix_transform.hpp>

CFramebuffer::CFramebuffer()
{
	uiFramebuffer = 0;
	uiDepthRenderbuffer = 0;
}

bool CFramebuffer::CreateFrameBufferForDepthShadow(int a_iWidth, int a_iHeight)
{
	if (uiFramebuffer != 0)
	{
		return false;
	}

	glGenFramebuffers(1, &uiFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, uiFramebuffer);

	tFramebufferTex.CreateDepthTexture(a_iWidth, a_iHeight);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tFramebufferTex.GetTextureID(), 0);

	glDrawBuffers(0, NULL); glReadBuffer(GL_NONE);

	iWidth = a_iWidth;
	iHeight = a_iHeight;

	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

// Creates a framebuffer and a texture to render to.
// a_iWidth - framebuffer width
// a_iHeight - framebuffer height
bool CFramebuffer::CreateFramebufferWithTexture(int a_iWidth, int a_iHeight)
{
	if(uiFramebuffer != 0)return false;

	glGenFramebuffers(1, &uiFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, uiFramebuffer);

	tFramebufferTex.CreateEmptyTexture(a_iWidth, a_iHeight, GL_RGB);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tFramebufferTex.GetTextureID(), 0);

	iWidth = a_iWidth;
	iHeight = a_iHeight;

	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

// 	Adds depth renderbuffer to framebuffer, so rendering can perform depth testing.
bool CFramebuffer::AddDepthBuffer()
{
	if(uiFramebuffer == 0)return false;

	glBindFramebuffer(GL_FRAMEBUFFER, uiFramebuffer);

	glGenRenderbuffers(1, &uiDepthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, uiDepthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, iWidth, iHeight);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, uiDepthRenderbuffer);

	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

// Binds this framebuffer.
// bSetFullViewport - set full framebuffer viewport, default is true
void CFramebuffer::BindFramebuffer(bool bSetFullViewport)
{
	glBindFramebuffer(GL_FRAMEBUFFER, uiFramebuffer);
	if(bSetFullViewport)glViewport(0, 0, iWidth, iHeight);
}

void CFramebuffer::BindFramebufferShadowMap()
{
	glBindFramebuffer(GL_FRAMEBUFFER, uiFramebuffer);
	glViewport(0, 0, 1024, 1024);
}

// Binds framebuffer texture, where renderings are stored.
// iTextureUnit - texture unit to bind to (defaul 0)
// bRegenMipMaps - regenerate mipmaps ? (default false)
void CFramebuffer::BindFramebufferTexture(int iTextureUnit, bool bRegenMipMaps)
{
	tFramebufferTex.BindTexture(iTextureUnit);
	if(bRegenMipMaps)glGenerateMipmap(GL_TEXTURE_2D);
}

// Sets filtering of framebuffer texture, poor texturing here results in greater performance.
void CFramebuffer::SetFramebufferTextureFiltering(int a_tfMagnification, int a_tfMinification)
{
	tFramebufferTex.SetFiltering(a_tfMagnification, a_tfMinification);
	tFramebufferTex.SetWrap();
}

// Deletes framebuffer and frees memory.
void CFramebuffer::DeleteFramebuffer()
{
	if(uiFramebuffer)
	{
		glDeleteFramebuffers(1, &uiFramebuffer);
		uiFramebuffer = 0;
	}
	if(uiDepthRenderbuffer)
	{
		glDeleteRenderbuffers(1, &uiDepthRenderbuffer);
		uiDepthRenderbuffer = 0;
	}
	tFramebufferTex.DeleteTexture();
}

// Calculates projection matrix.
// fFOV - field of view angle
// fNear, fFar - distance of near and far clipping plane
glm::mat4 CFramebuffer::CalculateProjectionMatrix(float fFOV, float fNear, float fFar)
{
	return glm::perspective(fFOV, float(iWidth)/float(iHeight), fNear, fFar);
}

// Calculates ortho 2D projection matrix.
glm::mat4 CFramebuffer::CalculateOrthoMatrix()
{
	return glm::ortho(0.0f, float(iWidth), 0.0f, float(iHeight));
}

int CFramebuffer::GetWidth()
{
	return iWidth;
}

int CFramebuffer::GetHeight()
{
	return iHeight;
}