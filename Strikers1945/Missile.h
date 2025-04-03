#pragma once
#include "GameObject.h"

class Image;
class Missile : public GameObject
{
private:
public:
	void Init() override;
	void Init(Type type);
	void Init(FPOINT dir, float speed, Image* image, RECT size, int health = 1);
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;
	void OnDamage() override;
	//RECT GetCollider();

	void Shoot(FPOINT pos, FPOINT dir);
	
private:
	bool outOfWindow();
};
