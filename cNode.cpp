#include "DXUT.h"
#include "cNode.h"


cNode::cNode(Vec2 vPos, float size)
	: m_vPos(vPos), size(size)
{
	Init();
}


cNode::~cNode()
{
	Release();
}

void cNode::Init()
{
	MyBounding = new cBoundingSphere;
	MyBounding->ComputeBoundingSphere(MAP, size);
	g_Bounding.GetBounding().push_back(MyBounding);
}

void cNode::Update()
{	
	MyBounding->SetPos(Vec3(m_vPos.x, 10, m_vPos.y));
}

void cNode::Render()
{
}

void cNode::Release()
{
	MyBounding->SetDel(true);
}
