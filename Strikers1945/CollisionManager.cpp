#include "CollisionManager.h"
#include "Collider.h"
#include "CommonFunction.h"
#include "GameObject.h"

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
    renderColliders(hdc, playerColliders);
    renderColliders(hdc, enemyColliders);
    renderColliders(hdc, playerBulletColliders);
    renderColliders(hdc, enemyBulletColliders);
}

void CollisionManager::Release()
{
    ReleaseInstance();
}

void CollisionManager::checkCollisions()
{
    // 플레이어 - 적
    for (auto player : playerColliders)
    {
        for (auto enemy : enemyColliders)
        {
            if (player->GetActive() && enemy->GetActive())
            {
                if (isColliding(player, enemy))
                {
                    // 플레이어 데미지
                    player->OnDamage();
                    enemy->OnDamage();
                }
            }
        }
    }
    // 플레이어 - 적 총알
    for (auto player : playerColliders)
    {
        for (auto enemyBullet : enemyBulletColliders)
        {
            if (player->GetActive() == false || enemyBullet->GetActive() == false) continue;
            if (isColliding(player, enemyBullet))
            {
                player->OnDamage();
                enemyBullet->OnDamage();
            }
        }
    }

    // 적 - 플레이어 총알
    for (auto enemy : enemyColliders)
    {
        for (auto playerBullet : playerBulletColliders)
        {
			if (enemy->GetActive() == false || playerBullet->GetActive() == false) continue;
			if (isColliding(enemy, playerBullet))
			{
				// 적 데미지
				enemy->OnDamage();
				playerBullet->OnDamage();
			}
        }
    }
}

void CollisionManager::renderColliders(HDC hdc, vector<Plane*>& planes)
{
    for (auto plane : planes)
    {
        if (plane->GetActive() == false) continue;
        RECT body = plane->GetCollider().body;
        RECT wing = plane->GetCollider().wing;

        Rectangle(hdc, body.left, body.top, body.right, body.bottom);
        Rectangle(hdc, wing.left, wing.top, wing.right, wing.bottom);
    }
}

void CollisionManager::renderColliders(HDC hdc, vector<Missile*>& missiles)
{
    for (auto missile : missiles)
    {
        if (missile->GetActive() == false) continue;
        RECT missileRc = missile->GetCollider();
        Rectangle(hdc, missileRc.left, missileRc.top, missileRc.right, missileRc.bottom);
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

bool CollisionManager::isColliding(Plane* plane1, Plane* plane2)
{
    RECT p1Body = plane1->GetCollider().body;
    RECT p1Wing = plane1->GetCollider().wing;

    RECT p2Body = plane1->GetCollider().body;
    RECT p2Wing = plane1->GetCollider().wing;

    return (RectInRect(p1Body, p2Body) || RectInRect(p1Body, p2Wing) || RectInRect(p1Wing, p2Body) || RectInRect(p1Wing, p2Wing));
}

bool CollisionManager::isColliding(Plane* plane, Missile* missile)
{
    RECT body = plane->GetCollider().body;
    RECT wing = plane->GetCollider().wing;

    RECT missileRc = missile->GetCollider();

    return (RectInRect(body, missileRc) || RectInRect(wing, missileRc));
}
