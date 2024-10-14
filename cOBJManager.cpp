#include "DXUT.h"
#include "cOBJManager.h"

cOBJManager::cOBJManager()
{
}


cOBJManager::~cOBJManager()
{
	Release();
}

Mesh * cOBJManager::AddOBJ(const string& key, const string& path, const string& mappath, const string& MtlPath)
{
	auto find = m_Mesh.find(key);
	if (find == m_Mesh.end()) {
		Mesh * temp = new Mesh;
		loader.OBJLOAD(temp, path, mappath , MtlPath);

		m_Mesh.insert(make_pair(key, temp));
		return temp;
	}
	else {
		return find->second;
	}
}

vector<Mesh*> cOBJManager::AddMultiOBJ(const string & key, const string & path, const string& mappath, int count, const string& MtlPath)
{
	vector<Mesh *> * m_VecOBJ = new vector<Mesh *>;

	char sz[128] = "";
	for (int i = 0; i <= count; i++) {
		sprintf(sz, path.c_str(), i);
		Mesh * temp = new Mesh;
		loader.OBJLOAD(temp, sz, mappath, MtlPath);
		DEBUG_LOG(sz);
		(*m_VecOBJ).push_back(temp);
	}
	m_MultiMesh.insert(make_pair(key, m_VecOBJ));
	return (*m_VecOBJ);
}

Mesh * cOBJManager::FindOBJ(const string& key)
{
	auto find = m_Mesh.find(key);
	if (find != m_Mesh.end()) {
		return find->second;
	}
	return nullptr;
}

Mesh * cOBJManager::FindMultidOBJ(const string & key, int count)
{
	auto find = m_MultiMesh.find(key);
	if (find != m_MultiMesh.end()) {
		return (*find->second)[count];
	}
	return nullptr;
}

