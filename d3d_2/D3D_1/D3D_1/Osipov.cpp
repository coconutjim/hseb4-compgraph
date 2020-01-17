/*
Осипов Лев Игоревич
Dirext3D. Проект 2.
Visual Studio 2013
10.12.2015
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

// Structure to hold the data about vertex
struct SimpleVertex
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR2 Texcoord;
	D3DXVECTOR4 Color;
};

// Global D3D variables
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

D3DXMATRIX                  g_World;
D3DXMATRIX                  g_View;
D3DXMATRIX                  g_Projection;

// Vertices and indices
const int vertices_count = sphere_vcount + tor_vcount + 12 + 24;
const int indices_count = sphere_icount + tor_icount + 12 + 24;
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

// Main function
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

// Window initializing
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
		L"Проект 2. Лев Осипов.",
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

// D3D initializing
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

	// Пытаемся создать устройство, проходя по списку
	// как только получилось - выходим из цикла
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

	// Представление данных для
	// буфера визуализации
	ID3D10Texture2D *pBackBuffer;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;
	// Создадим представление данных
	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;
	// Свяжем буфер визуализации с графическим конвейером
	g_pd3dDevice->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

	// Настроим область отображения
	D3D10_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pd3dDevice->RSSetViewports(1, &vp);

	// Используем наши шейдеры 
	// в файле эффектов cube_texture.fx
	hr = D3DX10CreateEffectFromFile(L"Osipov_shader.fx", NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		g_pd3dDevice, NULL, NULL, &g_pEffect, NULL, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Не удается обнаружить файл эффектов (FX). Файл эффектов должен находиться в той же папке, что и исполняемый файл", L"Ошибка", MB_OK);
		return hr;
	}

	// Извлекаем технику отображения
	g_pTechnique = g_pEffect->GetTechniqueByName("RenderTexture");

	D3DX10_IMAGE_INFO InfoFromFile;
	D3DX10_IMAGE_LOAD_INFO LoadImageInfo;

	// Читаем информацию об изображении из файла
	hr = D3DX10GetImageInfoFromFile(L"example.bmp", NULL, &InfoFromFile, NULL);

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

	hr = D3DX10CreateShaderResourceViewFromFile(g_pd3dDevice, L"example.bmp", &LoadImageInfo, NULL, &g_pShaderResource, NULL);
	if (FAILED(hr))
		return hr;

	// Связь с переменными шейдера
	g_pWorldVariable = g_pEffect->GetVariableByName("World")->AsMatrix();
	g_pViewVariable = g_pEffect->GetVariableByName("View")->AsMatrix();
	g_pProjectionVariable = g_pEffect->GetVariableByName("Projection")->AsMatrix();
	g_pTexResource = g_pEffect->GetVariableByName("g_txDiffuse")->AsShaderResource();

	g_pTexResource->SetResource(g_pShaderResource);

	// Описываем формат входных данных
	D3D10_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	// Создаем объект входных данных
	D3D10_PASS_DESC PassDesc;
	g_pTechnique->GetPassByIndex(0)->GetDesc(&PassDesc);
	hr = g_pd3dDevice->CreateInputLayout(layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &g_pVertexLayout);
	if (FAILED(hr))
		return hr;

	// Связываем объект входных данных с графическим конвейером
	g_pd3dDevice->IASetInputLayout(g_pVertexLayout);

	// Данные вершин куба: буфер вершин
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

	// Связываем буфер вершин с графическим конвейером
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	g_pd3dDevice->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// Создаем индексный буфер
	initializeIndices();


	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(DWORD) * (sphere_icount + tor_icount + 12);
	bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	InitData.pSysMem = indices;
	hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
	if (FAILED(hr))
		return hr;

	// Связываем индексный буфер с графическим конвейером
	g_pd3dDevice->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Задаем тип и способ построения примитивов
	g_pd3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Инициализируем мировую матрицу
	D3DXMatrixIdentity(&g_World);

	// Инициализируем матрицу вида
	D3DXVECTOR3 Eye(0.0f, 2.0f, -5.0f);
	D3DXVECTOR3 At(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&g_View, &Eye, &At, &Up);

	// Инициализируем матрицу проекции
	D3DXMatrixPerspectiveFovLH(&g_Projection, (float)D3DX_PI * 0.35f, width / (FLOAT)height, 0.1f, 100.0f);

	return S_OK;
}

void initializeVertices() {
	int iter = 0; // for iterating
	D3DXVECTOR4 colorMock = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f); // mock for color (we don't need it in torus and sphere)
	// Torus
	for (int i = iter; i < tor_vcount; ++i) {
		vertex vtx = tor_vertices[i];
		vertices[i] = { D3DXVECTOR3(vtx.point.x + 0.3f, vtx.point.y, vtx.point.z - 2.0f), D3DXVECTOR2(vtx.texture.x, vtx.texture.y),
			colorMock };
	}
	iter += tor_vcount;
	// Sphere
	for (int i = iter; i < sphere_vcount + iter; ++i) {
		vertex vtx = sphere_vertices[i - iter];
		vertices[i] = { D3DXVECTOR3(vtx.point.x - 1.0f, vtx.point.y + 1.5f, vtx.point.z - 0.0f), D3DXVECTOR2(vtx.texture.x, vtx.texture.y),
			colorMock };
	}

	iter += sphere_vcount;
	// Pyramid
	D3DXVECTOR2 textMock = D3DXVECTOR2(0.0f, 0.0f); // mock for texture (we don't need it in pyramid and octa)

	// Vertexes objects
	SimpleVertex v1 = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), textMock, D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f) };
	SimpleVertex v2 = { D3DXVECTOR3(1.0f, 0.0f, 0.0f), textMock, D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) };
	SimpleVertex v3 = { D3DXVECTOR3(0.5f, 0.5f * sqrt(3.0f), 0.0f), textMock, D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f) };
	SimpleVertex v4 = { D3DXVECTOR3(0.5f, 1.0f * sqrt(3.0f) / 6, 1.0f * sqrt(6.0f) / 3), textMock, D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f) };

	// Filling the array
	vertices[iter] = v4;
	vertices[iter + 1] = v1;
	vertices[iter + 2] = v3;
	vertices[iter + 3] = v4;
	vertices[iter + 4] = v3;
	vertices[iter + 5] = v2;
	vertices[iter + 6] = v4;
	vertices[iter + 7] = v2;
	vertices[iter + 8] = v1;
	vertices[iter + 9] = v3;
	vertices[iter + 10] = v1;
	vertices[iter + 11] = v2;

	iter += 12;
	// Octa
	/*vertices[iter] = { D3DXVECTOR3(-1.0f, 0.0f, 0.0f), textMock, D3DXVECTOR4(1.f, 1.f, 1.f, 1.0f) };
	vertices[iter + 1] = { D3DXVECTOR3(0.0f, 1.0f, 0.0f), textMock, D3DXVECTOR4(1.f, 1.f, 1.f, 1.0f) };
	vertices[iter + 2] = { D3DXVECTOR3(0.0f, 0.0f, -1.0f), textMock, D3DXVECTOR4(1.f, 1.f, 1.f, 1.0f) };
	vertices[iter + 3] = { D3DXVECTOR3(0.0f, 1.0f, 0.0f), textMock, D3DXVECTOR4(1.f, .75f, 0.79f, 1.0f) };
	vertices[iter + 4] = { D3DXVECTOR3(0.0f, 0.0f, -1.0f), textMock, D3DXVECTOR4(1.f, .75f, 0.79f, 1.0f) };
	vertices[iter + 5] = { D3DXVECTOR3(1.0f, 0.0f, 0.0f), textMock, D3DXVECTOR4(1.f, .75f, 0.79f, 1.0f) };
	vertices[iter + 6] = { D3DXVECTOR3(-1.0f, 0.0f, 0.0f), textMock, D3DXVECTOR4(0.f, 1.f, 0.f, 1.0f) };
	vertices[iter + 7] = { D3DXVECTOR3(0.0f, -1.0f, 0.0f), textMock, D3DXVECTOR4(0.f, 1.f, 0.f, 1.0f) };
	vertices[iter + 8] = { D3DXVECTOR3(0.0f, 0.0f, -1.0f), textMock, D3DXVECTOR4(0.f, 1.f, 0.f, 1.0f) };
	vertices[iter + 9] = { D3DXVECTOR3(0.0f, 0.0f, -1.0f), textMock, D3DXVECTOR4(0.f, 0.f, 1.f, 1.0f) };
	vertices[iter + 10] = { D3DXVECTOR3(0.0f, -1.0f, 0.0f), textMock, D3DXVECTOR4(0.f, 0.f, 1.f, 1.0f) };
	vertices[iter + 11] = { D3DXVECTOR3(1.0f, 0.0f, 0.0f), textMock, D3DXVECTOR4(0.f, 0.f, 1.f, 1.0f) };
	vertices[iter + 12] = { D3DXVECTOR3(-1.0f, 0.0f, 0.0f), textMock, D3DXVECTOR4(1.f, 0.84f, 0.f, 1.0f) };
	vertices[iter + 13] = { D3DXVECTOR3(0.0f, 1.0f, 0.0f), textMock, D3DXVECTOR4(1.f, 0.84f, 0.f, 1.0f) };
	vertices[iter + 14] = { D3DXVECTOR3(0.0f, 0.0f, 1.0f), textMock, D3DXVECTOR4(1.f, 0.84f, 0.f, 1.0f) };
	vertices[iter + 15] = { D3DXVECTOR3(0.0f, -1.0f, 0.0f), textMock, D3DXVECTOR4(0.f, 1.f, 0.f, 1.0f) };
	vertices[iter + 16] = { D3DXVECTOR3(0.0f, 0.0f, 1.0f), textMock, D3DXVECTOR4(0.4f, 0.f, 0.4f, 1.0f) };
	vertices[iter + 17] = { D3DXVECTOR3(1.0f, 0.0f, 0.0f), textMock, D3DXVECTOR4(0.4f, 0.f, 0.4f, 1.0f) };
	vertices[iter + 18] = { D3DXVECTOR3(-1.0f, 0.0f, 0.0f), textMock, D3DXVECTOR4(.47f, .25f, 0.f, .26f) };
	vertices[iter + 19] = { D3DXVECTOR3(0.0f, -1.0f, 0.0f), textMock, D3DXVECTOR4(.47f, .25f, 0.f, .26f) };
	vertices[iter + 20] = { D3DXVECTOR3(0.0f, 0.0f, 1.0f), textMock, D3DXVECTOR4(.47f, .25f, 0.f, .26f) };
	vertices[iter + 21] = { D3DXVECTOR3(0.0f, 0.0f, 1.0f), textMock, D3DXVECTOR4(1.f, .76f, 0.f, .62f) };
	vertices[iter + 22] = { D3DXVECTOR3(0.0f, -1.0f, 0.0f), textMock, D3DXVECTOR4(1.f, .76f, 0.f, .62f) };
	vertices[iter + 23] = { D3DXVECTOR3(1.0f, 0.0f, 0.0f), textMock, D3DXVECTOR4(1.f, .76f, 0.f, .62f) };*/

	vertices[iter] = { D3DXVECTOR3(0.0f, 0.5f, 0.0f), textMock, D3DXVECTOR4(1.f, 1.f, 1.f, 1.0f) };
	vertices[iter + 1] = { D3DXVECTOR3(-0.5f, 0.0f, 0.0f), textMock, D3DXVECTOR4(1.f, 1.f, 1.f, 1.0f) };
	vertices[iter + 2] = { D3DXVECTOR3(0.0f, 0.0f, 0.5f), textMock, D3DXVECTOR4(1.f, 1.f, 1.f, 1.0f) };
	
	vertices[iter + 3] = { D3DXVECTOR3(0.0f, 0.5f, 0.0f), textMock, D3DXVECTOR4(1.f, .75f, 0.79f, 1.0f) };
	vertices[iter + 4] = { D3DXVECTOR3(0.0f, 0.0f, 0.5f), textMock, D3DXVECTOR4(1.f, .75f, 0.79f, 1.0f) };
	vertices[iter + 5] = { D3DXVECTOR3(0.5f, 0.0f, 0.0f), textMock, D3DXVECTOR4(1.f, .75f, 0.79f, 1.0f) };
	
	vertices[iter + 6] = { D3DXVECTOR3(0.0f, 0.5f, 0.0f), textMock, D3DXVECTOR4(0.f, 1.f, 0.f, 1.0f) };
	vertices[iter + 7] = { D3DXVECTOR3(0.5f, 0.0f, 0.0f), textMock, D3DXVECTOR4(0.f, 1.f, 0.f, 1.0f) };
	vertices[iter + 8] = { D3DXVECTOR3(0.0f, 0.0f, -0.5f), textMock, D3DXVECTOR4(0.f, 1.f, 0.f, 1.0f) };
	
	vertices[iter + 9] = { D3DXVECTOR3(0.0f, 0.5f, 0.0f), textMock, D3DXVECTOR4(0.f, 0.f, 1.f, 1.0f) };
	vertices[iter + 10] = { D3DXVECTOR3(0.0f, 0.0f, -0.5f), textMock, D3DXVECTOR4(0.f, 0.f, 1.f, 1.0f) };
	vertices[iter + 11] = { D3DXVECTOR3(-0.5f, 0.0f, 0.0f), textMock, D3DXVECTOR4(0.f, 0.f, 1.f, 1.0f) };
	
	vertices[iter + 12] = { D3DXVECTOR3(0.0f, -0.5f, 0.0f), textMock, D3DXVECTOR4(1.f, 0.84f, 0.f, 1.0f) };
	vertices[iter + 13] = { D3DXVECTOR3(0.5f, 0.0f, 0.0f), textMock, D3DXVECTOR4(1.f, 0.84f, 0.f, 1.0f) };
	vertices[iter + 14] = { D3DXVECTOR3(0.0f, 0.0f, 0.5f), textMock, D3DXVECTOR4(1.f, 0.84f, 0.f, 1.0f) };
	
	vertices[iter + 15] = { D3DXVECTOR3(0.0f, -0.5f, 0.0f), textMock, D3DXVECTOR4(0.f, 1.f, 0.f, 1.0f) };
	vertices[iter + 16] = { D3DXVECTOR3(0.0f, 0.0f, -0.5f), textMock, D3DXVECTOR4(0.4f, 0.f, 0.4f, 1.0f) };
	vertices[iter + 17] = { D3DXVECTOR3(0.5f, 0.0f, 0.0f), textMock, D3DXVECTOR4(0.4f, 0.f, 0.4f, 1.0f) };
	
	vertices[iter + 18] = { D3DXVECTOR3(0.0f, -0.5f, 0.0f), textMock, D3DXVECTOR4(.47f, .25f, 0.f, .26f) };
	vertices[iter + 19] = { D3DXVECTOR3(-0.5f, 0.0f, 0.0f), textMock, D3DXVECTOR4(.47f, .25f, 0.f, .26f) };
	vertices[iter + 20] = { D3DXVECTOR3(0.0f, 0.0f, -0.5f), textMock, D3DXVECTOR4(.47f, .25f, 0.f, .26f) };
	
	vertices[iter + 21] = { D3DXVECTOR3(0.0f, -0.5f, 0.0f), textMock, D3DXVECTOR4(1.f, .76f, 0.f, .62f) };
	vertices[iter + 22] = { D3DXVECTOR3(0.0f, 0.0f, 0.5f), textMock, D3DXVECTOR4(1.f, .76f, 0.f, .62f) };
	vertices[iter + 23] = { D3DXVECTOR3(-0.5f, 0.0f, 0.0f), textMock, D3DXVECTOR4(1.f, .76f, 0.f, .62f) };

	// Cube
	/*vertices[iter] = { D3DXVECTOR3(-1.0f, 1.0f, -1.0f), textMock, D3DXVECTOR4(1.f, 1.f, 1.f, 1.0f) };
	vertices[iter + 1] = { D3DXVECTOR3(1.0f, 1.0f, -1.0f), textMock, D3DXVECTOR4(1.f, 1.f, 1.f, 1.0f) };
	vertices[iter + 2] = { D3DXVECTOR3(1.0f, 1.0f, 1.0f), textMock, D3DXVECTOR4(1.f, 1.f, 1.f, 1.0f) };
	vertices[iter + 3] = { D3DXVECTOR3(-1.0f, 1.0f, 1.0f), textMock, D3DXVECTOR4(1.f, .75f, 0.79f, 1.0f) };

	vertices[iter + 4] = { D3DXVECTOR3(-1.0f, -1.0f, -1.0f), textMock, D3DXVECTOR4(1.f, .75f, 0.79f, 1.0f) };
	vertices[iter + 5] = { D3DXVECTOR3(1.0f, -1.0f, -1.0f), textMock, D3DXVECTOR4(1.f, .75f, 0.79f, 1.0f) };
	vertices[iter + 6] = { D3DXVECTOR3(1.0f, -1.0f, 1.0f), textMock, D3DXVECTOR4(0.f, 1.f, 0.f, 1.0f) };
	vertices[iter + 7] = { D3DXVECTOR3(-1.0f, -1.0f, 1.0f), textMock, D3DXVECTOR4(0.f, 1.f, 0.f, 1.0f) };

	vertices[iter + 8] = { D3DXVECTOR3(-1.0f, -1.0f, 1.0f), textMock, D3DXVECTOR4(0.f, 1.f, 0.f, 1.0f) };
	vertices[iter + 9] = { D3DXVECTOR3(-1.0f, -1.0f, -1.0f), textMock, D3DXVECTOR4(0.f, 0.f, 1.f, 1.0f) };
	vertices[iter + 10] = { D3DXVECTOR3(-1.0f, 1.0f, -1.0f), textMock, D3DXVECTOR4(0.f, 0.f, 1.f, 1.0f) };
	vertices[iter + 11] = { D3DXVECTOR3(-1.0f, 1.0f, 1.0f), textMock, D3DXVECTOR4(0.f, 0.f, 1.f, 1.0f) };

	vertices[iter + 12] = { D3DXVECTOR3(1.0f, -1.0f, 1.0f), textMock, D3DXVECTOR4(1.f, 0.84f, 0.f, 1.0f) };
	vertices[iter + 13] = { D3DXVECTOR3(1.0f, -1.0f, -1.0f), textMock, D3DXVECTOR4(1.f, 0.84f, 0.f, 1.0f) };
	vertices[iter + 14] = { D3DXVECTOR3(1.0f, 1.0f, -1.0f), textMock, D3DXVECTOR4(1.f, 0.84f, 0.f, 1.0f) };
	vertices[iter + 15] = { D3DXVECTOR3(1.0f, 1.0f, 1.0f), textMock, D3DXVECTOR4(0.f, 1.f, 0.f, 1.0f) };

	vertices[iter + 16] = { D3DXVECTOR3(-1.0f, -1.0f, -1.0f), textMock, D3DXVECTOR4(0.4f, 0.f, 0.4f, 1.0f) };
	vertices[iter + 17] = { D3DXVECTOR3(1.0f, -1.0f, -1.0f), textMock, D3DXVECTOR4(0.4f, 0.f, 0.4f, 1.0f) };
	vertices[iter + 18] = { D3DXVECTOR3(1.0f, 1.0f, -1.0f), textMock, D3DXVECTOR4(.47f, .25f, 0.f, .26f) };
	vertices[iter + 19] = { D3DXVECTOR3(-1.0f, 1.0f, -1.0f), textMock, D3DXVECTOR4(.47f, .25f, 0.f, .26f) };

	vertices[iter + 20] = { D3DXVECTOR3(-1.0f, -1.0f, 1.0f), textMock, D3DXVECTOR4(.47f, .25f, 0.f, .26f) };
	vertices[iter + 21] = { D3DXVECTOR3(1.0f, -1.0f, 1.0f), textMock, D3DXVECTOR4(1.f, .76f, 0.f, .62f) };
	vertices[iter + 22] = { D3DXVECTOR3(1.0f, 1.0f, 1.0f), textMock, D3DXVECTOR4(1.f, .76f, 0.f, .62f) };
	vertices[iter + 23] = { D3DXVECTOR3(-1.0f, 1.0f, 1.0f), textMock, D3DXVECTOR4(1.f, .76f, 0.f, .62f) };*/
}

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
	// Pyramid
	for (int i = iter; i < iter + 12; ++i) {
		indices[i] = tor_vcount + sphere_vcount + (i - iter);
	}
	iter += 12;
	// Octa
	for (int i = iter; i < iter + 24; ++i) {
		indices[i] = tor_vcount + sphere_vcount + (i - iter);
	}
	// Cube
	/*indices[iter] = tor_vcount + sphere_vcount + 12 + 3;
	indices[iter + 1] = tor_vcount + sphere_vcount + 12 + 1;
	indices[iter + 2] = tor_vcount + sphere_vcount + 12 + 0;
	indices[iter + 3] = tor_vcount + sphere_vcount + 12 + 2;
	indices[iter + 4] = tor_vcount + sphere_vcount + 12 + 1;
	indices[iter + 5] = tor_vcount + sphere_vcount + 12 + 3;
	indices[iter + 6] = tor_vcount + sphere_vcount + 12 + 6;
	indices[iter + 7] = tor_vcount + sphere_vcount + 12 + 4;
	indices[iter + 8] = tor_vcount + sphere_vcount + 12 + 5;
	indices[iter + 9] = tor_vcount + sphere_vcount + 12 + 7;
	indices[iter + 10] = tor_vcount + sphere_vcount + 12 + 4;
	indices[iter + 11] = tor_vcount + sphere_vcount + 12 + 6;
	indices[iter + 12] = tor_vcount + sphere_vcount + 12 + 11;
	indices[iter + 13] = tor_vcount + sphere_vcount + 12 + 9;
	indices[iter + 14] = tor_vcount + sphere_vcount + 12 + 8;
	indices[iter + 15] = tor_vcount + sphere_vcount + 12 + 10;
	indices[iter + 16] = tor_vcount + sphere_vcount + 12 + 9;
	indices[iter + 17] = tor_vcount + sphere_vcount + 12 + 11;
	indices[iter + 18] = tor_vcount + sphere_vcount + 12 + 14;
	indices[iter + 19] = tor_vcount + sphere_vcount + 12 + 12;
	indices[iter + 20] = tor_vcount + sphere_vcount + 12 + 13;
	indices[iter + 21] = tor_vcount + sphere_vcount + 12 + 15;
	indices[iter + 22] = tor_vcount + sphere_vcount + 12 + 12;
	indices[iter + 23] = tor_vcount + sphere_vcount + 12 + 14;
	indices[iter + 24] = tor_vcount + sphere_vcount + 12 + 19;
	indices[iter + 25] = tor_vcount + sphere_vcount + 12 + 17;
	indices[iter + 26] = tor_vcount + sphere_vcount + 12 + 16;
	indices[iter + 27] = tor_vcount + sphere_vcount + 12 + 18;
	indices[iter + 28] = tor_vcount + sphere_vcount + 12 + 17;
	indices[iter + 29] = tor_vcount + sphere_vcount + 12 + 19;
	indices[iter + 30] = tor_vcount + sphere_vcount + 12 + 22;
	indices[iter + 31] = tor_vcount + sphere_vcount + 12 + 20;
	indices[iter + 32] = tor_vcount + sphere_vcount + 12 + 21;
	indices[iter + 33] = tor_vcount + sphere_vcount + 12 + 23;
	indices[iter + 34] = tor_vcount + sphere_vcount + 12 + 20;
	indices[iter + 35] = tor_vcount + sphere_vcount + 12 + 22;*/
}

