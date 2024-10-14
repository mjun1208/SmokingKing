#include "DXUT.h"
#include "cImageManager.h"

#include "cTexture.h"
#include "cSingleTexture.h"
#include "cMultiTexture.h"

cImageManager::cImageManager()
{
}

cImageManager::~cImageManager()
{
	Release();
}

void cImageManager::Begin(bool Ui ,bool BillBoard)
{

	if (BillBoard) {
		m_sprite->SetWorldViewLH(NULL,&CAMERA->GetView());
		m_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_BILLBOARD | D3DXSPRITE_OBJECTSPACE);
	}
	else {
		if (!Ui)
			m_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
		else
			m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
}

void cImageManager::End()
{
	m_sprite->End();
}

void cImageManager::Init()
{
	D3DXCreateSprite(g_Device, &m_sprite);
}

void cImageManager::Release()
{
	SAFE_RELEASE(m_sprite);
	for (auto iter : m_image)
		SAFE_DELETE(iter.second);
	m_image.clear();
}

void cImageManager::ResetDevice()
{
	m_sprite->OnResetDevice();
}

void cImageManager::LostDevice()
{
	m_sprite->OnLostDevice();
}

cTexture * cImageManager::AddImage(const string & key, const string & path, int count)
{
	auto find = m_image.find(key);
	if (find == m_image.end()) {
		cTexture * ret;

		if (count == 0)
			ret = new cSingleTexture;
		else
			ret = new cMultiTexture;

		ret->AddImage(path, count);
		m_image.insert(make_pair(key, ret));

		return ret;
	}
	else {
		return find->second;
	}
	return nullptr;
}

cTexture * cImageManager::FindImage(const string & key, int count)
{
	auto find = m_image.find(key);
	if (find != m_image.end()) {
		return find->second->FindImage(count);
	}
	return nullptr;
}

void cImageManager::PrintText(const string & str, Vec3 pos, float size, D3DCOLOR color, bool center)
{
	D3DXMATRIX mat;
	if (!center)
	{
		D3DXCreateFontA(g_Device, size, 0, 10, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, "Fixedsys", &font);
		D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);
	}
	else {
		D3DXCreateFontA(g_Device, size, 0, 0, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, "Fixedsys", &font);
		D3DXMatrixTranslation(&mat, pos.x - size * (str.size() * 0.2), pos.y - size / 2.f, pos.z);
	}

	m_sprite->SetTransform(&mat);

	font->DrawTextA(m_sprite, str.c_str(), str.size(), nullptr, DT_NOCLIP, color);
	SAFE_RELEASE(font);
}

void cImageManager::Render(cTexture * texture, Vec3 pos, float rot, bool center)
{
	D3DXMATRIX mat;
	D3DXMATRIX matS, matR, matT;

	D3DXMatrixScaling(&matS, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(rot));
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	mat = matS * matR * matT;

	m_sprite->SetTransform(&mat);
	if (!center) {
		m_sprite->Draw(texture->texturePtr, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}
	else {
		m_sprite->Draw(texture->texturePtr, NULL, &Vec3(texture->info.Width / 2, texture->info.Height / 2, 0), NULL, D3DCOLOR_XRGB(255, 255, 255));
	}
}

void cImageManager::Render(cTexture * texture, Vec3 pos, Vec3 size, float rot, D3DCOLOR color, bool center)
{
	D3DXMATRIX mat;
	D3DXMATRIX matS, matR, matT;

	D3DXMatrixScaling(&matS, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(rot));
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	mat = matS * matR * matT;

	m_sprite->SetTransform(&mat);
	if (!center) {
		m_sprite->Draw(texture->texturePtr, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}
	else {
		m_sprite->Draw(texture->texturePtr, NULL, &Vec3(texture->info.Width / 2, texture->info.Height / 2, 0), NULL, color);
	}
}

void cImageManager::CropRender(cTexture * texture, Vec3 pos, RECT rcRange, float size)
{
	D3DXMATRIX mat;
	D3DXMATRIX matS, matR, matT;

	D3DXMatrixScaling(&matS, size, size, size);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(0));
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	mat = matS * matR * matT;

	m_sprite->SetTransform(&mat);

	m_sprite->Draw(texture->texturePtr, &rcRange, &Vec3(texture->info.Width / 2, texture->info.Height / 2, 0), NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void cImageManager::CenterRender(cTexture * texture, Vec3 pos, const Vec3 & center, float rot)
{
	D3DXMATRIX mat;
	D3DXMATRIX matS, matR, matT;

	D3DXMatrixScaling(&matS, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(rot));
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	mat = matS * matR * matT;

	m_sprite->SetTransform(&mat);

	m_sprite->Draw(texture->texturePtr, NULL, &center, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

bool cFrame::Frame()
{
	if (FrameSkip <= timeGetTime() && IsDebug) {
		if (NowFrame == EndFrame)
			NowFrame = StartFrame;
		else
			NowFrame++;

		FrameSkip = FrameDelay + timeGetTime();

		return true;
	}
	return false;
}

void cFrame::SetFrame(int start, int end, unsigned long delay)
{
	NowFrame = StartFrame = start;
	EndFrame = end;
	FrameDelay = delay;
	FrameSkip = FrameDelay + timeGetTime();
}
