#include "EnemyManager.h"
#include "BackgroundManager.h"
#include "CollisionManager.h"
#include "Plane.h"

void EnemyManager::Init()
{
	// TODO : scripts init
	// Planes Init (enemy)

	scriptIndex = 0;
	planes.push_back(new Plane);
	planes.back()->Init(TEXT(ENEMY1_PATH), 300, Type::ENEMY);
	planes.back()->SetPos({ WINSIZE_X / 2, WINSIZE_Y / 3 });
	CollisionManager::GetInstance()->AddCollider(planes.back());
}

void EnemyManager::Release()
{
	//scripts.clear();
	//scripts.shrink_to_fit();
	planes.clear();
	planes.shrink_to_fit();
}

void EnemyManager::Update()
{
	// depends on struct
	//if (BackgroundManager::GetInstance()->GetCurrPosY() >= scripts[scriptIndex].second)
	//{
	//	if (DeployEnemy()) scriptIndex += 1;
	//}


	for (auto i : planes)
	{
		i->Update();
	}

}

void EnemyManager::Render(HDC hdc)
{

	for (auto i : planes)
	{
		if (i->GetRender())
		{
			i->Render(hdc);
		}
	}

}

bool EnemyManager::DeployEnemy()
{
	//TODO : DeployEnemy logic

	//switch (scripts[scriptIndex].first) // depends on struct
	//{
	//	// Init and addEnemy
	//	case NormalEnemy:
	//		
	//		return true;
	//		break;
	//	case HeliEnemy:

	//		return true;
	//		break;
	//	case BossEnemy:

	//		return true;
	//		break;
	//}

	return false;

}
