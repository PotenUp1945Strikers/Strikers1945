#pragma once
#include "config.h"

class EnemyManager
{
private:
	vector<struct Script> scripts;
	size_t scriptIndex;
	vector<class Plane*> planes;

public:
	
	void Init(); 
	void Release();
	void Update();
	void Render(HDC hdc);

	bool DeployEnemy();

};

