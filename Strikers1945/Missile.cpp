#include "Missile.h"
#include "config.h"
#include "Image.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "EffectManager.h"

void Missile::Init()
{
	type = Type::NONE;
	active = false;
	render = false;
	dir = { 0.0f, 0.0f };
	pos = { 0.0f, 0.0f };
	speed = 0.0f;
	image = nullptr;
	health = 1;
	size = { 0, 0, 0, 0 };
	currFrameX = 0;
	maxFrameX = 0;
	frameTime = ANIMATION_FRAME_TIME;
}

void Missile::Init(Type type)
{
	this->type = type;
	active = false;
	render = false;
	dir = { 0.0f, 0.0f };
	pos = { 0.0f, 0.0f };
	speed = 0.0f;
	image = nullptr;
	health = 1;
	size = { 0, 0, 0, 0 };
	currFrameX = 0;
	maxFrameX = 0;
	frameTime = ANIMATION_FRAME_TIME;
}

void Missile::Init(FPOINT dir, float speed, Image* image, RECT size, int damage, int maxFrameX)
{
	this->dir = dir;
	this->speed = speed;
	this->image = image;
	active = false;
	render = false;
	this->health = 1;
	this->damage = damage;
	this->size = size;
	currFrameX = 0;
	this->maxFrameX = maxFrameX;
	frameTime = ANIMATION_FRAME_TIME;
}

void Missile::Update()
{
	if (active)
	{
		float velocity = TimerManager::GetInstance()->GetDeltaTime() * speed;
		pos.x += dir.x * velocity;
		pos.y += dir.y * velocity;
	}

	if (outOfWindow())
	{
		active = false;
		render = false;
	}
}

void Missile::Render(HDC hdc)
{
	if (render)
	{
		if (maxFrameX)
		{
			frameTime -= TimerManager::GetInstance()->GetDeltaTime();
			if (frameTime < 0)
			{
				currFrameX = (currFrameX + 1) % maxFrameX;
				frameTime = ANIMATION_FRAME_TIME;
			}
		}
		image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0);
	}
}

void Missile::Release()
{
	image = nullptr;
}

//RECT Missile::GetCollider()
//{
//	RECT rc = { 
//		pos.x - size.left, 
//		pos.y - size.top, 
//		pos.x + size.right, 
//		pos.y + size.bottom 
//	};
//	return rc;
//}

void Missile::OnDamage(int damage)
{
	health -= damage;
	active = false;
	render = false;
	EffectManager::GetInstance()->OnEffect(TEXT(EFFECT2_PATH), pos);
}

bool Missile::Shoot(FPOINT pos, FPOINT dir)
{
	if (!active)
	{
		this->pos = pos;
		this->dir = dir;
		active = true;
		render = true;
		return true;
	}
	return false;
}

bool Missile::outOfWindow()
{
	if (pos.x + image->GetWidth() / 2 < 0)
		return true;

	if (pos.x - image->GetWidth() / 2 > WINSIZE_X)
		return true;

	if (pos.y + image->GetHeight() / 2 < 0)
		return true;

	if (pos.y - image->GetHeight() / 2 > WINSIZE_Y)
		return true;

	return false;
}
