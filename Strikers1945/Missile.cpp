#include "Missile.h"
#include "config.h"
#include "Image.h"
#include "ImageManager.h"
#include "TimerManager.h"

void Missile::Init()
{
	type = Type::NONE;
	active = false;
	render = false;
	dir = { 0.0f, 0.0f };
	pos = { 0.0f, 0.0f };
	speed = 0.0f;
	image = nullptr;
	health = 0;
	size = { 0, 0, 0, 0 };
}

void Missile::Init(Type type, FPOINT dir, FPOINT pos, float speed, Image* image)
{
	this->type = type;
	this->dir = dir;
	this->pos = pos;
	this->speed = speed;
	this->image = image;
	active = true;
	render = true;
	health = 1;
}

void Missile::Update()
{
	float velocity = TimerManager::GetInstance()->GetDeltaTime() * speed;
	pos.x += dir.x * velocity;
	pos.y += dir.y * velocity;
	if (outOfWindow())
	{
		active = false;
		render = false;
	}
}

void Missile::Render(HDC hdc)
{
	if(render)
		image->Render(hdc, pos.x, pos.y, 0);
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

void Missile::OnDamage()
{
	health--;
	if (health <= 0) {
		active = false;
		render = false;
	}
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
