#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "Exprotion.h"
#include "enemy.h"
#include"effect.h"
#define MAX_Bullet (128)//弾の最大数
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
}Bullet;

LPDIRECT3DTEXTURE9 g_pTextureBullet1 = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//頂点バッファへのポインタ
Bullet g_aBullet[MAX_Bullet] = {};
void InitBullet(void)		//プレイヤー用
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCountBullet;
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bullet.png",
		&g_pTextureBullet1);
	for (nCountBullet = 0; nCountBullet < MAX_Bullet; nCountBullet++)
	{
		g_aBullet[nCountBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCountBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCountBullet].exprotionpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCountBullet].fAngle = 0.0f;
		g_aBullet[nCountBullet].fLength = 0.0f;
		g_aBullet[nCountBullet].nLife = 0;
		g_aBullet[nCountBullet].bUse = false;
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4*MAX_Bullet,//確保したいバッファ数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL
	);
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得

	for (nCountBullet = 0; nCountBullet < MAX_Bullet; nCountBullet++)//弾の初期化１２８回
	{
		//一個目のポリゴン
		pVtx[0].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z - (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y - 25.0f;
		pVtx[0].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z - (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x - 150.0f;
		pVtx[0].pos.z = 0.0f;//0.0f;
		pVtx[1].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z + (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x + 150.0f;
		pVtx[1].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z + (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y - 25.0f;
		pVtx[1].pos.z = 0.0f;//0.0f;
		pVtx[2].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z + (0.0f - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x - 150.0f;
		pVtx[2].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z + (0.0f - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y + 25.0f;
		pVtx[2].pos.z = 0.0f;//0.0f;
		pVtx[3].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z + (0.0f + g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x + 150.0f;
		pVtx[3].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z + (0.0f + g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y + 25.0f;
		pVtx[3].pos.z = 0.0f;


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
	g_pVtxBuffBullet->Unlock();
}
//プレイヤーの終了処理
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet1 != NULL)
	{
		g_pTextureBullet1->Release();
		g_pTextureBullet1 = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
void UpdateBullet(void)
{
	int nCountBullet;
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得

	for (nCountBullet = 0; nCountBullet < MAX_Bullet; nCountBullet++)
	{
		if (g_aBullet[nCountBullet].bUse == true)//弾が使用されていたら
		{
			if (g_aBullet[nCountBullet].type == BULLETTYPE_PLAYER)
			{
				int ncountenemy;
				Player* pPlayer = GetPlayer();
				Enemy* pEnemy = GetEnemy();
				Exprotion* pExprotion = GetExprosion();
				for (ncountenemy = 0; ncountenemy < MAX_ENEMY; ncountenemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (g_aBullet[nCountBullet].pos.x >= g_aBullet[nCountBullet].exprotionpos.x - EXPROSION_WIDTH
							&& g_aBullet[nCountBullet].pos.x <= g_aBullet[nCountBullet].exprotionpos.x + EXPROSION_WIDTH
							&& g_aBullet[nCountBullet].pos.y >= g_aBullet[nCountBullet].exprotionpos.y - EXPROSION_HEITH
							&& g_aBullet[nCountBullet].pos.y <= g_aBullet[nCountBullet].exprotionpos.y + EXPROSION_HEITH
							)
						{
							SetExprotion(g_aBullet[nCountBullet].exprotionpos, D3DXCOLOR(255, 255, 255, 255));
							g_aBullet[nCountBullet].bUse = false;
							if (pExprotion->pos.x >= pEnemy->pos.x - ENEMY_WIDTH*2
								&& pExprotion->pos.x <= pEnemy->pos.x + ENEMY_WIDTH*2
								&& pExprotion->pos.y >= pEnemy->pos.y - ENEMY_HEIGHT*2
								&& pExprotion->pos.y <= pEnemy->pos.y + ENEMY_HEIGHT*2
								)
							{
								HitEnemy(ncountenemy, pPlayer->atack);
							}
						}
					}
					pEnemy++;
					pExprotion++;
				}
			}
			else if (g_aBullet[nCountBullet].type == BULLETTYPE_ENEMY)
			{
				Player* pPlayer = GetPlayer();
				Enemy* pEnemy = GetEnemy();
				//if (pPlayer->bUse == true)
				//{
				//	if (g_aBullet[nCountBullet].pos.x >= pPlayer->pos.x - 100
				//		&& g_aBullet[nCountBullet].pos.x <= pPlayer->pos.x + 100
				//		&& g_aBullet[nCountBullet].pos.y >= pPlayer->pos.y - 50
				//		&& g_aBullet[nCountBullet].pos.y <= pPlayer->pos.y + 50
				//		)
				//	{
				//		HitPlayer(pEnemy->atack);
				//		g_aBullet[nCountBullet].bUse = false;
				//	}
				//}
			}
			g_aBullet[nCountBullet].pos.x += g_aBullet[nCountBullet].move.x;
			g_aBullet[nCountBullet].pos.y += g_aBullet[nCountBullet].move.y;

			//頂点座標の更新
			pVtx[0].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z - (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y - 25.0f;
			pVtx[0].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z - (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x - 150.0f;
			pVtx[0].pos.z = 0.0f;//0.0f;
			pVtx[1].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z + (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x + 150.0f;
			pVtx[1].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z + (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y - 25.0f;
			pVtx[1].pos.z = 0.0f;//0.0f;
			pVtx[2].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z + (0.0f - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x - 150.0f;
			pVtx[2].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z + (0.0f - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y + 25.0f;
			pVtx[2].pos.z = 0.0f;//0.0f;
			pVtx[3].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z + (0.0f + g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x + 150.0f;
			pVtx[3].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z + (0.0f + g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y + 25.0f;
			pVtx[3].pos.z = 0.0f;

			SetEffect(g_aBullet[nCountBullet].pos,
				g_aBullet[nCountBullet].move,
				BULLETTYPE_PLAYER,
				90,
				g_aBullet[nCountBullet].fAngle,
				g_aBullet[nCountBullet].rot);

			if (g_aBullet[nCountBullet].pos.x >= WINDOW_WIDTH||g_aBullet[nCountBullet].pos.x<=0|| g_aBullet[nCountBullet].pos.y >= WINDOW_HEITH || g_aBullet[nCountBullet].pos.y <= 40)
			{
				SetExprotion(g_aBullet[nCountBullet].pos,D3DXCOLOR(255,255,255,255));
				g_aBullet[nCountBullet].bUse = false;
			}
		}
		pVtx += 4;//頂点バッファのポインタを４つ分進める
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		Enemy* pEnemy = GetEnemy();
		if (pEnemy->bUse == true)
		{
			if (pEnemy->pos.y + ENEMY_HEIGHT >= WINDOW_HEITH)
			{
				HitEnemy(i,9999);
				HitPlayer(1);
			}
		}
		pEnemy++;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}
//プレイヤーの描画処理
void DrawBullet(void)
{
	int ncount;
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX2D));

	for (ncount = 0; ncount < MAX_Bullet; ncount++)
	{
		if (g_aBullet[ncount].bUse == true)
		{
			//テクスチャの設定 
			pDevice->SetTexture(0, g_pTextureBullet1);//一つ目のポリゴン
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,ncount*4,2);
		}
	}
}
//弾の設定処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,float fLength,float fAngle,D3DXVECTOR3 rot,D3DXVECTOR3 expos)
{
	int nCountBullet;
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得
	for (nCountBullet = 0; nCountBullet < MAX_Bullet; nCountBullet++)
	{
		if (g_aBullet[nCountBullet].bUse == false)
		{//弾が使用されていない
			g_aBullet[nCountBullet].rot = rot;
			g_aBullet[nCountBullet].fLength = fLength;
			g_aBullet[nCountBullet].fAngle = fAngle;
			g_aBullet[nCountBullet].pos = pos;
			g_aBullet[nCountBullet].move = move;
			g_aBullet[nCountBullet].type = type;
			g_aBullet[nCountBullet].exprotionpos = expos;
			g_aBullet[nCountBullet].bUse = true;//使用している状態にする

			pVtx[0].pos.x = pos.x + sinf(rot.z - (D3DX_PI - fAngle)) * fLength;//pos.y - 25.0f;
			pVtx[0].pos.y = pos.y + cosf(rot.z - (D3DX_PI - fAngle)) * fLength;//pos.x - 150.0f;
			pVtx[0].pos.z = 0.0f;//0.0f;
			pVtx[1].pos.x = pos.x + sinf(rot.z + (D3DX_PI - fAngle)) * fLength;//pos.x + 150.0f;
			pVtx[1].pos.y = pos.y + cosf(rot.z + (D3DX_PI - fAngle)) * fLength;//pos.y - 25.0f;
			pVtx[1].pos.z = 0.0f;//0.0f;
			pVtx[2].pos.x = pos.x + sinf(rot.z + (0.0f - fAngle)) * fLength;//pos.x - 150.0f;
			pVtx[2].pos.y = pos.y + cosf(rot.z + (0.0f - fAngle)) * fLength;//pos.y + 25.0f;
			pVtx[2].pos.z = 0.0f;//0.0f;
			pVtx[3].pos.x = pos.x + sinf(rot.z + (0.0f + fAngle)) * fLength;//pos.x + 150.0f;
			pVtx[3].pos.y = pos.y + cosf(rot.z + (0.0f + fAngle)) * fLength;//pos.y + 25.0f;
			pVtx[3].pos.z = 0.0f;

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
 }