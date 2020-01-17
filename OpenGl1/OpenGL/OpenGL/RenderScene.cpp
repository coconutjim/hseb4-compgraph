/*
Осипов Лев Игоревич
Проект 13.
Visual Studio 2013
04.02.2016
Сделано:
1) Изменен цвет окна
2) Треугольник и четырехугольник перемещены в правый нижний край
3) Реализована радуга
4) Реализован контур пятиконечной звезды
5) Реализованы две шестиконечные звезды
6) Реализован переключатель между пятиконечной звездой
и шестиконечными звездами. Для переключения следует нажать клавишу s
7) Код в RenderScene.cpp декомпозирован и закомментирован
*/
#include "common_header.h"

#include "win_OpenGLApp.h"

#include "shaders.h"

// Constants =======================================================================================

// Figures count
const int fig_count = 6;

// Indices and vertices count for figures (each vertex has 3 floats)
// Triangle
const int triangle_vcount = 3;
const int triangle_icount = triangle_vcount * 3; 
// Quad
const int quad_vcount = 4;
const int quad_icount = quad_vcount * 3;
// Rainbow
const int rainbow_vcount = 14; // 7 segments, each has 2 borders
const int rainbow_icount = rainbow_vcount * 3;
// Six-pointed star
const int star6p_vcount = 6;
const int star6p_icount = star6p_vcount * 3;
// Five-pointed star
const int star5p_vcount = 5;
const int star5p_icount = star5p_vcount * 3;

// Data structures =======================================================================================

// Data to render figures
float fTriangle[triangle_icount]; 
float fQuad[quad_icount]; 
float fRainbow[rainbow_icount];
float fStar1[star6p_icount];
float fStar2[star6p_icount];
float fStar3[star5p_icount];

// Figures' colors
float fTriangleColor[triangle_icount];
float fQuadColor[quad_icount];
float fRainbowColor[rainbow_icount];
float fStar1Color[star6p_icount];
float fStar2Color[star6p_icount];
float fStar3Color[star5p_icount];

// Data holders
UINT uiVBO[fig_count * 2];
UINT uiVAO[fig_count];

CShader shVertex, shFragment;
CShaderProgram spMain;

// Functions' declarations =======================================================================================
void setupFigures();
void bindFigure(UINT uiVAO, int count, float vertices[], UINT uiVBO_v, float colors[], UINT uiVBO_c);

// Initializes OpenGL features that will be used.
// lpParam - Pointer to anything you want.
void InitScene(LPVOID lpParam)
{
	glClearColor(0.1f, 0.5f, 0.7f, 1.0f); // background color

	// Setup vertices and colors
	setupFigures();

	glGenVertexArrays(fig_count, uiVAO); // Generate three VAOs, for triangle, quad and rainbow
	glGenBuffers(fig_count * 2, uiVBO); // And six VBOs (vertices and colors for each figure)

	// Setup whole triangle
	bindFigure(uiVAO[0], triangle_icount, fTriangle, uiVBO[0], fTriangleColor, uiVBO[1]);
	
	// Setup whole quad
	bindFigure(uiVAO[1], quad_icount, fQuad, uiVBO[2], fQuadColor, uiVBO[3]);
	
	// Setup whole rainbow
	bindFigure(uiVAO[2], rainbow_icount, fRainbow, uiVBO[4], fRainbowColor, uiVBO[5]);

	// Setup the first star
	bindFigure(uiVAO[3], star6p_icount, fStar1, uiVBO[6], fStar1Color, uiVBO[7]);

	// Setup the second star
	bindFigure(uiVAO[4], star6p_icount, fStar2, uiVBO[8], fStar2Color, uiVBO[9]);

	// Setup the third star
	bindFigure(uiVAO[5], star5p_icount, fStar3, uiVBO[10], fStar3Color, uiVBO[11]);
	
	// Load shaders and create shader program

	shVertex.LoadShader("data\\shaders\\shader.vert", GL_VERTEX_SHADER);
	shFragment.LoadShader("data\\shaders\\shader.frag", GL_FRAGMENT_SHADER);

	spMain.CreateProgram();
	spMain.AddShaderToProgram(&shVertex);
	spMain.AddShaderToProgram(&shFragment);

	spMain.LinkProgram();
	spMain.UseProgram();
}

