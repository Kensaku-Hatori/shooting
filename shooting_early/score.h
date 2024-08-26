#ifndef _SCORE_H_
//==============
// マクロ定義
//==============
#define _SCORE_H_

#include"main.h"

//======================
// プロトタイプ宣言
//======================
// スコアの初期化処理
void Initscore(void);
// スコアの終了処理
void Uninitscore(void);
// スコアの更新処理
void Updatescore(void);
// スコアの描画処理
void Drawscore(void);
// スコアの設定処理
void Setscore(int score);
// スコアの加算処理
void Addscore(int nvalue);
// スコアの桁数を数える処理
int score(int score);
#endif