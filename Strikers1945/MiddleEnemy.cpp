#include "MiddleEnemy.h"

void MiddleEnemy::Init()
{
	this->Plane::Init();
	if (!left)
		left = new MissileManager;
	left->Init();
}

void MiddleEnemy::Init(const wchar_t* key, float startPos, Type type)
{
	this->Plane::Init(key, startPos, type);
	auto var = dict.find(key);
	if (!left)
		left = new MissileManager;
	left->Init();
	if (var != dict.end())
		left->Init(var->second.missileType, Type::ENEMY_BULLET);
}

void MiddleEnemy::Release(void)
{
	this->Plane::Release();
	if (left)
	{
		left->Release();
		delete left;
		left = nullptr;
	}
}

void MiddleEnemy::Update(void)
{
	this->Plane::Update();
	if (left)
		left->Update();
}

void MiddleEnemy::Render(HDC hdc)
{
	this->Plane::Render(hdc);
	if (left)
		left->Render(hdc);
}

void MiddleEnemy::OnDamage(int damage)
{
	health -= damage;
	currFrameY = 1;
	if (health <= 0)
	{
	
		for (int i = 0; i < 10; i++)
		{
			ItemManager::GetInstance()->CreateItem(pos);

			EffectManager::GetInstance()->OnEffect(TEXT(EFFECT3_PATH), { (rand() % 120 - 60) + pos.x, (rand() % 120 - 60) + pos.y });
		}
		active = false;
		render = false;
		use = true;
		state = GameObjectStates::Die;
	}
}

void MiddleEnemy::Shoot(void)
{
	if (active && launcher)
		launcher->Shoot({ pos.x + missilePos.x, pos.y + missilePos.y });
	if (active && left)
		left->Shoot({ pos.x - missilePos.x, pos.y + missilePos.y });
}
