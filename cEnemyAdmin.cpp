#include "DXUT.h"
#include "cEnemyAdmin.h"

#include "cEnemy.h"

#include "cBoss.h"
#include "cMonster.h"
#include "cPlayer.h"
#include "cCoin.h"
cEnemyAdmin::cEnemyAdmin(cPlayer * player, vector<cBullet *>& Bullet, vector<cCoin*>& Coin)
	: m_Player(player), m_Bullet(Bullet), m_Coin(Coin)
{
	Init();
}


cEnemyAdmin::~cEnemyAdmin()
{
	Release();
}

void cEnemyAdmin::Init()
{
	time = 0;
	for (int i = 0; i < 1; i++) {
		m_Enemy.push_back(new cMonster(Vec3(-409 + rand() % 4, 0, 73 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-407 + rand() % 4, 0, 278 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-406 + rand() % 4, 0, 0 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-318 + rand() % 4, 0, 336 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-287 + rand() % 4, 0, 540 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-370 + rand() % 4, 0, 560 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-304 + rand() % 4, 0, 207 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-302 + rand() % 4, 0, -152 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(218 + rand() % 4, 0, 540 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-105 + rand() % 4, 0, 507 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(214 + rand() % 4, 0, 317 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(320 + rand() % 4, 0, 194 + rand() % 4), (EnemyKind)(rand() % 5)));
	
		m_Enemy.push_back(new cMonster(Vec3(-409 + rand() % 4, 0, 73 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-407 + rand() % 4, 0, 278 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-406 + rand() % 4, 0, 0 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-318 + rand() % 4, 0, 336 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-287 + rand() % 4, 0, 540 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-370 + rand() % 4, 0, 560 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-304 + rand() % 4, 0, 207 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-302 + rand() % 4, 0, -152 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(218 + rand() % 4, 0, 540 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-105 + rand() % 4, 0, 507 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(214 + rand() % 4, 0, 317 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(320 + rand() % 4, 0, 194 - rand() % 4), (EnemyKind)(rand() % 5)));
	
		m_Enemy.push_back(new cMonster(Vec3(-409 - rand() % 4, 0, 73 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-407 - rand() % 4, 0, 278 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-406 - rand() % 4, 0, 0 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-318 - rand() % 4, 0, 336 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-287 - rand() % 4, 0, 540 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-370 - rand() % 4, 0, 560 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-304 - rand() % 4, 0, 207 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-302 - rand() % 4, 0, -152 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(218 - rand() % 4, 0, 540 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-105 - rand() % 4, 0, 507 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(214 - rand() % 4, 0, 317 + rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(320 - rand() % 4, 0, 194 + rand() % 4), (EnemyKind)(rand() % 5)));
	
		m_Enemy.push_back(new cMonster(Vec3(-409 - rand() % 4, 0, 73 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-407 - rand() % 4, 0, 278 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-406 - rand() % 4, 0, 0 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-318 - rand() % 4, 0, 336 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-287 - rand() % 4, 0, 540 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-370 - rand() % 4, 0, 560 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-304 - rand() % 4, 0, 207 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-302 - rand() % 4, 0, -152 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(218 - rand() % 4, 0, 540 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(-105 - rand() % 4, 0, 507 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(214 - rand() % 4, 0, 317 - rand() % 4), (EnemyKind)(rand() % 5)));
		m_Enemy.push_back(new cMonster(Vec3(320 - rand() % 4, 0, 194 - rand() % 4), (EnemyKind)(rand() % 5)));
	}

	m_Boss.push_back(new cBoss(Vec3(50, 0, -340), (EnemyKind)(Wolf)));
	//m_Enemy.push_back(new cMonster(Vec3(0, 0, 0), Wolf));
}

void cEnemyAdmin::Update()
{
	for (auto iter : m_Enemy) {
		iter->SetPlayer(m_Player);
		iter->SetTarget(m_Player->GetPos());
		iter->Update(m_Bullet);
	}

	for (auto iter = m_Enemy.begin(); iter != m_Enemy.end();) {
		if ((*iter)->GetDel()) {
			m_Coin.push_back(new cCoin((*iter)->GetPos()));
			SAFE_DELETE(*iter);
			iter = m_Enemy.erase(iter);
		}
		else
			++iter;
	}

	for (auto iter : m_Boss) {
		iter->SetPlayer(m_Player);
		iter->SetTarget(m_Player->GetPos());
		iter->Update(m_Bullet);
	}

	for (auto iter = m_Boss.begin(); iter != m_Boss.end();) {
		if ((*iter)->GetDel()) {
			SAFE_DELETE(*iter);
			iter = m_Boss.erase(iter);
		}
		else
			++iter;
	}

	if (m_Boss.size() == 0) {
		switch (Count)
		{
		case 0:
		m_Boss.push_back(new cBoss(Vec3(50, 0, -340), Zombie));
			break;
		case 1:
		m_Boss.push_back(new cBoss(Vec3(50, 0, -340), Zombie2));
			break;
		case 2:
		m_Boss.push_back(new cBoss(Vec3(50, 0, -340), Reaper));
			break;
		case 3:
		m_Boss.push_back(new cBoss(Vec3(50, 0, -340), Vampire));
			break;
		case 4:
			break;
		default:
			time += DeltaTime;
			if (time > 2.f) {
				SCENE->ChangeScene("Clear");
			}
			break;
		}
		Count++;
	}
}

void cEnemyAdmin::Render()
{
	for (auto iter : m_Enemy)
		iter->Render();
	for (auto iter : m_Boss)
		iter->Render();
	IMAGE->ReBegin(true, false);
	IMAGE->PrintText("³²Àº Àû : " + to_string(m_Enemy.size()), Vec3(0, 100, 0), 20, D3DCOLOR_XRGB(255, 255, 255), false);
	IMAGE->ReBegin(false, false);

}

void cEnemyAdmin::Release()
{
	for (auto iter : m_Enemy)
		SAFE_DELETE(iter);
	m_Enemy.clear();

	for (auto iter : m_Boss)
		SAFE_DELETE(iter);
	m_Boss.clear();
}
