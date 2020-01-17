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
#include "common_header.h"

#include "particle_system_tf.h"

CParticleSystemTransformFeedback::CParticleSystemTransformFeedback()
{
	bInitialized = false;
	iCurReadBuffer = 0;
}

/*-----------------------------------------------

Name:	InitalizeParticleSystem

Params:	none

Result:	Initializes all buffers and data on GPU
		for transform feedback particle system.

/*---------------------------------------------*/

bool CParticleSystemTransformFeedback::InitalizeParticleSystem()
{
	if(bInitialized)return false;

	const char* sVaryings[NUM_PARTICLE_ATTRIBUTES] = 
	{
		"vPositionOut",
		"vVelocityOut",
		"vColorOut",
		"fLifeTimeOut",
		"fSizeOut",
		"iTypeOut",
	};

	// Updating program

	shVertexUpdate.LoadShader("data\\shaders\\particles_update.vert", GL_VERTEX_SHADER);
	shGeomUpdate.LoadShader("data\\shaders\\particles_update.geom", GL_GEOMETRY_SHADER);

	spUpdateParticles.CreateProgram();
	spUpdateParticles.AddShaderToProgram(&shVertexUpdate);
	spUpdateParticles.AddShaderToProgram(&shGeomUpdate);
	FOR(i, NUM_PARTICLE_ATTRIBUTES)glTransformFeedbackVaryings(spUpdateParticles.GetProgramID(), 6, sVaryings, GL_INTERLEAVED_ATTRIBS);
	spUpdateParticles.LinkProgram();


	// Rendering program

	shVertexRender.LoadShader("data\\shaders\\particles_render.vert", GL_VERTEX_SHADER);
	shGeomRender.LoadShader("data\\shaders\\particles_render.geom", GL_GEOMETRY_SHADER);
	shFragRender.LoadShader("data\\shaders\\particles_render.frag", GL_FRAGMENT_SHADER);
	
	spRenderParticles.CreateProgram();

	spRenderParticles.AddShaderToProgram(&shVertexRender);
	spRenderParticles.AddShaderToProgram(&shGeomRender);
	spRenderParticles.AddShaderToProgram(&shFragRender);

	spRenderParticles.LinkProgram();

	glGenTransformFeedbacks(1, &uiTransformFeedbackBuffer);
	glGenQueries(1, &uiQuery);

	glGenBuffers(2, uiParticleBuffer);
	glGenVertexArrays(2, uiVAO);

	CParticle partInitialization;
	partInitialization.iType = PARTICLE_TYPE_GENERATOR;

	FOR(i, 2)
	{	
		glBindVertexArray(uiVAO[i]);
		glBindBuffer(GL_ARRAY_BUFFER, uiParticleBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CParticle)*MAX_PARTICLES_ON_SCENE, NULL, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(CParticle), &partInitialization);

		FOR(i, NUM_PARTICLE_ATTRIBUTES)glEnableVertexAttribArray(i);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)0); // Position
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)12); // Velocity
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)24); // Color
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)36); // Lifetime
		glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(CParticle), (const GLvoid*)40); // Size
		glVertexAttribPointer(5, 1, GL_INT,	  GL_FALSE, sizeof(CParticle), (const GLvoid*)44); // Type
	}
	iCurReadBuffer = 0;
	iNumParticles = 1;

	bInitialized = true;

	return true;
}

/*-----------------------------------------------

Name:	UpdateParticles

Params:	fTimePassed - time passed since last frame

Result:	Performs particle updating on GPU.

/*---------------------------------------------*/

float grandf(float fMin, float fAdd)
{
	float fRandom = float(rand()%(RAND_MAX+1))/float(RAND_MAX);
	return fMin+fAdd*fRandom;
}

