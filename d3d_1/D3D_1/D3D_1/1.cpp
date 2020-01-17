//--------------------------------------------------------------------------------------
//  ����� ������ �� �����
//--------------------------------------------------------------------------------------

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>

// ������ � ������ ����
#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 728

//--------------------------------------------------------------------------------------
// ���������� ����������
//--------------------------------------------------------------------------------------
HWND        g_hWnd = NULL;
D3D10_DRIVER_TYPE       g_driverType = D3D10_DRIVER_TYPE_NULL;
ID3D10Device*           g_pd3dDevice = NULL;
IDXGISwapChain*         g_pSwapChain = NULL;
ID3D10RenderTargetView* g_pRenderTargetView = NULL;

LPD3DX10FONT			g_pFont1_1 = NULL;
LPD3DX10FONT			g_pFont1_2 = NULL;
LPD3DX10FONT			g_pFont1_3 = NULL;
LPD3DX10FONT			g_pFont1_4 = NULL;
LPD3DX10FONT			g_pFont1_5 = NULL;
LPD3DX10FONT			g_pFont2_1 = NULL;
LPD3DX10FONT			g_pFont2_2 = NULL;
LPD3DX10FONT			g_pFont2_3 = NULL;
LPD3DX10FONT			g_pFont2_4 = NULL;
LPD3DX10FONT			g_pFont2_5 = NULL;
LPD3DX10FONT			g_pFont3_1 = NULL;
LPD3DX10FONT			g_pFont3_2 = NULL;
LPD3DX10FONT			g_pFont3_3 = NULL;
LPD3DX10FONT			g_pFont3_4 = NULL;
LPD3DX10FONT			g_pFont3_5 = NULL;
LPD3DX10FONT			g_pFontNie = NULL;
LPD3DX10FONT			g_pFontLev = NULL;

LPD3DX10FONT* g_pFont1;
LPD3DX10FONT* g_pFont2;
LPD3DX10FONT* g_pFont3;

//--------------------------------------------------------------------------------------
// ��������� �������
//--------------------------------------------------------------------------------------
HRESULT             InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT				InitDirect3D10();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void                Cleanup();
void                RenderScene();

//--------------------------------------------------------------------------------------
// � ���� ������� ���������� ���������� ���������
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ������� ���� ����������
	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;
	// �������������� Direct3D
	if (FAILED(InitDirect3D10()))
	{
		Cleanup();
		return 0;
	}

	// ���� ��������� ���������
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

	return (int)msg.wParam;
}

//--------------------------------------------------------------------------------------
// ����������� ������ � �������� ����
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// ������������ ����� ����
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

	// ������� ����
	g_hWnd = CreateWindow(
		L"SimpleWindowClass",
		L"DirectX 10: ������� ��������. ������ ���",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	// ���� �� ������� ������� ���� - ������� �� �������
	if (!g_hWnd)
		return E_FAIL;
	// ���������� ���� �� ������
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return S_OK;
}

