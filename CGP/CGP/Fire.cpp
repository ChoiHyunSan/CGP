#include "Fire.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

void Fire::Update()
{
	if (timer < 0.5f)
	{
		timer += fDT;
	}
	else
	{
		SceneMgr::GetInst()->getCureScene()->ClearEffects(EFFECT_TYPE::FIRE);
		OutputDebugStringA("FireOut");
	}
}

Fire::Fire(ID3D11Device* device, Pos pos)
	: EffectClass(device, EFFECT_TYPE::FIRE, pos),
	timer(0.f)
{

}

Fire::~Fire()
{

}
