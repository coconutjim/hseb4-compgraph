// ���� cube_texture.fx
//-----------------------------------------------------------------------
// ��������� ������
//-----------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD;
    float4 Color: COLOR;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD;
    float4 Color: COLOR;
};

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};
//-----------------------------------------------------------------------
// ���������� ����������
//-----------------------------------------------------------------------
matrix World;
matrix View;
matrix Projection;
Texture2D g_txDiffuse;
//-----------------------------------------------------------------------
// ������� ���������� �������
//-----------------------------------------------------------------------
PS_INPUT VS( VS_INPUT Data )
{
    PS_INPUT Out;
    Out = (PS_INPUT)0;
    
    // �������� ���������� �������
    // �� ������� ��������������
    Out.Pos = mul (Data.Pos, World);
    Out.Pos = mul (Out.Pos, View);
    Out.Pos = mul (Out.Pos, Projection);
    // ���������� ����������
    // ������� ��� ���������
    Out.Tex = Data.Tex;
    Out.Color = Data.Color;
   
    return Out;
}

//-----------------------------------------------------------------------
// ������� ����������� ������� (������ ��������) 
//-----------------------------------------------------------------------
float4 PS_Texture( PS_INPUT input ) : SV_Target
{
    return g_txDiffuse.Sample( samLinear, input.Tex );
}

float4 PS( PS_INPUT input ) : SV_Target
{
    return input.Color;
}
technique10 RenderTexture
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_Texture() ) );
     }
    pass P1
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
     }
}