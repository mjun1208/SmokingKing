#include "DXUT.h"
#include "cEnemy.h"

#include "cBoundingSphere.h"	
#include "cPlayer.h"

void cEnemy::SpeakSound()
{
	Vec3 Distance = m_vTarget - m_vPos;
	float dis = D3DXVec3Length(&Distance);
	dis = 100 - (dis / 2.5) + 20;
	if (rand() % 2 == 0)
		INPUT->DuplicatePlay("Zombie1", LONG(dis));
	else
		INPUT->DuplicatePlay("Zombie2", LONG(dis));

	CurSpeakTime = 0;
	RandomSpeakTime = rand() % 30 + 6;
}

cEnemy::cEnemy(Vec3 pos, EnemyKind Kind)
	: m_vPos(pos), m_EnemyState(Kind)
{
	prevQ = { 0,0,0,1 };
	vOriginDir = vDir = { 0, 0, 1.f };
	f_Angle = 0;

	m_HPEdge = IMAGE->FindImage("EnemyHPEdge");
	m_HPGauge = IMAGE->FindImage("EnemyHPGauge");

	m_IdleFrame = new cFrame();
	m_WalkFrame = new cFrame();
	m_AttackFrame = new cFrame();
	m_DeadFrame = new cFrame();

	switch (m_EnemyState)
	{
	case Wolf:
		m_IdleFrame->SetFrame(0, 140 , 0.5f);
		m_WalkFrame->SetFrame(0, 42, 0.5f);
		m_AttackFrame->SetFrame(0, 115, 0.5f);
		m_DeadFrame->SetFrame(0, 110, 0.5f);
		f_Scale = 0.13f;
		m_BoundingSphere = new cBoundingSphere;
		m_BoundingSphere->ComputeBoundingSphere(ENEMY ,7.f);
		g_Bounding.GetBounding().push_back(m_BoundingSphere);
		i_Hp = 100;
		f_Speed = 0.3f;
		f_Distance = 20000;
		f_AttackDistance = 15.f;
		break;
	case Zombie:
		m_IdleFrame->SetFrame(0, 120, 0.5f);
		m_WalkFrame->SetFrame(0, 24, 0.5f);
		m_AttackFrame->SetFrame(0, 139, 0.5f);
		m_DeadFrame->SetFrame(0, 89, 0.5f);
		f_Scale = 0.011f;
		m_BoundingSphere = new cBoundingSphere;
		m_BoundingSphere->ComputeBoundingSphere(ENEMY, 7.f);
		g_Bounding.GetBounding().push_back(m_BoundingSphere);
		i_Hp = 100;
		f_Speed = 0.8f;
		f_Distance = 20000;
		f_AttackDistance = 15.f;
		break;
	case Zombie2:
		m_IdleFrame->SetFrame(0, 120, 0.5f);
		m_WalkFrame->SetFrame(0, 24, 0.5f);
		m_AttackFrame->SetFrame(0, 125, 0.5f);
		m_DeadFrame->SetFrame(0, 89, 0.5f);
		f_Scale = 0.33f;
		m_BoundingSphere = new cBoundingSphere;
		m_BoundingSphere->ComputeBoundingSphere(ENEMY, 7.f);
		g_Bounding.GetBounding().push_back(m_BoundingSphere);
		i_Hp = 100;
		f_Speed = 0.6f;
		f_Distance = 20000;
		f_AttackDistance = 15.f;
		break;
	case Reaper:
		m_IdleFrame->SetFrame(0, 55, 0.5f);
		m_WalkFrame->SetFrame(0, 42, 0.5f);
		m_AttackFrame->SetFrame(0, 69, 0.5f);
		m_DeadFrame->SetFrame(0, 109, 0.5f);
		f_Scale = 0.1f;
		m_BoundingSphere = new cBoundingSphere;
		m_BoundingSphere->ComputeBoundingSphere(ENEMY, 7.f);
		g_Bounding.GetBounding().push_back(m_BoundingSphere);
		i_Hp = 100;
		f_Speed = 0.6f;
		f_Distance = 20000;
		f_AttackDistance = 100.f;
		break;
	case Vampire:
		m_IdleFrame->SetFrame(0, 120, 0.5f);
		m_WalkFrame->SetFrame(0, 31, 0.5f);
		m_AttackFrame->SetFrame(0, 69, 0.5f);
		m_DeadFrame->SetFrame(0, 78, 0.5f);
		f_Scale = 0.06f;
		m_BoundingSphere = new cBoundingSphere;
		m_BoundingSphere->ComputeBoundingSphere(ENEMY, 7.f);
		g_Bounding.GetBounding().push_back(m_BoundingSphere);
		i_Hp = 100;
		f_Speed = 0.6f;
		f_Distance = 20000;
		f_AttackDistance = 100.f;
		break;
	default:
		break;
	}

	b_Del = false;
	b_IsDead = false;
	b_CantMove = false;
	b_Attack = false;
	b_IsAttackEnd = false;

	m_AttackBound = new cAttackBound(7.f);
	m_AttackBound->SetPos(m_vPos);

	CurSpeakTime = 0;
	RandomSpeakTime = rand() % 30 + 6;
	//Init();
}


cEnemy::~cEnemy()
{
	//Release();
	if (m_IdleFrame) 
		SAFE_DELETE(m_IdleFrame);
	if (m_WalkFrame)
		SAFE_DELETE(m_WalkFrame);
	if (m_AttackFrame)
		SAFE_DELETE(m_AttackFrame);
	if (m_DeadFrame)
		SAFE_DELETE(m_DeadFrame);

	SAFE_DELETE(m_AttackBound);
}
