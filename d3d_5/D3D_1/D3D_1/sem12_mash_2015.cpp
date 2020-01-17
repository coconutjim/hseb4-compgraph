/*
Осипов Лев Игоревич
Dirext3D. Проект 5.
Visual Studio 2013
21.01.2016
Сделано два режима - на 8 (автономное плавание рыбки через тор) и на 10 (аквариум с управляемой рыбкой).
Управление:
включение/отключение освещения - клавиша l
переключение между режимами автономного плавания рыбки и аквариума - клавиша с
кнопки управления рыбкой в режиме аквариума:
a - движение налево
d - движение направо
w - движение вверх
s - движение вниз
z - движение вперед
x - движение назад
Примечание. Аквариум ограничен размерами 60х60х25 (xyz). Я с удовольствием сделал бы и побольше, но тогда из-за положения камеры рыбка будет заплывать за экран :(
*/
#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include "resource.h"
#include "meshobj.h"

//--------------------------------------------------------------------------------------
// Глобальные переменные
//--------------------------------------------------------------------------------------
HINSTANCE                   g_hInst = NULL;
HWND                        g_hWnd = NULL;
D3D10_DRIVER_TYPE           g_driverType = D3D10_DRIVER_TYPE_NULL;
ID3D10Device*               g_pd3dDevice = NULL;
IDXGISwapChain*             g_pSwapChain = NULL;
ID3D10RenderTargetView*     g_pRenderTargetView = NULL;
ID3D10Texture2D*			pDepthStencil = NULL;
ID3D10DepthStencilState *   pDSState;
ID3D10DepthStencilView*		pDSV;
ID3D10Effect*               g_pEffect = NULL;
ID3D10EffectTechnique*      g_pTechnique = NULL;
ID3D10InputLayout*          g_pVertexLayout = NULL;
ID3D10Buffer*               g_pVertexBuffer = NULL;
ID3D10Buffer*               g_pIndexBuffer = NULL;
ID3D10EffectMatrixVariable* g_pWorldVariable = NULL;
ID3D10EffectMatrixVariable* g_pViewVariable = NULL;
ID3D10EffectMatrixVariable* g_pProjectionVariable = NULL;
ID3D10EffectVectorVariable* g_LightPositionVariable =NULL;
ID3D10EffectVectorVariable* g_LightColorVariable =NULL;
ID3D10EffectVectorVariable* g_ViewVariable =NULL;
D3DXMATRIX                  g_World;
D3DXMATRIX                  g_View;
D3DXMATRIX                  g_Projection;
D3DXMATRIX					g_Scale;
D3DXMATRIX					g_Translation;
D3DXMATRIX					g_Rotation;
D3DXMATRIX					g_RotationX;
D3DXMATRIX					g_RotationY;
MeshFromObj*				g_MeshFromObj1=NULL;
MeshFromObj*				g_MeshFromObj2=NULL;
MeshFromObj*				g_MeshFromObj3=NULL;
MeshFromObj*				g_MeshFromObj4 = NULL;
const int texturesmax=4;
ID3D10ShaderResourceView*           g_pTextureRV[texturesmax];
ID3D10EffectShaderResourceVariable* g_pDiffuseTextureVariable[texturesmax];

bool state = false; // true - controlling fish, false - free diving

// Fish direction (for controlling)
// 0 - left
// 1 - right
// 2 - top
// 3 - bottom
// 4 - forward
// 5 - backward
int fishDirection = 0;

bool lights = true; // lights switcher


//--------------------------------------------------------------------------------------
// Объявления функций
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitDevice();
HRESULT InitGeometry();
void CleanupDevice();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void Render();

//--------------------------------------------------------------------------------------
// Главная функция программы. Происходят все инициализации, и затем выполняется
// цикл обработки сообщений
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
        return 0;

    if( FAILED( InitDevice() ) )
    {
        CleanupDevice();
        return 0;
    }

    if( FAILED( InitGeometry() ) )
    {
        return 0;
    }
    // Цикл обработки сообщений
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            Render();
        }
    }

    CleanupDevice();

    return ( int )msg.wParam;
}


