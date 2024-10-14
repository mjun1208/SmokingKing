#pragma once
class cNode
{
private:
	float size;
	Vec2 m_vPos;
	cBoundingSphere * MyBounding;
public:
	cNode(Vec2 vPos, float size);
	~cNode();

	void Init();
	void Update();
	void Render();
	void Release();

	Vec2 GetPos() { return m_vPos; }
	float GetSize() { return size; }
};

