#include "Enemy.h"

void Enemy::Update()
{
}

Enemy::Enemy(ID3D11Device* device)
	: ModelClass(device, GROUP_TYPE::ENEMY)
{
	setPos(0.f,1.f,1.f);
}

Enemy::~Enemy()
{
}
