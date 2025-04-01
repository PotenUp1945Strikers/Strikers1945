#pragma once
#include "GameObject.h"

class Image;
class Missile : public GameObject
{
private:
public:
	void Init() override;
	void Init(Type type, FPOINT dir, FPOINT pos, float speed, Image* image);
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;
	void OnDamage() override;
	//RECT GetCollider();
	
private:
	bool outOfWindow();
};
