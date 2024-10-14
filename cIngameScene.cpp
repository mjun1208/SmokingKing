#include "DXUT.h"
#include "cIngameScene.h"

#include "cBulletAdmin.h"
#include "cEnemyAdmin.h"
#include "cCoinAdmin.h"
#include "cPlayer.h"
#include "cNode.h"
cIngameScene::cIngameScene()
{
}


cIngameScene::~cIngameScene()
{
}

void cIngameScene::Init()
{
	CoinCount = 0;
	Damage = 1;
	m_Bullet = new cBulletAdmin();
	m_Player = new cPlayer(m_Bullet->GetBullet());
	m_Coin = new cCoinAdmin();
	m_Enemy = new cEnemyAdmin(m_Player, m_Bullet->GetBullet(), m_Coin->GetCoin());


	for (int i = 0; i < 3; i++) {
		MapSet->LoadInfo(i);
		for (auto iter : MapSet->OutInfo()) {
			m_Node.push_back(new cNode(iter->GetPos(), iter->GetSize()));
		}
		MapSet->Release();
	}
	INPUT->SoundPlay("BGM", true);
}

void cIngameScene::Update()
{
	m_Bullet->Update();
	m_Enemy->Update();
	m_Player->Update();
	m_Coin->Update();
	if (INPUT->KeyDown('M'))
		SCENE->ChangeScene("MapEditer");

	for (auto iter : m_Node) {
		iter->Update();
	}

	if (INPUT->KeyDown('R')) {
		SCENE->ChangeScene("Title");
	}
}

void cIngameScene::Render()
{
	for (auto iter : m_Node) {
		iter->Render();
	}

	m_Player->Render();
	m_Enemy->Render();
	m_Bullet->Render();
	m_Coin->Render();

	D3DXMATRIX matX, matY, matZ, matR;

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(0));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));

	matR = matX * matY * matZ;
	OBJ->Render(OBJ->FindOBJ("SkyBox"), Vec3(0, 0, 0), matR, 100.f);
	OBJ->Render(OBJ->FindOBJ("Floor"), Vec3(0, 0.1f, 0), matR, 1.f);
	OBJ->Render(OBJ->FindOBJ("Map"), Vec3(0, 64, 0), matR, 0.2f);

	IMAGE->ReBegin(true, false);
	IMAGE->PrintText("ÄÚÀÎ : " + to_string(CoinCount), Vec3(0, 200, 0), 20, D3DCOLOR_XRGB(255, 255, 255), false);
	IMAGE->ReBegin(false, false);
}

void cIngameScene::Release()
{
	INPUT->SoundStop("BGM");
	for (auto iter : m_Node) {
		SAFE_DELETE(iter);
	}
	m_Node.clear();

	SAFE_DELETE(m_Player);
	SAFE_DELETE(m_Bullet);
	SAFE_DELETE(m_Enemy);
	SAFE_DELETE(m_Coin);

}
