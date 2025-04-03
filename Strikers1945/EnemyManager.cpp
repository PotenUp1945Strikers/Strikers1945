#include "EnemyManager.h"
#include "PlayerManager.h"
#include "BackgroundManager.h"
#include "CollisionManager.h"
#include "Plane.h"


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
			plane->Init();
			plane->SetType(Type::ENEMY);
			CollisionManager::GetInstance()->AddCollider(plane);
		}
	}

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
	planes.shrink_to_fit();
}

void EnemyManager::Update()
{
	PutEnemy();

	for (auto i : planes)
	{
		i->Update();
	}

}

void EnemyManager::PutEnemy(void)
{
	if (currLev >= level.size())
		return;

	for (auto& plane : planes)
	{
		if (plane->GetActive() == false)
		{
			StageScript& script = level[currLev++];
			switch (script.type)
			{
			case EnemyType::PLANE:
				plane->Init(script.key, script.appeared, Type::ENEMY);
				plane->SetPos(script.pos);
				plane->SetPath(script.path);
				break;
			}
			if (currLev >= level.size())
				break;
		}
	}
}

void EnemyManager::Render(HDC hdc)
{

	for (auto i : planes)
	{
		if (i->GetRender())
		{
			i->Render(hdc);
		}
	}

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

	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("Pattern_Movearound")], { 100, -50 }, 300 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("Pattern_Movearound")], { 150, -50 }, 300 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("Pattern_Movearound")], { 200, -50 }, 300 });

	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("FOWARD_AND_TURN_RIGHT")], { WINSIZE_X - 100, -50 }, 600 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("FOWARD_AND_TURN_RIGHT")], { WINSIZE_X - 150, -50 }, 600 });
	level.push_back({ EnemyType::PLANE, TEXT(ENEMY1_PATH), dict[TEXT("FOWARD_AND_TURN_RIGHT")], { WINSIZE_X - 200, -50 }, 600 });
}


