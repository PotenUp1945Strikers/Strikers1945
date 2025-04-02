#include "EnemyManager.h"
#include "PlayerManager.h"
#include "BackgroundManager.h"
#include "CollisionManager.h"
#include "Plane.h"


map<const wchar_t*, TaskType> EnemyManager::dict;

void EnemyManager::Init()
{
	// TODO : scripts init
	if(dict.size() <= 0 )
		FillDict();
	
	
	// Planes Init (enemy)
	scriptIndex = 0;
	/*planes.push_back(new Plane);
	planes.back()->Init(TEXT(ENEMY1_PATH), 300, Type::ENEMY);
	planes.back()->SetPos({ WINSIZE_X / 2, WINSIZE_Y / 3 });
	CollisionManager::GetInstance()->AddCollider(planes.back());*/
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
	TaskType tmptask;
	tmptask.key = TEXT("Pattern_Straight");
	tmptask.tasks.resize(PATTERN_ENEMY_NUM);
	//tmptask.enemyNum = 6;
	for (int i = 0; i < PATTERN_ENEMY_NUM; i++)
	{
		vector<Task> tmpvec;

		Task moveTask1;
		moveTask1.type = eTaskType::MOVE;
		moveTask1.dest = { 50.0f * i + 50.f , 200.0f };
		moveTask1.taskTime = 0.0f;
		moveTask1.destRadian = 0.0f;
		tmpvec.push_back(moveTask1);

		
		Task moveTask2;
		moveTask2.type = eTaskType::MOVE;
		moveTask2.dest = { 50.0f * i + 50.f , 200.0f };
		moveTask2.taskTime = 0.0f;
		moveTask2.destRadian = 0.0f;
		tmpvec.push_back(moveTask2);

	
		Task moveTask3;
		moveTask3.type = eTaskType::MOVE;
		moveTask3.dest = { 50.0f * i + 50.f , WINSIZE_Y + 100.0f };
		moveTask3.taskTime = 0.0f;
		moveTask3.destRadian = 0.0f;
		tmpvec.push_back(moveTask3);


		tmptask.tasks[i] = tmpvec;
	}

	dict.insert(make_pair(TEXT("Pattern_Straight"), tmptask));

	tmptask.key = TEXT("Pattern_Movearound");
	tmptask.tasks.resize(PATTERN_ENEMY_NUM);

	for (int i = 0; i < PATTERN_ENEMY_NUM; i++)
	{
		vector<Task> tmpvec;

		Task moveTask1;
		moveTask1.type = eTaskType::MOVE;
		moveTask1.dest = { 50.0f * i + 50.f , 200.0f };
		moveTask1.taskTime = 0.0f;
		moveTask1.destRadian = 0.0f;
		tmpvec.push_back(moveTask1);


		Task moveTask2;
		moveTask2.type = eTaskType::MOVEAROUND;
		moveTask2.dest = { 300.0f , 300.0f };
		moveTask2.taskTime = 0.0f;
		moveTask2.destRadian = DEG_TO_RAD(360);
		tmpvec.push_back(moveTask2);


		Task moveTask3;
		moveTask3.type = eTaskType::MOVE;
		moveTask3.dest = { 50.0f * i + 50.f , WINSIZE_Y + 100.0f };
		moveTask3.taskTime = 0.0f;
		moveTask3.destRadian = 0.0f;
		tmpvec.push_back(moveTask3);

		tmptask.tasks[i] = tmpvec;
	}

	dict.insert(make_pair(TEXT("Pattern_Movearound"), tmptask));

	tmptask.key = TEXT("Pattern_Sin");
	tmptask.tasks.resize(PATTERN_ENEMY_NUM);

	for (int i = 0; i < PATTERN_ENEMY_NUM; i++)
	{
		vector<Task> tmpvec;

		Task moveTask1;
		moveTask1.type = eTaskType::MOVESIN;
		moveTask1.dest = { WINSIZE_X / 2, WINSIZE_Y / 3 * 2 };
		moveTask1.taskTime = 0.0f;
		moveTask1.destRadian = 0.0f;
		tmpvec.push_back(moveTask1);


		Task moveTask2;
		moveTask2.type = eTaskType::MOVESIN;
		moveTask2.dest = { i >= 3 ? 0.0f : WINSIZE_X, WINSIZE_Y };
		moveTask2.taskTime = 0.0f;
		moveTask2.destRadian = 0.0f;
		tmpvec.push_back(moveTask2);

		tmptask.tasks[i] = tmpvec;
	}

	dict.insert(make_pair(TEXT("Pattern_Sin"), tmptask));



}

void EnemyManager::MakePatternEnemy(const wchar_t* key)
{
	auto it = dict.find(key);
	if (it == dict.end()) return;

	TaskType& pattern = it->second;

	for (int i = 0; i < PATTERN_ENEMY_NUM; i++)
	{

		planes.push_back(new Plane);
		planes.back()->Init(TEXT(ENEMY1_PATH), 300, Type::ENEMY);
		planes.back()->SetPos({ WINSIZE_X / 2, -(WINSIZE_Y / 3) });
		CollisionManager::GetInstance()->AddCollider(planes.back());

		vector<Task> tmp;
		if (i < pattern.tasks.size()) {

			for (auto& task : pattern.tasks[i]) {
				tmp.push_back(task);
			}

			planes.back()->SetTask(tmp);
		}

	}

}
