#include "Enemy.h"
#include "Inputclass.h"
#include "TimeMgr.h"

void Enemy::Update()
{	


	if (!isMove) setTargetPos();

}

// �̵��ϴ� ���⿡ ���� Ÿ�� ��ġ�� �����Ѵ�.
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
	
	// �̵� �������� �ʱ���ġ�� Enemy Class�� ���� ��ġ�� �����Ѵ�.
	targetPos = this->getPos();
}

Enemy::~Enemy()
{
}
