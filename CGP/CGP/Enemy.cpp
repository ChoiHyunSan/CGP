#include "Enemy.h"
#include "Inputclass.h"
#include "TimeMgr.h"
#include "pch.h"

void Enemy::Update()
{	
	Move();
}

// �̵��ϴ� ���⿡ ���� Ÿ�� ��ġ�� �����Ѵ�.
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

	 //targetPos�� ���� ����ٸ� �̵����� �ʰ� �����Ѵ�.
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

	// ��ǥ ��ġ�� ���ؼ� �̵��Ѵ�.
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

	// ��ǥ ��ġ�� �����ϸ� �̵����¸� false�� ��ȯ
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

	// �̵� �������� �ʱ���ġ�� Enemy Class�� ���� ��ġ�� �����Ѵ�.
	targetPos = this->getPos();

	CreateCollider();
	GetCollider()->SetOffsetPos(Pos(0.f, 0.f, 0.f));
	GetCollider()->SetScale(Pos(0.8, 0.8f, 0.8f));
}

Enemy::~Enemy()
{
}
