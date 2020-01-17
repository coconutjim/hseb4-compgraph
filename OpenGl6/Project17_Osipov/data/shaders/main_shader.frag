#version 330

smooth in vec2 vTexCoord;
smooth in vec3 vNormal;
smooth in vec4 vEyeSpacePos;
smooth in vec3 vWorldPos;
out vec4 outputColor;

uniform sampler2D gSampler;
uniform vec4 vColor;

#include "dirLight.frag"
#include "pointLight.frag"
uniform DirectionalLight sunLight;
uniform PointLight myPointLight1;
uniform PointLight myPointLight2;
uniform PointLight myPointLight3;

#include "shadows.frag"

smooth in vec4 ShadowCoord;
uniform sampler2DShadow  shadowMap;
//uniform sampler2D  shadowMap;

void main()
{
	vec3 vNormalized = normalize(vNormal);
	
	vec4 vTexColor = texture2D(gSampler, vTexCoord);
	vec4 vMixedColor = vTexColor*vColor;
	
	float visibility = GetVisibility(shadowMap, ShadowCoord);
	vec4 vDiffuseColor = getDirectionalLightColor(sunLight, vNormalized, visibility);
	vec4 vMyPointlightColor1 = getPointLightColor(myPointLight1, vWorldPos, vNormalized);
	vec4 vMyPointlightColor2 = getPointLightColor(myPointLight2, vWorldPos, vNormalized);
	vec4 vMyPointlightColor3 = getPointLightColor(myPointLight3, vWorldPos, vNormalized);

	outputColor = vMixedColor*(vDiffuseColor+vMyPointlightColor1+vMyPointlightColor2+vMyPointlightColor3);
}