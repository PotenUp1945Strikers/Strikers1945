#include "EnemyManager.h"
#include "PlayerManager.h"
#include "BackgroundManager.h"
#include "CollisionManager.h"
#include "Plane.h"


map<const wchar_t*, vector<Task>*> EnemyManager::dict;

void EnemyManager::Init()
{
	// TODO : scripts init
	if(dict.size() <= 0 )
		FillDict();
	
	
	// Planes Init (enemy)
	scriptIndex = 0;

	if (planes.empty())
	{
		planes.push_back(new Plane);
		planes[0]->Init(TEXT(ENEMY1_PATH), 300, Type::ENEMY);
		planes[0]->SetPos({ WINSIZE_X / 2, -100});
		planes[0]->SetPath(dict[TEXT("Pattern_Movearound")]);
		CollisionManager::GetInstance()->AddCollider(planes[0]);
	}

}

void EnemyManager::Release()
{
	//scripts.clear();
	//scripts.shrink_to_fit();
	planes.clear();
	planes.shrink_to_fit();
}

void EnemyManager::Update()
{
	// depends on struct
	//if (BackgroundManager::GetInstance()->GetCurrPosY() >= scripts[scriptIndex].second)
	//{
	//	if (DeployEnemy()) scriptIndex += 1;
	//}


	for (auto i : planes)
	{
		i->Update();
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

bool EnemyManager::DeployEnemy()
{
	//TODO : DeployEnemy logic

	//switch (scripts[scriptIndex].first) // depends on struct
	//{
	//	// Init and addEnemy
	//	case NormalEnemy:
	//		
	//		return true;
	//		break;
	//	case HeliEnemy:

	//		return true;
	//		break;
	//	case BossEnemy:

	//		return true;
	//		break;
	//}

	return false;

}

void EnemyManager::FillDict(void)
{
	{
		vector<Task>* tmpVec = new vector<Task>;

		Task moveTask1;
		moveTask1.type = TaskType::MOVE;
		moveTask1.dest = { 0 , 200.0f };
		moveTask1.taskTime = 0.0f;
		moveTask1.destRadian = 0.0f;
		tmpVec->push_back(moveTask1);

		
		Task moveTask2;
		moveTask2.type = TaskType::MOVE;
		moveTask2.dest = { 0 , 200.0f };
		moveTask2.taskTime = 0.0f;
		moveTask2.destRadian = 0.0f;
		tmpVec->push_back(moveTask2);

	
		Task moveTask3;
		moveTask3.type = TaskType::MOVE;
		moveTask3.dest = { 0 , WINSIZE_Y + 100.0f };
		moveTask3.taskTime = 0.0f;
		moveTask3.destRadian = 0.0f;
		tmpVec->push_back(moveTask3);

		dict.insert(make_pair(TEXT("Pattern_Straight"), tmpVec));
	}

	{
		vector<Task>* tmpVec = new vector<Task>;

		Task moveTask1;
		moveTask1.type = TaskType::MOVE;
		moveTask1.dest = { 0, 200.0f };
		moveTask1.taskTime = 0.0f;
		moveTask1.destRadian = 0.0f;
		tmpVec->push_back(moveTask1);


		Task moveTask2;
		moveTask2.type = TaskType::MOVEAROUND;
		moveTask2.dest = { 0, 200.0f };
		moveTask2.taskTime = 0.0f;
		moveTask2.destRadian = DEG_TO_RAD(360);
		tmpVec->push_back(moveTask2);


		Task moveTask3;
		moveTask3.type = TaskType::MOVE;
		moveTask3.dest = { 0, WINSIZE_Y + 100.0f };
		moveTask3.taskTime = 0.0f;
		moveTask3.destRadian = 0.0f;
		tmpVec->push_back(moveTask3);

		dict.insert(make_pair(TEXT("Pattern_Movearound"), tmpVec));
	}

	{
		vector<Task>* tmpVec = new vector<Task>;

		Task moveTask1;
		moveTask1.type = TaskType::MOVESIN;
		moveTask1.dest = { WINSIZE_X / 2, WINSIZE_Y / 3 * 2 };
		moveTask1.taskTime = 0.0f;
		moveTask1.destRadian = 0.0f;
		tmpVec->push_back(moveTask1);


		Task moveTask2;
		moveTask2.type = TaskType::MOVESIN;
		moveTask2.dest = { WINSIZE_X, WINSIZE_Y };
		moveTask2.taskTime = 0.0f;
		moveTask2.destRadian = 0.0f;
		tmpVec->push_back(moveTask2);

		dict.insert(make_pair(TEXT("Pattern_Sin"), tmpVec));
	}

	
}

void EnemyManager::MakePatternEnemy(const wchar_t* key)
{
	/*auto it = dict.find(key);
	if (it == dict.end()) return;

	vector<Task>*& pattern = it->second;

	for (int i = 0; i < PATTERN_ENEMY_NUM; i++)
	{

		planes.push_back(new Plane);
		planes.back()->Init(TEXT(ENEMY1_PATH), 300, Type::ENEMY);
		planes.back()->SetPos({ WINSIZE_X / 2, -(WINSIZE_Y / 3) });
		CollisionManager::GetInstance()->AddCollider(planes.back());

		vector<Task> tmp;
		if (i < pattern->size()) {

			for (auto& task : *pattern) {
				tmp.push_back(task);
			}

			planes.back()->SetPath(tmp);
		}

	}*/

}
