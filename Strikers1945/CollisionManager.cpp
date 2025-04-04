#include "CollisionManager.h"
#include "Collider.h"
#include "CommonFunction.h"
#include "ItemManager.h"
#include "GameObject.h"
#include "Missile.h"
#include "Plane.h"
#include "EffectManager.h"
#include "ScoreManager.h"

void CollisionManager::Init()
{
	playerColliders = {};
	playerBulletColliders = {};
	enemyColliders = {};
	enemyBulletColliders = {};
	itemColliders = {};
	bombPlaneColliders = {};
}

void CollisionManager::Update()
{
	checkCollisions();
}

void CollisionManager::Render(HDC hdc)
{
	renderColliders(hdc, playerColliders);
	renderColliders(hdc, enemyColliders);
	renderColliders(hdc, playerBulletColliders);
	renderColliders(hdc, enemyBulletColliders);
	renderColliders(hdc, itemColliders);
	renderColliders(hdc, bombPlaneColliders);
}

void CollisionManager::Release()
{
	playerColliders.clear();
	playerBulletColliders.clear();
	enemyColliders.clear();
	enemyBulletColliders.clear();
	itemColliders.clear();
	bombPlaneColliders.clear();
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
				EffectManager::GetInstance()->OnEffect(TEXT(EFFECT4_PATH), player->GetPos());
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
				//enemy->OnDamage();
				playerBullet->OnDamage();
				ItemManager::GetInstance()->CreateItem(playerBullet->GetPos());
				
			}
		}
	}

	// 플레이어 - 아이템
	for (auto& player : playerColliders)
	{
		if (player->GetActive() == false) continue;
		for (auto& hoverItem : itemColliders)
		{
			if (hoverItem->GetActive() == false) continue;
			if (isColliding(player, hoverItem))
			{
				hoverItem->OnDamage();
				ItemManager::GetInstance()->OnGainItem(hoverItem, player);
			}
		}
	}

	// 폭탄 비행기 - (미사일, 적 총알)
	for (auto& bombPlane : bombPlaneColliders)
	{
		if (bombPlane->GetActive() == false) continue;
		
		for (auto& enemyBullet : enemyBulletColliders)
		{
			if (enemyBullet->GetActive() == false) continue;
			if (isColliding(bombPlane, enemyBullet))
			{
				enemyBullet->OnDamage();
			}
		}

		for (auto& enemy : enemyColliders)
		{
			if (enemy->GetActive() == false) continue;
			if (isColliding(bombPlane, enemy))
			{
				enemy->OnDamage();
				EffectManager::GetInstance()->OnEffect(TEXT(ITEM_EFFECT_PATH), hoverItem->GetPos());
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
		playerColliders.push_back(gameObject);
		break;
	case Type::ENEMY:
		enemyColliders.push_back(gameObject);
		break;
	case Type::PLAYER_BULLET:
		playerBulletColliders.push_back(gameObject);
		break;
	case Type::ENEMY_BULLET:
		enemyBulletColliders.push_back(gameObject);
	case Type::ITEM_HOVER_BOMB:
	case Type::ITEM_HOVER_POWERUP:
	case Type::ITEM_HOVER_MEDAL:
		itemColliders.push_back(gameObject);
		break;
	case Type::BOMB_PLANE:
		bombPlaneColliders.push_back(gameObject);
		break;
	default:
		break;
	}
}

bool CollisionManager::isColliding(GameObject* gameObject1, GameObject* gameObject2)
{
	return RectInRect(gameObject1->GetCollider(), gameObject2->GetCollider());
}
