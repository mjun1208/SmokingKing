#pragma once
class cCoin
{
private:
	Vec3 m_vPos;
	float Rot;
	cBoundingSphere * m_Bounding;

	bool b_Del;
	void CheckColl();

	bool IsCoin;
public:
	cCoin(Vec3 vPos);
	~cCoin();

	void Init();
	void Update();
	void Render();
	void Release();

	bool GetDel() { return b_Del; }
};

