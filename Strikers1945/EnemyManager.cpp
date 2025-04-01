#include "EnemyManager.h"
#include "BackgroundManager.h"

void EnemyManager::Init()
{
	// TODO : scripts init
	// Planes Init (enemy)

	scriptIndex = 0;


}

void EnemyManager::Release()
{
	scripts.clear();
	scripts.shrink_to_fit();
	planes.clear();
	planes.shrink_to_fit();
}

void EnemyManager::Update()
{
	// depends on struct
	if (BackgroundManager::GetInstance()->GetCurrPosY() >= scripts[scriptIndex].second)
	{
		DeployEnemy();
	}


	for (auto i : planes)
	{
		if (i->GetActive() && i->GetRender())
		{
			i->Update(hdc);
		}
	}

}

void EnemyManager::Render(HDC hdc)
{

	for (auto i : planes)
	{
		if (i->GetActive() && i->GetRender())
		{
			i->Render(hdc);
		}
	}

}

bool EnemyManager::DeployEnemy()
{
	//TODO : DeployEnemy logic

	switch (scripts[scriptIndex].first) // depends on struct
	{
		// Init and addEnemy
		case NormalEnemy:
			

			break;
		case HeliEnemy:

			break;
		case BossEnemy:

			break;
	}

}
