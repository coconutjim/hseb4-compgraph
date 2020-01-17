// вывод изображения без обработки (F1)
// текстуры
uniform sampler2D colorTexture, depthTexture;
// часть экрана, к которой нужно применить фильтр
uniform int filterPart;
// параметры фильтра 
uniform int param1;
uniform int param2;

// параметры полученные из вершинного шейдера
in Vertex
{
	vec2 texcoord;
} Vert;

layout(location = FRAG_OUTPUT0) out vec4 color;

void main(void)
{
	// вычислим итоговый цвет пикселя на экране с учетом текстуры
	color = texture(colorTexture, Vert.texcoord);
}
