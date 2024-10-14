#include "DXUT.h"
#include "cPlayer.h"

#include "cBullet.h"

void cPlayer::CheckColl()
{
	if (!m_BoundingSphere->GetDel() && m_BoundingSphere) {
		for (auto iter : m_BoundingSphere->GetCollinfo()) {
			if (iter->Tag == DARKBALL || iter->Tag == BAT) {
				g_Effect.GetEffect().push_back(new cEffect(IMAGE->FindImage("BloodEffect"), iter->Pos, 1.f, 0.05f));
				i_Hp -= 2;
				INPUT->DuplicatePlay("Hit", 100);
			}
			else if (iter->Tag == MAP) {
				Vec3 CollDis = iter->Pos - vPos;
				float fCollDis = (m_BoundingSphere->GetSize() + iter->Size) - D3DXVec3Length(&CollDis);
				D3DXVec3Normalize(&CollDis, &CollDis);
				vPos -= Vec3(CollDis.x, 0, CollDis.z) * 0.8f;
			}
		}
	}
}

cPlayer::cPlayer(vector<cBullet *>& Bullet)
	: m_Bullet(Bullet)
{
	m_IdleFrame = new cFrame();
	m_IdleFrame->SetFrame(0, 231, 1.f);
	m_PistolMoveFrame = new cFrame();
	m_PistolMoveFrame->SetFrame(0, 24, 1.f);
	m_PistolShootFrame = new cFrame();
	m_PistolShootFrame->SetFrame(0, 35, 1.f);
	m_BigGunMoveFrame = new cFrame();
	m_BigGunMoveFrame->SetFrame(0, 30, 1.f);
	m_BigGunShootFrame = new cFrame();
	m_BigGunShootFrame->SetFrame(0, 17, 1.f);
	m_DeadFrame = new cFrame();
	m_DeadFrame->SetFrame(0, 99, 1.f);
	Init();

	m_HPGauge = IMAGE->FindImage("PlayerHPGauge");
	m_HPEdge = IMAGE->FindImage("PlayerHPEdge");
}


cPlayer::~cPlayer()
{
	Release();
}

void cPlayer::Init()
{
	RotX = RotY = RotZ = 0;
	vPos = { 0,0,0 };
	fSpeed = 1.f;
	vOriginDir = vDir = { 0, 0, 1.f };
	Angle = 0;
	ShootAngle = 0;
	CurAngle = 0;
	AimAngle = 0;
	prevQ = { 0,0,0,1 };

	IsAttack = false;
	IsAiming = false;
	IsMove = false;
	IsFixedCamera = false;
	IsBackMove = false;

	WeaponState = Pistol;
	i_Hp = 100;
	InvincibilityDelay = 0;
	b_IsHit = false;

	m_BoundingSphere = new cBoundingSphere;
	m_BoundingSphere->ComputeBoundingSphere(PLAYER, 5.f);
	g_Bounding.GetBounding().push_back(m_BoundingSphere);
	IsDead = false;
	IsSceneChange = false;
	DeadDelay = 0;
}

