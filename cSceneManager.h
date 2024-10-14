#pragma once
#include "singleton.h"
class cScene;
class cSceneManager : public singleton<cSceneManager>
{
private:
	cScene * m_NowScene;
	cScene * m_NextScene;
	map<string,cScene *> m_Scene;
public:
	cSceneManager();
	virtual ~cSceneManager();
	

	cScene * AddScene(const string& key, cScene * scenePtr);
	cScene * ChangeScene(const string& key);

	void Update();
	void Render();
	void Release();
};

#define SCENE cSceneManager::GetInstance()

