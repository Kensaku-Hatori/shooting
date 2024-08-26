#include "enemy.h"
#include "bullet.h"
#include "input.h"
#include "exprotion.h"
#include"player.h"
#include"wave.h"
#include"item.h"

LPDIRECT3DTEXTURE9 g_pTextureEnemy[ENEMYTYPE_MAX] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;	//頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];//敵の情報
int g_nNumEnemy = 0;//敵の総数

//プレイヤーの初期化処理
void InitEnemy(void)
{
	int ncountenemy;
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy001.jpg",
		&g_pTextureEnemy[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D)*4*MAX_ENEMY,//確保したいバッファ数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL
	);
	VERTEX2D *pVtx;//頂点バッファへのポインタ
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得


	for (ncountenemy = 0; ncountenemy < MAX_ENEMY; ncountenemy++)
	{
		g_aEnemy[ncountenemy].move = D3DXVECTOR3(0.0f, 9.0f, 0.0f);
		g_aEnemy[ncountenemy].nType = 0;
		g_aEnemy[ncountenemy].nLife = 100;
		g_aEnemy[ncountenemy].statecount = 0;
		g_aEnemy[ncountenemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[ncountenemy].bUse = false;
		g_aEnemy[ncountenemy].atack = 10;
		g_nNumEnemy = 0;
		g_aEnemy[ncountenemy].cooldown = 0;
	}
	for (ncountenemy = 0; ncountenemy < MAX_ENEMY; ncountenemy++)
	{


		//rhwの設定
		pVtx[0].rhw = 1.0f;//値は1.0fで固定
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//RGBと透明度
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}
//プレイヤーの終了処理
void UninitEnemy(void)
{
	int ncountenemy;
	for (ncountenemy = 0; ncountenemy < ENEMYTYPE_MAX; ncountenemy++)
	{
		//テクスチャの破棄
		if (g_pTextureEnemy[ncountenemy] != NULL)
		{
			g_pTextureEnemy[ncountenemy]->Release();
			g_pTextureEnemy[ncountenemy] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy=NULL;
	}
}
//プレイヤーの更新処理
void UpdateEnemy(void)
{
	int ncountenemy;
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得
	for (ncountenemy = 0; ncountenemy < MAX_ENEMY; ncountenemy++)
	{
		if (g_aEnemy[ncountenemy].bUse == true)
		{
			switch (g_aEnemy[ncountenemy].state)
			{
			case ENEMYSTATE_NORMAL:
				g_aEnemy[ncountenemy].cooldowncount++;
				if (g_aEnemy[ncountenemy].cooldowncount >= g_aEnemy[ncountenemy].cooldown)
				{
					g_aEnemy[ncountenemy].cooldowncount = 0;
					g_aEnemy[ncountenemy].pos.y += g_aEnemy[ncountenemy].move.y;
				}
				break;
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[ncountenemy].statecount--;
				if (g_aEnemy[ncountenemy].statecount <= 0)
				{
					g_aEnemy[ncountenemy].statecount = 0;
					g_aEnemy[ncountenemy].state = ENEMYSTATE_NORMAL;
					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//RGBと透明度
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
			}
		}
		//一個目のポリゴン
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x - ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y - ENEMY_HEIGHT, 0.0f);//右回りゼロ番目
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x + ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y - ENEMY_HEIGHT, 0.0f);//一番目
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x - ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y + ENEMY_HEIGHT, 0.0f);//二番目
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x + ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y + ENEMY_HEIGHT, 0.0f);//三番目
		pVtx += 4;
	}
	g_pVtxBuffEnemy->Unlock();
}
//プレイヤーの描画処理
void DrawEnemy(void)
{
	int ncountenemy;
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX2D));

	for (ncountenemy = 0; ncountenemy < MAX_ENEMY; ncountenemy++)
	{
		if (g_aEnemy[ncountenemy].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEnemy[0]);//一つ目のポリゴン
 			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*ncountenemy, 2);
		}
	}
}
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int ncountenemy;
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得
	for(ncountenemy=0;ncountenemy<MAX_ENEMY;ncountenemy++)
	{
		if (g_aEnemy[ncountenemy].bUse == false)
		{
			g_aEnemy[ncountenemy].pos = pos;
			g_aEnemy[ncountenemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[ncountenemy].nLife = 100;
			g_aEnemy[ncountenemy].atack = 10;
			g_aEnemy[ncountenemy].nType = nType;
			g_aEnemy[ncountenemy].cooldown = 10;
			//一個目のポリゴン
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x-ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y-ENEMY_HEIGHT, 0.0f);//右回りゼロ番目
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x+ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y-ENEMY_HEIGHT, 0.0f);//一番目
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x-ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y+ ENEMY_HEIGHT, 0.0f);//二番目
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x+ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y+ ENEMY_HEIGHT, 0.0f);//三番目
			g_aEnemy[ncountenemy].bUse = true;
			g_nNumEnemy++;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffEnemy->Unlock();
}
void HitEnemy(int nCntEnemy, int nDamage)
{
	Player* pplayer = GetPlayer();
	WAVE* pwavestate = GetWave();
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife<=0)
	{
		g_nNumEnemy--;
		SetExprotion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(255, 255, 255, 255));
		g_aEnemy[nCntEnemy].bUse = false;
		int drop = rand() % 100 + 1;
		if (drop <= 30)
		{
			int item1 = rand() % (MAX_ITEMTYPE - 1) + 1;
			
			SetItem((ITEM_STATE)item1,g_aEnemy[nCntEnemy].pos);
		}
		if (g_nNumEnemy <= 0)
		{
 			pwavestate->nwavestate++;
			pwavestate->wavestate = (WAVE_STATE)pwavestate->nwavestate;
			pwavestate->waveflag = true;
			pplayer->level++;

			pplayer->nLife = pplayer->level * MIN_LIFE;
			pplayer->atack = pplayer->level * MIN_ATACK;
			pplayer->interval = MIN_INTERVAL / pplayer->level;
			pplayer->way = pplayer->level * MIN_WAY;
		}
 	}
	else
	{
		VERTEX2D* pVtx;//頂点バッファへのポインタ
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得
		pVtx += 4 * nCntEnemy;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].statecount = 5;
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);//RGBと透明度
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		g_pVtxBuffEnemy->Unlock();
	}
}
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}
int GetNumEnemy(void)
{
	return g_nNumEnemy;
}