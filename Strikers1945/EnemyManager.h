#pragma once
#include "config.h"
#include "Singleton.h"

class Plane;
class EnemyManager: public Singleton<EnemyManager>
{
private:

	static map<const wchar_t*, TaskType> dict;
	//vector<struct Script> scripts;
	vector<Task> tasks;
	size_t scriptIndex;
	vector<Plane*> planes;

public:
	
	void Init(); 
	void Release();
	void Update();
	void Render(HDC hdc);

	bool DeployEnemy();

	void FillDict(void);

	void MakePatternEnemy(const wchar_t* key);

	void MakeStraightPatternEnemy();
	void MakeAroundPatternEnemy();
	void MakeSinPatternEnemy();

};

