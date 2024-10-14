#pragma once
class cBoundingSphere;
class cBoundingSphereAdmin
{
private:
	vector<cBoundingSphere *> m_Bounding;
public:
	cBoundingSphereAdmin();
	~cBoundingSphereAdmin();

	void Init();
	void Update();
	void Render();
	void Release();

	vector<cBoundingSphere *>& GetBounding() { return m_Bounding; }
};

