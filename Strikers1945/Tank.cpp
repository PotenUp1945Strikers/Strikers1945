#include "Tank.h"
#include "CommonFunction.h"

void Tank::Update(void)
{
	switch (state)
	{
	case GameObjectStates::Die:
		if (render)
		{
			Stay();
			if (OutOfWindow())
			{
				render = false;
				use = true;
			}
		}
		break;
	case GameObjectStates::Wait:
		if (BackgroundManager::GetInstance()->GetCurrPosY() >= location)
		{
			oldLocation = location;
			render = true;
			state = GameObjectStates::Born;
		}
		break;
	case GameObjectStates::Born:
		Stay();
		if (!OutOfWindow())
		{
			active = true;
			state = GameObjectStates::Alive;
		}
		break;
	case GameObjectStates::Alive:
		Stay();
		Shoot();
		if (OutOfWindow())
		{
			active = false;
			state = GameObjectStates::Die;
		}
		break;
	}
	
	if (launcher)
		launcher->Update();
}

void Tank::Stay(void)
{
	float currLocation = BackgroundManager::GetInstance()->GetCurrPosY();
	float moveLength = currLocation - oldLocation;
	oldLocation = currLocation;
	pos.y += moveLength;
}

void Tank::OnDamage(int damage)
{
	health -= damage;
	currFrameY = 1;
	if (health <= 0)
	{
		active = false;
		currFrameY = 2;
		state = GameObjectStates::Die;
	}
}

void Tank::Render(HDC hdc)
{
	if (image && render)
	{
		if (currFrameY == 1)
		{
			hitRenderTime -= TimerManager::GetInstance()->GetDeltaTime();
			if (hitRenderTime < 0.0f)
			{
				currFrameY = 0;
				hitRenderTime = HIT_RENDER_TIME;
			}
		}

		switch (state)
		{
		case GameObjectStates::Die:
			image->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY);
			break;
		case GameObjectStates::Wait:
			image->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY);
			break;
		case GameObjectStates::Born:
		case GameObjectStates::Alive:
			rotateBarrel();
			image->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY);
			break;
		}
	}

	if (launcher)
		launcher->Render(hdc);
}

void Tank::Shoot(void)
{
	if (active && launcher)
		launcher->Shoot({ pos.x + (missilePos.x * cosf(barrelRadian)),
			pos.y + (missilePos.x * sinf(barrelRadian))});
}

void Tank::rotateBarrel(void)
{
	FPOINT playerPos = PlayerManager::GetInstance()->GetPlayer1Pos();
	barrelRadian = atan2f(playerPos.y - pos.y, playerPos.x - pos.x);
	float degree = fmod(RAD_TO_DEG(barrelRadian) + 450, 360);
	currFrameX = degree / 22.5;
}