// Binds a figure to buffers
void bindFigure(UINT uiVAO, int count, float vertices[], UINT uiVBO_v, float colors[], UINT uiVBO_c) {
	glBindVertexArray(uiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO_v);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO_c);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

// Renders whole scene.
// lpParam - Pointer to anything you want.
void RenderScene(LPVOID lpParam)
{
	// Typecast lpParam to COpenGLControl pointer
	COpenGLControl* oglControl = (COpenGLControl*)lpParam;

	// We just clear color
	glClear(GL_COLOR_BUFFER_BIT);

	// Render triangle
	glBindVertexArray(uiVAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, triangle_vcount);

	// Render quad
	glBindVertexArray(uiVAO[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, quad_vcount);

	// Render rainbow
	glBindVertexArray(uiVAO[2]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, rainbow_vcount);

	if (oglControl->isShowStars()) { // if we need to render two 6-pointed stars

		// Render star 1
		glBindVertexArray(uiVAO[3]);
		glDrawArrays(GL_TRIANGLES, 0, star6p_vcount);

		// Render star 2
		glBindVertexArray(uiVAO[4]);
		glDrawArrays(GL_TRIANGLES, 0, star6p_vcount);
	}
	else { // if we need to render one 5-pointed star
		glBindVertexArray(uiVAO[5]);
		glDrawArrays(GL_LINE_LOOP, 0, star5p_vcount);
	}

	oglControl->SwapBuffersM();
}

// Releases OpenGL scene.
// lpParam - Pointer to anything you want.
void ReleaseScene(LPVOID lpParam)
{
	spMain.DeleteProgram();

	shVertex.DeleteShader();
	shFragment.DeleteShader();
}

// Setups figures' vertices and colors
void setupFigures() {
	// Setup triangle vertices
	fTriangle[0] = 0.6f; fTriangle[1] = -0.5f; fTriangle[2] = 0.0f;
	fTriangle[3] = 0.8f; fTriangle[4] = -0.5f; fTriangle[5] = 0.0f;
	fTriangle[6] = 0.7f; fTriangle[7] = -0.2f; fTriangle[8] = 0.0f;

	// Setup triangle color
	fTriangleColor[0] = 1.0f; fTriangleColor[1] = 0.0f; fTriangleColor[2] = 0.0f;
	fTriangleColor[3] = 0.0f; fTriangleColor[4] = 1.0f; fTriangleColor[5] = 0.0f;
	fTriangleColor[6] = 0.0f; fTriangleColor[7] = 0.0f; fTriangleColor[8] = 1.0f;

	// Setup quad vertices
	fQuad[0] = 0.6f; fQuad[1] = -0.6f; fQuad[2] = 0.0f;
	fQuad[3] = 0.6f; fQuad[4] = -0.8f; fQuad[5] = 0.0f;
	fQuad[6] = 0.8f; fQuad[7] = -0.6f; fQuad[8] = 0.0f;
	fQuad[9] = 0.8f; fQuad[10] = -0.8f; fQuad[11] = 0.0f;

	// Setup quad color
	fQuadColor[0] = 1.0f; fQuadColor[1] = 0.0f; fQuadColor[2] = 0.0f;
	fQuadColor[3] = 0.0f; fQuadColor[4] = 1.0f; fQuadColor[8] = 0.0f;
	fQuadColor[6] = 0.0f; fQuadColor[7] = 0.0f; fQuadColor[5] = 1.0f;
	fQuadColor[9] = 1.0f; fQuadColor[10] = 1.0f; fQuadColor[11] = 0.0f;

	// Setup rainbow vertices
	float top = 0.9f; // rainbow top position
	float width = 2.0f; // rainbow width
	float height = 0.03f; // rainbow segment height
	// cycle through rainbow segments
	for (int i = 0, step = 0; i < rainbow_icount; i += 6, ++step) {
		// filling left and right border of a segment
		fRainbow[i] = -width / 2;
		fRainbow[i + 1] = top - step * height;
		fRainbow[i + 2] = 0;
		fRainbow[i + 3] = width / 2;
		fRainbow[i + 4] = top - step * height;
		fRainbow[i + 5] = 0;
	}

	// Rainbow colors (7 colors, 3 floats for each)
	float rainbowColorScheme[21] =
	{
		1.0f, 0.0f, 0.0f, // red
		1.0f, 0.5f, 0.0f, // orange
		1.0f, 1.0f, 0.0f, // yellow
		0.0f, 1.0f, 0.0f, // green
		0.0f, 1.0f, 1.0f, // blue
		0.0f, 0.0f, 1.0f, // dark blue
		1.0f, 0.0f, 1.0f  // purple
	};


	// Setup rainbow colors
	for (int i = 0, segNum = 0; i < rainbow_icount; i += 6, segNum += 3) {
		// Mapping color to each segment (to its left and right borders)
		fRainbowColor[i] = rainbowColorScheme[segNum];
		fRainbowColor[i + 1] = rainbowColorScheme[segNum + 1];
		fRainbowColor[i + 2] = rainbowColorScheme[segNum + 2];
		fRainbowColor[i + 3] = rainbowColorScheme[segNum];
		fRainbowColor[i + 4] = rainbowColorScheme[segNum + 1];
		fRainbowColor[i + 5] = rainbowColorScheme[segNum + 2];
	}

	// Array with sample 6-pointed star vertices
	float radius = 0.2f; // star radius
	float star6p[star6p_icount] = {
		0.0f, radius, 0.0f,
		-radius, -radius / 2, 0.0f,
		radius, -radius / 2, 0.0f,
		0.0f, -radius, 0.0f,
		-radius, radius / 2, 0.0f,
		radius, radius / 2, 0.0f,
	};

	// Trying to normalize the size to fit the resolution of 16 : 9
	for (int i = 0; i < star6p_icount; ++i) {
		if ((i - 1) % 3 == 0) {
			star6p[i] *= 16 / 9.0f;
		}
	}

	// Setup vertices of the first star (and moving it to the left)
	// and of the second star (and moving it to the right)
	for (int i = 0; i < star6p_icount; ++i) {
		fStar1[i] = star6p[i];
		fStar2[i] = star6p[i];
		if (i % 3 == 0) { // move every x coordinate
			fStar1[i] -= 0.3f;
			fStar2[i] += 0.3f;
		}
	}

	// Setup colors of the first and second stars
	for (int i = 0; i < star6p_icount; i += 3) {
		fStar1Color[i] = 0.1f;
		fStar1Color[i + 1] = 0.3f;
		fStar1Color[i + 2] = 0.9f;

		fStar2Color[i] = 0.1f;
		fStar2Color[i + 1] = 0.3f;
		fStar2Color[i + 2] = 0.9f;
	}

	// Array with sample 5-pointed star vertices
	float star5p[star5p_icount] = {
		0.0f, 2 * radius, 0.0f,
		radius, -4 * radius, 0.0f,
		-1.7 * radius, 0.0f, 0.0f,
		1.7 * radius, 0.0f, 0.0f,
		-radius, -4 * radius, 0.0f
	};

	// Setup vertices of the third star (and moving up a bit)
	for (int i = 0; i < star5p_icount; ++i) {
		fStar3[i] = star5p[i];
		if ((i - 1) % 3 == 0) { // move every y coordinate
			fStar3[i] += 0.2f;
		}
	}

	// Setup colors of the third star
	for (int i = 0; i < star5p_icount; i += 3) {
		fStar3Color[i] = 1.0f;
		fStar3Color[i + 1] = 0.0f;
		fStar3Color[i + 2] = 0.0f;
	}
}