#include "DXUT.h"
#include "cMultiTexture.h"


cMultiTexture::cMultiTexture()
{
}


cMultiTexture::~cMultiTexture()
{
	for (auto iter : m_VecTex)
		SAFE_DELETE(iter);
}

cTexture * cMultiTexture::AddImage(const string & path, int count)
{
	char sz[128] = "";
	for (int i = 0; i <= count; i++) {
		sprintf(sz, path.c_str(), i);
		cTexture * pTex = new cSingleTexture;
		pTex->AddImage(sz);
		m_VecTex.push_back(pTex);
	}
	return this;
}

cTexture * cMultiTexture::FindImage(int count)
{
	if (count != -1)
		return m_VecTex[count];
	else
		return this;
}

int cMultiTexture::GetLength()
{
	return m_VecTex.size();
}
