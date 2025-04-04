#include "Plane.h"
#include "CommonFunction.h"

map<const wchar_t*, PlaneType> Plane::dict;


void Plane::FillDict(void)
{
	{
		PlaneType player;
		player.key = TEXT(PLAYER_PATH);
		player.size = RECT{ -8, -15, 8, 9 };
		player.health = 1;
		player.missilePos = { 0, -31 };
		player.centerPos = { 32, 31 };
		player.missileType = TEXT(RAPIDFIRE_BULLET_PATH);
		player.maxFrameX = 7;
		player.renderType = PlaneRenderType::DIR_X;
		player.speed = 180;
		dict.insert(make_pair(TEXT(PLAYER_PATH), player));
	}

	{
		PlaneType player;
		player.key = TEXT(PLAYER2_PATH);
		player.size = RECT{ -8, -15, 8, 9 };
		player.health = 1;
		player.missilePos = { 0, -31 };
		player.centerPos = { 32, 31 };
		player.missileType = TEXT(PLAYER_BULLET1_PATH);
		player.maxFrameX = 7;
		player.renderType = PlaneRenderType::DIR_X;
		player.speed = 180;
		dict.insert(make_pair(TEXT(PLAYER2_PATH), player));
	}

	{
		PlaneType tank;
		tank.key = TEXT(TANK_PATH);
		tank.size = RECT{ -18, -26, 18, 26 };
		tank.health = 10;
		tank.missilePos = { 32, 0 };
		tank.centerPos = { 32, 32 };
		tank.missileType = TEXT(TARGETTING_BULLET_PATH);
		tank.maxFrameX = 16;
		tank.renderType = PlaneRenderType::TANK;
		tank.speed = 0;
		dict.insert(make_pair(TEXT(TANK_PATH), tank));
	}

	{
		PlaneType enemy1;
		enemy1.key = TEXT(ENEMY1_PATH);
		enemy1.size = RECT{ -4, -32, 6, 32 };
		enemy1.health = 4;
		enemy1.missilePos = { 0, -34 };
		enemy1.centerPos = { 39, 32 };
		enemy1.missileType = TEXT(TARGETTING_BULLET_PATH);
		enemy1.maxFrameX = 3;
		enemy1.renderType = PlaneRenderType::DIR_X;
		enemy1.speed = 160;
		dict.insert(make_pair(TEXT(ENEMY1_PATH), enemy1));
	}

	{
		PlaneType enemy2;
		enemy2.key = TEXT(ENEMY2_PATH);
		enemy2.size = RECT{ -6, -18, 8, 6 };
		enemy2.health = 3;
		enemy2.missilePos = { 0, 32 };
		enemy2.centerPos = { 20, 30 };
		enemy2.missileType = TEXT(TARGETTING_BULLET_PATH);
		enemy2.maxFrameX = 11;
		enemy2.renderType = PlaneRenderType::NORMAL;
		enemy2.speed = 230;
		dict.insert(make_pair(TEXT(ENEMY2_PATH), enemy2));
	}

	{
		PlaneType enemy3;
		enemy3.key = TEXT(ENEMY3_PATH);
		enemy3.size = RECT{ -10, -24, 12, 12 };
		enemy3.health = 3;
		enemy3.missilePos = { 0, 32 };
		enemy3.centerPos = { 18, 32 };
		enemy3.missileType = TEXT(TARGETTING_BULLET_PATH);
		enemy3.maxFrameX = 11;
		enemy3.renderType = PlaneRenderType::NORMAL;
		enemy3.speed = 230;
		dict.insert(make_pair(TEXT(ENEMY3_PATH), enemy3));
	}

	{
		PlaneType midEnemy1;
		midEnemy1.key = TEXT(MID_ENEMY1_PATH);
		midEnemy1.size = RECT{ -17, -96, 17, 62 };
		midEnemy1.health = 80;
		midEnemy1.missilePos = { 85, -15 };
		midEnemy1.centerPos = { 115, 121 };
		midEnemy1.missileType = TEXT(TARGETTING_BULLET_PATH);
		midEnemy1.maxFrameX = 1;
		midEnemy1.renderType = PlaneRenderType::NORMAL;
		midEnemy1.speed = 150;
		dict.insert(make_pair(TEXT(MID_ENEMY1_PATH), midEnemy1));
	}

	{
		PlaneType midEnemy2;
		midEnemy2.key = TEXT(MID_ENEMY2_PATH);
		midEnemy2.size = RECT{ -27, -16, 27, 73 };
		midEnemy2.health = 80;
		midEnemy2.missilePos = { 105, 30 };
		midEnemy2.centerPos = { 122, 133 };
		midEnemy2.missileType = TEXT(TARGETTING_BULLET_PATH);
		midEnemy2.maxFrameX = 2;
		midEnemy2.renderType = PlaneRenderType::DIR;
		midEnemy2.speed = 150;
		dict.insert(make_pair(TEXT(MID_ENEMY2_PATH), midEnemy2));
	}

	{
		PlaneType boss;
		boss.key = TEXT(BOSS_PATH);
		boss.size = RECT{ -88, -123, 70, 98 };
		boss.health = 500;
		boss.missilePos = { -17, 24 };
		boss.centerPos = { 232, 232 };
		boss.missileType = TEXT(TARGETTING_BULLET_PATH);
		boss.maxFrameX = 30;
		boss.renderType = PlaneRenderType::NORMAL;
		boss.speed = 120;
		dict.insert(make_pair(TEXT(BOSS_PATH), boss));
	}
}

