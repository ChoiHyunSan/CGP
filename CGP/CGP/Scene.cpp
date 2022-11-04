#pragma once
#include "Scene.h"
#include "modelclass.h"
#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "lightshaderclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "d3dclass.h"
#include "systemclass.h"
#include  <assert.h>
#include "inputclass.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Bomb.h"
#include "bitmapclass.h"
#include "textureshaderclass.h"
#include "textureclass.h"
#include "GameMgr.h"
#include "Enemy.h"
#include "EffectClass.h"
#include "fireshaderclass.h"
#include "Fire.h"

void Scene::render(D3DClass* D3D, float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	
	// effet를 위한 변수 선언
	XMFLOAT3 scrollSpeeds, scales;
	XMFLOAT2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	static float frameTime = 0.0f;

	bool result;
	// Clear the buffers to begin the scene.
	//D3D->BeginScene(163 / 255.0f, 230 / 255.0f, 163 / 255.0f, 1.0f);
	D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	D3D->GetWorldMatrix(worldMatrix);
	D3D->GetProjectionMatrix(projectionMatrix);

	for (int i = 0; i< (UINT)GROUP_TYPE::END; i++)
	{
		for(int j = 0; j < m_arrModel[i].size(); j++)
		{
			// Generate the view matrix based on the camera's position.
			m_Camera->Render();

			// Get the world, view, and projection matrices from the camera and d3d objects.
			m_Camera->GetViewMatrix(viewMatrix);

			D3D->GetWorldMatrix(worldMatrix);
			D3D->GetProjectionMatrix(projectionMatrix);

			// 뷰 메트릭스 조절
			viewMatrix *= XMMatrixRotationX(-0.8) * XMMatrixTranslation(0,-8,20);

			// 월드 메트릭스 조절
			worldMatrix = 
				m_arrModel[i][j]->getRotate() * m_arrModel[i][j]->getScale() *
				XMMatrixTranslation(m_arrModel[i][j]->getPos().x, m_arrModel[i][j]->getPos().y-2, m_arrModel[i][j]->getPos().z);

			// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			m_arrModel[i][j]->Render(D3D->GetDeviceContext());

			// Render the model using the light shader.
			result = m_LightShader->Render(D3D->GetDeviceContext(), m_arrModel[i][j]->GetVertexCount(), m_arrModel[i][j]->GetInstanceCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_arrModel[i][j]->GetTexture(),
				m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());


			m_arrModel[i][j]->finalUpdate();

			assert(result); 
		}
	}

	m_Camera->GetViewMatrix(viewMatrix);

	D3D->GetWorldMatrix(worldMatrix);
	D3D->GetProjectionMatrix(projectionMatrix);
	D3D->GetOrthoMatrix(orthoMatrix);
	D3D->TurnZBufferOff();

	result = m_Bitmap->Render(D3D->GetDeviceContext(), 0, 500);

	m_TextureShader->Render(D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), 
		worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());

	D3D->GetWorldMatrix(worldMatrix);
	D3D->GetProjectionMatrix(projectionMatrix);
	D3D->GetOrthoMatrix(orthoMatrix);

	D3D->TurnOnAlphaBlending();

	result = m_Text->Render(D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	
	D3D->TurnOffAlphaBlending();

	D3D->TurnZBufferOn();

	// frameTime 카운터를 증가시킵니다.
	frameTime += 0.01f;
	if (frameTime > 1000.0f)
	{
		frameTime = 0.0f;
	}
	// 세 노이즈 텍스쳐의 스크롤 속도를 설정합니다.
	scrollSpeeds = XMFLOAT3(1.3f, 2.1f, 2.3f);

	// 세 크기값을 사용하여 세 가지의 다른 노이즈 옥타브 텍스쳐를 만듭니다.
	scales = XMFLOAT3(1.0f, 2.0f, 3.0f);

	// 세 노이즈 텍스쳐의 서로 다른 세 개의 x, y 왜곡 인자를 설정합니다.
	distortion1 = XMFLOAT2(0.1f, 0.2f);
	distortion2 = XMFLOAT2(0.1f, 0.3f);
	distortion3 = XMFLOAT2(0.1f, 0.1f);

	// 텍스쳐 샘플링 좌표의 교란을 위한 크기 및 바이어스 값입니다.
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	D3D->TurnOnAlphaBlending();

	for (int i = 0; i < (UINT)EFFECT_TYPE::END; ++i)
	{
		for (int j = 0; j < m_arrEffect[i].size(); ++j)
		{
			// 카메라의 위치에 기반하여 뷰 행렬을 생성합니다.
			m_Camera->Render();
			
			// 카메라와 d3d객체에서 월드, 뷰, 투영 행렬을 가져옵니다.
			D3D->GetWorldMatrix(worldMatrix);
			m_Camera->GetViewMatrix(viewMatrix);
			D3D->GetProjectionMatrix(projectionMatrix);

			m_Effect->Render(D3D->GetDeviceContext());
			viewMatrix *= XMMatrixRotationX(-0.8) * XMMatrixTranslation(0, -8, 20);
			worldMatrix *= XMMatrixRotationX(3.141592 / 2) * XMMatrixTranslation(0.0f, -4.55f, 0.0f) * XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMMatrixTranslation(m_arrEffect[i][j]->getPos().x, m_arrEffect[i][j]->getPos().y -2 , m_arrEffect[i][j]->getPos().z);

			result = m_FireShader->Render(D3D->GetDeviceContext(), m_arrEffect[i][j]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_arrEffect[i][j]->GetTexture1(), m_arrEffect[i][j]->GetTexture2(), m_arrEffect[i][j]->GetTexture3(), frameTime, scrollSpeeds,
				scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
		
			m_arrEffect[i][j]->finalUpdate();
		}
	}

	// 알파 블렌딩을 끕니다.
	D3D->TurnOffAlphaBlending();

}

void Scene::update(D3DClass* D3D)
{
	bool result;

	// TODO : 오브젝트들을 업데이트 시킨다.
	if (InputClass::GetInst()->IsKeyDown(0x60))
	{
		SceneMgr::GetInst()->setCurScene(SCENE_TYPE::START);
	}
	else if (InputClass::GetInst()->IsKeyDown(0x61))
	{
		SceneMgr::GetInst()->setCurScene(SCENE_TYPE::STAGE_01);
	}
	GameMgr::GetInst()->update();
	m_Text->update();

	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrModel[i].size(); i++)
		{
			m_arrModel[i][j]->Update();
		}
	}
	for (int i = 0; i < (UINT)EFFECT_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrEffect[i].size(); i++)
		{
			m_arrEffect[i][j]->Update();
		}
	}
}

