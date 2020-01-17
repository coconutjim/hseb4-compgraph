/*
Осипов Лев Игоревич
OpenGL. Проект 16.
Visual Studio 2013
06.03.2016
Сделано:
1) Объекты сгенерированы раличными способами (куб - индексно, торы - процедурно, Дедпулы и Тор - используя меши)
2) Реализовано три дополнительных источников освещения - белый направленный, синий точечный и красный прожектор (последние 2 видны слева от торов)
3) Встроен собственный скайбокс
4) Реализовано три типа тумана (перелючение - клавиша f) и регулирование его параметров стрелками
5) Реализовано много объектов с движением в рамках композиции "Деревня Дедпулов, которую охраняет Тор"
Код закомментирован.
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