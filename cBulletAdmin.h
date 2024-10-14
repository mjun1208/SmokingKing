#pragma once
class cBullet;
class cBulletAdmin
{
private :
	vector<cBullet*> m_Bullet;
public:
	cBulletAdmin();
	~cBulletAdmin();
	
	void Init();
	void Update();
	void Render();
	void Release();

	vector<cBullet*>& GetBullet() { return m_Bullet; }
};

