/*
Осипов Лев Игоревич
Dirext3D. Проект 4.
Visual Studio 2013
17.01.2016
Управление:
переключение вывода изображения на z-буффер и обратно - клавиша z
включение и отключение облета камеры для обзора расположения фигур (с отключением движения фигур и оставлением вывода z-буффера в изначальном виде) - клавиша o
*/

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>

// Window size
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

/**
* ------------------------------------------------------------------
* Structure to hold the data about vertex
* ------------------------------------------------------------------
*/
struct SimpleVertex
{
    D3DXVECTOR3 Pos;  
	D3DXVECTOR4 Color;  
};

/**
* ------------------------------------------------------------------
* Global D3D variables
* ------------------------------------------------------------------
*/
HWND        g_hWnd = NULL;
D3D10_DRIVER_TYPE       g_driverType = D3D10_DRIVER_TYPE_NULL;
ID3D10Device*           g_pd3dDevice = NULL;
IDXGISwapChain*         g_pSwapChain = NULL;
ID3D10RenderTargetView* g_pRenderTargetView = NULL;

ID3D10Texture2D*            g_pDepthStencil = NULL;
ID3D10DepthStencilView*     g_pDepthStencilView = NULL;

ID3D10Effect*           g_pEffect = NULL;
ID3D10EffectTechnique*  g_pTechnique = NULL;
ID3D10InputLayout*      g_pVertexLayout = NULL;
ID3D10Buffer*           g_pVertexBuffer = NULL;

ID3D10Buffer*           g_pIndexBuffer = NULL;

ID3D10EffectMatrixVariable* g_pWorldVariable = NULL;
ID3D10EffectMatrixVariable* g_pViewVariable = NULL;
ID3D10EffectMatrixVariable* g_pProjectionVariable = NULL;
// Matrices
D3DXMATRIX                  g_World;
D3DXMATRIX                  g_View;
D3DXMATRIX                  g_Projection;

// Display state (general or z-buffer) - true for general state, false for z-buffer
bool displayState = true;

// Overview state
bool overviewState = false;

// Vertices and indices
const int vertices_count = 8;
const int indices_count = 36;
SimpleVertex vertices[vertices_count];
DWORD indices[indices_count];

/**
* ------------------------------------------------------------------
* Functions' prototypes
* ------------------------------------------------------------------
*/
HRESULT             InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT				InitDirect3D10();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void                Cleanup();
void                RenderScene();

/**
* ------------------------------------------------------------------
* Main function
* ------------------------------------------------------------------
*/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	// Creating window
	if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
        return 0;
	// Direct3D initializing
	if( FAILED( InitDirect3D10() ) )
    {
        Cleanup();
        return 0;
    }

	// Message processing
    MSG msg = {0};
    while( WM_QUIT != msg.message  )
    {
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
        TranslateMessage( &msg );
        DispatchMessage( &msg );
		}
		else
		{
			RenderScene();
		}

    }
    // Clearing memory
	Cleanup();
    return (int) msg.wParam;
}

/**
* ------------------------------------------------------------------
* Window initializing
* ------------------------------------------------------------------
*/
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
	// Window registration
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX); 
    wc.style          = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc    = WndProc;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;
    wc.hInstance      = hInstance;
    wc.hIcon          = NULL;
    wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName   = NULL;
    wc.lpszClassName  = L"SimpleWindowClass";
    wc.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);
    if( !RegisterClassEx(&wc) )
        return E_FAIL;

	// Window creation
    g_hWnd = CreateWindow(
		L"SimpleWindowClass", 
		L"Проект 12.1. Лев Осипов.", 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	// In case of failure
    if( !g_hWnd )
        return E_FAIL;
	// Showing
    ShowWindow( g_hWnd, nCmdShow );
	UpdateWindow(g_hWnd);
   
    return S_OK;
}

