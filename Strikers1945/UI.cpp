#include "UI.h"
#include "ImageManager.h"
#include "TimerManager.h"
void UI::Init()
{
	image = nullptr;
	currFrameX = 0;
	currFrameY = 0;
	renderPos = { 0.0f, 0.0f };
}

void UI::Release()
{
}

void UI::Update()
{
	elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (elapsedTime > 0.1f)
	{
		currFrameX++;
		if (currFrameX > image->GetMaxFrameX())
		{
			currFrameX = 0;
			currFrameY++;
			if (currFrameY > image->GetMaxFrameY())
			{
				currFrameY = 0;
			}
		}
		elapsedTime = 0.0f;
	}

}

void UI::Render(HDC hdc)
{
	if(image)
		image->FrameRender(hdc, renderPos.x, renderPos.y, currFrameX, currFrameY, false);
}

void UI::SetImage(const wchar_t* filePath, int width, int height, int maxFrameX, int maxFrameY)
{
	image = ImageManager::GetInstance()->AddImage("이미지 키값", filePath, width, height, maxFrameX, maxFrameY, true, RGB(255, 0, 255));
}
