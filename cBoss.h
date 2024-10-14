#pragma once
#include "cEnemy.h"
enum BossState
{
	_Idle, _Walk, _Attack, _Dead
};
class cBoss :
	public cEnemy
{
private:
	BossState State;
	void CheckColl();

	cBoundingSphere * m_BossBounding;
	cAttackBound * m_BossAttackBounding;
public:
	cBoss(Vec3 pos, EnemyKind Kind);
	virtual ~cBoss();

	virtual void Init() override;
	virtual void Update(vector<cBullet *>& Bullet) override;
	virtual void Render() override;
	virtual void Release() override;

	virtual void ObjUpdate() override;
	virtual void StateUpdate(vector<cBullet *>& Bullet) override;
};

