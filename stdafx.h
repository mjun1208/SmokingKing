#pragma once
#pragma comment (lib, "dsound.lib")
#include <iostream>
#include <algorithm>
#include <map>
#include <list>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <functional>
#include "SDKsound.h"
#include <queue>
#include <future>

using namespace std;

#define g_Device DXUTGetD3D9Device()
#define DeltaTime DXUTGetElapsedTime()

//extern bool IsDebug;

#ifdef _DEBUG
#define DEBUG_LOG(log) cout << log << endl;
#define IsDebug false
#else
#define DEBUG_LOG(log)
#define IsDebug true
#endif // _DEBUG

using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;

const int WINSIZEX = 1280;
const int WINSIZEY = 720;

#include "Utility.h"

#include "cCameraManager.h"
#include "cSceneManager.h"
#include "cImageManager.h"
#include "cInputManager.h"
#include "cFxManager.h"
#include "cTexture.h"
#include "cMapManager.h"
struct Material {
	string Name;

	D3DMATERIAL9 material;
	cTexture * map = nullptr;

	float fAlpha = 1;
	float fIllim;
	float fNs;

	Material() {
		material.Power = 1;
	}
};

struct Mesh {
	LPD3DXMESH mesh;
	vector<Material *> Material;

	~Mesh() {
		for (auto iter : Material)
			SAFE_DELETE(iter);

		Material.clear();
		SAFE_RELEASE(mesh);
	}
};

struct VERTEX
{
	Vec3 position;
	Vec3 normal;
	Vec2 texcoord;

	VERTEX(Vec3 pos, Vec3 normal, Vec2 tex)
		:position(pos), normal(normal), texcoord(tex) {}

	VERTEX() {}
};

#include "cOBJManager.h"
#include "cEffectAdmin.h"
#include "cEffect.h"
#include "cBoundingSphereAdmin.h"
#include "cBoundingSphere.h"
extern cEffectAdmin g_Effect;
extern cBoundingSphereAdmin g_Bounding;
extern int CoinCount;
extern float Damage;
extern int HealCount;
