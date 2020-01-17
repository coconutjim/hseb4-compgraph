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
#include "common_header.h"

#include "vertexBufferObject.h"

CVertexBufferObject::CVertexBufferObject()
{
	bDataUploaded = false;
}

// Creates vertex buffer object.
// a_iSize - initial size of buffer
void CVertexBufferObject::createVBO(int a_iSize)
{
	glGenBuffers(1, &uiBuffer);
	data.reserve(a_iSize);
	iSize = a_iSize;
}

// Releases VBO and frees all memory.
void CVertexBufferObject::releaseVBO()
{
	glDeleteBuffers(1, &uiBuffer);
	bDataUploaded = false;
	data.clear();
}

// Maps whole buffer data to memory and returns pointer to data.
// iUsageHint - GL_READ_ONLY, GL_WRITE_ONLY...
void* CVertexBufferObject::mapBufferToMemory(int iUsageHint)
{
	if(!bDataUploaded)return NULL;
	void* ptrRes = glMapBuffer(iBufferType, iUsageHint);
	return ptrRes;
}

// Maps specified part of buffer to memory.
// iUsageHint - GL_READ_ONLY, GL_WRITE_ONLY...
// uiOffset - data offset(from where should data be mapped).
// uiLength - length of data
void* CVertexBufferObject::mapSubBufferToMemory(int iUsageHint, UINT uiOffset, UINT uiLength)
{
	if(!bDataUploaded)return NULL;
	void* ptrRes = glMapBufferRange(iBufferType, uiOffset, uiLength, iUsageHint);
	return ptrRes;
}

// Unmaps previously mapped buffer.
void CVertexBufferObject::unmapBuffer()
{
	glUnmapBuffer(iBufferType);
}

// Binds this VBO.
// a_iBufferType - buffer type (GL_ARRAY_BUFFER, ...)
void CVertexBufferObject::bindVBO(int a_iBufferType)
{
	iBufferType = a_iBufferType;
	glBindBuffer(iBufferType, uiBuffer);
}

// Sends data to GPU.
// iUsageHint - GL_STATIC_DRAW, GL_DYNAMIC_DRAW...
void CVertexBufferObject::uploadDataToGPU(int iDrawingHint)
{
	glBufferData(iBufferType, data.size(), &data[0], iDrawingHint);
	bDataUploaded = true;
	data.clear();
}

// Adds arbitrary data to VBO.
// ptrData - pointer to arbitrary data uiDataSize - data size in bytes
void CVertexBufferObject::addData(void* ptrData, UINT uiDataSize)
{
	data.insert(data.end(), (BYTE*)ptrData, (BYTE*)ptrData+uiDataSize);
}

// Returns data pointer (only before uplading).
void* CVertexBufferObject::getDataPointer()
{
	if(bDataUploaded)return NULL;
	return (void*)data[0];
}

// Returns VBO ID.
UINT CVertexBufferObject::getBuffer()
{
	return uiBuffer;
}


