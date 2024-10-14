#include "DXUT.h"
#include "cInputManager.h"


cInputManager::cInputManager()
{
}


cInputManager::~cInputManager()
{
	Release();
}

bool cInputManager::MouseLPress()
{
	return (NowMouse[0] == true && OldMouse[0] == true);
}

bool cInputManager::MouseLUp()
{
	return (NowMouse[0] == false && OldMouse[0] == true);
}

bool cInputManager::MouseLDown()
{
	return (NowMouse[0] == true && OldMouse[0] == false);
}

bool cInputManager::MouseRPress()
{
	return (NowMouse[1] == true && OldMouse[1] == true);
}

bool cInputManager::MouseRUp()
{
	return (NowMouse[1] == false && OldMouse[1] == true);
}

bool cInputManager::MouseRDown()
{
	return (NowMouse[1] == true && OldMouse[1] == false);
}

bool cInputManager::KeyPress(int key)
{
	return (NowInput[key] == true && OldInput[key] == true);
}

bool cInputManager::KeyUp(int key)
{
	return (NowInput[key] == false && OldInput[key] == true);
}

bool cInputManager::KeyDown(int key)
{
	return (NowInput[key] == true && OldInput[key] == false);
}

void cInputManager::Init()
{
	pSoundManager = new CSoundManager();
	pSoundManager->Initialize(DXUTGetHWND(), 2);
}

void cInputManager::Update()
{
	for (int i = 0; i < 2; i++) {
		OldMouse[i] = NowMouse[i];
	}
	for (int i = 0; i < 256; i++) {
		OldInput[i] = NowInput[i];
	}

	for (int i = 0; i < 256; i++) {
		if (GetAsyncKeyState(i)) {
			NowInput[i] = true;
		}
		else
			NowInput[i] = false;
	}

	if (GetAsyncKeyState(VK_LBUTTON)) {
		NowMouse[0] = true;
	}
	else
		NowMouse[0] = false;

	if (GetAsyncKeyState(VK_RBUTTON)) {
		NowMouse[1] = true;
	}
	else
		NowMouse[1] = false;
}

void cInputManager::Release()
{
	for (auto iter : m_VecSound) {
		SAFE_DELETE(iter.second);
	}
	m_VecSound.clear();

	SAFE_DELETE(pSoundManager);
}

void cInputManager::AddSound(const string & key, const wstring & path)
{
	CSound* pS;
	pSoundManager->Create(&pS, (LPWSTR)path.c_str(), DSBCAPS_CTRLDEFAULT | DSBCAPS_STATIC |DSBCAPS_LOCSOFTWARE);

	m_VecSound[key] = pS;
}

void cInputManager::SoundPlay(const string & key, bool loop)
{
	m_VecSound[key]->Reset();
	m_VecSound[key]->Play(0, loop);
}

void cInputManager::SoundStop(const string & key)
{
	m_VecSound[key]->Stop();
}

void cInputManager::DuplicatePlay(const string & key, LONG Voulme)
{
	LPDIRECTSOUNDBUFFER pBuf;

	pSoundManager->GetDirectSound()->DuplicateSoundBuffer(m_VecSound[key]->GetBuffer(0), &pBuf);

	pBuf->SetCurrentPosition(0);
	IDirectSoundBuffer_SetVolume(pBuf, VOLUME_TO_DB(Voulme));
	pBuf->Play(0, 0, 0);
}
