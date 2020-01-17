// F7
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

vec3 filter(in vec2 texcoord)
{
	int val = int(param1/20.0);
	return vec3(
		textureOffset(colorTexture, texcoord, ivec2(val,val)).r,
		texture(colorTexture, texcoord).g,
		textureOffset(colorTexture, texcoord, ivec2(val*2,val*2)).b
	);
}

void main(void)
{
	// применяем фильтр к части экрана
	vec3 texel = Vert.texcoord.x < filterPart / 100.0 ? filter(Vert.texcoord)
		: texture(colorTexture, Vert.texcoord).rgb;

	color = vec4(texel, 1.0);
}
