#version 330

out vec4 outputColor;

uniform sampler2D samplerShadow;

smooth in vec2 vCoord;


void main()
{
	//float shadow  = PCF(vCoord);
  	vec4 vTexColor = texture2D(samplerShadow, vCoord);
	outputColor = vec4(vTexColor.r, vTexColor.r, vTexColor.r, vTexColor.r);
}