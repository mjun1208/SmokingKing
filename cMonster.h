#pragma once
#include "cEnemy.h"
class cBullet;
enum MonsterState
{Idle, Walk, Attack, Dead};
class cMonster : public cEnemy
{
private:
	MonsterState State;
	void CheckColl();
public:
	cMonster(Vec3 pos, EnemyKind Kind);
	virtual ~cMonster();

	virtual void Init() override;
	virtual void Update(vector<cBullet *>& Bullet) override;
	virtual void Render() override;
	virtual void Release() override;

	virtual void ObjUpdate() override;
	virtual void StateUpdate(vector<cBullet *>& Bullet) override;
};

