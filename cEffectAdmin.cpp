#include "DXUT.h"
#include "cEffectAdmin.h"

#include "cEffect.h"

cEffectAdmin::cEffectAdmin()
{
}


cEffectAdmin::~cEffectAdmin()
{
}

void cEffectAdmin::Init()
{
}

void cEffectAdmin::Update()
{
	for (auto iter : m_Effect)
		iter->Update();

	for (auto iter = m_Effect.begin(); iter != m_Effect.end();) {
		if ((*iter)->GetDel()) {
			SAFE_DELETE(*iter);
			iter = m_Effect.erase(iter);
		}
		else
			++iter;
	}
}

void cEffectAdmin::Render()
{
	for (auto iter : m_Effect)
		iter->Render();
}

void cEffectAdmin::Release()
{
	for (auto iter : m_Effect)
		SAFE_DELETE(iter);
	m_Effect.clear();
}
