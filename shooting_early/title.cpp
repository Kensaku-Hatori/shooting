#include "title.h"
#include "input.h"
#include "game.h"
#include"fade.h"
#include"sound.h"

LPDIRECT3DTEXTURE9 g_pTextureTitle1[TYPE_TITLE] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;	//頂点バッファへのポインタ
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title.png",
		&g_pTextureTitle1[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title1.png",
		&g_pTextureTitle1[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4*TYPE_TITLE,//確保したいバッファ数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL
	);
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得


	//二個目のポリゴン
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右回りゼロ番目
	pVtx[1].pos = D3DXVECTOR3(WINDOW_WIDTH, 0.0f, 0.0f);//一番目
	pVtx[2].pos = D3DXVECTOR3(0.0f, WINDOW_HEITH, 0.0f);//二番目
	pVtx[3].pos = D3DXVECTOR3(WINDOW_WIDTH,WINDOW_HEITH, 0.0f);//三番目

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
	g_pVtxBuffTitle->Unlock();
	PlaySound(SOUND_LABEL_BGM);
}
void UninitTitle(void)
{
	StopSound();
	//テクスチャの破棄
	for (int i = 0; i < TYPE_TITLE; i++)
	{
		if (g_pTextureTitle1[i] != NULL)
		{
			g_pTextureTitle1[i]->Release();
			g_pTextureTitle1[i] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}
void UpdateTitle(void)
{
	if (KeyboardTrigger(DIK_RETURN)||GetJoyPadPress(JOYKEY_START))
	{
		SetFade(MODE_GAME);
	}
}
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX2D));

	for (int i= 0; i < TYPE_TITLE; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle1[i]);//一つ目のポリゴン
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}