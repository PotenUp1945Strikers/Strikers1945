#include "MissileManager.h"
#include "CommonFunction.h"
#include "Missile.h"
#include "ImageManager.h"
#include "CollisionManager.h"
#include "TimerManager.h"
#include "Plane.h"
#include "PlayerManager.h"

map<const wchar_t*, MissileType> MissileManager::missileDict;

void MissileManager::FillDict()
{
	MissileType normalMissile;
	normalMissile.key = TEXT(NORMAL_BULLET_PATH);
	normalMissile.missileKind = MissileKind::Basic;
	normalMissile.missileSpeed = 400.0f;
	normalMissile.shootRate = 0.5f;
	normalMissile.damage = 1;
	normalMissile.reloadRate = 3.0f;
	normalMissile.missileAmount = 10;
	missileDict.insert(make_pair(TEXT(NORMAL_BULLET_PATH), normalMissile));


	MissileType targettingMissile;
	targettingMissile.key = TEXT(TARGETTING_BULLET_PATH);
	targettingMissile.missileKind = MissileKind::Targetting;
	targettingMissile.missileSpeed = 200.0f;
	targettingMissile.shootRate = 1.0f;
	targettingMissile.damage = 1;
	targettingMissile.reloadRate = 3.0f;
	targettingMissile.missileAmount = 10;
	missileDict.insert(make_pair(TEXT(TARGETTING_BULLET_PATH), targettingMissile));

	MissileType aroundMissile;
	aroundMissile.key = TEXT(AROUND_BULLET_PATH);
	aroundMissile.missileKind = MissileKind::Around;
	aroundMissile.missileSpeed = 200.0f;
	aroundMissile.shootRate = 0.1f;
	aroundMissile.damage = 1;
	aroundMissile.reloadRate = 5.0f;
	aroundMissile.missileAmount = 100;
	missileDict.insert(make_pair(TEXT(AROUND_BULLET_PATH), aroundMissile));
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
	missileKind = MissileKind::None;
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
		missileKind = (*var).second.missileKind;

		// size = (*var).second.size;
		size = { -missileImage->GetWidth() / 2, -missileImage->GetHeight() / 2,
			missileImage->GetWidth() / 2, missileImage->GetHeight() / 2 };

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
			reloadTime = 0.0f;
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
			MissileDirSetting(pos);
			missiles[i]->Shoot(pos, dir);
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

void MissileManager::MissileDirSetting(FPOINT pos)
{
	static float angle = 0.0f;
	static bool isAngleUp = true;
	FPOINT dest = { 100,100 };// = PlayerManager::GetInstance()->GetPlayer1()->GetPos();
	switch (missileKind)
	{
	case MissileKind::None:
	case MissileKind::Basic:
		if (type == Type::PLAYER_BULLET)
			dir = { 0,-1 };
		else if (type == Type::ENEMY_BULLET)
			dir = { 0,1 };
		break;
	case MissileKind::Targetting:
		dir = GetUnitVector(pos, dest);
		break;
	case MissileKind::Around:
		dir.x = cos(DEG_TO_RAD(angle));
		dir.y = sin(DEG_TO_RAD(angle));
		if (isAngleUp)
			angle += 10.0f;
		else
			angle -= 10.0f;
		if (angle >= 180.0f) isAngleUp = false;
		if (angle <= 0.0f) isAngleUp = true;
		break;
	default:
		break;
	}
}