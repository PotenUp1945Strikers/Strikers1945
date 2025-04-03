#include "InGameUI.h"
#include "ImageManager.h"

void InGameUI::Render(HDC hdc)
{
	switch (playerNum)
	{
	case PlayerNum::PLAYER1:
		for (int i = 0; i < count; i++)
		{
			image->FrameRender(hdc, renderPos.x + (interval * i), renderPos.y, currFrameX, currFrameY, false);
		}
		break;
	case PlayerNum::PLAYER2:
		for (int i = 0; i < count; i++)
		{
			image->FrameRender(hdc, renderPos.x - (interval * i), renderPos.y, currFrameX, currFrameY, false);
		}
		break;
	}
	
}
