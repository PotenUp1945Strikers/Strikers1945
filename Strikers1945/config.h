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
#define TARGETTING_BULLET_PATH "Image/TargettingBullet.bmp"
#define AROUND_BULLET_PATH "Image/AroundBullet.bmp"
#define TANK_PATH "Image/Tank.bmp"
#define ENEMY1_PATH "Image/Enemy1.bmp"
#define ENEMY2_PATH "Image/Enemy2.bmp"
#define ENEMY3_PATH "Image/Enemy3.bmp"
#define MID_ENEMY1_PATH "Image/MidEnemy1.bmp"
#define MID_ENEMY2_PATH "Image/MidEnemy2.bmp"
#define BOSS_PATH "Image/StageBoss.bmp"
#define BOMB_PLANE_PATH "Image/BombPlane.bmp"
#define BOMB_MINIBOMB_PATH "Image/MiniBomb.bmp"
#define BOMB_EFFECT_PATH "Image/playerBomb.bmp"
#define ITEM_HOVERBOMB_PATH "Image/HoverBomb.bmp"
#define ITEM_HOVERPOWERUP_PATH "Image/powerUp.bmp"
#define ITEM_HOVERMEDAL_PATH "Image/medal.bmp"
#define HIT_EFFECT_PATH "Image/hitEffect.bmp"
#define BOMB_EFFECT_PATH "Image/bombEffect.bmp"
#define EFFECT1_PATH "Image/Effect1.bmp"
#define EFFECT2_PATH "Image/Effect2.bmp"
#define EFFECT3_PATH "Image/Effect3.bmp"

#define PLAYER_BULLET1_PATH "Image/PlayerBullet1.bmp"
#define PLAYER_BULLET2_PATH "Image/PlayerBullet2.bmp"
#define PLAYER_BULLET3_PATH "Image/PlayerBullet3.bmp"
#define PLAYER_BULLET4_PATH "Image/PlayerBullet4.bmp"

#define BACKGROUND_SPEED 120
#define BACKGROUND_SIZE 4781

#define INVINCIBILITY_TIME 0.8f
#define HIT_RENDER_TIME 0.15f
#define ANIMATION_FRAME_TIME 0.1f

#define PLAYER_START_MOVE "PlayerMoveIn"
#define PLAYER_END_MOVE "PlayerMoveOut"

#define MAX_GAME_LENGTH 30000
#define MAX_MISSILE	30
#define MAX_ENEMY_PLANE 10

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

enum class PlaneRenderType : UINT8
{
	NONE,
	NORMAL,
	DIR,
	DIR_X,
	TANK
};

typedef struct tagPlaneType
{
	const wchar_t*	key;
	float			speed;
	int				health;
	RECT			size;
	FPOINT			missilePos;
	FPOINT			centerPos;
	int				maxFrameX;
	PlaneRenderType	renderType;
	const wchar_t*	missileType;
} PlaneType;

enum class MissileKind
{
	None,
	Basic,
	Targetting,
	Around
};

typedef struct tagMissileType
{
	const wchar_t*	key;
	float			missileSpeed;
	float			shootRate;
	int				damage;
	float			reloadRate;
	int				missileAmount;
	RECT			size;
	const wchar_t*	upgrade;
	int				maxFrameX;
	MissileKind		missileKind;

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

enum class Type : UINT8
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

enum class TaskType : UINT8
{
	NONE,
	STOP,
	MOVE,
	MOVEAROUND,
	MOVECURVE
};

struct Task
{
	TaskType	type;
	FPOINT		dest;
	FPOINT		control;
	float		taskTime;
	float		destRadian;
	bool		loop;
	size_t		loopIndex;
};

enum class EnemyType : UINT8
{
	NONE,
	PLANE,
	MIDDLE,
	TANK,
	BOSS
};

typedef struct tagStageScript
{
	EnemyType		type;
	const wchar_t*	key;
	vector<Task>*	path;
	FPOINT			pos;
	float			appeared;
	bool			bomb;
	bool			item;
}StageScript;
