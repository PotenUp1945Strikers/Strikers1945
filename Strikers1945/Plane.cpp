#include "Plane.h"
#include "CommonFunction.h"

map<const wchar_t*, PlaneType> Plane::dict;


void Plane::FillDict(void)
{
	{
		PlaneType player;
		player.key = TEXT(PLAYER_PATH);
		player.size = RECT{ -4, -8, 5, 6 };
		player.health = 1;
		player.missilePos = { 0, -20 };
		player.centerPos = { 16, 23 };
		player.missileType = TEXT(NORMAL_BULLET_PATH);
		player.maxFrameX = 7;
		player.renderType = PlaneRenderType::DIR_X;
		player.speed = 180;
		dict.insert(make_pair(TEXT(PLAYER_PATH), player));
	}

	{
		PlaneType tank;
		tank.key = TEXT(TANK_PATH);
		tank.size = RECT{ -9, -13, 9, 13 };
		tank.health = 10;
		tank.missilePos = { 16, 0 };
		tank.centerPos = { 16, 16 };
		tank.missileType = TEXT(NORMAL_BULLET_PATH);
		tank.maxFrameX = 16;
		tank.renderType = PlaneRenderType::TANK;
		tank.speed = 0;
		dict.insert(make_pair(TEXT(TANK_PATH), tank));
	}

	{
		PlaneType enemy1;
		enemy1.key = TEXT(ENEMY1_PATH);
		enemy1.size = RECT{ -2, -16, 3, 16 };
		enemy1.health = 5;
		enemy1.missilePos = { 0, -17 };
		enemy1.centerPos = { 19.5, 16 };
		enemy1.missileType = TEXT(NORMAL_BULLET_PATH);
		enemy1.maxFrameX = 3;
		enemy1.renderType = PlaneRenderType::DIR_X;
		enemy1.speed = 160;
		dict.insert(make_pair(TEXT(ENEMY1_PATH), enemy1));
	}

	{
		PlaneType enemy2;
		enemy2.key = TEXT(ENEMY2_PATH);
		enemy2.size = RECT{ -3, -9, 4, 3 };
		enemy2.health = 3;
		enemy2.missilePos = { 0, 16 };
		enemy2.centerPos = { 10, 15 };
		enemy2.missileType = TEXT(NORMAL_BULLET_PATH);
		enemy2.maxFrameX = 11;
		enemy2.renderType = PlaneRenderType::NORMAL;
		enemy2.speed = 230;
		dict.insert(make_pair(TEXT(ENEMY2_PATH), enemy2));
	}

	{
		PlaneType enemy3;
		enemy3.key = TEXT(ENEMY3_PATH);
		enemy3.size = RECT{ -5, -12, 6, 6 };
		enemy3.health = 4;
		enemy3.missilePos = { 0, 16 };
		enemy3.centerPos = { 9, 16 };
		enemy3.missileType = TEXT(NORMAL_BULLET_PATH);
		enemy3.maxFrameX = 11;
		enemy3.renderType = PlaneRenderType::NORMAL;
		enemy3.speed = 200;
		dict.insert(make_pair(TEXT(ENEMY3_PATH), enemy3));
	}

	{
		PlaneType midEnemy1;
		midEnemy1.key = TEXT(MID_ENEMY1_PATH);
		midEnemy1.size = RECT{ -2, -16, 2, 16 };
		midEnemy1.health = 3;
		midEnemy1.missilePos = { 0, -16 };
		midEnemy1.centerPos = { 18, 16 };
		midEnemy1.missileType = TEXT(NORMAL_BULLET_PATH);
		midEnemy1.maxFrameX = 1;
		midEnemy1.renderType = PlaneRenderType::NORMAL;
		midEnemy1.speed = 150;
		dict.insert(make_pair(TEXT(MID_ENEMY1_PATH), midEnemy1));

		PlaneType midEnemy1Left;
		midEnemy1Left.key = TEXT(MID_ENEMY1_LEFT);
		midEnemy1Left.size = RECT{ -2, -16, 2, 16 };
		midEnemy1Left.health = 3;
		midEnemy1Left.missilePos = { 0, -16 };
		midEnemy1Left.centerPos = { 18, 16 };
		midEnemy1Left.missileType = TEXT(NORMAL_BULLET_PATH);
		midEnemy1Left.renderType = PlaneRenderType::NORMAL;
		midEnemy1Left.speed = 150;
		dict.insert(make_pair(TEXT(MID_ENEMY1_LEFT), midEnemy1Left));

		PlaneType midEnemy1Right;
		midEnemy1Right.key = TEXT(MID_ENEMY1_RIGHT);
		midEnemy1Right.size = RECT{ -2, -16, 2, 16 };
		midEnemy1Right.health = 3;
		midEnemy1Right.missilePos = { 0, -16 };
		midEnemy1Right.centerPos = { 18, 16 };
		midEnemy1Right.missileType = TEXT(NORMAL_BULLET_PATH);
		midEnemy1Right.renderType = PlaneRenderType::NORMAL;
		midEnemy1Right.speed = 150;
		dict.insert(make_pair(TEXT(MID_ENEMY1_RIGHT), midEnemy1Right));
	}

	{
		PlaneType midEnemy2;
		midEnemy2.key = TEXT(MID_ENEMY2_PATH);
		midEnemy2.size = RECT{ -2, -16, 2, 16 };
		midEnemy2.health = 3;
		midEnemy2.missilePos = { 0, -16 };
		midEnemy2.centerPos = { 18, 16 };
		midEnemy2.missileType = TEXT(NORMAL_BULLET_PATH);
		midEnemy2.maxFrameX = 2;
		midEnemy2.renderType = PlaneRenderType::DIR;
		midEnemy2.speed = 150;
		dict.insert(make_pair(TEXT(MID_ENEMY2_PATH), midEnemy2));

		PlaneType midEnemy2Left;
		midEnemy2Left.key = TEXT(MID_ENEMY2_LEFT);
		midEnemy2Left.size = RECT{ -2, -16, 2, 16 };
		midEnemy2Left.health = 3;
		midEnemy2Left.missilePos = { 0, -16 };
		midEnemy2Left.centerPos = { 18, 16 };
		midEnemy2Left.missileType = TEXT(NORMAL_BULLET_PATH);
		midEnemy2Left.renderType = PlaneRenderType::NONE;
		midEnemy2Left.speed = 150;
		dict.insert(make_pair(TEXT(MID_ENEMY2_LEFT), midEnemy2Left));

		PlaneType midEnemy2Right;
		midEnemy2Right.key = TEXT(MID_ENEMY2_RIGHT);
		midEnemy2Right.size = RECT{ -2, -16, 2, 16 };
		midEnemy2Right.health = 3;
		midEnemy2Right.missilePos = { 0, -16 };
		midEnemy2Right.centerPos = { 18, 16 };
		midEnemy2Right.missileType = TEXT(NORMAL_BULLET_PATH);
		midEnemy2Right.renderType = PlaneRenderType::NONE;
		midEnemy2Right.speed = 150;
		dict.insert(make_pair(TEXT(MID_ENEMY2_RIGHT), midEnemy2Right));
	}

	{
		PlaneType boss;
		boss.key = TEXT(BOSS_PATH);
		boss.size = RECT{ -2, -16, 2, 16 };
		boss.health = 3;
		boss.missilePos = { 0, -16 };
		boss.centerPos = { 18, 16 };
		boss.missileType = TEXT(NORMAL_BULLET_PATH);
		boss.maxFrameX = 30;
		boss.renderType = PlaneRenderType::NORMAL;
		boss.speed = 150;
		dict.insert(make_pair(TEXT(BOSS_PATH), boss));

		PlaneType bossLeft;
		bossLeft.key = TEXT(BOSS_LEFT);
		bossLeft.size = RECT{ -2, -16, 2, 16 };
		bossLeft.health = 3;
		bossLeft.missilePos = { 0, -16 };
		bossLeft.centerPos = { 18, 16 };
		bossLeft.missileType = TEXT(NORMAL_BULLET_PATH);
		bossLeft.renderType = PlaneRenderType::NONE;
		bossLeft.speed = 150;
		dict.insert(make_pair(TEXT(BOSS_LEFT), bossLeft));

		PlaneType bossCenter;
		bossCenter.key = TEXT(MID_ENEMY2_RIGHT);
		bossCenter.size = RECT{ -2, -16, 2, 16 };
		bossCenter.health = 3;
		bossCenter.missilePos = { 0, -16 };
		bossCenter.centerPos = { 18, 16 };
		bossCenter.missileType = TEXT(NORMAL_BULLET_PATH);
		bossCenter.renderType = PlaneRenderType::NONE;
		bossCenter.speed = 150;
		dict.insert(make_pair(TEXT(MID_ENEMY2_RIGHT), bossCenter));

		PlaneType bossRight;
		bossRight.key = TEXT(MID_ENEMY2_RIGHT);
		bossRight.size = RECT{ -2, -16, 2, 16 };
		bossRight.health = 3;
		bossRight.missilePos = { 0, -16 };
		bossRight.centerPos = { 18, 16 };
		bossRight.missileType = TEXT(NORMAL_BULLET_PATH);
		bossRight.renderType = PlaneRenderType::NONE;
		bossRight.speed = 150;
		dict.insert(make_pair(TEXT(MID_ENEMY2_RIGHT), bossRight));
	}
}

void Plane::Init(void)
{
	if (dict.empty())
		FillDict();

	if (!launcher)
		launcher = new MissileManager;
	if (!bomb)
	{
		bomb = new Bomb;
		bomb->Init();
	}
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
			if (!bomb)
				bomb = new Bomb;
			bomb->Init();
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
	if (bomb)
	{
		bomb->Release();
		delete bomb;
		bomb = nullptr;
	}
}

void Plane::Render(HDC hdc)
{
	if (image && render)
		image->FrameRender(hdc, centerPos, pos.x, pos.y, 0, 0);
	if (launcher)
		launcher->Render(hdc);
	if (bomb)
		bomb->Render(hdc);
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

	if (bomb)
		bomb->Update();
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

void Plane::DropBomb()
{
	if (!ItemManager::GetInstance()->GetBombing())
	{
		bomb->SetActive(true);
		bomb->SetRender(true);
	}
}


Bomb* Plane::GetBombRef(void)
{
	return bomb;
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
