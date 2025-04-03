#include "PlayerManager.h"
#include "ItemManager.h"
#include "UIManager.h"

map<const wchar_t*, vector<Task>*> PlayerManager::dict;

void PlayerManager::FillDict(void)
{
	vector<Task>* start = new vector<Task>;

	Task task;
	task.type = TaskType::MOVE;
	task.dest = { 0 , -(WINSIZE_Y / 3) };
	task.taskTime = 0.0f;
	task.destRadian = 0.0f;
	start->push_back(task);

	dict.insert(make_pair(TEXT(PLAYER_START_MOVE), start));

	vector<Task>* end = new vector<Task>;

	task.type = TaskType::MOVE;
	task.dest = { 0 , -WINSIZE_Y };
	task.taskTime = 0.0f;
	task.destRadian = 0.0f;
	end->push_back(task);

	dict.insert(make_pair(TEXT(PLAYER_START_MOVE), end));
}

void PlayerManager::Init(void)
{
	if (dict.empty())
		FillDict();
	if (!player1)
	{
		player1 = new Plane;
		player1->Init(TEXT(PLAYER_PATH), 0, Type::PLAYER);
		CollisionManager::GetInstance()->AddCollider(player1);
	}
	else 
		player1->Init(TEXT(PLAYER_PATH), 0, Type::PLAYER);

	player1->SetPos({ WINSIZE_X / 2, WINSIZE_Y + 100});
	player1->SetPath(dict[TEXT(PLAYER_START_MOVE)]);
	player1Life = 3;
	player1Bomb = 2;
	UIManager::GetInstance()->SetLife(player1Life);
	UIManager::GetInstance()->SetBomb(player1Bomb);
}

void PlayerManager::Update(void)
{
	FPOINT player1Pos = { 0, };
	KeyManager* km = KeyManager::GetInstance();

	if (km->IsStayKeyDown(VK_UP))
		player1Pos.y += -1;
	if (km->IsStayKeyDown(VK_DOWN))
		player1Pos.y += 1;
	if (km->IsStayKeyDown(VK_LEFT))
		player1Pos.x += -1;
	if (km->IsStayKeyDown(VK_RIGHT))
		player1Pos.x += 1;
	if (km->IsStayKeyDown('Z'))
		player1->Shoot();
	if (km->IsOnceKeyDown('X'))
		LaunchBomb(1);

	player1->Move(player1Pos);
	player1->Update();
}

void PlayerManager::Render(HDC hdc)
{
	if (player1)
		player1->Render(hdc);
}

void PlayerManager::Release(void)
{
	if (player1)
	{
		player1->Release();
		delete player1;
		player1 = nullptr;
	}
}




bool PlayerManager::ReducePlayer1Bomb()
{
	if (this->player1Bomb > 0)
	{
		this->player1Bomb -= 1;
		return true;
	}
	return false;
}

bool PlayerManager::InCreasePlayer1Bomb()
{
	if (this->player1Bomb < 2 && this->player1Bomb >= 0)
	{
		this->player1Bomb += 1;
		return true;
	}
	return false;
}




bool PlayerManager::Revive(void)
{
	if (player1 && player1->GetState() == GameObjectStates::Die)
	{
		if (player1Life)
		{
			UIManager::GetInstance()->SetLife(--player1Life);
			return true;
		}
	}

	if (player2 && player2->GetState() == GameObjectStates::Die)
	{
		if (player2Life)
		{
			UIManager::GetInstance()->SetLife(--player2Life);
			return true;
		}
	}

	if (((player1 && !player2) && !player1Life) ||
		((player2 && !player1) && !player2Life) ||
		((player1 && player2) && !player1Life && !player2Life))
		EventHandler::GetInstance()->GameOver();
	return false;
}

FPOINT PlayerManager::GetPlayer1Pos(void)
{
	if (player1)
		return player1->GetPos();
	return { 0, 0 };
}

void PlayerManager::LaunchBomb(int playerNum)
{
	switch (playerNum)
	{
	case 1:
		if (!ItemManager::GetInstance()->GetBombing() && player1Bomb != 0)
		{
			
			player1Bomb -= 1;
			player1->DropBomb();
			UIManager::GetInstance()->SetBomb(player1Bomb);
			ItemManager::GetInstance()->OnDropButton();
		}
		break;
	case 2:
		if (!ItemManager::GetInstance()->GetBombing() && player2Bomb != 0)
		{
			player2Bomb -= 1;
			player2->DropBomb();
		}
		break;
	}
	
}

void PlayerManager::LaunchBombEnd()
{
	player1->GetBombRef()->Init();
	//player2->GetBombRef()->Init();
}

int PlayerManager::GetPlayer1bomb()
{
	return player1Bomb;
}
