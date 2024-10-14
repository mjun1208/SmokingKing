#pragma once
class cEnemy;
class cPlayer;
class cBullet;
class cCoin;
class cEnemyAdmin
{
private:
	vector<cBullet *>& m_Bullet;
	vector<cEnemy *> m_Enemy;
	vector<cEnemy *> m_Boss;
	vector<cCoin*>& m_Coin;

	cPlayer * m_Player;

	int Count = 0;

	float time;
public:
	cEnemyAdmin(cPlayer * player, vector<cBullet *>& Bullet, vector<cCoin*>& Coin);
	~cEnemyAdmin();

	void Init();
	void Update();
	void Render();
	void Release();

	vector<cEnemy *>& GetEnemy() { return m_Enemy; }
};

