#include "Enemy.h"
#include "Inputclass.h"
#include "TimeMgr.h"

void Enemy::Update()
{	


	if (!isMove) setTargetPos();

}

// 이동하는 방향에 따라서 타겟 위치를 변경한다.
void Enemy::setTargetPos(DIR dir)
{
	if (InputClass::GetInst()->IsKeyDown(0x41))
	{

	}

	isMove = true;
	switch (dir)
	{
	case DIR::UP:
		targetPos.z += 1;
		break;
	case DIR::DOWN:
		targetPos.z -= 1;
		break;
	case DIR::LEFT:
		targetPos.x -= 1;
		break;
	case DIR::RIGHT:
		targetPos.x += 1;
		break;
	}
}

void Enemy::Move()
{

}


Enemy::Enemy(ID3D11Device* device)
	: ModelClass(device, GROUP_TYPE::ENEMY),
	targetPos(0, 0, 0), isMove(false)
{
	setPos(0.f,1.f,1.f);
	
	// 이동 목적지의 초기위치는 Enemy Class의 스폰 위치로 지정한다.
	targetPos = this->getPos();
}

Enemy::~Enemy()
{
}
