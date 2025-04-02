#include "ItemManager.h"
#include "PlayerManager.h"

#include "Bomb.h"

void ItemManager::Init()
{
	bomb = new Bomb;
	bomb->Init();
	
	bombing = false;

}

void ItemManager::Release()
{
	delete bomb;
}

void ItemManager::Update()
{
	if (bomb && bomb->GetActive() && bomb->GetRender())
		bomb->Update();
}

void ItemManager::Render(HDC hdc)
{
	if (bomb && bomb->GetActive() && bomb->GetRender())
		bomb->Render(hdc);

}

void ItemManager::OnDropButton()
{
	if (!bombing) 
	{

		UIManager::GetInstance()->SetBomb(PlayerManager::GetInstance()->GetPlayer1Bomb()-1);
		bombing = true;
		bomb->SetActive(true);
		bomb->SetRender(true);
	}
}

void ItemManager::OnDropEnd()
{

	bombing = false;
	
	PlayerManager::GetInstance()->Onplayer1Bomb();
	bomb->Init();
}

bool ItemManager::GetBombing()
{
	return bombing;
}
