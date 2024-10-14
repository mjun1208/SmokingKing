#include "DXUT.h"
#include "cSingleTexture.h"


cSingleTexture::cSingleTexture()
{
}


cSingleTexture::~cSingleTexture()
{
	SAFE_RELEASE(texturePtr);
}

cTexture * cSingleTexture::AddImage(const string & path, int count)
{
	D3DXCreateTextureFromFileExA(g_Device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0,
		NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, NULL, &texturePtr);

	return this;
}

cTexture * cSingleTexture::FindImage(int count)
{
	return this;
}

int cSingleTexture::GetLength()
{
	return 1;
}
