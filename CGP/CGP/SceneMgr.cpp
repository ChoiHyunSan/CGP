#include "SceneMgr.h"
#include "pch.h"
#include "Scene.h"
#include "Title_Scene.h"
#include "graphicsclass.h"
#include "Stage01_Scene.h"

void SceneMgr::init()
{
	// TODO : ����� ���� �� �߰��ϱ�
	m_arrScene[(UINT)SCENE_TYPE::START] = new Title_Scene;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Title Scene");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new Stage01_Scene;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01]->SetName(L"Stage01_Scene");

	// ������� ��� ���� ���ؼ� �ʱ�ȭ�� �����Ѵ�.
	for (const auto& Scene : m_arrScene)
	{
		if (Scene != nullptr)
		{
			Scene->init(GraphicsClass::GetInst()->GetD3D());
		}
	}

	// �ʱ� �� ����
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
}

void SceneMgr::update(D3DClass* D3D)
{
	m_pCurScene->update(D3D);
}

void SceneMgr::render(D3DClass* D3D, float rotation)
{
	m_pCurScene->render(D3D , rotation);
}

void SceneMgr::setCurScene(SCENE_TYPE _eType)
{
	m_pCurScene = m_arrScene[(UINT)_eType];
}

SceneMgr::SceneMgr()
	: m_arrScene{}, m_pCurScene(nullptr)
{

}

SceneMgr::~SceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::START; ++i)
	{
		if (m_arrScene[i] != nullptr)
		{
			delete m_arrScene[i];
		}
	}
}