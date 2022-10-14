#include "Scene.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "d3dclass.h"
#include "systemclass.h"
#include  <assert.h>
#include "inputclass.h"
#include "SceneMgr.h"

void Scene::render(D3DClass* D3D, float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Clear the buffers to begin the scene.
	D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

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

			// 여기서 2D 랜더링의 경우 ortho 메트릭스를 발동시킨다.

			// Rotate the world matrix by the rotation value so that the triangle will spin.
			worldMatrix = XMMatrixRotationY(rotation);


			// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			m_arrModel[i][j]->Render(D3D->GetDeviceContext());

			// Render the model using the light shader.
			bool result = m_LightShader->Render(D3D->GetDeviceContext(), m_arrModel[i][j]->GetVertexCount(), m_arrModel[i][j]->GetInstanceCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_arrModel[i][j]->GetTexture(),
				m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

			assert(result); 
		}
	}
}

void Scene::update(D3DClass* D3D)
{
	bool result;

	// TODO : 오브젝트들을 업데이트 시킨다.
	if (InputClass::GetInst()->IsKeyDown(VK_LEFT))
	{
		SceneMgr::GetInst()->setCurScene(SCENE_TYPE::START);
	}
	else if (InputClass::GetInst()->IsKeyDown(VK_RIGHT))
	{
		SceneMgr::GetInst()->setCurScene(SCENE_TYPE::STAGE_01);
	}

}

void Scene::AddObject(D3DClass* D3D, GROUP_TYPE _eType)
{
	if(_eType == GROUP_TYPE::DEFAULT)
		m_Model = new ModelClass(D3D->GetDevice(), L"./data/cube.obj", L"./data/seafloor.dds");
	if (_eType == GROUP_TYPE::PLAYER)
		m_Model = new ModelClass(D3D->GetDevice(), L"./data/chair.obj", L"./data/chair_d.dds");

	m_arrModel[(UINT)_eType].push_back(m_Model);
}

Scene::Scene()
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

}
