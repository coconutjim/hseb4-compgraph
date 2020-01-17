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
#pragma once

enum ETextureFiltering
{
	TEXTURE_FILTER_MAG_NEAREST = 0, // Nearest criterion for magnification
	TEXTURE_FILTER_MAG_BILINEAR, // Bilinear criterion for magnification
	TEXTURE_FILTER_MIN_NEAREST, // Nearest criterion for minification
	TEXTURE_FILTER_MIN_BILINEAR, // Bilinear criterion for minification
	TEXTURE_FILTER_MIN_NEAREST_MIPMAP, // Nearest criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_BILINEAR_MIPMAP, // Bilinear criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_TRILINEAR, // Bilinear criterion for minification on two closest mipmaps, then averaged
};

// Wraps OpenGL texture object and performs their loading.
class CTexture
{
public:
	bool loadTexture2D(string a_sPath, bool bGenerateMipMaps = false);
	void bindTexture(int iTextureUnit = 0);

	void setFiltering(int a_tfMagnification, int a_tfMinification);

	int getMinificationFilter();
	int getMagnificationFilter();

	void releaseTexture();

	CTexture();
private:
	int iWidth, iHeight, iBPP; // Texture width, height, and bytes per pixel
	UINT uiTexture; // Texture name
	UINT uiSampler; // Sampler name
	bool bMipMapsGenerated;

	int tfMinification, tfMagnification;

	string sPath;
};

