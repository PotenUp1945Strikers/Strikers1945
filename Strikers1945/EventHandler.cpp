#include "EventHandler.h"

void EventHandler::Init()
{
	gameOver = false;
	gameClear = false;
}

bool EventHandler::IsGameOver()
{
	return gameOver;
}

bool EventHandler::IsGameClear()
{
	if (gameOver)
		return false;

	return gameClear;
}

void EventHandler::GameOver()
{
	gameOver = true;
}

void EventHandler::GameClear()
{
	gameClear = true;
}
