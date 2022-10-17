#include "Player.h"
#include "inputclass.h"
#include "pch.h"
#include "TimeMgr.h"

Player::Player(ID3D11Device* device, GROUP_TYPE type)
	: ModelClass(device, GROUP_TYPE::PLAYER)
{
	setPos(1.f, 0.f, 0.f);
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
}

