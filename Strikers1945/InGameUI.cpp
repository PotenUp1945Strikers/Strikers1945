#include "InGameUI.h"
#include "ImageManager.h"

void InGameUI::Render(HDC hdc)
{
	for (int i = 0; i < count; i++)
	{
		image->FrameRender(hdc, renderPos.x + (interval * i), renderPos.y, currFrameX, currFrameY, false);
	}
}
