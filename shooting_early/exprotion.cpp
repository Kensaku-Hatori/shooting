#include "main.h"
#include "player.h"
#include "input.h"
#include "Exprotion.h"
#define MAX_Exprotion (128)//弾の最大数
LPDIRECT3DTEXTURE9 g_pTextureExprotion1 = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExprotion = NULL;	//頂点バッファへのポインタ
Exprotion g_aExprotion[MAX_Exprotion];
void InitExprotion(void)		//プレイヤー用
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCountExprotion;
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExprotion1);
	for (nCountExprotion = 0; nCountExprotion < MAX_Exprotion; nCountExprotion++)
	{
		g_aExprotion[nCountExprotion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExprotion[nCountExprotion].nCountAnim = 0;
		g_aExprotion[nCountExprotion].nPatternAnim = 0;
		g_aExprotion[nCountExprotion].col = D3DCOLOR(0.0);
		g_aExprotion[nCountExprotion].bUse = false;
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4*MAX_Exprotion,//確保したいバッファ数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExprotion,
		NULL
	);
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffExprotion->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得

	for (nCountExprotion = 0; nCountExprotion < MAX_Exprotion; nCountExprotion++)//弾の初期化１２８回
	{
		//一個目のポリゴン
		pVtx[0].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x, g_aExprotion[nCountExprotion].pos.y-50.0f, 0.0f);//右回りゼロ番目
		pVtx[1].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x + 100, g_aExprotion[nCountExprotion].pos.y -50.0f, 0.0f);//一番目
		pVtx[2].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x, g_aExprotion[nCountExprotion].pos.y+30.0f, 0.0f);//二番目
		pVtx[3].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x + 100, g_aExprotion[nCountExprotion].pos.y+30.0f, 0.0f);//三番目

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;//頂点バッファのポインタを４つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExprotion->Unlock();
}
//プレイヤーの終了処理
void UninitExprotion(void)
{
	//テクスチャの破棄
	if (g_pTextureExprotion1 != NULL)
	{
		g_pTextureExprotion1->Release();
		g_pTextureExprotion1 = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffExprotion != NULL)
	{
		g_pVtxBuffExprotion->Release();
		g_pVtxBuffExprotion = NULL;
	}
}
void UpdateExprotion(void)
{
	int nCountExprotion;
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffExprotion->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得

	for (nCountExprotion = 0; nCountExprotion < MAX_Exprotion; nCountExprotion++)
	{
		if (g_aExprotion[nCountExprotion].bUse == true)//弾が使用されていたら
		{
			g_aExprotion[nCountExprotion].nCountAnim++;
			if (g_aExprotion[nCountExprotion].nCountAnim >= 5)
			{
				g_aExprotion[nCountExprotion].nCountAnim = 0;
				g_aExprotion[nCountExprotion].nPatternAnim++;
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f+g_aExprotion[nCountExprotion].nPatternAnim*0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f+g_aExprotion[nCountExprotion].nPatternAnim * 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + g_aExprotion[nCountExprotion].nPatternAnim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + g_aExprotion[nCountExprotion].nPatternAnim * 0.125f, 1.0f);
			}
			if (g_aExprotion[nCountExprotion].nPatternAnim>=8)
			{
				g_aExprotion[nCountExprotion].nPatternAnim = 0;
				g_aExprotion[nCountExprotion].bUse = false;
			}
		}
		pVtx += 4;//頂点バッファのポインタを４つ分進める
	}
	g_pVtxBuffExprotion->Unlock();
}
//プレイヤーの描画処理
void DrawExprotion(void)
{
	int ncount;
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffExprotion, 0, sizeof(VERTEX2D));

	for (ncount = 0; ncount < MAX_Exprotion; ncount++)
	{
		if (g_aExprotion[ncount].bUse == true)
		{
			//テクスチャの設定 
			pDevice->SetTexture(0, g_pTextureExprotion1);//一つ目のポリゴン
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4*ncount,2);
		}
	}
}
//弾の設定処理
void SetExprotion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCountExprotion;
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffExprotion->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得
	for (nCountExprotion = 0; nCountExprotion < MAX_Exprotion; nCountExprotion++)
	{
		if (g_aExprotion[nCountExprotion].bUse == false)
		{
			g_aExprotion[nCountExprotion].pos = pos;
			g_aExprotion[nCountExprotion].col = col;
			g_aExprotion[nCountExprotion].bUse = true;
			//一個目のポリゴン
			pVtx[0].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x-EXPROSION_WIDTH, g_aExprotion[nCountExprotion].pos.y -EXPROSION_HEITH,0.0f);//右回りゼロ番目
			pVtx[1].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x + EXPROSION_WIDTH, g_aExprotion[nCountExprotion].pos.y - EXPROSION_HEITH,0.0f);//一番目
			pVtx[2].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x- EXPROSION_WIDTH, g_aExprotion[nCountExprotion].pos.y+ EXPROSION_HEITH, 0.0f);//二番目
			pVtx[3].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x + EXPROSION_WIDTH, g_aExprotion[nCountExprotion].pos.y+ EXPROSION_HEITH, 0.0f);//三番目
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffExprotion->Unlock();
}
Exprotion* GetExprosion(void)
{
	return &g_aExprotion[0];
}