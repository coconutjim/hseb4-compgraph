/*
Осипов Лев Игоревич
Проект 14. OpenGL3
Visual Studio 2013
25.02.2016
Реализовано:
1) в существующих источниках - реализованы свитчеры солнца и текущего точечного источника (клавиши p и l соответственно) 
2) реализованы три новых источника - точечный, прожектор и направленный. включение/отключение - клавиши 1, 2 и 3 соответственно
3) реализовано вращение точечного источника и прожектора. включение/отключение - клавиши 4 и 5 соответственно
4) реализовано динамическое изменение цвета созданного направленного источника. включение - отключение - клавиша 6
5) код закомментирован
*/
#include "common_header.h"

#include "win_OpenGLApp.h"

#include "shaders.h"
#include "texture.h"
#include "vertexBufferObject.h"

#include "flyingCamera.h"

#include "spotLight.h"
#include "dirLight.h"
#include "pointLight.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define NUMTEXTURES 5

/* One VBO, where all static data are stored now,
in this tutorial vertex is stored as 3 floats for
position, 2 floats for texture coordinate and
3 floats for normal vector. */

CVertexBufferObject vboSceneObjects;
UINT uiVAOs[1]; // Only one VAO now

CTexture tTextures[NUMTEXTURES];
CFlyingCamera cCamera;

// Lights
CDirectionalLight dlSun;
CSpotLight slFlashLight;
CPointLight plLight;

CPointLight myPlLight;
CSpotLight mySlLight;
CDirectionalLight myDlLight;

// Flags for rotating lights
bool rotate_Pl = false;
bool rotate_Sl = false;
bool change_Dl = false;

#include "static_geometry.h"

// Initializes OpenGL features that will be used.
// lpParam - Pointer to anything you want.
void InitScene(LPVOID lpParam)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Prepare all scene objects

	vboSceneObjects.CreateVBO();
	glGenVertexArrays(1, uiVAOs); // Create one VAO
	glBindVertexArray(uiVAOs[0]);

	vboSceneObjects.BindVBO();

	AddSceneObjects(vboSceneObjects);

	vboSceneObjects.UploadDataToGPU(GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3)+sizeof(glm::vec2), 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3)+sizeof(glm::vec2), (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3)+sizeof(glm::vec2), (void*)(sizeof(glm::vec3)+sizeof(glm::vec2)));


	if(!PrepareShaderPrograms())
	{
		PostQuitMessage(0);
		return;
	}
	// Load textures

	string sTextureNames[] = {"grass.png", "met_wall01a.jpg", "tower.jpg", "box.jpg", "ground.jpg"};

	FOR(i, NUMTEXTURES)
	{
		tTextures[i].LoadTexture2D("data\\textures\\"+sTextureNames[i], true);
		tTextures[i].SetFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
	}

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	
	cCamera = CFlyingCamera(glm::vec3(0.0f, 10.0f, 120.0f), glm::vec3(0.0f, 10.0f, 119.0f), glm::vec3(0.0f, 1.0f, 0.0f), 25.0f, 0.001f);
	cCamera.SetMovingKeys('W', 'S', 'A', 'D');

	dlSun = CDirectionalLight(glm::vec3(0.13f, 0.13f, 0.13f), glm::vec3(sqrt(2.0f) / 2, -sqrt(2.0f) / 2, 0), 1, 1.0f);
	// Creating spotlight, position and direction will get updated every frame, that's why zero vectors
	slFlashLight = CSpotLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1, 15.0f, 0.017f);
	plLight = CPointLight(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 10.0f, 0.0f), 1, 0.15f, 0.3f, 0.007f, 0.00008f);

	// Creating additional lights
	myPlLight = CPointLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(40.0f, 0.0f, 0.0f), 1, 0.15f, 0.3f, 0.007f, 0.00008f);
	mySlLight = CSpotLight(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-70.0f, 10.0f, 0.0f), glm::normalize(glm::vec3(70.0f, -10.0f, 0.0f)), 1, 15.0f, 0.017f);
	myDlLight = CDirectionalLight(glm::vec3(0.57f, 0.13f, 0.13f), glm::vec3(0, 0, 0), 1, 1.0f);
}

float fGlobalAngle;

