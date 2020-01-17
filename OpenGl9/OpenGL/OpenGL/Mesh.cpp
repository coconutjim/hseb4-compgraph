/*
Осипов Лев Игоревич
Проект 19. OpenGL8
Visual Studio 2013
24.03.2016
Сделано:
1) реализовано 7 дополнительных фильтров:
отражение, искажение по синусу, эффект закручивания, эффект линзы, эффект волны, контраст, бинаризация
(включение - клавиши F8, F9, F11, NUMPAD0, NUMPAD1, NUMPAD2 соответственно)
2) Реализован Canny - NUMPAD3
3) реализован контроль области применения фильтров - клавиши Q и E
4) реализовано управление параметрами фильтров, как существующих, так и добавленных (но не всех, конечно, некоторые не нуждаются в конфигурации)
Управление реализовано стрелками. у некоторых фильтров регулируется один параметр стрелками влево и вправо, у некоторых два, и тогда
нужно работать еще и стрелками вверх и вниз, а у Canny еще больше нюансов
Список регулируемых фильтров:
	1. F5 - размытие - стрелки влево и вправо
	2. F6 - рельеф - стрелки влево и вправо
	3. F7 - абберация - стрелки влево и вправо
	3. F9 - искажение по синусу - стрелки влево и вправо
	4. F10 - закручивание - стрелки влево и вправо (радиус) и стрелки вверх и вниз (угол)
	5. F11 - линза - стрелки влево и вправо (радиус) и стрелки вверх и вниз (увеличение)
	6. NUMPAD0 - волна - стрелки влево и вправо (длина волны) и стрелки вверх и вниз (смещение)
	7. NUMPAD1 - контрастность - стрелки влево и вправо
	8. NUMPAD2 - бинаризация - стрелки влево и вправо
	9. NUMPAD3 - Canny - стрелки влево и вправо (степень размытия по Гауссу), стрелки вверх и вниз (контроль пороговой фильтрации).
		Также клавишей С можно контролировать этапы применения фильтра Canny - либо полный фильтр, либо только Гаусс с обесцвечиванием (без Собеля)
5) код закомментирован
*/
#include "Mesh.h"

struct vertex
{
	float3 position;
	float2 texcoord;
	float3 normal;
};

void MeshCreate(Mesh &mesh, const vec3 &position, const vertex *vertices, uint32_t vcount,
	const uint32_t *indices, uint32_t icount)
{
	ASSERT(vertices);
	ASSERT(indices);

	mesh.vcount = vcount;
	mesh.icount = icount;

	mesh.position = position;
	mesh.rotation = mat3_identity;

	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	glGenBuffers(2, mesh.vbo);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vcount * sizeof(vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount * sizeof(uint32_t), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(VERT_POSITION, 3, GL_FLOAT, GL_FALSE,
		sizeof(vertex), GL_OFFSET(0));
	glEnableVertexAttribArray(VERT_POSITION);

	glVertexAttribPointer(VERT_TEXCOORD, 2, GL_FLOAT, GL_FALSE,
		sizeof(vertex), GL_OFFSET(sizeof(float3)));
	glEnableVertexAttribArray(VERT_TEXCOORD);

	glVertexAttribPointer(VERT_NORMAL, 3, GL_FLOAT, GL_FALSE,
		sizeof(vertex), GL_OFFSET(sizeof(float3) + sizeof(float2)));
	glEnableVertexAttribArray(VERT_NORMAL);

	OPENGL_CHECK_FOR_ERRORS();
}

void MeshDestroy(Mesh &mesh)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, mesh.vbo);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &mesh.vao);
}

void MeshCreateQuad(Mesh &mesh, const vec3 &position, float size)
{
	#include "models/quad.h"
	return MeshCreate(mesh, position, vertices, vcount, indices, icount);
}

void MeshCreatePlane(Mesh &mesh, const vec3 &position, float size)
{
	#include "models/plane.h"
	return MeshCreate(mesh, position, vertices, vcount, indices, icount);
}

void MeshCreateCube(Mesh &mesh, const vec3 &position, float size)
{
	#include "models/cube.h"
	return MeshCreate(mesh, position, vertices, vcount, indices, icount);
}

void MeshCreateSphere(Mesh &mesh, const vec3 &position, float size)
{
	#include "models/sphere.h"
	return MeshCreate(mesh, position, vertices, vcount, indices, icount);
}

void MeshCreateTorus(Mesh &mesh, const vec3 &position, float size)
{
	#include "models/torus.h"
	return MeshCreate(mesh, position, vertices, vcount, indices, icount);
}

const mat4 MeshGetModelMatrix(const Mesh &mesh)
{
	return GLTranslation(mesh.position) * mat4(mesh.rotation);
}

void MeshRender(const Mesh &mesh)
{
	glBindVertexArray(mesh.vao);
	glDrawElements(GL_TRIANGLES, mesh.icount, GL_UNSIGNED_INT, NULL);
}
