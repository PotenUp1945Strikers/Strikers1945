#pragma once
#include "config.h"
#include <vector>

class Image;
class Missile;
class MissileManager
{
private:
	Image* bulletImage;
	float bulletSpeed;
	float shootRate;
	int bulletDamage;
	RECT size;

	vector<Missile*> missiles;
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void Shoot(FPOINT vec);

};