void cPlayer::Update()
{
	if (HealCount > 0) {
		i_Hp += HealCount;
		HealCount = 0;
		if (i_Hp >= 100)
			i_Hp = 100;
	}

	if (INPUT->KeyDown(VK_F1)) {
		i_Hp = i_MaxHp;
	}
	if (INPUT->KeyDown(VK_F2)) {
		CoinCount += 1000;
	}
	Damage = CoinCount * 1.2f;
	//if (INPUT->KeyDown(VK_F3)) {
	//	Damage *= 100;
	//}

	m_BoundingSphere->SetPos(vPos + Vec3(0, 10, 0));

	if (!IsDead && i_Hp <= 0) {
		IsDead = true;
	}

	if (IsDead && !IsSceneChange) {
		m_DeadFrame->Frame();

		if (m_DeadFrame->NowFrame == m_DeadFrame->EndFrame && !IsSceneChange)
			IsSceneChange = true;
	}
	else if (IsDead && IsSceneChange) {
		DeadDelay += DeltaTime;
		if (DeadDelay > 1.5f)
			SCENE->ChangeScene("GameOver");
	}
	else {
		if (!IsDebug && INPUT->MouseLPress()) {
			ShootBullet();
		}
		//if (INPUT->KeyDown('1')) {
		//	WeaponState = Pistol;
		//}
		//if (INPUT->KeyDown('2')) {
		//	WeaponState = BigGun;
		//}
		if (CoinCount >= 10)
			WeaponState = BigGun;

		fSpeed = 0;

		if (INPUT->KeyPress('Q')) {
			if (!IsSnipe)
				Angle = CAMERA->GetAngle();
			else {
				Angle = CAMERA->GetAngle();
			}
			IsFixedCamera = true;
		}
		else {
			if (!IsSnipe)
				Angle = CAMERA->GetAngle();
			else {
				Angle = CAMERA->GetAngle();
			}
			IsFixedCamera = false;
		}

		m_IdleFrame->Frame();

		if (INPUT->MouseRPress()) {
			AimAngle = Angle;
			IsSnipe = true;
		}
		else
			IsSnipe = false;

		if (IsMove && INPUT->MouseLPress())
			IsFixedCamera = true;

		if (IsSnipe)
			SnipeMove();
		else
			Move();

		if (IsAttack) {
			IsAiming = true;
			//Angle = ShootAngle;
			//fSpeed = 0.f;
			switch (WeaponState)
			{
			case Pistol:
				m_PistolShootFrame->Frame();
				if (m_PistolShootFrame->NowFrame == m_PistolShootFrame->EndFrame)
					IsAttack = false;
				break;
			case BigGun:
				m_BigGunShootFrame->Frame();
				if (m_BigGunShootFrame->NowFrame == m_BigGunShootFrame->EndFrame)
					IsAttack = false;
				break;
			case None:
				break;
			default:
				break;
			}
		}
		else {
			m_PistolShootFrame->NowFrame = m_PistolShootFrame->StartFrame;
			m_BigGunShootFrame->NowFrame = m_BigGunShootFrame->StartFrame;
		}

		if (fSpeed == 0) {
			IsMove = false;
		}
		else {
			IsMove = true;
			IsAiming = false;
			m_PistolMoveFrame->Frame();
			m_BigGunMoveFrame->Frame();
		}
	

		if (IsSnipe) {
			D3DXMATRIX matX, matY, matZ, matR;

			Vec3 CameraDir;
			D3DXMatrixRotationX(&matX, D3DXToRadian(0));
			D3DXMatrixRotationY(&matY, D3DXToRadian(CAMERA->GetAngle() - 90));
			D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
			matR = matX * matY * matZ;
			D3DXVec3TransformNormal(&CameraDir, &Vec3(-1, 0, -1), &matR);

			vCameraPos = Vec3(vPos.x, vPos.y + 15, vPos.z);
			vCameraPos += CameraDir * 7.f;
			CAMERA->SetPos(vCameraPos);
			///////////////////////////////

			D3DXMatrixRotationX(&matX, D3DXToRadian(0));
			D3DXMatrixRotationY(&matY, D3DXToRadian(AimAngle));
			D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
			matR = matX * matY * matZ;
			D3DXVec3TransformNormal(&CameraDir, &vOriginDir, &matR);

			Vec3 TargetPos;
			TargetPos = Vec3(vPos.x, vPos.y + 15, vPos.z);
			TargetPos += CameraDir * 60.f;
			CAMERA->SetTarget(TargetPos);
		}
		else
			CAMERA->SetTarget(Vec3(vPos.x, vPos.y + 15, vPos.z));

		CheckColl();

		if (b_IsHit) {
			if (InvincibilityDelay < 1.f) {
				InvincibilityDelay += DeltaTime;
			}
			else {
				b_IsHit = false;
				InvincibilityDelay = 0;
			}
		}
	}
}

