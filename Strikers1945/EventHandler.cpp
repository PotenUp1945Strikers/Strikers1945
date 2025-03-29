#include "EventHandler.h"

bool EventHandler::Update()
{
	if (MAX_GAME_LENGTH < BackgroundManager::GetInstance()->GetCurrPosY())
		return true;
	return false;
}
