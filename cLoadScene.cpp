#include "DXUT.h"
#include "cLoadScene.h"

#include "cThreadPoolManager.h"
//void cLoadScene::func1(int A)
//{
//	printf("%d", A);
//}
//
//void cLoadScene::ThreadLoad(int A, int B, mutex& m)
//{
//	//m.lock();
//	lock_guard<mutex> lock(m);
//		DEBUG_LOG(m_OBJLoad[B].key << " / " << m_OBJLoad[B].path << " / " << m_OBJLoad[B].count << " : " << NowOBJLoad);
//		if (m_OBJLoad[B].count == 0)
//    		OBJ->AddOBJ(
//    			m_OBJLoad[B].key,
//    			m_OBJLoad[B].path,
//    			m_OBJLoad[B].mappath);
//    	else
//    		OBJ->AddMultiOBJ(
//    			m_OBJLoad[B].key,
//    			m_OBJLoad[B].path,
//    			m_OBJLoad[B].mappath,
//    			m_OBJLoad[B].count,
//    			m_OBJLoad[B].mtlpath);
//    	NowOBJLoad += 1;
//}

int cLoadScene::ThreadLoadOBJ(int NowCount)
{
	if (m_OBJLoad[NowCount].count == 0)
		OBJ->AddOBJ(
			m_OBJLoad[NowCount].key,
			m_OBJLoad[NowCount].path,
			m_OBJLoad[NowCount].mappath);
	else
		OBJ->AddMultiOBJ(
			m_OBJLoad[NowCount].key,
			m_OBJLoad[NowCount].path,
			m_OBJLoad[NowCount].mappath,
			m_OBJLoad[NowCount].count,
			m_OBJLoad[NowCount].mtlpath);
	DEBUG_LOG(NowCount << " / " << MaxOBJLoad);

	return NowOBJLoad;
}

cLoadScene::cLoadScene()
{
}


cLoadScene::~cLoadScene()
{
}

