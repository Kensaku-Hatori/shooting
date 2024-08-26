#include"main.h"
#include"enemy.h"
#include"game.h"

#define MAX_ITEM (128)

typedef enum
{
	NONE_ITEM=0,
	BOM_ITEM,
	SCOREUP_ITEM,
	MAX_ITEMTYPE
}ITEM_STATE;

typedef struct
{
	bool bUse;				// ウェーブの使用状況
	ITEM_STATE Itemstate;	// ウェーブの状態
	int ncountItemAnim;			// ウェーブの敵が現れる間隔をカウント
	int ncountItemAnimPetternX;
	int ncountItemAnimPetternY;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
}ITEM;


//================
//プロトタイプ宣言
//================
void InitItem(void);	// ウェーブの初期化処理
void UninitItem(void);	// ウェーブの終了処理
void UpdateItem(void);	// ウェーブの更新処理
void DrawItem(void);	// ウェーブの描画処理
void SetItem(ITEM_STATE itemtype,D3DXVECTOR3 pos);			// ウェーブの設定処理
ITEM* GetItem(void);	// ウェーブ数の取得処理