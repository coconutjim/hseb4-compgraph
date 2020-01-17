// F12
const float PI = 3.14159265;
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

// эффект волны
vec3 filter(in vec2 texcoord)
{	
	ivec2 ires = textureSize(colorTexture, 0);
	float Res = float(ires.s);
	vec2 st = texcoord;
	float Radius = Res * .5;
	vec2 xy = Res * st;
	vec2 xy1 = xy;
	float ax = 5 + param2 / 10.;
	float ay = ax * 1.5;
	float tetax = 70. + param1;
	float tetay = tetax * 2;
	xy1 = xy + vec2(ax * sin(2 * PI * xy.y/tetax), ay * sin(2 * PI * xy.x/tetay));
	st = xy1/Res;
	return (texture(colorTexture, st).rgb);
}

void main(void)
{
	// применяем фильтр к части экрана
	vec3 texel = Vert.texcoord.x < filterPart / 100.0 ? filter(Vert.texcoord)
		: texture(colorTexture, Vert.texcoord).rgb;

	color = vec4(texel, 1.0);
}