void CParticleSystemTransformFeedback::UpdateParticles(float fTimePassed)
{
	if(!bInitialized)return;

	spUpdateParticles.UseProgram();

	glm::vec3 vUpload;
	spUpdateParticles.SetUniform("fTimePassed",			fTimePassed);
	spUpdateParticles.SetUniform("vGenPosition",		vGenPosition);
	spUpdateParticles.SetUniform("vGenVelocityMin",		vGenVelocityMin);
	spUpdateParticles.SetUniform("vGenVelocityRange",	vGenVelocityRange);
	spUpdateParticles.SetUniform("vGenColor",			vGenColor);
	spUpdateParticles.SetUniform("vGenGravityVector",	vGenGravityVector);

	spUpdateParticles.SetUniform("fGenLifeMin",			fGenLifeMin);
	spUpdateParticles.SetUniform("fGenLifeRange",		fGenLifeRange);

	spUpdateParticles.SetUniform("fGenSize",			fGenSize);
	spUpdateParticles.SetUniform("iNumToGenerate",			0);

	fElapsedTime += fTimePassed;

	if(fElapsedTime > fNextGenerationTime)
	{
		spUpdateParticles.SetUniform("iNumToGenerate", iNumToGenerate);
		fElapsedTime -= fNextGenerationTime;

		glm::vec3 vRandomSeed = glm::vec3(grandf(-10.0f, 20.0f), grandf(-10.0f, 20.0f), grandf(-10.0f, 20.0f));
		spUpdateParticles.SetUniform("vRandomSeed", &vRandomSeed);
	}

	glEnable(GL_RASTERIZER_DISCARD);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, uiTransformFeedbackBuffer);

	glBindVertexArray(uiVAO[iCurReadBuffer]);
	glEnableVertexAttribArray(1); // Re-enable velocity

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, uiParticleBuffer[1-iCurReadBuffer]);

	glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, uiQuery);
	glBeginTransformFeedback(GL_POINTS);

	glDrawArrays(GL_POINTS, 0, iNumParticles);

	glEndTransformFeedback();

	glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	glGetQueryObjectiv(uiQuery, GL_QUERY_RESULT, &iNumParticles);

	iCurReadBuffer = 1-iCurReadBuffer;

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}

/*-----------------------------------------------

Name:	RenderParticles

Params:	none

Result:	Performs particle rendering on GPU.

/*---------------------------------------------*/

void CParticleSystemTransformFeedback::RenderParticles()
{
	if(!bInitialized)return;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(0);

	glDisable(GL_RASTERIZER_DISCARD);
	spRenderParticles.UseProgram();
	spRenderParticles.SetUniform("matrices.mProj", &matProjection);
	spRenderParticles.SetUniform("matrices.mView", &matView);
	spRenderParticles.SetUniform("vQuad1", &vQuad1);
	spRenderParticles.SetUniform("vQuad2", &vQuad2);
	spRenderParticles.SetUniform("gSampler", 0);

	glBindVertexArray(uiVAO[iCurReadBuffer]);
	glDisableVertexAttribArray(1); // Disable velocity, because we don't need it for rendering

	glDrawArrays(GL_POINTS, 0, iNumParticles);

	glDepthMask(1);	
	glDisable(GL_BLEND);
}

/*-----------------------------------------------

Name:	SetMatrices

Params:	a_matProjection - projection matrix
		vEye, vView, vUpVector - definition of view matrix

Result:	Sets the projection matrix and view matrix,
		that shaders of transform feedback particle system
		need.

/*---------------------------------------------*/

void CParticleSystemTransformFeedback::SetMatrices(glm::mat4* a_matProjection, glm::vec3 vEye, glm::vec3 vView, glm::vec3 vUpVector)
{
	matProjection = *a_matProjection;

	matView = glm::lookAt(vEye, vView, vUpVector);
	vView = vView-vEye;
	vView = glm::normalize(vView);
	vQuad1 = glm::cross(vView, vUpVector);
	vQuad1 = glm::normalize(vQuad1);
	vQuad2 = glm::cross(vView, vQuad1);
	vQuad2 = glm::normalize(vQuad2);
}

/*-----------------------------------------------

Name:	SetGeneratorProperties

Params:	many properties of particle generation

Result:	Guess what it does :)

/*---------------------------------------------*/

void CParticleSystemTransformFeedback::SetGeneratorProperties(glm::vec3 a_vGenPosition, glm::vec3 a_vGenVelocityMin, glm::vec3 a_vGenVelocityMax, glm::vec3 a_vGenGravityVector, glm::vec3 a_vGenColor, float a_fGenLifeMin, float a_fGenLifeMax, float a_fGenSize, float fEvery, int a_iNumToGenerate)
{
	vGenPosition = a_vGenPosition;
	vGenVelocityMin = a_vGenVelocityMin;
	vGenVelocityRange = a_vGenVelocityMax - a_vGenVelocityMin;

	vGenGravityVector = a_vGenGravityVector;
	vGenColor = a_vGenColor;
	fGenSize = a_fGenSize;

	fGenLifeMin = a_fGenLifeMin;
	fGenLifeRange = a_fGenLifeMax - a_fGenLifeMin;

	fNextGenerationTime = fEvery;
	fElapsedTime = 0.8f;

	iNumToGenerate = a_iNumToGenerate;
}

/*-----------------------------------------------

Name:	GetNumParticles

Params:	none

Result:	Retrieves current number of particles.

/*---------------------------------------------*/

int CParticleSystemTransformFeedback::GetNumParticles()
{
	return iNumParticles;
}

