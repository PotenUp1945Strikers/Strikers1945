#include "Plane.h"

map<const wchar_t*, PlaneType> Plane::dict;

void Plane::Init(void)
{
	if (dict.empty())
		FillDict();
	if (!launcher)
	{
		launcher = new MissileManager;
		launcher->Init();
	}
	active = false;
	render = false;
	state = GameObjectStates::Wait;
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
	switch (state) {
	case GameObjectStates::Wait:
		UpdateWait();
		break;
	case GameObjectStates::Born:
		UpdateBorn();
		break;
	case GameObjectStates::Alive:
		UpdateAlive();
		break;
	}

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

void Plane::UpdateWait(void)
{
	if (BackgroundManager::GetInstance()->GetCurrPosY() >= location)
	{
		render = true;
		state = GameObjectStates::Born;
	}
}

void Plane::UpdateBorn(void)
{
	float deltatime = TimerManager::GetInstance()->GetDeltaTime();
	pos.x += speed * dir.x * deltatime;
	pos.y += speed * dir.y * deltatime;

	if ((type == Type::PLAYER && !InOfWindow()) ||
		(type == Type::ENEMY && !OutOfWindow()))
	{
		active = true;
		state = GameObjectStates::Alive;
	}
}

void Plane::UpdateAlive(void)
{

	float deltatime = TimerManager::GetInstance()->GetDeltaTime();
	FPOINT oldPos = pos;
	pos.x += speed * dir.x * deltatime;
	pos.y += speed * dir.y * deltatime;

	if (type == Type::PLAYER && InOfWindow())
		pos = oldPos;
	else if (type == Type::ENEMY && OutOfWindow())
	{
		active = false;
		render = false;
		state = GameObjectStates::Die;
	}
}

void Plane::FillDict(void)
{
	PlaneType player;
	player.key = TEXT(PLAYER_PATH);
	player.size = RECT{ -4, -20, 4, 20 };
	player.health = 1;
	player.missileType = TEXT(NORMAL_BULLET_PATH);
	player.speed = 180;
	dict.insert(make_pair(TEXT(PLAYER_PATH), player));

	PlaneType enemy1;
	enemy1.key = TEXT(ENEMY1_PATH);
	enemy1.size = RECT{ -2, -16, 2, 16 };
	enemy1.health = 1;
	enemy1.missileType = TEXT(NORMAL_BULLET_PATH);
	enemy1.speed = 150;
	dict.insert(make_pair(TEXT(ENEMY1_PATH), enemy1));
}

void Plane::Init(const wchar_t* key, float startPos, Type type)
{
	if (dict.empty())
		FillDict();

	auto var = dict.find(key);
	if (var != dict.end())
	{
		this->type = type;
		*this = var->second;
		if (!launcher)
			launcher = new MissileManager;
		location = startPos;
		if (type == Type::PLAYER)
			launcher->Init(var->second.missileType, Type::PLAYER_BULLET);
		else if (type == Type::ENEMY)
			launcher->Init(var->second.missileType, Type::ENEMY_BULLET);
	}
}

void Plane::Shoot(void)
{
	FPOINT missilePos = pos;
	if (type == Type::PLAYER)
		missilePos.y += size.top;
	else if (type == Type::ENEMY)
		missilePos.y += size.bottom;
	if (launcher)
		launcher->Shoot(missilePos);
}

void Plane::UpgradeMissile()
{
	//if (launcher)
	//	launcher->Upgrade();
}

void Plane::Move(FPOINT dir)
{
	float length = sqrtf(pow(dir.x, 2) + pow(dir.y, 2));
	if (length)
		this->dir = { dir.x / length, dir.y / length };
	else
		this->dir = { 0, };
}

void Plane::OnDamage(void)
{
	--health;
	if (health <= 0)
	{
		active = false;
		render = false;
		state = GameObjectStates::Die;
	}
}

Plane& Plane::operator=(const PlaneType& target)
{
	image = ImageManager::GetInstance()->GetImage(target.key);
	size = target.size;
	health = target.health;
	speed = target.speed;
	state = GameObjectStates::Wait;
	active = false;
	render = false;
	return *this;
}

bool Plane::OutOfWindow(void)
{
	if (pos.x + size.right < 0 || pos.x + size.left > WINSIZE_X ||
		pos.y + size.bottom < 0 || pos.y + size.top > WINSIZE_Y)
		return true;
	return false;
}

bool Plane::InOfWindow(void)
{
	if (pos.x + size.left < 0 || pos.x + size.right > WINSIZE_X ||
		pos.y + size.top < 0 || pos.y + size.bottom > WINSIZE_Y )
		return true;
	return false;
}
