#include "GameObject.h"
#include "ImageManager.h"

bool GameObject::OutOfWindow()
{

    //switch (type)
    //{
    //case Type::PLAYER:
    //    // TODO : player offset
    //    if (pos.x >= 0 && pos.x <= WINSIZE_X
    //        && pos.y >= 0 && pos.y <= WINSIZE_Y)
    //    {
    //        return false;
    //    }
    //    else return true;

    //    break;

    //case Type::PLAYER_BULLET: 
    //case Type::ENEMY: 
    //case Type::ENEMY_BULLET:
    //    if (pos.x < 0 || pos.x > WINSIZE_X || pos.y < 0 || pos.y > WINSIZE_Y)
    //    {
    //        return true;
    //    }
    //    else return false;
    //    break;
    //
    //}
    return false;
}

Type GameObject::GetType()
{
    return type;
}

void GameObject::SetPos(FPOINT pos)
{
    this->pos = pos;
}

bool GameObject::GetActive()
{
    return active;
}

bool GameObject::GetRender()
{
    return render;
}

RECT GameObject::GetCollider()
{
   RECT rc = {
       pos.x + size.left,
       pos.y + size.top,
       pos.x + size.right,
       pos.y + size.bottom
   };
   return rc;
    
}
