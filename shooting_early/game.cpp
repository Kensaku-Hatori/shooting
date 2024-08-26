#include "bg.h"
#include "bullet.h"
#include "exprotion.h"
#include "game.h"
#include "enemy.h"
#include "player.h"
#include "fade.h"
#include "score.h"
#include"cusor.h"
#include"wave.h"
#include"item.h"
#include"effect.h"


GAMESTATE g_gamestate = GAMESTATE_NONE;
int ncountergamestate = 0;
void InitGame(void)
{
	Initbackground();//背景の初期化処理
	InitCursor();
	Initscore();
	InitWave();
	InitItem();
	InitEffect();
	InitPlayer();//プレイヤーの初期化処理
	InitBullet();//プレイヤーの初期化処理
	InitExprotion();//プレイヤーの初期化処理
	InitEnemy();//プレイヤーの初期化処理
	SetEnemy(D3DXVECTOR3(600.0f, 300.0f, 0.0f), 1);
	//SetEnemy(D3DXVECTOR3(300.0f, 600.0f, 0.0f), 1);
	g_gamestate = GAMESTATE_NORMAL;
	ncountergamestate = 0;
}
void UninitGame(void)
{
	Uninitbackground();//背景の終了処理
	UninitCursor();
	Uninitscore();
	UninitWave();
	UninitItem();
	UninitEffect();
	UninitPlayer();//プレイヤーの終了処理
	UninitBullet();//プレイヤーの終了処理
	UninitExprotion();//プレイヤーの終了処理
	UninitEnemy();//プレイヤーの終了処理
}
void UpdateGame(void)
{
	srand((unsigned int)time(NULL));
	Updatebackground();//背景の更新処理
	UpdateCursor();
	Updatescore();
	UpdateWave();
	UpdateItem();
	UpdatePlayer();//プレイヤーの更新処理
	UpdateBullet();//プレイヤーの更新処理
	UpdateEffect();
	UpdateExprotion();//プレイヤーの更新処理
	UpdateEnemy();//プレイヤーの更新処理
	int Num = GetNumEnemy();
	Player* player = GetPlayer();
	if (player->bUse == false)
	{
		g_gamestate = GAMESTATE_END;
	}
	switch (g_gamestate)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_END:
		ncountergamestate++;
		if (ncountergamestate >= 60)
		{
			ncountergamestate = 0;
			g_gamestate = GAMESTATE_NONE;
			SetFade(MODE_RESULT);
		}
		break;
	}
}
void DrawGame(void)
{
	Drawbackground();//背景の描画処理
	Drawscore();
	DrawItem();
	DrawEffect();
	DrawPlayer();//プレイヤーの描画処理
	DrawBullet();//プレイヤーの描画処理
	DrawExprotion();//プレイヤーの描画処理
	DrawEnemy();//プレイヤーの描画処理
	DrawCursor();
}
void SetState(GAMESTATE state)
{
	g_gamestate = state;
}
GAMESTATE Getgamestate()
{
	return g_gamestate;
}