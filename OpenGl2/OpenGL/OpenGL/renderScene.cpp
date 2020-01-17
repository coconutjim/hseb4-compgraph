/*
Осипов Лев Игоревич
Проект 14. OpenGL2
Visual Studio 2013
17.02.2016
Выполнены все задания, код декомпозирован и закомментирован.
Релизованы куб, пирамида, октаэдр и тор (с разными текстурами).
Управление:
1) Трансформация каждой фигуры индивидуально - одновременное нажатие первой английской буквы фигуры и следующих клавиш:
a - движение влево
d - движение вправо
w - движение вверх
s - движение вниз
z - движение вперед
x - движение назад
стрелка вправо - вращение в одну сторону
стрелка влево - вращение в другую сторону
стрелка вверх - увеличение фигуры
стрелка вниз - уменьшение фигуры
Примеры:
увеличение куба - с + стрелка вверх
сдвиг тора вправо - t + d
2) включение режима случайного перемещения фигур - клавиша r, она же отвечает и за выключение этого режима
3) Для вращения камеры - левый ctrl + стрелки вправо и влево, для приближения/отдаления камеры - левый ctrl + стрелки вверх и вниз
*/

#pragma warning(disable:4996)

#include "common_header.h"

#include "win_OpenGLApp.h"

#include "shaders.h"
#include "texture.h"
#include "vertexBufferObject.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* One VBO, where all static data are stored now,
in this tutorial vertex is stored as 3 floats for
position and 2 floats for texture coordinate */

CVertexBufferObject vboSceneObjects;
UINT uiVAO; // And one VAO

CShader shVertex, shFragment;
CShaderProgram spMain;

CTexture tGold, tSnow, tBrown, tBubbles, tRings; // textures

#include "static_geometry.h"

int torusCount; // torus vertices count
bool randomMode = false; // random mode state

// Checks transformation bounds
void checkBounds();

// Reset figures' transformations
void resetFigures();

// Randomizes figures
void randomizeFigures();

// Initializes OpenGL features that will be used.
// lpParam - Pointer to anything you want.
void initScene(LPVOID lpParam)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	vboSceneObjects.createVBO();
	glGenVertexArrays(1, &uiVAO); // Create one VAO
	glBindVertexArray(uiVAO);

	vboSceneObjects.bindVBO();

	// Add cube to VBO

	FOR(i, 36)
	{
		vboSceneObjects.addData(&vCubeVertices[i], sizeof(glm::vec3));
		vboSceneObjects.addData(&vCubeTexCoords[i%6], sizeof(glm::vec2));
	}

	// Add pyramid to VBO

	FOR(i, 12)
	{
		vboSceneObjects.addData(&vPyramidVertices[i], sizeof(glm::vec3));
		vboSceneObjects.addData(&vPyramidTexCoords[i%3], sizeof(glm::vec2));
	}

	// Add octaedr (2 pyramids) to VBO

	FOR(i, 12)
	{
		vboSceneObjects.addData(&(vPyramidVertices[i] + glm::vec3(0.0f, 1.0f, 0.0f)), sizeof(glm::vec3));
		vboSceneObjects.addData(&vPyramidTexCoords[i % 3], sizeof(glm::vec2));
	}
	FOR(i, 12)
	{
		vboSceneObjects.addData(&(vPyramidVertices[i] * glm::vec3(1.0f, -1.0f, 1.0f)), sizeof(glm::vec3));
		vboSceneObjects.addData(&vPyramidTexCoords[i % 3], sizeof(glm::vec2));
	}

	// Add torus to VBO

	torusCount = generateTorus(vboSceneObjects, 1.0f, .4f, 50, 50) * 3; // faces * 3 = vertices

	// Add ground to VBO

	FOR(i, 6)
	{
		vboSceneObjects.addData(&vGround[i], sizeof(glm::vec3));
		vCubeTexCoords[i] *= 5.0f;
		vboSceneObjects.addData(&vCubeTexCoords[i%6], sizeof(glm::vec2));
	}

	vboSceneObjects.uploadDataToGPU(GL_STATIC_DRAW);
	
	// Vertex positions start on zero index, and distance between two consecutive is sizeof whole
	// vertex data (position and tex. coord)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)+sizeof(glm::vec2), 0);
	// Texture coordinates start right after positon, thus on (sizeof(glm::vec3)) index,
	// and distance between two consecutive is sizeof whole vertex data (position and tex. coord)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)+sizeof(glm::vec2), (void*)sizeof(glm::vec3));

	// Load shaders and create shader program

	shVertex.loadShader("data\\shaders\\shader.vert", GL_VERTEX_SHADER);
	shFragment.loadShader("data\\shaders\\shader.frag", GL_FRAGMENT_SHADER);

	spMain.createProgram();
	spMain.addShaderToProgram(&shVertex);
	spMain.addShaderToProgram(&shFragment);

	spMain.linkProgram();
	spMain.useProgram();

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	// Finally, load our texture

	tGold.loadTexture2D("data\\textures\\golddiag.jpg", true);
	tGold.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

	tSnow.loadTexture2D("data\\textures\\snow.jpg", true);
	tSnow.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

	tBrown.loadTexture2D("data\\textures\\brown.jpg", true);
	tBrown.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

	tBubbles.loadTexture2D("data\\textures\\bubbles.jpg", true);
	tBubbles.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

	tRings.loadTexture2D("data\\textures\\rings.jpg", true);
	tRings.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
	glEnable(GL_TEXTURE_2D);
}