void cPlayer::Render()
{
	//Hp 
	IMAGE->ReBegin(true, false);
	IMAGE->Render(m_HPEdge, Vec3(m_HPEdge->info.Width / 2 + 50, m_HPEdge->info.Height / 2 + 25, 0), 0, true);

	if (i_Hp <= 0) {
		i_Hp = 0;
	}
	RECT HpRECT{ 0, 0, ((float)m_HPGauge->info.Width / i_MaxHp) * i_Hp, m_HPGauge->info.Height };
	IMAGE->CropRender(m_HPGauge, Vec3(m_HPEdge->info.Width / 2 + 50, m_HPEdge->info.Height / 2 + 25, 0), HpRECT);
	IMAGE->ReBegin(false, false);


	// 각도 바꾸는거
	D3DXMATRIX matX, matY, matZ;

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(Angle));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));

	D3DXMATRIX matR;
	matR = matX * matY * matZ;
	D3DXQUATERNION currQ;
	D3DXQuaternionRotationMatrix(&currQ, &matR);
	D3DXQuaternionSlerp(&prevQ, &prevQ, &currQ, 0.1f);
	D3DXMATRIX mRQ;
	D3DXMatrixRotationQuaternion(&mRQ, &prevQ);
	// 방향 바꾸는거

	if (IsSnipe) {
		D3DXMatrixRotationX(&matX, D3DXToRadian(0));
		D3DXMatrixRotationY(&matY, D3DXToRadian(CAMERA->GetAngle()));
		D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
		mRQ = matX * matY * matZ;
		D3DXVec3TransformNormal(&vDir, &vOriginDir, &matR);
	}
	else
		D3DXVec3TransformNormal(&vDir, &vOriginDir, &mRQ);



	if (IsDead) {
		OBJ->Render(OBJ->FindMultidOBJ("Player_Dead", m_DeadFrame->NowFrame), vPos, mRQ, 0.01f);
	}
	else {
		if (IsMove) {
			switch (WeaponState)
			{
			case Pistol:
				if (IsBackMove)
					OBJ->Render(OBJ->FindMultidOBJ("Player_Pistol_Walk", m_PistolMoveFrame->EndFrame - m_PistolMoveFrame->NowFrame), vPos, mRQ, 0.01f);
				else
					OBJ->Render(OBJ->FindMultidOBJ("Player_Pistol_Walk", m_PistolMoveFrame->NowFrame), vPos, mRQ, 0.01f);
				break;
			case BigGun:
				if (IsBackMove)
					OBJ->Render(OBJ->FindMultidOBJ("Player_BigGun_Walk", m_BigGunMoveFrame->EndFrame - m_BigGunMoveFrame->NowFrame), vPos, mRQ, 0.01f);
				else
					OBJ->Render(OBJ->FindMultidOBJ("Player_BigGun_Walk", m_BigGunMoveFrame->NowFrame), vPos, mRQ, 0.01f);
				break;
			case None:
				break;
			default:
				break;
			}
		}
		else if (!IsMove && !IsAiming){
			switch (WeaponState)
			{
			case Pistol:
				OBJ->Render(OBJ->FindMultidOBJ("Player_Pistol_Idle", m_IdleFrame->NowFrame), vPos, mRQ, 0.01f);
				break;
			case BigGun:
				OBJ->Render(OBJ->FindMultidOBJ("Player_BigGun_Idle", m_IdleFrame->NowFrame), vPos, mRQ, 0.01f);
				break;
			case None:
				break;
			default:
				break;
			}
		}
		else if (IsAiming && !IsMove) {
			switch (WeaponState)
			{
			case Pistol:
				OBJ->Render(OBJ->FindMultidOBJ("Player_Pistol_Shoot", m_PistolShootFrame->NowFrame), vPos, mRQ, 0.01f);
				break;
			case BigGun:
				OBJ->Render(OBJ->FindMultidOBJ("Player_BigGun_Shoot", m_BigGunShootFrame->NowFrame), vPos, mRQ, 0.01f);
				break;
			case None:
				break;
			default:
				break;
			}
		}
	}

	IMAGE->ReBegin(true, false);
	IMAGE->PrintText("좌표 : " + to_string(vPos.x) + " " + to_string(vPos.y) + " " + to_string(vPos.z), Vec3(0, 150, 0), 20, D3DCOLOR_XRGB(255, 255, 255), false);

	if (INPUT->MouseRPress()) {
		IMAGE->Render(IMAGE->FindImage("Aim"), Vec3(WINSIZEX / 2, WINSIZEY / 2, 0), 0, true);
	}
	IMAGE->ReBegin(false, false);
}

