#ifndef _FADE_H_
#define _FADE_H_
#include"main.h"
typedef enum
{
	FADE_NONE = 0,	//フェードの状態
	FADE_IN,		// フェードINの状態
	FADE_OUT,		// フェードOUTの状態
	FADE_MAX
}FADE;


//================
//プロトタイプ宣言
//================
void InitFade(MODE modeNext);	// フェードの初期化処理
void UninitFade(void);			// フェードの終了処理
void UpdateFade(void);			// フェードの更新処理
void DrawFade(void);			// フェードの描画処理
void SetFade(MODE modeNext);	// フェードの設定処理
FADE GetFade(void);				// フェードの状態の取得処理
#endif