//--------------------------------------------------------------------------------------
// ������������� Direct3D
//--------------------------------------------------------------------------------------
HRESULT InitDirect3D10()
{
	HRESULT hr = S_OK;

	// ������ ������� ���������� ������� ����
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	// ������ ��������� ����� ����������
	D3D10_DRIVER_TYPE driverTypes[] =
	{
		D3D10_DRIVER_TYPE_HARDWARE,
		D3D10_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	// ��������� ��������� 
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

	// �������� ������� ����������, ������� �� ������
	// ��� ������ ���������� - ������� �� �����
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

	// ������������� ������ ���
	// ������ ������������
	ID3D10Texture2D *pBackBuffer;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;
	// �������� ������������� ������
	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;
	// ������ ����� ������������ � ����������� ����������
	g_pd3dDevice->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

	// �������� ������� �����������
	D3D10_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pd3dDevice->RSSetViewports(1, &vp);

	// ������� ��������� ������
	D3DX10CreateFont(g_pd3dDevice, 30, 20, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Verdana", &g_pFont1_1);
	D3DX10CreateFont(g_pd3dDevice, 40, 30, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Verdana", &g_pFont1_2);
	D3DX10CreateFont(g_pd3dDevice, 20, 10, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Verdana", &g_pFont1_3);
	D3DX10CreateFont(g_pd3dDevice, 10, 5, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Verdana", &g_pFont1_4);
	D3DX10CreateFont(g_pd3dDevice, 50, 30, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Verdana", &g_pFont1_5);
	D3DX10CreateFont(g_pd3dDevice, 30, 20, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Times New Roman", &g_pFont2_1);
	D3DX10CreateFont(g_pd3dDevice, 40, 30, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Times New Roman", &g_pFont2_2);
	D3DX10CreateFont(g_pd3dDevice, 20, 10, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Times New Roman", &g_pFont2_3);
	D3DX10CreateFont(g_pd3dDevice, 10, 5, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Times New Roman", &g_pFont2_4);
	D3DX10CreateFont(g_pd3dDevice, 50, 30, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Times New Roman", &g_pFont2_5);
	D3DX10CreateFont(g_pd3dDevice, 30, 20, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Calibri", &g_pFont3_1);
	D3DX10CreateFont(g_pd3dDevice, 40, 30, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Calibri", &g_pFont3_2);
	D3DX10CreateFont(g_pd3dDevice, 20, 10, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Calibri", &g_pFont3_3);
	D3DX10CreateFont(g_pd3dDevice, 10, 5, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Calibri", &g_pFont3_4);
	D3DX10CreateFont(g_pd3dDevice, 50, 30, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Calibri", &g_pFont3_5);
	D3DX10CreateFont(g_pd3dDevice, 200, 100, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Gothica", &g_pFontNie);
	D3DX10CreateFont(g_pd3dDevice, 20, 10, 1, 1, FALSE, 0, 0, 0, DEFAULT_PITCH | FF_MODERN, L"Gothica", &g_pFontLev);
	g_pFont1 = new LPD3DX10FONT[5];
	g_pFont1[0] = g_pFont1_1;
	g_pFont1[1] = g_pFont1_2;
	g_pFont1[2] = g_pFont1_3;
	g_pFont1[3] = g_pFont1_4;
	g_pFont1[4] = g_pFont1_5;
	g_pFont2 = new LPD3DX10FONT[5];
	g_pFont2[0] = g_pFont2_1;
	g_pFont2[1] = g_pFont2_2;
	g_pFont2[2] = g_pFont2_3;
	g_pFont2[3] = g_pFont2_4;
	g_pFont2[4] = g_pFont2_5;
	g_pFont3 = new LPD3DX10FONT[5];
	g_pFont3[0] = g_pFont3_1;
	g_pFont3[1] = g_pFont3_2;
	g_pFont3[2] = g_pFont3_3;
	g_pFont3[3] = g_pFont3_4;
	g_pFont3[4] = g_pFont3_5;

	return S_OK;
}

//--------------------------------------------------------------------------------------
// ���������� ���������� �����
//--------------------------------------------------------------------------------------
void RenderScene()
{
	// ������� ��������� �����
	float ClearColor[4] = { rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.), 1.0f }; //���������� ��������, ��������, ������, ������������
	g_pd3dDevice->ClearRenderTargetView(g_pRenderTargetView, ClearColor);

	//������� �������������� ��� �������������� ������
	RECT Rect;
	Rect.left = 10;
	Rect.top = 10;
	Rect.right = WINDOW_WIDTH - 100;
	Rect.bottom = WINDOW_HEIGHT - 100;

	g_pFont1[rand() % 5]->DrawText(NULL, L"������ �����������", -1, &Rect, DT_LEFT, D3DXCOLOR(rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.), 1.0));
	g_pFont2[rand() % 5]->DrawText(NULL, L"������ ����", -1, &Rect, DT_CENTER | DT_VCENTER, D3DXCOLOR(rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.), 1.0));
	g_pFont3[rand() % 5]->DrawText(NULL, L"������� ������", -1, &Rect, DT_RIGHT | DT_BOTTOM, D3DXCOLOR(rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.), 1.0));
	g_pFontNie->DrawText(NULL, L"�����", -1, &Rect, DT_RIGHT | DT_TOP, D3DXCOLOR(0, 0, 0, 1));
	g_pFontLev->DrawText(NULL, L"��� ������", -1, &Rect, DT_LEFT | DT_BOTTOM, D3DXCOLOR(0, 0, 0, 1));

	g_pSwapChain->Present(0, 0);
}
//--------------------------------------------------------------------------------------
// ��������� ���������
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
// ������� ������ 
//--------------------------------------------------------------------------------------
void Cleanup()
{
	if (g_pd3dDevice) g_pd3dDevice->ClearState();

	if (g_pRenderTargetView) g_pRenderTargetView->Release();
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pd3dDevice) g_pd3dDevice->Release();

	if (g_pFont1_1) g_pFont1_1->Release();
	if (g_pFont1_2) g_pFont1_2->Release();
	if (g_pFont1_3) g_pFont1_3->Release();
	if (g_pFont1_4) g_pFont1_4->Release();
	if (g_pFont1_5) g_pFont1_5->Release();
	if (g_pFont2_1) g_pFont2_1->Release();
	if (g_pFont2_2) g_pFont2_2->Release();
	if (g_pFont2_3) g_pFont2_3->Release();
	if (g_pFont2_4) g_pFont2_4->Release();
	if (g_pFont2_5) g_pFont2_5->Release();
	if (g_pFont3_1) g_pFont3_1->Release();
	if (g_pFont3_2) g_pFont3_2->Release();
	if (g_pFont3_3) g_pFont3_3->Release();
	if (g_pFont3_4) g_pFont3_4->Release();
	if (g_pFont3_5) g_pFont3_5->Release();
	if (g_pFontNie) g_pFontNie->Release();
	if (g_pFontLev) g_pFontNie->Release();

	if (g_pFont1) delete[] g_pFont1;
	if (g_pFont2) delete[] g_pFont2;
	if (g_pFont3) delete[] g_pFont3;
}