void cOBJManager::Render(Mesh * mesh, Vec3 Pos, D3DXMATRIX matR, float scale, bool b_Boss)
{
	D3DXMATRIX matW, matS, matT;
	D3DXMatrixScaling(&matS, scale, scale, scale);
	D3DXMatrixTranslation(&matT, Pos.x, Pos.y, Pos.z);

	matW = matS * matR * matT;

	if (b_Boss) {
		HRESULT hr;

		//float4x4 matWorldView;
		//float4x4 matWorldViewIT;
		//float4x4 matProjection;
		//float3 LightDir;
		//float4 diffuseColor;
		//float4 ambientColor;
		//float4 GlowColor;
		//float4 GlowAmbient;
		//float GlowThickness;
		//texture base;

		if (mesh->Material[0]->map)
			FXBoss->SetTexture((D3DXHANDLE)"base", mesh->Material[0]->map->texturePtr);
		else
			FXBoss->SetTexture((D3DXHANDLE)"base", nullptr);

		FXBoss->SetTexture((D3DXHANDLE)"UVAnime", mesh->Material[0]->map->texturePtr);

		FXBoss->SetMatrix((D3DXHANDLE)"matWorldView", &(matW * CAMERA->view));
		D3DXMATRIX InverseTranspose = matW * CAMERA->view;
		D3DXMatrixInverse(&InverseTranspose, NULL, &InverseTranspose);
		D3DXMatrixTranspose(&InverseTranspose, &InverseTranspose);
		FXBoss->SetMatrix((D3DXHANDLE)"matWorldViewIT", &InverseTranspose);
		FXBoss->SetMatrix((D3DXHANDLE)"matProjection", &CAMERA->proj);
		FXBoss->SetVector((D3DXHANDLE)"LightDir", &D3DXVECTOR4(CAMERA->eye.x, CAMERA->eye.y, CAMERA->eye.z , 1.f));
		FXBoss->SetVector((D3DXHANDLE)"diffuseColor", &D3DXVECTOR4(1.f, 1.f, 1.f, 1.f));
		FXBoss->SetVector((D3DXHANDLE)"ambientColor", &D3DXVECTOR4(1.f, 1.f, 1.f, 1.f));

		//float4 gWorldLightPosition;
		//float4 gWorldCameraPosition;

		FXBoss->SetVector((D3DXHANDLE)"GlowColor", &D3DXVECTOR4(0.7f, 0.1f, 0.1f, 0.6f));
		FXBoss->SetVector((D3DXHANDLE)"GlowAmbient", &D3DXVECTOR4(1.f, 0.1f, 0.1f, 1.f));
		FXBoss->SetFloat((D3DXHANDLE)"GlowThickness", 0.2f);

		FXBoss->SetTechnique((D3DXHANDLE)"Boss");

		UINT cPass;
		FXBoss->Begin(&cPass, 0); //Pass∞° ∏Ó∞≥¿Œ¡ˆ πﬁæ∆ø»

		for (UINT p = 0; p < cPass; ++p)
		{
			FXBoss->BeginPass(p);

			g_Device->SetTransform(D3DTS_WORLD, &matW); //fx«“∂© æ»«ÿµµµ 
			for (int i = 0; i < mesh->Material.size(); ++i)
			{
				if (mesh->Material[i]->map) {
					g_Device->SetTexture(0, mesh->Material[i]->map->texturePtr);
				}
				else
					g_Device->SetTexture(0, nullptr);

				g_Device->SetMaterial(&mesh->Material[i]->material);

				mesh->mesh->DrawSubset(i);
			}

			FXBoss->EndPass();

		}
		FXBoss->End();
	}
	else {



		HRESULT hr;
		if (mesh->Material[0]->map)
			FX->SetTexture((D3DXHANDLE)"DiffuseSampler", mesh->Material[0]->map->texturePtr);
		else
			FX->SetTexture((D3DXHANDLE)"DiffuseSampler", nullptr);
		D3DXVECTOR4 gWorldLightPosition(CAMERA->eye.x, CAMERA->eye.y, CAMERA->eye.z, 1.0f);
		D3DXVECTOR4 gWorldCameraPosition(CAMERA->eye.x, CAMERA->eye.y, CAMERA->eye.z, 1.0f);
		FX->SetVector((D3DXHANDLE)"gWorldLightPosition", &gWorldLightPosition);
		FX->SetVector((D3DXHANDLE)"gWorldCameraPosition", &gWorldCameraPosition);
		FX->SetMatrix((D3DXHANDLE)"m_World", &matW);
		FX->SetMatrix((D3DXHANDLE)"m_View", &CAMERA->view);
		FX->SetMatrix((D3DXHANDLE)"m_Proj", &CAMERA->proj);
		
		//Vec3 vecDir;		
		//vecDir = Vec3(0, 0, 4);
		//D3DXVec3TransformCoord(&vecDir, &vecDir, &CAMERA->view);
		//D3DXVec3Normalize((Vec3*)&vecDir, &vecDir);
		//
		//FX->SetVector((D3DXHANDLE)"gLightDir", &D3DXVECTOR4(vecDir.x, vecDir.y, vecDir.z, 1.f));

		FX->SetTechnique((D3DXHANDLE)"BoSoo");
		
		UINT cPass;
		FX->Begin(&cPass, 0); //Pass∞° ∏Ó∞≥¿Œ¡ˆ πﬁæ∆ø»
		
		for (UINT p = 0; p < cPass; ++p)
		{
			FX->BeginPass(p);
		
			g_Device->SetTransform(D3DTS_WORLD, &matW); //fx«“∂© æ»«ÿµµµ 
			for (int i = 0; i < mesh->Material.size(); ++i)
			{
				if (mesh->Material[i]->map) {
					g_Device->SetTexture(0, mesh->Material[i]->map->texturePtr);
				}
				else
					g_Device->SetTexture(0, nullptr);
				mesh->Material[i]->material.Diffuse.r = mesh->Material[i]->material.Ambient.r = 1.0f;
				mesh->Material[i]->material.Diffuse.g = mesh->Material[i]->material.Ambient.g = 1.0f;
				mesh->Material[i]->material.Diffuse.b = mesh->Material[i]->material.Ambient.b = 1.0f;
				mesh->Material[i]->material.Diffuse.a = mesh->Material[i]->material.Ambient.a = 1.0f;
				
				D3DLIGHT9 light;
				ZeroMemory(&light, sizeof(D3DLIGHT9));
				light.Type = D3DLIGHT_SPOT;

				Vec3 vecDir = Vec3(0.f,0.f,1.f);
				//vecDir = CAMERA->eye - CAMERA->GetTarget();//Vec3(0, 0, 1);
				D3DXVec3TransformCoord(&vecDir, &vecDir, &CAMERA->view);
				D3DXVec3Normalize(&vecDir, &vecDir);
				light.Direction = vecDir;
				light.Position.x = CAMERA->eye.x;
				light.Position.y = CAMERA->eye.y;
				light.Position.z = CAMERA->eye.z;

				light.Diffuse.r = 1.f;
				light.Diffuse.g = 1.f;
				light.Diffuse.b = 0.1f;
				light.Diffuse.a = 1.f;

				light.Falloff = 1.f;
				light.Theta = D3DX_PI / 4.f;
				light.Phi = D3DX_PI / 2.f;
				light.Range = 300.f;

				g_Device->SetLight(0, &light);
				g_Device->LightEnable(0, true);
				g_Device->SetRenderState(D3DRS_LIGHTING, true);
				g_Device->SetRenderState(D3DRS_AMBIENT, 0x00040404);

				g_Device->SetMaterial(&mesh->Material[i]->material);

				mesh->mesh->DrawSubset(i);
	     	}
		
			FX->EndPass();
		
		}
		FX->End();
	}
}

