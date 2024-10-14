#include "DXUT.h"
#include "OBJLoader.h"


OBJLoader::OBJLoader()
{
}


OBJLoader::~OBJLoader()
{
}

void OBJLoader::CreateMesh(LPD3DXMESH * mesh)
{
	if (FAILED(D3DXCreateMeshFVF(Index.size() / 3, Vertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, g_Device, mesh)))
	{
		DEBUG_LOG("Failed D3DXCreateMeshFVF");
		return;
	}
	// Copy the vertex data
	VERTEX* pVertex = nullptr;
	if (FAILED((*mesh)->LockVertexBuffer(0, (void**)&pVertex)))
	{
		DEBUG_LOG("Failed LockVertexBuffer");
		return;
	}
	memcpy(pVertex, &Vertex[0], sizeof(VERTEX) * Vertex.size());
	(*mesh)->UnlockVertexBuffer();
	Vertex.clear();
	
	// Copy the index data
	DWORD* pIndex = nullptr;
	if (FAILED((*mesh)->LockIndexBuffer(0, (void**)&pIndex)))
	{
		DEBUG_LOG("Failed LockIndexBuffer");
		return;
	}
	memcpy(pIndex, &Index[0], sizeof(DWORD) * Index.size());
	(*mesh)->UnlockIndexBuffer();
	Index.clear();

	// Copy the attribute data
	DWORD* pAttribute = nullptr;
	if (FAILED((*mesh)->LockAttributeBuffer(0, &pAttribute)))
	{
		DEBUG_LOG("Failed LockAttributeBuffer");
		return;
	}
	memcpy(pAttribute, &Attribute[0], sizeof(DWORD) * Attribute.size());
	(*mesh)->UnlockAttributeBuffer();
	Attribute.clear();

	for (int i = 0; i < VertexCache.size(); ++i) {
		CacheEntry* pEntry = VertexCache[i];
		while (pEntry != NULL) {
			CacheEntry* pNext = pEntry->pNext;
			SAFE_DELETE(pEntry);
			pEntry = pNext;
		}
	}

	VertexCache.clear();
	Pos.clear();
	Tex.clear();
	Normal.clear();
}

void OBJLoader::MtlLoad(const string & mtlName, Mesh * mesh, const string & mapPath)
{

	ifstream mtlLoader;
	mtlLoader.open(mtlPath);

	if (mtlLoader.fail()) {
		DEBUG_LOG("Mtl 파일 로드 실패 : " << mtlName << " " << mtlPath);
		return;
	}

	Material* pMaterial = nullptr;
	D3DMATERIAL9 * d3dmtl = nullptr;

	bool findMtl = false;

	while (!mtlLoader.eof())
	{
		string tag;
		mtlLoader >> tag;
		if (!findMtl) {
			if (tag == "newmtl")
			{
				mtlLoader >> tag;
				if (tag == mtlName) {
					pMaterial = new Material;

					pMaterial->Name = mtlName;
					mesh->Material.push_back(pMaterial);

					d3dmtl = &pMaterial->material;

					findMtl = true;
				}
			}
		}
		else {

			if (tag == "Ka")
			{
				// Ambient color
				float r, g, b;
				r = g = b = 0.f;
				mtlLoader >> tag;
				r = atof(tag.c_str());

				d3dmtl->Ambient = D3DXCOLOR{ r,g,b,1.f };
			}
			if (tag == "Kd")
			{
				float r, g, b;
				r = g = b = 0.f;
				mtlLoader >> tag;
				r = atof(tag.c_str());

				d3dmtl->Diffuse = D3DXCOLOR{ r,g,b,1.f };
			}
			if (tag == "Ks")
			{
				float r, g, b;
				r = g = b = 0.f;
				mtlLoader >> tag;
				r = atof(tag.c_str());

				d3dmtl->Specular = D3DXCOLOR{ r,g,b,1.f };
			}
			if (tag == "Ke") {
				float r, g, b;
				r = g = b = 0.f;
				mtlLoader >> tag;
				r = atof(tag.c_str());

				d3dmtl->Emissive = D3DXCOLOR{ r,g,b,1.f };
			}
			if (tag == "d" || tag == "Tr")
			{
				float a;
				mtlLoader >> tag;

				if (tag == "Tr")
					a = 1.f - atof(tag.c_str());
				else
					a = atof(tag.c_str());

				pMaterial->fAlpha = a;
			}
			if (tag == "Ns")
			{
				int nShininess;
				mtlLoader >> tag;
				nShininess = atof(tag.c_str());
				pMaterial->fNs = nShininess;
			}
			if (tag == "illum")
			{
				// Specular on/off
				float illumination;
				mtlLoader >> tag;
				illumination = atof(tag.c_str());

				pMaterial->fIllim = 1;
			}
			if (tag == "map_Kd")
			{
				mtlLoader >> tag;
				string ImagePath;

				if (mapPath == "None") {
					int PathIndex = OBJPath.rfind("/");
					ImagePath = OBJPath.substr(0, PathIndex + 1) + tag;
				}
				else
					ImagePath = mapPath + tag;
				pMaterial->map = IMAGE->AddImage(ImagePath, ImagePath);
			}
			if (tag == "newmtl")
				break;
		}
	}

	mtlLoader.close();
}

