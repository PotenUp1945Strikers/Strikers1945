#pragma once
#include "config.h"
#include "Singleton.h"
#include <map>

class Plane;
class EnemyManager: public Singleton<EnemyManager>
{
private:
	map<const wchar_t*, vector<Task>*>	dict;
	vector<StageScript>					level;
	vector<Task>						tasks;
	size_t								currLev;
	vector<Plane*>						planes;

	void CreateLevel(void);
	void FillDict(void);

	void PutEnemy(void);
public:
	
	void Init(); 
	void Release();
	void Update();
	void Render(HDC hdc);

	bool DeployEnemy();


	void MakePatternEnemy(const wchar_t* key);


};

