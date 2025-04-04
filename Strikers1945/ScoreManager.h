#pragma once
#include "Singleton.h"

class ScoreManager : public Singleton<ScoreManager>
{
private:
    int player1Score;
    int player2Score;

public:
    void Init();
    void AddScore(int player, int score);
    int GetScore(int player);
};

