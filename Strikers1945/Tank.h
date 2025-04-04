#pragma once
#include "Plane.h"
#include "BackgroundManager.h"
#include "PlayerManager.h"

class Tank: public Plane
{
private:
	float oldLocation;
	float barrelRadian;

	void rotateBarrel(void);

public:
	void Update(void);
	void Render(HDC hdc);
	void Shoot(void);
	void Stay(void);

	void OnDamage(int damage);
};

