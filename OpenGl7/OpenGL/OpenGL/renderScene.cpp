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

#include "win_OpenGLApp.h"

#include "shaders.h"
#include "texture.h"
#include "vertexBufferObject.h"

#include "flyingCamera.h"

#include "freeTypeFont.h"

#include "skybox.h"
#include "dirLight.h"
#include "material.h"

#include "assimp_model.h"

#include "heightmap.h"

#include "static_geometry.h"

#include "particle_system_tf.h"

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}



CVertexBufferObject vboSceneObjects;
UINT uiVAOSceneObjects;

CFreeTypeFont ftFont;

CSkybox sbMainSkybox;
CFlyingCamera cCamera;

CDirectionalLight dlSun;

CMaterial matShiny;
CAssimpModel amModels[6];

CMultiLayeredHeightmap hmWorld;

int iTorusFaces;

bool bDisplayNormals = false; // Do not display normals by default

CParticleSystemTransformFeedback psMainParticleSystem;

// Particle systems for Deadpools
CParticleSystemTransformFeedback psDP1;
CParticleSystemTransformFeedback psDP2;
CParticleSystemTransformFeedback psDP3;

/*-----------------------------------------------

Name:    InitScene

Params:  lpParam - Pointer to anything you want.

Result:  Initializes OpenGL features that will
         be used.

/*---------------------------------------------*/

void InitScene(LPVOID lpParam)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	if(!PrepareShaderPrograms())
	{
		PostQuitMessage(0);
		return;
	}
	
	LoadAllTextures();

	vboSceneObjects.CreateVBO();
	glGenVertexArrays(1, &uiVAOSceneObjects); // Create one VAO
	glBindVertexArray(uiVAOSceneObjects);

	vboSceneObjects.BindVBO();

	iTorusFaces = GenerateTorus(vboSceneObjects, 7.0f, 2.0f, 20, 20);
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


	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	// Here we load font with pixel size 32 - this means that if we print with size above 32, the quality will be low
	ftFont.LoadSystemFont("arial.ttf", 32);
	ftFont.SetShaderProgram(&spFont2D);
	
	cCamera = CFlyingCamera(glm::vec3(0.0f, 30.0f, 100.0f), glm::vec3(0.0f, 30.0f, 99.0f), glm::vec3(0.0f, 1.0f, 0.0f), 25.0f, 0.1f);
	cCamera.SetMovingKeys('W', 'S', 'A', 'D');

	sbMainSkybox.LoadSkybox("data\\skyboxes\\bluefreeze\\", "bluefreeze_front.jpg", "bluefreeze_back.jpg", "bluefreeze_right.jpg", "bluefreeze_left.jpg", "bluefreeze_top.jpg", "bluefreeze_top.jpg");

	dlSun = CDirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(sqrt(2.0f)/2, -sqrt(2.0f)/2, 0), 0.5f, 0);

	amModels[0].LoadModelFromFile("data\\models\\house\\house.3ds");
	amModels[1].LoadModelFromFile("data\\models\\treasure_chest_obj\\treasure_chest.obj");
	amModels[2].LoadModelFromFile("data\\models\\deadpool\\deadpool.obj");
	amModels[3].LoadModelFromFile("data\\models\\deadpool\\deadpool.obj");
	amModels[4].LoadModelFromFile("data\\models\\deadpool\\deadpool.obj");
	amModels[5].LoadModelFromFile("data\\models\\deadpool\\deadpool.obj");
	
	CAssimpModel::FinalizeVBO();
	CMultiLayeredHeightmap::LoadTerrainShaderProgram();
	hmWorld.LoadHeightMapFromImage("data\\worlds\\world_like_in_21th.bmp");

	matShiny = CMaterial(1.0f, 32.0f);

	psMainParticleSystem.InitalizeParticleSystem();

	psMainParticleSystem.SetGeneratorProperties(
		glm::vec3(-10.0f, 17.5f, 0.0f), // Where the particles are generated
		glm::vec3(-5, 0, -5), // Minimal velocity
		glm::vec3(5, 20, 5), // Maximal velocity
		glm::vec3(0, -5, 0), // Gravity force applied to particles
		glm::vec3(0.0f, 0.5f, 1.0f), // Color (light blue)
		1.5f, // Minimum lifetime in seconds
		3.0f, // Maximum lifetime in seconds
		0.8f, // Rendered size
		0.02f, // Spawn every 0.02 seconds
		30); // And spawn 30 particles


	// Initilizae particle systems for Deadpools

	psDP1.InitalizeParticleSystem();
	psDP1.SetGeneratorProperties(
		glm::vec3(-60.0f, 35.0f, -30.0f), 
		glm::vec3(-5, 40, -5), 
		glm::vec3(5, 50, 5), 
		glm::vec3(0, -5, 0), 
		glm::vec3(0.0f, 1.0f, 0.0f), 
		4.5f, 7.0f, 0.75f, 0.02f, 30); 

	psDP2.InitalizeParticleSystem();
	psDP2.SetGeneratorProperties(
		glm::vec3(-80.0f, 35.0f, -30.0f), 
		glm::vec3(-5, 80, -5), 
		glm::vec3(5, 90, 5), 
		glm::vec3(0, -5, 0), 
		glm::vec3(1.0f, 0.5f, 0.0f), 
		0.1f, 0.2f, 4.75f, 0.02f, 30); 

	psDP3.InitalizeParticleSystem();
	psDP3.SetGeneratorProperties(
		glm::vec3(-100.0f, 35.0f, -30.0f), 
		glm::vec3(-5, 0, -5), 
		glm::vec3(5, 20, 5), 
		glm::vec3(0, -5, 0), 
		glm::vec3(1.0f, 0.0f, 0.0f),
		1.5f, 3.0f, 0.1f, 0.02f, 30); 
}

