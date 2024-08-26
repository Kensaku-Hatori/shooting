#ifndef _PALYER_H_
#define _PLAYER_H_
#define Playerwidth (100)
#define Playerheight (100)
#define MIN_LIFE (100)
#define MIN_ATACK (10)
#define MIN_INTERVAL (6)
#define MIN_WAY (1)
typedef enum
{
	PLAYERSTATE_NORMAL = 0,	// プレイヤーが何もしていないときの状態
	PLAYERSTATE_DAMAGE,		// プレイヤーがダメージを食らったとき
	PLAYERSTATE_MAX
}PLAYERSTATE;
typedef struct
{
	D3DXVECTOR3 pos;		// 場所
	D3DXVECTOR3 rot;		// 向き
	PLAYERSTATE state;		// 状態
	int cooldown;
	int statecount;
	int nCountAnimPlayer;	// アニメーションカウント
	int nPatternAnimPlayer;	// アニメーションパターンNo
	float nLengthPlayer;	// 対角線の長さ
	float fAnglePlayer;		// 対角線の角度
	bool bUse;				// プレイヤーの使用状態
	int level;				// プレイヤーのレベル
	int nLife;				// プレイヤーのHP
	int atack;				// プレイヤーの攻撃力
	int interval;			// プレイヤーの攻撃間隔
	int way;				// プレイヤーが発射する玉の数
	int intervalcount;
}Player;


//================
//プロトタイプ宣言
//================
void InitPlayer(void);				// プレイヤーの初期化処理
void UninitPlayer(void);			// プレイヤーの終了処理
void UpdatePlayer(void);			// プレイヤー更新処理
void DrawPlayer(void);				// プレイヤーの描画処理
void HitPlayer(int nDamageEnemy);	// プレイヤーのヒット処理
Player*GetPlayer(void);				// プレイヤーの座標の取得処理
#endif