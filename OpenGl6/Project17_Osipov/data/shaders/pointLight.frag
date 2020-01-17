#version 330

#include_part

struct PointLight
{
	vec3 vColor; // Color of that point light
	vec3 vPosition;
	
	// Used as boolean, whether the light is on
	int bOn;
	
	float fAmbient;

	float fConstantAtt;
	float fLinearAtt;
	float fExpAtt;
};

vec4 getPointLightColor(const PointLight ptLight, vec3 vWorldPos, vec3 vNormal);

#definition_part

vec4 getPointLightColor(const PointLight ptLight, vec3 vWorldPos, vec3 vNormal)
{
	// If the light isn't turned on, return no color
	if(ptLight.bOn == 0)return vec4(0.0, 0.0, 0.0, 0.0);
	vec3 vPosToLight = vWorldPos-ptLight.vPosition;
	float fDist = length(vPosToLight);
	vPosToLight = normalize(vPosToLight);
	
	float fDiffuse = max(0.0, dot(vNormal, -vPosToLight));

	float fAttTotal = ptLight.fConstantAtt + ptLight.fLinearAtt*fDist + ptLight.fExpAtt*fDist*fDist;

	return vec4(ptLight.vColor, 1.0)*(ptLight.fAmbient+fDiffuse)/fAttTotal;
}