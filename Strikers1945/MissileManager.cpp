#include "MissileManager.h"
#include "Missile.h"
#include "ImageManager.h"
#include "CollisionManager.h"

void MissileManager::Init()
{
	type = Type::NONE;
	bulletImage = nullptr;
	bulletSpeed = 0.0f;
	shootRate = 1.0f;
	bulletDamage = 1;
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
	bulletImage = ImageManager::GetInstance()->GetImage(key);
	this->type = type;

	bulletSpeed = 0.0f;
	shootRate = 1.0f;
	if (type == Type::PLAYER_BULLET) dir = { 0,-1 };
	else if (type == Type::ENEMY_BULLET) dir = { 0,1 };
	size = { bulletImage->GetWidth() / 2, bulletImage->GetHeight() / 2, 
		bulletImage->GetWidth() / 2, bulletImage->GetHeight() / 2 };

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
	for (int i = 0; i < missiles.size(); i++)
	{
		if (missiles[i]->GetActive() == false)
		{
			missiles[i]->Init(type, dir, pos, bulletSpeed, bulletImage);
			return;
		}
	}
}
