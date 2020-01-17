// Шейдеры для точечного источника света
// Файл PointLight.fx
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
    float3 InterPos : TEXTCOORD0;
    float3 Normal : TEXTCOORD1;
};
//-----------------------------------------------------------------------
// Глобальные переменные
//-----------------------------------------------------------------------
matrix World;
matrix View;
matrix Projection;

float4 LightColor;
float4 LightPosition;

//-----------------------------------------------------------------------
// Функция вершинного шейдера
//-----------------------------------------------------------------------
PS_INPUT VS( VS_INPUT Data )
{
    PS_INPUT Out;
    Out = (PS_INPUT)0;
    
     // Умножим координаты вершины
    // на матрицу преобразований
    Out.Pos = mul (Data.Pos, World);
    
    // Подготовим эти координаты для
    // передачи в пиксельный шейдер
    Out.InterPos = Out.Pos.xyz;
    
    // Умножим координаты на
    // оставшиеся матрицы 
    Out.Pos = mul (Out.Pos, View);
    Out.Pos = mul (Out.Pos, Projection);
            
    Out.Normal = normalize(mul (Data.Normal, (float3x3)World) ); 
  
    return Out;
}
//-----------------------------------------------------------------------
// Функция пиксельного шейдера
//-----------------------------------------------------------------------
float4 PS_PointLight( PS_INPUT Vertex ) : SV_Target
{

    float3 PixelToLight = (float3)LightPosition - Vertex.InterPos;
    
    float3 NewNormal = normalize(Vertex.Normal);
    float3 NewDirection = normalize(PixelToLight);

    float4 LightIntensity =LightColor/pow(length(PixelToLight),2.0);
   
    float4 FinalColor = saturate( 0.3+max(LightIntensity*dot(NewNormal, NewDirection),0) );
    FinalColor.a = 1;
    
    return FinalColor;
}
//-----------------------------------------------------------------------
// Техника отображения
//-----------------------------------------------------------------------
technique10 RenderPointLight
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_PointLight() ) );
    }
}
