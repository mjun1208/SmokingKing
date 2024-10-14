#include "DXUT.h"
#include "cAttackBound.h"


cAttackBound::cAttackBound(float size)
	: m_fSize(size)
{
	Init();
}


cAttackBound::~cAttackBound()
{
	Release();
}

void cAttackBound::Init()
{
	m_tag = ENEMYATTACKBOUND;
	m_BoundingSphere = new cBoundingSphere;
	m_BoundingSphere->ComputeBoundingSphere(m_tag, m_fSize);
	g_Bounding.GetBounding().push_back(m_BoundingSphere);
	m_BoundingSphere->SetPos(m_vPos);
	IsActive = false;
	m_BoundingSphere->SetActive(IsActive);
}

void cAttackBound::Update()
{
	m_BoundingSphere->SetActive(IsActive);
	m_BoundingSphere->SetPos(m_vPos);
}

void cAttackBound::Render()
{
}

void cAttackBound::Release()
{
	m_BoundingSphere->SetDel(true);
}