void cOBJManager::RenderShadow(Mesh * mesh, Vec3 Pos)
{
	g_Device->SetRenderState(D3DRS_STENCILENABLE, true);
	g_Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	g_Device->SetRenderState(D3DRS_STENCILREF, 0x0);
	g_Device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	g_Device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	g_Device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	g_Device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	g_Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	
	D3DXVECTOR4 lightDirection(0.f, -0.5f, 0.f, 0.0f);
	D3DXPLANE groundPlane(0.0f, -1.0f, 0.0f, 0.0f);

	D3DXMATRIX S;
	D3DXMatrixShadow(&S, &lightDirection, &groundPlane);

	D3DXMATRIX T;
	D3DXMatrixTranslation(&T, Pos.x, Pos.y, Pos.z);
	D3DXMATRIX W = T * S;
	g_Device->SetTransform(D3DTS_WORLD, &W);

	g_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTALPHA);

	Material * mtrl = new Material();
	mtrl->material.Diffuse.r = 0.f;
	mtrl->material.Diffuse.g = 0.f;
	mtrl->material.Diffuse.b = 0.f;
	mtrl->material.Power = 0.f;

	mtrl->material.Diffuse.a = 0.5f;

	g_Device->SetRenderState(D3DRS_ZENABLE, false);

	g_Device->SetMaterial(&mtrl->material);
	g_Device->SetTexture(0, 0);
	mesh->mesh->DrawSubset(0);

	g_Device->SetRenderState(D3DRS_ZENABLE, true);

	g_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_Device->SetRenderState(D3DRS_STENCILENABLE, false);
	SAFE_DELETE(mtrl);
}

void cOBJManager::Release()
{
	for (auto iter : m_Mesh)
		SAFE_DELETE(iter.second);

	m_Mesh.clear();

	for (auto iter : m_MultiMesh) {
		for (auto _iter : (*iter.second)) {
			SAFE_DELETE(_iter);
		}
		SAFE_DELETE(iter.second);
	}

	m_Mesh.clear();
}
