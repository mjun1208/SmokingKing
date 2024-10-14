#include "DXUT.h"
#include "cBoss.h"

#include "cBullet.h"
#include "cPlayer.h"
cBoss::cBoss(Vec3 pos, EnemyKind Kind)
	: cEnemy(pos, Kind)
{
	switch (m_EnemyState)
	{
	case Wolf:
		m_Obj = OBJ->FindMultidOBJ("Wolf_Idle", 0);
		break;
	case Zombie:
		m_Obj = OBJ->FindMultidOBJ("Zombie_Idle", 0);
		break;
	case Zombie2:
		m_Obj = OBJ->FindMultidOBJ("Zombie2_Idle", 0);
		break;
	case Reaper:
		m_Obj = OBJ->FindMultidOBJ("Reaper_Idle", 0);
		break;
	case Vampire:
		m_Obj = OBJ->FindMultidOBJ("Vampire_Idle", 0);
		break;
	default:
		break;
	}


	Init();
}


cBoss::~cBoss()
{
	Release();
}

void cBoss::Init()
{
	f_Scale *= 2;
	f_AttackDistance *= 2;
	i_MaxHp *= 5;
	i_Hp *= 5;
	m_HPEdge = IMAGE->FindImage("BossHPEdge");
	m_HPGauge = IMAGE->FindImage("BossHPGauge");

	m_BossBounding = new cBoundingSphere;
	m_BossBounding->ComputeBoundingSphere(ENEMY, 14.f);
	g_Bounding.GetBounding().push_back(m_BossBounding);

	m_BoundingSphere->SetDel(true);
	//m_AttackBound->SetDel(true);

	SAFE_DELETE(m_AttackBound);
	m_BossAttackBounding = new cAttackBound(14.f);
	m_BossAttackBounding->SetPos(m_vPos + Vec3(0,10,0));
}

void cBoss::Update(vector<cBullet *>& Bullet)
{
	if (CurSpeakTime > RandomSpeakTime)
		SpeakSound();
	else
		CurSpeakTime += DeltaTime;

	vDir = m_vTarget - m_vPos;

	if (i_Hp <= 0) {
		i_Hp = 0;
		State = _Dead;
	}
	else {
		if (D3DXVec3Length(&vDir) < f_AttackDistance && !b_Attack) {
			State = _Attack;
			b_Attack = true;
			b_IsAttackEnd = true;
		}
		else if (D3DXVec3Length(&vDir) < f_Distance && !b_Attack) {
			State = _Walk;
			m_AttackFrame->NowFrame = 0;
		}
		else if (!b_Attack) {
			State = _Idle;
			m_AttackFrame->NowFrame = 0;
		}
	}
	StateUpdate(Bullet);
	b_CantMove = false;
	if (!m_BossBounding->GetDel() && m_BossBounding) {
		m_BossBounding->SetPos(m_vPos + Vec3(0, 10, 0));
		CheckColl();
	}
	ObjUpdate();
	m_BossAttackBounding->Update();
}

void cBoss::Render()
{
	//Hp
	IMAGE->ReBegin(true, false);
	IMAGE->Render(m_HPEdge, Vec3(800, 50, 0), Vec3(1.5f, 1.5f, 1.5f), 0, D3DCOLOR_XRGB(255, 255, 255), true);
	RECT HpRECT{ 0, 0, ((float)m_HPGauge->info.Width / i_MaxHp) * i_Hp, m_HPGauge->info.Height };
	IMAGE->CropRender(m_HPGauge, Vec3(800, 50, 0), HpRECT, 1.5f);

	switch (m_EnemyState)
	{
	case Wolf:
		IMAGE->PrintText("ºò »çÀÌÁî ´Á´ë", Vec3(800, 50, 0), 50, D3DCOLOR_XRGB(255, 255, 255), true);
		break;
	case Zombie:
		IMAGE->PrintText("ºò »çÀÌÁî Á»ºñ", Vec3(800, 50, 0), 50, D3DCOLOR_XRGB(255, 255, 255), true);
		break;
	case Zombie2:
		IMAGE->PrintText("ºò »çÀÌÁî Á»ºñ2", Vec3(800, 50, 0), 50, D3DCOLOR_XRGB(255, 255, 255), true);
		break;
	case Reaper:
		IMAGE->PrintText("ºò »çÀÌÁî ¸®ÆÛ", Vec3(800, 50, 0), 50, D3DCOLOR_XRGB(255, 255, 255), true);
		break;
	case Vampire:
		IMAGE->PrintText("ºò »çÀÌÁî ¹ìÆÄÀÌ¾î", Vec3(800, 50, 0), 50, D3DCOLOR_XRGB(255, 255, 255), true);
		break;
	default:
		break;
	}

	//Vec3 Distance = m_vTarget - m_vPos;
	//float dis = D3DXVec3Length(&Distance);
	//dis = 100 - (dis / 2.5);
	//IMAGE->PrintText(to_string(dis), Vec3(9, 200, 0), 50, D3DCOLOR_XRGB(255, 255, 255), false);
	IMAGE->ReBegin(false, false);



	D3DXMATRIX matX, matY, matZ;

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(f_Angle));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));

	D3DXMATRIX matR;
	matR = matX * matY * matZ;
	D3DXQUATERNION currQ;
	D3DXQuaternionRotationMatrix(&currQ, &matR);
	D3DXQuaternionSlerp(&prevQ, &prevQ, &currQ, 0.1f);
	D3DXMATRIX mRQ;
	D3DXMatrixRotationQuaternion(&mRQ, &prevQ);

	OBJ->Render(m_Obj, m_vPos, matR, f_Scale, true);

}

