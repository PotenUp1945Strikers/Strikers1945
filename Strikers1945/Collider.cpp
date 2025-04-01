#include "Collider.h"
#include "CommonFunction.h"
// #include "GameObject.h"

void Collider::Init(GameObject* owner, Type type, FPOINT pos, float size)
{
    this->owner = owner;
    this->type = type;
    this->pos = pos;
    this->size = size;
    collisionRC = GetRectAtCenter(pos.x, pos.y, size, size);
}

void Collider::Update()
{
    // pos = owner->GetPos();
    collisionRC = GetRectAtCenter(pos.x, pos.y, size, size);

}

void Collider::Render(HDC hdc)
{
    Rectangle(hdc, pos.x - size / 2, pos.y - size / 2, pos.x + size / 2, pos.y + size / 2);
}

void Collider::Release()
{
    owner = nullptr;
}

bool Collider::IsColliding(const Collider& other)
{
    return RectInRect(this->collisionRC, other.collisionRC);
}
