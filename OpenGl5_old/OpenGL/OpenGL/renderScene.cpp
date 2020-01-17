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
#include "common_header.h"

#include "win_OpenGLApp.h"

#include "shaders.h"
#include "texture.h"
#include "vertexBufferObject.h"

#include "flyingCamera.h"

#include "skybox.h"

#include "spotLight.h"
#include "dirLight.h"
#include "pointLight.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "objModel.h"

#define NUMTEXTURES 13

/* One VBO, where all static data are stored now,
in this tutorial vertex is stored as 3 floats for
position, 2 floats for texture coordinate and
3 floats for normal vector. */

CVertexBufferObject vboSceneObjects, vboCubeInd, vboCube;
UINT uiVAOs[2]; // Only one VAO now

CTexture tTextures[NUMTEXTURES];
CFlyingCamera cCamera;

CSkybox sbMainSkybox;

CDirectionalLight dlSun;

CSpotLight slMySlLight;
CDirectionalLight dfMyDlLight;
CPointLight plMyPlLight;
CObjModel mdlHouse;
// Custom models
CObjModel mdlDeadpool;
CObjModel mdlDeadpool1;


#include "static_geometry.h"


// Initializes OpenGL features that will be used.
// lpParam - Pointer to anything you want.
void InitScene(LPVOID lpParam)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Prepare all scene objects

	vboSceneObjects.CreateVBO();
	glGenVertexArrays(2, uiVAOs); // Create one VAO
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

	glBindVertexArray(uiVAOs[1]);

	vboCube.CreateVBO();

	vboCube.BindVBO();
	AddCube(vboCube);
	vboCube.UploadDataToGPU(GL_STATIC_DRAW);

	vboCubeInd.CreateVBO();
	// Bind indices
	vboCubeInd.BindVBO(GL_ELEMENT_ARRAY_BUFFER);
	vboCubeInd.AddData(&iCubeindices, sizeof(iCubeindices));
	vboCubeInd.UploadDataToGPU(GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

	if(!PrepareShaderPrograms())
	{
		PostQuitMessage(0);
		return;
	}
	// Load textures

	string sTextureNames[] = {"grass.png",
		"cube1.jpg", "cube2.jpg", "cube3.jpg", "cube4.jpg", 
		"cube5.jpg", "cube6.jpg", "cube7.jpg", "cube8.jpg",
		"cube9.jpg", "cube10.jpg", "cube11.jpg", "cube12.jpg" };

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

	// Loading custom skybox
	sbMainSkybox.LoadSkybox("data\\skyboxes\\sor_hills\\", "hills_ft.jpg", "hills_bk.jpg", "hills_lf.jpg", "hills_rt.jpg", "hills_up.jpg", "hills_dn.jpg");

	dlSun = CDirectionalLight(glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(sqrt(2.0f) / 2, -sqrt(2.0f) / 2, 0), 1.0f);
	
	// Loading custom lights
	dfMyDlLight = CDirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(sqrt(2.0f) / 2, -sqrt(2.0f) / 2, -sqrt(2.0f) / 2), 0.2f);
	slMySlLight = CSpotLight(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-50.0f, 15.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1, 30.0f, 0.017f);
	plMyPlLight = CPointLight(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-50.0f, 15.0f, 0.0f), 0.15f, 0.3f, 0.007f, 0.00008f);

	// Loading custom models
	mdlHouse.LoadModel("data\\models\\house\\house.obj", "house.mtl");
	mdlDeadpool.LoadModel("data\\models\\deadpool\\deadpool.obj", "deadpool.mtl");
	mdlDeadpool1.LoadModel("data\\models\\deadpool\\deadpool.obj", "deadpool1.mtl");
}

