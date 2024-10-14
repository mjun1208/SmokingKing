#include "DXUT.h"
#include "cBoundingSphere.h"


cBoundingSphere::cBoundingSphere()
{
}
 

cBoundingSphere::~cBoundingSphere()
{
	Release();
}

void cBoundingSphere::ComputeBoundingSphere(ObjTag tag, float radius)
{
	b_Del = false;
	b_SetActive = true;
	m_Tag = tag;
	D3DXCreateSphere(g_Device, radius, 10, 10, &SphereMesh, NULL);
	f_Size = radius;
	MyInfo = new CollInfo{ m_Tag, m_vPos , f_Size };

	b_IsColl = false;
}

void cBoundingSphere::Update()
{
	MyInfo->Pos = m_vPos;

	for (auto iter : m_Collinfo)
		SAFE_DELETE(iter);
	m_Collinfo.clear();
}

void cBoundingSphere::Render()
{
	D3DXMATRIX matW, matS, matR, matT;
	D3DXMATRIX matX, matY, matZ;

	D3DXMatrixScaling(&matS, 1.f, 1.f, 1.f);

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(0));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
	matR = matX * matY * matZ;

	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);

	matW = matS * matR * matT;

	g_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));

	mtrl.Diffuse.r = mtrl.Ambient.r = 1.f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.f;

	g_Device->SetMaterial(&mtrl);
	g_Device->SetTransform(D3DTS_WORLD, &matW);
	//WireFrame으로 출력
	SphereMesh->DrawSubset(0);
	//출력
	g_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//Solid로 변경
}

void cBoundingSphere::Release()
{
	SAFE_RELEASE(SphereMesh);
	for (auto iter : m_Collinfo)
		SAFE_DELETE(iter);
	m_Collinfo.clear();

	SAFE_DELETE(MyInfo);
}