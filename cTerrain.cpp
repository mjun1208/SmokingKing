//#include "DXUT.h"
//#include "cTerrain.h"
//
//
//cTerrain::cTerrain()
//{
//
//}
//
//
//cTerrain::~cTerrain()
//{
//	Release();
//}
//
//void cTerrain::InitTexture(const string& HeightMap, const string& ColorMap)
//{
//	g_pTexHeight = IMAGE->AddImage(HeightMap, HeightMap);
//	g_pTexDiffuse = IMAGE->AddImage(ColorMap, ColorMap);
//	//// 높이맵 텍스쳐
//	//// D3DFMT_X8R8G8B8와 D3DPOOL_MANAGED를 주기 위해 이 함수 사용
//	//D3DXCreateTextureFromFileExA(g_Device, HeightMap.c_str(), D3DX_DEFAULT,
//	//	D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT,
//	//	D3DX_DEFAULT, 0, NULL, NULL, &g_pTexHeight);
//	//
//	//// 색깔 맵
//	//D3DXCreateTextureFromFileA(g_Device, ColorMap.c_str() , &g_pTexDiffuse);
//}
//
//void cTerrain::InitVB()
//{
//	D3DLOCKED_RECT d3drc;
//	// 텍스쳐의 가로크기
//	g_cxHeight = g_pTexHeight->info.Width;
//	// 텍스쳐의 세로크기
//	g_czHeight = g_pTexHeight->info.Height;
//
//	/// 정점 버퍼 생성
//	g_Device->CreateVertexBuffer(g_cxHeight*g_czHeight * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
//		D3DPOOL_DEFAULT, &g_pVB, NULL);
//
//	// 텍스쳐 메모리 락
//	g_pTexHeight->texturePtr->LockRect(0, &d3drc, NULL, D3DLOCK_READONLY);
//	VOID* pVertices;
//	// 정점버퍼 락
//	g_pVB->Lock(0, g_cxHeight*g_czHeight * sizeof(CUSTOMVERTEX), (void**)&pVertices, 0);
//
//	CUSTOMVERTEX v;
//	CUSTOMVERTEX* pV = (CUSTOMVERTEX*)pVertices;
//
//	for (DWORD z = 0; z < g_czHeight; z++)
//	{
//		for (DWORD x = 0; x < g_cxHeight; x++)
//		{
//			v.p.x = (float)x - g_cxHeight / 2.0f; // 정점의 x좌표 (메시를 원점에 정렬)
//			v.p.z = -((float)z - g_czHeight / 2.0f); // 정점의 z좌표 (메시를 원점에 정렬), z축이 모니터 안쪽이므로 -를 곱한다.
//			v.p.y = ((float)(*((LPDWORD)d3drc.pBits + x + z *
//				(d3drc.Pitch / 4)) & 0x000000ff)) / 10.0f;
//			// DWORD이므로 pitch/4
//
//			v.n.x = v.p.x;
//			v.n.y = v.p.y;
//			v.n.z = v.p.z;
//
//			D3DXVec3Normalize(&v.n, &v.n);
//			v.t.x = (float)x / (g_cxHeight - 1);
//			v.t.y = (float)z / (g_czHeight - 1);
//			*pV++ = v;
//			//g_pLog->Log("[%f, %f, %f]", v.x, v.y, v.z);
//		}
//	}
//	g_pVB->Unlock();
//	g_pTexHeight->texturePtr->UnlockRect(0);
//}
//
//void cTerrain::InitIB()
//{
//	g_Device->CreateIndexBuffer((g_cxHeight - 1)*(g_czHeight - 1) * 2 * sizeof(MYINDEX),
//		0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL);
//
//	MYINDEX i;
//	MYINDEX* pI;
//	g_pIB->Lock(0, (g_cxHeight - 1)*(g_czHeight - 1) * 2 * sizeof(MYINDEX), (void**)&pI, 0);
//
//	for (DWORD z = 0; z < g_czHeight - 1; z++)
//	{
//		for (DWORD x = 0; x < g_cxHeight - 1; x++)
//		{
//			i._0 = (z*g_cxHeight + x);
//			i._1 = (z*g_cxHeight + x + 1);
//			i._2 = ((z + 1)*g_cxHeight + x);
//			*pI++ = i;
//			i._0 = ((z + 1)*g_cxHeight + x);
//			i._1 = (z*g_cxHeight + x + 1);
//			i._2 = ((z + 1)*g_cxHeight + x + 1);
//			*pI++ = i;
//		}
//	}
//	g_pIB->Unlock();
//}
//
//void cTerrain::Render()
//{
//	D3DXMATRIX matW,matS, matR, matT;
//	D3DXMATRIX matX, matY, matZ;
//
//	D3DXMatrixScaling(&matS, 1.f, 1.f, 1.f);
//
//	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
//	D3DXMatrixRotationY(&matY, D3DXToRadian(0));
//	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
//	matR = matX * matY * matZ;
//
//	D3DXMatrixTranslation(&matT, 0.f, 0.f, 0.f);
//
//	matW = matS * matR * matT;
//
//	// 0번 텍스쳐 스테이지에 텍스쳐 고정(색깔 맵)
//	g_Device->SetTexture(0, g_pTexDiffuse->texturePtr);
//
//	// 0번 텍스쳐 스테이지의 확대 필터
//	g_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
//
//	// 0번 텍스쳐 : 0번 텍스쳐 인덱스 사용
//	g_Device->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
//
//	g_Device->SetTransform(D3DTS_WORLD, &matW);
//	g_Device->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
//	g_Device->SetFVF(D3DFVF_CUSTOMVERTEX);
//	g_Device->SetIndices(g_pIB);
//	g_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, g_cxHeight*g_czHeight, 0, (g_cxHeight - 1)*(g_czHeight - 1) * 2);
//}
//
//void cTerrain::Release()
//{
//	SAFE_RELEASE(g_pVB);
//	SAFE_RELEASE(g_pIB);
//}
//
//
//int cTerrain::GetHeightMapEntry(int _Row, int _Col)
//{
//	return m_vecHeightmap[_Row * m_iNumVertsPerRow + _Col];
//}
//
//float cTerrain::GetHeight(float _fX, float _fZ)
//{
//	_fX = ((float)g_cxHeight / 2.f) + _fX;
//	_fZ = ((float)g_czHeight / 2.f) - _fZ;
//
//	//_fX /= (float)m_iCellSpacing; 
//	//_fZ /= (float)m_iCellSpacing;
//
//	float col = floorf(_fX);
//	float row = floorf(_fZ);
//
//	float A = GetHeightMapEntry(row, col);
//	float B = GetHeightMapEntry(row, col + 1);
//	float C = GetHeightMapEntry(row + 1, col);
//	float D = GetHeightMapEntry(row + 1, col + 1);
//
//
//	float dx = _fX - col;
//	float dz = _fZ - row;
//
//	float height = 0.f;
//	if (dz < 1.f - dx)
//	{
//		float uy = B - A;
//		float vy = C - A;
//
//		height = A + lerp(0.0f, uy, dx) + lerp(0.0f, vy, dz);
//	}
//	else
//	{
//		float uy = C - D;
//		float vy = B - D;
//
//
//
//		height = D + lerp(0.0f, uy, 1.f - dx) + lerp(0.0f, vy, 1.f - dz);
//	}
//
//	return height;
//}