// Camera 
float cameraX, cameraY, cameraZ;
float cameraAngle = 0.0f;
float cameraDistance = 26.83f;

// Transformation variables
float fCubeXPosition = -10.0f, fPyramidXPosition = 10.0f, fOctaedrXPosition = 0.0f, fTorusXPosition = 12.0f;
float fCubeYPosition = 0.0f, fPyramidYPosition = 0.0f, fOctaedrYPosition = 0.0f, fTorusYPosition = 10.0f;
float fCubeZPosition = 0.0f, fPyramidZPosition = 0.0f, fOctaedrZPosition = 0.0f, fTorusZPosition = 0.0f;
float fRotationAngleCube = 0.0f, fRotationAnglePyramid = 0.0f, fRotationAngleOctaedr = 0.0f, fRotationAngleTorus = 0.0f;
float fCubeRotationSpeed = 0.0f, fPyramidRotationSpeed = 0.0f, fOctaedrRotationSpeed = 0.0f, fTorusRotationSpeed = 0.0f;
float fCubeScale = 7.0f, fPyramidScale = 7.0f, fOctaedrScale = 6.0f, fTorusScale = 3.0f;
const float PIover180 = 3.1415f/180.0f;

void displayTextureFiltersInfo()
{
	char buf[255];
	string sInfoMinification[] = 
	{
		"Nearest",
		"Bilinear"
	};
	string sInfoMagnification[] =
	{
		"Nearest",
		"Bilinear",
		"Nearest on closest mipmap",
		"Bilinear on closest mipmap",
		"Trilinear"
	};
	sprintf(buf, "Mag. Filter: %s, Min. Filter: %s", sInfoMinification[tSnow.getMagnificationFilter()].c_str(), 
																	sInfoMagnification[tSnow.getMinificationFilter()-2].c_str());
	SetWindowText(appMain.hWnd, buf);
}

// Transformation steps
const float moveStep = 3.0f;
const float rotateStep = 5.0f;
const float scaleStep = 1.0f;

