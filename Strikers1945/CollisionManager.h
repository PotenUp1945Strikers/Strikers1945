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
<<<<<<< HEAD
    vector<Plane*> playerColliders;
    vector<Missile*> playerMissileColliders;
    vector<Plane*> enemyColliders;
    vector<Missile*> enemyMissileColliders;    
=======
    vector<GameObject*> playerColliders;
    vector<GameObject*> playerBulletColliders;
    vector<GameObject*> enemyColliders;
    vector<GameObject*> enemyBulletColliders;
>>>>>>> a392ccfcc60ffe797aa87330aead414cd2156175

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

