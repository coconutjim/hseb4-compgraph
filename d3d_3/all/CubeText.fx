// Файл cube_texture.fx
//-----------------------------------------------------------------------
// Структуры данных
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
// Глобальные переменные
//-----------------------------------------------------------------------
matrix World;
matrix View;
matrix Projection;
Texture2D g_txDiffuse;
float4 PointLightColor;
float4 PointLightPosition;
//-----------------------------------------------------------------------
// Функция вершинного шейдера
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

//-----------------------------------------------------------------------
// Функция пиксельного шейдера (рисует текстуру) 
//-----------------------------------------------------------------------
float4 PS_Texture( PS_INPUT input ) : SV_Target
{
    // Point light
    float3 PixelToLight = (float3)PointLightPosition - input.InterPos; 
    float3 NewNormal = normalize(input.Normal);
    float3 NewDirection = normalize(PixelToLight);
    float4 LightIntensity = PointLightColor / pow(length(PixelToLight), 2.0); 
    float4 PointColor = saturate( 0.3 + max(LightIntensity * dot(NewNormal, NewDirection), 0) );
    PointColor.a = 1;
    
    // Texture
    float4 TextureColor = g_txDiffuse.Sample( samLinear, input.Tex );
    return PointColor * TextureColor;
}

technique10 RenderTexture
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_Texture() ) );
     }
}