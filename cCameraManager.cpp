#include "DXUT.h"
#include "cCameraManager.h"


cCameraManager::cCameraManager()
{
	isClip = true;
	IsSnipe = false;
}


cCameraManager::~cCameraManager()
{
}

void cCameraManager::Init()
{


}

void cCameraManager::Update()
{
	if (shakeFrame > 0)
	{
		eye.x += RandNum(-20, 20) * 0.1f;
		eye.y += RandNum(-20, 20) * 0.1f;
		eye.z += RandNum(-20, 20) * 0.1f;
		shakeFrame -= DeltaTime;
	}

	float moveSpeed = 0.1f;
	float rotSpeed = 2.f;

	POINT vCur;
	GetCursorPos(&vCur);

	if (INPUT->MouseRPress()) {
		IsSnipe = true;
	}
	else
		IsSnipe = false;

	if (isClip && !IsSnipe)
	{
		POINT vCenter = { WINSIZEX / 2 , WINSIZEY / 2 };
		ClientToScreen(DXUTGetHWND(), &vCenter);
		SetCursorPos(vCenter.x , vCenter.y);

		Vec3 Dir = Vec3(0.f, 1.f, -5.f);
		Vec3 OriginalDir = Vec3(0.f, 1.f, -5.f);

		if (vCur.x < vCenter.x)
		{
			angle -= rotSpeed;
			if (angle < -360)
				angle += 360;
		}
		
		if (vCur.x > vCenter.x)
		{
			angle += rotSpeed;
			if (angle > 360)
				angle -= 360;
		}

		if (vCur.y < vCenter.y - 30)
		{
			angle_y -= rotSpeed;
			if (angle_y < -360)
				angle_y += 360;
		}

		if (vCur.y > vCenter.y + 30 ) 
		{
			angle_y += rotSpeed;
			if (angle_y > 360)
				angle_y -= 360;
		}

		D3DXMATRIX matRotation_x, matRotation_y , matR;
		D3DXMatrixRotationY(&matRotation_y, D3DXToRadian(angle));
		D3DXMatrixRotationX(&matRotation_x, D3DXToRadian(angle_y));
		matR = matRotation_x * matRotation_y;
		D3DXVec3TransformNormal(&Dir, &OriginalDir, &matR);

		eye = at + Dir * 6.f;
	}
	else if (isClip && IsSnipe) {
		float rotSpeed = 1.f;
		POINT vCenter = { WINSIZEX / 2 , WINSIZEY / 2 };
		ClientToScreen(DXUTGetHWND(), &vCenter);
		SetCursorPos(vCenter.x, vCenter.y);

		if (vCur.x < vCenter.x)
		{
			angle -= rotSpeed;
			if (angle < -360)
				angle += 360;
		}
		
		if (vCur.x > vCenter.x)
		{
			angle += rotSpeed;
			if (angle > 360)
				angle -= 360;
		}

		Vec3 Dir = Vec3(0.f, 0.f, 0.f);
		Vec3 OriginalDir = Vec3(0.f, 0.f, 0.f);

		D3DXMATRIX matRotation_x, matRotation_y, matR;
		D3DXMatrixRotationY(&matRotation_y, D3DXToRadian(angle));
		D3DXMatrixRotationX(&matRotation_x, D3DXToRadian(4));
		matR = matRotation_x * matRotation_y;
		D3DXVec3TransformNormal(&Dir, &OriginalDir, &matR);

		eye = at + Dir;
	}
	else {
		//DEBUG_LOG("Hi");
	}
}

void cCameraManager::Render()
{	
	D3DXMatrixLookAtLH(&view, &eye, &at, &up);
	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(60), float(WINSIZEX) / float(WINSIZEY), 1, 10000.0f);
	g_Device->SetTransform(D3DTS_VIEW, &view);
	g_Device->SetTransform(D3DTS_PROJECTION, &proj);
}
