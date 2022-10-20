#pragma once
#include "Title_Scene.h"
#include "modelclass.h"
#include "d3dclass.h"
#include "systemclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "textureclass.h"

Title_Scene::Title_Scene()
{

}

Title_Scene::~Title_Scene()
{

}

void Title_Scene::init(D3DClass* D3D)
{
	bool result;

	// 모델들을을 생성 후, 벡터에 추가

	// TODO : 타이틀 씬에서 생성할 도형들을 벡터에 추가
	AddObject(D3D, GROUP_TYPE::DEFAULT);
	AddObject(D3D, GROUP_TYPE::PLAYER);

	// 라이트 효과 추가
	if (m_Light == nullptr)
	{
		// Create the light object.
		m_Light = new LightClass;

		assert(m_Light);

		// Initialize the light object.
		m_Light->SetAmbientColor(0.8f, 0.8f, 0.8f, 1.0f);
		m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light->SetDirection(0.0f, 0.5f, 0.5f);
		m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light->SetSpecularPower(32.0f);
	}

	if (m_LightShader == nullptr)
	{
		// Create the light shader object.
		m_LightShader = new LightShaderClass;

		// Initialize the light shader object.
		result = m_LightShader->Initialize(D3D->GetDevice(), SystemClass::GetInst()->GetHwnd());

		assert(result);
	}

	// Create the texture shader object.
	if (m_TextureShader == nullptr)
	{
		m_TextureShader = new TextureShaderClass;

		// Initialize the texture shader object.
		result = m_TextureShader->Initialize(D3D->GetDevice(), SystemClass::GetInst()->GetHwnd());
		if (!result)
		{
			MessageBox(SystemClass::GetInst()->GetHwnd(), L"Could not initialize the texture shader object.", L"Error", MB_OK);
		}
	}

	// Create the bitmap object.
	if (m_Bitmap == nullptr)
	{
		m_Bitmap = new BitmapClass;

		// Initialize the bitmap object.
		result = m_Bitmap->Initialize(D3D->GetDevice(), 800, 600, L"./data/UI.dds", 800, 100);
		if (!result)
		{
			MessageBox(SystemClass::GetInst()->GetHwnd(), L"Could not initialize the bitmap object.", L"Error", MB_OK);
		}
	}

	if (m_Camera == nullptr)
	{
		m_Camera = new CameraClass;

		// Set the initial position of the camera.
		m_Camera->SetPosition(0.0f, 0.0f, -5.0f);	// for cube
	}

	// Create the text object.
	if (m_Text == nullptr)
	{
		m_Camera->Render();
		m_Camera->GetViewMatrix(m_baseViewMatrix);

		m_Text = new TextClass;

		// Initialize the text object.
		result = m_Text->Initialize(D3D->GetDevice(), D3D->GetDeviceContext(), SystemClass::GetInst()->GetHwnd(), 800, 600, m_baseViewMatrix);
		if (!result)
		{
			MessageBox(SystemClass::GetInst()->GetHwnd(), L"Could not initialize the text object.", L"Error", MB_OK);
		}
	}

}

void Title_Scene::Exit()
{

}
