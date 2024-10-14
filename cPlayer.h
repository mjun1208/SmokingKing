#pragma once
class cBullet;
enum WeaponKind {
	Pistol, BigGun, None
};
class cPlayer
{
private:
	vector<cBullet *>& m_Bullet;
private:
	cTexture * m_HPGauge;
	cTexture * m_HPEdge;

	const int i_MaxHp = 100;
	int i_Hp = 100;

	cFrame * m_IdleFrame;
	cFrame * m_PistolMoveFrame;
	cFrame * m_PistolShootFrame;
	cFrame * m_BigGunMoveFrame;
	cFrame * m_BigGunShootFrame;
	cFrame * m_DeadFrame;

	D3DXQUATERNION prevQ;

	float RotX;
	float RotY;
	float RotZ;

	float fSpeed;

	float OldAngle;
	float CurAngle;
	float Angle;

	float ShootAngle;
	float AimAngle;

	Vec3 vOriginDir;
	Vec3 vDir;

	Vec3 vPos;
	Vec3 vCameraPos;

	bool IsAttack;
	bool IsAiming;
	bool IsMove;
	bool IsBackMove;

	bool IsSnipe;

	bool IsFixedCamera;

	WeaponKind WeaponState;

	void Move();
	void SnipeMove();
	void ShootBullet();

	bool b_IsHit;
	float InvincibilityDelay;

	cBoundingSphere * m_BoundingSphere;

	void CheckColl();

	bool IsDead;
	bool IsSceneChange;
	float DeadDelay;
public:
	cPlayer(vector<cBullet *>& Bullet);
	~cPlayer();

	void Init();
	void Update();
	void Render();
	void Release();

	Vec3 GetPos() { return vPos; }

	void Hit() { if (!b_IsHit) { b_IsHit = true; INPUT->DuplicatePlay("Hit", 100);  i_Hp -= 5; if (i_Hp <= 0) i_Hp = 0; g_Effect.GetEffect().push_back(new cEffect(IMAGE->FindImage("BloodEffect"), m_BoundingSphere->GetPos(), 1.f, 0.05f)); } };
};

