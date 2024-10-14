#pragma once
class cEffect
{
private:
	cTexture * m_Image;
	cFrame * m_Frame;
	Vec3 m_vPos;
	bool b_IsDead;
	bool b_Del;

	float m_fScale;
public:
	cEffect(cTexture * image, Vec3 vpos, unsigned long delay, float scale);
	~cEffect();

	void Init();
	void Update();
	void Render();
	void Release();

	bool GetDel() { return b_Del; }
};