void cLoadScene::Init()
{
	//Thread.Init();
	
	NowLoad = 0;
	NowOBJLoad = 0;

	Load("Shader_Boss", "./Fx/AA.png");

	Load("BloodEffect", "./resorce/Effect/Blood/(%d).png", 5);

	Load("Aim", "./resorce/Aim.png");

	Load("CoinEffect", "./resorce/Effect/Coin/(%d).png", 15);
	Load("HealEffect", "./resorce/Effect/Heal/(%d).png", 15);

	Load("PlayerHPGauge", "./resorce/Player/HPGauge.png");
	Load("PlayerHPEdge", "./resorce/Player/HPEdge.png");
	Load("EnemyHPGauge", "./resorce/Enemy/HPGauge.png");
	Load("EnemyHPEdge", "./resorce/Enemy/HPEdge.png");
	Load("BossHPGauge", "./resorce/Enemy/BossHPGauge.png");
	Load("BossHPEdge", "./resorce/Enemy/BossHPEdge.png");

	Load("Title", "./resorce/Title.png");
	Load("Clear", "./resorce/Clear.png");
	Load("GameOver", "./resorce/GameOver.png");

	OBJLoad("Map", "./resorce/Map/Map.obj", "./resorce/Map/");
	OBJLoad("Floor", "./resorce/Floor.obj", "./resorce/");
	OBJLoad("SkyBox", "./resorce/SkyBox.obj", "./resorce/");
	OBJLoad("Tree", "./resorce/Tree/Tree.obj", "./resorce/Tree/");
	OBJLoad("Coin", "./resorce/Item/Coin/Coin.obj", "./resorce/Item/Coin/");
	OBJLoad("Heal", "./resorce/Item/Heal/Heal.obj", "./resorce/Item/Heal/");

	if (IsDebug) {
		OBJLoad("Player_Dead", "./resorce/Player/Dead/PlayerDead(%d).obj", "./resorce/Player/Dead/", 99, "PlayerDead.mtl");

		OBJLoad("Player_Pistol_Idle", "./resorce/Player/Pistol/Idle/PlayerIdle(%d).obj", "./resorce/Player/Pistol/Idle/", 231, "PlayerIdle.mtl");
		OBJLoad("Player_Pistol_Walk", "./resorce/Player/Pistol/Walk/PlayerWalk(%d).obj", "./resorce/Player/Pistol/Walk/", 24, "PlayerWalk.mtl");
		OBJLoad("Player_Pistol_Shoot", "./resorce/Player/Pistol/Shoot/PlayerShoot(%d).obj", "./resorce/Player/Pistol/Shoot/", 35, "PlayerShoot.mtl");

		OBJLoad("Player_BigGun_Idle", "./resorce/Player/BigGun/Idle/PlayerIdle(%d).obj", "./resorce/Player/BigGun/Idle/", 231, "PlayerIdle.mtl");
		OBJLoad("Player_BigGun_Walk", "./resorce/Player/BigGun/Walk/PlayerWalk(%d).obj", "./resorce/Player/BigGun/Walk/", 30, "PlayerWalk.mtl");
		OBJLoad("Player_BigGun_Shoot", "./resorce/Player/BigGun/Shoot/PlayerShoot(%d).obj", "./resorce/Player/BigGun/Shoot/", 17, "PlayerShoot.mtl");

		OBJLoad("Player_Bullet", "./resorce/Player/Bullet.obj", "./resorce/Player/");

		//Wolf
		OBJLoad("Wolf_Idle", "./resorce/Enemy/Wolf/Idle/WolfIdle_(%d).obj", "./resorce/Enemy/Wolf/Idle/", 140, "WolfIdle.mtl");
		OBJLoad("Wolf_Walk", "./resorce/Enemy/Wolf/Walk/WolfWalk(%d).obj", "./resorce/Enemy/Wolf/Walk/", 42, "WolfWalk.mtl");
		OBJLoad("Wolf_Attack", "./resorce/Enemy/Wolf/Attack/WolfAttack(%d).obj", "./resorce/Enemy/Wolf/Attack/", 115, "WolfAttack.mtl");
		OBJLoad("Wolf_Dead", "./resorce/Enemy/Wolf/Dead/WolfDead(%d).obj", "./resorce/Enemy/Wolf/Dead/", 110, "WolfDead.mtl");

		//Zombie
		OBJLoad("Zombie_Idle", "./resorce/Enemy/Zombie/Idle/ZombieIdle(%d).obj", "./resorce/Enemy/Zombie/Idle/", 120, "ZombieIdle.mtl");
		OBJLoad("Zombie_Walk", "./resorce/Enemy/Zombie/Walk/ZombieWalk(%d).obj", "./resorce/Enemy/Zombie/Walk/", 24, "ZombieWalk.mtl");
		OBJLoad("Zombie_Attack", "./resorce/Enemy/Zombie/Attack/ZombieAttack(%d).obj", "./resorce/Enemy/Zombie/Attack/", 139, "ZombieAttack.mtl");
		OBJLoad("Zombie_Dead", "./resorce/Enemy/Zombie/Dead/ZombieDead(%d).obj", "./resorce/Enemy/Zombie/Dead/", 89, "ZombieDead.mtl");

		//Zombie
		OBJLoad("Zombie2_Idle", "./resorce/Enemy/Zombie2/Idle/ZombieIdle(%d).obj", "./resorce/Enemy/Zombie2/Idle/", 120, "ZombieIdle.mtl");
		OBJLoad("Zombie2_Walk", "./resorce/Enemy/Zombie2/Walk/ZombieWalk(%d).obj", "./resorce/Enemy/Zombie2/Walk/", 24, "ZombieWalk.mtl");
		OBJLoad("Zombie2_Attack", "./resorce/Enemy/Zombie2/Attack/ZombieAttack(%d).obj", "./resorce/Enemy/Zombie2/Attack/", 125, "ZombieAttack.mtl");
		OBJLoad("Zombie2_Dead", "./resorce/Enemy/Zombie2/Dead/ZombieDead(%d).obj", "./resorce/Enemy/Zombie2/Dead/", 89, "ZombieDead.mtl");

		//Reaper
		OBJLoad("Reaper_Idle", "./resorce/Enemy/Reaper/Idle/ReaperIdle(%d).obj", "./resorce/Enemy/Reaper/Idle/", 55, "ReaperIdle.mtl");
		OBJLoad("Reaper_Walk", "./resorce/Enemy/Reaper/Walk/ReaperWalk(%d).obj", "./resorce/Enemy/Reaper/Walk/", 42, "ReaperWalk.mtl");
		OBJLoad("Reaper_Attack", "./resorce/Enemy/Reaper/Attack/ReaperAttack(%d).obj", "./resorce/Enemy/Reaper/Attack/", 69, "ReaperAttack.mtl");
		OBJLoad("Reaper_Dead", "./resorce/Enemy/Reaper/Dead/ReaperDead(%d).obj", "./resorce/Enemy/Reaper/Dead/", 109, "ReaperDead.mtl");
		OBJLoad("DarkBall", "./resorce/Enemy/Reaper/Bullet/DarkBall.obj", "./resorce/Enemy/Reaper/Bullet/");

		Load("DarkBall", "./resorce/Enemy/Reaper/Bullet/(%d).png", 4);
		Load("DarkBallEffect", "./resorce/Enemy/Reaper/Bullet/Effect/(%d).png", 20);

		//Vampire
		OBJLoad("Vampire_Idle", "./resorce/Enemy/Vampire/Idle/VampireIdle(%d).obj", "./resorce/Enemy/Vampire/Idle/", 120, "VampireIdle.mtl");
		OBJLoad("Vampire_Walk", "./resorce/Enemy/Vampire/Walk/VampireWalk(%d).obj", "./resorce/Enemy/Vampire/Walk/", 31, "VampireWalk.mtl");
		OBJLoad("Vampire_Attack", "./resorce/Enemy/Vampire/Attack/VampireAttack(%d).obj", "./resorce/Enemy/Vampire/Attack/", 69, "VampireAttack.mtl");
		OBJLoad("Vampire_Attack2", "./resorce/Enemy/Vampire/Attack2/VampireAttack(%d).obj", "./resorce/Enemy/Vampire/Attack2/", 125, "VampireAttack.mtl");
		OBJLoad("Vampire_Dead", "./resorce/Enemy/Vampire/Dead/VampireDead(%d).obj", "./resorce/Enemy/Vampire/Dead/", 89, "VampireDead.mtl");

		OBJLoad("Bat", "./resorce/Enemy/Vampire/Bat.obj", "./resorce/Enemy/Vampire/");

	}
	else {
		OBJLoad("Player_Dead", "./resorce/Player/Dead/PlayerDead(%d).obj", "./resorce/Player/Dead/", 1, "PlayerDead.mtl");

		OBJLoad("Player_Pistol_Idle", "./resorce/Player/Pistol/Idle/PlayerIdle(%d).obj", "./resorce/Player/Pistol/Idle/", 1, "PlayerIdle.mtl");
		OBJLoad("Player_Pistol_Walk", "./resorce/Player/Pistol/Walk/PlayerWalk(%d).obj", "./resorce/Player/Pistol/Walk/", 1, "PlayerWalk.mtl");
		OBJLoad("Player_Pistol_Shoot", "./resorce/Player/Pistol/Shoot/PlayerShoot(%d).obj", "./resorce/Player/Pistol/Shoot/", 1, "PlayerShoot.mtl");

		OBJLoad("Player_BigGun_Idle", "./resorce/Player/BigGun/Idle/PlayerIdle(%d).obj", "./resorce/Player/BigGun/Idle/", 1, "PlayerIdle.mtl");
		OBJLoad("Player_BigGun_Walk", "./resorce/Player/BigGun/Walk/PlayerWalk(%d).obj", "./resorce/Player/BigGun/Walk/", 1, "PlayerWalk.mtl");
		OBJLoad("Player_BigGun_Shoot", "./resorce/Player/BigGun/Shoot/PlayerShoot(%d).obj", "./resorce/Player/BigGun/Shoot/", 1, "PlayerShoot.mtl");

		OBJLoad("Player_Bullet", "./resorce/Player/Bullet.obj", "./resorce/Player/");

		//Wolf
		OBJLoad("Wolf_Idle", "./resorce/Enemy/Wolf/Idle/WolfIdle_(%d).obj", "./resorce/Enemy/Wolf/Idle/", 1, "WolfIdle.mtl");
		OBJLoad("Wolf_Walk", "./resorce/Enemy/Wolf/Walk/WolfWalk(%d).obj", "./resorce/Enemy/Wolf/Walk/", 1, "WolfWalk.mtl");
		OBJLoad("Wolf_Attack", "./resorce/Enemy/Wolf/Attack/WolfAttack(%d).obj", "./resorce/Enemy/Wolf/Attack/", 1, "WolfAttack.mtl");
		OBJLoad("Wolf_Dead", "./resorce/Enemy/Wolf/Dead/WolfDead(%d).obj", "./resorce/Enemy/Wolf/Dead/", 1, "WolfDead.mtl");

		//Zombie
		OBJLoad("Zombie_Idle", "./resorce/Enemy/Zombie/Idle/ZombieIdle(%d).obj", "./resorce/Enemy/Zombie/Idle/", 1, "ZombieIdle.mtl");
		OBJLoad("Zombie_Walk", "./resorce/Enemy/Zombie/Walk/ZombieWalk(%d).obj", "./resorce/Enemy/Zombie/Walk/", 1, "ZombieWalk.mtl");
		OBJLoad("Zombie_Attack", "./resorce/Enemy/Zombie/Attack/ZombieAttack(%d).obj", "./resorce/Enemy/Zombie/Attack/", 1, "ZombieAttack.mtl");
		OBJLoad("Zombie_Dead", "./resorce/Enemy/Zombie/Dead/ZombieDead(%d).obj", "./resorce/Enemy/Zombie/Dead/", 1, "ZombieDead.mtl");

		//Zombie2
		OBJLoad("Zombie2_Idle", "./resorce/Enemy/Zombie2/Idle/ZombieIdle(%d).obj", "./resorce/Enemy/Zombie2/Idle/", 1, "ZombieIdle.mtl");
		OBJLoad("Zombie2_Walk", "./resorce/Enemy/Zombie2/Walk/ZombieWalk(%d).obj", "./resorce/Enemy/Zombie2/Walk/", 1, "ZombieWalk.mtl");
		OBJLoad("Zombie2_Attack", "./resorce/Enemy/Zombie2/Attack/ZombieAttack(%d).obj", "./resorce/Enemy/Zombie2/Attack/", 1, "ZombieAttack.mtl");
		OBJLoad("Zombie2_Dead", "./resorce/Enemy/Zombie2/Dead/ZombieDead(%d).obj", "./resorce/Enemy/Zombie2/Dead/", 1, "ZombieDead.mtl");

		//Reaper
		OBJLoad("Reaper_Idle", "./resorce/Enemy/Reaper/Idle/ReaperIdle(%d).obj", "./resorce/Enemy/Reaper/Idle/", 1, "ReaperIdle.mtl");
		OBJLoad("Reaper_Walk", "./resorce/Enemy/Reaper/Walk/ReaperWalk(%d).obj", "./resorce/Enemy/Reaper/Walk/", 1, "ReaperWalk.mtl");
		OBJLoad("Reaper_Attack", "./resorce/Enemy/Reaper/Attack/ReaperAttack(%d).obj", "./resorce/Enemy/Reaper/Attack/", 1, "ReaperAttack.mtl");
		OBJLoad("Reaper_Dead", "./resorce/Enemy/Reaper/Dead/ReaperDead(%d).obj", "./resorce/Enemy/Reaper/Dead/", 1, "ReaperDead.mtl");
		OBJLoad("DarkBall", "./resorce/Enemy/Reaper/Bullet/DarkBall.obj", "./resorce/Enemy/Reaper/Bullet/");

		Load("DarkBall", "./resorce/Enemy/Reaper/Bullet/(%d).png", 4);
		Load("DarkBallEffect", "./resorce/Enemy/Reaper/Bullet/Effect/(%d).png", 20);

		//Vampire
		OBJLoad("Vampire_Idle", "./resorce/Enemy/Vampire/Idle/VampireIdle(%d).obj", "./resorce/Enemy/Vampire/Idle/", 1, "VampireIdle.mtl");
		OBJLoad("Vampire_Walk", "./resorce/Enemy/Vampire/Walk/VampireWalk(%d).obj", "./resorce/Enemy/Vampire/Walk/", 1, "VampireWalk.mtl");
		OBJLoad("Vampire_Attack", "./resorce/Enemy/Vampire/Attack/VampireAttack(%d).obj", "./resorce/Enemy/Vampire/Attack/", 1, "VampireAttack.mtl");
		OBJLoad("Vampire_Attack2", "./resorce/Enemy/Vampire/Attack2/VampireAttack(%d).obj", "./resorce/Enemy/Vampire/Attack2/", 1, "VampireAttack.mtl");
		OBJLoad("Vampire_Dead", "./resorce/Enemy/Vampire/Dead/VampireDead(%d).obj", "./resorce/Enemy/Vampire/Dead/", 1, "VampireDead.mtl");

		OBJLoad("Bat", "./resorce/Enemy/Vampire/Bat.obj", "./resorce/Enemy/Vampire/");
	}

	MaxLoad = m_Load.size();
	MaxOBJLoad = m_OBJLoad.size();

	INPUT->AddSound("BGM", L"./Sound/BGM.wav");
	INPUT->AddSound("Title", L"./Sound/Title.wav");
	INPUT->AddSound("BigGun", L"./Sound/BigGun.wav");
	INPUT->AddSound("Pistol", L"./Sound/Pistol.wav");
	INPUT->AddSound("WolfHowl", L"./Sound/WolfHowl.wav");
	INPUT->AddSound("Zombie1", L"./Sound/Zombie1.wav");
	INPUT->AddSound("Zombie2", L"./Sound/Zombie2.wav");

	INPUT->AddSound("Heal", L"./Sound/Heal.wav");
	INPUT->AddSound("Coin", L"./Sound/Coin.wav");
	INPUT->AddSound("Hit", L"./Sound/Hit.wav");
	//멀티스레드

	//for (int i = 0; i < MaxOBJLoad; i++) {
	//	futures.emplace_back(Thread.EnqueueJob([&] { ThreadLoadOBJ(i); }));
	//}
	//for (auto& f : futures)
	//	printf("result : %d\n", f.get());
	
	
	///////////////////////

	//for (int i = 0; i < 8; i++) {
	//	int A = i * (MaxOBJLoad / 8);
	//	int B = A + MaxOBJLoad / 8 - 1;
	//	//ThreadLoad(A, B, m_OBJLoad, &NowOBJLoad);
	//	//std::function <void()> f1 = ThreadLoad(A, B, m_OBJLoad, &NowOBJLoad);
	//	workers.push_back(thread([&] {ThreadLoad(A, B, m_OBJLoad, &NowOBJLoad); }));
	//}
	//
	//int A = MaxOBJLoad - MaxOBJLoad % 8;
	//int B = MaxOBJLoad;

	//이거만 가능
	//for (int i = 0; i < MaxOBJLoad; i++) {
	//	DEBUG_LOG(i);
	//	workers.push_back(thread([&] {ThreadLoad(0, i, ref(Mutex)); }));
	//}


    //DEBUG_LOG(workers.size());
	//for (int i = 0; i < workers.size(); i++) {
	//	workers[i].join();
	//}
}

