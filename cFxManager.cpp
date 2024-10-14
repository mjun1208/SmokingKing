#include "DXUT.h"
#include "cFxManager.h"


cFxManager::cFxManager()
{
	DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;

	LPD3DXBUFFER errBuffer;

	if (FAILED(D3DXCreateEffectFromFile(g_Device, L"./Fx/Test.fx", NULL, NULL, dwShaderFlags,
		NULL, &m_pEffect, &errBuffer)))
	{
		MessageBoxA(DXUTGetHWND(), (LPCSTR)errBuffer->GetBufferPointer(), "ERROR", MB_OK);
		SAFE_RELEASE(errBuffer);
	}

	DWORD _dwShaderFlags = D3DXFX_NOT_CLONEABLE;

	LPD3DXBUFFER _errBuffer;

	if (FAILED(D3DXCreateEffectFromFile(g_Device, L"./Fx/Boss.fx", NULL, NULL, _dwShaderFlags,
		NULL, &m_pBossEffect, &_errBuffer)))
	{
		MessageBoxA(DXUTGetHWND(), (LPCSTR)_errBuffer->GetBufferPointer(), "ERROR", MB_OK);
		SAFE_RELEASE(_errBuffer);
	}
}


cFxManager::~cFxManager()
{
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pBossEffect);
}
