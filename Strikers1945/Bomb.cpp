#include "Bomb.h"
#include "ImageManager.h"
#include "ItemManager.h"
#include "TimerManager.h"

void Bomb::Init()
{
	type = Type::PLAYER_BOMB;

    bombPlaneImage = ImageManager::GetInstance()->GetImage(TEXT(BOMB_PLANE_PATH));
    miniBombImage = ImageManager::GetInstance()->GetImage(TEXT(BOMB_MINIBOMB_PATH));
    bombEffectImage = ImageManager::GetInstance()->GetImage(TEXT(BOMB_EFFECT_PATH));

    srand(time(NULL));

	active = false;
	render = false;

	dir = { 0.0f,-1.0f };
	speed = 300.0f;
	image = nullptr;

	miniBombDropTime = 2.0f;

    for (int i = 0; i < 3; i++)
    {
        planePos[i] = { 20.0f + 200.f * i, WINSIZE_Y };

        for (int j = 0; j < 6; j++)
        {
            currDropTime[i][j] = 0;
            hasDropped[i][j] = false;
            randDropFrameX[i][j] = rand() % 32;
            dropPos[i][j] = { 0.0f,0.0f };
        }
    }

	currDropInd = 0;
    currDropFrameX = 0;
    currTime = 0.0f;
    maxDropFrameX = miniBombImage->GetMaxFrameX();
    frameDuration = 0.1f;
}

void Bomb::Release()
{

}

void Bomb::Update()
{
    float deltaTime = TimerManager::GetInstance()->GetDeltaTime();

    if (active && render)
    {

    
        if (currTime >= frameDuration)
        {
            currDropFrameX = (currDropFrameX + 1) % maxDropFrameX;
            currTime = 0.0f;
        }

        currTime += deltaTime;

        int newDropInd = static_cast<int>(((WINSIZE_Y - planePos[0].y) / 150));

        for (int i = 0; i < 3; i++)
        {
            planePos[i].y += speed * dir.y * deltaTime;

            for (int j = 0; j < 6; j++)
            {
                if (newDropInd < 6 && hasDropped[i][newDropInd] == false)
                {
                    hasDropped[i][newDropInd] = true;
                    
                    dropPos[i][newDropInd] = { 
                        planePos[i].x + bombPlaneImage->GetWidth() / 2  + (rand() % 60 - 60),
                        planePos[i].y + bombPlaneImage->GetHeight() / 2 + (rand() % 60 - 60)
                    };
                }

                if (hasDropped[i][j])
                { 
                    currDropTime[i][j] += deltaTime;
                }
            }
        }

        if (currDropTime[2][5] > miniBombDropTime) ItemManager::GetInstance()->OnDropEnd();
    }

    

}

void Bomb::Render(HDC hdc)
{
    float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
   
    if (active && render)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 6; j++)
            {
               if (hasDropped[i][j] && currDropTime[i][j] <= miniBombDropTime)
               {
                    miniBombImage->FrameRender(hdc, dropPos[i][j].x, dropPos[i][j].y, (randDropFrameX[i][j] + currDropFrameX) % maxDropFrameX, 0, false);
               }
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        bombPlaneImage->Render(hdc, planePos[i].x, planePos[i].y);
    }
}

void Bomb::OnDamage()
{
}

