#include "Plane.h"
#include "CommonFunction.h"

map<const wchar_t*, PlaneType> Plane::dict;


void Plane::FillDict(void)
{
	PlaneType player;
	player.key = TEXT(PLAYER_PATH);
	player.size = RECT{ -4, -20, 4, 20 };
	player.health = 1;
	player.missilePos = {0, -20};
	player.centerPos = { 16, 23 };
	player.missileType = TEXT(NORMAL_BULLET_PATH);
	player.speed = 180;
	dict.insert(make_pair(TEXT(PLAYER_PATH), player));

	PlaneType enemy1;
	enemy1.key = TEXT(ENEMY1_PATH);
	enemy1.size = RECT{ -2, -16, 2, 16 };
	enemy1.health = 1;
	enemy1.missilePos = { 0, -16 };
	enemy1.centerPos = { 18, 16 };
	enemy1.missileType = TEXT(NORMAL_BULLET_PATH);
	enemy1.speed = 150;
	dict.insert(make_pair(TEXT(ENEMY1_PATH), enemy1));
}

void Plane::Init(void)
{
	if (dict.empty())
		FillDict();

	if (!launcher)
		launcher = new MissileManager;
	state = GameObjectStates::Die;
	path = nullptr;
	active = false;
	render = false;
	currPath = 0;
	goal = { 0, };
}


void Plane::Init(const wchar_t* key, float startPos, Type type)
{
	if (dict.empty())
		FillDict();

	state = GameObjectStates::Wait;
	path = nullptr;
	active = false;
	render = false;
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
			absTime = INVINCIBILITY_TIME;
			break;
		case Type::ENEMY:
			launcher->Init(var->second.missileType, Type::ENEMY_BULLET);
			absTime = 0;
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
		image->FrameRender(hdc, centerPos, pos.x, pos.y, 0, 0);
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
	if (MoveAlongPath() && !InOfWindow())
		state = GameObjectStates::Alive;
}

void Plane::UpdatePlayerAlive(void)
{
	float deltatime = TimerManager::GetInstance()->GetDeltaTime();
	if (!active)
	{
		absTime -= deltatime;
		if (absTime <= 0)
			active = true;
	}

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
	if (active && launcher)
		launcher->Shoot({ pos.x + missilePos.x, pos.y + missilePos.y });
}

void Plane::UpgradeMissile()
{
	//if (launcher)
	//	launcher->Upgrade();
}

void Plane::Move(FPOINT dir)
{
	if (state == GameObjectStates::Alive)
		this->dir = GetUnitVector({ 0, 0 }, dir);
}

bool Plane::MoveAlongPath()
{
	switch (this->pathType)
	{
	case TaskType::NONE:
		if (type == Type::PLAYER)
			return true;
		else
			pos.y += speed * TimerManager::GetInstance()->GetDeltaTime();
		break;
	case TaskType::STOP:
		MoveAlongPathStop();
		break;
	case TaskType::MOVE:
		MoveAlongPathMove();
		break;
	case TaskType::MOVEAROUND:
		MoveAlongPathMoveAround();
		break;
	case TaskType::MOVECURVE:
		MoveAlongPathMoveCurve();
		break;
	}
	return false;
}

void Plane::MoveAlongPathStop()
{
	float deltatime = TimerManager::GetInstance()->GetDeltaTime();

	if (taskTime > 0)
		taskTime -= deltatime;
	else
		SetGoal();
}

void Plane::MoveAlongPathMove()
{
	float deltatime = TimerManager::GetInstance()->GetDeltaTime();

	if (IsAlmostEqual(goal.x, pos.x, speed * dir.x * deltatime) &&
		IsAlmostEqual(goal.y, pos.y, speed * dir.y * deltatime))
	{
		pos = goal;
		return SetGoal();
	}

	dir = GetUnitVector(pos, goal);
	pos.x += speed * dir.x * deltatime;
	pos.y += speed * dir.y * deltatime;
}

void Plane::MoveAlongPathMoveAround()
{
	float deltatime = TimerManager::GetInstance()->GetDeltaTime();

	pathRadian += DEG_TO_RAD(speed * pathComplex * deltatime);
	if (fabs(pathRadian) >= fabs(goalRadian))
		return SetGoal();

	float rad = startRadian + pathRadian;
	pos.x = goal.x + pathRadius * cosf(rad);
	pos.y = goal.y + pathRadius * sinf(rad);
}

void Plane::MoveAlongPathMoveCurve()
{
	if (curveVar >= 1.0)
		return SetGoal();

	float deltatime = TimerManager::GetInstance()->GetDeltaTime();

	float step = speed * deltatime;
	float tmpVar = curveVar;

	while (tmpVar < 1.0) {
		tmpVar += 1e-5f;
		FPOINT nextPos = getBezierPoint(tmpVar, startPos, curveContolPos, goal);
		if (GetDistance(pos, nextPos) >= step) {
			pos = nextPos;
			break;
		}
	}
	curveVar = tmpVar;
}

void Plane::OnDamage(void)
{
	--health;
	if (health <= 0)
	{
		active = false;
		render = false;
		state = GameObjectStates::Die;
		if (type == Type::PLAYER && PlayerManager::GetInstance()->Revive())
		{
			state = GameObjectStates::Wait;
			currPath = 0;
			pos = { WINSIZE_X / 2, WINSIZE_Y + 100 };
			absTime = INVINCIBILITY_TIME;
			SetGoal();
		}
	}
}

GameObjectStates Plane::GetState(void)
{
	return state;
}

void Plane::SetPath(vector<Task>* path)
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
	if (path && this->path->size() > currPath)
	{
		Task& target = this->path->at(currPath++);
		pathType = target.type;
		taskTime = target.taskTime;
		FPOINT tmp = target.dest;
		goal = { pos.x + tmp.x, pos.y + tmp.y };

		switch (pathType)
		{
		case TaskType::STOP:
			dir = { 0, };
			break;
		case TaskType::MOVEAROUND:
			pathRadian = 0;
			goalRadian = target.destRadian;
			pathRadius = sqrtf(powf(tmp.x, 2) + powf(tmp.y, 2));
			pathComplex = 360 / (PI * (pathRadius * 2));
			startRadian = atan2f(pos.y - goal.y, pos.x - goal.x);
			break;
		case TaskType::MOVECURVE:
			curveContolPos = { pos.x + target.control.x, pos.y + target.control.y};
			startPos = pos;
			curveVar = 0;
			break;
		}
	}
	else
		pathType = TaskType::NONE;
}

Plane& Plane::operator=(const PlaneType& target)
{
	image = ImageManager::GetInstance()->GetImage(target.key);
	size = target.size;
	health = target.health;
	missilePos = target.missilePos;
	centerPos = target.centerPos;
	speed = target.speed;
	return *this;
}

bool Plane::OutOfWindow(void)
{
	int halfWidth = image->GetWidth() / 2;
	int halfHeight = image->GetHeight() / 2;

	if (pos.x + size.left + centerPos.x < 0 || pos.x + size.right - centerPos.x > WINSIZE_X ||
		pos.y + size.top + centerPos.y < 0 || pos.y + size.bottom - centerPos.y > WINSIZE_Y)
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
