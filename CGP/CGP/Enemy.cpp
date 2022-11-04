#include "Enemy.h"
#include "Inputclass.h"
#include "TimeMgr.h"
#include "pch.h"

void Enemy::Update()
{	
	Move();
}

// 이동하는 방향에 따라서 타겟 위치를 변경한다.
void Enemy::setTargetPos(DIR dir)
{
	isMove = true;
	switch (dir)
	{
	case DIR::UP:
		targetPos.z += 1;
		setRotate('y', 3.141592f / 1);
		break;
	case DIR::DOWN:
		targetPos.z -= 1;
		setRotate('y', 0);
		break;
	case DIR::LEFT:
		targetPos.x -= 1;
		setRotate('y', 3.141592f / 2);
		break;
	case DIR::RIGHT:
		targetPos.x += 1;
		setRotate('y', 3.141592f / 2 * 3);
		break;
	}

	 //targetPos가 맵을 벗어난다면 이동하지 않게 조정한다.
	if (targetPos.x > MAPSIZE / 2)
	{
		targetPos.x -= 1;
		isMove = false;
		Move();
	}
	if (targetPos.z > MAPSIZE) 
	{ 
		targetPos.z -= 1;
		isMove = false;
		Move();
	}
	if (targetPos.x < -MAPSIZE / 2) 
	{ 
		targetPos.x += 1;
		isMove = false;
		Move();
	}
	if (targetPos.z < 0) 
	{ 
		targetPos.z += 1; 
		isMove = false;
		Move();
	}
}

void Enemy::Move()
{
	int dir = rand() % 4;

	if (!isMove) setTargetPos((DIR)dir);

	// 목표 위치를 향해서 이동한다.
	if (getPos().x >= targetPos.x)
	{
		addPos(-fDT * speed, 0, 0);
	}
	if (getPos().x <= targetPos.x)
	{
		addPos(fDT * speed, 0, 0);
	}
	if (getPos().z >= targetPos.z)
	{
		addPos(0, 0, -fDT * speed);
	}
	if (getPos().z <= targetPos.z)
	{
		addPos(0, 0, fDT * speed);
	}

	// 목표 위치에 도달하면 이동상태를 false로 변환
	if (abs(targetPos.x - getPos().x) <= 0.05f && abs(targetPos.z - getPos().z) <= 0.05f)
	{
		isMove = false;
	}
}


Enemy::Enemy(ID3D11Device* device)
	: ModelClass(device, GROUP_TYPE::ENEMY),
	targetPos(0, 0, 0), isMove(false), speed(1.3f)
{
	setPos(0.f,1.f,1.f);
	
	SetName(L"Enemy");

	// 이동 목적지의 초기위치는 Enemy Class의 스폰 위치로 지정한다.
	targetPos = this->getPos();

	CreateCollider();
	GetCollider()->SetOffsetPos(Pos(0.f, 0.f, 0.f));
	GetCollider()->SetScale(Pos(0.8, 0.8f, 0.8f));
}

Enemy::~Enemy()
{
}
