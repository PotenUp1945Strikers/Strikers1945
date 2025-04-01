#include "PlayerManager.h"

void PlayerManager::Init(void)
{
	if (!player1)
		player1 = new Plane;
	player1->Init(TEXT(PLAYER_PATH));
	player1Life = 3;
	player1Bomb = 2;
	CollisionManager::GetInstance()->AddCollider(player1, Type::PLAYER);
}

void PlayerManager::Update(void)
{
	FPOINT player1Pos = { 0, };
	KeyManager* km = KeyManager::GetInstance();

	if (km->IsStayKeyDown(VK_UP))
		player1Pos.y += 1;
	if (km->IsStayKeyDown(VK_DOWN))
		player1Pos.y += -1;
	if (km->IsStayKeyDown(VK_LEFT))
		player1Pos.x += -1;
	if (km->IsStayKeyDown(VK_RIGHT))
		player1Pos.x += 1;
	if (km->IsStayKeyDown('Z'))
		player1->Shoot();

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

void PlayerManager::LaunchBomb(void)
{
}
