#version 330

smooth in vec2 vTexCoord;
smooth in vec3 vNormal;
smooth in vec3 vEyeSpacePos;
smooth in vec3 vWorldPos;
out vec4 outputColor;

uniform sampler2D gSampler;
uniform vec4 vColor;

#include "dirLight.frag"
#include "spotLight.frag"
#include "pointLight.frag"

uniform DirectionalLight sunLight;
uniform SpotLight spotLight;
uniform PointLight pointLight;
uniform DirectionalLight myDlLight;
uniform SpotLight mySlLight;
uniform PointLight myPlLight;

void main()
{
	vec3 vNormalized = normalize(vNormal);
	
	vec4 vTexColor = texture2D(gSampler, vTexCoord);
	vec4 vMixedColor = vTexColor*vColor;
	vec4 vDirLightColor = getDirectionalLightColor(sunLight, vNormal);
	vec4 vSpotlightColor = GetSpotLightColor(spotLight, vWorldPos);
	vec4 vPointlightColor = getPointLightColor(pointLight, vWorldPos, vNormalized);
	vec4 vDirLightColor1 = getDirectionalLightColor(myDlLight, vNormal);
	vec4 vSpotlightColor1 = GetSpotLightColor(mySlLight, vWorldPos);
	vec4 vPointlightColor1 = getPointLightColor(myPlLight, vWorldPos, vNormalized);
	outputColor = vMixedColor*(vDirLightColor+vSpotlightColor+vPointlightColor+vDirLightColor1+vSpotlightColor1+vPointlightColor1);
}