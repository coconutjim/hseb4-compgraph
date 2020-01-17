// Шейдеры для прожектора
// Файл SpotLight.fx
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
float4 LightDirection;
float  Phi; 
float  Theta;

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
             
    Out.Normal = mul (Data.Normal, World);
  
    return Out;
}

// Функция расчета интенсивности света
float GetAngleIntensity ( float3 LightDir, float3 PixelToLight )
{
  float F = 1.0;
  float AngleIntensity = 0.0;
  
  float rho = saturate(dot(LightDir, -PixelToLight));
  
   if(rho>cos(Theta/2)) AngleIntensity=1.0;
   else if(rho<cos(Phi/2)) AngleIntensity=0.0;
   else AngleIntensity = saturate(pow((rho-cos(Phi/2))/(cos(Theta/2)-cos(Phi/2)),F));

   return AngleIntensity;  
}

//-----------------------------------------------------------------------
// Функция пиксельного шейдера
//-----------------------------------------------------------------------
float4 PS_SpotLight( PS_INPUT Vertex ) : SV_Target
{
    float A = 0.2;
    float B = 0.0;
    float C = 0.0;

    float3 PixelToLight = (float3)LightPosition - Vertex.InterPos;
    
    float3 NewNormal = normalize(Vertex.Normal);
    float3 NewDirection = normalize(PixelToLight);

    float LightAtten =1/( A*pow(length(PixelToLight),2.0)+B*length(PixelToLight)+C );
    
    float LightAngle = GetAngleIntensity (normalize((float3)LightDirection), NewDirection);
    
    float4 LightIntensity = LightColor*LightAngle*LightAtten;
   
    float4 FinalColor = saturate(0.2+max(LightIntensity*dot(NewNormal, NewDirection),0) );
    FinalColor.a = 1;
    
    return FinalColor;
}
//-----------------------------------------------------------------------
// Техника отображения
//-----------------------------------------------------------------------
technique10 RenderSpotLight
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_SpotLight() ) );
    }
}