#include "DXUT.h"
#include "cTerrain.h"

const DWORD cTerrain::TerrainVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;


cTerrain::cTerrain()
{
}


cTerrain::~cTerrain()
{
	Release();
}

void cTerrain::CreateHeightMap(const string& _Path, int _NumVertsPerRow, int _NumVertsPerCol, int _CellSpacing, float _HeightScale)
{
	m_iNumVertsPerRow = _NumVertsPerRow;
	m_INumVertsPerCol = _NumVertsPerCol;
	m_iCellSpacing = _CellSpacing;

	m_iNumCellsPerRow = m_iNumVertsPerRow - 1;
	m_iNumCellsPerCol = m_INumVertsPerCol - 1;

	m_iWidth = m_iNumCellsPerRow * m_iCellSpacing;
	m_iDepth = m_iNumCellsPerCol * m_iCellSpacing;

	m_iNumVertices = m_iNumVertsPerRow * m_INumVertsPerCol;
	m_iNumTriangles = m_iNumCellsPerRow * m_iNumCellsPerCol * 2;

	m_fHeightScale = _HeightScale;

	LoadRawFile(_Path);

	for (auto& iter : m_vecHeightmap)
	{
		iter *= m_fHeightScale;
	}

	ComputeVertices();

	ComputeIndices();
}

int cTerrain::GetHeightMapEntry(int _Row, int _Col)
{
	return m_vecHeightmap[_Row * m_iNumVertsPerRow + _Col];
}

void cTerrain::SetHeightMapEntry(int _Row, int _Col, int _Value)
{
	m_vecHeightmap[_Row * m_iNumVertsPerRow + _Col] = _Value;
}

