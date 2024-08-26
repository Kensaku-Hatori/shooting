#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"

#define BULLED_WIDTH (100)
#define BULLED_HEIGHT (100)
typedef enum
{
	BULLETTYPE_PLAYER=0,// 弾の属性がプレイヤーの時
	BULLETTYPE_ENEMY,	// 弾の属性が敵の時
	BULLETTYPE_MAX
}BULLETTYPE;


//================
//プロトタイプ宣言
//================
void InitBullet(void);		// 弾の初期化処理
void UninitBullet(void);	// 弾の終了処理
void UpdateBullet(void);	// 弾更新処理
void DrawBullet(void);		// 弾の描画処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,float fLength, float fAngle, D3DXVECTOR3 rot,D3DXVECTOR3 expos);// 弾の設定処理
#endif