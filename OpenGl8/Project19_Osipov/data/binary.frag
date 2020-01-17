// NUMPAD2
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

// бинаризация
vec3 filter(in vec2 texcoord)
{
	vec3 col = texture(colorTexture, texcoord).rgb;
	vec3 res = col;
	float sum = col.x + col.y + col.z;
	if (sum < (1-param1/100.)) 
	{
		res = vec3(0.,0.,0.);
	}
	else 
	{
		res = vec3(1.,1.,1.);
	}
	return res;
}

void main(void)
{
	// применяем фильтр к части экрана
	vec3 texel = Vert.texcoord.x < filterPart / 100.0 ? filter(Vert.texcoord)
		: texture(colorTexture, Vert.texcoord).rgb;

	color = vec4(texel, 1.0);
}
