#pragma once
class cCoin;
class cCoinAdmin
{
private:
	vector<cCoin*> m_Coin;
public:
	cCoinAdmin();
	~cCoinAdmin();

	void Update();
	void Render();
	void Release();

	vector<cCoin*>& GetCoin() { return m_Coin; };
};

