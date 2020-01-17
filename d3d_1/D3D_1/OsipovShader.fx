//-----------------------------------------------------------------------
// Data structures
//-----------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD;
    float3 Normal : NORMAL;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 InterPos : TEXTCOORD0;
    float2 Tex : TEXCOORD;
    float3 Normal : TEXTCOORD1;
};

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};
//-----------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------
matrix World;
matrix View;
matrix Projection;
Texture2D g_txDiffuse;
float4 PointLightColor;
float4 PointLightPosition;
float4 DirectLightColor;
float4 DirectLightDirection;
float4 SpotLightColor;
float4 SpotLightPosition;
float4 SpotLightDirection;
float  Phi; 
float  Theta;
//-----------------------------------------------------------------------
// Vertex shader
//-----------------------------------------------------------------------
PS_INPUT VS( VS_INPUT Data )
{
    PS_INPUT Out;
    Out = (PS_INPUT)0;
    
    // Multiplying
    Out.Pos = mul (Data.Pos, World);
    Out.InterPos = Out.Pos.xyz;
    Out.Pos = mul (Out.Pos, View);
    Out.Pos = mul (Out.Pos, Projection);
    // Texture
    Out.Tex = Data.Tex;
    // Normal
    Out.Normal = normalize(mul (Data.Normal, (float3x3)World) ); 
   
    return Out;
}

// Ñounts light intensity for spot light
float GetSpotAngleIntensity ( float3 LightDir, float3 PixelToLight )
{
  float F = 1.0;
  float AngleIntensity = 0.0;  
  float rho = saturate(dot(LightDir, -PixelToLight));
  if(rho > cos(Theta / 2)) AngleIntensity = 1.0;
  else if(rho < cos(Phi / 2)) AngleIntensity = 0.0;
  else AngleIntensity = saturate(pow((rho - cos(Phi / 2)) / (cos(Theta / 2) - cos(Phi / 2)), F));
  return AngleIntensity;  
}

//-----------------------------------------------------------------------
// Pixel shader. Draws texture.
//-----------------------------------------------------------------------
float4 PS_LightsTexture( PS_INPUT input ) : SV_Target
{
    float3 NewNormal = normalize(input.Normal);

    // Point light
    float3 PixelToPointLight = (float3)PointLightPosition - input.InterPos; 
    float3 NewPointDirection = normalize(PixelToPointLight);
    float4 LightIntensity = PointLightColor / pow(length(PixelToPointLight), 2.0); 
    float4 PointColor = saturate( 0.2 + max(LightIntensity * dot(NewNormal, NewPointDirection), 0) );
    PointColor.a = 1;

    // Direct light
    float4 DirectColor = saturate( 0.2 + max(DirectLightColor * dot( (float3)DirectLightDirection, input.Normal ), 0) );
    DirectColor.a = 1;

    // Spot light
    float A = 0.2;
    float B = 0.0;
    float C = 0.0;
    float3 PixelToSpotLight = (float3)SpotLightPosition - input.InterPos;
    float3 NewSpotDirection = normalize(PixelToSpotLight);
    float SpotLightAtten = 1 / ( A * pow(length(PixelToSpotLight), 2.0) + B * length(PixelToSpotLight) + C );
    float SpotLightAngle = GetSpotAngleIntensity (normalize((float3)SpotLightDirection), NewSpotDirection);
    float4 SpotLightIntensity = SpotLightColor * SpotLightAngle * SpotLightAtten;
    float4 SpotColor = saturate(0.2 + max(SpotLightIntensity * dot(NewNormal, NewSpotDirection), 0) );
    SpotColor.a = 1;
    
    // Texture
    float4 TextureColor = g_txDiffuse.Sample( samLinear, input.Tex );
    
    // Multiplying
    return saturate(PointColor + DirectColor + SpotColor) * TextureColor;
}

technique10 RenderAll
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_LightsTexture() ) );
     }
}