#pragma once
#include "config.h"
#include "Singleton.h"

class ScoreManager : public Singleton<ScoreManager>
{
private:
    int player1Score;
    int player2Score;

public:
    void Init();
    void AddScore(PlayerNum player, int score);
    int GetScore(PlayerNum player);
};

