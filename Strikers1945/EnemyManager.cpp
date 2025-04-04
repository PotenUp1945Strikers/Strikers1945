#include "EnemyManager.h"
#include "PlayerManager.h"
#include "BackgroundManager.h"
#include "CollisionManager.h"
#include "Plane.h"
#include "Tank.h"
#include "MiddleEnemy.h"
#include "Boss.h"


void EnemyManager::Init()
{
	// TODO : scripts init
	FillDict();
	CreateLevel();

	// Planes Init (enemy)
	currLev = 0;

	if (planes.empty())
	{
		planes.resize(MAX_MISSILE);
		for (auto& plane : planes)
		{
			plane = new Plane;
			plane->SetType(Type::ENEMY);
			plane->Init();
			CollisionManager::GetInstance()->AddCollider(plane);
		}
	}
	else
	{
		for (auto& plane : planes)
			plane->Init();
	}

	if (tanks.empty())
	{
		tanks.resize(MAX_MISSILE);
		for (auto& tank : tanks)
		{
			tank = new Tank;
			tank->SetType(Type::ENEMY);
			tank->Init();
			CollisionManager::GetInstance()->AddCollider(tank);
		}
	}
	else
	{
		for (auto& tank : tanks)
			tank->Init();
	}


	if (middles.empty())
	{
		middles.resize(MAX_ENEMY_PLANE);
		for (auto& mid : middles)
		{
			mid = new MiddleEnemy;
			mid->SetType(Type::ENEMY);
			mid->Init();
			CollisionManager::GetInstance()->AddCollider(mid);
		}
	}
	else
	{
		for (auto& mid : middles)
			mid->Init();
	}
	
	if (!boss)
	{
		boss = new Boss;
		boss->SetType(Type::ENEMY);
		boss->Init();
		CollisionManager::GetInstance()->AddCollider(boss);
	}
	else
		boss->Init();

	PutEnemy();
}

void EnemyManager::Release()
{
	if (!planes.empty())
	{
		for (auto& plane : planes)
		{
			plane->Release();
			delete plane;
		}
	}
	planes.clear();

	if (!tanks.empty())
	{
		for (auto& tank : tanks)
		{
			tank->Release();
			delete tank;
		}
	}
	tanks.clear();

	if (!middles.empty())
	{
		for (auto& mid : middles)
		{
			mid->Release();
			delete mid;
		}
	}
	middles.clear();

	if (boss)
	{
		boss->Release();
		delete boss;
		boss = nullptr;
	}
}

void EnemyManager::Update()
{
	PutEnemy();

	for (auto& plane : planes)
		plane->Update();

	for (auto& tank : tanks)
		tank->Update();

	for (auto& mid : middles)
		mid->Update();

	if (boss)
		boss->Update();
}

void EnemyManager::PutEnemy(void)
{
	if (currLev >= level.size())
		return;

	bool busy = false;

	while (!busy && currLev < level.size())
	{
		StageScript& script = level[currLev];
		busy = true;
		switch (script.type)
		{
		case EnemyType::PLANE:
			for (auto& plane : planes)
			{
				if (plane->CanIUseIt())
				{
					plane->Init(script.key, script.appeared, Type::ENEMY);
					plane->SetPos(script.pos);
					plane->SetPath(script.path);
					busy = false;
					currLev++;
					break;
				}
			}
			break;
		case EnemyType::TANK:
			for (auto& tank : tanks)
			{
				if (tank->CanIUseIt())
				{
					tank->Init(script.key, script.appeared, Type::ENEMY);
					tank->SetPos(script.pos);
					busy = false;
					currLev++;
					break;
				}
			}
			break;
		case EnemyType::MIDDLE:
			for (auto& mid : middles)
			{
				if (mid->CanIUseIt())
				{
					mid->Init(script.key, script.appeared, Type::ENEMY);
					mid->SetPos(script.pos);
					mid->SetPath(script.path);
					busy = false;
					currLev++;
					break;
				}
			}
			break;
		case EnemyType::BOSS:
			if (boss && boss->CanIUseIt())
			{
				boss->Init(script.key, script.appeared, Type::ENEMY);
				boss->SetPos(script.pos);
				boss->SetPath(script.path);
				busy = false;
				currLev++;
				break;
			}
			break;
		}
	}	
}

void EnemyManager::Render(HDC hdc)
{
	for (auto& plane : planes)
		plane->Render(hdc);

	for (auto& tank : tanks)
		tank->Render(hdc);

	for (auto& mid : middles)
		mid->Render(hdc);

	if (boss)
		boss->Render(hdc);

}

