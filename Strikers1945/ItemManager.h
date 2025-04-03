#pragma once
#include "config.h"
#include "Singleton.h"
#include "GameObject.h"

class Bomb;
class ItemManager : public Singleton<ItemManager>
{
private:
	//vector<GameObject>* items;

	Bomb* bomb;
	bool bombing;


public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void OnDropButton();
	void OnDropEnd();

	bool GetBombing();

};

