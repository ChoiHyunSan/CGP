#include "Bomb.h"
#include "inputclass.h"
#include "pch.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "GameMgr.h"
#include "graphicsclass.h"

Bomb::Bomb(ID3D11Device* device)
	: ModelClass(device, GROUP_TYPE::BOMB),
	timer(0.0f)
{

}

Bomb::~Bomb()
{

}

void Bomb::Update()
{
	if (timer < 3.0f)
	{
		timer += fDT;
	}
	else
	{
		// ������� ���ÿ� ���� ��ġ ���� ���μ��η� ���� PlayerPower��ŭ Fire Effect����
		int power = GameMgr::GetInst()->getPlayerPower();

		// ��ź ��ġ ����
		SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos());

		for (int i = 0; i < power; ++i)
		{
			// TODO : ��ź�� �����ϸ鼭 ���� ��ġ�� �浹������ ����ų ������Ʈ�� ���� �����Ѵ�.

			// ��ź �¿� ����
			SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos() + Pos((i + 1), 0, 0));
			SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos() + Pos(-(i + 1), 0, 0));

			// ��ź ���� ����
			SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos() + Pos(0,0,  (i + 1)));
			SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos() + Pos(0, 0 , -(i + 1)));
		}
		OutputDebugStringA("Fire");

		SceneMgr::GetInst()->GetCurScene()->ClearObjects(GROUP_TYPE::BOMB);
	}
}
