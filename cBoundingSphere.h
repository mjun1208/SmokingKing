#pragma once
enum ObjTag
{NONE, PLAYER, ENEMY, PLAYERBULLET, DARKBALL ,BAT, ENEMYATTACKBOUND, MAP , COIN, HEAL};

struct CollInfo
{
	ObjTag Tag;
	Vec3 Pos;
	float Size;
};

class cBoundingSphere
{
public:
private:
    struct SPHERE {
		Vec3 vCenter;
		float fRadius;

		SPHERE(Vec3 Center, float Radius)
			:vCenter(Center), fRadius(Radius) {};
	};

	LPD3DXMESH SphereMesh;

	Vec3 m_vPos;
	ObjTag m_Tag;
	bool b_Del;
	float f_Size;
	bool b_SetActive;
	
	bool b_IsColl;

	CollInfo * MyInfo;

	vector<CollInfo *> m_Collinfo;
public:

	cBoundingSphere();
	~cBoundingSphere();

	void ComputeBoundingSphere(ObjTag tag, float radius);
	void Update();
	void Render();
	void Release();

	void SetPos(Vec3 vPos) { m_vPos = vPos; }
	Vec3 GetPos() { return m_vPos; }
	bool GetDel() { return b_Del; }
	void SetDel(bool del) { b_Del = del; }
	ObjTag GetTag() { return m_Tag; }
	float GetSize() { return f_Size; }

	vector<CollInfo *>& GetCollinfo() { return m_Collinfo; }

	bool GetActive() { return b_SetActive; }
	void SetActive(bool Coll) { b_SetActive = Coll; }

	CollInfo * GetInfo() { return MyInfo; }
};

