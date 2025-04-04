#include "ItemManager.h"
#include "PlayerManager.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "ScoreManager.h"
#include "Bomb.h"
#include "HoverItem.h"

void ItemManager::Init()
{
	bombing = false;

	//hoverItems.reserve(30);
	if (hoverItems.empty())
	{
		hoverItems.resize(50);
		for (int i = 0; i < 50; i++)
		{
			hoverItems[i] = new HoverItem;
			hoverItems[i]->Init();
		}
		srand(time(NULL));
	}
	else
	{
		for (int i = 0; i < 50; i++)
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
	// �������� �Ŀ���, ��ź, �޴� ��ȯ�� ����
	for (int i = 0; i < 50; i++)
	{
		int randNum = rand() % 100;
		if (!hoverItems[i]->GetActive())
		{
			if (randNum < 7)
			{
				hoverItems[i]->Init(Type::ITEM_HOVER_BOMB, TEXT(ITEM_HOVERBOMB_PATH), pos);
				CollisionManager::GetInstance()->AddCollider(hoverItems[i]);
				break;
			}
			else if (randNum < 37 )
			{
				hoverItems[i]->Init(Type::ITEM_HOVER_POWERUP, TEXT(ITEM_HOVERPOWERUP_PATH),pos);
				CollisionManager::GetInstance()->AddCollider(hoverItems[i]);

				break;
			}
			else if (randNum < 77)
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
		ScoreManager::GetInstance()->AddScore(static_cast<Plane*>(owner)->GetPlayerNum(),10);
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
