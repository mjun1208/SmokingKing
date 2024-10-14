#pragma once
#include "cScene.h"

class cBulletAdmin;
class cEnemyAdmin;
class cEffectAdmin;
class cCoinAdmin;
class cPlayer;
class cNode;
class cIngameScene : public cScene
{
private:
	cBulletAdmin * m_Bullet;
	cEnemyAdmin * m_Enemy;
	cPlayer * m_Player;
	cCoinAdmin * m_Coin;

	vector<cNode*> m_Node;
public:
	cIngameScene();
	virtual ~cIngameScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

