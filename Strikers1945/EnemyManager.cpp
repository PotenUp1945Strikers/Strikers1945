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
		planes.resize(MAX_ENEMY_PLANE);
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
		tanks.resize(MAX_ENEMY_PLANE);
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
		tmpVec->back().type = TaskType::MOVE;
		tmpVec->back().dest = { 0 , 200.0f };
		tmpVec->back().control = { 0, 0 };
		tmpVec->back().taskTime = 0.0f;
		tmpVec->back().destRadian = 0.0f;
		
		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVE;
		tmpVec->back().dest = { 0 , 200.0f };
		tmpVec->back().control = { 0, 0 };
		tmpVec->back().taskTime = 0.0f;
		tmpVec->back().destRadian = 0.0f;

	
		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVE;
		tmpVec->back().dest = { 0 , WINSIZE_Y + 100.0f };
		tmpVec->back().control = { 0, 0 };
		tmpVec->back().taskTime = 0.0f;
		tmpVec->back().destRadian = 0.0f;
		
		dict.insert(make_pair(TEXT("Pattern_Straight"), tmpVec));
	}

	{
		vector<Task>* tmpVec = new vector<Task>;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVE;
		tmpVec->back().dest = { 0, 200.0f };
		tmpVec->back().control = { 0, 0 };
		tmpVec->back().taskTime = 0.0f;
		tmpVec->back().destRadian = 0.0f;


		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVEAROUND;
		tmpVec->back().dest = { 0, 200.0f };
		tmpVec->back().control = { 0, 0 };
		tmpVec->back().taskTime = 0.0f;
		tmpVec->back().destRadian = DEG_TO_RAD(360);


		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVE;
		tmpVec->back().dest = { 0, WINSIZE_Y + 100.0f };
		tmpVec->back().control = { 0, 0 };
		tmpVec->back().taskTime = 0.0f;
		tmpVec->back().destRadian = 0.0f;

		dict.insert(make_pair(TEXT("Pattern_Movearound"), tmpVec));
	}

	{
		vector<Task>* tmpVec = new vector<Task>;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { 0, WINSIZE_Y - WINSIZE_Y / 3 };
		tmpVec->back().control = { 200, WINSIZE_Y / 4 };
		tmpVec->back().taskTime = 0.0f;
		tmpVec->back().destRadian = 0.0f;

		tmpVec->push_back(Task{});
		tmpVec->back().type = TaskType::MOVECURVE;
		tmpVec->back().dest = { 0, WINSIZE_Y / 3 };
		tmpVec->back().control = { -200,  WINSIZE_Y / 6};
		tmpVec->back().taskTime = 0.0f;
		tmpVec->back().destRadian = 0.0f;

		dict.insert(make_pair(TEXT("Pattern_Sin"), tmpVec));
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
}

void EnemyManager::CreateLevel(void)
{
	if (!level.empty() || dict.empty())
		return;

	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("FOWARD_AND_TURN_LEFT")], { 100, -50 }, 300 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("FOWARD_AND_TURN_LEFT")], { 150, -50 }, 300 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("FOWARD_AND_TURN_LEFT")], { 200, -50 }, 300 });

	level.push_back({ EnemyType::TANK, TEXT(TANK_PATH), nullptr, { WINSIZE_X / 2, -50 }, 500 });

	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("FOWARD_AND_TURN_RIGHT")], { WINSIZE_X - 100, -50 }, 800 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("FOWARD_AND_TURN_RIGHT")], { WINSIZE_X - 150, -50 }, 800 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("FOWARD_AND_TURN_RIGHT")], { WINSIZE_X - 200, -50 }, 800 });

	level.push_back({ EnemyType::PLANE, TEXT(ENEMY2_PATH), dict[TEXT("FOWARD_AND_TURN_LEFT")], { 100, -50 }, 1500 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY2_PATH), dict[TEXT("FOWARD_AND_TURN_LEFT")], { 150, -50 }, 1500 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY2_PATH), dict[TEXT("FOWARD_AND_TURN_LEFT")], { 200, -50 }, 1500 });

	level.push_back({ EnemyType::PLANE, TEXT(ENEMY3_PATH), dict[TEXT("FOWARD_AND_TURN_RIGHT")], { WINSIZE_X - 100, -50 }, 2300 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY3_PATH), dict[TEXT("FOWARD_AND_TURN_RIGHT")], { WINSIZE_X - 150, -50 }, 2300 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY3_PATH), dict[TEXT("FOWARD_AND_TURN_RIGHT")], { WINSIZE_X - 200, -50 }, 2300 });
	
	level.push_back({ EnemyType::MIDDLE, TEXT(MID_ENEMY1_PATH), dict[TEXT("FOWARD_AND_TURN_LEFT")], { 200, -50 }, 2600 });
	level.push_back({ EnemyType::MIDDLE, TEXT(MID_ENEMY2_PATH), dict[TEXT("FOWARD_AND_TURN_RIGHT")], { WINSIZE_X - 200, -50 }, 2600 });

	level.push_back({ EnemyType::BOSS, TEXT(BOSS_PATH), dict[TEXT("Pattern_Straight")], { WINSIZE_X / 2, -100 }, 3000 });
}