//--------------------------------------------------------------------------------------
// Создание окна
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"sem12_mash_2015";
    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, 800, 600 };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    g_hWnd = CreateWindow( L"sem12_mash_2015", L"Проект 12.2. Осипов Лев.", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
                           NULL );
    if( !g_hWnd )
        return E_FAIL;

    ShowWindow( g_hWnd, nCmdShow );

    return S_OK;
}

//--------------------------------------------------------------------------------------
// Инициализация Z буфера
//--------------------------------------------------------------------------------------
void InitZBuffer()
{
	RECT rc;
	GetClientRect( g_hWnd, &rc );
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	D3D10_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth,sizeof(descDepth));
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
	g_pd3dDevice->CreateTexture2D( &descDepth, NULL, &pDepthStencil );

	bool TuneUPzbuffer=false;

	if (TuneUPzbuffer)
	{
	D3D10_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc,sizeof(dsDesc));
	// Depth test parameters
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D10_COMPARISON_LESS;

	// Stencil test parameters
	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Create depth stencil state
	g_pd3dDevice->CreateDepthStencilState(&dsDesc, &pDSState);

	// Bind depth stencil state
	g_pd3dDevice->OMSetDepthStencilState(pDSState, 1);
	}

	D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV,sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice=0;

	// Create the depth stencil view
	g_pd3dDevice->CreateDepthStencilView( pDepthStencil, // Depth stencil texture
											 &descDSV, // Depth stencil desc
											 &pDSV );  // [out] Depth stencil view

}
//--------------------------------------------------------------------------------------
// Инициализация Direct3D устройства
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect( g_hWnd, &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

    D3D10_DRIVER_TYPE driverTypes[] =
    {
        D3D10_DRIVER_TYPE_HARDWARE,
        D3D10_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = sizeof( driverTypes ) / sizeof( driverTypes[0] );

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
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

    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
        g_driverType = driverTypes[driverTypeIndex];
        hr = D3D10CreateDeviceAndSwapChain( NULL, g_driverType, NULL, createDeviceFlags,
                                            D3D10_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice );
        if( SUCCEEDED( hr ) )
            break;
    }
    if( FAILED( hr ) )
        return hr;

    // Создание рендер-таргета
    ID3D10Texture2D* pBuffer;
    hr = g_pSwapChain->GetBuffer( 0, __uuidof( ID3D10Texture2D ), ( LPVOID* )&pBuffer );
    if( FAILED( hr ) )
        return hr;

    hr = g_pd3dDevice->CreateRenderTargetView( pBuffer, NULL, &g_pRenderTargetView );
    pBuffer->Release();
    if( FAILED( hr ) )
        return hr;

	InitZBuffer();
    g_pd3dDevice->OMSetRenderTargets( 1, &g_pRenderTargetView, pDSV );

    D3D10_VIEWPORT vp;
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_pd3dDevice->RSSetViewports( 1, &vp );
	return S_OK;
}
//--------------------------------------------------------------------------------------
// Названия текстур
wchar_t * texturenames[texturesmax] = { L"grace_cube.dds", L"tiles.png", L"seafloor.dds", L"aquafish01.png" };
//--------------------------------------------------------------------------------------
// Инициализация геометрии
//--------------------------------------------------------------------------------------
HRESULT InitGeometry()
{
    HRESULT hr = S_OK;
    RECT rc;
    GetClientRect( g_hWnd, &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    // Загружаем эффект
    DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3D10_SHADER_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3D10_SHADER_DEBUG;
    #endif
    hr = D3DX10CreateEffectFromFile( L"sem12_mash_2015.fx", NULL, NULL, "fx_4_0", dwShaderFlags, 0, g_pd3dDevice, NULL,
                                         NULL, &g_pEffect, NULL, NULL );
    if( FAILED( hr ) )
    {
        MessageBox( NULL,
                    L"The FX file cannot be located.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }

    // Получаем технику
    //g_pTechnique = g_pEffect->GetTechniqueByName( "Render" );

    // Obtain the variables
    g_pWorldVariable = g_pEffect->GetVariableByName( "World" )->AsMatrix();
    g_pViewVariable = g_pEffect->GetVariableByName( "View" )->AsMatrix();
    g_pProjectionVariable = g_pEffect->GetVariableByName( "Projection" )->AsMatrix();

	// Получаем переменные для источников света
	g_LightPositionVariable = g_pEffect->GetVariableByName( "vLightPosition" )->AsVector();
	g_LightColorVariable =g_pEffect->GetVariableByName( "vLightColor" )->AsVector();
	g_ViewVariable =g_pEffect->GetVariableByName( "vView" )->AsVector();

    // Initialize the world matrix
    D3DXMatrixIdentity( &g_World );

    // Initialize the view matrix
    D3DXVECTOR3 Eye( 0.0f, 1.0f, -5.0f );
    D3DXVECTOR3 At( 0.0f, 1.0f, 0.0f );
    D3DXVECTOR3 Up( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &g_View, &Eye, &At, &Up );

    // Initialize the projection matrix
    D3DXMatrixPerspectiveFovLH( &g_Projection, ( float )D3DX_PI * 0.5f, width / ( FLOAT )height, 0.1f, 100.0f );

    //Загрузка меша из файла obj
	g_MeshFromObj1=new MeshFromObj(g_pd3dDevice,g_pEffect,"Render0","torus.obj");
	g_MeshFromObj2=new MeshFromObj(g_pd3dDevice,g_pEffect,"Render1","torus.obj");
	g_MeshFromObj3=new MeshFromObj(g_pd3dDevice,g_pEffect,"Render2","light.obj");
	g_MeshFromObj4 = new MeshFromObj(g_pd3dDevice, g_pEffect, "Render3", "aquafish01.obj");

    // Загрузка текстур
	for (int i=0; i<texturesmax; i++)
	{
    hr = D3DX10CreateShaderResourceViewFromFile( g_pd3dDevice, texturenames[i], NULL, NULL, &g_pTextureRV[i], NULL );
    if( FAILED( hr ) ) return hr;
	}

	//Установка константы шейдера для всех текстур
	for (int i=0; i<texturesmax; i++)
	{
	char shadertexname[16]="txDiffuse0"; shadertexname[9]+=i;
    g_pDiffuseTextureVariable[i] = g_pEffect->GetVariableByName( shadertexname )->AsShaderResource();
	}

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Очистка переменных
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
    if( g_pd3dDevice ) g_pd3dDevice->ClearState();

    if( g_pVertexBuffer ) g_pVertexBuffer->Release();
    if( g_pIndexBuffer ) g_pIndexBuffer->Release();
    if( g_pVertexLayout ) g_pVertexLayout->Release();
    if( g_pEffect ) g_pEffect->Release();
    if( g_pRenderTargetView ) g_pRenderTargetView->Release();
    if( g_pSwapChain ) g_pSwapChain->Release();
    if( pDepthStencil) pDepthStencil->Release();
	if( pDSState) pDSState->Release();
	if (g_MeshFromObj1) delete g_MeshFromObj1;
	if (g_MeshFromObj2) delete g_MeshFromObj2;
    if( g_pd3dDevice ) g_pd3dDevice->Release();
}


//--------------------------------------------------------------------------------------
// Процедура обработки сообщений Windows
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

		case WM_KEYDOWN:
			if (wParam == 'C') { //  state switcher
				state = !state;
				fishDirection = 0;
			}

			if (state) { // if we are controlling the fish
				if (wParam == 'A') { // moving left
					fishDirection = 0;
				}
				if (wParam == 'D') { // moving right
					fishDirection = 1;
				}
				if (wParam == 'W') { // moving top
					fishDirection = 2;
				}
				if (wParam == 'S') { // moving bot
					fishDirection = 3;
				}
				if (wParam == 'Z') { // moving forward
					fishDirection = 4;
				}
				if (wParam == 'X') { // moving backward
					fishDirection = 5;
				}
			}

			if (wParam == 'L') { //  lights switcher
				lights = !lights;
			}
			break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}

//--------------------------------------------------------------------------------------
float orbit = 0.0f;
float fishRotation = 0.0f;
float tor1SelfRotation = 0.0f;
float tor1Rotation = 0.0f;
float tor2SelfRotation = 0.0f;
float tor2Rotation = 0.0f;

float fishXPos = 0.0f;
float fishYPos = 0.0f;
float fishZPos = 0.0f;
//--------------------------------------------------------------------------------------
// Рендер
//--------------------------------------------------------------------------------------
void Render()
{
    //
    // Очистка рендер-таргета
    //
	float ClearColor[4] = { 0.1f, 0.5f, 0.7f, 1.0f }; // цвет
	g_pd3dDevice->ClearRenderTargetView( g_pRenderTargetView, ClearColor );
	g_pd3dDevice->ClearDepthStencilView(pDSV,D3D10_CLEAR_DEPTH,1.0f,0);

    // Изменение позиции камеры на орбите
	float radius=4.5f;
	orbit+=0.0002f;

	// Инициализация матрицы камеры из орбитальных данных её координат
    D3DXVECTOR3 Eye( 0, 3.0f, -8.0f );
	D3DXVECTOR4 View(Eye.x,Eye.y,Eye.z,0);
    D3DXVECTOR3 At( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 Up( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &g_View, &Eye, &At, &Up );

    //
    // Установка матриц камеры в качестве констант шейдера
    //
    g_pViewVariable->SetMatrix( ( float* )&g_View );
    g_pProjectionVariable->SetMatrix( ( float* )&g_Projection );

	float f0=2.0f;
	float f1=3.0f;
	float f2=2.5f;
	float r=4.0f;

	//Установка координат источников освещения
	D3DXVECTOR4 LightPos[5];
	D3DXVECTOR4 LightColor[5];
	LightPos[0]=D3DXVECTOR4(sin(orbit*f0)*r,cos(orbit*f0)*r+2.0f,cos(orbit*f0)*r,0);
	LightPos[1]=D3DXVECTOR4(sin(orbit*f1)*r,-sin(orbit*f1)*r*0,-cos(orbit*f1)*r,0);
	LightPos[2]=D3DXVECTOR4(cos(orbit*f2)*r,sin(orbit*f2)*r,sin(orbit*f2)*r,0);
	LightPos[1]=D3DXVECTOR4(7,4,0,0);

	if (lights) {
		LightColor[0] = D3DXVECTOR4(0.5f, 1, 0, 1);
		LightColor[1] = D3DXVECTOR4(0.2f, 1, 1, 1);
		LightColor[1] = D3DXVECTOR4(0, 0.75f, 1.5f, 1);
		LightColor[2] = D3DXVECTOR4(0, 1, 1, 1);
	}
	else {
		LightColor[0] = D3DXVECTOR4(0, 0, 0, 1);
		LightColor[1] = D3DXVECTOR4(0, 0, 0, 1);
		LightColor[1] = D3DXVECTOR4(0, 0, 0, 1);
		LightColor[2] = D3DXVECTOR4(0, 0, 0, 1);
	}

	//Установка координат источников в качестве констант шейдера
	g_LightPositionVariable->SetFloatVectorArray((float *)LightPos,0,5);
	g_LightColorVariable->SetFloatVectorArray((float *)LightColor,0,5);
	g_ViewVariable->SetFloatVector((float *)View);

    //
    //Отображение источников освещения
	for (int i=0; i<1; i++)
	{
		D3DXMATRIX Scale;
		D3DXMatrixScaling(&Scale,0.3f,0.3f,0.3f);
		D3DXMatrixTranslation(&g_World,LightPos[i].x,LightPos[i].y,LightPos[i].z); 	g_World=Scale*g_World;
		g_pWorldVariable->SetMatrix( ( float* )&g_World );
		g_MeshFromObj3->Draw();
	}


	//Установка текстуры как константы шейдера
	for (int i=0; i<texturesmax; i++)
    g_pDiffuseTextureVariable[i]->SetResource( g_pTextureRV[i] );

	float angle = 3.14f / 2; // 90 degrees

	if (state) {
		//Рендер загруженного меша1
		D3DXMatrixRotationX(&g_RotationX, angle / 2);
		tor1SelfRotation -= 0.0005f;
		D3DXMatrixRotationY(&g_RotationY, tor1SelfRotation);
		D3DXMatrixMultiply(&g_World, &g_RotationX, &g_RotationY);
		D3DXMatrixTranslation(&g_Translation, 1.5f, 3.0f, 0);
		D3DXMatrixMultiply(&g_World, &g_World, &g_Translation);
		tor1Rotation += 0.0003f;
		D3DXMatrixRotationY(&g_RotationY, tor1Rotation);
		D3DXMatrixMultiply(&g_World, &g_World, &g_RotationY);
		g_pWorldVariable->SetMatrix((float*)&g_World);
		g_MeshFromObj1->Draw();
	}

	//Рендер загруженного меша2
	float offcet = state ? -2.0f : 0.0f;
	D3DXMatrixRotationX(&g_RotationX, angle);
	tor2SelfRotation += 0.002f;
	D3DXMatrixRotationY(&g_RotationY, tor2SelfRotation);
	D3DXMatrixMultiply(&g_World, &g_RotationX, &g_RotationY);
	D3DXMatrixTranslation(&g_Translation, 2.5f, offcet, 0);
	D3DXMatrixMultiply(&g_World, &g_World, &g_Translation);
	tor2Rotation -= 0.0007f;
	D3DXMatrixRotationY(&g_RotationY, tor2Rotation);
	D3DXMatrixMultiply(&g_World, &g_World, &g_RotationY);
    g_pWorldVariable->SetMatrix( ( float* )&g_World );
    g_MeshFromObj2->Draw();

	//Рендер загруженного меша3 (the fish)
	if (state) { // if we controlling the fish
		float step = 0.01f; // fish step
		switch (fishDirection)
		{
		case 0: // fish is moving left
			D3DXMatrixRotationY(&g_Rotation, angle);
			fishXPos -= step;
			if (fishXPos < -30.0f) { // checking borders
				fishXPos = -30.0f;
			}
			D3DXMatrixTranslation(&g_Translation, fishXPos, fishYPos, fishZPos);
			break;
		case 1: // fish is moving right
			D3DXMatrixRotationY(&g_Rotation, -angle);
			fishXPos += step;
			if (fishXPos > 30.0f) { // checking borders
				fishXPos = 30.0f;
			}
			D3DXMatrixTranslation(&g_Translation, fishXPos, fishYPos, fishZPos);
			break;
		case 2: // fish is moving top
			D3DXMatrixRotationX(&g_Rotation, angle);
			fishYPos += step;
			if (fishYPos > 30.0f) { // checking borders
				fishYPos = 30.0f;
			}
			D3DXMatrixTranslation(&g_Translation, fishXPos, fishYPos, fishZPos);
			break;
		case 3: // fish is moving bottom
			D3DXMatrixRotationX(&g_Rotation, -angle);
			fishYPos -= step;
			if (fishYPos < -30.0f) { // checking borders
				fishYPos = -30.0f;
			}
			D3DXMatrixTranslation(&g_Translation, fishXPos, fishYPos, fishZPos);
			break;
		case 4: // fish is moving forward
			D3DXMatrixRotationY(&g_Rotation, 2 * angle);
			fishZPos += step;
			if (fishZPos > 20.0f) { // checking borders
				fishZPos = 20.0f;
			}
			D3DXMatrixTranslation(&g_Translation, fishXPos, fishYPos, fishZPos);
			break;
		case 5: // fish is moving backward
			D3DXMatrixRotationY(&g_Rotation, 0.0f);
			fishZPos -= step;
			if (fishZPos < -5.0f) { // checking borders
				fishZPos = -5.0f;
			}
			D3DXMatrixTranslation(&g_Translation, fishXPos, fishYPos, fishZPos);
			break;
		}
		D3DXMatrixMultiply(&g_World, &g_Rotation, &g_Translation);
		D3DXMatrixScaling(&g_Scale, 0.2f, 0.2f, 0.2f);
		D3DXMatrixMultiply(&g_World, &g_World, &g_Scale);
	}
	else {
		D3DXMatrixScaling(&g_Scale, 0.2f, 0.2f, 0.2f);
		D3DXMatrixTranslation(&g_Translation, 2.5f, 0, 0);
		D3DXMatrixMultiply(&g_World, &g_Scale, &g_Translation);
		fishRotation += 0.003f;
		D3DXMatrixRotationY(&g_RotationY, fishRotation);
		D3DXMatrixMultiply(&g_World, &g_World, &g_RotationY);
	}
	g_pWorldVariable->SetMatrix((float*)&g_World);
	g_MeshFromObj4->Draw();

    // Вывод на экран содержимого рендер-таргета
    //
    g_pSwapChain->Present( 0, 0 );
}