void CParticleSystemTransformFeedback::incVelocity() {
	vGenVelocityMin += glm::vec3(0.0f, 1.0f, 0.0f);
	if (vGenVelocityMin[1] + vGenVelocityRange[1] > 70.0f) {
		vGenVelocityMin[1] = 50.0f;
	}

}
void CParticleSystemTransformFeedback::decVelocity() {
	vGenVelocityMin += glm::vec3(0.0f, -1.0f, 0.0f);
	if (vGenVelocityMin[1] < 1.0f) {
		vGenVelocityMin[1] = 1.0f;
	}
}
void CParticleSystemTransformFeedback::incRed() {
	vGenColor += glm::vec3(0.1f, 0.0f, 0.0f);
	if (vGenColor[0] > 1.0f) {
		vGenColor[0] = 1.0f;
	}
}
void CParticleSystemTransformFeedback::decRed() {
	vGenColor += glm::vec3(-0.1f, 0.0f, 0.0f);
	if (vGenColor[0] < 0.0f) {
		vGenColor[0] = 0.0f;
	}
}
void CParticleSystemTransformFeedback::incGreen() {
	vGenColor += glm::vec3(0.0f, 0.1f, 0.0f);
	if (vGenColor[1] > 1.0f) {
		vGenColor[1] = 1.0f;
	}
}
void CParticleSystemTransformFeedback::decGreen() {
	vGenColor += glm::vec3(0.0f, -0.1f, 0.0f);
	if (vGenColor[1] < 0.0f) {
		vGenColor[1] = 0.0f;
	}
}
void CParticleSystemTransformFeedback::incBlue() {
	vGenColor += glm::vec3(0.0f, 0.0f, 0.1f);
	if (vGenColor[2] > 1.0f) {
		vGenColor[2] = 1.0f;
	}
}
void CParticleSystemTransformFeedback::decBlue() {
	vGenColor += glm::vec3(0.0f, 0.0f, -0.1f);
	if (vGenColor[2] < 0.0f) {
		vGenColor[2] = 0.0f;
	}
}
void CParticleSystemTransformFeedback::incGenLife() {
	fGenLifeMin += 0.5f;
	if (fGenLifeMin + fGenLifeRange > 15.0f) {
		fGenLifeMin = 13.5f;
	}
}
void CParticleSystemTransformFeedback::decGenLife() {
	fGenLifeMin -= 0.5f;
	if (fGenLifeMin < 0.5f) {
		fGenLifeMin = 0.5f;
	}
}
void CParticleSystemTransformFeedback::incSize() {
	fGenSize += 0.1;
	if (fGenSize > 3.0f) {
		fGenSize = 3.0f;
	}
}
void CParticleSystemTransformFeedback::decSize() {
	fGenSize -= 0.1f;
	if (fGenSize < 0.01f) {
		fGenSize = 0.01f;
	}
}
void CParticleSystemTransformFeedback::incSpawnTime() {
	fNextGenerationTime += 0.05f;
	if (fNextGenerationTime > 3.0f) {
		fNextGenerationTime = 3.0f;
	}
}
void CParticleSystemTransformFeedback::decSpawnTime() {
	fNextGenerationTime -= 0.05f;
	if (fNextGenerationTime < 0.05f) {
		fNextGenerationTime = 0.05f;
	}
}
void CParticleSystemTransformFeedback::incCount() {
	iNumToGenerate += 3;
	if (iNumToGenerate > 1000) {
		iNumToGenerate = 1000;
	}
}
void CParticleSystemTransformFeedback::decCount() {
	iNumToGenerate -= 3;
	if (iNumToGenerate < 1) {
		iNumToGenerate = 1;
	}
}

// Getters

float CParticleSystemTransformFeedback::getMinVelocity() {
	return vGenVelocityMin[1];
}
float CParticleSystemTransformFeedback::getMaxVelocity() {
	return vGenVelocityMin[1] + vGenVelocityRange[1];
}
float CParticleSystemTransformFeedback::getRed() {
	return vGenColor[0];
}
float CParticleSystemTransformFeedback::getGreen() {
	return vGenColor[1];
}
float CParticleSystemTransformFeedback::getBlue() {
	return vGenColor[2];
}
float CParticleSystemTransformFeedback::getGenLifeMin() {
	return fGenLifeMin;
}
float CParticleSystemTransformFeedback::getGenLifeMax() {
	return fGenLifeMin + fGenLifeRange;
}
float CParticleSystemTransformFeedback::getSize() {
	return fGenSize;
}
float CParticleSystemTransformFeedback::getSpawnTime() {
	return fNextGenerationTime;
}
float CParticleSystemTransformFeedback::getCount() {
	return iNumToGenerate;
}