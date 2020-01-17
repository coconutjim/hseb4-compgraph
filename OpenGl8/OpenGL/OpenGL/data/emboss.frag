// F6
// текстуры цвета (используется для эффектов), глубины (не используется для эффектов)
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

// ядро свертки
#define KERNEL_SIZE 9

const float kernel[KERNEL_SIZE] = float[](
	2.0,  0.0,  0.0,
	0.0, -1.0,  0.0,
	0.0,  0.0, -1.0
);

const vec3 factor = vec3(0.27, 0.67, 0.06);

vec3 filter(in vec2 texcoord)
{
	float val = param1 / 20.;
	vec2 offset[KERNEL_SIZE] = vec2[](
		vec2(-val,-val), vec2( 0.0,-val), vec2( val,-val),
		vec2(-val, 0.0), vec2( 0.0, 0.0), vec2( val, 0.0),
		vec2(-val, val), vec2( 0.0, val), vec2( val, val)
	);
	
	vec2 pstep = vec2(1.0) / vec2(textureSize(colorTexture, 0));
	vec4 res   = vec4(0.5);

	for (int i = 0; i < KERNEL_SIZE; ++i)
		res += texture(colorTexture, texcoord + offset[i] * pstep) * kernel[i];

	return vec3(dot(factor, vec3(res)));
}

void main(void)
{
	// применяем фильтр к части экрана
	vec3 texel = Vert.texcoord.x < filterPart / 100.0 ? filter(Vert.texcoord)
		: texture(colorTexture, Vert.texcoord).rgb;

	color = vec4(texel, 1.0);
}
