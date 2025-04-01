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


}




Type GameObject::GetType()
{
    return type;
}

bool GameObject::GetActive()
{
    return active;
}

bool GameObject::GetRender()
{
    return render;
}

void GameObject::OnDamage()
{
    switch (type)
    {
    case Type::PLAYER:

        health -= 1;

        break;
    case Type::ENEMY:

        //TODO : tune value
        // health -= ;

        break;

   case Type::PLAYER_BULLET: 
   case Type::ENEMY_BULLET:

       //TODO : DestroyActor, Start Effect Animation

       active = false;
       render = false;


       break;

    }

}
