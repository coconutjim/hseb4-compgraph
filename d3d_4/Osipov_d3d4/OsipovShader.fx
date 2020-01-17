//-----------------------------------------------------------------------
// Data structures
//-----------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float4 Color: COLOR;
};

struct GSPS_INPUT
{
    float4 Pos : SV_POSITION;
    float4 Color: COLOR;
};

//-----------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------
matrix World;
matrix View;
matrix Projection;

//-----------------------------------------------------------------------
// Vertex shader
//-----------------------------------------------------------------------
GSPS_INPUT VS( VS_INPUT Data )
{
    GSPS_INPUT Out;
    Out = (GSPS_INPUT)0;
    
    // Multiplying
    Out.Pos = mul (Data.Pos, World);

    // We do not change the color
    Out.Color = Data.Color;
    
    return Out;
}

//-----------------------------------------------------------------------
// Scales vertex position
//-----------------------------------------------------------------------
float4 scalePos(float4 Pos, float sc) {
	float4 newPos = Pos;
	// Multiplying coordinates
	newPos.x *= sc;
	newPos.y *= sc;
	newPos.z *= sc;
	return newPos;
}

//-----------------------------------------------------------------------
// Rotates vertex position (around x axis)
//-----------------------------------------------------------------------
float4 rotatePosX(float4 Pos, float angle) {
	float4x4 rotationXMatrix = { { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, cos(angle), sin(angle), 0.0f },
		{ 0.0f, -sin(angle), cos(angle), 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f } }; // setting rotation matrix (around x axis)
	return mul(Pos, rotationXMatrix); // multiplying
}

//-----------------------------------------------------------------------
// Creates new vertices
// colorType: 0 - negative, 1 - blue, 2 - yellow, 3 - z-buffer color 
//-----------------------------------------------------------------------
void createNewVertices(triangle GSPS_INPUT input[3], GSPS_INPUT output, inout TriangleStream<GSPS_INPUT> TriStream, float3 faceNormal,
	float xOffset, float yOffset, float zOffset, float distance, float scale, float angle, uint colorType) {

	for (int i = 0; i < 3; i++)
	{
		output.Pos = input[i].Pos + float4(distance * faceNormal, 0); // controlling distance from center

		// Scaling
		output.Pos = scalePos(output.Pos, scale);

		// Rotating around x axis
		output.Pos = rotatePosX(output.Pos, angle);

		// Taking offsets
		output.Pos.x += xOffset;
		output.Pos.y += yOffset;
		output.Pos.z += zOffset;

		// Taking color
		switch (colorType) {
			case 0:
				output.Color = float4(1.0f - input[i].Color.r, 1.0f - input[i].Color.g, 1.0f - input[i].Color.b, 1.0f); // negative
				break;

			case 1:
				output.Color = float4(0.0f, 0.0f, 1.0f, 1.0f); // blue color
				break;

			case 2:
				output.Color = float4(1.0f, 1.0f, 0.0f, 1.0f); // yellow color
				break;

			case 3:
				// Taking color depending on the point depth
				float3 eye = { 0.0f, 3.0f, -8.0f }; // considering eye position
				float3 toPoint = output.Pos.xyz - eye; // vector from eye to point
				float depth = dot(toPoint, toPoint); // taking vector length
				depth = depth / 300.0f; // norming
				output.Color = float4(depth, depth, depth, 1.0f);
				break;

			default:
				output.Color = input[i].Color; // original color by default
				break;
		}

		// Multiplying (taking projection)
		output.Pos = mul(output.Pos, View);
		output.Pos = mul(output.Pos, Projection);

		TriStream.Append(output);
	}

	TriStream.RestartStrip();
}

