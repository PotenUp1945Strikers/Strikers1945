#include "EffectManager.h"
#include "GameObject.h"
#include "ImageManager.h"
#include "Image.h"
#include "TimerManager.h"
void EffectManager::Update()
{
	for (auto& eff : dict)
	{
		if (eff.second.active)
		{
			eff.second.elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
			if (eff.second.elapsedTime > 0.1f)
			{
				eff.second.frameX++;
				if (eff.second.frameX > ImageManager::GetInstance()->GetImage(eff.second.key)->GetMaxFrameX())
				{
					eff.second.frameX = 0;
					eff.second.frameY++;
					if (eff.second.frameY > ImageManager::GetInstance()->GetImage(eff.second.key)->GetMaxFrameY())
					{
						eff.second.frameY = 0;
						eff.second.active = false;
					}
				}
				eff.second.elapsedTime = 0.0f;
			}
		}
	}
}

void EffectManager::Render(HDC hdc)  
{  
   for (auto& eff : dict)  
   {  
       if (eff.second.active)  
       {  
		   Image* image = ImageManager::GetInstance()->GetImage(eff.second.key);
		   FPOINT pos = eff.first->GetPos();
		   image->FrameRender(hdc, pos.x, pos.y, eff.second.frameX, eff.second.frameY);
       }  
   }  
}

void EffectManager::Release()
{
	dict.clear();
}

void EffectManager::AddEffect(GameObject* owner)
{
	Effect effect;
	effect.active = false;
	effect.owner = owner;
	effect.frameX = 0;
	effect.frameY = 0;
	effect.elapsedTime = 0.0f;
	switch (owner->GetType())
	{
	case Type::PLAYER:
		effect.key = TEXT(HIT_EFFECT_PATH);
		break;
	case Type::PLAYER_BULLET:
		effect.key = TEXT(HIT_EFFECT_PATH);
		break;
	case Type::ENEMY:
		effect.key = TEXT(HIT_EFFECT_PATH);
		break;
	case Type::ENEMY_BULLET:
		effect.key = TEXT(HIT_EFFECT_PATH);
		break;
	case Type::NONE:
	default:
		break;
	}
	dict.insert(make_pair(owner, effect));
}

void EffectManager::OnEffect(GameObject* owner)
{
	auto var = dict.find(owner);
	if (var != dict.end())
	{
		(*var).second.active = true;
	}
}
