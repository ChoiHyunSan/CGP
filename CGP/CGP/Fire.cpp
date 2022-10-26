#include "Fire.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

void Fire::update()
{
	if (timer < 0.1f)
	{
		timer += fDT;
	}
	else
	{
		SceneMgr::GetInst()->getCureScene()->ClearEffects(EFFECT_TYPE::FIRE);
	}

}

Fire::Fire(ID3D11Device* device)
	: EffectClass(device, EFFECT_TYPE::FIRE),
	timer(0.f)
{

}

Fire::~Fire()
{

}
