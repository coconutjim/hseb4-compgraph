// F11
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

// эффект линзы
vec3 filter(in vec2 texcoord)
{	
	ivec2 ires = textureSize(colorTexture, 0);
	float Res = float(ires.s);
	vec2 st = texcoord;
	float Radius = Res * param1/100.;
	vec2 xy = Res * st;
	vec2 dxy = xy - Res/2.;
	float r = length(dxy);
	float z = sqrt(Radius * Radius - r * r);
	float val = 1.3 + param2/100.;
	float betax = (1 - 1/val) * asin(dxy.x/sqrt(dxy.x*dxy.x+z*z));
	float betay = (1 - 1/val) * asin(dxy.y/sqrt(dxy.y*dxy.y+z*z));
	vec2 xy1 = xy;
	if (r<=Radius)
	{
		xy1 = z * vec2(tan(betax), tan(betay));
	}
	else 
	{
		xy1 = vec2(0.0, 0.0);
	}
	xy1 = xy - xy1;
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
