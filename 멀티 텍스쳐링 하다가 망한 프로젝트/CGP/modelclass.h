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
#include "pch.h"
#include "Collider.h"

using namespace DirectX;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"
#include <fstream>
#include "texturearrayclass.h"
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
		float tx, ty, tz;
		float bx, by, bz;
	};

	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VectorType
	{
		float x, y, z;
	};

	struct InstanceType
	{
		XMFLOAT3 position;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	ModelClass(ID3D11Device*, GROUP_TYPE type);
	ModelClass(ID3D11Device*, GROUP_TYPE type, Pos pos);

	virtual ~ModelClass();

	bool Initialize(ID3D11Device* , GROUP_TYPE type);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	ID3D11ShaderResourceView* GetTexture();

	bool LoadModel(const WCHAR*);
	void ReleaseModel();

	int GetVertexCount();
	int GetInstanceCount();
	ID3D11ShaderResourceView** GetTextureArray();

	GROUP_TYPE GetType();
	Pos getPos() const{ return m_Pos; }
	void correctPos();

	XMMATRIX getRotate() { return m_rotate; }
	XMMATRIX getScale() { return m_scale; }

	bool IsDead() const { return !m_bAlive; }
	void SetDead() { m_bAlive = false; }

	Collider* GetCollider() const { return m_pCollider; }

	virtual void finalUpdate() final;
	void CreateCollider();

	const wstring& GetName() { return m_strName; }
	void SetName(const wstring& str) { m_strName = str; }
private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTextures(ID3D11Device*, const WCHAR*, const WCHAR*);
	void ReleaseTextures();

	bool ReadFileCounts(const WCHAR*);
	bool LoadDataStructures(const WCHAR*, int, int, int, int);

	void CalculateModelVectors();
	void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);
	void CalculateNormal(VectorType, VectorType, VectorType&);

	void setInstPosInfo();
	void setFileInfo();
	
public:
	virtual void Update();

	// ?????????????? ???????? ?????? ?????????? ????????.
	virtual void OnCollision(Collider* _pOther);
	virtual void OnCollisionEnter(Collider* _pOther);
	virtual void OnCollisionExit(Collider* _pOther);

protected:
	void setPos(float ,float ,float);
	void addPos(float ,float ,float);
	void setRotate(char, float);
	void setScale(float, float, float);

private:
	ID3D11Buffer *m_vertexBuffer;
	int m_vertexCount, m_textureCount, m_normalCount, m_faceCount;
	TextureClass* m_Texture1;
	TextureClass* m_Texture2;


	ID3D11Buffer * m_instanceBuffer;
	int m_instanceCount;

	GROUP_TYPE m_ObjType;
	ModelType* m_model;

	Pos m_Pos;
	XMMATRIX m_rotate;
	XMMATRIX m_scale;

	GROUP_TYPE m_type;
	WCHAR* m_modelFilename;
	WCHAR* m_textureFilename1;
	WCHAR* m_textureFilename2;
	TextureArrayClass* m_TextureArray;

	bool m_bAlive = true;

	Collider* m_pCollider;

	wstring m_strName;

protected:
	vector<XMFLOAT3> m_vInstancePos;
	friend class EventMgr;
	friend class Fire;
};

#endif