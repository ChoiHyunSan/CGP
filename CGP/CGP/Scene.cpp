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

void Scene::render(D3DClass* D3D, float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;

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
		for(int j = 0; j < m_arrModel[i].size(); i++)
		{
			// Generate the view matrix based on the camera's position.
			m_Camera->Render();

			// Get the world, view, and projection matrices from the camera and d3d objects.
			m_Camera->GetViewMatrix(viewMatrix);
			D3D->GetWorldMatrix(worldMatrix);
			D3D->GetProjectionMatrix(projectionMatrix);

			// 뷰 메트릭스 조절
			viewMatrix *= XMMatrixRotationX(-0.8f) * XMMatrixTranslation(0,-8,20);

			// 월드 메트릭스 조절
			worldMatrix = 
				m_arrModel[i][j]->getRotate() * m_arrModel[i][j]->getScale() *
				XMMatrixTranslation(m_arrModel[i][j]->getPos().x, m_arrModel[i][j]->getPos().y-2, m_arrModel[i][j]->getPos().z);

			// 여기서 2D 랜더링의 경우 ortho 메트릭스를 발동시킨다.


			// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			m_arrModel[i][j]->Render(D3D->GetDeviceContext());

			// Render the model using the light shader.
			result = m_LightShader->Render(D3D->GetDeviceContext(), m_arrModel[i][j]->GetVertexCount(), m_arrModel[i][j]->GetInstanceCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_arrModel[i][j]->GetTexture(),
				m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

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
	// Initialize a base view matrix with the camera for 2D user interface rendering.
	//m_Camera->SetPosition(0.0f, 0.0f, -1.0f);

	D3D->TurnOnAlphaBlending();

	result = m_Text->Render(D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	
	D3D->TurnOffAlphaBlending();

	D3D->TurnZBufferOn();
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

	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrModel[i].size(); i++)
		{
			m_arrModel[i][j]->Update();
		}
	}

}

void Scene::AddObject(D3DClass* D3D, GROUP_TYPE _eType)
{
	if(_eType == GROUP_TYPE::DEFAULT)
		m_Model = new ModelClass(D3D->GetDevice(), GROUP_TYPE::DEFAULT);

	if (_eType == GROUP_TYPE::PLAYER)
		m_Model = new Player(D3D->GetDevice(), GROUP_TYPE::PLAYER);

	if (_eType == GROUP_TYPE::BOMB)
		m_Model = new Bomb(D3D->GetDevice(), GROUP_TYPE::BOMB);

	m_arrModel[(UINT)_eType].push_back(m_Model);
}

void Scene::ClearObjects(GROUP_TYPE _eType)
{
	m_arrModel[(UINT)_eType].clear();
}

Scene::Scene():
	m_Model(0),
	m_Camera(0),
	m_Light(0),
	m_LightShader(0),
	m_Bitmap(0),
	m_TextureShader(0),
	m_Text(0)
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
}
