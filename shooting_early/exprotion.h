#ifndef _EXPROTION_H_
#define _EXPROTION_H_
#include "main.h"
#define EXPROSION_WIDTH (100)
#define EXPROSION_HEITH (100)

typedef struct
{
	D3DXVECTOR3 pos;	// 爆発の位置
	D3DXCOLOR col;		// 爆発の色
	int nCountAnim;		// 爆発のアニメーションの間隔
	int nPatternAnim;	// 爆発のアニメーションの総数
	bool bUse;			// 爆発の使用状況
}Exprotion;


//================
//プロトタイプ宣言
//================
void InitExprotion(void);							// 爆発の初期化処理
void UninitExprotion(void);							// 爆発の終了処理
void UpdateExprotion(void);							// 爆発の更新処理
void DrawExprotion(void);							// 爆発の描画処理
void SetExprotion(D3DXVECTOR3 pos, D3DXCOLOR col);	// 爆発の設定処理
Exprotion *GetExprosion(void);						// 爆発の座標取得処理
#endif