/*-----------------------------------------------

Name:    RenderScene

Params:  lpParam - Pointer to anything you want.

Result:  Renders whole scene.

/*---------------------------------------------*/

float rotationSpeed = 50.0f;

void RenderScene(LPVOID lpParam)
{
	// Typecast lpParam to COpenGLControl pointer
	COpenGLControl* oglControl = (COpenGLControl*)lpParam;
	oglControl->ResizeOpenGLViewportFull();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	spMain.UseProgram();

	spMain.SetUniform("matrices.projMatrix", oglControl->GetProjectionMatrix());
	spMain.SetUniform("matrices.viewMatrix", cCamera.Look());

	spMain.SetUniform("gSampler", 0);

	spMain.SetUniform("matrices.modelMatrix", glm::mat4(1.0));
	spMain.SetUniform("matrices.normalMatrix", glm::mat4(1.0));
	spMain.SetUniform("vColor", glm::vec4(1, 1, 1, 1));

	// This values will set the darkness of whole scene, that's why such name of variable :D
	static float fAngleOfDarkness = 45.0f;
	// You can play with direction of light with '+' and '-' key
	if(Keys::Key(VK_ADD))fAngleOfDarkness += appMain.sof(90);
	if(Keys::Key(VK_SUBTRACT))fAngleOfDarkness -= appMain.sof(90);
	// Set the directional vector of light
	dlSun.vDirection = glm::vec3(-sin(fAngleOfDarkness*3.1415f/180.0f), -cos(fAngleOfDarkness*3.1415f/180.0f), 0.0f);
	
	dlSun.iSkybox = 1;
	dlSun.SetUniformData(&spMain, "sunLight");

	spMain.SetUniform("matrices.modelMatrix", glm::translate(glm::mat4(1.0), cCamera.vEye));
	sbMainSkybox.RenderSkybox();

	dlSun.iSkybox = 0;
	dlSun.SetUniformData(&spMain, "sunLight");

	spMain.SetUniform("matrices.modelMatrix", glm::mat4(1.0));

	spMain.SetUniform("vEyePosition", cCamera.vEye);
	matShiny.SetUniformData(&spMain, "matActive");
	
	// Render a house

	CAssimpModel::BindModelsVAO();

	glm::mat4 mModel = glm::translate(glm::mat4(1.0), glm::vec3(40.0f, 17.0f, 0));
	mModel = glm::scale(mModel, glm::vec3(8, 8, 8));

	spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
	amModels[0].RenderModel();
	
	// ... and a treasure chest

	mModel = glm::translate(glm::mat4(1.0), glm::vec3(-10.0f, 17.5f, 0));
	mModel = glm::scale(mModel, glm::vec3(0.5f, 0.5f, 0.5f));

	spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
	amModels[1].RenderModel();

	// and 3 Deadpools :)

	FOR(i, 3)
	{
		mModel = glm::translate(glm::mat4(1.0), glm::vec3(-60.0f - 20.0f * i, 35.0f, -30.0f));
		mModel = glm::scale(mModel, glm::vec3(0.5f, 0.5f, 0.5f));

		spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		amModels[i == 2? 5 : i + 2].RenderModel();
	}

	// Render 3 rotated tori to create interesting object

	tTextures[5].BindTexture();
	glBindVertexArray(uiVAOSceneObjects);
	static float fGlobalAngle = 0.0f;

	FOR(i, 2)
	{
		glm::vec3 vCenter = glm::vec3(-40+i*40, 30, -20);
		mModel = glm::translate(glm::mat4(1.0), vCenter);
		if(i == 0)mModel = glm::rotate(mModel, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		glDrawArrays(GL_TRIANGLES, 0, iTorusFaces*3);

		mModel = glm::translate(glm::mat4(1.0), vCenter+glm::vec3(0.01f, 0.0f, 0.0f));
		if(i == 0)mModel = glm::rotate(mModel, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		mModel = glm::rotate(mModel, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		glDrawArrays(GL_TRIANGLES, 0, iTorusFaces*3);

		mModel = glm::translate(glm::mat4(1.0), vCenter+glm::vec3(0.00f, 0.01f, 0.0f));

		if(i == 0)mModel = glm::rotate(mModel, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		mModel = glm::rotate(mModel, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		glDrawArrays(GL_TRIANGLES, 0, iTorusFaces*3);
	}

	fGlobalAngle += appMain.sof(rotationSpeed);

	// Now we're going to render terrain

	hmWorld.SetRenderSize(300.0f, 35.0f, 300.0f);
	CShaderProgram* spTerrain = CMultiLayeredHeightmap::GetShaderProgram();

	spTerrain->UseProgram();

	spTerrain->SetUniform("matrices.projMatrix", oglControl->GetProjectionMatrix());
	spTerrain->SetUniform("matrices.viewMatrix", cCamera.Look());

	spTerrain->SetUniform("vEyePosition", cCamera.vEye);
	matShiny.SetUniformData(spTerrain, "matActive");

	// We bind all 5 textures - 3 of them are textures for layers, 1 texture is a "path" texture, and last one is
	// the places in heightmap where path should be and how intense should it be
	FOR(i, 5)
	{
		char sSamplerName[256];
		sprintf_s(sSamplerName, "gSampler[%d]", i);//_s
		tTextures[i].BindTexture(i);
		spTerrain->SetUniform(sSamplerName, i);
	}

	// ... set some uniforms
	spTerrain->SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", glm::mat4(1.0));
	spTerrain->SetUniform("vColor", glm::vec4(1, 1, 1, 1));

	dlSun.SetUniformData(spTerrain, "sunLight");

	// ... and finally render heightmap
	hmWorld.RenderHeightmap();

	if(bDisplayNormals)
	{
		spNormalDisplayer.UseProgram();
		spNormalDisplayer.SetUniform("fNormalLength", 1.0f);
		spNormalDisplayer.SetUniform("matrices.projMatrix", oglControl->GetProjectionMatrix());
		spNormalDisplayer.SetUniform("matrices.viewMatrix", cCamera.Look());

		CAssimpModel::BindModelsVAO();

		// ... Render the house again

		glm::mat4 mModel = glm::translate(glm::mat4(1.0), glm::vec3(40.0f, 17.0f, 0));
		mModel = glm::scale(mModel, glm::vec3(8, 8, 8));

		spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		amModels[0].RenderModel(GL_POINTS);

		// ... and the treasure chest again

		mModel = glm::translate(glm::mat4(1.0), glm::vec3(-10.0f, 17.5f, 0));
		mModel = glm::scale(mModel, glm::vec3(0.5f, 0.5f, 0.5f));

		spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		amModels[1].RenderModel(GL_POINTS);

		// and Deadpools

		FOR(i, 3)
		{
			mModel = glm::translate(glm::mat4(1.0), glm::vec3(-60.0f - 20.0f * i, 35.0f, -30.0f));
			mModel = glm::scale(mModel, glm::vec3(0.5f, 0.5f, 0.5f));

			spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
			amModels[i == 2 ? 5 : i + 2].RenderModel(GL_POINTS);
		}

		glBindVertexArray(uiVAOSceneObjects);

		FOR(i, 2)
		{
			glm::vec3 vCenter = glm::vec3(-40+i*40, 30, -20);
			mModel = glm::translate(glm::mat4(1.0), vCenter);
			if(i == 0)mModel = glm::rotate(mModel, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
			spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
			glDrawArrays(GL_POINTS, 0, iTorusFaces*3);

			mModel = glm::translate(glm::mat4(1.0), vCenter+glm::vec3(0.01f, 0.0f, 0.0f));
			if(i == 0)mModel = glm::rotate(mModel, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
			mModel = glm::rotate(mModel, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
			glDrawArrays(GL_POINTS, 0, iTorusFaces*3);

			mModel = glm::translate(glm::mat4(1.0), vCenter+glm::vec3(0.00f, 0.01f, 0.0f));

			if(i == 0)mModel = glm::rotate(mModel, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
			mModel = glm::rotate(mModel, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
			glDrawArrays(GL_POINTS, 0, iTorusFaces*3);
		}

		spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", hmWorld.GetScaleMatrix());
		hmWorld.RenderHeightmapForNormals();
	}

	tTextures[6].BindTexture(); 

	psMainParticleSystem.SetMatrices(oglControl->GetProjectionMatrix(), cCamera.vEye, cCamera.vView, cCamera.vUp);

	psMainParticleSystem.UpdateParticles(appMain.sof(1.0f));
	psMainParticleSystem.RenderParticles();

	// Updating and rendering particle systems for Deadpools
	psDP1.SetMatrices(oglControl->GetProjectionMatrix(), cCamera.vEye, cCamera.vView, cCamera.vUp);
	psDP1.UpdateParticles(appMain.sof(1.0f));
	psDP1.RenderParticles();
	psDP2.SetMatrices(oglControl->GetProjectionMatrix(), cCamera.vEye, cCamera.vView, cCamera.vUp);
	psDP2.UpdateParticles(appMain.sof(1.0f));
	psDP2.RenderParticles();
	psDP3.SetMatrices(oglControl->GetProjectionMatrix(), cCamera.vEye, cCamera.vView, cCamera.vUp);
	psDP3.UpdateParticles(appMain.sof(1.0f));
	psDP3.RenderParticles();

	cCamera.Update();

	// Print something over scene
	
	spFont2D.UseProgram();
	glDisable(GL_DEPTH_TEST);
	spFont2D.SetUniform("matrices.projMatrix", oglControl->GetOrthoMatrix());

	int w = oglControl->GetViewportWidth(), h = oglControl->GetViewportHeight();
	
	spFont2D.SetUniform("vColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ftFont.Print("OpenGL_7", 20, 20, 24);

	ftFont.PrintFormatted(20, h-30, 20, "FPS: %d", oglControl->GetFPS());
	ftFont.PrintFormatted(20, h-80, 20, "Particles (of the box system): %d", psMainParticleSystem.GetNumParticles());

	ftFont.PrintFormatted(20, h-110, 20, "Specular Intensity: %.2f (Press 'Q' and 'E' to change)", matShiny.fSpecularIntensity);
	if(Keys::Key('Q'))matShiny.fSpecularIntensity -= appMain.sof(0.2f);
	if(Keys::Key('E'))matShiny.fSpecularIntensity += appMain.sof(0.2f);

	ftFont.PrintFormatted(20, h-140, 20, "Specular Power: %.2f (Press 'Z' and 'C' to change)", matShiny.fSpecularPower);
	if(Keys::Key('Z'))matShiny.fSpecularPower -= appMain.sof(8.0f);
	if(Keys::Key('C'))matShiny.fSpecularPower += appMain.sof(8.0f);

	ftFont.PrintFormatted(20, h-200, 20, "Displaying Normals: %s (Press 'N' to toggle)", bDisplayNormals ? "Yes" : "Nope");
	if(Keys::Onekey('N'))bDisplayNormals = !bDisplayNormals;


	// Labels
	ftFont.PrintFormatted(20, h - 230, 20, "For changing particle system of the box (others are stable):");
	ftFont.PrintFormatted(20, h - 250, 20, "Velocity - O and P, current - %.1f-%.1f", psMainParticleSystem.getMinVelocity(), psMainParticleSystem.getMaxVelocity());
	ftFont.PrintFormatted(20, h - 270, 20, "Red level - 1 and 2, current - %.1f", psMainParticleSystem.getRed());
	ftFont.PrintFormatted(20, h - 290, 20, "Green level - 3 and 4, current - %.1f", psMainParticleSystem.getGreen());
	ftFont.PrintFormatted(20, h - 310, 20, "Blue level - 5 and 6, current - %.1f", psMainParticleSystem.getBlue());
	ftFont.PrintFormatted(20, h - 330, 20, "Size - down and up arrows, current - %.2f", psMainParticleSystem.getSize());
	ftFont.PrintFormatted(20, h - 350, 20, "Lifetime - U and I, current - %.1f-%.1f", psMainParticleSystem.getGenLifeMin(), psMainParticleSystem.getGenLifeMax());
	ftFont.PrintFormatted(20, h - 370, 20, "Spawn time - K and L, current - %.2f", psMainParticleSystem.getSpawnTime());
	ftFont.PrintFormatted(20, h - 390, 20, "Count - right and left arrows, current - %.1f", psMainParticleSystem.getCount());
	ftFont.PrintFormatted(20, h - 420, 20, "Controlling rotation speed - G and H, current - %.1f", rotationSpeed);
	ftFont.PrintFormatted(20, h - 450, 20, "Lev Osipov. BSE121(1). 20.03.2016");

	// Controlling particle system
	if (Keys::Onekey(VK_UP)) psMainParticleSystem.incSize();
	if (Keys::Onekey(VK_DOWN)) psMainParticleSystem.decSize();
	if (Keys::Onekey(VK_RIGHT)) psMainParticleSystem.incCount();
	if (Keys::Onekey(VK_LEFT)) psMainParticleSystem.decCount();
	if (Keys::Onekey('2')) psMainParticleSystem.incRed();
	if (Keys::Onekey('1')) psMainParticleSystem.decRed();
	if (Keys::Onekey('4')) psMainParticleSystem.incGreen();
	if (Keys::Onekey('3')) psMainParticleSystem.decGreen();
	if (Keys::Onekey('6')) psMainParticleSystem.incBlue();
	if (Keys::Onekey('5')) psMainParticleSystem.decBlue();
	if (Keys::Onekey('P')) psMainParticleSystem.incVelocity();
	if (Keys::Onekey('O')) psMainParticleSystem.decVelocity();
	if (Keys::Onekey('I')) psMainParticleSystem.incGenLife();
	if (Keys::Onekey('U')) psMainParticleSystem.decGenLife();
	if (Keys::Onekey('L')) psMainParticleSystem.incSpawnTime();
	if (Keys::Onekey('K')) psMainParticleSystem.decSpawnTime();

	// Controlling rotation
	if (Keys::Onekey('H')) {
		rotationSpeed += 10.0f;
		if (rotationSpeed > 100.0f) rotationSpeed = 100.0f;
	}
	if (Keys::Onekey('G')) {
		rotationSpeed -= 10.0f;
		if (rotationSpeed < 0.0f) rotationSpeed = 0.0f;
	}

	glEnable(GL_DEPTH_TEST);	
	if(Keys::Onekey(VK_ESCAPE))PostQuitMessage(0);

	oglControl->SwapBuffers();
}

/*-----------------------------------------------

Name:    ReleaseScene

Params:  lpParam - Pointer to anything you want.

Result:  Releases OpenGL scene.

/*---------------------------------------------*/

void ReleaseScene(LPVOID lpParam)
{
	FOR(i, NUMTEXTURES)tTextures[i].DeleteTexture();
	sbMainSkybox.DeleteSkybox();

	spMain.DeleteProgram();
	spOrtho2D.DeleteProgram();
	spFont2D.DeleteProgram();
	FOR(i, NUMSHADERS)shShaders[i].DeleteShader();
	ftFont.DeleteFont();

	glDeleteVertexArrays(1, &uiVAOSceneObjects);
	vboSceneObjects.DeleteVBO();

	hmWorld.ReleaseHeightmap();
	CMultiLayeredHeightmap::ReleaseTerrainShaderProgram();
}