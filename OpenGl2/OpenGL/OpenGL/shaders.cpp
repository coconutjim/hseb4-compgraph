/*
������ ��� ��������
������ 14. OpenGL2
Visual Studio 2013
17.02.2016
��������� ��� �������, ��� �������������� � ���������������.
���������� ���, ��������, ������� � ��� (� ������� ����������).
����������:
1) ������������� ������ ������ ������������� - ������������� ������� ������ ���������� ����� ������ � ��������� ������:
a - �������� �����
d - �������� ������
w - �������� �����
s - �������� ����
z - �������� ������
x - �������� �����
������� ������ - �������� � ���� �������
������� ����� - �������� � ������ �������
������� ����� - ���������� ������
������� ���� - ���������� ������
�������:
���������� ���� - � + ������� �����
����� ���� ������ - t + d
2) ��������� ������ ���������� ����������� ����� - ������� r, ��� �� �������� � �� ���������� ����� ������
3) ��� �������� ������ - ����� ctrl + ������� ������ � �����, ��� �����������/��������� ������ - ����� ctrl + ������� ����� � ����
*/
#pragma warning(disable:4996)

#include "common_header.h"

#include "shaders.h"

CShader::CShader()
{
	bLoaded = false;
}

// Loads and compiles shader.
// sFile - path to a file
// a_iType - type of shader(fragment, vertex, geometry)
bool CShader::loadShader(string sFile, int a_iType)
{
	FILE* fp = fopen(sFile.c_str(), "rt");
	if(!fp)return false;

	// Get all lines from a file

	vector<string> sLines;
	char sLine[255];
	while(fgets(sLine, 255, fp))sLines.push_back(sLine);
	fclose(fp);

	const char** sProgram = new const char*[ESZ(sLines)];
	FOR(i, ESZ(sLines))sProgram[i] = sLines[i].c_str();
	
	uiShader = glCreateShader(a_iType);

	glShaderSource(uiShader, ESZ(sLines), sProgram, NULL);
	glCompileShader(uiShader);

	delete[] sProgram;

	int iCompilationStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iCompilationStatus);

	if(iCompilationStatus == GL_FALSE)return false;
	iType = a_iType;
	bLoaded = true;

	return 1;
}

// True if shader was loaded and compiled.
bool CShader::isLoaded()
{
	return bLoaded;
}

// Returns ID of a generated shader.
UINT CShader::getShaderID()
{
	return uiShader;
}

// Deletes shader and frees memory in GPU.
void CShader::deleteShader()
{
	if(!isLoaded())return;
	bLoaded = false;
	glDeleteShader(uiShader);
}

CShaderProgram::CShaderProgram()
{
	bLinked = false;
}

// Creates a new program.
void CShaderProgram::createProgram()
{
	uiProgram = glCreateProgram();
}

// Adds a shader (like source file) to a program, but only compiled one.
// sShader - shader to add
bool CShaderProgram::addShaderToProgram(CShader* shShader)
{
	if(!shShader->isLoaded())return false;

	glAttachShader(uiProgram, shShader->getShaderID());

	return true;
}

// Performs final linkage of OpenGL program.
bool CShaderProgram::linkProgram()
{
	glLinkProgram(uiProgram);
	int iLinkStatus;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &iLinkStatus);
	bLinked = iLinkStatus == GL_TRUE;
	return bLinked;
}

// Deletes program and frees memory on GPU.
void CShaderProgram::deleteProgram()
{
	if(!bLinked)return;
	bLinked = false;
	glDeleteProgram(uiProgram);
}

// Tells OpenGL to use this program.
void CShaderProgram::useProgram()
{
	if(bLinked)glUseProgram(uiProgram);
}

// Returns OpenGL generated shader program ID.
UINT CShaderProgram::getProgramID()
{
	return uiProgram;
}