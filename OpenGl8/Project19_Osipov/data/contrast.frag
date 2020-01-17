// NUMPAD1
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

// контрастность
vec3 filter(in vec2 texcoord)
{	
	vec3 rgb = texture(colorTexture, vec2(texcoord.x, texcoord.y)).rgb;
	float factor = (param1/100. + 1.) / (1. - param1/100.);
	vec3 newrgb = rgb;
	newrgb.x = factor * (rgb.x - 0.5) + 0.5;
	newrgb.y = factor * (rgb.y - 0.5) + 0.5;
	newrgb.z = factor * (rgb.z - 0.5) + 0.5;
	return newrgb;
}

void main(void)
{
	// применяем фильтр к части экрана
	vec3 texel = Vert.texcoord.x < filterPart / 100.0 ? filter(Vert.texcoord)
		: texture(colorTexture, Vert.texcoord).rgb;

	color = vec4(texel, 1.0);
}
