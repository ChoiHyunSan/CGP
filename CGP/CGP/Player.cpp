#include "Player.h"
#include "inputclass.h"
#include "pch.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "graphicsclass.h"
#include "GameMgr.h"

Player::Player(ID3D11Device* device, GROUP_TYPE type, Pos pos)
	: ModelClass(device, GROUP_TYPE::PLAYER),
	canMoveLeft(true),
	canMoveRight(true),
	canMoveUp(true),
	canMoveDown(true)
{
	setPos(pos.x,pos.y,pos.z);
	SetName(L"Player");
	GetCollider()->SetScale(Pos(0.8,0.8f,0.8f));
}

Player::~Player()
{

}


void Player::Update()
{
	if (InputClass::GetInst()->GetKeyState(DIK_LEFT) & 0x80)
	{
		if (canMoveLeft)
			addPos(-4.0f * fDT, 0.0f, 0.0f);
		setRotate('y', 3.141592f / 2);
	}
	else if (InputClass::GetInst()->GetKeyState(DIK_RIGHT) & 0x80)
	{
		setRotate('y', 3.141592f / 2 * 3);
		if (canMoveRight)
			addPos(4.0f * fDT, 0.0f, 0.0f);
	}
	else if (InputClass::GetInst()->GetKeyState(DIK_UP) & 0x80)
	{
		if (canMoveUp)
			addPos(0.0f, 0.0f, 4.0f * fDT);
		setRotate('y', 3.141592f / 1);
	}
	else if (InputClass::GetInst()->GetKeyState(DIK_DOWN) & 0x80)
	{
		if (canMoveDown)
			addPos(0.0f, 0.0f, -4.0f * fDT);
		setRotate('y', 0);
	}

	if (InputClass::GetInst()->GetKeyState(DIK_SPACE) & 0x80)
	{
		if (SceneMgr::GetInst()->GetCurScene()->isModelArrEmpty(GROUP_TYPE::BOMB))
		{
			SceneMgr::GetInst()->GetCurScene()->AddObject(GraphicsClass::GetInst()->GetD3D(), GROUP_TYPE::BOMB);
			OutputDebugStringA("bomb \n");
		}
	}
}

void Player::OnCollisionEnter(Collider* _pOther)

{
	if (_pOther->GetModel() != nullptr && _pOther->GetModel()->GetName() == L"Enemy")
	{
		int playerLife = GameMgr::GetInst()->getPlayerLife();
		if (playerLife > 1)
		{
			// �÷��̾��� ������ ������ ��� �̺�Ʈ�� ���� �ش� �κ��� ó���ϵ��� �����ϱ�
			GameMgr::GetInst()->AddLife(-1);
			setPos(0.f, 0.f, 0.f);
		}
		else
		{
			GameMgr::GetInst()->AddLife(-1);
			SetDead();

			GameMgr::GetInst()->SetGameState(GAME_STATE::GAME_OVER);
		}
	}

	if (_pOther->GetModel() != nullptr && _pOther->GetModel()->GetName() == L"Default")
	{
		//// ���� ��쿡 ��� ���⿡�� �ε��������� Ȯ���Ͽ� �ش� ���������� �̵��� ���´�.
		Pos pos = _pOther->GetModel()->getPos();
		if (pos.y != 1) return;

		// �÷��̾ ������ �����ʿ� �ִ� ���
		if (this->getPos().x > pos.x) 
		{ 
			//// �÷��̾�� ������ x,z �Ÿ� �� �� ����� ���� �پ��ִ� ���̶�� �Ǵ�.
			if (abs(this->getPos().x - pos.x) < abs(this->getPos().z - pos.z))
			{
				canMoveLeft = false;
				_pOther->GetModel()->left = true;
			}
			else
			{
				if (this->getPos().z > pos.z)
				{
					canMoveDown = false;
					_pOther->GetModel()->down = true;
				}
				else
				{
					canMoveUp = false;
					_pOther->GetModel()->up = true;
				}
			}
		}
		// �÷��̾ ������ ���ʿ� �ִ� ���
		else
		{
			if (abs(this->getPos().x - pos.x) > abs(this->getPos().z - pos.z))
			{
				canMoveRight = false;
				_pOther->GetModel()->right = true;
			}
			else
			{
				if (this->getPos().z > pos.z)
				{
					canMoveDown = false;
					_pOther->GetModel()->down = true;
				}
				else
				{
					canMoveUp = false;
					_pOther->GetModel()->up = true;
				}
			}
		}
	}
}

void Player::OnCollisionExit(Collider* _pOther)
{
	if (_pOther->GetModel() != nullptr && _pOther->GetModel()->GetName() == L"Default")
	{

		if (_pOther->GetModel()->down)
		{
			canMoveDown = true;
			_pOther->GetModel()->down = false;
		}
		if (_pOther->GetModel()->left)
		{
			canMoveLeft = true;
			_pOther->GetModel()->left = false;
		}
		if (_pOther->GetModel()->right)
		{
			canMoveRight = true;
			_pOther->GetModel()->right = false;
		}
		if (_pOther->GetModel()->up)
		{
			canMoveUp = true;
			_pOther->GetModel()->up = false;
		}
	}

}

