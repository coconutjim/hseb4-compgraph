#version 330

smooth in vec2 vTexCoord;
smooth in vec3 vNormal;
smooth in vec4 vEyeSpacePos;
smooth in vec3 vWorldPos;
out vec4 outputColor;


#include "dirLight.frag"
#include "spotLight.frag"
#include "pointLight.frag"


uniform sampler2D gSamplers[2];
uniform float fTextureContributions[2];
uniform vec4 vColor;
uniform int numTextures;
uniform SpotLight streetLight;
uniform DirectionalLight sideLight;
uniform PointLight myPointLight;
uniform vec3 vEyePosition;

uniform DirectionalLight sunLight;

// reflection
uniform int isReflect;
// reflection params
uniform int reflParam1;
uniform int reflParam2;

void main()
{
	vec3 vNormalized = normalize(vNormal);
	
	vec4 vTexColor1 = texture2D(gSamplers[0], vTexCoord);
	vec4 vTexColor2 = texture2D(gSamplers[1], vTexCoord);
	vec4 vMixedTexColor = vTexColor1*fTextureContributions[0];
	if (numTextures > 1)
		 vMixedTexColor += vTexColor2*fTextureContributions[1];
	vec4 vDirLightColor = getDirectionalLightColor(sunLight, vNormal);
	vec4 vDirSideColor = getDirectionalLightColor(sideLight, vNormal);
	vec4 vStreetlightColor = GetSpotLightColor(streetLight, vWorldPos);
	vec4 vMyPointlightColor = getPointLightColor(myPointLight, vWorldPos, vNormalized);
	
	// considering reflection
	vec4 vSpecularColor;
	if (isReflect == 1) {
		vSpecularColor = GetSpecularColor(vWorldPos, vEyePosition, vNormalized, sunLight, reflParam1, reflParam2);
	} else {
		vSpecularColor = vec4(0.0, 0.0, 0.0, 0.0);
	}

	vec4 vMixedColor = vColor*vMixedTexColor*(vDirLightColor+vDirSideColor+vStreetlightColor+vMyPointlightColor+vSpecularColor);
 	outputColor = vMixedColor;
}