void EnemyManager::FillDict(void)
{
	if (!dict.empty())
		return;
	{
		vector<Task>* tmpVec = new vector<Task>;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { WINSIZE_X + 100 , WINSIZE_Y / 2 };
		tmpVec->back().control = { WINSIZE_X + 100, 0 };
		tmpVec->back().taskTime = 0.0f;
		tmpVec->back().destRadian = 0.0f;
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;
		
		dict.insert(make_pair(TEXT("LEFT_TOP_TO_RIGHT_BOTTOM"), tmpVec));
	}

	{
		vector<Task>* tmpVec = new vector<Task>;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { -(WINSIZE_X + 100) , WINSIZE_Y / 2 };
		tmpVec->back().control = { -(WINSIZE_X + 100), 0 };
		tmpVec->back().taskTime = 0.0f;
		tmpVec->back().destRadian = 0.0f;
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		dict.insert(make_pair(TEXT("RIGHT_TOP_TO_LEFT_BOTTOM"), tmpVec));
	}

	{
		vector<Task>* tmpVec = new vector<Task>;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { WINSIZE_X / 2 , - WINSIZE_Y / 4 };
		tmpVec->back().control = { WINSIZE_X / 3, 0 };
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::STOP;
		tmpVec->back().taskTime = 5.0f;
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::NONE;
		tmpVec->back().loop = true;
		tmpVec->back().loopIndex = 1;

		dict.insert(make_pair(TEXT("LEFT_UP_AND_STOP"), tmpVec));
	}

	{
		vector<Task>* tmpVec = new vector<Task>;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { -WINSIZE_X / 2 , -WINSIZE_Y / 4 };
		tmpVec->back().control = { -WINSIZE_X / 3, 0 };
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::STOP;
		tmpVec->back().taskTime = 5.0f;
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::NONE;
		tmpVec->back().loop = true;
		tmpVec->back().loopIndex = 1;

		dict.insert(make_pair(TEXT("RIGHT_UP_AND_STOP"), tmpVec));
	}

	{
		vector<Task>* tmpVec = new vector<Task>;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVE;
		tmpVec->back().dest = { 0, WINSIZE_Y / 3 };

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVEAROUND;
		tmpVec->back().dest = { WINSIZE_X / 3, 0 };
		tmpVec->back().destRadian = DEG_TO_RAD(180);


		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVE;
		tmpVec->back().dest = { 0, -WINSIZE_Y / 3 };

		dict.insert(make_pair(TEXT("MOVEAROUND"), tmpVec));
	}

	{
		vector<Task>* tmpVec = new vector<Task>;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVE;
		tmpVec->back().dest = { 0, WINSIZE_Y / 2 };

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { -WINSIZE_X / 2, WINSIZE_Y / 2 };
		tmpVec->back().control = { 0,  WINSIZE_Y / 2 };

		dict.insert(make_pair(TEXT("FOWARD_AND_TURN_LEFT"), tmpVec));
	}

	{
		vector<Task>* tmpVec = new vector<Task>;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVE;
		tmpVec->back().dest = { 0, WINSIZE_Y / 2 };

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { WINSIZE_X / 2, WINSIZE_Y / 2 };
		tmpVec->back().control = { 0,  WINSIZE_Y / 2 };

		dict.insert(make_pair(TEXT("FOWARD_AND_TURN_RIGHT"), tmpVec));
	}


	{
		vector<Task>* tmpVec = new vector<Task>;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { WINSIZE_X / 2, -WINSIZE_Y / 5 };
		tmpVec->back().control = { 0,  -WINSIZE_Y / 5 };

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVE;
		tmpVec->back().dest = { 0, -WINSIZE_Y };

		dict.insert(make_pair(TEXT("LEFT_TO_FOWARD"), tmpVec));
	}

	{
		vector<Task>* tmpVec = new vector<Task>;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { -WINSIZE_X / 2, -WINSIZE_Y / 5 };
		tmpVec->back().control = { 0,  -WINSIZE_Y / 5 };

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVE;
		tmpVec->back().dest = { 0, -WINSIZE_Y };

		dict.insert(make_pair(TEXT("RIGHT_TO_FOWARD"), tmpVec));
	}

	{
		vector<Task>* tmpVec = new vector<Task>;

		float stopTime = 0.3f;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVE;
		tmpVec->back().dest = { 0, WINSIZE_Y / 2 };
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::STOP;
		tmpVec->back().taskTime = stopTime;
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { 120, -120 };
		tmpVec->back().control = { 0,  -120 };
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::STOP;
		tmpVec->back().taskTime = stopTime;
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { -120, 0 };
		tmpVec->back().control = { 0,  120 };
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::STOP;
		tmpVec->back().taskTime = stopTime;
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { -120, 0 };
		tmpVec->back().control = { 0,  -120 };
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::STOP;
		tmpVec->back().taskTime = stopTime;
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { 120, 120 };
		tmpVec->back().control = { 0,  120 };
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::STOP;
		tmpVec->back().taskTime = stopTime;
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { 120, 0 };
		tmpVec->back().control = { 0,  -120 };
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::STOP;
		tmpVec->back().taskTime = stopTime;
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { -120, -120 };
		tmpVec->back().control = { -120,  0 };
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::STOP;
		tmpVec->back().taskTime = stopTime;
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { -120, 120 };
		tmpVec->back().control = { 0,  120 };
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::STOP;
		tmpVec->back().taskTime = stopTime;
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { 120, 0 };
		tmpVec->back().control = { 0,  -120 };
		tmpVec->back().loop = false;
		tmpVec->back().loopIndex = 0;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::NONE;
		tmpVec->back().loop = true;
		tmpVec->back().loopIndex = 1;

		dict.insert(make_pair(TEXT("BOSS"), tmpVec));
	}
}

