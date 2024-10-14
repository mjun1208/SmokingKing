#pragma once
class cAttackBound
{
private:
	Vec3 m_vPos;
	float m_fSize;
	ObjTag m_tag;
	cBoundingSphere * m_BoundingSphere;
	bool IsActive;
public:
	cAttackBound(float size);
	~cAttackBound();
	
	void Init();
	void Update();
	void Render();
	void Release();

	void SetPos(Vec3 Pos) { m_vPos = Pos; }
	Vec3 GetPos() { return m_vPos; }

	void SetActive(bool active) { IsActive  = active; }
	cBoundingSphere * GetBoundingSphere() { return m_BoundingSphere; }
};

