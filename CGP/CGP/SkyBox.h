#pragma once
#include <vector>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <directxmath.h>

#include "AlignedAllocationPolicy.h"

using namespace DirectX;

class SkyBox
{
	ID3D11Buffer* sphereIndexBuffer;
	ID3D11Buffer* sphereVertBuffer;
	ID3D11VertexShader* SKYMAP_VS;
	ID3D11PixelShader* SKYMAP_PS;
	ID3D10Blob* SKYMAP_VS_Buffer;
	ID3D10Blob* SKYMAP_PS_Buffer;
	ID3D11ShaderResourceView* smrv;
	ID3D11DepthStencilState* DSLessEqual;
	ID3D11RasterizerState* RSCullNone;
	int NumSphereVertices;
	int NumSphereFaces;
	XMMATRIX sphereWorld;
public:

	void CreateSphere(int LatLines, int LongLines);
	void ShutDown();
	void Render();
	void init();
};