//-----------------------------------------------------------------------
// Geometry shader (general)
//-----------------------------------------------------------------------
[MaxVertexCount(15)]
void GS_GENERAL(triangle GSPS_INPUT input[3], inout TriangleStream<GSPS_INPUT> TriStream)
{
	GSPS_INPUT output;

	// Drawing original vertices
	for (int i = 0; i < 3; i++)
	{
		output.Pos = input[i].Pos;

		output.Pos = mul(output.Pos, View);
		output.Pos = mul(output.Pos, Projection);

		output.Color = input[i].Color;

		TriStream.Append(output);
	}

	TriStream.RestartStrip();

	// Creating new vertices

	// Calculating normal to the triangle
	float3 faceEdgeA = input[1].Pos - input[0].Pos;
	float3 faceEdgeB = input[2].Pos - input[0].Pos;
	float3 faceNormal = normalize(cross(faceEdgeA, faceEdgeB));

	// First copy 
	createNewVertices(input, output, TriStream, faceNormal, 4.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.5f, 2);
	// Second copy 
	createNewVertices(input, output, TriStream, faceNormal, -6.0f, -1.0f, 4.0f, 0.1f, 1.5f, 2.5f, 0);
	// Third copy 
	createNewVertices(input, output, TriStream, faceNormal, 0.0f, 3.0f, 0.0f, 1.5f, 0.5f, 1.0f, 1);
	// Fourth copy 
	createNewVertices(input, output, TriStream, faceNormal, 0.0f, 0.0f, -4.5f, 0.2f, 0.5f, 3.5f, 0);
}

//-----------------------------------------------------------------------
// Geometry shader with showing z-buffer
//-----------------------------------------------------------------------
[MaxVertexCount(15)]
void GS_DEPTH(triangle GSPS_INPUT input[3], inout TriangleStream<GSPS_INPUT> TriStream)
{
	GSPS_INPUT output;

	// Coefficient for norming z-buffer color
	float coeff = 300.0f;

	// Drawing original vertices
	for (int i = 0; i < 3; i++)
	{
		output.Pos = input[i].Pos;

		// Taking color depending on the point depth
		float3 eye = { 0.0f, 3.0f, -8.0f }; // considering eye position
		float3 toPoint = input[i].Pos.xyz - eye; // vector from eye to point
		float depth = dot(toPoint, toPoint); // taking vector length
		depth = depth / coeff; // norming
		output.Color = float4(depth, depth, depth, 1.0f);

		output.Pos = mul(output.Pos, View);
		output.Pos = mul(output.Pos, Projection);

		TriStream.Append(output);
	}

	TriStream.RestartStrip();

	// Creating new vertices

	// Calculating normal to the triangle
	float3 faceEdgeA = input[1].Pos - input[0].Pos;
	float3 faceEdgeB = input[2].Pos - input[0].Pos;
	float3 faceNormal = normalize(cross(faceEdgeA, faceEdgeB));
	// Offset parameter
	float offset = 4.5f;

	// First copy 
	createNewVertices(input, output, TriStream, faceNormal, 4.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.5f, 3);
	// Second copy 
	createNewVertices(input, output, TriStream, faceNormal, -6.0f, -1.0f, 4.0f, 0.1f, 1.5f, 2.5f, 3);
	// Third copy 
	createNewVertices(input, output, TriStream, faceNormal, 0.0f, 3.0f, 0.0f, 1.5f, 0.5f, 1.0f, 3);
	// Fourth copy 
	createNewVertices(input, output, TriStream, faceNormal, 0.0f, 0.0f, -4.5f, 0.2f, 0.5f, 3.5f, 3);
}

//-----------------------------------------------------------------------
// Pixel shader
//-----------------------------------------------------------------------
float4 PS_Color( GSPS_INPUT input ) : SV_Target
{
    return input.Color;
}

//-----------------------------------------------------------------------
// Display technique
//-----------------------------------------------------------------------
// Rastering congifuration (without deleting invisible faces)
RasterizerState rsNoCulling { CullMode = None; };
        
technique10 RenderAll
{
	// General rendering
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( CompileShader( gs_4_0, GS_GENERAL() ) );
        SetPixelShader( CompileShader( ps_4_0, PS_Color() ) );
        
        SetRasterizerState ( rsNoCulling );
    }

	// Showing z-buffer
	pass P1
	{
		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetGeometryShader(CompileShader(gs_4_0, GS_DEPTH()));
		SetPixelShader(CompileShader(ps_4_0, PS_Color()));

		SetRasterizerState(rsNoCulling);
	}
}
