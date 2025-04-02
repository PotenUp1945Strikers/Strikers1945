#include "MissileManager.h"
#include "Missile.h"
#include "ImageManager.h"
#include "CollisionManager.h"
#include "TimerManager.h"

map<const wchar_t*, MissileType> MissileManager::missileDict;

void MissileManager::FillDict()
{
	MissileType playerNormalMissile;
	playerNormalMissile.key = TEXT(NORMAL_BULLET_PATH);
	playerNormalMissile.missileSpeed = 400.0f;
	playerNormalMissile.shootRate = 1.0f;
	playerNormalMissile.damage = 1;
	playerNormalMissile.reloadRate = 1;
	playerNormalMissile.missileAmount = 30;
	// playerNormalMissile.size = {};
	// playerNormalMissile.upgrade = TEXT("");
	missileDict.insert(make_pair(TEXT(NORMAL_BULLET_PATH), playerNormalMissile));

	MissileType enemyNormalMissile;
	enemyNormalMissile.key = TEXT(NORMAL_BULLET_PATH);
	enemyNormalMissile.missileSpeed = 400.0f;
	enemyNormalMissile.shootRate = 0.1;
	enemyNormalMissile.damage = 1;
	enemyNormalMissile.reloadRate = 1;
	enemyNormalMissile.missileAmount = 10;
	// enemyNormalMissile.size = {};
	// enemyNormalMissile.upgrade = TEXT("");
	missileDict.insert(make_pair(TEXT(NORMAL_BULLET_PATH), enemyNormalMissile));


}
void MissileManager::Init()
{
	missileCount = 0;
	isReloading = false;
	elapsedTime = 0.0f;
	type = Type::NONE;
	missileImage = nullptr;
	missileSpeed = 0.0f;
	shootRate = 0.1f;
	missileDamage = 1;
	size = { 0,0,0,0 };
	reloadRate = 0.0f;
	missileAmount = 0;
	missiles.resize(MAX_MISSILE);
	if (missileDict.empty())
		FillDict();
	for (int i = 0; i < missiles.size(); i++)
	{
		Missile* missile = new Missile();
		missile->Init();
		missiles[i] = missile;
		CollisionManager::GetInstance()->AddCollider(missile);
	}
}

void MissileManager::Init(const wchar_t* key, Type type)
{
	missileCount = 0;
	elapsedTime = 0.0f;
	isReloading = false;
	reloadTime = 0.0f;
	if (missileDict.empty())
		FillDict();

	if (missiles.empty())
	{
		missiles.resize(MAX_MISSILE);
		for (int i = 0; i < MAX_MISSILE; ++i)
		{
			missiles[i] = new Missile();
			missiles[i]->Init(type);
			CollisionManager::GetInstance()->AddCollider(missiles[i]);
		}
	}

	auto var = missileDict.find(key);
	if (var != missileDict.end())
	{
		missileImage = ImageManager::GetInstance()->GetImage(key);
		this->type = type;
		missileSpeed = (*var).second.missileSpeed;
		shootRate = (*var).second.shootRate;
		missileDamage = (*var).second.damage;
		reloadRate = (*var).second.reloadRate;
		missileAmount = (*var).second.missileAmount;
		// size = (*var).second.size;
		size = { -missileImage->GetWidth() / 2, -missileImage->GetHeight() / 2,
			missileImage->GetWidth() / 2, missileImage->GetHeight() / 2 };

		if (type == Type::PLAYER_BULLET)
			dir = { 0,-1 };
		else if (type == Type::ENEMY_BULLET)
			dir = { 0,1 };

		for (auto& missile : missiles)
			missile->Init(dir, missileSpeed, missileImage, size);
	}
}

void MissileManager::Update()
{
	elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (isReloading)
	{
		reloadTime += TimerManager::GetInstance()->GetDeltaTime();
		if (reloadTime >= reloadRate) {
			reloadTime = 0;
			isReloading = false;
		}
	}
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
	if (elapsedTime < shootRate || isReloading)
		return;
	for (int i = 0; i < missiles.size(); i++)
	{
		if (missiles[i]->GetActive() == false)
		{
			missileCount++;
			missiles[i]->Shoot(pos);
			if (missileCount >= missileAmount)
			{
				isReloading = true;
				missileCount = 0;
			}
			break;
		}
	}
	elapsedTime = 0;
}
