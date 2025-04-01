#pragma once
#include "config.h"

class GameObject;
class Collider
{
private:
	CollisionType type;
	FPOINT pos; // �浹ü �簢�� ����
	float size;
	RECT collisionRC;
	GameObject* owner;

public:
	void Init(GameObject* owner, CollisionType type, FPOINT pos, float size);
	void Update();
	void Render(HDC hdc);
	void Release();
	
	bool IsColliding(const Collider& other);
	CollisionType GetType() { return type; }
};

