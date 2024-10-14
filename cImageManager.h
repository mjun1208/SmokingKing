#pragma once
#include "singleton.h"
class cTexture;
class cFrame {
public:
	int NowFrame;
	int StartFrame;
	int EndFrame;

	unsigned long FrameDelay;
	unsigned long FrameSkip;

	bool Frame();
	void SetFrame(int start, int end, unsigned long delay);
	void ChangeDelay(unsigned long delay) { FrameDelay = delay; }
};

class cImageManager : public singleton<cImageManager>
{
private:
	LPD3DXSPRITE m_sprite;
	map<string, cTexture *> m_image;
	LPD3DXFONT font;
public:
	cImageManager();
	virtual ~cImageManager();

	void Begin(bool Ui, bool BillBoard);
	void End();
	void ReBegin(bool Ui , bool BillBoard) { End(); Begin(Ui, BillBoard); }

	void Init();
	void Release();

	void ResetDevice();
	void LostDevice();

public:
	cTexture * AddImage(const string& key, const string& path, int count = 0);
	cTexture * FindImage(const string& key, int count = -1);

	void PrintText(const string& str, Vec3 pos, float size, D3DCOLOR color, bool center = false);

	void Render(cTexture * texture, Vec3 pos, float rot = 0, bool center = false);
	void Render(cTexture * texture, Vec3 pos, Vec3 size, float rot = 0, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255), bool center = false);
	void CropRender(cTexture * texture, Vec3 pos, RECT rcRange , float size = 1.f);
	void CenterRender(cTexture * texture, Vec3 pos, const Vec3 & center, float rot = 0);
};

#define IMAGE cImageManager::GetInstance()

