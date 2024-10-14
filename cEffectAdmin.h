#pragma once
class cEffect;
class cEffectAdmin
{
private:
	vector<cEffect *> m_Effect;
public:
	cEffectAdmin();
	~cEffectAdmin();

	void Init();
	void Update();
	void Render();
	void Release();

	vector<cEffect *> & GetEffect() { return m_Effect; }
};

