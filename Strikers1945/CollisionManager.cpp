#include "CollisionManager.h"
#include "Collider.h"
#include "CommonFunction.h"
#include "GameObject.h"
#include "Missile.h"
#include "Plane.h"

void CollisionManager::Init()
{
	playerColliders = {};
	playerBulletColliders = {};
	enemyColliders = {};
	enemyBulletColliders = {};
}

void CollisionManager::Update()
{
	checkCollisions();
}

void CollisionManager::Render(HDC hdc)
{
	renderColliders(hdc, reinterpret_cast<vector<GameObject*>&>(playerColliders));
	renderColliders(hdc, reinterpret_cast<vector<GameObject*>&>(enemyColliders));
	renderColliders(hdc, reinterpret_cast<vector<GameObject*>&>(playerBulletColliders));
	renderColliders(hdc, reinterpret_cast<vector<GameObject*>&>(enemyBulletColliders));
}

void CollisionManager::Release()
{
	playerColliders.clear();
	playerBulletColliders.clear();
	enemyColliders.clear();
	enemyBulletColliders.clear();
}

void CollisionManager::checkCollisions()
{
	// 플레이어 - 적 총알
	for (auto& player : playerColliders)
	{
		if (player->GetActive() == false) continue;
		for (auto& enemyBullet : enemyBulletColliders)
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
		for (auto& playerBullet : playerBulletColliders)
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

void CollisionManager::renderColliders(HDC hdc, vector<GameObject*>& gameObjects)
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
		playerBulletColliders.push_back(dynamic_cast<Missile*>(gameObject));
		break;
	case Type::ENEMY_BULLET:
		enemyBulletColliders.push_back(dynamic_cast<Missile*>(gameObject));
		break;
	default:
		break;
	}
}

bool CollisionManager::isColliding(GameObject* gameObject1, GameObject* gameObject2)
{
	return RectInRect(gameObject1->GetCollider(), gameObject2->GetCollider());
}
