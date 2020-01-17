//---------------------------------------------------------------------------
// Meshobj.h
// �������� ������� �� �����    
//---------------------------------------------------------------------------
#include <d3d10.h>
#include <d3dx10.h>
//---------------------------------------------------------------------------
// ������ ������������ ���������� ������ � ��������. ��� ��������
// ����� ��������� ���� ��������� ��������� ������� ����       
//---------------------------------------------------------------------------
const int buffermax=16384;
//---------------------------------------------------------------------------
// ������� ����� ��� �������� � �������� �����. �������� ��������� �����������
// ������� ������ ��� �������� � ���� ���������� ���������� �����
//---------------------------------------------------------------------------
class MeshFromObj
{
	public:
	MeshFromObj(ID3D10Device * pd3dDevice, ID3D10Effect * pEffect, char * techname, char * fname);
	void Draw();
	~MeshFromObj();

	protected:
	ID3D10Device*               c_pd3dDevice;
	ID3D10Effect*               c_pEffect;
	ID3D10EffectTechnique*      c_pTechnique;
	ID3D10InputLayout*          c_pVertexLayout;
	ID3D10Buffer*               c_pVertexBuffer;
	ID3D10Buffer*               c_pIndexBuffer;
	int						    verticesCount;
	int						    indicesCount;
	char*					    techniquename;
	bool						meshloaded;
	void LoadMeshFromObj(char * fname);
	HRESULT CreateVertexAndIndexBuffers();
};
//---------------------------------------------------------------------------