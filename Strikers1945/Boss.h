#pragma once
#include "Plane.h"
#include "GameObject.h"
#include "config.h"

class Boss: public Plane
{
private:
	MissileManager* left;
	MissileManager* right;
	FPOINT			leftPos;
	FPOINT			rightPos;

public:
	void Init(void);
	void Init(const wchar_t* key, float startPos, Type type);
	void Release(void);
	void Update(void);
	void Render(HDC hdc);

	void OnDamage(int damage);
	void Shoot(void);
};

