#include "main.h"
#include "player.h"
#define NUM_BG (3)
LPDIRECT3DTEXTURE9 g_pTextureBackground[NUM_BG] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBackground = NULL;	//頂点バッファへのポインタ
float g_aPosTexU[NUM_BG];

void Initbackground(void)//背景の初期化処理
{
	int ncountBG;
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg100.png",
		&g_pTextureBackground[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg101.png",
		&g_pTextureBackground[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg102.png",
		&g_pTextureBackground[2]);
	for (ncountBG = 0; ncountBG < NUM_BG; ncountBG++)
	{
		g_aPosTexU[ncountBG] = 0.0f;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4*NUM_BG,//確保したいバッファ数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBackground,
		NULL
	);
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得

	for (ncountBG = 0; ncountBG < NUM_BG; ncountBG++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右回りゼロ番目
		pVtx[1].pos = D3DXVECTOR3(WINDOW_WIDTH, 0.0f, 0.0f);//一番目
		pVtx[2].pos = D3DXVECTOR3(0.0f, WINDOW_HEITH, 0.0f);//二番目
		pVtx[3].pos = D3DXVECTOR3(WINDOW_WIDTH, WINDOW_HEITH, 0.0f);//三番目

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
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[ncountBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[ncountBG]+1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[ncountBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[ncountBG]+1.0f, 1.0f);
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBackground->Unlock();
}
void Uninitbackground(void)//背景の破棄
{
	int ncountbg;
	//テクスチャの破棄
	for (ncountbg =0; ncountbg < NUM_BG; ncountbg++)
	{
		if (g_pTextureBackground[ncountbg] != NULL)
		{
			g_pTextureBackground[ncountbg]->Release();
			g_pTextureBackground[ncountbg] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBackground != NULL)
	{
		g_pVtxBuffBackground->Release();
		g_pVtxBuffBackground = NULL;
	}
}
void Updatebackground(void)//背景の更新処理
{
	int ncountbg;
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得
	for (ncountbg = 0; ncountbg < NUM_BG; ncountbg++)
	{
		g_aPosTexU[ncountbg]+=0.001f*(ncountbg+1);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[ncountbg], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[ncountbg] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[ncountbg], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[ncountbg] + 1.0f, 1.0f);
		pVtx += 4;
	}
	g_pVtxBuffBackground->Unlock();
}
void Drawbackground(void)//背景の描画処理
{
	int ncountbg;
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffBackground, 0, sizeof(VERTEX2D));

	for (ncountbg = 0; ncountbg < NUM_BG; ncountbg++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBackground[ncountbg]);//一つ目のポリゴン
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*ncountbg, 2);
	}
}