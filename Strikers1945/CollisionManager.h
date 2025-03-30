#pragma once
#include "config.h"
#include "Singleton.h"
#include <vector>

class Collider;
class CollisionManager : public Singleton<CollisionManager>
{
private:
    vector<Collider*> playerColliders;
    vector<Collider*> playerBulletColliders;
    vector<Collider*> enemyColliders;
    vector<Collider*> enemyBulletColliders;    

public:
    void Init();
    void Update();
    void Render(HDC hdc);
    void Release();


    void AddCollider(/*GameObject* owner, */CollisionType type, FPOINT pos, float size);
    void DeleteCollider(Collider* collider);

private:
    void checkCollisions();

    void renderColliders(HDC hdc, vector<Collider*>& colliders);
    void updateColliders(vector<Collider*>& colliders);
    void removeColliderFromVector(vector<Collider*>& colliders, Collider* collider);
    void releaseColliders(vector<Collider*>& colliders);
};

