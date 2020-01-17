#version 330

#include_part

struct DirectionalLight
{
	vec3 vColor;
	vec3 vDirection;
	
	// Used as boolean, whether the light is on
	int bOn;

	float fAmbient;
};

vec4 getDirectionalLightColor(DirectionalLight dirLight, vec3 vNormal);

#definition_part

vec4 getDirectionalLightColor(DirectionalLight dirLight, vec3 vNormal)
{
	// If the light isn't turned on, return no color
	if(dirLight.bOn == 0)return vec4(0.0, 0.0, 0.0, 0.0);
	float fDiffuseIntensity = max(0.0, dot(vNormal, -dirLight.vDirection));
	float fMult = clamp(dirLight.fAmbient+fDiffuseIntensity, 0.0, 1.0);
	return vec4(dirLight.vColor*fMult, 1.0);
}