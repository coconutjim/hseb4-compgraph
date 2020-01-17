//--------------------------------------------------------------------------------------
// File: sem12_mash_2015.fx
//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
matrix World;
matrix View;
matrix Projection;
//--------------------------------------------------------------------------------------
float4 vLightPosition[5];		
float4 vLightColor[5];	
float4 vView;		
//--------------------------------------------------------------------------------------
TextureCube txDiffuse0;
Texture2D   txDiffuse1;
Texture2D	txDiffuse2;
Texture2D	txDiffuse3;
//--------------------------------------------------------------------------------------
SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};
//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
	float4 L: COLOR1;
	float4 N: COLOR2;
	float4 LI: COLOR3;
	float4 LJ: COLOR4;
	float4 Diffuse: COLOR5;
	float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader 0
//--------------------------------------------------------------------------------------
VS_OUTPUT VS0( float4 Pos : POSITION, float3 Normal : NORMAL, float2 Tex: TEXCOORD)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul( Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
	output.Color=float4(0.0f,0.0f,0.0f,0);
	output.Diffuse=float4(0.4f,0.4f,0.4f,0);
	float4 lviewvec=normalize(vView-Pos); //mul(View,float4(0,0,1,0));	

	for (int i=0; i<2; i++)
	output.Diffuse+=dot(normalize(Normal),normalize((float3)vLightPosition[i]-(float3)Pos) )*vLightColor[i];
	
	for (int i=0; i<2; i++)
	{
	float3 lpos=(float3)vLightPosition[i];
	float a=dot(normalize(Normal),normalize(lpos-(float3)Pos));
	float b=dot(normalize(Normal),(float3)lviewvec);
	float c=1.0f/(1.0f+(a-b)*(a-b)*5); c=pow(c,5);
	output.Color+=vLightColor[i]*c;
	}

	output.Tex=Tex;

	output.L=lviewvec;
	output.N=float4(Normal.x,Normal.y,Normal.z,0);
	output.LI=normalize(vLightPosition[0]-Pos);
	output.LJ=normalize(vLightPosition[1]-Pos);
    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader 0
//--------------------------------------------------------------------------------------
float4 PS0( VS_OUTPUT input ) : SV_Target
{
	float3 refl=reflect((float3)input.L,(float3)input.N);
	return input.Color+txDiffuse0.Sample(samLinear,refl)*0.8f+float4(0.1f,0,0.1f,0);
}
//--------------------------------------------------------------------------------------
// Pixel Shader 1
//--------------------------------------------------------------------------------------
float4 PS1( VS_OUTPUT input ) : SV_Target
{
	input.Tex.y*=4.0f;
	float3 bump=txDiffuse1.Sample(samLinear,input.Tex)*2.0f - 1.0f;
	float shine=dot((float3)input.LI,normalize(bump)); shine+=dot((float3)input.LJ,normalize(bump));
	float4 ambient=txDiffuse2.Sample(samLinear,input.Tex)*input.Diffuse;
	return ambient*(shine*0.5f)+pow(shine,4) * input.Diffuse*0.1f+ambient*0.5f+float4(0.1f,0,0.1f,0);
}
//--------------------------------------------------------------------------------------
// Pixel Shader 2
//--------------------------------------------------------------------------------------
float4 PS2( VS_OUTPUT input ) : SV_Target
{
	return float4(0.8f,1.0f,0,0);
}

//--------------------------------------------------------------------------------------
// Pixel Shader 3
//--------------------------------------------------------------------------------------
float4 PS3(VS_OUTPUT input) : SV_Target
{
	return txDiffuse3.Sample(samLinear, input.Tex) + input.Color;
}

//--------------------------------------------------------------------------------------
technique10 Render0
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS0() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS0() ) );
    }
}

//--------------------------------------------------------------------------------------
technique10 Render1
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS0() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS1() ) );
    }
}
//--------------------------------------------------------------------------------------
technique10 Render2
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS0() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS2() ) );
    }
}

technique10 Render3
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS0()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS3()));
	}
}
//--------------------------------------------------------------------------------------

