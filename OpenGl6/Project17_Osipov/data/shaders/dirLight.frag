#version 330

#include_part

struct DirectionalLight
{
	vec3 vColor;
	vec3 vDirection;
	
	// Used as boolean, whether the light is on
	int bOn;
	
	float fAmbient;
	int iSkybox;
};

vec4 getDirectionalLightColor(DirectionalLight dirLight, vec3 vNormal, float Shadow);

#definition_part

vec4 getDirectionalLightColor(DirectionalLight dirLight, vec3 vNormal, float Shadow)
{
	// If the light isn't turned on, return no color
	if(dirLight.bOn == 0)return vec4(0.0, 0.0, 0.0, 0.0);
	float fDiffuseIntensity = max(0.0, dot(vNormal, -dirLight.vDirection));
	float fMult = dirLight.fAmbient + fDiffuseIntensity * Shadow;
   if(dirLight.iSkybox == 1)fMult = dirLight.fAmbient;
	return vec4(dirLight.vColor*fMult, 1.0);
}