float fGlobalAngle;
float fTextureContribution = 0.5f;
bool fTCDecrease; // to decide increade or decrease it
bool fTCManual; // Manual texture management
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

	glm::vec3 vCameraDir = glm::normalize(cCamera.vView-cCamera.vEye);

	oglControl->ResizeOpenGLViewportFull();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	spMain.UseProgram();
	slMySlLight.SetUniformData(&spMain, "streetLight");
	dfMyDlLight.SetUniformData(&spMain, "sideLight");

	plMyPlLight.SetUniformData(&spMain, "myPointLight");

	spMain.SetUniform("matrices.projMatrix", oglControl->GetProjectionMatrix());
	spMain.SetUniform("gSamplers[0]", 0);
	spMain.SetUniform("gSamplers[1]", 1);
	spMain.SetUniform("fTextureContributions[0]", 1.0f);
	spMain.SetUniform("fTextureContributions[1]", fTextureContribution);
	spMain.SetUniform("numTextures", 1);
	


	mView = cCamera.Look();
	spMain.SetUniform("matrices.viewMatrix", &mView);

	mModelMatrix = glm::translate(glm::mat4(1.0f), cCamera.vEye);
	
	spMain.SetUniform("matrices.modelMatrix", &mModelMatrix);
	spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mView*mModelMatrix)));

	CDirectionalLight dlSun2 = dlSun;

	// We set full ambient for skybox, so that its color isn't affected by directional light

	dlSun2.fAmbient = 1.0f;
	dlSun2.vColor = glm::vec3(1.0f, 1.0f, 1.0f);
	dlSun2.SetUniformData(&spMain, "sunLight");

	// Rendering skybox

	sbMainSkybox.RenderSkybox();
	glBindVertexArray(uiVAOs[1]);
	glEnable(GL_DEPTH_TEST);

	float PI = float(atan(1.0)*4.0);

	// Render cube

	glm::mat4 mModelToCamera;

	// Changing contribution
	if (!fTCManual) {
		if (fTCDecrease) {
			fTextureContribution -= 0.001f;
			if (fTextureContribution < 0.0f) {
				fTextureContribution = 0.0f;
				fTCDecrease = false;
			}
		}
		else {
			fTextureContribution += 0.001f;
			if (fTextureContribution > 1.0f) {
				fTextureContribution = 1.0f;
				fTCDecrease = true;
			}
		}
	}

	FOR(i, 6) {

		tTextures[i * 2 + 1].BindTexture();
		tTextures[i * 2 + 2].BindTexture(1);

		spMain.SetUniform("fTextureContributions[0]", 1.0f - fTextureContribution);
		spMain.SetUniform("numTextures", 2);

		glEnable(GL_CULL_FACE);
		//glFrontFace(GL_CCW); //Done by default
		glm::vec3 vPos2 = glm::vec3(0.0f, 30.0f, 50.0f);
		mModelMatrix = glm::mat4(1.0f);
		mModelMatrix = glm::translate(mModelMatrix, vPos2);
		mModelMatrix = glm::scale(mModelMatrix, glm::vec3(20.0f, 20.0f, 20.0f));
		// We need to transform normals properly, it's done by transpose of inverse matrix of rotations and scales
		spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
		spMain.SetUniform("matrices.modelMatrix", mModelMatrix);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i * 6 * sizeof(GLuint))); // one cube face
		glDisable(GL_CULL_FACE);

	}

	spMain.SetUniform("fTextureContributions[0]", 1.0f);
	spMain.SetUniform("numTextures", 1);

	glBindVertexArray(uiVAOs[0]);

	dlSun.SetUniformData(&spMain, "sunLight");

	spMain.SetUniform("vColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	spMain.SetUniform("matrices.modelMatrix", glm::mat4(1.0f));
	spMain.SetUniform("matrices.normalMatrix", glm::mat4(1.0f));

	// Render ground

	tTextures[0].BindTexture();
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Render house

	glm::vec3 vPos = glm::vec3(-50.0f, 0.0f, 50.0f);
	mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
	mModelMatrix = glm::scale(mModelMatrix, glm::vec3(8.0f, 8.0, 8.0f));
	spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
	spMain.SetUniform("matrices.modelMatrix", &mModelMatrix);
	mdlHouse.RenderModel();

	// Render Deadpools

	vPos = glm::vec3(40.0f, 0.0f, 50.0f);
	mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
	mModelMatrix = glm::rotate(mModelMatrix, -PI / 2, glm::vec3(0.0f, 1.0f, 0.0f));
	mModelMatrix = glm::scale(mModelMatrix, glm::vec3(1.0f, 1.0, 1.0f));
	spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
	spMain.SetUniform("matrices.modelMatrix", &mModelMatrix);
	mdlDeadpool.RenderModel();

	vPos = glm::vec3(110.0f, 0.0f, 50.0f);
	mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
	mModelMatrix = glm::rotate(mModelMatrix, -PI / 2, glm::vec3(0.0f, 1.0f, 0.0f));
	mModelMatrix = glm::scale(mModelMatrix, glm::vec3(1.0f, 1.0, 1.0f));
	spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
	spMain.SetUniform("matrices.modelMatrix", &mModelMatrix);
	mdlDeadpool1.RenderModel();

	cCamera.Update();

	if (Keys::Onekey('F')) fTCManual = !fTCManual;

	if (fTCManual) {
		if (Keys::Key('Q')) fTextureContribution += appMain.sof(-0.2f);
		if (Keys::Key('E')) fTextureContribution += appMain.sof(0.2f);
		fTextureContribution = min(max(0.0f, fTextureContribution), 1.0f);
	}

	if(Keys::Onekey(VK_ESCAPE))PostQuitMessage(0);
	fGlobalAngle += appMain.sof(1.0f);
	oglControl->SwapBuffers();
}

// Releases OpenGL scene.
// lpParam - Pointer to anything you want.
void ReleaseScene(LPVOID lpParam)
{
	FOR(i, NUMTEXTURES)tTextures[i].DeleteTexture();
	sbMainSkybox.DeleteSkybox();
	spMain.DeleteProgram();
	FOR(i, NUMSHADERS)shShaders[i].DeleteShader();

	glDeleteVertexArrays(2, uiVAOs);
	vboSceneObjects.DeleteVBO();
	vboCubeInd.DeleteVBO();
	vboCube.DeleteVBO();
}