void Scene::AddObject(D3DClass* D3D, GROUP_TYPE _eType, Pos pos)
{
	if(_eType == GROUP_TYPE::DEFAULT)
		m_Model = new ModelClass(D3D->GetDevice(), GROUP_TYPE::DEFAULT, pos);

	if (_eType == GROUP_TYPE::PLAYER)
		m_Model = new Player(D3D->GetDevice());

	if (_eType == GROUP_TYPE::BOMB)
		m_Model = new Bomb(D3D->GetDevice());

	if (_eType == GROUP_TYPE::ENEMY)
		m_Model = new Enemy(D3D->GetDevice());

	m_arrModel[(UINT)_eType].push_back(m_Model);
}

void Scene::AddEffect(D3DClass* D3D, EFFECT_TYPE _eType, Pos pos)
{
	if (_eType == EFFECT_TYPE::FIRE)
	{
		m_Effect = new Fire(D3D->GetDevice(), pos);
		
	}
	m_arrEffect[(UINT)_eType].push_back(m_Effect);
}

void Scene::ClearObjects(GROUP_TYPE _eType)
{
	m_arrModel[(UINT)_eType].clear();
}

void Scene::ClearEffects(EFFECT_TYPE _eType)
{
	m_arrEffect[(UINT)_eType].clear();
}

Scene::Scene():
	m_Model(0),
	m_Camera(0),
	m_Light(0),
	m_LightShader(0),
	m_Bitmap(0),
	m_TextureShader(0),
	m_Text(0),
	m_Effect(0),
	m_FireShader(0)
{

}

Scene::~Scene()
{
	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}
	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the Effect object.
	if (m_Effect)
	{
		m_Effect->Shutdown();
		delete m_Effect;
		m_Effect = 0;
	}

	// Release the fire shader object.
	if (m_FireShader)
	{
		m_FireShader->Shutdown();
		delete m_FireShader;
		m_FireShader = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrModel[i].size(); j++)
		{
			delete m_arrModel[i][j];
		}
	}

	for (int i = 0; i < (UINT)EFFECT_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrEffect[i].size(); j++)
		{
			delete m_arrEffect[i][j];
		}
	}

}
