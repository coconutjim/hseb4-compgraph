/*
Осипов Лев Игоревич
OpenGL. Проект 16-2.
Visual Studio 2013
23.03.2016
Сделано:
1) Дом и три Дедпула по мешам, скайбокс, три источника освещения (видны на доме)
2) Фотокуб с различными картинками на всех гранях, картинки перетекают в другие (и обратно)
Перетекание осуществляется в двух режимах - автоматическом и ручном (по умолчанию автоматический)
Переключение режима перетекания - клавиша f, управление в ручном режиме - клавиши q и e
3) Три Дедпула реализованы по-разному:
	1. Первый Дедпул - просто Дедпул.
	2. Второй Дедпул реализован с отблесками (как будто сделан из металла).
		Реализовано управление отблесками: стрелки влево и вправо - площадь отблесков, стрелки вниз и вверх - "сила" отблесков
	3. Третий Дедпул - это просто Дедпул с деревянной текстурой (подключил в mtl другую картинку)
Код закомментирован.
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

#define NUMSHADERS 7

extern CShader shShaders[NUMSHADERS];
extern CShaderProgram spMain, spColor;