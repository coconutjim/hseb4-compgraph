/*
Осипов Лев Игоревич
Dirext3D. Проект 3.
Visual Studio 2013
11.01.2016
Управление:
включение/отключение движения фигур - клавиша f
включение/отключение точечного источника света - клавиша p
включение/отключение направленного источника света - клавиша d
включение/отключение прожектора - клавиша s
включения/отключение движения камеры - клавиша c (изначально отключено)
включение/отключение движения источников света - клавиша l (изначально отключено)
*/
#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include "sphere.h"
#include "torus.h"
#pragma once

// Window size
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

/**
* Structure to hold the data about vertex
*/
struct SimpleVertex
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR2 Texcoord;
	D3DXVECTOR3 Normal;
};

/** 
* Global D3D variables
*/
HWND        g_hWnd = NULL;
D3D10_DRIVER_TYPE       g_driverType = D3D10_DRIVER_TYPE_NULL;
ID3D10Device*           g_pd3dDevice = NULL;
IDXGISwapChain*         g_pSwapChain = NULL;
ID3D10RenderTargetView* g_pRenderTargetView = NULL;

ID3D10Effect*           g_pEffect = NULL;
ID3D10EffectTechnique*  g_pTechnique = NULL;
ID3D10InputLayout*      g_pVertexLayout = NULL;
ID3D10Buffer*           g_pVertexBuffer = NULL;

ID3D10Buffer*               g_pIndexBuffer = NULL;

ID3D10EffectMatrixVariable* g_pWorldVariable = NULL;
ID3D10EffectMatrixVariable* g_pViewVariable = NULL;
ID3D10EffectMatrixVariable* g_pProjectionVariable = NULL;
ID3D10EffectShaderResourceVariable* g_pTexResource = NULL;

ID3D10ShaderResourceView* g_pShaderResource = NULL;

// Figures moving
bool figuresMovingState = true;

// Point light
ID3D10EffectVectorVariable* g_pPointLightColor = NULL;
ID3D10EffectVectorVariable* g_pPointLightPosition = NULL;
bool pointLightState = true;
// Direct light
ID3D10EffectVectorVariable* g_pDirectLightColor = NULL;
ID3D10EffectVectorVariable* g_pDirectLightDirection = NULL;
bool directLightState = true;
// Spot light
ID3D10EffectVectorVariable* g_pSpotLightColor = NULL;
ID3D10EffectVectorVariable* g_pSpotLightPosition = NULL;
ID3D10EffectVectorVariable* g_pSpotLightDirection = NULL;
ID3D10EffectScalarVariable* g_pSpotLightPhi = NULL;
ID3D10EffectScalarVariable* g_pSpotLightTheta = NULL;
bool spotLightState = true;
// Light moving
bool lightMovingState = false;

// Camera moving
bool cameraMovingState = false;

// Matrices
D3DXMATRIX                  g_World;
D3DXMATRIX                  g_View;
D3DXMATRIX                  g_Projection;

// Vertices and indices
const int vertices_count = sphere_vcount + tor_vcount + 24;
const int indices_count = sphere_icount + tor_icount + 36;
SimpleVertex vertices[vertices_count];
DWORD indices[indices_count];

// Functions' prototypes
HRESULT             InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT				InitDirect3D10();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void                Cleanup();
void                RenderScene();
void				initializeVertices();
void				initializeIndices();
void				resetCamera();

