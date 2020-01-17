// F5
// текстуры
uniform sampler2D colorTexture, depthTexture;
// часть экрана, к которой нужно применить фильтр
uniform int filterPart;
// параметры фильтра 
uniform int param1;
uniform int param2;

// параметры, полученные из вершинного шейдера
in Vertex
{
	vec2 texcoord;
} Vert;

layout(location = FRAG_OUTPUT0) out vec4 color;

// Ядро свертки
#define KERNEL_SIZE 9

const float kernel[KERNEL_SIZE] = float[](
	0.0625, 0.1250, 0.0625,
	0.1250, 0.2500, 0.1250,
	0.0625, 0.1250, 0.0625
);

vec3 filter(in vec2 texcoord)
{
	float val = param1 / 10.;
	vec2 offset[KERNEL_SIZE] = vec2[](
		vec2(-val,-val), vec2( 0.0,-val), vec2( val,-val),
		vec2(-val, 0.0), vec2( 0.0, 0.0), vec2( val, 0.0),
		vec2(-val, val), vec2( 0.0, val), vec2( val, val)
	);

	vec2 pstep = vec2(1.0) / vec2(textureSize(colorTexture, 0));
	vec4 res   = vec4(0.0);

	for (int i = 0; i < KERNEL_SIZE; ++i)
		res += texture(colorTexture, texcoord + offset[i] * pstep) * kernel[i];

	return vec3(res);
}

void main(void)
{
	// применяем фильтр к части экрана
	vec3 texel = Vert.texcoord.x < filterPart / 100.0 ? filter(Vert.texcoord)
		: texture(colorTexture, Vert.texcoord).rgb;

	color = vec4(texel, 1.0);
}
