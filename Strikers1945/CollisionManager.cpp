#include "CollisionManager.h"
#include "Collider.h"
#include "CommonFunction.h"
#include "GameObject.h"
#include "Missile.h"
#include "Plane.h"

void CollisionManager::Init()
{
	playerColliders = {};
	playerMissileColliders = {};
	enemyColliders = {};
	enemyMissileColliders = {};
}

void CollisionManager::Update()
{
	checkCollisions();
}

void CollisionManager::Render(HDC hdc)
{
	renderColliders(hdc, playerColliders);
	renderColliders(hdc, enemyColliders);
	renderColliders(hdc, playerMissileColliders);
	renderColliders(hdc, enemyMissileColliders);
}

void CollisionManager::Release()
{
	playerColliders.clear();
	playerMissileColliders.clear();
	enemyColliders.clear();
	enemyMissileColliders.clear();
}

void CollisionManager::checkCollisions()
{
	// 플레이어 - 적 총알
	for (auto& player : playerColliders)
	{
		if (player->GetActive() == false) continue;
		for (auto& enemyBullet : enemyMissileColliders)
		{
			if (enemyBullet->GetActive() == false) continue;
			if (isColliding(player, enemyBullet))
			{
				player->OnDamage();
				enemyBullet->OnDamage();
			}
		}
	}

	// 적 - 플레이어 총알
	for (auto& enemy : enemyColliders)
	{
		if (enemy->GetActive() == false) continue;
		for (auto& playerBullet : playerMissileColliders)
		{
			if (playerBullet->GetActive() == false) continue;
			if (isColliding(enemy, playerBullet))
			{
				// 적 데미지
				enemy->OnDamage();
				playerBullet->OnDamage();
			}
		}
	}
}
template<typename T>
void CollisionManager::renderColliders(HDC hdc, vector<T*>& gameObjects)
{
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetActive() == false || gameObject->GetRender() == false) continue;
		RECT rc = gameObject->GetCollider();
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}
}
void CollisionManager::AddCollider(GameObject* gameObject)
{
	switch (gameObject->GetType())
	{
	case Type::PLAYER:
		playerColliders.push_back(dynamic_cast<Plane*>(gameObject));
		break;
	case Type::ENEMY:
		enemyColliders.push_back(dynamic_cast<Plane*>(gameObject));
		break;
	case Type::PLAYER_BULLET:
		playerMissileColliders.push_back(dynamic_cast<Missile*>(gameObject));
		break;
	case Type::ENEMY_BULLET:
		enemyMissileColliders.push_back(dynamic_cast<Missile*>(gameObject));
		break;
	default:
		break;
	}
}

bool CollisionManager::isColliding(GameObject* gameObject1, GameObject* gameObject2)
{
	return RectInRect(gameObject1->GetCollider(), gameObject2->GetCollider());
}
