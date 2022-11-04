#include "Collider.h"
#include "pch.h"
#include "ModelClass.h"


UINT Collider::g_iNextID = 0;

Collider::Collider()
	:m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iCol(0)
{
}

Collider::Collider(const Collider& _origin)
	:m_pOwner(nullptr),
	m_vOffsetPos(_origin.m_vOffsetPos),
	m_vScale(_origin.m_vScale),
	m_iID(g_iNextID++),
	m_iCol(0)
{

}

Collider::~Collider()
{

}

void Collider::finalUpdate()
{
	// Object�� ��ġ�� ���󰣴�.
	Pos vObjectPos = m_pOwner->getPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void Collider::render()
{

}

void Collider::OnCollision(Collider* _pOther)
{
	// �浹�� �ݶ��̴��� ������ ������Ʈ�κ��� OnCollision�Լ� ȣ��
	m_pOwner->OnCollision(_pOther);
}

void Collider::OnCollisionEnter(Collider* _pOther)
{
	++m_iCol;
	m_pOwner->OnCollisionEnter(_pOther);
}

void Collider::OnCollisionExit(Collider* _pOther)
{
	--m_iCol;
	m_pOwner->OnCollisionExit(_pOther);
}
