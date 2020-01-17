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

uniform DirectionalLight sunLight;

uniform struct FogParameters
{
	vec4 vFogColor; // Fog color
	float fStart; // This is only for linear fog
	float fEnd; // This is only for linear fog
	float fDensity; // For exp and exp2 equation
	
	int iEquation; // 0 = linear, 1 = exp, 2 = exp2
} fogParams;

float getFogFactor(FogParameters params, float fFogCoord)
{
	float fResult = 0.0;
	if(params.iEquation == 0)
		fResult = (params.fEnd-fFogCoord)/(params.fEnd-params.fStart);
	else if(params.iEquation == 1)
		fResult = exp(-params.fDensity*fFogCoord);
	else if(params.iEquation == 2)
		fResult = exp(-pow(params.fDensity*fFogCoord, 2.0));
		
	fResult = 1.0-clamp(fResult, 0.0, 1.0);
	
	return fResult;
}


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
	float fFogCoord = abs(vEyeSpacePos.z/vEyeSpacePos.w);

	vec4 vMixedColor = vColor*vMixedTexColor*(vDirLightColor+vDirSideColor+vStreetlightColor+vMyPointlightColor);
 	outputColor = mix(vMixedColor, fogParams.vFogColor, getFogFactor(fogParams, fFogCoord));
}