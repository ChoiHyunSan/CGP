#include "Player.h"
#include "inputclass.h"
#include "pch.h"
#include "TimeMgr.h"

Player::Player(ID3D11Device* device, const WCHAR* modelFilename, const WCHAR* textureFilename)
	: ModelClass(device, modelFilename, textureFilename)
{


}

Player::~Player()
{

}


void Player::Update()
{
	if (InputClass::GetInst()->IsKeyDown(VK_LEFT))
	{
		addPos(-1.0f * fDT, 0.0f, 0.0f);
		setRotate('y', 3.141592f / 2);
	}
	else if (InputClass::GetInst()->IsKeyDown(VK_RIGHT))
	{
		addPos(1.0f * fDT, 0.0f, 0.0f);
		setRotate('y', 3.141592f / 2 *3);
	}
}

