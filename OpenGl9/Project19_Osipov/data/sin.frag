// F9
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

// искажение по синусу
vec3 filter(in vec2 texcoord)
{	
	vec2 st = texcoord;
	vec2 xy = st;
	xy = 2.*xy-1;
	xy += param1/100. * sin(PI*xy);
	st = (xy+1.)/2.;
	return (texture(colorTexture, st).rgb);
}

void main(void)
{
	// применяем фильтр к части экрана
	vec3 texel = Vert.texcoord.x < filterPart / 100.0 ? filter(Vert.texcoord)
		: texture(colorTexture, Vert.texcoord).rgb;

	color = vec4(texel, 1.0);
}
