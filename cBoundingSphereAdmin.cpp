#include "DXUT.h"
#include "cBoundingSphereAdmin.h"

#include "cBoundingSphere.h"

cBoundingSphereAdmin::cBoundingSphereAdmin()
{
}


cBoundingSphereAdmin::~cBoundingSphereAdmin()
{
	Release();
}

void cBoundingSphereAdmin::Init()
{
}

void cBoundingSphereAdmin::Update()
{
	for (auto iter = m_Bounding.begin(); iter != m_Bounding.end();) {
		if ((*iter)->GetDel()) {
			SAFE_DELETE(*iter);
			iter = m_Bounding.erase(iter);
		}
		else
			++iter;
	}
	
	for (auto iter : m_Bounding)
		iter->Update();


	for (auto iter : m_Bounding) {
		for (auto iter_ : m_Bounding) {
			if (iter->GetTag() != MAP && iter != iter_ && iter->GetActive() && iter_->GetActive()) {
				Vec3 Distance = iter->GetPos() - iter_->GetPos();
				float fDistance = D3DXVec3Length(&Distance);
				if (fDistance < iter->GetSize() + iter_->GetSize()) {
					if (iter_->GetTag() == PLAYERBULLET) {
						iter_->GetCollinfo().push_back(new CollInfo(*iter->GetInfo()));
						iter_->SetActive(false);
					}
					iter->GetCollinfo().push_back(new CollInfo(*iter_->GetInfo()));
				}
			}
		}
	}

} 

void cBoundingSphereAdmin::Render()
{
	for (auto iter : m_Bounding) {
		if (iter->GetActive())
			iter->Render();
	}
}

void cBoundingSphereAdmin::Release()
{
	for (auto iter : m_Bounding)
		SAFE_DELETE(iter);
	m_Bounding.clear();
}
