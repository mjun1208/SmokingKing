#include "DXUT.h"
#include "cCoinAdmin.h"

#include "cCoin.h"

cCoinAdmin::cCoinAdmin()
{
}


cCoinAdmin::~cCoinAdmin()
{
	Release();
}

void cCoinAdmin::Update()
{
	for (auto iter : m_Coin)
		iter->Update();

	for (auto iter = m_Coin.begin(); iter != m_Coin.end();) {
		if ((*iter)->GetDel()) {
			SAFE_DELETE(*iter);
			iter = m_Coin.erase(iter);
		}
		else
			++iter;
	}
}

void cCoinAdmin::Render()
{
	for (auto iter : m_Coin)
		iter->Render();
}

void cCoinAdmin::Release()
{
	for (auto iter : m_Coin)
		SAFE_DELETE(iter);
	m_Coin.clear();
}
