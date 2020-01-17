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

#include "vertexBufferObject.h"

CVertexBufferObject::CVertexBufferObject()
{
	bDataUploaded = false;
	uiBuffer = 0;
}

/*-----------------------------------------------

Name:	CreateVBO

Params:	a_iSize - initial size of buffer

Result:	Creates vertex buffer object.

/*---------------------------------------------*/

void CVertexBufferObject::CreateVBO(int a_iSize)
{
	glGenBuffers(1, &uiBuffer);
	data.reserve(a_iSize);
	iSize = a_iSize;
	iCurrentSize = 0;
}

/*-----------------------------------------------

Name:	DeleteVBO

Params:	none

Result:	Releases VBO and frees all memory.

/*---------------------------------------------*/

void CVertexBufferObject::DeleteVBO()
{
	glDeleteBuffers(1, &uiBuffer);
	bDataUploaded = false;
	data.clear();
}

/*-----------------------------------------------

Name:	mapBufferToMemory

Params:	iUsageHint - GL_READ_ONLY, GL_WRITE_ONLY...

Result:	Maps whole buffer data to memory and
		returns pointer to data.

/*---------------------------------------------*/

void* CVertexBufferObject::MapBufferToMemory(int iUsageHint)
{
	if(!bDataUploaded)return NULL;
	void* ptrRes = glMapBuffer(iBufferType, iUsageHint);
	return ptrRes;
}

/*-----------------------------------------------

Name:	MapSubBufferToMemory

Params:	iUsageHint - GL_READ_ONLY, GL_WRITE_ONLY...
		uiOffset - data offset (from where should
					data be mapped).
		uiLength - length of data

Result:	Maps specified part of buffer to memory.

/*---------------------------------------------*/

void* CVertexBufferObject::MapSubBufferToMemory(int iUsageHint, UINT uiOffset, UINT uiLength)
{
	if(!bDataUploaded)return NULL;
	void* ptrRes = glMapBufferRange(iBufferType, uiOffset, uiLength, iUsageHint);
	return ptrRes;
}

/*-----------------------------------------------

Name:	UnmapBuffer

Params:	none

Result:	Unmaps previously mapped buffer.

/*---------------------------------------------*/

void CVertexBufferObject::UnmapBuffer()
{
	glUnmapBuffer(iBufferType);
}

/*-----------------------------------------------

Name:	BindVBO

Params:	a_iBufferType - buffer type (GL_ARRAY_BUFFER, ...)

Result:	Binds this VBO.

/*---------------------------------------------*/

void CVertexBufferObject::BindVBO(int a_iBufferType)
{
	iBufferType = a_iBufferType;
	glBindBuffer(iBufferType, uiBuffer);
}

/*-----------------------------------------------

Name:	UploadDataToGPU

Params:	iUsageHint - GL_STATIC_DRAW, GL_DYNAMIC_DRAW...

Result:	Sends data to GPU.

/*---------------------------------------------*/

void CVertexBufferObject::UploadDataToGPU(int iDrawingHint)
{
	glBufferData(iBufferType, data.size(), &data[0], iDrawingHint);
	bDataUploaded = true;
	data.clear();
}

/*-----------------------------------------------

Name:	AddData

Params:	ptrData - pointer to arbitrary data
		uiDataSize - data size in bytes

Result:	Adds arbitrary data to VBO.

/*---------------------------------------------*/

void CVertexBufferObject::AddData(void* ptrData, UINT uiDataSize)
{
	data.insert(data.end(), (BYTE*)ptrData, (BYTE*)ptrData+uiDataSize);
	iCurrentSize += uiDataSize;
}

/*-----------------------------------------------

Name:	GetDataPointer

Params:	none

Result:	Returns data pointer (only before uploading).

/*---------------------------------------------*/

void* CVertexBufferObject::GetDataPointer()
{
	if(bDataUploaded)return NULL;
	return (void*)data[0];
}

/*-----------------------------------------------

Name:	GetBufferID

Params:	none

Result:	Returns VBO ID.

/*---------------------------------------------*/

UINT CVertexBufferObject::GetBufferID()
{
	return uiBuffer;
}

/*-----------------------------------------------

Name:	GetCurrentSize

Params:	none

Result: Returns size of data that has been added to
		the buffer object.

/*---------------------------------------------*/

int CVertexBufferObject::GetCurrentSize()
{
	return iCurrentSize;
}