// Renders whole scene.
// lpParam - Pointer to anything you want.
void renderScene(LPVOID lpParam)
{
	// Typecast lpParam to COpenGLControl pointer
	COpenGLControl* oglControl = (COpenGLControl*)lpParam;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int iModelViewLoc = glGetUniformLocation(spMain.getProgramID(), "modelViewMatrix");
	int iProjectionLoc = glGetUniformLocation(spMain.getProgramID(), "projectionMatrix");
	glUniformMatrix4fv(iProjectionLoc, 1, GL_FALSE, glm::value_ptr(*oglControl->getProjectionMatrix()));

	// Setting camera
	cameraX = cameraDistance * sin(cameraAngle);
	cameraY = sqrt(cameraDistance * cameraDistance / 5);
	cameraZ = cameraDistance * cos(cameraAngle);

	glm::mat4 mModelView = glm::lookAt(glm::vec3(cameraX, cameraY, cameraZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mCurrent;

	glBindVertexArray(uiVAO);

	// Texture binding - we set GL_ACTIVE_TEXTURE0, and then we tell fragment shader,
	// that gSampler variable will fetch data from GL_ACTIVE_TEXTURE0

	int iSamplerLoc = glGetUniformLocation(spMain.getProgramID(), "gSampler");
	glUniform1i(iSamplerLoc, 0);

	tBrown.bindTexture(0);

	// Rendering of cube

	mCurrent = glm::translate(mModelView, glm::vec3(fCubeXPosition, fCubeYPosition, fCubeZPosition));
	mCurrent = glm::scale(mCurrent, glm::vec3(fCubeScale, fCubeScale, fCubeScale));
	mCurrent = glm::rotate(mCurrent, fRotationAngleCube, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mCurrent));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Rendering of pyramid

	tBubbles.bindTexture();

	mCurrent = glm::translate(mModelView, glm::vec3(fPyramidXPosition, fPyramidYPosition, fPyramidZPosition));
	mCurrent = glm::scale(mCurrent, glm::vec3(fPyramidScale, fPyramidScale, fPyramidScale));
	mCurrent = glm::rotate(mCurrent, fRotationAnglePyramid, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mCurrent));

	glDrawArrays(GL_TRIANGLES, 36, 12);

	// Rendering of octaedr

	tGold.bindTexture();

	mCurrent = glm::translate(mModelView, glm::vec3(fOctaedrXPosition, fOctaedrYPosition, fOctaedrZPosition));
	mCurrent = glm::scale(mCurrent, glm::vec3(fOctaedrScale, fOctaedrScale, fOctaedrScale));
	mCurrent = glm::rotate(mCurrent, fRotationAngleOctaedr, glm::vec3(0.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mCurrent));

	glDrawArrays(GL_TRIANGLES, 48, 24);

	// Rendering of torus

	tRings.bindTexture();

	mCurrent = glm::translate(mModelView, glm::vec3(fTorusXPosition, fTorusYPosition, fTorusZPosition));
	mCurrent = glm::scale(mCurrent, glm::vec3(fTorusScale, fTorusScale, fTorusScale));
	mCurrent = glm::rotate(mCurrent, fRotationAngleTorus, glm::vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mCurrent));

	glDrawArrays(GL_TRIANGLES, 72, torusCount);

	// Render ground

	tSnow.bindTexture();

	glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, glm::value_ptr(mModelView));
	glDrawArrays(GL_TRIANGLES, torusCount + 72, 6);

	// A little (or not so litle) interaction for user

	// Random mode switcher
	if (Keys::onekey('R')) {
		randomMode = !randomMode;
		if (!randomMode) {
			resetFigures(); // reseting 
		}
	}
	
	if (randomMode) { // randomize all transformations
		randomizeFigures();
	}
	else { // just allow user to tansform figure
		// Cube
		if (Keys::key('C')) {
			// Moving
			if (Keys::key('D'))fCubeXPosition += appMain.sof(moveStep); // right
			if (Keys::key('A'))fCubeXPosition -= appMain.sof(moveStep); // left
			if (Keys::key('W'))fCubeYPosition += appMain.sof(moveStep); // up
			if (Keys::key('S'))fCubeYPosition -= appMain.sof(moveStep); // down
			if (Keys::key('X'))fCubeZPosition += appMain.sof(moveStep); // back
			if (Keys::key('Z'))fCubeZPosition -= appMain.sof(moveStep); // forward

			// Rotating 
			if (Keys::key(VK_RIGHT))fCubeRotationSpeed += appMain.sof(rotateStep);
			if (Keys::key(VK_LEFT))fCubeRotationSpeed -= appMain.sof(rotateStep);

			// Scaling 
			if (Keys::key(VK_UP))fCubeScale += appMain.sof(scaleStep); // bigger
			if (Keys::key(VK_DOWN))fCubeScale -= appMain.sof(scaleStep); // smaller
		}

		// Pyramid
		if (Keys::key('P')) {
			// Moving
			if (Keys::key('D'))fPyramidXPosition += appMain.sof(moveStep); // right
			if (Keys::key('A'))fPyramidXPosition -= appMain.sof(moveStep); // left
			if (Keys::key('W'))fPyramidYPosition += appMain.sof(moveStep); // up
			if (Keys::key('S'))fPyramidYPosition -= appMain.sof(moveStep); // down
			if (Keys::key('X'))fPyramidZPosition += appMain.sof(moveStep); // back
			if (Keys::key('Z'))fPyramidZPosition -= appMain.sof(moveStep); // forward

			// Rotating 
			if (Keys::key(VK_RIGHT))fPyramidRotationSpeed += appMain.sof(rotateStep);
			if (Keys::key(VK_LEFT))fPyramidRotationSpeed -= appMain.sof(rotateStep);

			// Scaling 
			if (Keys::key(VK_UP))fPyramidScale += appMain.sof(scaleStep); // bigger
			if (Keys::key(VK_DOWN))fPyramidScale -= appMain.sof(scaleStep); // smaller
		}

		// Octaedr
		if (Keys::key('O')) {
			// Moving
			if (Keys::key('D'))fOctaedrXPosition += appMain.sof(moveStep); // right
			if (Keys::key('A'))fOctaedrXPosition -= appMain.sof(moveStep); // left
			if (Keys::key('W'))fOctaedrYPosition += appMain.sof(moveStep); // up
			if (Keys::key('S'))fOctaedrYPosition -= appMain.sof(moveStep); // down
			if (Keys::key('X'))fOctaedrZPosition += appMain.sof(moveStep); // back
			if (Keys::key('Z'))fOctaedrZPosition -= appMain.sof(moveStep); // forward

			// Rotating 
			if (Keys::key(VK_RIGHT))fOctaedrRotationSpeed += appMain.sof(rotateStep);
			if (Keys::key(VK_LEFT))fOctaedrRotationSpeed -= appMain.sof(rotateStep);

			// Scaling 
			if (Keys::key(VK_UP))fOctaedrScale += appMain.sof(scaleStep); // bigger
			if (Keys::key(VK_DOWN))fOctaedrScale -= appMain.sof(scaleStep); // smaller
		}

		// Torus
		if (Keys::key('T')) {
			// Moving
			if (Keys::key('D'))fTorusXPosition += appMain.sof(moveStep); // right
			if (Keys::key('A'))fTorusXPosition -= appMain.sof(moveStep); // left
			if (Keys::key('W'))fTorusYPosition += appMain.sof(moveStep); // up
			if (Keys::key('S'))fTorusYPosition -= appMain.sof(moveStep); // down
			if (Keys::key('X'))fTorusZPosition += appMain.sof(moveStep); // back
			if (Keys::key('Z'))fTorusZPosition -= appMain.sof(moveStep); // forward

			// Rotating 
			if (Keys::key(VK_RIGHT))fTorusRotationSpeed += appMain.sof(rotateStep);
			if (Keys::key(VK_LEFT))fTorusRotationSpeed -= appMain.sof(rotateStep);

			// Scaling 
			if (Keys::key(VK_UP))fTorusScale += appMain.sof(scaleStep); // bigger
			if (Keys::key(VK_DOWN))fTorusScale -= appMain.sof(scaleStep); // smaller
		}
	}

	// Camera step
	float cameraStep = 0.005f;

	if (Keys::key(VK_LCONTROL)) { // camera

		// Moving
		if (Keys::key(VK_UP)) cameraDistance -= cameraStep * 10;
		if (Keys::key(VK_DOWN)) cameraDistance += cameraStep * 10;
		// Rotating
		if (Keys::key(VK_LEFT)) cameraAngle -= cameraStep;
		if (Keys::key(VK_RIGHT)) cameraAngle += cameraStep;
	}

	// Checking bounds
	checkBounds();

	// Applying rotation
	fRotationAngleCube += appMain.sof(fCubeRotationSpeed);
	fRotationAnglePyramid += appMain.sof(fPyramidRotationSpeed);
	fRotationAngleOctaedr += appMain.sof(fOctaedrRotationSpeed);
	fRotationAngleTorus += appMain.sof(fTorusRotationSpeed);

	//fCubeRotationSpeed = fPyramidRotationSpeed = fOctaedrRotationSpeed = fTorusRotationSpeed = 0.0f;

	// If user presses escape, quit the application
	if(Keys::onekey(VK_ESCAPE))PostQuitMessage(0);

	// F1 and F2 change the texture filterings and set window text about that
	if(Keys::onekey(VK_F1))
	{
		tGold.setFiltering((tGold.getMagnificationFilter()+1)%2, tGold.getMinificationFilter());
		tSnow.setFiltering((tSnow.getMagnificationFilter()+1)%2, tSnow.getMinificationFilter());
		displayTextureFiltersInfo();
	}
	if(Keys::onekey(VK_F2))
	{
		int iNewMinFilter = tSnow.getMinificationFilter() == TEXTURE_FILTER_MIN_TRILINEAR ? TEXTURE_FILTER_MIN_NEAREST : tSnow.getMinificationFilter()+1;
		tSnow.setFiltering(tSnow.getMagnificationFilter(), iNewMinFilter); 
		tGold.setFiltering(tGold.getMagnificationFilter(), iNewMinFilter);
		displayTextureFiltersInfo();
	}
	oglControl->swapBuffers();
}

