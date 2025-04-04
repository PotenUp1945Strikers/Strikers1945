#include "Boss.h"

void Boss::Init(void)
{
	this->Plane::Init();
	if (!left)
		left = new MissileManager;
	if (!right)
		right = new MissileManager;
	left->Init();
	right->Init();
}

void Boss::Init(const wchar_t* key, float startPos, Type type)
{
	if (dict.find(key) == dict.end())
		return;
	this->Plane::Init(key, startPos, type);
	if (!left)
		left = new MissileManager;
	if (!right)
	right = new MissileManager;
	left->Init(TEXT(AROUND_BULLET_PATH), Type::ENEMY_BULLET);
	right->Init(TEXT(AROUND_BULLET_PATH), Type::ENEMY_BULLET);
	leftPos = { -169, 182 };
	rightPos = { 138, 182 };
}

void Boss::Release(void)
{
	this->Plane::Release();
	if (left)
	{
		left->Release();
		delete left;
		left = nullptr;
	}
	if (right)
	{
		right->Release();
		delete right;
		right = nullptr;
	}
}

void Boss::Update(void)
{
	this->Plane::Update();
	if (left)
		left->Update();
	if (right)
		right->Update();
}

void Boss::Render(HDC hdc)
{
	this->Plane::Render(hdc);
	if (left)
		left->Render(hdc);
	if (right)
		right->Render(hdc);
}

void Boss::OnDamage(int damage)
{
	if (damageTickTime >= 0)
		return;
	else
		damageTickTime = HIT_TICK_TIME;

	health -= damage;
	currFrameY = 1;
	if (health <= 0)
	{
		for (int i = 0; i < 10; i++)
		{

			ItemManager::GetInstance()->CreateItem(pos);
			EffectManager::GetInstance()->OnEffect(TEXT(EFFECT3_PATH), { (rand() % 500 - 250) + pos.x, (rand() % 500 - 250) + pos.y });
			EffectManager::GetInstance()->OnEffect(TEXT(EFFECT4_PATH), { (rand() % 500 - 250) + pos.x, (rand() % 500 - 250) + pos.y });
		}
		active = false;
		render = false;
		use = true;
		state = GameObjectStates::Die;
		EventHandler::GetInstance()->GameClear();
	}
}

void Boss::Shoot(void)
{
	if (active && launcher)
		launcher->Shoot({ pos.x + missilePos.x, pos.y + missilePos.y });
	if (active && left)
		left->Shoot({ pos.x + leftPos.x, pos.y + leftPos.y });
	if (active && right)
		right->Shoot({ pos.x + rightPos.x, pos.y + rightPos.y });
}
