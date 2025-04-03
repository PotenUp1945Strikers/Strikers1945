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

    bombInfo.miniBombDropTime = 2.0f;

    for (int i = 0; i < 3; i++)
    {
        bombInfo.planePos[i] = { 20.0f + 200.f * i, WINSIZE_Y };

        for (int j = 0; j < 6; j++)
        {
            bombInfo.currDropTime[i][j] = 0;
            bombInfo.hasDropped[i][j] = false;
            bombInfo.randDropFrameX[i][j] = rand() % 32;
            bombInfo.dropPos[i][j] = { 0.0f,0.0f };
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

        int newDropInd = static_cast<int>(((WINSIZE_Y - bombInfo.planePos[0].y) / 150));

        for (int i = 0; i < 3; i++)
        {
            bombInfo.planePos[i].y += speed * dir.y * deltaTime;

            for (int j = 0; j < 6; j++)
            {
                if (newDropInd < 6 && bombInfo.hasDropped[i][newDropInd] == false)
                {
                    bombInfo.hasDropped[i][newDropInd] = true;
                    
                    bombInfo.dropPos[i][newDropInd] = {
                        bombInfo.planePos[i].x + bombPlaneImage->GetWidth() / 2  + (rand() % 60 - 60),
                        bombInfo.planePos[i].y + bombPlaneImage->GetHeight() / 2 + (rand() % 60 - 60)
                    };
                }

                if (bombInfo.hasDropped[i][j])
                { 
                    bombInfo.currDropTime[i][j] += deltaTime;
                }
            }
        }

        if (bombInfo.currDropTime[2][5] > bombInfo.miniBombDropTime) ItemManager::GetInstance()->OnDropEnd();
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
               if (bombInfo.hasDropped[i][j] && bombInfo.currDropTime[i][j] <= bombInfo.miniBombDropTime)
               {
                    miniBombImage->FrameRender(hdc, bombInfo.dropPos[i][j].x, bombInfo.dropPos[i][j].y, (bombInfo.randDropFrameX[i][j] + currDropFrameX) % maxDropFrameX, 0, false);
               }
               
               if (bombInfo.currDropTime[i][j] >= bombInfo.miniBombDropTime)
               {
                  // EffectManager::GetInstance()->OnEffect(TEXT(BOMB_EFFECT_PATH), bombInfo.dropPos[i][j]);
               }

            }
        }

        for (int i = 0; i < 3; i++)
        {
            bombPlaneImage->Render(hdc, bombInfo.planePos[i].x, bombInfo.planePos[i].y);
        }
    }

}

void Bomb::OnDamage(int damage)
{

}

