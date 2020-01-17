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
#pragma once

//Wraps OpenGL shader loading and compiling.
class CShader
{
public:
	bool LoadShader(string sFile, int a_iType);
	void DeleteShader();

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

	CShaderProgram();

private:
	UINT uiProgram; // ID of program
	bool bLinked; // Whether program was linked and is ready to use
};