void cLoadScene::Update()
{
	if (NowLoad != MaxLoad) {
		IMAGE->AddImage(
			m_Load[NowLoad].key,
			m_Load[NowLoad].path,
			m_Load[NowLoad].count);
		NowLoad++;
	}
	else {
		//if(Thread.stop_all)
		//	SCENE->ChangeScene("Title");


		if (NowOBJLoad != MaxOBJLoad) {
			//for (int i = 0; i < MaxOBJLoad; i++) {
			//	workers[i].join();
			//}
			if(m_OBJLoad[NowOBJLoad].count == 0)
			OBJ->AddOBJ(
				m_OBJLoad[NowOBJLoad].key,
				m_OBJLoad[NowOBJLoad].path,
				m_OBJLoad[NowOBJLoad].mappath);
			else
			OBJ->AddMultiOBJ(
				m_OBJLoad[NowOBJLoad].key,
				m_OBJLoad[NowOBJLoad].path,
				m_OBJLoad[NowOBJLoad].mappath,
				m_OBJLoad[NowOBJLoad].count,
				m_OBJLoad[NowOBJLoad].mtlpath);
			DEBUG_LOG(NowOBJLoad << " / " << MaxOBJLoad);
			NowOBJLoad++;
		}
		else {
			SCENE->ChangeScene("Title");
		}
		//SCENE->ChangeScene("Title");
	}
}

void cLoadScene::Render()
{
	IMAGE->ReBegin(true, false);
	IMAGE->PrintText("로딩중", Vec3(WINSIZEX / 2, WINSIZEY / 2, 0), 100, D3DCOLOR_XRGB(255, 255, 255), true);
	char str[128] = "";
	sprintf(str, "%.0f%%", (float)((float)((float)100 / MaxOBJLoad) * NowOBJLoad));
	IMAGE->PrintText(str, Vec3(WINSIZEX / 2, WINSIZEY / 2 + 100, 0), 100, D3DCOLOR_XRGB(255, 255, 255), true);
	IMAGE->ReBegin(false, false);
}

void cLoadScene::Release()
{
}