// Renders whole scene.
// lpParam - Pointer to anything you want.
void RenderScene(LPVOID lpParam)
{
	// Typecast lpParam to COpenGLControl pointer
	COpenGLControl* oglControl = (COpenGLControl*)lpParam;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	spMain.UseProgram();

	glm::mat4 mModelMatrix, mView;

	// Set spotlight parameters

	glm::vec3 vSpotLightPos = cCamera.vEye;
	glm::vec3 vCameraDir = glm::normalize(cCamera.vView-cCamera.vEye);
	// Move down a little
	vSpotLightPos.y -= 3.2f;
	// Find direction of spotlight
	glm::vec3 vSpotLightDir = (vSpotLightPos+vCameraDir*75.0f)-vSpotLightPos;
	vSpotLightDir = glm::normalize(vSpotLightDir);
	// Find vector of horizontal offset
	glm::vec3 vHorVector = glm::cross(cCamera.vView-cCamera.vEye, cCamera.vUp);
	vSpotLightPos += vHorVector*3.3f;
	// Set it
	slFlashLight.vPosition = vSpotLightPos;
	slFlashLight.vDirection = vSpotLightDir;

	// Rotating lights, if rotate mode is switched on
	if (rotate_Pl) {
		myPlLight.vPosition = glm::vec3(cos(fGlobalAngle + 2000) * 40.0f, 0.0f, sin(fGlobalAngle + 2000) * 40.0f); // point light
	}

	if (rotate_Sl) {
		mySlLight.vPosition = glm::vec3(cos(fGlobalAngle) * 70.0f, 10.0f, sin(fGlobalAngle) * 70.0f); // spot light
		mySlLight.vDirection = glm::normalize(glm::vec3(-cos(fGlobalAngle) * 70.0f, -10.0f, -sin(fGlobalAngle) * 70.0f)); 
	}

	if (change_Dl) {
		myDlLight.vColor = glm::vec3(((float)rand() / (RAND_MAX)), ((float)rand() / (RAND_MAX)), ((float)rand() / (RAND_MAX)));
	}
	
	// Mapping spot lights
	slFlashLight.SetUniformData(&spMain, "spotLight");
	mySlLight.SetUniformData(&spMain, "mySlLight");

	// Mapping point lights
	plLight.SetUniformData(&spMain, "pointLight");
	myPlLight.SetUniformData(&spMain, "myPlLight");

	oglControl->ResizeOpenGLViewportFull();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	spMain.UseProgram();

	spMain.SetUniform("matrices.projMatrix", oglControl->GetProjectionMatrix());
	spMain.SetUniform("gSampler", 0);

	mView = cCamera.Look();
	spMain.SetUniform("matrices.viewMatrix", &mView);

	mModelMatrix = glm::translate(glm::mat4(1.0f), cCamera.vEye);
	
	spMain.SetUniform("matrices.modelMatrix", &mModelMatrix);
	spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mView*mModelMatrix)));

	glBindVertexArray(uiVAOs[0]);

	// Mapping directional lights
	dlSun.SetUniformData(&spMain, "sunLight");
	myDlLight.SetUniformData(&spMain, "myDlLight");

	spMain.SetUniform("vColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	spMain.SetUniform("matrices.modelMatrix", glm::mat4(1.0f));
	spMain.SetUniform("matrices.normalMatrix", glm::mat4(1.0f));

	// Render ground

	tTextures[0].BindTexture();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	// Render cubes
	glm::mat4 mModelToCamera;

	tTextures[3].BindTexture();
	float PI = float(atan(1.0)*4.0);

	FOR(j, 2)
	FOR(i, 16)
	{
		//glm::vec3 vPos = glm::vec3(cos(PI/4 * i) * 30.0f, 4.0f, sin(PI/4*i) * 30.0f);
		glm::vec3 vPos = glm::vec3(30.0f, 4.0f + 8.0f*j, 0.0f);
		mModelMatrix = glm::mat4(1.0f);
		mModelMatrix = glm::rotate(mModelMatrix, PI/8*i + PI/16*j, glm::vec3(0.0f, 1.0f, 0.0f));
		mModelMatrix = glm::translate(mModelMatrix, vPos);
		mModelMatrix = glm::scale(mModelMatrix, glm::vec3(8.0f, 8.0f, 8.0f));
		// We need to transform normals properly, it's done by transpose of inverse matrix of rotations and scales
		spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
		spMain.SetUniform("matrices.modelMatrix", mModelMatrix);
		glDrawArrays(GL_TRIANGLES, 6, 36);
	}

	// render torus
	tTextures[1].BindTexture();
	// Now it's gonna float in the air
	glm::vec3 vPos = glm::vec3(0.0f, 10.0, 0.0f);
	mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
	mModelMatrix = glm::rotate(mModelMatrix, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
	spMain.SetUniform("matrices.modelMatrix", &mModelMatrix);
	glDrawArrays(GL_TRIANGLES, 42, iTorusFaces * 3);

	tTextures[2].BindTexture();
	mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
	mModelMatrix = glm::rotate(mModelMatrix, fGlobalAngle, glm::vec3(1.0f, 0.0f, 0.0f));
	spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
	spMain.SetUniform("matrices.modelMatrix", &mModelMatrix);
	glDrawArrays(GL_TRIANGLES, 42 + iTorusFaces * 3, iTorusFaces2 * 3);


	cCamera.Update();

	// Controlling lights

	if(Keys::Onekey('F'))
		slFlashLight.bOn = 1-slFlashLight.bOn;
	if (Keys::Onekey('P'))
		plLight.bOn = 1 - plLight.bOn;
	if (Keys::Onekey('L'))
		dlSun.bOn = 1 - dlSun.bOn;

	// Switching ligths
	if (Keys::Onekey('1')) // controlling point light
		myPlLight.bOn = 1 - myPlLight.bOn;
	if (Keys::Onekey('2')) // controlling spot light
		mySlLight.bOn = 1 - mySlLight.bOn;
	if (Keys::Onekey('3')) // controlling directional light
		myDlLight.bOn = 1 - myDlLight.bOn;

	// Rotating lights
	if (Keys::Onekey('4')) // controlling point light
		rotate_Pl = !rotate_Pl;
	if (Keys::Onekey('5')) // controlling spot light
		rotate_Sl = !rotate_Sl;
	if (Keys::Onekey('6')) // controlling direct light
		change_Dl = !change_Dl;

	glEnable(GL_DEPTH_TEST);
	if(Keys::Onekey(VK_ESCAPE))PostQuitMessage(0);
	fGlobalAngle += appMain.sof(1.0f);
	oglControl->SwapBuffers();
}

// Releases OpenGL scene.
// lpParam - Pointer to anything you want.
void ReleaseScene(LPVOID lpParam)
{
	FOR(i, NUMTEXTURES)tTextures[i].DeleteTexture();

	spMain.DeleteProgram();
	FOR(i, NUMSHADERS)shShaders[i].DeleteShader();

	glDeleteVertexArrays(1, uiVAOs);
	vboSceneObjects.DeleteVBO();
}