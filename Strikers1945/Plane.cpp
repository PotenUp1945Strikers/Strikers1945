#include "Plane.h"
#include "CommonFunction.h"

map<const wchar_t*, PlaneType> Plane::dict;


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

void Plane::Init(void)
{
	if (dict.empty())
		FillDict();
	if (!launcher)
	{
		launcher = new MissileManager;
		launcher->Init();
	}
	path = nullptr;
	currPath = 0;
	goal = { 0, };
	active = false;
	render = false;
	state = GameObjectStates::Wait;
}


void Plane::Init(const wchar_t* key, float startPos, Type type)
{
	if (dict.empty())
		FillDict();

	state = GameObjectStates::Wait;
	active = false;
	render = false;
	path = nullptr;
	currPath = 0;
	goal = { 0, };
	if (!launcher)
		launcher = new MissileManager;

	auto var = dict.find(key);
	if (var != dict.end())
	{
		this->type = type;
		*this = var->second;
		location = startPos;

		switch (type) {
		case Type::PLAYER:
			launcher->Init(var->second.missileType, Type::PLAYER_BULLET);
			break;
		case Type::ENEMY:
			launcher->Init(var->second.missileType, Type::ENEMY_BULLET);
			break;
		}
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

void Plane::Render(HDC hdc)
{
	if (image && render)
		image->FrameRender(hdc, pos.x, pos.y, 0, 0);
	if (launcher)
		launcher->Render(hdc);
}

void Plane::Update(void)
{
	switch (type) {
	case Type::PLAYER:
		UpdatePlayer();
		break;
	case Type::ENEMY:
		UpdateEnemy();
		break;
	}
	
	if (launcher)
		launcher->Update();
}

void Plane::UpdatePlayer(void)
{
	switch (state) {
	case GameObjectStates::Wait:
		UpdateWait();
		break;
	case GameObjectStates::Born:
		UpdatePlayerBorn();
		break;
	case GameObjectStates::Alive:
		UpdatePlayerAlive();
		break;
	}
}

void Plane::UpdateEnemy(void)
{
	switch (state) {
	case GameObjectStates::Wait:
		UpdateWait();
		break;
	case GameObjectStates::Born:
		UpdateEnemyBorn();
		break;
	case GameObjectStates::Alive:
		UpdateEnemyAlive();
		break;
	}
}

void Plane::UpdateWait(void)
{
	if (BackgroundManager::GetInstance()->GetCurrPosY() >= location)
	{
		render = true;
		state = GameObjectStates::Born;
	}
}

void Plane::UpdatePlayerBorn(void)
{
	MoveAlongPath();
	if (!InOfWindow())
	{
		active = true;
		state = GameObjectStates::Alive;
	}
}

void Plane::UpdatePlayerAlive(void)
{
	float deltatime = TimerManager::GetInstance()->GetDeltaTime();
	FPOINT oldPos = pos;
	pos.x += speed * dir.x * deltatime;
	pos.y += speed * dir.y * deltatime;

	if (InOfWindow())
		pos = oldPos;
}

void Plane::UpdateEnemyBorn(void)
{
	MoveAlongPath();
	if (!OutOfWindow())
	{
		active = true;
		state = GameObjectStates::Alive;
	}
}

void Plane::UpdateEnemyAlive(void)
{
	MoveAlongPath();
	Shoot();
	if (OutOfWindow())
	{
		active = false;
		render = false;
		state = GameObjectStates::Die;
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
	this->dir = GetUnitVector({ 0, 0 }, dir);
}

void Plane::MoveAlongPath()
{
	float deltatime = TimerManager::GetInstance()->GetDeltaTime();

	if (path && path->size() < currPath)
	{
		if (IsAlmostEqual(goal.x, pos.x) &&
			IsAlmostEqual(goal.y, pos.y))
			SetGoal();
		else
			dir = GetUnitVector(pos, goal);
	}
	else
	{
		FPOINT tmpDir = { 0, };
		if (pos.x + size.left < 0)
			tmpDir.x += 1;
		else if (pos.x + size.right > WINSIZE_X)
			tmpDir.x += -1;
		if (pos.y + size.top < 0)
			tmpDir.y += 1;
		else if (pos.y + size.bottom > WINSIZE_Y)
			tmpDir.y += -1;
		dir = GetUnitVector({ 0,0 }, tmpDir);
	}

	pos.x += speed * dir.x * deltatime;
	pos.y += speed * dir.y * deltatime;

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

void Plane::SetPath(vector<FPOINT>* path)
{
	if (path)
	{
		this->path = path;
		currPath = 0;
		SetGoal();
	}
}

void Plane::SetGoal(void)
{
	if (this->path->size() > currPath)
	{
		FPOINT tmp = this->path->at(currPath++);
		goal = { pos.x + tmp.x, pos.y + tmp.y };
	}
	else
		goal = { 0, 0 };
}

Plane& Plane::operator=(const PlaneType& target)
{
	image = ImageManager::GetInstance()->GetImage(target.key);
	size = target.size;
	health = target.health;
	speed = target.speed;
	return *this;
}

bool Plane::OutOfWindow(void)
{
	int halfWidth = image->GetWidth() / 2;
	int halfHeight = image->GetHeight() / 2;

	if (pos.x - halfWidth < 0 || pos.x + halfWidth > WINSIZE_X ||
		pos.y - halfHeight < 0 || pos.y + halfHeight > WINSIZE_Y)
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
