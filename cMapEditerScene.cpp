#include "DXUT.h"
#include "cMapEditerScene.h"

#include "cNode.h"

cMapEditerScene::cMapEditerScene()
{
}


cMapEditerScene::~cMapEditerScene()
{
}

void cMapEditerScene::Init()
{
	m_vCameraPos = Vec2(0, 0);
	CAMERA->SetTarget(Vec3(m_vCameraPos.x, 10, m_vCameraPos.y));
	g_Bounding.Release();
	vOriginDir = vDir = { 0, 0, 1.f };
	size = 5;
	MyBounding = new cBoundingSphere;
	MyBounding->ComputeBoundingSphere(MAP, size);
	g_Bounding.GetBounding().push_back(MyBounding);
}

void cMapEditerScene::Update()
{
	if (INPUT->KeyPress('W')) {
		Angle = CAMERA->GetAngle();
		m_vCameraPos += Vec2(vDir.x, vDir.z) * 1;
	}
	else if (INPUT->KeyPress('S')) {
		Angle = CAMERA->GetAngle();
		m_vCameraPos -= Vec2(vDir.x, vDir.z) * 1;
	}
	else if (INPUT->KeyPress('A')) {
		Angle = CAMERA->GetAngle() - 90;
		m_vCameraPos += Vec2(vDir.x, vDir.z) * 1;
	}
	else if (INPUT->KeyPress('D')) {
		Angle = CAMERA->GetAngle() + 90;
		m_vCameraPos += Vec2(vDir.x, vDir.z) * 1;
	}
	
	if (INPUT->KeyPress('Q')) {
		size += 0.1f;
	}
	else if (INPUT->KeyPress('E')) {
		if(size > 0.2f)
		    size -= 0.1f;
		else {
			size = 0.1f;
		}
	}
	MyBounding->SetPos(Vec3(m_vCameraPos.x, 10, m_vCameraPos.y));
	CAMERA->SetTarget(Vec3(m_vCameraPos.x, 10, m_vCameraPos.y));

	if (INPUT->MouseLDown()) {
		m_Node.push_back(new cNode(Vec2(m_vCameraPos.x,m_vCameraPos.y), size));
	}
	if (INPUT->KeyDown('F') && m_Node.size() > 0) {
		SAFE_DELETE(m_Node[m_Node.size() - 1]);
		m_Node.erase(m_Node.end() - 1);
	}

	if (INPUT->KeyDown('L')) {
		for (auto iter : m_Node)
			MapSet->AddInfo(iter->GetPos().x , iter->GetPos().y , iter->GetSize());
		MapSet->SaveInfo();
	}

	for (auto iter : m_Node) {
		iter->Update();
	}
}

void cMapEditerScene::Render()
{
	for (auto iter : m_Node) {
		iter->Render();
	}

	// 각도 바꾸는거
	D3DXMATRIX matX, matY, matZ;

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(Angle));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));

	D3DXMATRIX matR;
	matR = matX * matY * matZ;
	// 방향 바꾸는거
    D3DXVec3TransformNormal(&vDir, &vOriginDir, &matR);

	////////////////////////////////////

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(0));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
	matR = matX * matY * matZ;

	OBJ->Render(OBJ->FindOBJ("Floor"), Vec3(0, 0.1f, 0), matR, 1.f);
	OBJ->Render(OBJ->FindOBJ("Map"), Vec3(0, 64, 0), matR, 0.2f);

	IMAGE->ReBegin(true, false);
	IMAGE->PrintText("사이즈 : " + to_string(size), Vec3(0, 100, 0), 30, D3DCOLOR_XRGB(255, 255, 255), false);
	IMAGE->ReBegin(false, false);
}

void cMapEditerScene::Release()
{
	MyBounding->SetDel(true);
	for (auto iter : m_Node) {
		SAFE_DELETE(iter);
	}
	m_Node.clear();
}