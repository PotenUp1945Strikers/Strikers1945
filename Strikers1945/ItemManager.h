#pragma once
#include "config.h"
#include "Singleton.h"
#include "GameObject.h"

class Bomb;
class HoverItem;
class ItemManager : public Singleton<ItemManager>
{
private:
	bool bombing;
	HoverItem* tmp;
	
	vector<HoverItem*> hoverItems;


public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void CreateItem(FPOINT pos);
	//void RemoveItem(HoverItem* item);
	
	void OnGainItem(GameObject* object);


	void OnDropButton();
	void OnDropEnd();

	bool GetBombing();

};

