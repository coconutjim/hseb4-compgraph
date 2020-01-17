// F10
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

// эффект закручивания
vec3 filter(in vec2 texcoord)
{	
	ivec2 ires = textureSize(colorTexture, 0);
	float Res = float(ires.s);
	vec2 st = texcoord;
	float Radius = Res * param1/100.;
	vec2 xy = Res * st;
	vec2 dxy = xy - Res/2.;
	float r = length(dxy);
	float beta = atan(dxy.y, dxy.x) + radians(float(param2))*(Radius - r)/Radius;
	vec2 xy1 = xy;
	if (r<=Radius)
	{
		xy1 = Res/2. + r * vec2(cos(beta), sin(beta));
	}
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
