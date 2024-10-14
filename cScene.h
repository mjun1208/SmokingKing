#pragma once
class cScene abstract
{
public:
	cScene();
	virtual ~cScene();

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

