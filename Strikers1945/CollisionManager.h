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
    vector<Missile*> playerMissileColliders;
    vector<Plane*> enemyColliders;
    vector<Missile*> enemyMissileColliders;    

public:
    void Init();
    void Update();
    void Render(HDC hdc);
    void Release();

    void AddCollider(GameObject* gameObject);
private:
    void checkCollisions();

    template<typename T>
    void renderColliders(HDC hdc, vector<T*>& gameObjects);
    bool isColliding(GameObject* gameObject1, GameObject* gameObject2);
};

