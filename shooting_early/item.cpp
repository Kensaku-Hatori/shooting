#include"main.h"
#include"item.h"
#include"game.h"

LPDIRECT3DTEXTURE9 g_pTextureItem1[MAX_ITEMTYPE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	//���_�o�b�t�@�ւ̃|�C���^
ITEM g_Item[MAX_ITEM];

void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\unti.png",
		&g_pTextureItem1[BOM_ITEM]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\scoreup.png",
		&g_pTextureItem1[SCOREUP_ITEM]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4 * MAX_ITEM,//�m�ۂ������o�b�t�@��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL
	);
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��

	for (int i = 0; i < MAX_ITEM; i++)
	{
		g_Item[i].bUse = false;
		g_Item[i].Itemstate = NONE_ITEM;
		g_Item[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;//�l��1.0f�ŌŒ�
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//RGB�Ɠ����x
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25f);
		pVtx[3].tex = D3DXVECTOR2(0.2f, 0.25f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}
void UninitItem(void)
{
	for (int i = 0; i < MAX_ITEMTYPE; i++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureItem1[i] != NULL)
		{
			g_pTextureItem1[i]->Release();
			g_pTextureItem1[i] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}
void UpdateItem(void)
{
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
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
					//�e�N�X�`�����W�̐ݒ�
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
					//�e�N�X�`�����W�̐ݒ�
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
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX2D));

	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (g_Item[i].bUse == true)
		{
			switch (g_Item[i].Itemstate)
			{
			case BOM_ITEM:
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem1[BOM_ITEM]);//��ڂ̃|���S��
				break;
			case SCOREUP_ITEM:
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem1[SCOREUP_ITEM]);//��ڂ̃|���S��
				break;
			}
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*i, 2);
		}
	}
}
void SetItem(ITEM_STATE itemtype,D3DXVECTOR3 pos)
{
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (g_Item[i].bUse == false)
		{
			g_Item[i].pos = pos;
			g_Item[i].bUse = true;
			g_Item[i].Itemstate = itemtype;

			//��ڂ̃|���S��
			pVtx[0].pos = D3DXVECTOR3(g_Item[i].pos.x - ENEMY_WIDTH, g_Item[i].pos.y - ENEMY_HEIGHT, 0.0f);//�E���[���Ԗ�
			pVtx[1].pos = D3DXVECTOR3(g_Item[i].pos.x + ENEMY_WIDTH, g_Item[i].pos.y - ENEMY_HEIGHT, 0.0f);//��Ԗ�
			pVtx[2].pos = D3DXVECTOR3(g_Item[i].pos.x - ENEMY_WIDTH, g_Item[i].pos.y + ENEMY_HEIGHT, 0.0f);//��Ԗ�
			pVtx[3].pos = D3DXVECTOR3(g_Item[i].pos.x + ENEMY_WIDTH, g_Item[i].pos.y + ENEMY_HEIGHT, 0.0f);//�O�Ԗ�
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