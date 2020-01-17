//---------------------------------------------------------------------------
// Meshobj.cpp
// Загрузка объекта из мешей    
//---------------------------------------------------------------------------
#include <d3d10.h>
#include <d3dx10.h>
#include <fstream>
using namespace std;
#include "meshobj.h"
//---------------------------------------------------------------------------
// Формат структуры VERTEX должен совпадать с форматом вершинного буфера 
//---------------------------------------------------------------------------
struct VERTEX
{
    D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
    D3DXVECTOR2 texcoord;
};
//---------------------------------------------------------------------------
// Временный буфер для хранения вершин и индексов
//---------------------------------------------------------------------------
struct {
    VERTEX vertices[buffermax];
    DWORD  indices[buffermax];
    int    verticesI;
    int    indicesI;
} buffer;
//---------------------------------------------------------------------------
// Определение методов класса MeshFromObj
//---------------------------------------------------------------------------
MeshFromObj::MeshFromObj(ID3D10Device * pd3dDevice, ID3D10Effect * pEffect, char * techname, char * fname)
{
	c_pd3dDevice=pd3dDevice;
	c_pEffect=pEffect;
	c_pTechnique=NULL;
	c_pVertexLayout=NULL;
	c_pVertexBuffer=NULL;
	c_pIndexBuffer=NULL;
	techniquename=techname;
	meshloaded=false;
	LoadMeshFromObj(fname); if (buffer.verticesI==0) return;
	HRESULT hr=CreateVertexAndIndexBuffers();
	if (!FAILED(hr)) meshloaded=true; 	
}
//---------------------------------------------------------------------------
// Деструктор объекта MeshFromObj
//---------------------------------------------------------------------------
MeshFromObj::~MeshFromObj()
{
    if( c_pVertexBuffer ) c_pVertexBuffer->Release();
    if( c_pIndexBuffer ) c_pIndexBuffer->Release();
    if( c_pVertexLayout ) c_pVertexLayout->Release();
}
//---------------------------------------------------------------------------
// Фукнция создания вершинного и индексного буферов, 
// эта функция должна вызываться после функции LoadMeshFromObj
//---------------------------------------------------------------------------
HRESULT MeshFromObj::CreateVertexAndIndexBuffers()
{
	//определяем количество вершин и количество индексов
	verticesCount=buffer.verticesI;
	indicesCount=buffer.indicesI;

	//Hresult
	HRESULT hr;

	// Получаем технику
    c_pTechnique = c_pEffect->GetTechniqueByName( techniquename );

	// Определяем формат вершинного буфера
	D3D10_INPUT_ELEMENT_DESC layout[] =
	{
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },   
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
    UINT numElements = sizeof( layout ) / sizeof( layout[0] );

    // Создание объекта для задания формата буфера
    D3D10_PASS_DESC PassDesc;
    c_pTechnique->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    hr = c_pd3dDevice->CreateInputLayout( layout, numElements, PassDesc.pIAInputSignature,
                                          PassDesc.IAInputSignatureSize, &c_pVertexLayout );
    if( FAILED( hr ) )
        return hr;

 	// Заполняем вершинный буфер
	D3D10_BUFFER_DESC bd;
    bd.Usage = D3D10_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( VERTEX ) * (verticesCount+1);
    bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = buffer.vertices;
    hr = c_pd3dDevice->CreateBuffer( &bd, &InitData, &c_pVertexBuffer );
    if( FAILED( hr ) )
        return hr;

    bd.Usage = D3D10_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( DWORD ) * indicesCount;        
    bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
	InitData.pSysMem = buffer.indices;
    hr = c_pd3dDevice->CreateBuffer( &bd, &InitData, &c_pIndexBuffer );
    if( FAILED( hr ) )
        return hr;
}
//---------------------------------------------------------------------------
void MeshFromObj::Draw()
{
    if(meshloaded)
	{
    // Установка форамата в Direct3D
    c_pd3dDevice->IASetInputLayout( c_pVertexLayout );

	// Установка вершинного буфера
    UINT stride = sizeof( VERTEX );
    UINT offset = 0;
    c_pd3dDevice->IASetVertexBuffers( 0, 1, &c_pVertexBuffer, &stride, &offset );

    // Установка индексного буфера
    c_pd3dDevice->IASetIndexBuffer( c_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0 );

    // Установка топологии буфера
    c_pd3dDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	D3D10_TECHNIQUE_DESC techDesc;
    c_pTechnique->GetDesc( &techDesc );
    c_pTechnique->GetPassByIndex( 0 )->Apply( 0 );
    c_pd3dDevice->DrawIndexed( indicesCount, 0, 0 ); 
	}
}
//---------------------------------------------------------------------------
// Функции для добавления вершин и индексов
//---------------------------------------------------------------------------
int AddVertex(int vertexI, VERTEX vertex)
{
	int res=-1;
	//Поиск существующей вершины
	for (int i=0; i<buffer.verticesI; i++)
		if (memcmp(&buffer.vertices[i],&vertex,sizeof(VERTEX))==0) res=i;
	//Добавление
	if (res<0) {
		buffer.vertices[buffer.verticesI++]=vertex; res=buffer.verticesI-1; }
	return res;
}
//---------------------------------------------------------------------------
void AddIndex(int index)
{
    buffer.indices[buffer.indicesI++]=index;
}
//---------------------------------------------------------------------------
// Функция осуществляет проход файла obj и загрузку из него данных
// вершинного и индексного буфера
//---------------------------------------------------------------------------
void MeshFromObj::LoadMeshFromObj(char * fname)
{
    // Очистка данных
    buffer.verticesI=0;
    buffer.indicesI=0;

    //Создание временного хранилища входящих данных, как только данные будут
    //загружены в подходящий формат скопируем эти данные в вершинный и индексный буферы
    D3DXVECTOR3 * Positions=(D3DXVECTOR3*)malloc(buffermax*sizeof(D3DXVECTOR3));
    D3DXVECTOR2 * TexCoords=(D3DXVECTOR2*)malloc(buffermax*sizeof(D3DXVECTOR2));
    D3DXVECTOR3 * Normals=(D3DXVECTOR3*)malloc(buffermax*sizeof(D3DXVECTOR3));

    // Индексы для массивов
    int PositionsI=0;
    int TexCoordsI=0;
    int NormalsI=0;

    // Ввод данных из файла
    //char fname[256];
    //strcpy(fname,Edit1->Text.c_str());
    WCHAR strCommand[256] = {0};
    wifstream InFile( fname );

    if( !InFile ) return;

    for(; ; )
    {
        InFile >> strCommand;
        if( !InFile )
            break;

        if( 0 == wcscmp( strCommand, L"#" ) )
        {
            // Комментарий
        }
        else if( 0 == wcscmp( strCommand, L"v" ) )
        {
            // Координаты
            float x, y, z;
            InFile >> x >> y >> z;
            Positions[PositionsI++]=D3DXVECTOR3(x,y,z)*0.05f;
        }
        else if( 0 == wcscmp( strCommand, L"vt" ) )
        {
            // Текстурные координаты
            float u, v;
            InFile >> u >> v;
			TexCoords[TexCoordsI++]=D3DXVECTOR2(u,-v);
        }
        else if( 0 == wcscmp( strCommand, L"vn" ) )
        {
            // Нормали
            float x, y, z;
            InFile >> x >> y >> z;
            Normals[NormalsI++]=D3DXVECTOR3(x,y,z);
        }
        else if( 0 == wcscmp( strCommand, L"f" ) )
        {
            // Face
            UINT iPosition, iTexCoord, iNormal;
            VERTEX vertex;

            for( UINT iFace = 0; iFace < 3; iFace++ )
            {
                ZeroMemory( &vertex, sizeof( VERTEX ) );

                // OBJ формат использует массивы с индексами от 1
                InFile >> iPosition;
                vertex.position = Positions[ iPosition - 1 ];

                if( '/' == InFile.peek() )
                {
                    InFile.ignore();

                    if( '/' != InFile.peek() )
                    {
                        // Опционно текстурные координаты
                        InFile >> iTexCoord;
                        vertex.texcoord = TexCoords[ iTexCoord - 1 ];
                    }

                    if( '/' == InFile.peek() )
                    {
                        InFile.ignore();

                        // Опционно нормали
                        InFile >> iNormal;
                        vertex.normal = Normals[ iNormal - 1 ];
                    }
                }

                //Добавляем вершину и индекс
                int index=AddVertex( iPosition, vertex );
                AddIndex( index );

            }
    }
    }
    InFile.close();

    //Очистка временных массивов
    free(Positions);
    free(TexCoords);
    free(Normals);
}
//---------------------------------------------------------------------------