#include "DXUT.h"
#include "cMapManager.h"

#include "cNode.h"

cMapManager::cMapManager()
{
	ifstream mapIf;
	int i = 0;
	while (true) {
		char str[128] = "";
		sprintf(str, "./MapFile/Stage1/map(%d).txt", i);
		mapIf = ifstream(str);

		if (mapIf.is_open()) {

			i++;
			mapIf.close();
		}
		else {
			break;
		}
	}
}

cMapManager::~cMapManager()
{
	Release();
}

void cMapManager::AddInfo(int _x, int _y, float size)
{
	mapCode.push_back(new cNode(Vec2(_x, _y), size));
}

void cMapManager::SaveInfo()
{
	ofstream mapOf;
	ifstream mapIf;
	int i = 0;
	//string path;
	while (true) {
		char str[128] = "";
		sprintf(str, "./Map/Map(%d).txt", i);
		mapIf = ifstream(str);
		if (mapIf.is_open()) {

			i++;
			mapIf.close();
		}
		else {
			mapOf = ofstream(str);
			break;
		}
	}
	string tempCode;
	for (auto iter : mapCode)
	{
		tempCode.append(" (");
		tempCode.append(to_string(iter->GetPos().x));
		tempCode.append(" ,");
		tempCode.append(to_string(iter->GetPos().y));
		tempCode.append(")\t");
		tempCode.append(to_string(iter->GetSize()));
		tempCode.append("/\n");
		/*
		깔쌈하게 수정 해야 됨
		*/
	}

	if (mapOf.is_open())
	{
		mapOf << tempCode;
	}
	mapOf.close();
}

void cMapManager::LoadInfo(int Count)
{
	char str[128] = "";
	sprintf(str, "./Map/Map(%d).txt", Count);
	ifstream mapIf(str);

	if (!mapIf.is_open())
	{
		DEBUG_LOG("파일이 없음");
		return;
	}

	string tempCode;

	while (mapIf)
	{
		string tempStr;
		getline(mapIf, tempStr);
		tempCode.append(tempStr);
		if (tempStr.empty())
		{
			DEBUG_LOG("empty");
			continue;
		}
		string x;

		if (tempStr.at(1) != 'E')
		{
			int i = 0;

			while (1) {
				if (tempStr.at(2 + i) == ' ') break;
				else
				{
					x += tempStr.at(2 + i);
				}
				i++;
			}

			string y;

			int j = 0;
			while (1) {
				if (tempStr.at(4 + i + j) == ')') break;
				else
				{
					y += tempStr.at(4 + i + j);
				}
				j++;
			}

			string size;

			int k = 0;
			while(1)
			{
				if (tempStr.at(i + j + 6 + k) == '/') break;
				else
				{
					size += tempStr.at(i + j + 6 + k);
				}
				k++;
			}
			AddInfo(stoi(x), stoi(y), stoi(size));
		}
	}

	//DEBUG_LOG(tempCode);
	mapIf.close();
}

void cMapManager::Release()
{
	for (auto iter : mapCode) {
		SAFE_DELETE(iter);
	}
	mapCode.clear();
}
