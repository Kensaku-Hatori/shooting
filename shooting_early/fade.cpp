#include "fade.h"
#include "main.h"
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	//頂点バッファへのポインタ
FADE g_Fade;
MODE g_modenext;
D3DXCOLOR g_colorFade;
void InitFade(MODE modenext)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();
		//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4,//確保したいバッファ数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL
	);

	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得

	g_Fade = FADE_IN;

	g_modenext = modenext;

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

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
	pVtx[0].col = D3DCOLOR(g_colorFade);//RGBと透明度
	pVtx[1].col = D3DCOLOR(g_colorFade);
	pVtx[2].col = D3DCOLOR(g_colorFade);
	pVtx[3].col = D3DCOLOR(g_colorFade);

	g_pVtxBuffFade->Unlock();

	SetMode(g_modenext);
}
void UpdateFade()
{
	if (g_Fade != FADE_NONE)
	{
		if (g_Fade == FADE_IN)
		{
			g_colorFade.a -= 0.03f;

			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_Fade = FADE_NONE;
			}
		}
		else if (g_Fade == FADE_OUT)
		{
			g_colorFade.a += 0.03f;

			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_Fade = FADE_IN;
				SetMode(g_modenext);
			}
		}
		VERTEX2D* pVtx;//頂点バッファへのポインタ
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR(g_colorFade);//RGBと透明度
		pVtx[1].col = D3DCOLOR(g_colorFade);
		pVtx[2].col = D3DCOLOR(g_colorFade);
		pVtx[3].col = D3DCOLOR(g_colorFade);

		g_pVtxBuffFade->Unlock();
	}
}
void DrawFade()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX2D));

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);//一つ目のポリゴン
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void UninitFade()
{
	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}
void SetFade(MODE modenext)
{
	g_Fade = FADE_OUT;
	g_modenext = modenext;
}
FADE GetFade(void)
{
	return g_Fade;
}