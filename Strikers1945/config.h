#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

#define WINSIZE_X	600
#define WINSIZE_Y	800
#define PI 3.141592
#define DEG_TO_RAD(degree) ((PI / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / PI) * radian)

#define PAUSE_KEY 'P'
#define SUICIDE_KEY 'K'
#define REGAME_KEY 'R'
#define CLEAR_KEY 'O'

#define BACKGROUND_PATH "Image/Background.bmp"
#define OPENING_PATH "Image/Opening.bmp"
#define PAUSE_PATH "Image/Pause.bmp"
#define GAMEOVER_PATH "Image/GameOver.bmp"
#define ENDING_PATH "Image/Ending.bmp"
#define PLAYER_PATH "Image/Player.bmp"
#define LIFE_COUNT_PATH "Image/PlayerLifeCount.bmp"
#define BOMB_COUNT_PATH "Image/PlayerBombCount.bmp"
#define NUMBER_SET1_PATH "Image/NumberSet1.bmp"
#define NORMAL_BULLET_PATH "Image/NormalBullet.bmp"
#define ENEMY1_PATH "Image/Enemy1.bmp"
#define BOMB_PLANE_PATH "Image/BombPlane.bmp"
#define BOMB_MINIBOMB_PATH "Image/MiniBomb.bmp"
#define BOMB_EFFECT_PATH "Image/BombEffect.bmp"
#define ITEM_HOVERBOMB_PATH "Image/HoverBomb.bmp"

#define PATTERN_ENEMY_NUM 6

#define BOSS_PATH "Image/Boss.bmp"

#define BACKGROUND_SPEED 120
#define BACKGROUND_SIZE 4781

#define INVINCIBILITY_TIME 1.2f

#define PLAYER_START_MOVE "PlayerMoveIn"
#define PLAYER_END_MOVE "PlayerMoveOut"

#define MAX_GAME_LENGTH 30000

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

typedef struct tagColider
{
	RECT Body;
	RECT Wing;
} Colider;

typedef struct tagPlaneType
{
	const wchar_t*	key;
	float			speed;
	int				health;
	RECT			size;
	const wchar_t*	missileType;
} PlaneType;

typedef struct tagMissileType
{
	const wchar_t*	key;
	float			missileSpeed;
	float			shootRate;
	int				damage;
	float			reloadRate;
	int				missileAmount;
	// RECT			size;
	const wchar_t*	upgrade;
} MissileType;

enum class GameStates: UINT8
{
	Intro,
	InGame,
	Pause,
	GameOver,
	Ending
};

enum class GameObjectStates : UINT8
{
	Die,
	Wait,
	Born,
	Alive
};

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;

enum class Type
{
	NONE,
	PLAYER,
	ENEMY,
	PLAYER_BULLET,
	ENEMY_BULLET,
	PLAYER_UPGRADE_BULLET,
	PLAYER_BOMB,
	ITEM_HOVER_BOMB,
	ITEM_HOVER_POWERUP,
	ITEM_HOVER_MEDAL
};

enum class TaskType
{
	NONE,
	STOP,
	MOVE,
	MOVEAROUND,
	MOVESIN
};

struct Task
{
	TaskType type;
	FPOINT dest;
	float taskTime = 0.0f;
	float destRadian = 0.0f;
};