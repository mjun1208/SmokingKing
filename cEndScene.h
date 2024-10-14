#pragma once
#include "cScene.h"
class cEndScene : public cScene
{
private:
	cTexture * m_Image;

	bool IsClear;
public:
	cEndScene(bool IsClear);
	~cEndScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