/**
* ------------------------------------------------------------------
* Main function 
* ------------------------------------------------------------------
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Creqting window
	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;
	// Direct3D initializing
	if (FAILED(InitDirect3D10()))
	{
		Cleanup();
		return 0;
	}

	// Message processing
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			RenderScene();
		}

	}

	Cleanup();
	return (int)msg.wParam;
}

/**
* ------------------------------------------------------------------
* Window initializing
* ------------------------------------------------------------------
*/
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// Window registration
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"SimpleWindowClass";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc))
		return E_FAIL;

	// Window creation
	g_hWnd = CreateWindow(
		L"SimpleWindowClass",
		L"Проект 3. Лев Осипов.",
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
	if (!g_hWnd)
		return E_FAIL;

	// Showing
	ShowWindow(g_hWnd, nCmdShow);
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
	GetClientRect(g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	// Driver rypes
	D3D10_DRIVER_TYPE driverTypes[] =
	{
		D3D10_DRIVER_TYPE_HARDWARE,
		D3D10_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	// Filling the structure
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
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
	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D10CreateDeviceAndSwapChain(NULL, g_driverType, NULL, 0,
			D3D10_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Data representation for visualization buffer
	ID3D10Texture2D *pBackBuffer;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	// Creating data representation
	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	// Connecting visualization buffer with graphic conveyor
	g_pd3dDevice->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

	// Configuring display area
	D3D10_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pd3dDevice->RSSetViewports(1, &vp);

	// Retrieving shaders
	hr = D3DX10CreateEffectFromFile(L"OsipovShader.fx", NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		g_pd3dDevice, NULL, NULL, &g_pEffect, NULL, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Не удается обнаружить файл эффектов (FX). Файл эффектов должен находиться в той же папке, что и исполняемый файл", L"Ошибка", MB_OK);
		return hr;
	}

	// Retrieving technique
	g_pTechnique = g_pEffect->GetTechniqueByName("RenderAll");

	D3DX10_IMAGE_INFO InfoFromFile;
	D3DX10_IMAGE_LOAD_INFO LoadImageInfo;

	// Reading image from file
	hr = D3DX10GetImageInfoFromFile(L"example.png", NULL, &InfoFromFile, NULL);

	LoadImageInfo.Width = InfoFromFile.Width;
	LoadImageInfo.Height = InfoFromFile.Height;
	LoadImageInfo.Depth = InfoFromFile.Depth;
	LoadImageInfo.FirstMipLevel = 1;
	LoadImageInfo.MipLevels = InfoFromFile.MipLevels;
	LoadImageInfo.Usage = D3D10_USAGE_DEFAULT;
	LoadImageInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE;
	LoadImageInfo.CpuAccessFlags = 0;
	LoadImageInfo.MiscFlags = 0;
	LoadImageInfo.Format = InfoFromFile.Format;
	LoadImageInfo.Filter = D3DX10_FILTER_NONE;
	LoadImageInfo.MipFilter = D3DX10_FILTER_NONE;
	LoadImageInfo.pSrcInfo = &InfoFromFile;

	hr = D3DX10CreateShaderResourceViewFromFile(g_pd3dDevice, L"example.png", &LoadImageInfo, NULL, &g_pShaderResource, NULL);
	if (FAILED(hr))
		return hr;

	// Binding shader's variables
	g_pWorldVariable = g_pEffect->GetVariableByName("World")->AsMatrix();
	g_pViewVariable = g_pEffect->GetVariableByName("View")->AsMatrix();
	g_pProjectionVariable = g_pEffect->GetVariableByName("Projection")->AsMatrix();
	g_pTexResource = g_pEffect->GetVariableByName("g_txDiffuse")->AsShaderResource();
	g_pPointLightColor = g_pEffect->GetVariableByName("PointLightColor")->AsVector();
	g_pPointLightPosition = g_pEffect->GetVariableByName("PointLightPosition")->AsVector();
	g_pDirectLightColor = g_pEffect->GetVariableByName("DirectLightColor")->AsVector();
	g_pDirectLightDirection = g_pEffect->GetVariableByName("DirectLightDirection")->AsVector();
	g_pSpotLightColor = g_pEffect->GetVariableByName("SpotLightColor")->AsVector();
	g_pSpotLightPosition = g_pEffect->GetVariableByName("SpotLightPosition")->AsVector();
	g_pSpotLightDirection = g_pEffect->GetVariableByName("SpotLightDirection")->AsVector();
	g_pSpotLightPhi = g_pEffect->GetVariableByName("Phi")->AsScalar();
	g_pSpotLightTheta = g_pEffect->GetVariableByName("Theta")->AsScalar();

	g_pTexResource->SetResource(g_pShaderResource);

	// Configuring input format
	D3D10_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	// Creating input data object
	D3D10_PASS_DESC PassDesc;
	g_pTechnique->GetPassByIndex(0)->GetDesc(&PassDesc);
	hr = g_pd3dDevice->CreateInputLayout(layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &g_pVertexLayout);
	if (FAILED(hr))
		return hr;

	// Connecting input data object with graphic conveyor
	g_pd3dDevice->IASetInputLayout(g_pVertexLayout);

	// Initializing vertices (creating vertex buffer)
	initializeVertices();

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * (vertices_count);
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
	if (FAILED(hr))
		return hr;

	// Connecting vertex buffer with graphic conveyor
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	g_pd3dDevice->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// Initializing indices (creating index buffer)
	initializeIndices();


	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(DWORD) * (indices_count);
	bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	InitData.pSysMem = indices;
	hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
	if (FAILED(hr))
		return hr;

	// Connecting index buffer with graphic conveyor
	g_pd3dDevice->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// Configuring polygon type
	g_pd3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // setting triangles

	// Initializaing world matrix
	D3DXMatrixIdentity(&g_World);

	// Initializing view matrix
	resetCamera();

	// Initializing projection matrix
	D3DXMatrixPerspectiveFovLH(&g_Projection, (float)D3DX_PI * 0.35f, width / (FLOAT)height, 0.1f, 100.0f);

	return S_OK;
}

/**
* ------------------------------------------------------------------
* Reseting camera
* ------------------------------------------------------------------
*/
void resetCamera() {
	D3DXVECTOR3 Eye(0.0f, 2.0f, -5.0f);
	D3DXVECTOR3 At(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&g_View, &Eye, &At, &Up);
}

/**
* ------------------------------------------------------------------
* Initializing figures' vertices
* ------------------------------------------------------------------
*/
void initializeVertices() {
	int iter = 0; // for iterating
	// Torus
	for (int i = iter; i < tor_vcount; ++i) {
		vertex vtx = tor_vertices[i];
		vertices[i] = { D3DXVECTOR3(vtx.point.x + 0.3f, vtx.point.y, vtx.point.z - 2.0f), D3DXVECTOR2(vtx.texture.x, vtx.texture.y),
			D3DXVECTOR3(vtx.normal.x, vtx.normal.y, vtx.normal.z) };
	}
	iter += tor_vcount;
	// Sphere
	for (int i = iter; i < sphere_vcount + iter; ++i) {
		vertex vtx = sphere_vertices[i - iter];
		vertices[i] = { D3DXVECTOR3(vtx.point.x - 1.0f, vtx.point.y + 2.0f, vtx.point.z - 0.0f), D3DXVECTOR2(vtx.texture.x, vtx.texture.y),
			D3DXVECTOR3(vtx.normal.x, vtx.normal.y, vtx.normal.z) };
	}

	iter += sphere_vcount;
	
	// Cube
	SimpleVertex cube_vertices[] = { 
			{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f) },
			{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f) },
			{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f) },
			{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f) },
			{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f) },
			{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f) },
			{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f) },
			{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f) },
			{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f) },
			{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f) },
			{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f) },
			{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f) },
			{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f) },
			{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f) },
			{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f) },
			{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f) },
			{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f) },
			{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f) },
			{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f) },
			{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f) },
			{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f) },
			{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f) },
			{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f) },
			{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f) },
	};

	for (int i = 0; i < 24; ++i) {
		SimpleVertex vertex = cube_vertices[i];
		float coeff = 1.0f;
		vertex.Pos[0] /= coeff;
		vertex.Pos[1] /= coeff;
		vertex.Pos[2] /= coeff;
		vertices[iter + i] = vertex;
	}

	iter += 24;
}

