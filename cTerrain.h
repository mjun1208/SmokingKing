#pragma once
//class cTerrain
//{
//private:
//	LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
//	LPDIRECT3DINDEXBUFFER9 g_pIB = NULL;
//
//	cTexture * g_pTexHeight = NULL; // 텍스쳐 높이맵
//	cTexture * g_pTexDiffuse = NULL; // 텍스쳐 색깔맵
//
//	DWORD g_cxHeight = 0;
//	DWORD g_czHeight = 0;
//
//	struct CUSTOMVERTEX
//	{
//		D3DXVECTOR3 p;
//		D3DXVECTOR3 n;
//		D3DXVECTOR3 t;
//	};
//	struct MYINDEX
//	{
//		WORD _0, _1, _2; // 일반적으로 인덱스는 16비트의 크기를 갖는다
//	};
//public:
//	cTerrain();
//	~cTerrain();
//
//	void InitTexture(const string& HeightMap, const string& ColorMap);
//	void InitVB();
//	void InitIB();
//
//	void Render();
//	int GetHeightMapEntry(int _Row, int _Col);
//	float GetHeight(float _fX, float _fZ);
//
//	void Release();
//};
//#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

#pragma once
class cTerrain
{
public:
	cTerrain();
	~cTerrain();


	void Render();
	void Release();

	void CreateHeightMap(const string& _Path, int _NumVertsPerRow, int _NumVertsPerCol, int _CellSpacing, float _HeightScale);

	int GetHeightMapEntry(int _Row, int _Col);
	void SetHeightMapEntry(int _Row, int _Col, int _Value);

	float GetHeight(float _fX, float _fZ);

	void LoadTexture(const string& _Path);
	void genTextrue(Vec3 DirectionToLight);


private:
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DTEXTURE9   m_pTexture;

	int m_iNumVertsPerRow;
	int m_INumVertsPerCol;

	int m_iCellSpacing; // 셀 간의 간격

	int m_iNumCellsPerRow;
	int m_iNumCellsPerCol;
	int m_iWidth;
	int m_iDepth;
	int m_iNumVertices;
	int m_iNumTriangles;


	float m_fHeightScale; // 높이 배율을 조정하는 값

	vector<int> m_vecHeightmap;
	struct TerrainVertex
	{
		TerrainVertex() {}
		TerrainVertex(float x, float y, float z, float u, float v)
		{
			_x = x; _y = y; _z = z; _u = u; _v = v;
		}
		float _x, _y, _z;
		float _u, _v;

		static const DWORD FVF;
	};
public:
	void  LoadRawFile(const string& _Path);
	void  ComputeVertices();
	void  ComputeIndices();
	void  LightTerrain(Vec3 _directionToLight);
	float ComputeShade(int _CellRow, int _CellCol, Vec3 _DirectionToLight);

};

