#include "ScoreManager.h"

void ScoreManager::Init()
{
    player1Score = 0;
    player2Score = 0;
}

void ScoreManager::AddScore(PlayerNum player, int score)
{
    if (player == PlayerNum::PLAYER1)
    {
        player1Score += score;
    }
    else if (player == PlayerNum::PLAYER2)
    {
        player2Score += score;
    }
}

int ScoreManager::GetScore(PlayerNum player)
{
    if (player == PlayerNum::PLAYER1)
    {
        return player1Score;
    }
    else if (player == PlayerNum::PLAYER2)
    {
        return player2Score;
    }
    return 0;
}