/**
* ------------------------------------------------------------------
* D3D initializing
* ------------------------------------------------------------------
*/
HRESULT InitDirect3D10()
{
	HRESULT hr = S_OK;

	// Client window size
    RECT rc;
    GetClientRect( g_hWnd, &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

	// Driver types
	D3D10_DRIVER_TYPE driverTypes[] = 
    {
        D3D10_DRIVER_TYPE_HARDWARE,
        D3D10_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	// Filling the structure
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof(sd) );
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = g_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

	// Traversing throug driver types to find the available one
	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D10CreateDeviceAndSwapChain( NULL, g_driverType, NULL, 0, 
			D3D10_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice );
		if( SUCCEEDED( hr ) )
			break;
	}
	if( FAILED(hr) )
		return hr;

	// Data representation for visualization buffer
    ID3D10Texture2D *pBackBuffer;
    hr = g_pSwapChain->GetBuffer( 0, __uuidof( ID3D10Texture2D ), (LPVOID*)&pBackBuffer );
    if( FAILED(hr) )
        return hr;
	// Creating data representation as visualization buffer
    hr = g_pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &g_pRenderTargetView );
    pBackBuffer->Release();
    if( FAILED(hr) )
        return hr;

	// Creating depth buffer
    D3D10_TEXTURE2D_DESC descDepth;
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D32_FLOAT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D10_USAGE_DEFAULT;
    descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    hr = g_pd3dDevice->CreateTexture2D( &descDepth, NULL, &g_pDepthStencil );
    if( FAILED(hr) )
        return hr;

	// Creating data representation as depth buffer
    D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = g_pd3dDevice->CreateDepthStencilView( g_pDepthStencil, &descDSV, &g_pDepthStencilView );
    if( FAILED(hr) )
        return hr;

	// Connecting visualization and depth buffers with graphic conveyor
	g_pd3dDevice->OMSetRenderTargets( 1, &g_pRenderTargetView, g_pDepthStencilView );

	// Configuring display area
    D3D10_VIEWPORT vp;
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_pd3dDevice->RSSetViewports( 1, &vp );

	// Retrieving shaders
	D3DX10CreateEffectFromFile( L"OsipovShader.fx", NULL, NULL,  "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, 
                                     g_pd3dDevice, NULL, NULL, &g_pEffect, NULL, &hr );
    if( FAILED( hr ) )
    {
        MessageBox( NULL, L"Не удается обнаружить файл эффектов (FX). Файл эффектов должен находиться в той же папке, что и исполняемый файл", L"Ошибка", MB_OK );
        return hr;
    }

	// Retrieving technique
    g_pTechnique = g_pEffect->GetTechniqueByName( "RenderAll" );

	// Binding shader's variables
    g_pWorldVariable = g_pEffect->GetVariableByName( "World" )->AsMatrix();
    g_pViewVariable = g_pEffect->GetVariableByName( "View" )->AsMatrix();
    g_pProjectionVariable = g_pEffect->GetVariableByName( "Projection" )->AsMatrix();
	
	// Configuring input format
    D3D10_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT numElements = sizeof(layout)/sizeof(layout[0]);

	// Creating input data object
    D3D10_PASS_DESC PassDesc;
    g_pTechnique->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    hr = g_pd3dDevice->CreateInputLayout( layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &g_pVertexLayout );
    if( FAILED( hr ) )
        return hr;

	// Connecting input data object with graphic conveyor
    g_pd3dDevice->IASetInputLayout( g_pVertexLayout );

	// Initializing vertices (creating vertex buffer)
    SimpleVertex cube_vertices[] = {
        { D3DXVECTOR3( -1.0f,  1.0f, -1.0f ), D3DXVECTOR4( 0.0f, 0.0f, 1.0f, 1.0f ) },
        { D3DXVECTOR3(  1.0f,  1.0f, -1.0f ), D3DXVECTOR4( 0.0f, 1.0f, 0.0f, 1.0f ) },
        { D3DXVECTOR3(  1.0f,  1.0f,  1.0f ), D3DXVECTOR4( 0.0f, 1.0f, 1.0f, 1.0f ) },
        { D3DXVECTOR3( -1.0f,  1.0f,  1.0f ), D3DXVECTOR4( 1.0f, 0.0f, 0.0f, 1.0f ) },
        { D3DXVECTOR3( -1.0f, -1.0f, -1.0f ), D3DXVECTOR4( 1.0f, 0.0f, 1.0f, 1.0f ) },
        { D3DXVECTOR3(  1.0f, -1.0f, -1.0f ), D3DXVECTOR4( 1.0f, 1.0f, 0.0f, 1.0f ) },
        { D3DXVECTOR3(  1.0f, -1.0f,  1.0f ), D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) },
        { D3DXVECTOR3( -1.0f, -1.0f,  1.0f ), D3DXVECTOR4( 0.0f, 0.0f, 0.0f, 1.0f ) },
    };

	// Cube
	for (int i = 0; i < 8; ++i) {
		SimpleVertex vertex = cube_vertices[i];
		vertices[i] = vertex;
	}


    D3D10_BUFFER_DESC bd;
    bd.Usage = D3D10_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( SimpleVertex ) * vertices_count; // allocating space for vertices
    bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = vertices;
    hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &g_pVertexBuffer );
    if( FAILED( hr ) )
        return hr;

	// Connecting vertex buffer with graphic conveyor
    UINT stride = sizeof( SimpleVertex );
    UINT offset = 0;
    g_pd3dDevice->IASetVertexBuffers( 0, 1, &g_pVertexBuffer, &stride, &offset );

	// Initializing indices (creating index buffer)
    DWORD cube_indices[] =
    {
        3, 1, 0,
        2, 1, 3,
        0, 5, 4,
        1, 5, 0,
        3, 4, 7,
        0, 4, 3,
        1, 6, 5,
        2, 6, 1,
        2, 7, 6,
        3, 7, 2,
        6, 4, 5,
        7, 4, 6,
    };

	// Cube
	for (int i = 0; i < 36; ++i) {
		indices[i] = cube_indices[i];
	}

    bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(DWORD) * indices_count; // allocating space for indices
    bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    InitData.pSysMem = indices;
    hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &g_pIndexBuffer );
    if( FAILED(hr) )
        return hr;

	// Connecting index buffer with graphic conveyor
    g_pd3dDevice->IASetIndexBuffer( g_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0 );

	// Configuring primitive type
    g_pd3dDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// Initializaing world matrix
    D3DXMatrixIdentity( &g_World );
    
	// Initializaing view matrix
    D3DXVECTOR3 Eye( 0.0f, 3.0f, -8.0f );
    D3DXVECTOR3 At( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 Up( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &g_View, &Eye, &At, &Up );

	// Initializaing projection matrix
    D3DXMatrixPerspectiveFovLH( &g_Projection, (float)D3DX_PI * 0.35f, width/(FLOAT)height, 0.1f, 100.0f );

    return S_OK;
}