void cPlayer::Release()
{
	SAFE_DELETE(m_IdleFrame);
	SAFE_DELETE(m_PistolMoveFrame);
	SAFE_DELETE(m_PistolShootFrame);
	SAFE_DELETE(m_BigGunMoveFrame);
	SAFE_DELETE(m_BigGunShootFrame);
	SAFE_DELETE(m_DeadFrame);
}

void cPlayer::Move()
{
	//if (!IsAttack) {
		if (INPUT->KeyPress('A') || INPUT->KeyPress('D')) {
			if (INPUT->KeyPress('A')) {
				if (INPUT->KeyPress('W')) {
					if (IsFixedCamera)
						Angle -= 30;
					else
						Angle -= 45;
				}

				else if (INPUT->KeyPress('S')) {
					if (IsFixedCamera)
						Angle += 30;
					else
						Angle += 45;
				}
				else {
					if (IsFixedCamera)
						Angle -= 20;
					else
						Angle -= 90;
				}
				//Angle = CAMERA->GetAngle() - 90;
			}
			if (INPUT->KeyPress('D')) {
				if (INPUT->KeyPress('W')) {
					if (IsFixedCamera)
						Angle += 30;
					else
						Angle += 45;
				}
				else if (INPUT->KeyPress('S')) {
					if (IsFixedCamera)
						Angle -= 30;
					else
						Angle -= 45;
					IsBackMove = true;
				}
				else {
					if (IsFixedCamera)
						Angle += 20;
					else
						Angle += 90;
				}
				//Angle = CAMERA->GetAngle() + 90;
			}
		}

		if ((INPUT->KeyPress('S') && IsFixedCamera)) {
			IsBackMove = true;
			fSpeed = -1.f;
		}
		else if (INPUT->KeyPress('W') || INPUT->KeyPress('A') || INPUT->KeyPress('D') || INPUT->KeyPress('S'))
		{
			if (INPUT->KeyPress('S'))
				Angle -= 180;

			IsBackMove = false;
			fSpeed = 1.f;
		}
		if (INPUT->MouseLPress() && !IsAttack) {
			ShootBullet();
		}
	//}

	vPos += vDir * fSpeed;
}

void cPlayer::SnipeMove()
{
	IsAiming = true;
	//if (!IsAttack) {
		if (INPUT->KeyPress('A')) {
			if (INPUT->KeyPress('W'))
				Angle = AimAngle - 45;
			else if(INPUT->KeyPress('S'))
				Angle = AimAngle + 45;
			else
				Angle = AimAngle - 90;
		}
		else if (INPUT->KeyPress('D')) {
			if (INPUT->KeyPress('W'))
				Angle = AimAngle + 45;
			else if (INPUT->KeyPress('S'))
				Angle = AimAngle - 45;
			else
				Angle = AimAngle + 90;
		}

		if ((INPUT->KeyPress('S'))) {
			fSpeed = -1.f;
		}
		else if (INPUT->KeyPress('W') || INPUT->KeyPress('A') || INPUT->KeyPress('D') || INPUT->KeyPress('S'))
			fSpeed = 1.f;
		
		if (INPUT->MouseLPress() && !IsAttack) {
			ShootBullet();
		}
	//}
	//Vec3 TargetPos = vPos + vDir * fSpeed;
	//D3DXVec3Lerp(&vPos, &vPos, &TargetPos, 0.8f);

		D3DXMATRIX matX, matY, matZ, matR;

		D3DXMatrixRotationX(&matX, D3DXToRadian(0));
		D3DXMatrixRotationY(&matY, D3DXToRadian(Angle));
		D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
		matR = matX * matY * matZ;
		D3DXVec3TransformNormal(&vDir, &vOriginDir, &matR);

	vPos += vDir * fSpeed * 0.6f;
}

