////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textureclass.h"
#include <vector>
#include <dinput.h>
#include <cstdlib>
#include<ctime>

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
#define D3DX_PI    ((FLOAT)  3.141592654f)

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	void SetAmbientEffect();
	void SetDiffuseEffect();
	void SetSpecularColorEffect();

private:
	bool Render(float);
	float RandNum(int);
private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	bool isLightOn[3] = {true, true , true};
	int m_screenWidth; 
	int m_screenHeight;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	float rotate;
	vector<ModelClass*> m_Models;
	TextureClass* m_TextureShader;
	bool isArrive = false;

	/////////////////
	XMVECTOR   m_Eye;                  // 카메라 위치        (위치)
	XMVECTOR   m_At;                 // 카메라가 보는 곳 (위치)
	XMVECTOR   m_Up;                    // 카메라의 기준 축 ( 축이 위로 향하는 카메라 방향 )

	LightClass* m_Light1, * m_Light2, * m_Light3, * m_Light4;
public:

};

#endif