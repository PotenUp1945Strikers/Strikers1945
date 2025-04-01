#pragma once
#include "config.h"
#include <vector>

class Image;
class Missile;
class MissileManager
{
private:
	Image* missileImage;
	float missileSpeed;
	float shootRate;
	int missileDamage;
	RECT size;
	Type type;
	vector<Missile*> missiles;
	FPOINT dir;
	float elapsedTime;
public:
	void Init();
	void Init(const wchar_t* key, Type type);
	void Update();
	void Render(HDC hdc);
	void Release();

	void Shoot(FPOINT vec);

};