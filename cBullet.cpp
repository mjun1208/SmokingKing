#include "DXUT.h"
#include "cBullet.h"


cBullet::cBullet(Vec3 pos, Vec3 Dir, ObjTag tag, float speed, float size,  float lifetime)
	: m_vPos(pos) , m_vDir(Dir), m_tag(tag), m_fSpeed(speed), m_fDelTime(lifetime) , m_fSize(size)
{
	//m_fSpeed = 33.f;
	b_Del = false;
	m_fLifeTime = 0;
	Init();

	if (m_tag == DARKBALL) {
		m_DarkBallFrame = new cFrame();
		m_DarkBallFrame->SetFrame(0, 4, 50);
	}
}


cBullet::~cBullet()
{
	Release();
}

void cBullet::Init()
{
	m_BoundingSphere = new cBoundingSphere;
	m_BoundingSphere->ComputeBoundingSphere(m_tag, m_fSize);
	g_Bounding.GetBounding().push_back(m_BoundingSphere);
	m_BoundingSphere->SetPos(m_vPos);
}

void cBullet::Update()
{
	m_fLifeTime += DeltaTime;
	m_vPos += m_vDir * m_fSpeed;

	if (m_tag == DARKBALL) {
		m_DarkBallFrame->Frame();
	}

	if (m_fLifeTime > m_fDelTime)
		b_Del = true;

	if (!b_Del && !m_BoundingSphere->GetDel() && m_BoundingSphere) {
		m_BoundingSphere->SetPos(m_vPos);
		CheckColl();
	}
}

void cBullet::Render()
{
	D3DXMATRIX matX, matY, matZ, matR;
	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, atan2f(m_vDir.x, m_vDir.z) + D3DXToRadian(180));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
	matR = matX * matY * matZ;
	switch (m_tag)
	{
	case NONE:
		break;
	case PLAYER:
		break;
	case ENEMY:
		break;
	case PLAYERBULLET:
		OBJ->Render(OBJ->FindOBJ("Player_Bullet"), m_vPos, matR, 0.05f);
		break;
	case DARKBALL:
		OBJ->Render(OBJ->FindOBJ("DarkBall"), m_vPos, matR, 0.05f);
		IMAGE->ReBegin(false, true);
		IMAGE->Render(IMAGE->FindImage("DarkBall")->FindImage(m_DarkBallFrame->NowFrame), m_vPos + Vec3(0, 4, 0) , Vec3(0.2, -0.2, 0.2), 0, D3DCOLOR_XRGB(255, 255, 255), true);
		IMAGE->ReBegin(false, false);
		break;
	case BAT:
		OBJ->Render(OBJ->FindOBJ("Bat"), m_vPos, matR, 0.05f);
	default:
		break;
	}
}

void cBullet::Release()
{
	m_BoundingSphere->SetDel(true);
	if (m_tag == DARKBALL) 
		SAFE_DELETE(m_DarkBallFrame);
}

void cBullet::CheckColl()
{
	if (!b_Del && !m_BoundingSphere->GetDel() && m_BoundingSphere) {
		for (auto iter : m_BoundingSphere->GetCollinfo()) {
			if (iter->Tag == ENEMY && m_tag == PLAYERBULLET) {
				b_Del = true;
				m_BoundingSphere->SetActive(false);
			}
		}
	}

	if (!b_Del && !m_BoundingSphere->GetDel() && m_BoundingSphere) {
		for (auto iter : m_BoundingSphere->GetCollinfo()) {
			if (iter->Tag == PLAYER && (m_tag == DARKBALL || m_tag == BAT)) {
				b_Del = true;
				m_BoundingSphere->SetActive(false);
			}
		}
	}

	if (!b_Del && !m_BoundingSphere->GetDel() && m_BoundingSphere) {
		for (auto iter : m_BoundingSphere->GetCollinfo()) {
			if (iter->Tag == MAP) {
				b_Del = true;
				m_BoundingSphere->SetActive(false);
			}
		}
	}
}