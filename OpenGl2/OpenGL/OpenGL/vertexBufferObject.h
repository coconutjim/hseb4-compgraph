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
#pragma once

// Wraps OpenGL vertex buffer object.
class CVertexBufferObject
{
public:
	void createVBO(int a_iSize = 0);
	void releaseVBO();

	void* mapBufferToMemory(int iUsageHint);
	void* mapSubBufferToMemory(int iUsageHint, UINT uiOffset, UINT uiLength);
	void unmapBuffer();

	void bindVBO(int a_iBufferType = GL_ARRAY_BUFFER);
	void uploadDataToGPU(int iUsageHint);
	
	void addData(void* ptrData, UINT uiDataSize);

	void* getDataPointer();
	UINT getBuffer();

	CVertexBufferObject();

private:
	UINT uiBuffer;
	int iSize;
	int iBufferType;
	vector<BYTE> data;

	bool bDataUploaded;
};