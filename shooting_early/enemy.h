#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h" 
#define MAX_ENEMY (128)
#define ENEMY_WIDTH (50)
#define ENEMY_HEIGHT (50)
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_MAX
}ENEMYSTATE;

typedef enum
{
	ENEMYTYPE_ONE = 0,
	ENEMYTYPE_TWE,
	ENEMYTYPE_MAX
}ENEMYTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	// 敵の位置
	D3DXVECTOR3 move;	// 敵の移動量
	D3DXVECTOR3 rot;	// 敵の向き
	ENEMYSTATE state;	// 敵の状態
	int cooldown;		// 敵の出現間隔
	int cooldowncount;	// 敵の出現間隔のカウントダウン
	int statecount;		// 敵の状態の時間をカウント
	int nLife;			// 敵のHP
	int nType;			// 敵の種類
	bool bUse;			// 敵の使用状況
	int atack;			// 敵の攻撃力
}Enemy;


//================
//プロトタイプ宣言
//================
void InitEnemy(void);						// 敵の初期化処理
void UninitEnemy(void);						// 敵の終了処理
void UpdateEnemy(void);						// 敵の更新処理
void DrawEnemy(void);						// 敵の描画処理
void SetEnemy(D3DXVECTOR3 pos, int nType);	// 敵の設定処理
void HitEnemy(int nCntEnemy, int nDamage);	// 敵のヒット処理
int GetNumEnemy();							// 敵の総数を取得
Enemy* GetEnemy(void);						// 敵の座標取得処理
#endif