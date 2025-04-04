#include "ItemManager.h"
#include "PlayerManager.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "Bomb.h"
#include "HoverItem.h"

void ItemManager::Init()
{
	bombing = false;

	//hoverItems.reserve(30);
	if (hoverItems.empty())
	{
		hoverItems.resize(30);
		for (int i = 0; i < 30; i++)
		{
			hoverItems[i] = new HoverItem;
			hoverItems[i]->Init();
		}
		srand(time(NULL));
	}
	else
	{
		for (int i = 0; i < 30; i++)
			hoverItems[i]->Init();
	}
}

void ItemManager::Release()
{
	hoverItems.clear();
}

void ItemManager::Update()
{
	for (auto& i : hoverItems)
	{
		if (i->GetActive() && i->GetRender())
		{
			i->Update();
		}
	}

	//CreateItem({ (float)(rand() % 600) , (float)(rand() % 800)});
}

void ItemManager::Render(HDC hdc)
{
	for (auto& i : hoverItems)
	{
		if (i->GetActive() && i->GetRender())
		{
			i->Render(hdc);
		}
	}

}

void ItemManager::CreateItem(FPOINT pos)
{
	// 랜덤으로 파워업, 폭탄, 메달 소환할 예정
	int randNum = rand() % 100;
	
	for (int i = 0; i < 30; i++)
	{
		if (!hoverItems[i]->GetActive())
		{
			if (randNum < 10)
			{
				hoverItems[i]->Init(Type::ITEM_HOVER_BOMB, TEXT(ITEM_HOVERBOMB_PATH), pos);
				CollisionManager::GetInstance()->AddCollider(hoverItems[i]);
				break;
			}
			else if (randNum < 25 )
			{
				hoverItems[i]->Init(Type::ITEM_HOVER_POWERUP, TEXT(ITEM_HOVERPOWERUP_PATH),pos);
				CollisionManager::GetInstance()->AddCollider(hoverItems[i]);

				break;
			}
			else if (randNum < 60)
			{
				hoverItems[i]->Init(Type::ITEM_HOVER_MEDAL, TEXT(ITEM_HOVERMEDAL_PATH),pos);
				CollisionManager::GetInstance()->AddCollider(hoverItems[i]);

				break;
			}


		}
	}


}

void ItemManager::OnGainItem(GameObject* gainedobject, GameObject* owner)
{

	switch (gainedobject->GetType())
	{
	case Type::ITEM_HOVER_BOMB:

		if (static_cast<Plane*>(owner)->GetPlayerNum() == PlayerNum::PLAYER1)
		{
			PlayerManager::GetInstance()->InCreasePlayer1Bomb();
			UIManager::GetInstance()->SetPlayer1Bomb(PlayerManager::GetInstance()->GetPlayer1bomb());
		}
		else if (static_cast<Plane*>(owner)->GetPlayerNum() == PlayerNum::PLAYER2)
		{
			PlayerManager::GetInstance()->InCreasePlayer2Bomb();
			UIManager::GetInstance()->SetPlayer2Bomb(PlayerManager::GetInstance()->GetPlayer2bomb());
		}
			
			break;
	case Type::ITEM_HOVER_POWERUP:
			// TODO : POWERUP IN PLANE
		break;
	case Type::ITEM_HOVER_MEDAL:
		// TODO : Score ++
		break;
	}

}

void ItemManager::OnDropButton()
{
	if (!bombing)
	{
		bombing = true;
	}
}

void ItemManager::OnDropEnd()
{
	bombing = false;
	PlayerManager::GetInstance()->LaunchBombEnd();
}

bool ItemManager::GetBombing()
{
	return bombing;
}