void cPlayer::ShootBullet()
{
	IsAttack = true;
	ShootAngle = Angle;

	Vec3 ShootDir = Vec3(0, 0, 1);
	Vec3 PistolDir = Vec3(0, 0, 1);
	Vec3 BigGunDir = Vec3(0, 0, 1);
	if (IsSnipe) {
		D3DXMATRIX matX, matY, matZ, matR;

		D3DXMatrixRotationX(&matX, D3DXToRadian(0));
		D3DXMatrixRotationY(&matY, D3DXToRadian(AimAngle - 13));
		D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
		matR = matX * matY * matZ;
		D3DXVec3TransformNormal(&PistolDir, &vOriginDir, &matR);
		D3DXVec3TransformNormal(&BigGunDir, &vOriginDir, &matR);

		D3DXMatrixRotationX(&matX, D3DXToRadian(0));
		D3DXMatrixRotationY(&matY, D3DXToRadian(AimAngle));
		D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
		matR = matX * matY * matZ;
		D3DXVec3TransformNormal(&ShootDir, &vOriginDir, &matR);

		BigGunDir *= 15;
	}
	else {
		D3DXMATRIX matX, matY, matZ, matR;

		if (!IsFixedCamera) {
		    D3DXMatrixRotationX(&matX, D3DXToRadian(0));
		    D3DXMatrixRotationY(&matY, D3DXToRadian(CAMERA->GetAngle() - 8));
		    D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
		    matR = matX * matY * matZ;
		    D3DXVec3TransformNormal(&PistolDir, &vOriginDir, &matR);
		    
		    D3DXMatrixRotationX(&matX, D3DXToRadian(0));
		    D3DXMatrixRotationY(&matY, D3DXToRadian(CAMERA->GetAngle() - 2));
		    D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
		    matR = matX * matY * matZ;
		    D3DXVec3TransformNormal(&BigGunDir, &vOriginDir, &matR);

			D3DXMatrixRotationX(&matX, D3DXToRadian(0));
			D3DXMatrixRotationY(&matY, D3DXToRadian(CAMERA->GetAngle()));
			D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
			matR = matX * matY * matZ;
			D3DXVec3TransformNormal(&ShootDir, &vOriginDir, &matR);
		}
		else {
			D3DXMatrixRotationX(&matX, D3DXToRadian(0));
			D3DXMatrixRotationY(&matY, D3DXToRadian(Angle));
			D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
			matR = matX * matY * matZ;
			D3DXVec3TransformNormal(&PistolDir, &vOriginDir, &matR);

			D3DXMatrixRotationX(&matX, D3DXToRadian(0));
			D3DXMatrixRotationY(&matY, D3DXToRadian(Angle));
			D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
			matR = matX * matY * matZ;
			D3DXVec3TransformNormal(&BigGunDir, &vOriginDir, &matR);

			D3DXMatrixRotationX(&matX, D3DXToRadian(0));
			D3DXMatrixRotationY(&matY, D3DXToRadian(Angle));
			D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
			matR = matX * matY * matZ;
			D3DXVec3TransformNormal(&ShootDir, &vOriginDir, &matR);
		}
		BigGunDir *= 12;
	}


	switch (WeaponState)
	{
	case Pistol:
		INPUT->DuplicatePlay("Pistol", 100);
		m_Bullet.push_back(new cBullet(vPos + Vec3(0, 13, 0) + PistolDir * 13, ShootDir, PLAYERBULLET, 3.f, 0.8f, 5.f));
		break;
	case BigGun:
		INPUT->DuplicatePlay("Pistol", 100);
		m_Bullet.push_back(new cBullet(vPos + Vec3(0, 14, 0) + BigGunDir, ShootDir,PLAYERBULLET , 3.f, 0.8f, 5.f));
		break;
	case None:
		break;
	default:
		break;
	}
}