float cTerrain::GetHeight(float _fX, float _fZ)
{
	_fX = ((float)m_iWidth / 2.f) + _fX;
	_fZ = ((float)m_iDepth / 2.f) - _fZ;

	_fX /= (float)m_iCellSpacing;
	_fZ /= (float)m_iCellSpacing;

	float col = floorf(_fX);
	float row = floorf(_fZ);

	float A = GetHeightMapEntry(row, col);
	float B = GetHeightMapEntry(row, col + 1);
	float C = GetHeightMapEntry(row + 1, col);
	float D = GetHeightMapEntry(row + 1, col + 1);


	float dx = _fX - col;
	float dz = _fZ - row;

	float height = 0.f;
	if (dz < 1.f - dx)
	{
		float uy = B - A;
		float vy = C - A;

		height = A + lerp(0.0f, uy, dx) + lerp(0.0f, vy, dz);
	}
	else
	{
		float uy = C - D;
		float vy = B - D;



		height = D + lerp(0.0f, uy, 1.f - dx) + lerp(0.0f, vy, 1.f - dz);
	}

	return height;
}

void cTerrain::LoadTexture(const string& _Path)
{
	D3DXCreateTextureFromFileA(
		g_Device,
		_Path.c_str(),
		&m_pTexture
	);
}

void cTerrain::genTextrue(Vec3 DirectionToLight)
{
	int texWidth = m_iNumCellsPerRow;
	int texHeight = m_iNumCellsPerCol;

	D3DXCreateTexture(
		g_Device,
		texWidth, texHeight,
		0,
		0,
		D3DFMT_X8R8G8B8,
		D3DPOOL_MANAGED,
		&m_pTexture);

	D3DSURFACE_DESC textureDesc;
	m_pTexture->GetLevelDesc(NULL, &textureDesc);

	D3DLOCKED_RECT LockRect;
	m_pTexture->LockRect(NULL, &LockRect, NULL, NULL);

	DWORD * PixelData = (DWORD*)LockRect.pBits;
	for (int i = 0; i < texHeight; i++)
	{
		for (int j = 0; j < texWidth; j++)
		{
			D3DXCOLOR c;

			float height = (float)GetHeightMapEntry(i, j) / m_fHeightScale;

			if ((height) < 42.5f)        c = BEACH_SAND;
			else if ((height) < 85.0f)    c = LIGHT_YELLOW_GREEN;
			else if ((height) < 127.5f)  c = PUREGREEN;
			else if ((height) < 170.0f)  c = DARK_YELLOW_GREEN;
			else if ((height) < 212.5f)  c = DARKBROWN;
			else                        c = WHITE;

			PixelData[i * LockRect.Pitch / 4 + j] = (D3DCOLOR)c;
		}
	}
	m_pTexture->UnlockRect(0);

	LightTerrain(DirectionToLight);

	D3DXFilterTexture(
		m_pTexture,
		NULL,
		NULL,
		D3DX_DEFAULT);
}



void cTerrain::LoadRawFile(const string& _Path)
{
	std::vector<BYTE> in(m_iNumVertices);

	std::ifstream inFile(_Path.c_str(), std::ios_base::binary);

	inFile.read(
		(char*)&in[0], // buffer
		in.size());// number of bytes to read into buffer

	inFile.close();

	// copy BYTE vector to int vector
	m_vecHeightmap.resize(m_iNumVertices);

	for (int i = 0; i < in.size(); i++)
		m_vecHeightmap[i] = in[i];
}

void cTerrain::ComputeVertices()
{
	g_Device->CreateVertexBuffer(
		m_iNumVertices * sizeof(TerrainVertex),
		D3DUSAGE_WRITEONLY,
		TerrainVertex::FVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		NULL);

	int StartX = -m_iWidth / 2;
	int StartZ = m_iDepth / 2;


	int EndX = m_iWidth / 2;
	int EndZ = -m_iDepth / 2;

	float uCoordIncrementSize = 1.0f / (float)m_iNumCellsPerRow;
	float vCoordIncrementSize = 1.0f / (float)m_iNumCellsPerCol;

	TerrainVertex * Vertex = NULL;

	m_pVertexBuffer->Lock(0, 0, (void**)&Vertex, NULL);

	int i = 0;
	for (int z = StartZ; z >= EndZ; z -= m_iCellSpacing)
	{
		int j = 0;
		for (int x = StartX; x <= EndX; x += m_iCellSpacing)
		{
			int Index = i * m_iNumVertsPerRow + j;

			Vertex[Index] = TerrainVertex(
				(float)x,
				(float)m_vecHeightmap[Index],
				(float)z,
				(float)j * uCoordIncrementSize,
				(float)i * vCoordIncrementSize);

			j++;
		}
		i++;
	}
	m_pVertexBuffer->Unlock();

}

