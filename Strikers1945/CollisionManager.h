#pragma once
#include "config.h"
#include "Singleton.h"
#include <vector>

class GameObject;
class Plane;
class Missile;
class CollisionManager : public Singleton<CollisionManager>
{
private:
    vector<Plane*> playerColliders;
    vector<Missile*> playerBulletColliders;
    vector<Plane*> enemyColliders;
    vector<Missile*> enemyBulletColliders;    

public:
    void Init();
    void Update();
    void Render(HDC hdc);
    void Release();

    void AddCollider(GameObject* gameObject);
private:
    void checkCollisions();
    void renderColliders(HDC hdc, vector<GameObject*>& gameObjects);
    bool isColliding(GameObject* gameObject1, GameObject* gameObject2);
};

