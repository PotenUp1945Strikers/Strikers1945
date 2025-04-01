#include "Plane.h"

void Plane::Init(void)
{
	if (dict.empty())
		FillDict();
	if (!launcher)
	{
		launcher = new MissileManager;
		launcher->Init();
	}
}

void Plane::Release(void)
{
	if (launcher)
	{
		launcher->Release();
		delete launcher;
		launcher = nullptr;
	}
}

void Plane::Update(void)
{
	float deltatime = TimerManager::GetInstance()->GetDeltaTime();
	FPOINT oldPos = pos;
	pos.x += speed * dir.x * deltatime;
	pos.y += speed * dir.y * deltatime;

	if (type == Type::PLAYER && InOfWindow())
		pos = oldPos;
	else if (type == Type::ENEMY && OutOfWindow())
		active = false;

	if (launcher)
		launcher->Update();
}

void Plane::Render(HDC hdc)
{
	if (image)
		image->FrameRender(hdc, pos.x, pos.y, 0, 0);
	if (launcher)
		launcher->Render(hdc);
}

void Plane::FillDict(void)
{
	PlaneType player;
	player.key = TEXT(PLAYER_PATH);
	player.bodySize = RECT{ -5, -24, 5, 23 };
	player.health = 1;
	player.missileType = TEXT("Missile");
	player.speed = 120;
	player.wingSize = RECT{-16, -4, 4, 16 };
	player.wingPos = {0, 2};
	dict.insert(make_pair(TEXT(PLAYER_PATH), player));

	PlaneType enemy1;
	enemy1.key = TEXT(ENEMY1_PATH);
	enemy1.bodySize = RECT{ -2, -16, 2, 16 };
	enemy1.health = 1;
	enemy1.missileType = TEXT("Missile");
	enemy1.speed = 90;
	enemy1.wingSize = RECT{ -20, -2, 20, 2 };
	enemy1.wingPos = { 0, -1 };
	dict.insert(make_pair(TEXT(ENEMY1_PATH), enemy1));
}

void Plane::Init(const wchar_t* key)
{
	if (dict.empty())
		FillDict();

	auto var = dict.find(key);
	if (var != dict.end())
		*this = var->second;
}

Colider Plane::GetColider(void)
{
	RECT posBodySize = { pos.x + bodySize.left, pos.y + bodySize.top,
		pos.x + bodySize.right, pos.y + bodySize.bottom };
	RECT posWingSize = { pos.x + wingPos.x + bodySize.left, pos.y + wingPos.y + bodySize.top,
	pos.x + wingPos.x + bodySize.right, pos.y + wingPos.y + bodySize.bottom };
	return Colider{ posBodySize, posWingSize };
}

void Plane::Shoot(void)
{
	if (launcher)
	{
		launcher->Shoot(pos);
	}
}

void Plane::UpgradeMissile()
{
	if (launcher)
	{
		launcher->Upgrade();
	}
}

void Plane::Move(FPOINT dir)
{
	float length = sqrtf(pow(dir.x, 2) + pow(dir.y, 2));
	this->dir = { dir.x * length, dir.y * length };
}

Plane& Plane::operator=(const PlaneType& target)
{
	image = ImageManager::GetInstance()->GetImage(target.key);
	bodySize = target.bodySize;
	wingSize = target.wingSize;
	wingPos = target.wingPos;
	health = target.health;
	speed = target.speed;
	if (!launcher)
		launcher = new MissileManager;
	launcher->Init(target.missileType);
}

bool Plane::OutOfWindow(void)
{
	if (pos.x + wingSize.right < 0 || pos.x + wingSize.left > WINSIZE_X ||
		pos.y + wingSize.bottom < 0 || pos.y + wingSize.top > WINSIZE_Y)
		return true;
	return false;
}

bool Plane::InOfWindow(void)
{
	if (pos.x + wingSize.left < 0 || pos.x + wingSize.right > WINSIZE_X ||
		pos.y + wingSize.top < 0 || pos.y + wingSize.bottom > WINSIZE_Y )
		return true;
	return false;
}
