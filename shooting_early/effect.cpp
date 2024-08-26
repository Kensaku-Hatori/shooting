#include "main.h"
#include "player.h"
#include "input.h"
#include "Effect.h"
#include "Exprotion.h"
#include "enemy.h"
#include "effect.h"
#include"bullet.h"
#define MAX_EFFECT (4096)//弾の最大数
#define EFFECT_LIFE (20)
typedef struct
{
	D3DXVECTOR3 pos;//弾の位置
	D3DXVECTOR3 exprotionpos;
	D3DXVECTOR3 move;//弾の移動量
	int nLife;//弾の寿命
	BULLETTYPE type;
	bool bUse;
	D3DXVECTOR3 rot;
	float fLength;
	float fAngle;
	float faduce;
}EFFECT;

LPDIRECT3DTEXTURE9 g_pTextureEffect1 = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//頂点バッファへのポインタ
EFFECT g_aEffect[MAX_EFFECT] = {};
void InitEffect(void)		//プレイヤー用
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCountEffect;
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect1);
	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		g_aEffect[nCountEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCountEffect].exprotionpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCountEffect].nLife = EFFECT_LIFE;
		g_aEffect[nCountEffect].bUse = false;
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4*MAX_EFFECT,//確保したいバッファ数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL
	);
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得

	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)//弾の初期化１２８回
	{
		//一個目のポリゴン
		pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);//右回りゼロ番目
		pVtx[1].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);//一番目
		pVtx[2].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);//二番目
		pVtx[3].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);//三番目

		//rhwの設定
		pVtx[0].rhw = 1.0f;//値は1.0fで固定
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);//RGBと透明度
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点バッファのポインタを４つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}
//プレイヤーの終了処理
void UninitEffect(void)
{
	//テクスチャの破棄
	if (g_pTextureEffect1 != NULL)
	{
		g_pTextureEffect1->Release();
		g_pTextureEffect1 = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
void UpdateEffect(void)
{
	int nCountEffect;

	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得

	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		if (g_aEffect[nCountEffect].bUse == true)//弾が使用されていたら
		{
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);//RGBと透明度
			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

			//頂点座標の更新
			pVtx[0].pos.x = (g_aEffect[nCountEffect].pos.x + sinf(g_aEffect[nCountEffect].rot.z + (D3DX_PI + g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.y - 25.0f;
			pVtx[0].pos.y = (g_aEffect[nCountEffect].pos.y + cosf(g_aEffect[nCountEffect].rot.z + (D3DX_PI + g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.x - 150.0f;
			pVtx[0].pos.z = 0.0f;//0.0f;
			pVtx[1].pos.x = (g_aEffect[nCountEffect].pos.x + sinf(g_aEffect[nCountEffect].rot.z + (D3DX_PI - g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.x + 150.0f;
			pVtx[1].pos.y = (g_aEffect[nCountEffect].pos.y + cosf(g_aEffect[nCountEffect].rot.z + (D3DX_PI - g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.y - 25.0f;
			pVtx[1].pos.z = 0.0f;//0.0f;
			pVtx[2].pos.x = (g_aEffect[nCountEffect].pos.x + sinf(g_aEffect[nCountEffect].rot.z + (0.0f - g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.x - 150.0f;
			pVtx[2].pos.y = (g_aEffect[nCountEffect].pos.y + cosf(g_aEffect[nCountEffect].rot.z + (0.0f - g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.y + 25.0f;
			pVtx[2].pos.z = 0.0f;//0.0f;
			pVtx[3].pos.x = (g_aEffect[nCountEffect].pos.x + sinf(g_aEffect[nCountEffect].rot.z + (0.0f + g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.x + 150.0f;
			pVtx[3].pos.y = (g_aEffect[nCountEffect].pos.y + cosf(g_aEffect[nCountEffect].rot.z + (0.0f + g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.y + 25.0f;
			pVtx[3].pos.z = 0.0f;

			g_aEffect[nCountEffect].nLife--;
			g_aEffect[nCountEffect].fLength -= 5;
			if (g_aEffect[nCountEffect].nLife <= 0)
			{
				g_aEffect[nCountEffect].bUse = false;
			}
		}
		pVtx += 4;
	}

	g_pVtxBuffEffect->Unlock();
}
//プレイヤーの描画処理
void DrawEffect(void)
{
	int ncount;
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX2D));

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (ncount = 0; ncount < MAX_EFFECT; ncount++)
	{
		if (g_aEffect[ncount].bUse == true)
		{
			//テクスチャの設定 
			pDevice->SetTexture(0, g_pTextureEffect1);//一つ目のポリゴン
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,ncount*4,2);
		}
	}

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//弾の設定処理
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,float fLength,float fAngle,D3DXVECTOR3 rot)
{
	int nCountEffect;
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得
	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		if (g_aEffect[nCountEffect].bUse == false)
		{//弾が使用されていない
			g_aEffect[nCountEffect].fLength = fLength,
			g_aEffect[nCountEffect].rot = rot;
			g_aEffect[nCountEffect].fAngle = fAngle;
			g_aEffect[nCountEffect].pos = pos;
			g_aEffect[nCountEffect].type = type;
			g_aEffect[nCountEffect].nLife = EFFECT_LIFE;
			g_aEffect[nCountEffect].bUse = true;//使用している状態にする

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffEffect->Unlock();
 }