void EnemyManager::CreateLevel(void)
{
	if (!level.empty() || dict.empty())
		return;

	level.push_back({ EnemyType::PLANE, TEXT(ENEMY3_PATH), dict[TEXT("LEFT_TOP_TO_RIGHT_BOTTOM")], { -50, 200 }, 300 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY3_PATH), dict[TEXT("LEFT_TOP_TO_RIGHT_BOTTOM")], { -50, 200 }, 340 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY3_PATH), dict[TEXT("LEFT_TOP_TO_RIGHT_BOTTOM")], { -50, 200 }, 380 });
	level.push_back({ EnemyType::MIDDLE, TEXT(MID_ENEMY1_PATH), dict[TEXT("RIGHT_UP_AND_STOP")], { WINSIZE_X + 150, 600 }, 390 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY3_PATH), dict[TEXT("LEFT_TOP_TO_RIGHT_BOTTOM")], { -50, 200 }, 420 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY3_PATH), dict[TEXT("LEFT_TOP_TO_RIGHT_BOTTOM")], { -50, 200 }, 460 });

	level.push_back({ EnemyType::TANK, TEXT(TANK_PATH), nullptr, { 500, -50 }, 500 });
	level.push_back({ EnemyType::TANK, TEXT(TANK_PATH), nullptr, { 560, -50 }, 560 });
	level.push_back({ EnemyType::TANK, TEXT(TANK_PATH), nullptr, { 460, -50 }, 620 });

	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("RIGHT_TO_FOWARD")], { WINSIZE_X + 50, 700 }, 500 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("RIGHT_TO_FOWARD")], { WINSIZE_X + 150, 700 }, 500 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("RIGHT_TO_FOWARD")], { WINSIZE_X + 250, 700 }, 500 });

	level.push_back({ EnemyType::PLANE, TEXT(ENEMY2_PATH), dict[TEXT("RIGHT_TOP_TO_LEFT_BOTTOM")], { WINSIZE_X + 50, 100 }, 800 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY2_PATH), dict[TEXT("RIGHT_TOP_TO_LEFT_BOTTOM")], { WINSIZE_X + 50, 100 }, 840 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY2_PATH), dict[TEXT("RIGHT_TOP_TO_LEFT_BOTTOM")], { WINSIZE_X + 50, 100 }, 880 });

	level.push_back({ EnemyType::TANK, TEXT(TANK_PATH), nullptr, { 300, -50 }, 900 });
	level.push_back({ EnemyType::TANK, TEXT(TANK_PATH), nullptr, { 250, -50 }, 970 });
	level.push_back({ EnemyType::TANK, TEXT(TANK_PATH), nullptr, { 320, -50 }, 1020 });
	level.push_back({ EnemyType::TANK, TEXT(TANK_PATH), nullptr, { 200, -50 }, 1030 });

	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("LEFT_TOP_TO_RIGHT_BOTTOM")], { -50, 300 }, 1100 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("LEFT_TOP_TO_RIGHT_BOTTOM")], { -50, 300 }, 1180 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("LEFT_TOP_TO_RIGHT_BOTTOM")], { -50, 300 }, 1260 });

	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("RIGHT_TOP_TO_LEFT_BOTTOM")], { WINSIZE_X + 50, 300 }, 1400 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("RIGHT_TOP_TO_LEFT_BOTTOM")], { WINSIZE_X + 120, 370 }, 1400 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("RIGHT_TOP_TO_LEFT_BOTTOM")], { WINSIZE_X + 190, 440 }, 1400 });

	level.push_back({ EnemyType::BOSS, TEXT(BOSS_PATH), dict[TEXT("BOSS")], { WINSIZE_X / 2, -160 }, 3000 });
}


