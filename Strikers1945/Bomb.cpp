#include "Bomb.h"
#include "ImageManager.h"
#include "ItemManager.h"
#include "EffectManager.h"
#include "CollisionManager.h"
#include "TimerManager.h"

void Bomb::Init()
{
	type = Type::BOMB_PLANE;

    bombPlaneImage = ImageManager::GetInstance()->GetImage(TEXT(BOMB_PLANE_PATH));
    miniBombImage = ImageManager::GetInstance()->GetImage(TEXT(BOMB_MINIBOMB_PATH));
    bombEffectImage = ImageManager::GetInstance()->GetImage(TEXT(BOMB_EFFECT_PATH));

    srand(time(NULL));

	active = false;
	render = false;

	dir = { 0.0f,-1.0f };
    pos = { 0.0f, WINSIZE_Y };
	speed = 300.0f;
	image = nullptr;

    size = { -WINSIZE_X,-bombPlaneImage->GetHeight()/2 + 40, WINSIZE_X , bombPlaneImage->GetHeight() / 2 };

    // struct init

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
            bombInfo.onEffect[i][j] = false;
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

        for (int i = 0; i < 3; i++)
        {

            bombInfo.planePos[i].y += speed * dir.y * deltaTime;

             int newDropInd = static_cast<int>(((WINSIZE_Y - bombInfo.planePos[i].y) / 150));
            
            if (bombInfo.hasDropped[i][newDropInd] == false)
            {
                bombInfo.hasDropped[i][newDropInd] = true;

                bombInfo.dropPos[i][newDropInd] = {
                    bombInfo.planePos[i].x + bombPlaneImage->GetWidth() / 2 + (rand() % 60 - 60),
                    bombInfo.planePos[i].y + bombPlaneImage->GetHeight() / 2 + (rand() % 60 - 60)
                };
            }

            for (int j = 0; j < 6; j++)
            {

                if (bombInfo.hasDropped[i][j])
                {
                    bombInfo.currDropTime[i][j] += deltaTime;
                }

            }
        }

        pos.y += speed * dir.y * deltaTime;
       
        if (bombInfo.currDropTime[0][5] > bombInfo.miniBombDropTime)
            ItemManager::GetInstance()->OnDropEnd();
    }

    

}

void Bomb::Render(HDC hdc)
{
    float deltaTime = TimerManager::GetInstance()->GetDeltaTime();

    wchar_t szText[128];
    swprintf(szText, 128, L"y pos = %.2f  active = %d   render %d", pos.y, active, render); // 소수점 둘째 자리까지 출력
    TextOut(hdc, 20, 60, szText, wcslen(szText));
  
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
            }
        }

        for (int i = 0; i < 3; i++)
        {
            bombPlaneImage->Render(hdc, bombInfo.planePos[i].x, bombInfo.planePos[i].y);
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (!bombInfo.onEffect[i][j] && (bombInfo.currDropTime[i][j] >= bombInfo.miniBombDropTime))
                {
                    EffectManager::GetInstance()->OnEffect(TEXT(BOMB_EFFECT_PATH), { bombInfo.dropPos[i][j].x,bombInfo.dropPos[i][j].y - bombEffectImage->GetHeight()/2});
                    bombInfo.onEffect[i][j] = true;
                }
            }
        }


    }

}

void Bomb::OnDamage()
{
}

float Bomb::GetBombPlanePosY()
{
    return bombInfo.planePos[0].y;
}
