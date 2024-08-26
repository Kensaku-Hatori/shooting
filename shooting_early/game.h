#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
typedef enum
{
	GAMESTATE_NONE = 0,	// 何もしていない状態
	GAMESTATE_NORMAL,	// 通常状態
	GAMESTATE_END,		// 終了状態
	GAMESTATE_MAX
}GAMESTATE;


//================
//プロトタイプ宣言
//================
void InitGame(void);			// ゲームの初期化処理
void UninitGame(void);			// ゲームの終了処理
void UpdateGame(void);			// ゲームの更新処理
void DrawGame(void);			// ゲームの描画処理
void SetState(GAMESTATE state);	// ゲームの設定処理
GAMESTATE GetState(void);		// ゲームの状態を取得処理
#endif // !_GAME_H_