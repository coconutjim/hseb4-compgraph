#version 330

#include_part

float GetVisibility(sampler2DShadow shadowMap, vec4 vShadowCoord);

#definition_part

uniform sampler2D rotationTexture;

uniform float scale, radius;

uniform int bShadowsOn;

float PCF(in vec4 ShadowCoord, sampler2DShadow shadowMap)
{
  float res = 0.0;

  res += textureProjOffset(shadowMap, ShadowCoord, ivec2(-1,-1));
  res += textureProjOffset(shadowMap, ShadowCoord, ivec2( 0,-1));
  res += textureProjOffset(shadowMap, ShadowCoord, ivec2( 1,-1));
  res += textureProjOffset(shadowMap, ShadowCoord, ivec2(-1, 0));
  res += textureProjOffset(shadowMap, ShadowCoord, ivec2( 0, 0));
  res += textureProjOffset(shadowMap, ShadowCoord, ivec2( 1, 0));
  res += textureProjOffset(shadowMap, ShadowCoord, ivec2(-1, 1));
  res += textureProjOffset(shadowMap, ShadowCoord, ivec2( 0, 1));
  res += textureProjOffset(shadowMap, ShadowCoord, ivec2( 1, 1));

  return (res / 9.0);
}

float GetVisibility(sampler2DShadow shadowMap, vec4 vShadowCoord)
{
    
    float visibility = 1.0;
    
    
    if(bShadowsOn == 1)
    {
      visibility = PCF(vShadowCoord, shadowMap);
     }
  return visibility;
}