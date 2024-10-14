#pragma once
#include "singleton.h"
class cInputManager : public singleton<cInputManager>
{
private:
	bool NowMouse[2];
	bool OldMouse[2];

	bool NowInput[256];
	bool OldInput[256];
public:
	cInputManager();
	virtual ~cInputManager();

	bool MouseLPress();
	bool MouseLUp();
	bool MouseLDown();

	bool MouseRPress();
	bool MouseRUp();
	bool MouseRDown();

	bool KeyPress(int key);
	bool KeyUp(int key);
	bool KeyDown(int key);

	void Init();
	void Update();
	void Release();

	Vec2 GetMousePos() {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(DXUTGetHWND(), &pt);

		return Vec2((float)pt.x, (float)pt.y);
	}

	Vec2 GetScreenPos() {
		Vec2 MousePos = GetMousePos();
		Vec2 ScreenPos = MousePos + Vec2(CAMERA->GetPos().x , CAMERA->GetPos().z);
		return Vec2((float)ScreenPos.x, (float)ScreenPos.y);
	}

	CSoundManager* pSoundManager = nullptr;
	map<string, CSound*> m_VecSound;

	void AddSound(const string& key, const wstring& path);
	void SoundPlay(const string& key, bool loop = false);
	void SoundStop(const string& key);
	void DuplicatePlay(const string& key, LONG Voulme = 0); // บาทý 0 ~ 100;
};

#define INPUT cInputManager::GetInstance()
#define DSBCAPS_CTRLDEFAULT  (DSBCAPS_CTRLFREQUENCY |DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME)
#define VOLUME_TO_DB(volume)   ((DWORD)(-30*(100-volume))) 