/**
* ------------------------------------------------------------------
* Initializing figures' indices
* ------------------------------------------------------------------
*/
void initializeIndices() {
	int iter = 0; // for iterating
	// Torus
	for (int i = iter; i < tor_icount; ++i) {
		indices[i] = tor_indices[i];
	}
	iter += tor_icount;
	// Sphere
	for (int i = iter; i < iter + sphere_icount; ++i) {
		indices[i] = sphere_indices[i - iter] + tor_vcount;
	}
	iter += sphere_icount;
	
	// Cube
	DWORD cube_indices[] =
	{
		3, 1, 0,
		2, 1, 3,

		6, 4, 5,
		7, 4, 6,

		11, 9, 8,
		10, 9, 11,

		14, 12, 13,
		15, 12, 14,

		19, 17, 16,
		18, 17, 19,

		22, 20, 21,
		23, 20, 22
	};

	for (int i = iter; i < iter + 36; ++i) {
		indices[i] = cube_indices[i - iter] + tor_vcount + sphere_vcount;
	}
	iter += 36;
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
	if (g_driverType == D3D10_DRIVER_TYPE_REFERENCE)
	{
		t += (float)D3DX_PI * 0.0125f;
	}
	else
	{
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

	// Transforming scene
	if (figuresMovingState) {
		D3DXMatrixRotationY(&g_World, -t);
	}

	// Clearing second buffer
	//float ClearColor[4] = { 0.1f, 0.5f, 0.7f, 1.0f }; // background color
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // background color
	g_pd3dDevice->ClearRenderTargetView(g_pRenderTargetView, ClearColor);

	// Setting matrices
	g_pWorldVariable->SetMatrix((float*)&g_World);
	g_pViewVariable->SetMatrix((float*)&g_View);
	g_pProjectionVariable->SetMatrix((float*)&g_Projection);

	// Configuring point light
	float pointLightColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	if (!pointLightState) { // disabling this light if switcher is off
		pointLightColor[1] = 0.0f;
	}
	g_pPointLightColor->SetFloatVector((float*)&pointLightColor);
	float pointLightPos[4] = { -0.5f, 0.0f, -2.0f, 1.0f };
	if (lightMovingState) { // moving light position
		double r = sqrt(0.25f + 4.0f); // radius here is a hypotenuse
		pointLightPos[0] = r * sin(t);
		pointLightPos[2] = r * cos(t);
	}
	g_pPointLightPosition->SetFloatVector((float*)&pointLightPos);

	// Configuring direct light
	float directLightColor[4] = { 0.0f, 0.0f, 1.0f, 2.0f };
	if (!directLightState) { // disabling this light if switcher is off
		directLightColor[2] = 0.0f;
	}
	g_pDirectLightColor->SetFloatVector((float*)&directLightColor);
	float directLightDir[4] = { 0.0f, 0.0f, -1.5f, 1.0f };
	if (lightMovingState) { // moving light direction
		directLightDir[0] = 1.5f * sin(t);
		directLightDir[2] = 1.5f * cos(t);
	}
	g_pDirectLightDirection->SetFloatVector((float*)&directLightDir);

	// Configuring spot light
	float spotLightColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	if (! spotLightState) { // disabling this light if switcher is off
		spotLightColor[0] = 0.0f;
	}
	g_pSpotLightColor->SetFloatVector((float*)&spotLightColor);
	float spotLightPos[4] = { 1.0f, 0.0f, -2.0f, 1.0f };
	if (lightMovingState) { // moving light position
		double r = sqrt(1.0f + 4.0f); // radius here is a hypotenuse
		spotLightPos[0] = r * sin(t);
		spotLightPos[2] = r * cos(t);
	}
	g_pSpotLightPosition->SetFloatVector((float*)&spotLightPos);
	float spotLightDir[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	g_pSpotLightDirection->SetFloatVector((float*)&spotLightDir);
	float phi = 0.9f; // Phi and Theta are given in radians
	float theta = 0.4f;
	g_pSpotLightPhi->SetFloat(phi);
	g_pSpotLightTheta->SetFloat(theta);


	if (cameraMovingState) { // moving camera
		D3DXVECTOR3 Eye(5.0f * sin(t), 2.0f, 5.0f * cos(t));
		D3DXVECTOR3 At(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
		D3DXMatrixLookAtLH(&g_View, &Eye, &At, &Up); // configuring
	}

	// Drawing scene
	D3D10_TECHNIQUE_DESC techDesc;
	g_pTechnique->GetDesc(&techDesc);
	g_pTechnique->GetPassByIndex(0)->Apply(0); // getting technique
	g_pd3dDevice->DrawIndexed(indices_count, 0, 0); // drawing

	// Swapping buffers
	g_pSwapChain->Present(0, 0);
}

/**
* ------------------------------------------------------------------
* Processing messages
* ------------------------------------------------------------------
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			if (wParam == 'F') { // figures moving switcher
				figuresMovingState = !figuresMovingState;
			}
			if (wParam == 'P') { // point light switcher
				pointLightState = !pointLightState;
			}
			if (wParam == 'D') { // direct light switcher
				directLightState = !directLightState;
			}
			if (wParam == 'S') { // spot light switcher
				spotLightState = !spotLightState;
			}
			if (wParam == 'L') { // light moving switcher
				lightMovingState = !lightMovingState;
			}
			if (wParam == 'C') { // camera moving switcher
				cameraMovingState = !cameraMovingState;
				if (!cameraMovingState) {
					resetCamera();
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
	if (g_pd3dDevice) g_pd3dDevice->ClearState();

	if (g_pVertexBuffer) g_pVertexBuffer->Release();
	if (g_pVertexLayout) g_pVertexLayout->Release();
	if (g_pEffect) g_pEffect->Release();

	if (g_pRenderTargetView) g_pRenderTargetView->Release();
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pd3dDevice) g_pd3dDevice->Release();
}

