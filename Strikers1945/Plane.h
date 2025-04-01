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
	GameObjectStates	state;
	MissileManager*		launcher;
	
	void UpdateWait(void);
	void UpdateBorn(void);
	void UpdateAlive(void);

	bool OutOfWindow(void);
	bool InOfWindow(void);
	
public:
	void Init(void);
	void Release(void);
	void Update(void);
	void Render(HDC hdc);

	void FillDict(void);
	void Init(const wchar_t* key, float startPos, Type type);
	void Shoot(void);
	void UpgradeMissile();
	void Move(FPOINT dir);
	void OnDamage(void);

	Plane& operator=(const PlaneType& target);
};
