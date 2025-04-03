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
	hoverItems.resize(30);
	for (int i = 0; i < 30; i++)
	{
		hoverItems[i] = new HoverItem;
		hoverItems[i]->Init();
	}
	srand(time(NULL));
}

void ItemManager::Release()
{
	hoverItems.clear();
}

void ItemManager::Update()
{
	//if (tmp && tmp->GetActive() && tmp->GetRender())
	//	tmp->Update();
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
	/*if (tmp && tmp->GetActive() && tmp->GetRender())
		tmp->Render(hdc);*/
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
	int randNum = rand() % 100;
	
	for (int i = 0; i < 30; i++)
	{
		if (!hoverItems[i]->GetActive())
		{
			if (randNum > 0)
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

void ItemManager::OnGainItem(GameObject* object)
{

	switch (object->GetType())
	{
	case Type::ITEM_HOVER_BOMB:
			PlayerManager::GetInstance()->InCreasePlayer1Bomb();
			UIManager::GetInstance()->SetBomb(PlayerManager::GetInstance()->GetPlayer1bomb());
			break;
	case Type::ITEM_HOVER_POWERUP:
			// TODO : POWERUP IN PLANE
		break;
	case Type::ITEM_HOVER_MEDAL:
		// TODO : Score ++
		break;
	}

}

//void ItemManager::RemoveItem(HoverItem* item)
//{
//	if (!item->GetActive() && !item->GetRender())
//	{
//		hoverItems.erase(
//			std::remove(hoverItems.begin(), hoverItems.end(), item),
//			hoverItems.end()
//		);
//		delete item;
//	}
//}


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
