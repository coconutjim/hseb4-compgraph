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
#pragma once

// Wraps OpenGL shader loading and compiling.
class CShader
{
public:
	bool LoadShader(string sFile, int a_iType);
	void DeleteShader();

	bool GetLinesFromFile(string sFile, bool bIncludePart, vector<string>* vResult);

	bool IsLoaded();
	UINT GetShaderID();

	CShader();

private:
	UINT uiShader; // ID of shader
	int iType; // GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
	bool bLoaded; // Whether shader was loaded and compiled
};

// Wraps OpenGL shader program and make its usage easy.
class CShaderProgram
{
public:
	void CreateProgram();
	void DeleteProgram();

	bool AddShaderToProgram(CShader* shShader);
	bool LinkProgram();

	void UseProgram();

	UINT GetProgramID();

	// Setting vectors
	void SetUniform(string sName, glm::vec2* vVectors, int iCount = 1);
	void SetUniform(string sName, const glm::vec2 vVector);
	void SetUniform(string sName, glm::vec3* vVectors, int iCount = 1);
	void SetUniform(string sName, const glm::vec3 vVector);
	void SetUniform(string sName, glm::vec4* vVectors, int iCount = 1);
	void SetUniform(string sName, const glm::vec4 &vVector);

	// Setting floats
	void SetUniform(string sName, float* fValues, int iCount = 1);
	void SetUniform(string sName, const float fValue);

	// Setting 3x3 matrices
	void SetUniform(string sName, glm::mat3* mMatrices, int iCount = 1);
	void SetUniform(string sName, const glm::mat3 mMatrix);

	// Setting 4x4 matrices
	void SetUniform(string sName, glm::mat4* mMatrices, int iCount = 1);
	void SetUniform(string sName, const glm::mat4 &mMatrix);

	// Setting integers
	void SetUniform(string sName, int* iValues, int iCount = 1);
	void SetUniform(string sName, const int iValue);

	CShaderProgram();

private:
	UINT uiProgram; // ID of program
	bool bLinked; // Whether program was linked and is ready to use
};

bool PrepareShaderPrograms();

#define NUMSHADERS 14

extern CShader shShaders[NUMSHADERS];
extern CShaderProgram spMain, spColor, spShadowMapper, spShadowMapRender, spSkybox;