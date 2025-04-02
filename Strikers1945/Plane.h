#pragma once
#include "GameObject.h"
#include "MissileManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "BackgroundManager.h"
#include <map>
#include "config.h"

class Plane: public GameObject
{
private:
	static map<const wchar_t*, PlaneType> dict;

	float				location;
	vector<FPOINT>*		path;
	size_t				currPath;
	FPOINT				goal;
	GameObjectStates	state;
	MissileManager*		launcher;
	
	void FillDict(void);

	void UpdatePlayer(void);
	void UpdateEnemy(void);

	void UpdateWait(void);
	void UpdatePlayerBorn(void);
	void UpdatePlayerAlive(void);
	void UpdateEnemyBorn(void);
	void UpdateEnemyAlive(void);

	bool OutOfWindow(void);
	bool InOfWindow(void);

	void SetGoal(void);
	void MoveAlongPath(void);
	
public:
	void Init(void);
	void Release(void);
	void Update(void);
	void Render(HDC hdc);

	void Init(const wchar_t* key, float startPos, Type type);
	void Shoot(void);
	void UpgradeMissile();
	void Move(FPOINT dir);
	void OnDamage(void);

	void SetPath(vector<FPOINT>* path);

	Plane& operator=(const PlaneType& target);
};
