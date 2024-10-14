#include "DXUT.h"
#include "cEndScene.h"


cEndScene::cEndScene(bool IsClear)
	:IsClear(IsClear)
{
}


cEndScene::~cEndScene()
{
}

void cEndScene::Init()
{
	if (IsClear)
		m_Image = IMAGE->FindImage("Clear");
	else
		m_Image = IMAGE->FindImage("GameOver");
}

void cEndScene::Update()
{
	if (INPUT->MouseLDown())
		SCENE->ChangeScene("Title");
}

void cEndScene::Render()
{
	IMAGE->ReBegin(true, false);
	IMAGE->Render(m_Image, Vec3(WINSIZEX / 2, WINSIZEY / 2, 0), 0, true);
	IMAGE->ReBegin(false, false);
}

void cEndScene::Release()
{
}
