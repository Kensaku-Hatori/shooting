#ifndef _CURSOR_H_
#define _CURSOR_H_
#include"main.h"
#define Cursorwidth (50)
#define Cursorheight (50)
#define CURSOR_MOVE_X (6)
#define CURSOR_MOVE_Y (6)

typedef struct
{
	D3DXVECTOR3 pos;		// カーソルの場所
	D3DXVECTOR3 move;		// カーソルの移動量
	D3DXVECTOR3 rot;		// カーソルの向き
	float nLengthCusor;		// 対角線の長さ
	float fAngleCusor;		// 対角線の角度
	bool bUse;				// カーソルの使用状況
}Cursor;


//================
//プロトタイプ宣言
//================
void InitCursor(void);		// カーソルの初期化処理
void UninitCursor(void);	// カーソルの終了処理
void UpdateCursor(void);	// カーソルの更新処理
void DrawCursor(void);		// カーソルの描画処理
Cursor* GetCursor1(void);	// カーソルの座標の取得処理
#endif