#include "Fire.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "EventMgr.h"
#include "GameMgr.h"
void Fire::Update()
{
	if (timer < 0.5f)
	{
		timer += fDT;
	}
	else
	{
		SceneMgr::GetInst()->GetCurScene()->ClearEffects(EFFECT_TYPE::FIRE);
		//OutputDebugStringA("FireOut");
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

void Fire::OnCollisionEnter(Collider* _pOther)
{
	if (_pOther->GetModel()->GetName() == L"Player" 
		|| _pOther->GetModel()->GetName() == L"Enemy")
	{
		OutputDebugStringA("Bomb Collision \n");

		_pOther->GetModel()->SetDead();

		if (_pOther->GetModel()->GetName() == L"Enemy")
		{
			GameMgr::GetInst()->AddScore();
		}
	}
}
