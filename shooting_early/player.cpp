#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include"score.h"
#include "exprotion.h"
#include"cusor.h"

LPDIRECT3DTEXTURE9 g_pTexturePlayer1 = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファへのポインタ
Player g_player;


//プレイヤーの初期化処理
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\spaceShips_001.png",
		&g_pTexturePlayer1);

	g_player.pos = D3DXVECTOR3(WINDOW_WIDTH / 2, WINDOW_HEITH, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.nLengthPlayer = sqrtf(Playerwidth * Playerwidth + Playerheight * Playerheight);
	g_player.fAnglePlayer = atan2f(Playerwidth, Playerheight);
	g_player.bUse = true;
	g_player.level = 1;
	g_player.nLife = MIN_LIFE;
	g_player.atack = MIN_ATACK;
	g_player.interval = MIN_INTERVAL;
	g_player.way = MIN_WAY;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D)*4,//確保したいバッファ数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL
	);
	VERTEX2D *pVtx;//頂点バッファへのポインタ
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得

	//頂点座標の更新			
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI + g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.y - 25.0f;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI + g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.x - 150.0f;
	pVtx[0].pos.z = 0.0f;//0.0f;
	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.x + 150.0f;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.y - 25.0f;
	pVtx[1].pos.z = 0.0f;//0.0f;
	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.x - 150.0f;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.y + 25.0f;
	pVtx[2].pos.z = 0.0f;//0.0f;
	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.x + 150.0f;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.y + 25.0f;
	pVtx[3].pos.z = 0.0f;

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

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}
//プレイヤーの終了処理
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer1 != NULL)
	{
		g_pTexturePlayer1->Release();
		g_pTexturePlayer1 = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer=NULL;
	}
}
//プレイヤーの更新処理
void UpdatePlayer(void)
{
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得

	Cursor *pcursor = GetCursor1();

	if (g_player.intervalcount <= MIN_INTERVAL)
	{
		g_player.intervalcount++;
	}

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_player.statecount--;
		if (g_player.statecount <= 0)
		{
			g_player.statecount = 0;
			g_player.state = PLAYERSTATE_NORMAL;
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//RGBと透明度
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		break;
	}
		if (KeyboardTrigger(DIK_SPACE) || JoyPadTrigger(JOYKEY_A))
		{
			if (g_player.interval <= g_player.intervalcount)
			{
				g_player.intervalcount = 0;
				for (int i = 0; i < g_player.way; i++)
				{
					SetBullet
					(
						g_player.pos,
						D3DXVECTOR3
						(
							sinf(g_player.rot.z) * 20.0f,
							cosf(g_player.rot.z) * 20.0f,
							0.0f
						),
						BULLETTYPE_PLAYER,
						sqrtf(BULLED_WIDTH * BULLED_WIDTH + BULLED_HEIGHT * BULLED_HEIGHT),
						atan2f(BULLED_WIDTH, BULLED_HEIGHT),
						g_player.rot,
						pcursor->pos
					);
				}
			}
		}

		if (g_player.bUse == true)
		{
			switch (g_player.state)
			{
			case ENEMYSTATE_DAMAGE:
				g_player.statecount--;
				if (g_player.statecount <= 0)
				{
					g_player.state = PLAYERSTATE_NORMAL;
					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//RGBと透明度
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
			}
		}

		g_player.rot.z = atan2f(pcursor->pos.x - g_player.pos.x, pcursor->pos.y - g_player.pos.y),
		pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z - (D3DX_PI - g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z - (D3DX_PI - g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[3].pos.z = 0.0f;
		g_pVtxBuffPlayer->Unlock();
}
//プレイヤーの描画処理
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX2D));

	if (g_player.bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer1);//一つ目のポリゴン
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
void HitPlayer(int nDamageEnemy)
{
	g_player.nLife -= nDamageEnemy;
	if (g_player.nLife <= 0)
	{
		SetExprotion(g_player.pos, D3DXCOLOR(255, 255, 255, 255));
		g_player.bUse = false;
	}
	else
	{
		VERTEX2D* pVtx;//頂点バッファへのポインタ
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.statecount = 5;
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);//RGBと透明度
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		g_pVtxBuffPlayer->Unlock();
	}
}
Player* GetPlayer(void)
{
	return &g_player;
}