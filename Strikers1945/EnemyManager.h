#pragma once
#include "config.h"
#include "Singleton.h"

class Plane;
class EnemyManager: public Singleton<EnemyManager>
{
private:
	//vector<struct Script> scripts;
	size_t scriptIndex;
	vector<Plane*> planes;

public:
	
	void Init(); 
	void Release();
	void Update();
	void Render(HDC hdc);

	bool DeployEnemy();

};

