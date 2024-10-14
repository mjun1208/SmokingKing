#pragma once
struct CacheEntry {
	UINT index;
	CacheEntry* pNext;
};

class OBJLoader
{
private:
	string OBJPath;
	vector<Vec3> Pos;
	vector<Vec2> Tex;
	vector<Vec3> Normal;

	vector<VERTEX> Vertex;
	vector<DWORD> Index;
	vector<DWORD> Attribute;

	vector<CacheEntry*> VertexCache;

	string mtlPath;

	void CreateMesh(LPD3DXMESH * mesh);
	void MtlLoad(const string & mtlName, Mesh * mesh, const string & mapPath = "None");
	DWORD AddVertex(UINT hash, VERTEX* pVertex);
public:
	OBJLoader();
	~OBJLoader();

	void OBJLOAD(Mesh * mesh, const string& objpath, const string& mapPath = "None", const string & MtlPath = "None");
};

