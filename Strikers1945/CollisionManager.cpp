#include "CollisionManager.h"
#include "Collider.h"
// #include "GameObject.h"

void CollisionManager::Init()
{
	playerColliders = {};
	playerBulletColliders = {};
	enemyColliders = {};
	enemyBulletColliders = {};
}

void CollisionManager::Update()
{
    updateColliders(playerColliders);
    updateColliders(enemyColliders);
    updateColliders(playerBulletColliders);
    updateColliders(enemyBulletColliders);

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
    releaseColliders(playerColliders);
    releaseColliders(enemyColliders);
    releaseColliders(playerBulletColliders);
    releaseColliders(enemyBulletColliders);

    ReleaseInstance();
}

void CollisionManager::checkCollisions()
{
    // 플레이어 - 적
    for (auto playerCollider : playerColliders)
    {
        for (auto enemyCollider : enemyColliders)
        {
            if (playerCollider->IsColliding(*enemyCollider))
            {
                // 플레이어 데미지
                int a = 0;
            }
        }
    }
    // 플레이어 - 적 총알
    for (auto playerCollider : playerColliders)
    {
        for (auto enemyBulletCollider : enemyBulletColliders)
        {
            if (playerCollider->IsColliding(*enemyBulletCollider))
            {
                // 플레이어 데미지
            }
        }
    }

    // 적 - 플레이어 총알
    for (auto enemyCollider : enemyColliders)
    {
        for (auto playerBulletCollider : playerBulletColliders)
        {
            if (enemyCollider->IsColliding(*playerBulletCollider))
            {
                // 적 데미지
            }
        }
    }
}

void CollisionManager::AddCollider(GameObject* owner, CollisionType type, float size)
{
    Collider* collider = new Collider();
    // collider->Init(owner, type, owner->GetPos(), size);
    switch (type)
    {
    case CollisionType::PLAYER:
        playerColliders.push_back(collider);
        break;
    case CollisionType::ENEMY:
        enemyColliders.push_back(collider);
        break;
    case CollisionType::PLAYER_BULLET:
        playerBulletColliders.push_back(collider);
        break;
    case CollisionType::ENEMY_BULLET:
        enemyBulletColliders.push_back(collider);
        break;
    default:
        break;
    }
}

void CollisionManager::DeleteCollider(Collider* collider)
{
    switch (collider->GetType())
    {
    case CollisionType::PLAYER:
        removeColliderFromVector(playerColliders, collider);
        break;  
    case CollisionType::ENEMY:
        removeColliderFromVector(enemyColliders, collider);
        break;
    case CollisionType::PLAYER_BULLET:
        removeColliderFromVector(playerBulletColliders, collider);
        break;
    case CollisionType::ENEMY_BULLET:
        removeColliderFromVector(enemyBulletColliders, collider);
        break;
    default:
        break;
    }
}

void CollisionManager::updateColliders(vector<Collider*>& colliders)
{
    for (auto collider : colliders)
    {
        if (collider)
        {
            collider->Update();
        }
    }
}

void CollisionManager::renderColliders(HDC hdc, vector<Collider*>& colliders)
{
    for (auto collider : colliders)
    {
        if (collider)
        {
            collider->Render(hdc);
        }
    }
}

void CollisionManager::removeColliderFromVector(vector<Collider*>& colliders, Collider* collider)
{
    auto it = find(colliders.begin(), colliders.end(), collider);
    if (it != colliders.end())
    {
        if (*it)
        {
            (*it)->Release();
            delete (*it);
            (*it) = nullptr;
        }
        colliders.erase(it);
    }
}

void CollisionManager::releaseColliders(vector<Collider*>& colliders)
{
    for (auto collider : colliders)
    {
        if (collider)
        {
            collider->Release();
            delete collider;
            collider = nullptr;
        }
    }
}