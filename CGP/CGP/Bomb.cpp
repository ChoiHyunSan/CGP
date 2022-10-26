#include "Bomb.h"
#include "inputclass.h"
#include "pch.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "GameMgr.h"
Bomb::Bomb(ID3D11Device* device)
	: ModelClass(device, GROUP_TYPE::BOMB),
	timer(0.0f)
{

}

Bomb::~Bomb()
{
	// ������� ���ÿ� ���� ��ġ ���� ���μ��η� ���� PlayerPower��ŭ Fire Effect����
	int power = GameMgr::GetInst()->Get

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
