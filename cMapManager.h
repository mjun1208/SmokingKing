#pragma once
#include "singleton.h"

class cNode;

class cMapManager : public singleton<cMapManager>
{
private:
	vector<cNode*> mapCode;
public:
	cMapManager();
	virtual ~cMapManager();

	void AddInfo(int _x, int _y, float size);
	void SaveInfo();
	void LoadInfo(int Count);

	void Release();

	vector<cNode*>& OutInfo() { return mapCode; };
};

#define MapSet cMapManager::GetInstance()