////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
#include <vector>
using namespace DirectX;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"

#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
	    XMFLOAT2 texture;
		XMFLOAT3 normal;
		XMFLOAT3 instancePosition;
	};

	struct FaceType
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct InstanceType
	{
		XMFLOAT3 position;
	};

public:
	ModelClass();
	ModelClass(ID3D11Device* device, const WCHAR* modelFilename, const WCHAR* textureFilename1, const WCHAR* textureFilename2, vector<XMFLOAT3> instancePosition, int instanceCount, XMFLOAT3 modelScail);
	~ModelClass();

	bool Initialize(ID3D11Device*, const WCHAR*, const WCHAR*,  const WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetVertexCount();
	int GetInstanceCount();
	ID3D11ShaderResourceView** GetTextureArray();

	bool LoadModel(const WCHAR*);
	void ReleaseModel();
	float m_x, m_y, m_z;
	XMFLOAT3 m_modelScail;
	int m_RandScail;
private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, const WCHAR*, const WCHAR*);
	void ReleaseTexture();

	bool ReadFileCounts(const WCHAR*);
	bool LoadDataStructures(const WCHAR*, int, int, int, int);

private:
	ID3D11Buffer *m_vertexBuffer;
	int m_vertexCount, m_textureCount, m_normalCount, m_faceCount;
	TextureClass* m_TextureArray;
	ID3D11Buffer* m_instanceBuffer;
	ModelType* m_model;
	vector<XMFLOAT3> m_instancePosition;
};

#endif