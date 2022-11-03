#include "Player.h"
#include "inputclass.h"
#include "pch.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "graphicsclass.h"
Player::Player(ID3D11Device* device)
	: ModelClass(device, GROUP_TYPE::PLAYER)
{
	setPos(0.f, 0.f, 0.f);
}

Player::~Player()
{

}


void Player::Update()
{
	if (InputClass::GetInst()->IsKeyDown(VK_LEFT))
	{
		setRotate('y', 3.141592f / 2);
		addPos(-4.0f * fDT, 0.0f, 0.0f);
	}
	else if (InputClass::GetInst()->IsKeyDown(VK_RIGHT))
	{
		addPos(4.0f * fDT, 0.0f, 0.0f);
		setRotate('y', 3.141592f / 2 * 3);
	}
	else if (InputClass::GetInst()->IsKeyDown(VK_UP))
	{
		addPos(0.0f, 0.0f, 4.0f * fDT);
		setRotate('y', 3.141592f / 1);
	}
	else if (InputClass::GetInst()->IsKeyDown(VK_DOWN))
	{
		addPos(0.0f, 0.0f, -4.0f * fDT);
		setRotate('y', 0);
	}

	if (InputClass::GetInst()->IsKeyDown(VK_SPACE))
	{
		if (SceneMgr::GetInst()->GetCurScene()->isModelArrEmpty(GROUP_TYPE::BOMB))
		{
			SceneMgr::GetInst()->GetCurScene()->AddObject(GraphicsClass::GetInst()->GetD3D(), GROUP_TYPE::BOMB);
			OutputDebugStringA("bomb");
		}
		
	}
}

