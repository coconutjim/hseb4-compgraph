// Файл cube_texture.fx
//-----------------------------------------------------------------------
// Структуры данных
//-----------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float4 Color: COLOR;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float4 Color: COLOR;
};

//-----------------------------------------------------------------------
// Глобальные переменные
//-----------------------------------------------------------------------
matrix World;
matrix View;
matrix Projection;
//-----------------------------------------------------------------------
// Функция вершинного шейдера
//-----------------------------------------------------------------------
PS_INPUT VS( VS_INPUT Data )
{
    PS_INPUT Out;
    Out = (PS_INPUT)0;
    Out.Pos = mul (Data.Pos, World);
    Out.Pos = mul (Out.Pos, View);
    Out.Pos = mul (Out.Pos, Projection);
    Out.Color = Data.Color;
    return Out;
}

//-----------------------------------------------------------------------
// Функция пиксельного шейдера (возвращает всегда белый цвет)
//-----------------------------------------------------------------------
float4 PS( PS_INPUT Pos ) : SV_Target
{
    return float4( 1.0f, 1.0f, 1.0f, 1.0f );
}

//-----------------------------------------------------------------------
// Функция пиксельного шейдера 
//-----------------------------------------------------------------------
float4 PS_Color( PS_INPUT input ) : SV_Target
{
    return input.Color;
}

        
technique10 RenderWhite
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}

technique10 RenderColor
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_Color() ) );
    }
}