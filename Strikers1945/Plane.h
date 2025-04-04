#pragma once
#include "GameObject.h"
#include "MissileManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "ItemManager.h"
#include "CollisionManager.h"
#include "BackgroundManager.h"
#include "EffectManager.h"
#include <map>
#include "config.h"
#include "PlayerManager.h"
#include "Bomb.h"

class Plane: public GameObject
{
protected:
	static map<const wchar_t*, PlaneType> dict;

	bool				use;
	float				hitRenderTime;
	float				frameTime;

	PlayerNum			playerNum;

	float				location;
	FPOINT				missilePos;
	FPOINT				centerPos;
	float				absTime;
	PlaneRenderType		renderType;
	int					maxFrameX;
	int					currFrameX;
	int					currFrameY;

	vector<Task>*		path;
	TaskType			pathType;

	float				pathRadian;
	float				pathComplex;
	float				startRadian;
	float				goalRadian;
	float				pathRadius;

	FPOINT				curveContolPos;
	FPOINT				startPos;
	float				curveVar;

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
	void MoveAlongPathMoveCurve();
	
public:
	void Init(void);
	void Release(void);
	void Update(void);
	void Render(HDC hdc);

	virtual void Init(const wchar_t* key, float startPos, Type type);
	virtual void Shoot(void);
	void UpgradeMissile();
	void Move(FPOINT dir);
	void OnDamage(int damage);
	void DropBomb();
	
	Bomb* GetBombRef(void);
	PlayerNum GetPlayerNum();


	GameObjectStates GetState(void);
	void SetPath(vector<Task>* path);
	bool CanIUseIt(void);
	void SetPlayerNum(PlayerNum playerNum);

	Plane& operator=(const PlaneType& target);
};