//--------------------------------------------------------------------------------------
// Прорисовка трехмерной сцены
//--------------------------------------------------------------------------------------
void RenderScene()
{
	// Счетчик времени
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


	// Матрица поворота треугольника
	// на угол в зависимости от времени t
	D3DXMatrixRotationY(&g_World, t);

	// Очищаем вторичный буфер
	float ClearColor[4] = { 0.1f, 0.5f, 0.1f, 1.0f }; //компоненты красного, зелеого, синего, прозрачность
	g_pd3dDevice->ClearRenderTargetView(g_pRenderTargetView, ClearColor);

	// Передаем информацию о матрицах преобразования
	g_pWorldVariable->SetMatrix((float*)&g_World);
	g_pViewVariable->SetMatrix((float*)&g_View);
	g_pProjectionVariable->SetMatrix((float*)&g_Projection);


	// Рисуем нашу сцену
	D3D10_TECHNIQUE_DESC techDesc;
	g_pTechnique->GetDesc(&techDesc);
	g_pTechnique->GetPassByIndex(0)->Apply(0); // for torus and sphere
	g_pd3dDevice->DrawIndexed(tor_icount + sphere_icount, 0, 0);
	g_pTechnique->GetPassByIndex(1)->Apply(0);
	g_pd3dDevice->DrawIndexed(36, tor_icount + sphere_icount, 0); // for pyramid
	//g_pd3dDevice->DrawIndexed(36, tor_icount + sphere_icount + 12, 0);
	// Переключаем буферы
	g_pSwapChain->Present(0, 0);
}
//--------------------------------------------------------------------------------------
// Обработка сообщений
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//--------------------------------------------------------------------------------------
// Очищаем память 
//--------------------------------------------------------------------------------------
void Cleanup()
{
	if (g_pd3dDevice) g_pd3dDevice->ClearState();

	if (g_pRenderTargetView) g_pRenderTargetView->Release();
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pd3dDevice) g_pd3dDevice->Release();
}