// Bound constants
const float XMAX = 30.0f;
const float XMIN = -30.0f;
const float YMAX = 15.0f;
const float YMIN = 0.0f;
const float ZMAX = 10.0f;
const float ZMIN = -10.0f;
const float SCALE_MAX = 12.0f;
const float SCALE_MIN = 1.0f;
const float CAMERA_DISTANCE_MAX = 90.0f;
const float CAMERA_DISTANCE_MIN = 20.0f;

// Checks transformation bounds
void checkBounds() {
	// Checking cube
	// Moving bounds
	if (fCubeXPosition > XMAX) fCubeXPosition = XMAX;
	if (fCubeXPosition < XMIN) fCubeXPosition = XMIN;
	if (fCubeYPosition > YMAX) fCubeYPosition = YMAX;
	if (fCubeYPosition < YMIN) fCubeYPosition = YMIN;
	if (fCubeZPosition > ZMAX) fCubeZPosition = ZMAX;
	if (fCubeZPosition < ZMIN) fCubeZPosition = ZMIN;
	// Scaling bounds
	if (fCubeScale > SCALE_MAX) fCubeScale = SCALE_MAX;
	if (fCubeScale < SCALE_MIN) fCubeScale = SCALE_MIN;

	// Checking pyramid
	// Moving bounds
	if (fPyramidXPosition > XMAX) fPyramidXPosition = XMAX;
	if (fPyramidXPosition < XMIN) fPyramidXPosition = XMIN;
	if (fPyramidYPosition > YMAX) fPyramidYPosition = YMAX;
	if (fPyramidYPosition < YMIN) fPyramidYPosition = YMIN;
	if (fPyramidZPosition > ZMAX) fPyramidZPosition = ZMAX;
	if (fPyramidZPosition < ZMIN) fPyramidZPosition = ZMIN;
	// Scaling bounds
	if (fPyramidScale > SCALE_MAX) fPyramidScale = SCALE_MAX;
	if (fPyramidScale < SCALE_MIN) fPyramidScale = SCALE_MIN;

	// Checking octaedr
	// Moving bounds
	if (fOctaedrXPosition > XMAX) fOctaedrXPosition = XMAX;
	if (fOctaedrXPosition < XMIN) fOctaedrXPosition = XMIN;
	if (fOctaedrYPosition > YMAX) fOctaedrYPosition = YMAX;
	if (fOctaedrYPosition < YMIN) fOctaedrYPosition = YMIN;
	if (fOctaedrZPosition > ZMAX) fOctaedrZPosition = ZMAX;
	if (fOctaedrZPosition < ZMIN) fOctaedrZPosition = ZMIN;
	// Scaling bounds
	if (fOctaedrScale > SCALE_MAX) fOctaedrScale = SCALE_MAX;
	if (fOctaedrScale < SCALE_MIN) fOctaedrScale = SCALE_MIN;

	// Checking torus
	// Moving bounds
	if (fTorusXPosition > XMAX) fTorusXPosition = XMAX;
	if (fTorusXPosition < XMIN) fTorusXPosition = XMIN;
	if (fTorusYPosition > YMAX) fTorusYPosition = YMAX;
	if (fTorusYPosition < YMIN) fTorusYPosition = YMIN;
	if (fTorusZPosition > ZMAX) fTorusZPosition = ZMAX;
	if (fTorusZPosition < ZMIN) fTorusZPosition = ZMIN;
	// Scaling bounds
	if (fTorusScale > SCALE_MAX) fTorusScale = SCALE_MAX;
	if (fTorusScale < SCALE_MIN) fTorusScale = SCALE_MIN;

	// Camera bounds 
	if (cameraDistance > CAMERA_DISTANCE_MAX) cameraDistance = CAMERA_DISTANCE_MAX;
	if (cameraDistance < CAMERA_DISTANCE_MIN) cameraDistance = CAMERA_DISTANCE_MIN;
}

