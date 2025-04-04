#pragma once
#include "config.h"
#include <map>

class Image;
class Missile;
class MissileManager
{
private:
	static map<const wchar_t*, MissileType> missileDict;

	Image* missileImage;
	float missileSpeed;
	float shootRate;	
	float reloadRate;
	int	  missileAmount;
	int missileDamage;
	RECT size;
	Type type;
	vector<Missile*> missiles;
	FPOINT dir;
	float elapsedTime;
	bool isReloading;
	float reloadTime;
	int missileCount;
	MissileKind missileKind;
	wchar_t* upgradeKey;

	const wchar_t*	nextMissile;
	int				maxFrameX;

	void FillDict();
public:
	void Init();
	void Init(const wchar_t* key, Type type);
	void Update();
	void Render(HDC hdc);
	void Release();

	void Shoot(FPOINT pos);
	void MissileDirSetting(FPOINT pos);
	void Upgrade(void);
};