void Plane::Init(void)
{
	if (dict.empty())
		FillDict();

	if (!launcher)
		launcher = new MissileManager;
	launcher->Init();

	if (!bomb)
	{
		bomb = new Bomb;
		bomb->Init();
		CollisionManager::GetInstance()->AddCollider(bomb);
	}
	state = GameObjectStates::Die;
	use = true;
	path = nullptr;
	active = false;
	render = false;
	currPath = 0;
	goal = { 0, };
	currFrameX = 0;
	currFrameY = 0;
	hitRenderTime = HIT_RENDER_TIME;
	frameTime = ANIMATION_FRAME_TIME;
	damageTickTime = HIT_TICK_TIME;
	playerNum = PlayerNum::NONE;
}


void Plane::Init(const wchar_t* key, float startPos, Type type)
{
	if (dict.empty())
		FillDict();

	state = GameObjectStates::Wait;
	use = false;
	path = nullptr;
	active = false;
	render = false;
	currPath = 0;
	goal = { 0, };
	currFrameX = 0;
	currFrameY = 0;
	hitRenderTime = HIT_RENDER_TIME;
	frameTime = ANIMATION_FRAME_TIME;
	damageTickTime = HIT_TICK_TIME;
	playerNum = PlayerNum::NONE;

	if (!launcher)
		launcher = new MissileManager;
	launcher->Init();
	if (!bomb)
	{
		bomb = new Bomb;
		bomb->Init();
		CollisionManager::GetInstance()->AddCollider(bomb);
	}

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
	float deltatime = TimerManager::GetInstance()->GetDeltaTime();
	if (currFrameY == 1 && type == Type::ENEMY)
	{
		hitRenderTime -= deltatime;
		if (hitRenderTime < 0.0f)
		{
			currFrameY = 0;
			hitRenderTime = HIT_RENDER_TIME;
		}
	}

	if (image && render)
	{
		switch (renderType)
		{
		case PlaneRenderType::NORMAL:
			frameTime -= deltatime;
			if (frameTime < 0.0f)
			{
				currFrameX = ++currFrameX % maxFrameX;
				frameTime = ANIMATION_FRAME_TIME;
			}
			break;
		case PlaneRenderType::DIR:
			if (dir.x + dir.y != 0.0f)
				currFrameX = 1;
			else
				currFrameX = 0;
			break;
		case PlaneRenderType::DIR_X:
			int frame = 0;
			if (dir.x < 0.0f && currFrameX > 0)
				--frame;
			else if (dir.x > 0.0f && currFrameX < maxFrameX - 1)
				++frame;
			else if (dir.x == 0.0f && currFrameX < maxFrameX / 2)
				++frame;
			else if (dir.x == 0.0f && currFrameX > maxFrameX / 2)
				--frame;
			frameTime -= deltatime;
			if (frameTime < 0.0f)
			{
				currFrameX += frame;
				frameTime = ANIMATION_FRAME_TIME;
			}
			break;
		}
		image->FrameRender(hdc, centerPos, pos.x, pos.y, currFrameX, currFrameY);
	}

	if (launcher)
		launcher->Render(hdc);
	if (bomb)
		bomb->Render(hdc);
}

void Plane::Update(void)
{
	damageTickTime -= TimerManager::GetInstance()->GetDeltaTime();

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
		use = true;
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
	if (launcher)
		launcher->Upgrade();
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
			dir = GetUnitVector(pos, nextPos);
			pos = nextPos;
			break;
		}
	}
	curveVar = tmpVar;
}

void Plane::OnDamage(int damage)
{
	if (damageTickTime >= 0)
		return;
	else
		damageTickTime = HIT_TICK_TIME;

	health -= damage;
	if (type == Type::ENEMY)
		currFrameY = 1;
	if (type == Type::ENEMY && health <= 0)
	{
		ItemManager::GetInstance()->CreateItem(pos);
		EffectManager::GetInstance()->OnEffect(TEXT(EFFECT3_PATH), pos);
	}
	if (health <= 0)
	{
		active = false;
		render = false;
		use = true;
		state = GameObjectStates::Die;
		if (type == Type::PLAYER && PlayerManager::GetInstance()->Revive())
		{
			state = GameObjectStates::Wait;
			currPath = 0;
			pos = { static_cast<float>(static_cast<int>(playerNum) == static_cast<int>(PlayerNum::PLAYER1) ? WINSIZE_X / 2 - 150 : WINSIZE_X / 2 + 150)      , WINSIZE_Y + 100 };
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

PlayerNum Plane::GetPlayerNum()
{
	return playerNum;
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

bool Plane::CanIUseIt(void)
{
	return use;
}

void Plane::SetPlayerNum(PlayerNum playerNum)
{
	this->playerNum = playerNum;
}

void Plane::SetGoal(void)
{
	if (path && this->path->size() > currPath)
	{
		if (this->path->at(currPath).loop)
			currPath = this->path->at(currPath).loopIndex;
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
	renderType = target.renderType;
	maxFrameX = target.maxFrameX;
	if (renderType == PlaneRenderType::DIR_X)
		currFrameX = maxFrameX / 2;
	return *this;
}

bool Plane::OutOfWindow(void)
{
	int halfWidth = image->GetWidth() / 2;
	int halfHeight = image->GetHeight() / 2;

	if (pos.x + halfWidth < 0 || pos.x - halfWidth > WINSIZE_X ||
		pos.y + halfHeight < 0 || pos.y - halfHeight > WINSIZE_Y)
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
