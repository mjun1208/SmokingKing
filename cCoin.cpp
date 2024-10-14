#include "DXUT.h"
#include "cCoin.h"


void cCoin::CheckColl()
{
	if (!b_Del && !m_Bounding->GetDel() && m_Bounding) {
		for (auto iter : m_Bounding->GetCollinfo()) {
			if (iter->Tag == PLAYER) {
				if (IsCoin) {
					CoinCount++;
					INPUT->DuplicatePlay("Coin", 100);
					g_Effect.GetEffect().push_back(new cEffect(IMAGE->FindImage("CoinEffect"), m_vPos + Vec3(0, 5, 0), 20, 0.5f));
				}
				else {
					HealCount += 10;
					INPUT->DuplicatePlay("Heal", 100);
					g_Effect.GetEffect().push_back(new cEffect(IMAGE->FindImage("HealEffect"), m_vPos + Vec3(0, 5, 0), 20, 0.5f));
				}
				m_Bounding->SetActive(false);
				b_Del = true;
			}
		}
	}
}

cCoin::cCoin(Vec3 vPos)
	: m_vPos(vPos)
{
	if (rand() % 5 == 0) {
		IsCoin = false;
	}
	else
		IsCoin = true;

	Init();
}

cCoin::~cCoin()
{
	Release();
}

void cCoin::Init()
{
	m_Bounding = new cBoundingSphere;
	if (IsCoin)
	    m_Bounding->ComputeBoundingSphere(COIN, 5.f);
	else
		m_Bounding->ComputeBoundingSphere(HEAL, 5.f);
	g_Bounding.GetBounding().push_back(m_Bounding);
	Rot = 0;
	b_Del = false;
}

void cCoin::Update()
{
	m_Bounding->SetPos(m_vPos + Vec3(0, 10, 0));
	if (Rot > 360)
		Rot -= 360;
	Rot+= 4;

	CheckColl();
}

void cCoin::Render()
{
	D3DXMATRIX matX, matY, matZ;

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(Rot));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));

	D3DXMATRIX matR;
	matR = matX * matY * matZ;
	
	if (IsCoin)
	    OBJ->Render(OBJ->FindOBJ("Coin"),m_vPos + Vec3(0, 10, 0), matR ,0.1f);
	else
		OBJ->Render(OBJ->FindOBJ("Heal"), m_vPos + Vec3(0, 10, 0), matR, 0.1f);
}

void cCoin::Release()
{
	if (m_Bounding)
		m_Bounding->SetDel(true);
}
