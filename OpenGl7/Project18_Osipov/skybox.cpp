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

#include "skybox.h"

/*-----------------------------------------------

Name:	LoadSkybox

Params:	paths of skybox pictures

Result:	Loads skybox and creates VAO and VBO for it.

/*---------------------------------------------*/

void CSkybox::LoadSkybox(string a_sDirectory, string a_sFront, string a_sBack, string a_sLeft, string a_sRight, string a_sTop, string a_sBottom)
{
	tTextures[0].LoadTexture2D(a_sDirectory+a_sFront);
	tTextures[1].LoadTexture2D(a_sDirectory+a_sBack);
	tTextures[2].LoadTexture2D(a_sDirectory+a_sLeft);
	tTextures[3].LoadTexture2D(a_sDirectory+a_sRight);
	tTextures[4].LoadTexture2D(a_sDirectory+a_sTop);
	tTextures[5].LoadTexture2D(a_sDirectory+a_sBottom);

	sDirectory = a_sDirectory;

	sFront = a_sFront;
	sBack = a_sBack;
	sLeft = a_sLeft;
	sRight = a_sRight;
	sTop = a_sTop;
	sBottom = a_sBottom;

	FOR(i, 6)
	{
		tTextures[i].SetFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR);
		tTextures[i].SetSamplerParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		tTextures[i].SetSamplerParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glGenVertexArrays(1, &uiVAO);
	glBindVertexArray(uiVAO);

	vboRenderData.CreateVBO();
	vboRenderData.BindVBO();

	glm::vec3 vSkyBoxVertices[24] = 
	{
		// Front face
		glm::vec3(200.0f, 200.0f, 200.0f), glm::vec3(200.0f, -200.0f, 200.0f), glm::vec3(-200.0f, 200.0f, 200.0f), glm::vec3(-200.0f, -200.0f, 200.0f),
		// Back face
		glm::vec3(-200.0f, 200.0f, -200.0f), glm::vec3(-200.0f, -200.0f, -200.0f), glm::vec3(200.0f, 200.0f, -200.0f), glm::vec3(200.0f, -200.0f, -200.0f),
		// Left face
		glm::vec3(-200.0f, 200.0f, 200.0f), glm::vec3(-200.0f, -200.0f, 200.0f), glm::vec3(-200.0f, 200.0f, -200.0f), glm::vec3(-200.0f, -200.0f, -200.0f),
		// Right face
		glm::vec3(200.0f, 200.0f, -200.0f), glm::vec3(200.0f, -200.0f, -200.0f), glm::vec3(200.0f, 200.0f, 200.0f), glm::vec3(200.0f, -200.0f, 200.0f),
		// Top face
		glm::vec3(-200.0f, 200.0f, -200.0f), glm::vec3(200.0f, 200.0f, -200.0f), glm::vec3(-200.0f, 200.0f, 200.0f), glm::vec3(200.0f, 200.0f, 200.0f),
		// Bottom face
		glm::vec3(200.0f, -200.0f, -200.0f), glm::vec3(-200.0f, -200.0f, -200.0f), glm::vec3(200.0f, -200.0f, 200.0f), glm::vec3(-200.0f, -200.0f, 200.0f),
	};
	glm::vec2 vSkyBoxTexCoords[4] =
	{
		glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f)
	};

	glm::vec3 vSkyBoxNormals[6] = 
	{
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};

	FOR(i, 24)
	{
		vboRenderData.AddData(&vSkyBoxVertices[i], sizeof(glm::vec3));
		vboRenderData.AddData(&vSkyBoxTexCoords[i%4], sizeof(glm::vec2));
		vboRenderData.AddData(&vSkyBoxNormals[i/4], sizeof(glm::vec3));
	}

	vboRenderData.UploadDataToGPU(GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3)+sizeof(glm::vec2), 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3)+sizeof(glm::vec2), (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3)+sizeof(glm::vec2), (void*)(sizeof(glm::vec3)+sizeof(glm::vec2)));
}

/*-----------------------------------------------

Name:	RenderSkybox

Params:	none

Result: Guess what it does :)

/*---------------------------------------------*/

void CSkybox::RenderSkybox()
{
	glDepthMask(0);
	glBindVertexArray(uiVAO);
	FOR(i, 6)
	{
		tTextures[i].BindTexture();
		glDrawArrays(GL_TRIANGLE_STRIP, i*4, 4);
	}
	glDepthMask(1);
}

/*-----------------------------------------------

Name:	DeleteSkybox

Params:	none

Result:	Deletes skybox and all associated memory.

/*---------------------------------------------*/

void CSkybox::DeleteSkybox()
{
	FOR(i, 6)tTextures[i].DeleteTexture();
	glDeleteVertexArrays(1, &uiVAO);
	vboRenderData.DeleteVBO();
}