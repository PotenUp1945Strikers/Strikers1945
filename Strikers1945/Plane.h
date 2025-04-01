#pragma once
#include "GameObject.h"
#include "MissileManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include <map>
#include "config.h"

class Plane
{
	
private:
	static map<const wchar_t*, PlaneType> dict;
	RECT	bodySize;
	RECT	wingSize;
	FPOINT	wingPos;
	MissileManager* launcher;

	bool OutOfWindow(void);
	bool InOfWindow(void);
	
public:
	void Init(void);
	void Release(void);
	void Update(void);
	void Render(HDC hdc);

	void FillDict(void);
	void Init(const wchar_t* key);
	Colider GetColider(void);
	void Shoot(void);
	void UpgradeMissile();
	void Move(FPOINT dir);

	Plane& operator=(const PlaneType& target);
};
