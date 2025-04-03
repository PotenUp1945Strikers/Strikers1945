#include "ScoreManager.h"

void ScoreManager::Init()
{
    player1Score = 0;
    player2Score = 0;
}

void ScoreManager::AddScore(int player, int score)
{
    if (player == 1)
    {
        player1Score += score;
    }
    else if (player == 2)
    {
        player2Score += score;
    }
}

int ScoreManager::GetScore(int player)
{
    if (player == 1)
    {
        return player1Score;
    }
    else if (player == 2)
    {
        return player2Score;
    }
    return 0;
}