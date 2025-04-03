#include "ItemManager.h"
#include "PlayerManager.h"

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

	CreateItem({ (float)(rand() % 600) , (float)(rand() % 800)});
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
	// 랜덤으로 파워업, 폭탄, 메달 소환할 예정
	int randNum = rand() % 100;
	
	for (int i = 0; i < 30; i++)
	{
		if (!hoverItems[i]->GetActive())
		{
			if (randNum < 10)
			{
				hoverItems[i]->Init(Type::ITEM_HOVER_BOMB, TEXT(ITEM_HOVERBOMB_PATH), pos);
				break;
			}
			else if (randNum < 40 && randNum >= 10)
			{
				hoverItems[i]->Init(Type::ITEM_HOVER_POWERUP, TEXT(ITEM_HOVERPOWERUP_PATH),pos);
				break;
			}
			else
			{
				hoverItems[i]->Init(Type::ITEM_HOVER_MEDAL, TEXT(ITEM_HOVERMEDAL_PATH),pos);
				break;
			}


		}
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