void cTerrain::ComputeIndices()
{
	g_Device->CreateIndexBuffer(
		m_iNumTriangles * 3 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIndexBuffer,
		NULL);
	WORD * indices = NULL;
	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);

	int baseIndex = 0;

	for (int i = 0; i < m_iNumCellsPerCol; i++)
	{
		for (int j = 0; j < m_iNumCellsPerRow; j++)
		{
			indices[baseIndex] = i * m_iNumVertsPerRow + j;
			indices[baseIndex + 1] = i * m_iNumVertsPerRow + j + 1;
			indices[baseIndex + 2] = (i + 1)   * m_iNumVertsPerRow + j;

			indices[baseIndex + 3] = (i + 1)   * m_iNumVertsPerRow + j;
			indices[baseIndex + 4] = i * m_iNumVertsPerRow + j + 1;
			indices[baseIndex + 5] = (i + 1)   * m_iNumVertsPerRow + j + 1;

			baseIndex += 6;
		}
	}

	m_pIndexBuffer->Unlock();
}

void cTerrain::LightTerrain(Vec3 _directionToLight)
{
	D3DSURFACE_DESC textureDesc;
	m_pTexture->GetLevelDesc(0, &textureDesc);

	D3DLOCKED_RECT LockRect;
	m_pTexture->LockRect(
		NULL,
		&LockRect,
		NULL,
		NULL);

	DWORD * PixelData = (DWORD*)LockRect.pBits;
	for (int i = 0; i < textureDesc.Height; i++)
	{
		for (int j = 0; j < textureDesc.Width; j++)
		{
			int index = i * LockRect.Pitch / 4 + j;

			D3DXCOLOR c(PixelData[index]);

			c *= ComputeShade(i, j, _directionToLight);

			PixelData[index] = (D3DCOLOR)c;
		}
	}
	m_pTexture->UnlockRect(NULL);
}

float cTerrain::ComputeShade(int _CellRow, int _CellCol, Vec3 _DirectionToLight)
{

	// get heights of three vertices on the quad
	float heightA = GetHeightMapEntry(_CellRow, _CellCol);
	float heightB = GetHeightMapEntry(_CellRow, _CellCol + 1);
	float heightC = GetHeightMapEntry(_CellRow + 1, _CellCol);

	// build two vectors on the quad
	D3DXVECTOR3 u(m_iCellSpacing, heightB - heightA, 0.0f);
	D3DXVECTOR3 v(0.0f, heightC - heightA, -m_iCellSpacing);

	// find the normal by taking the cross product of two
	// vectors on the quad.
	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);
	D3DXVec3Normalize(&n, &n);

	float cosine = D3DXVec3Dot(&n, &_DirectionToLight);

	if (cosine < 0.0f)
		cosine = 0.0f;

	return cosine;

}

void cTerrain::Render()
{
	D3DXMATRIX matW, matS, matR, matT;
	D3DXMATRIX matX, matY, matZ;

	D3DXMatrixScaling(&matS, 1.f, 1.f, 1.f);

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(0));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
	matR = matX * matY * matZ;

	D3DXMatrixTranslation(&matT, 0.f, 0.f, 0.f);

	matW = matS * matR * matT;

	g_Device->SetTransform(D3DTS_WORLD, &matW);

	g_Device->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(TerrainVertex));
	g_Device->SetFVF(TerrainVertex::FVF);
	g_Device->SetIndices(m_pIndexBuffer);

	g_Device->SetTexture(NULL, m_pTexture);

	g_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_Device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		NULL,
		NULL,
		m_iNumVertices,
		NULL,
		m_iNumTriangles);
	g_Device->SetRenderState(D3DRS_LIGHTING, TRUE);


	//g_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//g_Device->DrawIndexedPrimitive(
	//   D3DPT_TRIANGLELIST,
	//   NULL,
	//   NULL,
	//   m_iNumVertices,
	//   NULL,
	//   m_iNumTriangles);
	//
	//g_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void cTerrain::Release()
{
	m_pVertexBuffer->Release();
	m_pTexture->Release();
	m_pIndexBuffer->Release();
}