#include "DXUT.h"
#include "cEffect.h"


cEffect::cEffect(cTexture * image, Vec3 vpos , unsigned long delay, float scale)
	: m_Image(image), m_vPos(vpos) , m_fScale(scale)
{
	m_Frame = new cFrame();
	m_Frame->SetFrame(0, m_Image->GetLength() - 1, delay);
	Init();
}


cEffect::~cEffect()
{
	Release();
}

void cEffect::Init()
{
	b_IsDead = false;
	b_Del = false;
}

void cEffect::Update()
{
	m_Frame->Frame();
	if (m_Frame->NowFrame == m_Frame->EndFrame)
		b_IsDead = true;
	if (m_Frame->NowFrame == m_Frame->StartFrame && b_IsDead)
		b_Del = true;

	if (!IsDebug)
		b_Del = true;
}

void cEffect::Render()
{
	IMAGE->ReBegin(false, true);
	IMAGE->Render(m_Image->FindImage(m_Frame->NowFrame), m_vPos,Vec3(m_fScale, m_fScale, m_fScale) , 0, D3DCOLOR_XRGB(255,255,255), true);
	IMAGE->ReBegin(false, false);
}

void cEffect::Release()
{
	SAFE_DELETE(m_Frame);
}
