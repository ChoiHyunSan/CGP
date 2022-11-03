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
		// »ç¶óÁü°ú µ¿½Ã¿¡ º»ÀÎ À§Ä¡ Æ÷ÇÔ °¡·Î¼¼·Î·Î °¢°¢ PlayerPower¸¸Å­ Fire Effect»ý¼º
		int power = GameMgr::GetInst()->getPlayerPower();

		// ÆøÅº À§Ä¡ »ý¼º
		SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos());

		for (int i = 0; i < power; ++i)
		{
			// ÆøÅº ÁÂ¿ì »ý¼º
			SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos() + Pos((i + 1), 0, 0));
			SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos() + Pos(-(i + 1), 0, 0));

			// ÆøÅº »óÇÏ »ý¼º
			SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos() + Pos(0,0,  (i + 1)));
			SceneMgr::GetInst()->GetCurScene()->AddEffect(GraphicsClass::GetInst()->GetD3D(), EFFECT_TYPE::FIRE, getPos() + Pos(0, 0 , -(i + 1)));
		}
		OutputDebugStringA("Fire");

		SceneMgr::GetInst()->GetCurScene()->ClearObjects(GROUP_TYPE::BOMB);
	}
}
