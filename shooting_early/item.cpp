#include"main.h"
#include"item.h"
#include"game.h"

LPDIRECT3DTEXTURE9 g_pTextureItem1[MAX_ITEMTYPE] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	//頂点バッファへのポインタ
ITEM g_Item[MAX_ITEM];

void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\unti.png",
		&g_pTextureItem1[BOM_ITEM]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\scoreup.png",
		&g_pTextureItem1[SCOREUP_ITEM]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4 * MAX_ITEM,//確保したいバッファ数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL
	);
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得

	for (int i = 0; i < MAX_ITEM; i++)
	{
		g_Item[i].bUse = false;
		g_Item[i].Itemstate = NONE_ITEM;
		g_Item[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25f);
		pVtx[3].tex = D3DXVECTOR2(0.2f, 0.25f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}
void UninitItem(void)
{
	for (int i = 0; i < MAX_ITEMTYPE; i++)
	{
		//テクスチャの破棄
		if (g_pTextureItem1[i] != NULL)
		{
			g_pTextureItem1[i]->Release();
			g_pTextureItem1[i] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}
void UpdateItem(void)
{
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得
	for(int i=0;i<MAX_ITEM;i++)
	{
		if (g_Item[i].bUse == true)
		{
			switch (g_Item[i].Itemstate)
			{
			case BOM_ITEM:
				g_Item[i].ncountItemAnim++;
				if (g_Item[i].ncountItemAnim >= 6)
				{
					g_Item[i].ncountItemAnim = 0;
					g_Item[i].ncountItemAnimPetternX++;

					if (g_Item[i].ncountItemAnimPetternX >= 5)
					{
						g_Item[i].ncountItemAnimPetternX = 0;
						g_Item[i].ncountItemAnimPetternY++;
						if (g_Item[i].ncountItemAnimPetternY >= 4)
						{
							g_Item[i].ncountItemAnimPetternY = 0;
						}
					}
					//テクスチャ座標の設定
					pVtx[0].tex = D3DXVECTOR2(0.0f + (0.2f * g_Item[i].ncountItemAnimPetternX), 0.0f + g_Item[i].ncountItemAnimPetternY * 0.25f);
					pVtx[1].tex = D3DXVECTOR2(0.2f + (0.2f * g_Item[i].ncountItemAnimPetternX), 0.0f + g_Item[i].ncountItemAnimPetternY * 0.25f);
					pVtx[2].tex = D3DXVECTOR2(0.0f + (0.2f * g_Item[i].ncountItemAnimPetternX), 0.25f+ g_Item[i].ncountItemAnimPetternY * 0.25f);
					pVtx[3].tex = D3DXVECTOR2(0.2f + (0.2f * g_Item[i].ncountItemAnimPetternX), 0.25f+ g_Item[i].ncountItemAnimPetternY * 0.25f);
				}
				break;
			case SCOREUP_ITEM:
				g_Item[i].ncountItemAnim++;
				if (g_Item[i].ncountItemAnim >= 6)
				{
					g_Item[i].ncountItemAnim = 0;
					g_Item[i].ncountItemAnimPetternX++;


					if (g_Item[i].ncountItemAnimPetternX >= 5)
					{
						g_Item[i].ncountItemAnimPetternX = 0;
						g_Item[i].ncountItemAnimPetternY++;
						if (g_Item[i].ncountItemAnimPetternY >= 4)
						{
							g_Item[i].ncountItemAnimPetternY = 0;
						}
					}
					//テクスチャ座標の設定
					pVtx[0].tex = D3DXVECTOR2(0.0f + (0.2f*g_Item[i].ncountItemAnimPetternX),    0.0f + g_Item[i].ncountItemAnimPetternY * 0.25f);
					pVtx[1].tex = D3DXVECTOR2(0.2f + (0.2f * g_Item[i].ncountItemAnimPetternX),  0.0f + g_Item[i].ncountItemAnimPetternY * 0.25f);
					pVtx[2].tex = D3DXVECTOR2(0.0f + (0.2f * g_Item[i].ncountItemAnimPetternX), 0.25f + g_Item[i].ncountItemAnimPetternY * 0.25f);
					pVtx[3].tex = D3DXVECTOR2(0.2f + (0.2f * g_Item[i].ncountItemAnimPetternX), 0.25f + g_Item[i].ncountItemAnimPetternY * 0.25f);
				}
				break;
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffItem->Unlock();
}
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX2D));

	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (g_Item[i].bUse == true)
		{
			switch (g_Item[i].Itemstate)
			{
			case BOM_ITEM:
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureItem1[BOM_ITEM]);//一つ目のポリゴン
				break;
			case SCOREUP_ITEM:
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureItem1[SCOREUP_ITEM]);//一つ目のポリゴン
				break;
			}
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*i, 2);
		}
	}
}
void SetItem(ITEM_STATE itemtype,D3DXVECTOR3 pos)
{
	VERTEX2D* pVtx;//頂点バッファへのポインタ
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);//頂点バッファをロックし、頂点へのポインタを習得
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (g_Item[i].bUse == false)
		{
			g_Item[i].pos = pos;
			g_Item[i].bUse = true;
			g_Item[i].Itemstate = itemtype;

			//一個目のポリゴン
			pVtx[0].pos = D3DXVECTOR3(g_Item[i].pos.x - ENEMY_WIDTH, g_Item[i].pos.y - ENEMY_HEIGHT, 0.0f);//右回りゼロ番目
			pVtx[1].pos = D3DXVECTOR3(g_Item[i].pos.x + ENEMY_WIDTH, g_Item[i].pos.y - ENEMY_HEIGHT, 0.0f);//一番目
			pVtx[2].pos = D3DXVECTOR3(g_Item[i].pos.x - ENEMY_WIDTH, g_Item[i].pos.y + ENEMY_HEIGHT, 0.0f);//二番目
			pVtx[3].pos = D3DXVECTOR3(g_Item[i].pos.x + ENEMY_WIDTH, g_Item[i].pos.y + ENEMY_HEIGHT, 0.0f);//三番目
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffItem->Unlock();
}
ITEM *GetItem(void)
{
	return &g_Item[0];
}