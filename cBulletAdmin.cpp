#include "DXUT.h"
#include "cBulletAdmin.h"

#include "cBullet.h"

cBulletAdmin::cBulletAdmin()
{
}


cBulletAdmin::~cBulletAdmin()
{
	Release();
}

void cBulletAdmin::Init()
{
}

void cBulletAdmin::Update()
{
	for (auto iter : m_Bullet)
		iter->Update();

	for (auto iter = m_Bullet.begin(); iter != m_Bullet.end();) {
		if ((*iter)->GetDel()) {
			if ((*iter)->GetTag() == DARKBALL)
				g_Effect.GetEffect().push_back(new cEffect(IMAGE->FindImage("DarkBallEffect"), (*iter)->GetPos(), 1, 0.5f));
			SAFE_DELETE(*iter);
			iter = m_Bullet.erase(iter);
		}
		else
			++iter;
	}
}

void cBulletAdmin::Render()
{
	for (auto iter : m_Bullet)
		iter->Render();
}

void cBulletAdmin::Release()
{
	for (auto iter : m_Bullet)
		SAFE_DELETE(iter);

	m_Bullet.clear();
}
