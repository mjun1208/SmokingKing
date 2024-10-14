#pragma once
class cMainGame
{
private:
	bool IsBoundingRender = true;
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render();
	void Release();

	void ResetDevice();
	void LostDevice();
};

