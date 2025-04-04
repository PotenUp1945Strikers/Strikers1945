#include "EffectManager.h"
#include "GameObject.h"
#include "ImageManager.h"
#include "Image.h"
#include "TimerManager.h"

void EffectManager::FillDict()
{
	vector<Effect> effects;
	for (int i = 0; i < 30; i++)
	{
		Effect effect;
		effect.active = false;
		effect.pos = { 0,0 };
		effect.frameX = 0;
		effect.frameY = 0;
		effect.elapsedTime = 0.0f;
		effects.push_back(effect);
	}

	dict.insert(make_pair(TEXT(HIT_EFFECT_PATH), effects));
	dict.insert(make_pair(TEXT(BOMB_EFFECT_PATH), effects));
	dict.insert(make_pair(TEXT(BOMB_EFFECT2_PATH), effects));
	dict.insert(make_pair(TEXT(EFFECT1_PATH), effects));
	dict.insert(make_pair(TEXT(EFFECT2_PATH), effects));
	dict.insert(make_pair(TEXT(EFFECT3_PATH), effects));
	dict.insert(make_pair(TEXT(EFFECT4_PATH), effects));
	dict.insert(make_pair(TEXT(ITEM_EFFECT_PATH), effects));
}

void EffectManager::Init()
{
	if (dict.empty())
		FillDict();
}

void EffectManager::Update()
{
	for (auto& effectPair : dict)
	{
		for (auto& effect : effectPair.second)
		{
			if (effect.active)
			{
				effect.elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
				if (effect.elapsedTime > 0.05f)
				{
					effect.frameX++;
					if (effect.frameX > ImageManager::GetInstance()->GetImage(effectPair.first)->GetMaxFrameX())
					{
						effect.frameX = 0;
						effect.frameY++;
						if (effect.frameY > ImageManager::GetInstance()->GetImage(effectPair.first)->GetMaxFrameY())
						{
							effect.active = false;
							effect.frameY = 0;
						}
					}
					effect.elapsedTime = 0.0f;
				}
			}
		}
	}*/
	for (auto& effectPair : dict)
	{
		for (auto& effect : effectPair.second)
		{
			if (effect.active)
			{
				effect.elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
				if (effect.elapsedTime > 0.05f)
				{
					effect.frameX++;
					if (effect.frameX > ImageManager::GetInstance()->GetImage(effectPair.first)->GetMaxFrameX())
					{
						effect.frameX = 0;
						effect.frameY++;
						if (effect.frameY > ImageManager::GetInstance()->GetImage(effectPair.first)->GetMaxFrameY())
						{
							effect.active = false;
							effect.frameY = 0;
						}
					}
					effect.elapsedTime = 0.0f;
				}
			}
		}
	}
}

void EffectManager::Render(HDC hdc)  
{  
	for (auto& effectPair : dict)
	{
		Image* image = ImageManager::GetInstance()->GetImage(effectPair.first);
		for (auto& effect : effectPair.second)
		{
			if (effect.active)
			{
				image->FrameRender(hdc, effect.pos.x, effect.pos.y, effect.frameX, effect.frameY);
			}
		}
	}
}

void EffectManager::Release()
{
	dict.clear();
}

void EffectManager::OnEffect(const wchar_t* key, FPOINT pos)
{
	/*if (dict.empty())
		FillDict();

	auto var = dict.find(key);
	if (var != dict.end())
	{
		for (auto& effect : var->second)
		{
			if (!effect.active)
			{
				effect.frameX = 0;
				effect.frameY = 0;
				effect.elapsedTime = 0.0f;
				effect.pos = pos;
				effect.active = true;
				return;
			}
		}

		var->second[0].frameX = 0;
		var->second[0].frameY = 0;
		var->second[0].elapsedTime = 0.0f;
		var->second[0].pos = pos;
		var->second[0].active = true;
	}
}
