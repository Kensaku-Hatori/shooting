#include "score.h"
//===========================
// マウロ定義
//===========================
#define MAX_DIGIT (8)
#define uunti (10)


typedef struct
{
	bool buse;
}DIGIT;
//=================
// グローバル変数
//=================
LPDIRECT3DTEXTURE9 g_pTextureScore1 = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posscore;// スコアの座標
int g_nscore;// スコアを収める変数
DIGIT g_score[MAX_DIGIT];

//===========================
// スコアの初期化処理
//===========================
void Initscore()
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&g_pTextureScore1);


	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4*MAX_DIGIT,//確保したいバッファ数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL
	);


	g_posscore = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_nscore = 0;


	// 頂点バッファへのポインタ
	VERTEX2D* pVtx;

	// 頂点バッファをロックし、頂点へのポインタを習得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);


	for (int ncount = 0; ncount < MAX_DIGIT; ncount++, pVtx += 4)
	{
		//二個目のポリゴン
		pVtx[0].pos = D3DXVECTOR3(0.0f + ncount * 100.0f, 0.0f, 0.0f);//右回りゼロ番目
		pVtx[1].pos = D3DXVECTOR3(100.0f + ncount * 100.0f, 0.0f, 0.0f);//一番目
		pVtx[2].pos = D3DXVECTOR3(0.0f + ncount * 100.0f, 100.0f, 0.0f);//二番目
		pVtx[3].pos = D3DXVECTOR3(100.0f + ncount * 100.0f, 100.0f, 0.0f);//三番目

		// rhwの設定
		pVtx[0].rhw = 1.0f;//値は1.0fで固定
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//RGBと透明度
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//===========================
// スコアの終了処理
//===========================
void Uninitscore()
{
	// テクスチャの破棄
	if (g_pTextureScore1 != NULL)
	{
		g_pTextureScore1->Release();
		g_pTextureScore1 = NULL;
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
//===========================
// スコアの更新処理
//===========================
void Updatescore()
{
	int ndata=0, ndata1=0;
	ndata = score(g_nscore);

	// 頂点バッファへのポインタ
	VERTEX2D* pVtx;

	// 頂点バッファをロックし、頂点へのポインタを習得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);


	for (ndata1 = 0; ndata1 < MAX_DIGIT; ndata1++)
	{
		if (ndata1 >= MAX_DIGIT - ndata)
		{
			g_score[ndata1].buse = true;
		}
		else
		{
			g_score[ndata1].buse = false;
		}
	}
}
//===========================
// スコアの描画処理
//===========================
void Drawscore()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX2D));


	for (int ncount = 0; ncount < MAX_DIGIT; ncount++)
	{
		if (g_score[ncount].buse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureScore1);//一つ目のポリゴン
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * ncount, 2);
		}
	}
}
//===========================
// スコアの設定処理
//===========================
void Setscore(int nscore)
{
	int apostexu[MAX_DIGIT];
	g_nscore = nscore;
}
//===========================
// スコアの加算処理
//===========================
void Addscore(int nvalue)
{
	int apostexu[MAX_DIGIT],ncount,unti,unti1;
	unti = 100000000, unti1 = 10000000;
	g_nscore += nvalue;
	// 頂点バッファへのポインタ
	VERTEX2D* pVtx;

	// 頂点バッファをロックし、頂点へのポインタを習得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (ncount = 0; ncount < MAX_DIGIT; ncount++)
	{
		apostexu[ncount]=g_nscore%unti/unti1;
		unti = unti / uunti;
		unti1 = unti1 / uunti;
	}
	for (ncount = 0; ncount < MAX_DIGIT; ncount++, pVtx += 4)
	{
		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + apostexu[ncount] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + apostexu[ncount] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + apostexu[ncount] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + apostexu[ncount]*0.1f, 1.0f);
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
int score(int score)
{
	int score1 = score;
	int digit=0;
	while (score1!=0)
	{
		score1/=uunti;
		digit++;
	}
	if (score == 0)
	{
		digit = 1;
	}
	return digit;
}