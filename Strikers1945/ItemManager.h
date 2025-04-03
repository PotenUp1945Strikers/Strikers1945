#pragma once
#include "config.h"
#include "Singleton.h"
#include "GameObject.h"

class Bomb;
class HoverItem;
class ItemManager : public Singleton<ItemManager>
{
private:
	//vector<GameObject>* items;

	bool bombing;

	HoverItem* tmp;


public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void OnDropButton();
	void OnDropEnd();

	bool GetBombing();

};

