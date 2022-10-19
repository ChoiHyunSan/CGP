#include "Stage01_Scene.h"
#include "modelclass.h"
#include "d3dclass.h"
#include "systemclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "textureclass.h"

Stage01_Scene::Stage01_Scene()
{

}

Stage01_Scene::~Stage01_Scene()
{

}

void Stage01_Scene::init(D3DClass* D3D)
{
	bool result;

	// 모델들을을 생성 후, 벡터에 추가

	// TODO : 타이틀 씬에서 생성할 도형들을 벡터에 추가
	AddObject(D3D , GROUP_TYPE::DEFAULT);

	// 라이트 효과 추가
	if (m_Light == nullptr)
	{
		// Create the light object.
		m_Light = new LightClass;

		assert(m_Light);

		// Initialize the light object.
		m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light->SetDirection(1.0f, 0.0f, 0.0f);
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
		result = m_Bitmap->Initialize(D3D->GetDevice(), 800, 600, L"./data/chair_d.dds", 256, 256);
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

	//// Create the texture shader object.
	//m_TextureShader = new TextureShaderClass;

	//// Initialize the texture shader object.
	//result = m_TextureShader->Initialize(D3D->GetDevice(), SystemClass::GetInst()->GetHwnd());
	//if (!result)
	//{
	//	MessageBox(SystemClass::GetInst()->GetHwnd(), L"Could not initialize the texture shader object.", L"Error", MB_OK);
	//}

	//// Create the bitmap object.
	//m_Bitmap = new BitmapClass;

	//// Initialize the bitmap object.
	//result = m_Bitmap->Initialize(D3D->GetDevice(), 800, 600,
	//	L"./data/chair_d.dds", 256, 256);
}

void Stage01_Scene::Exit()
{

}
