#include "Title_Scene.h"
#include "modelclass.h"
#include "d3dclass.h"
#include "systemclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"

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
	m_Model = new ModelClass(D3D->GetDevice(), L"./data/cube.obj", L"./data/seafloor.dds");
	AddObject(m_Model, GROUP_TYPE::DEFAULT);

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

	if (m_Camera == nullptr)
	{
		m_Camera = new CameraClass;

		// Set the initial position of the camera.
		m_Camera->SetPosition(0.0f, 0.0f, -5.0f);	// for cube
	}
}

void Title_Scene::Exit()
{

}
