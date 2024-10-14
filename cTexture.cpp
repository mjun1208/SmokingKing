#include "DXUT.h"
#include "cTexture.h"


cTexture::cTexture()
	:texturePtr(nullptr)
{
}


cTexture::~cTexture()
{
	SAFE_RELEASE(texturePtr);
}
