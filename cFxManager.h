#pragma once
#include "singleton.h"
class cFxManager : public singleton<cFxManager>
{
private:
	LPD3DXEFFECT m_pEffect;
	LPD3DXEFFECT m_pBossEffect;
public:
	cFxManager();
	virtual ~cFxManager();

	LPD3DXEFFECT GetEffect() { return m_pEffect; }
	LPD3DXEFFECT GetBossEffect() { return m_pBossEffect; }
};
#define FX cFxManager::GetInstance()->GetEffect()
#define FXBoss cFxManager::GetInstance()->GetBossEffect()
