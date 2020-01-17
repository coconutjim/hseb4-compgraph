/*
������ ��� ��������
������ 14. OpenGL3
Visual Studio 2013
25.02.2016
�����������:
1) � ������������ ���������� - ����������� �������� ������ � �������� ��������� ��������� (������� p � l ��������������)
2) ����������� ��� ����� ��������� - ��������, ��������� � ������������. ���������/���������� - ������� 1, 2 � 3 ��������������
3) ����������� �������� ��������� ��������� � ����������. ���������/���������� - ������� 4 � 5 ��������������
4) ����������� ������������ ��������� ����� ���������� ������������� ���������. ��������� - ���������� - ������� 6
5) ��� ���������������
*/
#pragma once

// Wraps OpenGL vertex buffer object.
class CVertexBufferObject
{
public:
	void CreateVBO(int a_iSize = 0);
	void DeleteVBO();

	void* MapBufferToMemory(int iUsageHint);
	void* MapSubBufferToMemory(int iUsageHint, UINT uiOffset, UINT uiLength);
	void UnmapBuffer();

	void BindVBO(int a_iBufferType = GL_ARRAY_BUFFER);
	void UploadDataToGPU(int iUsageHint);
	
	void AddData(void* ptrData, UINT uiDataSize);

	void* GetDataPointer();
	UINT GetBufferID();

	CVertexBufferObject();

private:
	UINT uiBuffer;
	int iSize;
	int iBufferType;
	vector<BYTE> data;

	bool bDataUploaded;
};