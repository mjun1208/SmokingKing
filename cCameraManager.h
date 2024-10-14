#pragma once
#include "singleton.h"
class cCameraManager : public singleton<cCameraManager>
{
public:	
	D3DXMATRIX view, proj;
	Vec3 eye = { 0, 10, -20 };
private:
	Vec3 at = { 0, 0, 0 };
	Vec3 up = { 0, 1, 0 };
	float shakeFrame = 0.0f;

	bool isClip;
	float angle = 0;
	float angle_y = 0;

	bool IsSnipe;
public:
	cCameraManager();
	virtual ~cCameraManager();

	void Init();
	void Update();
	void Render();

	void SetPos(Vec3 eye_) { eye = eye_; }
	void SetTarget(Vec3 at_) { at = at_; }

	Vec3 GetPos() { return eye; }
	Vec3 GetTarget() { return at; }

	float GetAngle() { return angle; }
	void SetAngle(float _angle) { angle = _angle; }

	bool GetMouseClip() { return isClip; }
	void SetMouseClip(bool clip) { isClip = clip; }

	D3DXMATRIX GetView() { return view; }
};
#define CAMERA cCameraManager::GetInstance()
