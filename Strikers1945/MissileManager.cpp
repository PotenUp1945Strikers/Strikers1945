#include "MissileManager.h"
#include "Missile.h"
#include "ImageManager.h"
#include "CollisionManager.h"

void MissileManager::Init()
{
	bulletImage = ImageManager::GetInstance()->GetImage(TEXT(NORMAL_BULLET_PATH));
	bulletSpeed = 0.0f;
	shootRate = 0.0f;
	bulletDamage = 1;
	size = { 0,0,0,0 };

	missiles = {};
}

void MissileManager::Update()
{
	for (auto missile : missiles)
	{
		if (missile->GetActive() == false) continue;
		missile->Update();
	}
}

void MissileManager::Render(HDC hdc)
{
	for (auto missile : missiles)
	{
		if (missile->GetActive() == false && missile->GetRender()) continue;
		missile->Render(hdc);
	}
}

void MissileManager::Release()
{
	for (auto missile : missiles)
	{
		if (missile)
		{
			missile->Release();
			delete missile;
			missile = nullptr;
		}
	}
}

void MissileManager::Shoot(FPOINT vec)
{
	Missile* missile = new Missile();
	missile->Init();
	missiles.push_back(missile);
	CollisionManager::GetInstance()->AddCollider(missile);
}
