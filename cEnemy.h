#pragma once
#include "cBoundingSphere.h"
#include "cAttackBound.h"

class cPlayer;
class cBullet;
enum EnemyKind{
	Wolf, Zombie, Zombie2 ,Reaper , Vampire
};
class cBoundingSphere;
class cAttackBound;
class cEnemy abstract
{
protected:
	Mesh * m_Obj;

	Vec3 m_vPos;
	Vec3 m_vTarget;
	bool b_Del;
	int i_Hp;
	int i_MaxHp = 100;
	float f_Scale;

	float f_BossScale;
	float f_Angle;
	D3DXQUATERNION prevQ;
	
	float f_Speed;
	float f_Distance;
	float f_AttackDistance;

	Vec3 vOriginDir;
	Vec3 vDir;

	bool b_IsDead;
	bool b_Attack;
	bool b_IsAttackEnd;

	bool b_CantMove;

	EnemyKind m_EnemyState;

	cFrame * m_IdleFrame;
	cFrame * m_WalkFrame;
	cFrame * m_AttackFrame;
	cFrame * m_DeadFrame;

	cBoundingSphere * m_BoundingSphere;
	cAttackBound * m_AttackBound;

	cTexture * m_HPGauge;
	cTexture * m_HPEdge;

	cPlayer * Player;

	void SpeakSound();

	float CurSpeakTime;
	float RandomSpeakTime;
public:
	cEnemy(Vec3 pos ,EnemyKind Kind);
	virtual ~cEnemy();
	
	virtual void Init() PURE;
	virtual void Update(vector<cBullet *>& Bullet) PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

	virtual void ObjUpdate() PURE;
	virtual void StateUpdate(vector<cBullet *>& Bullet) PURE;
 
	void SetTarget(Vec3 Target) { m_vTarget = Target; }
	void SetPlayer(cPlayer * player) { Player = player; }
	int GetHp() { return i_Hp; }
	void SetHp(int hp) { i_Hp = hp; }

	bool GetDel() { return b_Del; }

	Vec3 GetPos() { return m_vPos; }
};

