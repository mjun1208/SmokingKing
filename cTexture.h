#pragma once
class cTexture abstract
{
public:
	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;
public:
	cTexture();
	virtual ~cTexture();

	virtual cTexture * AddImage(const string& path, int count = 0) PURE;
	virtual cTexture * FindImage(int count = -1) PURE;
	virtual int GetLength() PURE;
};

