#include "EffectManager.h"
#include "GameObject.h"
#include "ImageManager.h"
#include "Image.h"
#include "TimerManager.h"

void EffectManager::FillDict()
{
	//Effect effect;
	//effect.active = false;
	//effect.pos = { 0,0 };
	//effect.frameX = 0;
	//effect.frameY = 0;
	//effect.elapsedTime = 0.0f;

	//dict.insert(make_pair(TEXT(HIT_EFFECT_PATH), effect));
	//dict.insert(make_pair(TEXT(BOMB_EFFECT_PATH), effect));
	//dict.insert(make_pair(TEXT(BOMB_EFFECT2_PATH), effect));
	//dict.insert(make_pair(TEXT(EFFECT1_PATH), effect));
	//dict.insert(make_pair(TEXT(EFFECT2_PATH), effect));
	//dict.insert(make_pair(TEXT(EFFECT3_PATH), effect));
	//dict.insert(make_pair(TEXT(EFFECT4_PATH), effect));

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
	//dict.insert(make_pair(TEXT(BOMB_EFFECT2_PATH), effects));
	dict.insert(make_pair(TEXT(EFFECT1_PATH), effects));
	dict.insert(make_pair(TEXT(EFFECT2_PATH), effects));
	dict.insert(make_pair(TEXT(EFFECT3_PATH), effects));
	//dict.insert(make_pair(TEXT(EFFECT4_PATH), effects));
}

void EffectManager::Init()
{
	if (dict.empty())
		FillDict();
}

void EffectManager::Update()
{
	/*for (auto& eff : dict)
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
	/*for (auto& eff : dict)
	{
		if (eff.second.active)
		{
			Image* image = ImageManager::GetInstance()->GetImage(eff.first);
			image->FrameRender(hdc, eff.second.pos.x, eff.second.pos.y, eff.second.frameX, eff.second.frameY);
		}
	}  */
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
		var->second.frameX = 0;
		var->second.frameY = 0;
		var->second.elapsedTime = 0.0f;
		var->second.pos = pos;
		var->second.active = true;
	}*/
	if (dict.empty())
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