// Randomizes figures
void randomizeFigures() {
	srand(time(NULL));
	int interval = 7;
	int offset = 3;
	float coeff = 1000.0f; 

	// Cube
	float r = (rand() % interval - offset) / coeff;
	fCubeXPosition += r * moveStep;
	r = (rand() % interval - offset) / coeff;
	fCubeYPosition += r * moveStep;
	r = (rand() % interval - offset) / coeff;
	fCubeZPosition += r * moveStep;
	r = (rand() % interval - offset) / coeff;
	fCubeRotationSpeed += r * rotateStep;
	r = (rand() % interval - offset) / coeff;
	fCubeScale += r * scaleStep;

	// Pyramid
	r = (rand() % interval - offset) / coeff;
	fPyramidXPosition += r * moveStep;
	r = (rand() % interval - offset) / coeff;
	fPyramidYPosition += r * moveStep;
	r = (rand() % interval - offset) / coeff;
	fPyramidZPosition += r * moveStep;
	r = (rand() % interval - offset) / coeff;
	fPyramidRotationSpeed += r * rotateStep;
	r = (rand() % interval - offset) / coeff;
	fPyramidScale += r * scaleStep;

	// Octaedr
	r = (rand() % interval - offset) / coeff;
	fOctaedrXPosition += r * moveStep;
	r = (rand() % interval - offset) / coeff;
	fOctaedrYPosition += r * moveStep;
	r = (rand() % interval - offset) / coeff;
	fOctaedrZPosition += r * moveStep;
	r = (rand() % interval - offset) / coeff;
	fOctaedrRotationSpeed += r * rotateStep;
	r = (rand() % interval - offset) / coeff;
	fOctaedrScale += r * scaleStep;

	// Torus
	r = (rand() % interval - offset) / coeff;
	fTorusXPosition += r * moveStep;
	r = (rand() % interval - offset) / coeff;
	fTorusYPosition += r * moveStep;
	r = (rand() % interval - offset) / coeff;
	fTorusZPosition += r * moveStep;
	r = (rand() % interval - offset) / coeff;
	fTorusRotationSpeed += r * rotateStep;
	r = (rand() % interval - offset) / coeff;
	fTorusScale += r * scaleStep;
}

