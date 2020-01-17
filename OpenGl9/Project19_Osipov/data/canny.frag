// NUMPAD3
// текстуры
uniform sampler2D colorTexture, depthTexture;
// часть экрана, к которой нужно применить фильтр
uniform int filterPart;
// параметры фильтра 
uniform int param1;
uniform int param2;
// показывать ли весь Canny
uniform int fullCanny;

// параметры, полученные из вершинного шейдера
in Vertex
{
	vec2 texcoord;
} Vert;

layout(location = FRAG_OUTPUT0) out vec4 color;

// Ядра свертки
#define KERNEL_SIZE_GAUSS 25
#define KERNEL_SIZE_SOBEL 9

const float kernel_gauss[KERNEL_SIZE_GAUSS] = float[](
	2.0, 4.0, 5.0, 4.0, 2.0,
	4.0, 9.0, 12.0, 9.0, 4.0,
	5.0, 12.0, 15.0, 12.0, 5.0,
	2.0, 4.0, 5.0, 4.0, 2.0,
	4.0, 9.0, 12.0, 9.0, 4.0
);

const float kernel_sobel_hor[KERNEL_SIZE_SOBEL] = float[](
	-3.0, 0.0 , 3.0,
	-10.0, 0.0, 10.0,
	-3.0, 0.0, 3.0
);

const float kernel_sobel_vert[KERNEL_SIZE_SOBEL] = float[](
	-3.0, -10.0 , -3.0,
	0.0, 0.0, 0.0,
	3.0, 10.0, 3.0
);

const vec2 offset_sobel[KERNEL_SIZE_SOBEL] = vec2[](
	vec2(-1.0,-1.0), vec2( 0.0,-1.0), vec2( 1.0,-1.0),
	vec2(-1.0, 0.0), vec2( 0.0, 0.0), vec2( 1.0, 0.0),
	vec2(-1.0, 1.0), vec2( 0.0, 1.0), vec2( 1.0, 1.0)
);

// оценка яркости значения в формате RGB 
const vec3 lum = vec3(0.2126, 0.7152, 0.0722); 
float luminance( vec3 color ) {return dot(lum, color);}

float mean(vec4 vec) {return (vec.x+vec.y+vec.z)/3.;}

vec3 filter(in vec2 texcoord)
{
	// Gauss
	float val = param1 / 10.;
	
	vec2 offset_gauss[KERNEL_SIZE_GAUSS] = vec2[](
		vec2(-2.0*val,-2.0*val), vec2(-1.0*val,-2.0*val), vec2(0.0,-2.0*val), vec2(1.0*val,-2.0*val), vec2(2.0*val,-2.0*val),
		vec2(-2.0*val,-1.0*val), vec2(-1.0*val,-1.0*val), vec2(0.0,-1.0*val), vec2(1.0*val,-1.0*val), vec2(2.0*val,-1.0*val),
		vec2(-2.0*val, 0.0), vec2(-1.0*val, 0.0), vec2(0.0, 0.0), vec2(1.0*val, 0.0), vec2(2.0*val, 0.0),
		vec2(-2.0*val, 1.0*val), vec2(-1.0*val, 1.0*val), vec2(0.0, 1.0*val), vec2(1.0*val, 1.0*val), vec2(2.0*val, 1.0*val),
		vec2(-2.0*val, 2.0*val), vec2(-1.0*val, 2.0*val), vec2(0.0, 2.0*val), vec2(1.0*val, 2.0*val), vec2(2.0*val, 2.0*val)
	);
	
	vec2 pstep = vec2(1.0) / vec2(textureSize(colorTexture, 0));
	float res[9] = float[](0,0,0,0,0,0,0,0,0);
	
	for (int i = 0; i < KERNEL_SIZE_SOBEL; ++i) {
		for (int j = 0; j < KERNEL_SIZE_GAUSS; j++){
			res[i] += mean(texture(colorTexture, texcoord + (offset_sobel[i] + offset_gauss[j]) * pstep)) * kernel_gauss[j];
		}
		res[i] /= 159.0;
	}
	
	if (fullCanny == 1) {
		float sx;
		float sy;
		for (int i = 0; i < KERNEL_SIZE_SOBEL; ++i) {
			sx += res[i] * kernel_sobel_hor[i];
			sy += res[i] * kernel_sobel_vert[i];
		}
		
		float dist = sx*sx+sy*sy;
		if (dist > param2/100.) {
			return vec3(1.0);
		}
		else {
			return vec3(0.0);
		}
	}
	else {
		return vec3(res[4]);
	}
}

void main(void)
{
	// применяем фильтр к части экрана
	vec3 texel = Vert.texcoord.x < filterPart / 100.0 ? filter(Vert.texcoord)
		: texture(colorTexture, Vert.texcoord).rgb;

	color = vec4(texel, 1.0);
}
