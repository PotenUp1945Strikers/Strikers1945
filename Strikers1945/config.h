#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>

using namespace std;

#define WINSIZE_X	600
#define WINSIZE_Y	800
#define DEG_TO_RAD(degree) ((3.14 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.14) * radian)

#define PAUSE_KEY 'P'
#define SUICIDE_KEY 'K'
#define REGAME_KEY 'R'

#define BACKGROUND_PATH "Image/Background.bmp"
#define OPENING_PATH "Image/Opening.bmp"
#define PAUSE_PATH "Image/Pause.bmp"
#define GAMEOVER_PATH "Image/GameOver.bmp"
#define ENDING_PATH "Image/Ending.bmp"
#define LIFE_COUNT_PATH "Image/PlayerLifeCount.bmp"
#define BOMB_COUNT_PATH "Image/PlayerBombCount.bmp"
#define NUMBER_SET1_PATH "Image/NumberSet1.bmp"

#define BACKGROUND_SPEED 120
#define BACKGROUND_SIZE 4781

#define MAX_GAME_LENGTH 30000

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

enum class GameStates: UINT8
{
	Intro,
	InGame,
	Pause,
	GameOver,
	Ending
};

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;

enum class CollisionType
{
	NONE,
	PLAYER,
	ENEMY,
	PLAYER_BULLET,
	ENEMY_BULLET,
};