// Reset figures' transformations
void resetFigures() {
	fCubeXPosition = -10.0f;
	fPyramidXPosition = 10.0f;
	fOctaedrXPosition = 0.0f;
	fTorusXPosition = 12.0f;
	fCubeYPosition = 0.0f;
	fPyramidYPosition = 0.0f;
	fOctaedrYPosition = 0.0f;
	fTorusYPosition = 10.0f;
	fCubeZPosition = 0.0f;
	fPyramidZPosition = 0.0f;
	fOctaedrZPosition = 0.0f;
	fTorusZPosition = 0.0f;
	fRotationAngleCube = 0.0f;
	fRotationAnglePyramid = 0.0f;
	fRotationAngleOctaedr = 0.0f;
	fRotationAngleTorus = 0.0f;
	fCubeRotationSpeed = 0.0f;
	fPyramidRotationSpeed = 0.0f;
	fOctaedrRotationSpeed = 0.0f;
	fTorusRotationSpeed = 0.0f;
	fCubeScale = 7.0f;
	fPyramidScale = 7.0f;
	fOctaedrScale = 7.0f;
	fTorusScale = 5.0f;
}

// Releases OpenGL scene.
// lpParam - Pointer to anything you want.
void releaseScene(LPVOID lpParam)
{
	spMain.deleteProgram();

	shVertex.deleteShader();
	shFragment.deleteShader();

	vboSceneObjects.releaseVBO();
	glDeleteVertexArrays(1, &uiVAO);

	tGold.releaseTexture();
	tSnow.releaseTexture();
}