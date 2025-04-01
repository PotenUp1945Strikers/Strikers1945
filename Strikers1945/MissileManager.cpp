#include "MissileManager.h"
#include "Missile.h"
#include "ImageManager.h"
#include "CollisionManager.h"
#include "TimerManager.h"
void MissileManager::Init()
{
	elapsedTime = 0.0f;
	type = Type::NONE;
	missileImage = nullptr;
	missileSpeed = 0.0f;
	shootRate = 0.1f;
	missileDamage = 1;
	size = { 0,0,0,0 };

	missiles.resize(30);
	for (int i = 0; i < missiles.size(); i++)
	{
		Missile* missile = new Missile();
		missile->Init();
		missiles.push_back(missile);
		CollisionManager::GetInstance()->AddCollider(missile);
	}
}

void MissileManager::Init(const wchar_t* key, Type type)
{
	if (missiles.empty())
	{
		missiles.resize(30);
		for (int i = 0; i < 30; ++i)
		{
			missiles[i] = new Missile();
			missiles[i]->Init(type);
			CollisionManager::GetInstance()->AddCollider(missiles[i]);
		}
	}

	if (!missiles.empty())
	{
		missileImage = ImageManager::GetInstance()->GetImage(key);
		this->type = type;

		missileSpeed = 400.0f;
		shootRate = 0.1f;
		if (type == Type::PLAYER_BULLET) dir = { 0,-1 };
		else if (type == Type::ENEMY_BULLET) dir = { 0,1 };
		size = { -missileImage->GetWidth() / 2, -missileImage->GetHeight() / 2,
			missileImage->GetWidth() / 2, missileImage->GetHeight() / 2 };
		for (auto& missile : missiles)
			missile->Init(dir, missileSpeed, missileImage, size);
	}
}

void MissileManager::Update()
{
	elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
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
		if (missile->GetActive() == false || missile->GetRender() == false) continue;
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

void MissileManager::Shoot(FPOINT pos)
{
	if (elapsedTime < shootRate)
		return;
	for (int i = 0; i < missiles.size(); i++)
	{
		if (missiles[i]->GetActive() == false)
		{
			missiles[i]->Shoot(pos);
			break;
		}
	}
	elapsedTime = 0;
}