DWORD OBJLoader::AddVertex(UINT hash, VERTEX * pVertex)
{
	// If this vertex doesn't already exist in the Vertices list, create a new entry.
	// Add the index of the vertex to the Indices list.
	bool bFoundInList = false;
	DWORD index = 0;

	// Since it's very slow to check every element in the vertex list, a hashtable stores
	// vertex indices according to the vertex position's index as reported by the OBJ file
	if ((UINT)VertexCache.size() > hash)
	{
		CacheEntry* pEntry = VertexCache[hash];
		while (pEntry != NULL)
		{
			VERTEX* pCacheVertex = &Vertex[pEntry->index];

			// If this vertex is identical to the vertex already in the list, simply
			// point the index buffer to the existing vertex
			if (0 == memcmp(pVertex, pCacheVertex, sizeof(VERTEX)))
			{
				bFoundInList = true;
				index = pEntry->index;
				break;
			}

			pEntry = pEntry->pNext;
		}
	}

	// Vertex was not found in the list. Create a new entry, both within the Vertices list
	// and also within the hashtable cache
	if (!bFoundInList)
	{
		// Add to the Vertices list
		index = Vertex.size();
		Vertex.push_back(*pVertex);

		// Add this to the hashtable
		CacheEntry* pNewEntry = new CacheEntry;
		if (pNewEntry == NULL)
			return (DWORD)-1;

		pNewEntry->index = index;
		pNewEntry->pNext = NULL;

		// Grow the cache if needed
		while ((UINT)VertexCache.size() <= hash)
		{
			VertexCache.push_back(NULL);
		}

		// Add to the end of the linked list
		CacheEntry* pCurEntry = VertexCache[hash];
		if (pCurEntry == NULL)
		{
			// This is the head element
			VertexCache[hash] = pNewEntry;
		}
		else
		{
			// Find the tail
			while (pCurEntry->pNext != NULL)
			{
				pCurEntry = pCurEntry->pNext;
			}

			pCurEntry->pNext = pNewEntry;
		}
	}

	return index;
}

void OBJLoader::OBJLOAD(Mesh * mesh, const string & objpath, const string & mapPath , const string & MtlPath)
{
	OBJPath = OBJPath;

	DWORD dwAttribute = 0;

	ifstream loader;

	loader.open(objpath.c_str());

	if (loader.fail()) {
		DEBUG_LOG("파일을 여는데 실패 했습니다 : " << objpath.c_str());
		return;
	}
	

	while (!loader.eof())
	{
		string tag;
		loader >> tag;

		if (tag == "v")
		{
			// Vertex Position
			Vec3 pos;
			loader >> pos.x >> pos.y >> pos.z;
			Pos.push_back(pos);
		}
		if (tag == "vt")
		{
			// Vertex TexCoord
			Vec2 tex;
			loader >> tex.x >> tex.y;
			tex.y = 1.f - tex.y;
			Tex.push_back(tex);
		}
		if (tag == "vn")
		{
			// Vertex Normal
			Vec3 normal;
			loader >> normal.x >> normal.y >> normal.z;
			Normal.push_back(normal);
		}
		if (tag == "f")
		{
			// Face
			for (UINT iFace = 0; iFace < 3; iFace++)
			{
				string str;
				loader >> str;

				UINT ipos;
				UINT iTex;
				UINT iNormal;

				sscanf(str.c_str(), "%u/%u/%u", &ipos, &iTex, &iNormal);

				VERTEX vertex;
				vertex.position = Pos[ipos - 1];
		
				vertex.texcoord = Tex[iTex - 1];
				
				vertex.normal = Normal[iNormal - 1];

				DWORD index = AddVertex(ipos, &vertex);
				Index.push_back(index);
				
			
			}
			Attribute.push_back(dwAttribute);
		}
		if (tag == "mtllib")
		{
			loader >> mtlPath;

			int pathIndex = objpath.rfind("/");
			if (MtlPath != "None")
				mtlPath = objpath.substr(0, pathIndex + 1) + MtlPath;
			else
				mtlPath = objpath.substr(0, pathIndex + 1) + mtlPath;
		}
		if (tag == "usemtl")
		{
			// Material
			loader >> tag;

			bool bFind = false;

			for (int iMaterial = 0; iMaterial < mesh->Material.size(); ++iMaterial)
			{
				if (mesh->Material[iMaterial]->Name == tag)
				{
					dwAttribute = iMaterial;
					bFind = true;
				}
			}

			if (!bFind)
			{
				dwAttribute = mesh->Material.size();
				MtlLoad(tag, mesh, mapPath);
			}
		}
	}

	return CreateMesh(&mesh->mesh);
}
