#include "GameObject.h"
#include "ImageManager.h"

bool GameObject::OutOfWindow()
{
    int halfWidth = image->GetWidth() / 2;
    int halfHeight = image->GetHeight() / 2;

    if (pos.x - halfWidth < 0 || pos.x + halfWidth > WINSIZE_X ||
        pos.y - halfHeight < 0 || pos.y + halfHeight > WINSIZE_Y)
        return true;
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

void GameObject::SetActive(bool active)
{
    this->active = active;
}

void GameObject::SetRender(bool render)
{
    this->render = render;
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
