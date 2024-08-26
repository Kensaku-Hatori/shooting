#include"main.h"
#include"enemy.h"
#include"game.h"

#define WAVE_ENEMY (1)

typedef enum
{
	NONE_WAVE = 0,
	FIRST_WAVE,
	SECOND_WAVE,
	THIRD_WAVE,
	FOURTH_WAVE,
	FIFTH_WAVE,
	END_WAVE,
	MAX_WAVE
}WAVE_STATE;

typedef struct
{
	bool bUse;				// ウェーブの使用状況
	WAVE_STATE wavestate;	// ウェーブの状態
	int nwavestate;
	int timecount;			// ウェーブの敵が現れる間隔をカウント
	int wavecount;
	bool waveflag;
	int waveenemycount;
}WAVE;


//================
//プロトタイプ宣言
//================
void InitWave(void);	// ウェーブの初期化処理
void UninitWave(void);	// ウェーブの終了処理
void UpdateWave(void);	// ウェーブの更新処理
void DrawWave(void);	// ウェーブの描画処理
void SetWave();			// ウェーブの設定処理
WAVE* GetWave(void);	// ウェーブ数の取得処理