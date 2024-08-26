#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
#include"bullet.h"
#define EFFECT_WIDTH (100)
#define EFFECT_HEIGHT (100)


//================
//プロトタイプ宣言
//================
void InitEffect(void);		// 弾の初期化処理
void UninitEffect(void);	// 弾の終了処理
void UpdateEffect(void);	// 弾更新処理
void DrawEffect(void);		// 弾の描画処理
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,float fLength, float fAngle, D3DXVECTOR3 rot);// 弾の設定処理
#endif