void cBoss::Release()
{
	if (m_BossBounding)
		m_BossBounding->SetDel(true);
	SAFE_DELETE(m_BossAttackBounding);
}

void cBoss::ObjUpdate()
{
	switch (State)
	{
	case _Idle:
		switch (m_EnemyState)
		{
		case Wolf:
			m_Obj = OBJ->FindMultidOBJ("Wolf_Idle", m_IdleFrame->NowFrame);
			break;
		case Zombie:
			m_Obj = OBJ->FindMultidOBJ("Zombie_Idle", m_IdleFrame->NowFrame);
			break;
		case Zombie2:
			m_Obj = OBJ->FindMultidOBJ("Zombie2_Idle", m_IdleFrame->NowFrame);
			break;
		case Reaper:
			m_Obj = OBJ->FindMultidOBJ("Reaper_Idle", m_IdleFrame->NowFrame);
			break;
		case Vampire:
			m_Obj = OBJ->FindMultidOBJ("Vampire_Idle", m_IdleFrame->NowFrame);
			break;
		default:
			break;
		}
		break;
	case _Walk:
		switch (m_EnemyState)
		{
		case Wolf:
			m_Obj = OBJ->FindMultidOBJ("Wolf_Walk", m_WalkFrame->NowFrame);
			break;
		case Zombie:
			m_Obj = OBJ->FindMultidOBJ("Zombie_Walk", m_WalkFrame->NowFrame);
			break;
		case Zombie2:
			m_Obj = OBJ->FindMultidOBJ("Zombie2_Walk", m_WalkFrame->NowFrame);
			break;
		case Reaper:
			m_Obj = OBJ->FindMultidOBJ("Reaper_Walk", m_WalkFrame->NowFrame);
			break;
		case Vampire:
			m_Obj = OBJ->FindMultidOBJ("Vampire_Walk", m_WalkFrame->NowFrame);
			break;
		default:
			break;
		}
		break;
	case _Attack:
		switch (m_EnemyState)
		{
		case Wolf:
			m_Obj = OBJ->FindMultidOBJ("Wolf_Attack", m_AttackFrame->NowFrame);
			break;
		case Zombie:
			m_Obj = OBJ->FindMultidOBJ("Zombie_Attack", m_AttackFrame->NowFrame);
			break;
		case Zombie2:
			m_Obj = OBJ->FindMultidOBJ("Zombie2_Attack", m_AttackFrame->NowFrame);
			break;
		case Reaper:
			m_Obj = OBJ->FindMultidOBJ("Reaper_Attack", m_AttackFrame->NowFrame);
			break;
		case Vampire:
			m_Obj = OBJ->FindMultidOBJ("Vampire_Attack", m_AttackFrame->NowFrame);
			break;
		default:
			break;
		}
		break;
	case _Dead:
		switch (m_EnemyState)
		{
		case Wolf:
			m_Obj = OBJ->FindMultidOBJ("Wolf_Dead", m_DeadFrame->NowFrame);
			break;
		case Zombie:
			m_Obj = OBJ->FindMultidOBJ("Zombie_Dead", m_DeadFrame->NowFrame);
			break;
		case Zombie2:
			m_Obj = OBJ->FindMultidOBJ("Zombie2_Dead", m_DeadFrame->NowFrame);
			break;
		case Reaper:
			m_Obj = OBJ->FindMultidOBJ("Reaper_Dead", m_DeadFrame->NowFrame);
			break;
		case Vampire:
			m_Obj = OBJ->FindMultidOBJ("Vampire_Dead", m_DeadFrame->NowFrame);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void cBoss::StateUpdate(vector<cBullet *>& Bullet)
{
	switch (State)
	{
	case _Idle:
		m_IdleFrame->Frame();
		break;
	case _Walk:
		m_WalkFrame->Frame();
		vDir = m_vTarget - m_vPos;
		D3DXVec3Normalize(&vDir, &vDir);
		if (!b_CantMove)
			m_vPos += vDir * f_Speed;
		f_Angle = atan2f(vDir.x, vDir.z);
		f_Angle = D3DXToDegree(f_Angle);
		break;
	case _Attack:
		m_AttackFrame->Frame();
		vDir = m_vTarget - m_vPos;
		D3DXVec3Normalize(&vDir, &vDir);
		f_Angle = atan2f(vDir.x, vDir.z);
		f_Angle = D3DXToDegree(f_Angle);

		////////////°ø°Ý
		if ((m_AttackFrame->NowFrame == m_AttackFrame->EndFrame / 2) && m_EnemyState == Reaper) {
			Bullet.push_back(new cBullet(m_vPos + Vec3(0, 10, 0), vDir, DARKBALL, 3.f, 0.8f, 2.f));
		}
		if ((m_AttackFrame->NowFrame == m_AttackFrame->EndFrame / 2) && m_EnemyState == Vampire) {
			Bullet.push_back(new cBullet(m_vPos + Vec3(0, 10, 0), vDir, BAT, 3.f, 0.8f, 2.f));
		}

		if ((m_AttackFrame->NowFrame >= m_AttackFrame->EndFrame - 60)) {
			m_BossAttackBounding->SetActive(false);
		}
		else if ((m_AttackFrame->NowFrame >= m_AttackFrame->EndFrame / 3) && m_EnemyState != Reaper && m_EnemyState != Vampire) {
			m_BossAttackBounding->SetPos(m_vPos + Vec3(0, 10, 0) + (vDir * (f_AttackDistance / 2)));
			m_BossAttackBounding->SetActive(true);
			//Bullet.push_back(new cBullet(m_vPos + Vec3(0, 10, 0) + (vDir * (f_AttackDistance / 2)), vDir, , 0.f, 7.f, 1.f));
		}

		if (m_AttackFrame->NowFrame == m_AttackFrame->EndFrame) {
			b_IsAttackEnd = false;
		}
		if (m_AttackFrame->NowFrame == m_AttackFrame->StartFrame && !b_IsAttackEnd) {
			b_Attack = false;
			State = _Idle;
			m_BossAttackBounding->SetActive(false);
		}
		break;
	case _Dead:
		if (m_BossBounding)
			m_BossBounding->SetActive(false);
		m_DeadFrame->Frame();

		if (!IsDebug)
			b_Del = true;

		if (m_DeadFrame->NowFrame == m_DeadFrame->EndFrame)
			b_IsDead = true;
		if (m_DeadFrame->NowFrame == m_DeadFrame->StartFrame && b_IsDead)
			b_Del = true;
		break;
	default:
		break;
	}
}

void cBoss::CheckColl()
{
	if (!m_BossBounding->GetDel() && m_BossBounding) {
		for (auto iter : m_BossBounding->GetCollinfo()) {
			if (iter->Tag == PLAYERBULLET) {
				g_Effect.GetEffect().push_back(new cEffect(IMAGE->FindImage("BloodEffect"), iter->Pos, 1.f, 0.05f));
				i_Hp -= 30;
			}
			else if (iter->Tag == ENEMY || iter->Tag == MAP) {
				b_CantMove = true;
				Vec3 CollDis = iter->Pos - m_vPos;
				float fCollDis = (m_BossBounding->GetSize() + iter->Size) - D3DXVec3Length(&CollDis);
				D3DXVec3Normalize(&CollDis, &CollDis);
				m_vPos -= Vec3(CollDis.x, 0, CollDis.z) * 0.2f;
			}
		}
	}

	if (m_BossAttackBounding->GetBoundingSphere() && !m_BossAttackBounding->GetBoundingSphere()->GetDel() && m_BossAttackBounding->GetBoundingSphere()->GetActive()) {
		for (auto iter : m_BossAttackBounding->GetBoundingSphere()->GetCollinfo()) {
			if (iter->Tag == PLAYER) {
				Player->Hit();
			}
		}
	}
}