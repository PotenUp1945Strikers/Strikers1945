#include "EffectManager.h"
#include "GameObject.h"
#include "ImageManager.h"
#include "Image.h"
#include "TimerManager.h"

void EffectManager::FillDict()
{
	Effect effect;
	effect.active = false;
	effect.pos = { 0,0 };
	effect.frameX = 0;
	effect.frameY = 0;
	effect.elapsedTime = 0.0f;

	dict.insert(make_pair(TEXT(HIT_EFFECT_PATH), effect));
	dict.insert(make_pair(TEXT(BOMB_EFFECT_PATH), effect));
	dict.insert(make_pair(TEXT(EFFECT1_PATH), effect));
	dict.insert(make_pair(TEXT(EFFECT2_PATH), effect));
	dict.insert(make_pair(TEXT(EFFECT3_PATH), effect));


}

void EffectManager::Init()
{
	if (dict.empty())
		FillDict();
}

void EffectManager::Update()
{
	for (auto& eff : dict)
	{
		if (eff.second.active)
		{
			eff.second.elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
			if (eff.second.elapsedTime > 0.05f)
			{
				eff.second.frameX++;
				if (eff.second.frameX > ImageManager::GetInstance()->GetImage(eff.first)->GetMaxFrameX())
				{
					eff.second.frameX = 0;
					eff.second.frameY++;
					if (eff.second.frameY > ImageManager::GetInstance()->GetImage(eff.first)->GetMaxFrameY())
					{
						eff.second.active = false;
						eff.second.frameY = 0;
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
		   Image* image = ImageManager::GetInstance()->GetImage(eff.first);
		   image->FrameRender(hdc, eff.second.pos.x, eff.second.pos.y, eff.second.frameX, eff.second.frameY);
       }  
   }  
}

void EffectManager::Release()
{
	dict.clear();
}

void EffectManager::OnEffect(const wchar_t* key, FPOINT pos)
{
	if (dict.empty())
		FillDict();

	auto var = dict.find(key);
	if (var != dict.end())
	{
		var->second.frameX = 0;
		var->second.frameY = 0;
		var->second.elapsedTime = 0.0f;
		var->second.pos = pos;
		var->second.active = true;
	}
}
