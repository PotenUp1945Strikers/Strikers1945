#pragma once
#include "config.h"
#include "Singleton.h"
#include <map>

class Plane;
class Tank;
class MiddleEnemy;
class Boss;
class EnemyManager: public Singleton<EnemyManager>
{
private:
	map<const wchar_t*, vector<Task>*>	dict;
	vector<StageScript>					level;
	vector<Task>						tasks;
	size_t								currLev;
	vector<Plane*>						planes;
	vector<Tank*>						tanks;
	vector<MiddleEnemy*>				middles;
	Boss*								boss;

	void CreateLevel(void);
	void FillDict(void);

	void PutEnemy(void);
public:
	
	void Init(); 
	void Release();
	void Update();
	void Render(HDC hdc);





};

