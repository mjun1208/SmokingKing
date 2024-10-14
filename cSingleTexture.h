#pragma once
#include "cTexture.h"
class cSingleTexture : public cTexture
{
public:
	cSingleTexture();
	virtual ~cSingleTexture();

	virtual cTexture * AddImage(const string& path, int count = 0) override;
	virtual cTexture * FindImage(int count = -1) override;

	virtual int GetLength() override;
};

