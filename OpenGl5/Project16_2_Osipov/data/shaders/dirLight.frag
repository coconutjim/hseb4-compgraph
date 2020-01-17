#version 330

#include_part

struct DirectionalLight
{
	vec3 vColor;
	vec3 vDirection;

	float fAmbient;
};

vec4 getDirectionalLightColor(DirectionalLight dirLight, vec3 vNormal);
vec4 GetSpecularColor(vec3 vWorldPos, vec3 vEyePos, vec3 vNormal, DirectionalLight dLight, int reflParam1, int reflParam2);

#definition_part

vec4 getDirectionalLightColor(DirectionalLight dirLight, vec3 vNormal)
{
	float fDiffuseIntensity = max(0.0, dot(vNormal, -dirLight.vDirection));
	float fMult = clamp(dirLight.fAmbient+fDiffuseIntensity, 0.0, 1.0);
	return vec4(dirLight.vColor*fMult, 1.0);
}

// reflection from the dirLight
vec4 GetSpecularColor(vec3 vWorldPos, vec3 vEyePos, vec3 vNormal, DirectionalLight dLight, int reflParam1, int reflParam2)
{
   vec4 vResult = vec4(0.0, 0.0, 0.0, 0.0);
   
   
   // if too far, don't care about this
   if (abs(vWorldPos.x) > 200.0 || abs(vWorldPos.y) > 200.0 || abs(vWorldPos.z) > 200.0) {
		return vResult;
   }
   
   // using predefined values for the reflection computing
   vec3 vReflectedVector = normalize(reflect(dLight.vDirection, vNormal));
   vec3 vVertexToEyeVector = normalize(vEyePos-vWorldPos);
   float fSpecularFactor = dot(vVertexToEyeVector, vReflectedVector);
   
   if (fSpecularFactor > 0)
   {
	  fSpecularFactor = pow(fSpecularFactor, 110 - reflParam1);
      vResult = vec4(dLight.vColor, 1.0) * reflParam2 * fSpecularFactor;  
   }
   return vResult;
}