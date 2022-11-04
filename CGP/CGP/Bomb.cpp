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
		// 사라짐과 동시에 본인 위치 포함 가로세로로 각각 PlayerPower만큼 Fire Effect생성
		int power = GameMgr::GetInst()->getPlayerPower();

		// 폭탄 위치 생성
		SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos());

		for (int i = 0; i < power; ++i)
		{
			// TODO : 폭탄을 생성하면서 같은 위치에 충돌판정을 일으킬 오브젝트를 같이 생성한다.

			// 폭탄 좌우 생성
			SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos() + Pos((i + 1), 0, 0));
			SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos() + Pos(-(i + 1), 0, 0));

			// 폭탄 상하 생성
			SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos() + Pos(0,0,  (i + 1)));
			SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos() + Pos(0, 0 , -(i + 1)));
		}
		OutputDebugStringA("Fire");

		SceneMgr::GetInst()->GetCurScene()->ClearObjects(GROUP_TYPE::BOMB);
	}
}
