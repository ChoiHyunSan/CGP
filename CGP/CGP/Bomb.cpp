#include "Bomb.h"
#include "inputclass.h"
#include "pch.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

Bomb::Bomb(ID3D11Device* device, GROUP_TYPE type)
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
		SceneMgr::GetInst()->getCureScene()->ClearObjects(GROUP_TYPE::BOMB);
	}
}
