// Шейдеры для направленного источника света
// Файл DirectLight.fx
//-----------------------------------------------------------------------
// Структуры данных
//-----------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Normal : NORMAL;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Normal : TEXTCOORD0;
};
//-----------------------------------------------------------------------
// Глобальные переменные
//-----------------------------------------------------------------------
matrix World;
matrix View;
matrix Projection;

float4 LightColor;
float4 LightDirection;

//-----------------------------------------------------------------------
// Функция вершинного шейдера
//-----------------------------------------------------------------------
PS_INPUT VS( VS_INPUT Data )
{
    PS_INPUT Out;
    Out = (PS_INPUT)0;
    
     // Умножаем координаты вершины
    // на матрицы преобразований
    Out.Pos = mul (Data.Pos, World);
    Out.Pos = mul (Out.Pos, View);
    Out.Pos = mul (Out.Pos, Projection);
    
    Out.Normal = mul (Data.Normal, World);
  
    return Out;
}
//-----------------------------------------------------------------------
// Функция пиксельного шейдера
//-----------------------------------------------------------------------
float4 PS_DirectLight( PS_INPUT Vertex ) : SV_Target
{
 
    float4 FinalColor = saturate( 0.3+LightColor*dot( (float3)LightDirection,Vertex.Normal ) );
    FinalColor.a = 1;
    
    return FinalColor;
}
//-----------------------------------------------------------------------
// Техника отображения
//-----------------------------------------------------------------------
technique10 RenderDirectLight
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_DirectLight() ) );
    }
}
