#pragma once
#include "GameObject.h"
#include "MissileManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "ItemManager.h"
#include "BackgroundManager.h"
#include <map>
#include "config.h"
#include "PlayerManager.h"
#include "Bomb.h"

class Plane: public GameObject
{
private:
	static map<const wchar_t*, PlaneType> dict;

	float				location;
	float				absTime;

	vector<Task>*		path;
	TaskType			pathType;

	float				pathRadian;
	float				pathComplex;
	float				startRadian;
	float				goalRadian;
	float				pathRadius;

	size_t				currPath;
	float				taskTime;
	FPOINT				goal;

	GameObjectStates	state;

	MissileManager*		launcher;
	Bomb*				bomb;

	
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

	bool MoveAlongPath(void);
	void MoveAlongPathStop();
	void MoveAlongPathMove();
	void MoveAlongPathMoveAround();
	void MoveAlongPathMoveSin();
	
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
	void DropBomb();
	
	Bomb* GetBombRef(void);


	GameObjectStates GetState(void);
	void SetPath(vector<Task>* path);

	Plane& operator=(const PlaneType& target);
};