/**
* ------------------------------------------------------------------
* Rendering and drawing 3D scene
* ------------------------------------------------------------------
*/
void RenderScene()
{
	// Counting t - our transform coefficient
    static float t = 0.0f;
    if ( g_driverType == D3D10_DRIVER_TYPE_REFERENCE )
    {
        t += (float)D3DX_PI * 0.0125f;
    }
    else
    {
        static DWORD dwTimeStart = 0;
        DWORD dwTimeCur = GetTickCount();
        if( dwTimeStart == 0 )
            dwTimeStart = dwTimeCur;
        t = ( dwTimeCur - dwTimeStart) / 1000.0f;
    }

	if (overviewState) {
		// If we are at overview state, rotating the camera (depending on t)
		D3DXVECTOR3 Eye(15.0f * sin(t), 3.0f, -15.0f * cos(t));
		D3DXVECTOR3 At(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
		D3DXMatrixLookAtLH(&g_View, &Eye, &At, &Up); // configuring
	}
	else {
		// Transforming scene (rotating depending on t)
		D3DXMatrixRotationY(&g_World, t);
	}

	// Clearing second buffer
	float ClearColor[4] = { 0.1f, 0.5f, 0.7f, 1.0f }; // background color
    g_pd3dDevice->ClearRenderTargetView( g_pRenderTargetView, ClearColor );

	// Clearing depth buffer
    g_pd3dDevice->ClearDepthStencilView( g_pDepthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL , 1.0f, 0 );

	// Setting transforming matrices
    g_pWorldVariable->SetMatrix( (float*)&g_World );
    g_pViewVariable->SetMatrix( (float*)&g_View );
    g_pProjectionVariable->SetMatrix( (float*)&g_Projection );

	// Drawing scene
	D3D10_TECHNIQUE_DESC techDesc;
	g_pTechnique->GetDesc( &techDesc );

	int techniqueType = displayState ? 0 : 1; // choosing tecnique type in case of display state
	g_pTechnique->GetPassByIndex(techniqueType)->Apply(0); // getting technique
	g_pd3dDevice->DrawIndexed(indices_count, 0, 0); // drawing

	// Swapping buffers
	g_pSwapChain->Present( 0, 0 );

}

/**
* ------------------------------------------------------------------
* Processing messages
* ------------------------------------------------------------------
*/
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{    
    switch (message) 
    {
        
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

		case WM_KEYDOWN:
			if (wParam == 'Z') { // display state switcher
				displayState = !displayState;
			}
			if (wParam == 'O') { // overview state switcher
				overviewState = !overviewState;
				if (!overviewState) {
					// If we switch it off, reset camera
					D3DXVECTOR3 Eye(0.0f, 3.0f, -8.0f);
					D3DXVECTOR3 At(0.0f, 0.0f, 0.0f);
					D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
					D3DXMatrixLookAtLH(&g_View, &Eye, &At, &Up);
				}
			}
			break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

/**
* ------------------------------------------------------------------
* Cleaning memory
* ------------------------------------------------------------------
*/
void Cleanup()
{
 	if( g_pd3dDevice ) g_pd3dDevice->ClearState();

	if ( g_pVertexBuffer ) g_pVertexBuffer->Release();
	if ( g_pVertexLayout ) g_pVertexLayout->Release();
	if ( g_pEffect ) g_pEffect->Release();

	if( g_pDepthStencilView ) g_pDepthStencilView->Release();
    if( g_pRenderTargetView ) g_pRenderTargetView->Release();
    if( g_pSwapChain ) g_pSwapChain->Release();
    if( g_pd3dDevice ) g_pd3dDevice->Release();
}

