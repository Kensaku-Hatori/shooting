#include"main.h"
#include"wave.h"
#include"game.h"
#include"enemy.h"
#include"fade.h"

LPDIRECT3DTEXTURE9 g_pTextureWave1 = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWave = NULL;	//頂点バッファへのポインタ
WAVE g_Wave;

void InitWave(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Wave001.jpg",
		&g_pTextureWave1);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4 * MAX_WAVE,//確保したいバッファ数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWave,
		NULL
	);


	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffWave->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得


	g_Wave.bUse = false;
	g_Wave.wavestate = NONE_WAVE;
	g_Wave.waveenemycount = 0;
	g_Wave.nwavestate = 0;

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
	g_pVtxBuffWave->Unlock();
}
void UninitWave(void)
{
	//テクスチャの破棄
	if (g_pTextureWave1 != NULL)
	{
		g_pTextureWave1->Release();
		g_pTextureWave1 = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffWave != NULL)
	{
		g_pVtxBuffWave->Release();
		g_pVtxBuffWave = NULL;
	}
}
void UpdateWave(void)
{
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffWave->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得
	g_pVtxBuffWave->Unlock();
	if (g_Wave.wavestate >= MAX_WAVE)
	{
		SetFade(MODE_RESULT);
	}
	else if (g_Wave.waveflag == true)
	{
		if (g_Wave.waveenemycount < WAVE_ENEMY * g_Wave.wavestate)
		{
			g_Wave.wavecount = rand() % 120 + 0;
			g_Wave.timecount++;
			if (g_Wave.wavecount <= g_Wave.timecount)
			{
				g_Wave.timecount = 0;
				float x, y = 0;
				int type;
				type = rand() % ENEMYTYPE_MAX + 0;
				x = rand() % (WINDOW_WIDTH - ENEMY_WIDTH) + (0.0f + ENEMY_WIDTH);
				SetEnemy(D3DXVECTOR3(x, y, 0.0f), type);
				g_Wave.waveenemycount++;
			}
		}
		else
		{
			g_Wave.waveenemycount = 0;
			g_Wave.waveflag = false;
		}
	}
}
void DrawWave(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffWave, 0, sizeof(VERTEX2D));

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureWave1);//一つ目のポリゴン
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}
void SetWave()
{
	//switch (g_Wave.wavestate)
	//{
	//case NONE_WAVE:
 //  		g_Wave.wavestate = FIRST_WAVE;
	//	break;
	//case FIRST_WAVE:
	//	for (int i = 0; i < WAVE_ENEMY * FIRST_WAVE; i++)
	//	{
	//		g_Wave.wavecount = rand() % 120 +0;
	//		float x, y = 0;
	//		int type;
	//		type = rand() % ENEMYTYPE_MAX + 0;
	//		x = rand() % WINDOW_WIDTH + 0.0f;
	//		//y = rand() % WINDOW_HEITH + 0.0f;
	//		SetEnemy(D3DXVECTOR3(x, y, 0.0f), type);
	//		delay(1);
	//	}
	//	g_Wave.wavestate = SECOND_WAVE;
	//	break;
	//case SECOND_WAVE:
	//	for (int i = 0; i < WAVE_ENEMY * SECOND_WAVE; i++)
	//	{
	//		float x, y = 0;
	//		int type;
	//		type = rand() % ENEMYTYPE_MAX + 0;
	//		x = rand() % WINDOW_WIDTH + 0.0f;
	//		//y = rand() % WINDOW_HEITH + 0.0f;
	//		SetEnemy(D3DXVECTOR3(x, y, 0.0f), type);
	//	}
	//	g_Wave.wavestate = THIRD_WAVE;
	//	break;
	//case THIRD_WAVE:
	//	for (int i = 0; i < WAVE_ENEMY * THIRD_WAVE; i++)
	//	{
	//		float x, y = 0;
	//		int type;
	//		type = rand() % ENEMYTYPE_MAX + 0;
	//		x = rand() % WINDOW_WIDTH + 0.0f;
	//		//y = rand() % WINDOW_HEITH + 0.0f;
	//		SetEnemy(D3DXVECTOR3(x, y, 0.0f), type);
	//	}
	//	g_Wave.wavestate = FOURTH_WAVE;
	//	break;
	//case FOURTH_WAVE:
	//	for (int i = 0; i < WAVE_ENEMY * FOURTH_WAVE; i++)
	//	{
	//		float x, y = 0;
	//		int type;
	//		type = rand() % ENEMYTYPE_MAX + 0;
	//		x = rand() % WINDOW_WIDTH + 0.0f;
	//		//y = rand() % WINDOW_HEITH + 0.0f;
	//		SetEnemy(D3DXVECTOR3(x, y, 0.0f), type);
	//	}
	//	g_Wave.wavestate = FIFTH_WAVE;
	//	break;
	//case FIFTH_WAVE:
	//	for (int i = 0; i < WAVE_ENEMY * FIFTH_WAVE; i++)
	//	{
	//		float x, y = 0;
	//		int type;
	//		type = rand() % ENEMYTYPE_MAX + 0;
	//		x = rand() % WINDOW_WIDTH + 0.0f;
	//		//y = rand() % WINDOW_HEITH + 0.0f;
	//		SetEnemy(D3DXVECTOR3(x, y, 0.0f), type);
	//	}
	//	g_Wave.wavestate = END_WAVE;
	//	break;
	//case END_WAVE:
	//	SetState(GAMESTATE_END);
	//	break;
	//}
}
WAVE *GetWave(void)
{
	return &g_Wave;
}
