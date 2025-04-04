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
	MissileType playerMissile1;
	playerMissile1.key = TEXT(PLAYER_BULLET1_PATH);
	playerMissile1.missileKind = MissileKind::Basic;
	playerMissile1.missileSpeed = 400.0f;
	playerMissile1.shootRate = 0.15f;
	playerMissile1.damage = 1;
	playerMissile1.size = {-11, 3, 11, 23};
	playerMissile1.reloadRate = 0.0f;
	playerMissile1.missileAmount = 10;
	playerMissile1.upgrade = TEXT(PLAYER_BULLET2_PATH);
	playerMissile1.maxFrameX = 4;
	missileDict.insert(make_pair(TEXT(PLAYER_BULLET1_PATH), playerMissile1));
	
	MissileType playerMissile2;
	playerMissile2.key = TEXT(PLAYER_BULLET2_PATH);
	playerMissile2.missileKind = MissileKind::Basic;
	playerMissile2.missileSpeed = 400.0f;
	playerMissile2.shootRate = 0.15f;
	playerMissile2.damage = 2;
	playerMissile2.size = { -11, -1, 11, 37 };
	playerMissile2.reloadRate = 0.0f;
	playerMissile2.missileAmount = 10;
	playerMissile2.upgrade = TEXT(PLAYER_BULLET3_PATH);
	playerMissile2.maxFrameX = 4;
	missileDict.insert(make_pair(TEXT(PLAYER_BULLET2_PATH), playerMissile2));
	
	MissileType playerMissile3;
	playerMissile3.key = TEXT(PLAYER_BULLET3_PATH);
	playerMissile3.missileKind = MissileKind::Basic;
	playerMissile3.missileSpeed = 400.0f;
	playerMissile3.shootRate = 0.15f;
	playerMissile3.damage = 3;
	playerMissile3.size = { -17, 9, 17, 33 };
	playerMissile3.reloadRate = 0.0f;
	playerMissile3.missileAmount = 10;
	playerMissile3.upgrade = TEXT(PLAYER_BULLET4_PATH);
	playerMissile3.maxFrameX = 4;
	missileDict.insert(make_pair(TEXT(PLAYER_BULLET3_PATH), playerMissile3));
	
	MissileType playerMissile4;
	playerMissile4.key = TEXT(PLAYER_BULLET4_PATH);
	playerMissile4.missileKind = MissileKind::Basic;
	playerMissile4.missileSpeed = 400.0f;
	playerMissile4.shootRate = 0.15f;
	playerMissile4.damage = 4;
	playerMissile4.size = { -21, -35, 21, -4 };
	playerMissile4.reloadRate = 0.0f;
	playerMissile4.missileAmount = 10;
	playerMissile4.upgrade = nullptr;
	playerMissile4.maxFrameX = 4;
	missileDict.insert(make_pair(TEXT(PLAYER_BULLET4_PATH), playerMissile4));

	MissileType targettingMissile;
	targettingMissile.key = TEXT(TARGETTING_BULLET_PATH);
	targettingMissile.missileKind = MissileKind::Targetting;
	targettingMissile.missileSpeed = 200.0f;
	targettingMissile.shootRate = 0.3f;
	targettingMissile.damage = 1;
	targettingMissile.size = { -6, -6, 6, 6 };
	targettingMissile.reloadRate = 3.0f;
	targettingMissile.missileAmount = 10;
	targettingMissile.upgrade = nullptr;
	targettingMissile.maxFrameX = 0;
	missileDict.insert(make_pair(TEXT(TARGETTING_BULLET_PATH), targettingMissile));

	MissileType aroundMissile;
	aroundMissile.key = TEXT(AROUND_BULLET_PATH);
	aroundMissile.missileKind = MissileKind::Around;
	aroundMissile.missileSpeed = 200.0f;
	aroundMissile.shootRate = 0.1f;
	aroundMissile.damage = 1;
	aroundMissile.size = { -12, -12, 12, 12 };
	aroundMissile.reloadRate = 5.0f;
	aroundMissile.missileAmount = 100;
	aroundMissile.upgrade = nullptr;
	aroundMissile.maxFrameX = 0;
	missileDict.insert(make_pair(TEXT(AROUND_BULLET_PATH), aroundMissile));

	MissileType randomMissile;
	randomMissile.key = TEXT(RANDOM_BULLET_PATH);
	randomMissile.missileKind = MissileKind::Random;
	randomMissile.missileSpeed = 100.0f;
	randomMissile.shootRate = 0.5f;
	randomMissile.damage = 2;
	randomMissile.size = { -10, -10, 10, 10 };
	randomMissile.reloadRate = 3.0f;
	randomMissile.missileAmount = 20;
	randomMissile.upgrade = nullptr;
	randomMissile.maxFrameX = 7;
	missileDict.insert(make_pair(TEXT(RANDOM_BULLET_PATH), randomMissile));

	MissileType rapidFireMissile;
	rapidFireMissile.key = TEXT(RAPIDFIRE_BULLET_PATH);
	rapidFireMissile.missileKind = MissileKind::RapidFire;
	rapidFireMissile.missileSpeed = 400.0f;
	rapidFireMissile.shootRate = 0.05f;
	rapidFireMissile.damage = 1;
	rapidFireMissile.size = { -10, -10, 10, 10 };
	rapidFireMissile.reloadRate = 3.0f;
	rapidFireMissile.missileAmount = 10;
	rapidFireMissile.upgrade = nullptr;
	rapidFireMissile.maxFrameX = 0;
	missileDict.insert(make_pair(TEXT(RAPIDFIRE_BULLET_PATH), rapidFireMissile));
}
void MissileManager::Init()
{
	missileCount = 0;
	isReloading = false;
	elapsedTime = 0.0f;
	missileImage = nullptr;
	missileSpeed = 0.0f;
	shootRate = 0.1f;
	missileDamage = 1;
	size = { 0,0,0,0 };
	reloadRate = 0.0f;
	missileAmount = 0;
	missileKind = MissileKind::None;
	type = Type::NONE;
	nextMissile = nullptr;
	maxFrameX = 0;

	if (missileDict.empty())
		FillDict();
	
	if (!missiles.empty())
	{
		for (auto& missile : missiles)
			missile->Init();
	}
}

void MissileManager::Init(const wchar_t* key, Type type)
{
	missileCount = 0;
	elapsedTime = 0.0f;
	isReloading = false;
	reloadTime = 0.0f;
	maxFrameX = 0;

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
		size = (*var).second.size;
		nextMissile = var->second.upgrade;
		maxFrameX = var->second.maxFrameX;
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
			missiles[i]->Init(dir, missileSpeed, missileImage, size, missileDamage, maxFrameX);
			MissileDirSetting(pos);
			missiles[i]->Shoot(pos, dir);
			if (++missileCount >= missileAmount)
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
	FPOINT dest = PlayerManager::GetInstance()->GetPlayer1Pos();
	if (GetDistance(dest, pos) >
		GetDistance(PlayerManager::GetInstance()->GetPlayer2Pos(), pos))
		dest = PlayerManager::GetInstance()->GetPlayer2Pos();

	switch (missileKind)
	{
	case MissileKind::None:
	case MissileKind::Basic:
	case MissileKind::RapidFire:
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
	case MissileKind::Random:
	{
		float randomAngle = static_cast<float>(rand() % 360);
		dir.x = cos(DEG_TO_RAD(randomAngle));
		dir.y = sin(DEG_TO_RAD(randomAngle));
	}
	break;
	default:
		break;
	}
}

void MissileManager::Upgrade(void)
{
	if (nextMissile)
		Init(nextMissile, type);
}
