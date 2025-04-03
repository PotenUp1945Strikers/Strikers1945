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
		player1->SetPlayerNum(PlayerNum::PLAYER1);
		CollisionManager::GetInstance()->AddCollider(player1);
	}
	else 
		player1->Init(TEXT(PLAYER_PATH), 0, Type::PLAYER);

	player1->SetPos({ WINSIZE_X / 2, WINSIZE_Y + 100});
	player1->SetPath(dict[TEXT(PLAYER_START_MOVE)]);
	player1Life = 1;
	player1Bomb = 2;
	UIManager::GetInstance()->SetPlayer1Life(player1Life);
	UIManager::GetInstance()->SetPlayer1Bomb(player1Bomb);


	if (!player2)
	{
		player2 = new Plane;

		player2->Init(TEXT(PLAYER_PATH), 0, Type::PLAYER);
		player2->SetPlayerNum(PlayerNum::PLAYER2);
		CollisionManager::GetInstance()->AddCollider(player2);
	}
	else
		player2->Init(TEXT(PLAYER_PATH), 0, Type::PLAYER);

	player2->SetPos({ WINSIZE_X / 2, WINSIZE_Y + 100 });
	player2->SetPath(dict[TEXT(PLAYER_START_MOVE)]);
	player2Life = 1;
	player2Bomb = 2;
	UIManager::GetInstance()->SetPlayer2Life(player2Life);
	UIManager::GetInstance()->SetPlayer2Bomb(player2Bomb);
}

void PlayerManager::Update(void)
{
	FPOINT player1Pos = { 0, };
	KeyManager* km = KeyManager::GetInstance();

	if (km->IsStayKeyDown('W'))
		player1Pos.y += -1;
	if (km->IsStayKeyDown('S'))
		player1Pos.y += 1;
	if (km->IsStayKeyDown('A'))
		player1Pos.x += -1;
	if (km->IsStayKeyDown('D'))
		player1Pos.x += 1;
	if (km->IsStayKeyDown('B'))
		player1->Shoot();
	if (km->IsOnceKeyDown('N'))
		LaunchBomb(PlayerNum::PLAYER1);

	FPOINT player2Pos = { 0, };

	if (km->IsStayKeyDown(VK_NUMPAD8))
		player2Pos.y += -1;
	if (km->IsStayKeyDown(VK_NUMPAD5))
		player2Pos.y += 1;
	if (km->IsStayKeyDown(VK_NUMPAD4))
		player2Pos.x += -1;
	if (km->IsStayKeyDown(VK_NUMPAD6))
		player2Pos.x += 1;
	if (km->IsStayKeyDown(VK_OEM_4))
		player2->Shoot();
	if (km->IsOnceKeyDown(VK_OEM_6))
		LaunchBomb(PlayerNum::PLAYER2);


	player1->Move(player1Pos);
	player1->Update();

	player2->Move(player2Pos);
	player2->Update();
}

void PlayerManager::Render(HDC hdc)
{
	if (player1)
		player1->Render(hdc);
	if (player2)
		player2->Render(hdc);
}

void PlayerManager::Release(void)
{
	if (player1)
	{
		player1->Release();
		delete player1;
		player1 = nullptr;
	}
	if (player2)
	{
		player2->Release();
		delete player2;
		player2 = nullptr;
	}
}



int PlayerManager::GetPlayer1bomb()
{
	return player1Bomb;
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

int PlayerManager::GetPlayer2bomb()
{
	return player2Bomb;
}

bool PlayerManager::ReducePlayer2Bomb()
{
	if (this->player2Bomb > 0)
	{
		this->player2Bomb -= 1;
		return true;
	}
	return false;
}

bool PlayerManager::InCreasePlayer2Bomb()
{
	if (this->player2Bomb < 2 && this->player2Bomb >= 0)
	{
		this->player2Bomb += 1;
		return true;
	}
	return false;
}




bool PlayerManager::Revive(void)
{
	if (player1 && player1->GetState() == GameObjectStates::Die )
	{
		if (player1Life)
		{
			UIManager::GetInstance()->SetPlayer1Life(--player1Life);

			if (player1Life > 0) return true;
		}
	}

	if (player2 && player2->GetState() == GameObjectStates::Die)
	{
		if (player2Life)
		{
			UIManager::GetInstance()->SetPlayer2Life(--player2Life);
			
			if (player2Life > 0) return true;
		}
	}

	if (((player1 && !player2) && !player1Life) ||
		((player2 && !player1) && !player2Life) ||
		((player1 && player2) && !player1Life && !player2Life))
		EventHandler::GetInstance()->GameOver();

	return false;
}

void PlayerManager::LaunchBomb(PlayerNum playerNum)
{
	switch (playerNum)
	{
	case PlayerNum::PLAYER1:
		if (!ItemManager::GetInstance()->GetBombing() && player1Bomb != 0)
		{
			
			player1->DropBomb();
			UIManager::GetInstance()->SetPlayer1Bomb(--player1Bomb);
			ItemManager::GetInstance()->OnDropButton();
		}
		break;
	case PlayerNum::PLAYER2:
		if (!ItemManager::GetInstance()->GetBombing() && player2Bomb != 0)
		{
			player2->DropBomb();
			UIManager::GetInstance()->SetPlayer2Bomb(--player2Bomb);
			ItemManager::GetInstance()->OnDropButton();
		}
		break;
	}
	
}

void PlayerManager::LaunchBombEnd()
{
	player1->GetBombRef()->Init();
	player2->GetBombRef()->Init();
}

