#include "DXUT.h"
#include "cTitleScene.h"


cTitleScene::cTitleScene()
{
}


cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{
	INPUT->SoundPlay("Title", true);
}

void cTitleScene::Update()
{
	if (INPUT->MouseLDown())
		SCENE->ChangeScene("Ingame");
}

void cTitleScene::Render()
{
	IMAGE->ReBegin(true,false);
	IMAGE->Render(IMAGE->FindImage("Title"), Vec3(WINSIZEX / 2, WINSIZEY / 2, 0), 0, true);
	IMAGE->ReBegin(false,false);
}

void cTitleScene::Release()
{
	INPUT->SoundStop("Title");
}
