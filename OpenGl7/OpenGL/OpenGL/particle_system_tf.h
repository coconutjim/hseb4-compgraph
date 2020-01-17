/*
Осипов Лев Игоревич
Проект 18. OpenGL7
Visual Studio 2013
20.03.2016
Сделано:
1) на сцену добавлены объекты - дом, сундук и 3 Дедпула
2) у всех объектов можно посмотреть нормали
3) кроме существующей системы частиц, добавлено еще 3 дополнительных системы (под Дедпулами). Они имеют разные параметры,
средняя имитирует пламя
4) параметры существующей системы частиц выводятся на сцену и изменяются с помощью клавиш (клавиши управления см. на сцене)
5) можно изменить скорость вращения объекта (клавиши управления см. на сцене)
6) вся информация об управлении и об авторе программе вынесена на сцену
7) код закомментирован
*/
#pragma once

#include "shaders.h"

#define NUM_PARTICLE_ATTRIBUTES 6
#define MAX_PARTICLES_ON_SCENE 100000

#define PARTICLE_TYPE_GENERATOR 0
#define PARTICLE_TYPE_NORMAL 1

/*****************************************************

Class:		CParticle

Purpose:	Encapsulates particle and its properties.

*****************************************************/

class CParticle
{
public:
	glm::vec3 vPosition;
	glm::vec3 vVelocity;
	glm::vec3 vColor;
	float fLifeTime;
	float fSize;
	int iType;
};

/**********************************************************************

Class:		CParticleSystemTransformFeedback

Purpose:	Particle system class that uses transform feedback feature.

***********************************************************************/

class CParticleSystemTransformFeedback
{
public:
	bool InitalizeParticleSystem();

	void RenderParticles();
	void UpdateParticles(float fTimePassed);

	void SetGeneratorProperties(glm::vec3 a_vGenPosition, glm::vec3 a_vGenVelocityMin, glm::vec3 a_vGenVelocityMax, glm::vec3 a_vGenGravityVector, glm::vec3 a_vGenColor, float a_fGenLifeMin, float a_fGenLifeMax, float a_fGenSize, float fEvery, int a_iNumToGenerate);

	void ClearAllParticles();
	bool ReleaseParticleSystem();

	int GetNumParticles();

	void SetMatrices(glm::mat4* a_matProjection, glm::vec3 vEye, glm::vec3 vView, glm::vec3 vUpVector);

	CParticleSystemTransformFeedback();

	// For transformations
	void incVelocity();
	void decVelocity();
	void incRed();
	void decRed();
	void incBlue();
	void decBlue();
	void incGreen();
	void decGreen();
	void incGenLife();
	void decGenLife();
	void incSize();
	void decSize();
	void incSpawnTime();
	void decSpawnTime();
	void incCount();
	void decCount();

	// Getters
	float getMinVelocity();
	float getMaxVelocity();
	float getRed();
	float getGreen();
	float getBlue();
	float getGenLifeMin();
	float getGenLifeMax();
	float getSize();
	float getSpawnTime();
	float getCount();

private:
	bool bInitialized;
	
	UINT uiTransformFeedbackBuffer;

	UINT uiParticleBuffer[2];
	UINT uiVAO[2];

	UINT uiQuery;
	UINT uiTexture;

	int iCurReadBuffer;
	int iNumParticles;

	glm::mat4 matProjection, matView;
	glm::vec3 vQuad1, vQuad2;

	float fElapsedTime;
	float fNextGenerationTime;

	glm::vec3 vGenPosition;
	glm::vec3 vGenVelocityMin, vGenVelocityRange;
	glm::vec3 vGenGravityVector;
	glm::vec3 vGenColor;

	float fGenLifeMin, fGenLifeRange;
	float fGenSize;

	int iNumToGenerate;

	CShader shVertexRender, shGeomRender, shFragRender;
	CShader shVertexUpdate, shGeomUpdate, shFragUpdate;
	CShaderProgram spRenderParticles;
	CShaderProgram spUpdateParticles;
};