#include "HoverItem.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "ItemManager.h"

void HoverItem::Init()
{
	type = Type::NONE;
	active = false;
	render = false;
	dir = { 0.0f,0.0f };
	pos = { 0.0f,0.0f };
	size = { 0,0,0,0 };
	reflectCnt = 0;
	currFrameX = 0;
	maxFrameX = 0;
	currTime = 0.0f;
	itemFrameTime = 0.0f;
}

void HoverItem::Init(Type type, const wchar_t* key, FPOINT onDamagePos)
{
	srand(time(NULL));
	this->type = type;
	this->image = ImageManager::GetInstance()->GetImage(key);
	size = { -image->GetWidth()/2 -5,-image->GetHeight()/2 -5 ,image->GetWidth()/2 -5 ,image->GetHeight()/2 -5 };

	active = true;
	render = true;
	
	if(type == Type::ITEM_HOVER_MEDAL)
	{
		dir = { 0.0f, 1.0f};
	}
	else
	{
		int randX = (rand() % 2 == 0) ? 1 : -1;
		int randY = (rand() % 2 == 0) ? 1 : -1;
		dir = { static_cast<float>(randX), static_cast<float>(randY) };
	}
	
	pos = { onDamagePos.x, onDamagePos.y };
	reflectCnt = 0;
	currFrameX = 0;
	maxFrameX = image->GetMaxFrameX();
	currTime = 0.0f;
	itemFrameTime = 8.0f;
	speed = 90.0f;
	frameDuration = 0.2f;
}

void HoverItem::Release()	
{
}

void HoverItem::Update()
{
	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	if (active && render)
	{
		if (currTime >= frameDuration)
		{
			currFrameX = (currFrameX + 1) % maxFrameX;
			currTime = 0.0f;
		}

		currTime += deltaTime;

		pos.x += speed * dir.x * deltaTime;
		pos.y += speed * dir.y * deltaTime;

		if (OutOfWindow() && type == Type::ITEM_HOVER_MEDAL)
		{
			active = false;
			render = false;
			return;
		}
		
		if(OutOfWindow())
		{
			if (reflectCnt <= 4)
			{
				int halfWidth = image->GetWidth() / 2;
				int halfHeight = image->GetHeight() / 2;

				if (pos.x - halfWidth < 0 || pos.x + halfWidth > WINSIZE_X)
				{

					dir.x = -dir.x;
					reflectCnt++;
				}
				else if (pos.y - halfHeight < 0 || pos.y + halfHeight > WINSIZE_Y)
				{
					dir.y = -dir.y;
					reflectCnt++;
				}
			}

		}
	}
}

void HoverItem::Render(HDC hdc)
{
	if (active && render)
	{
		//if(type == Type::ITEM_HOVER_BOMB || type == Type::ITEM_HOVER_POWERUP)
			image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0);
		//else if (type == Type::ITEM_HOVER_MEDAL)
		//{
		//	image->Render(hdc, pos.x, pos.y);
		//}
	}
}

void HoverItem::OnDamage(int damage)
{
	active = false;
	render = false;
	
	
	//ItemManager::GetInstance()->RemoveItem(this);
}