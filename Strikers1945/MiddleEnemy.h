#pragma once
#include "Plane.h"

class MiddleEnemy: public Plane
{
private:
	MissileManager* left;

public:
	void Init(void);
	void Init(const wchar_t* key, float startPos, Type type);
	void Release(void);
	void Update(void);
	void Render(HDC hdc);

	void OnDamage(int damage);
	void Shoot(void);
};

