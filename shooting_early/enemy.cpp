#include "enemy.h"
#include "bullet.h"
#include "input.h"
#include "exprotion.h"
#include"player.h"
#include"wave.h"
#include"item.h"

LPDIRECT3DTEXTURE9 g_pTextureEnemy[ENEMYTYPE_MAX] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];//�G�̏��
int g_nNumEnemy = 0;//�G�̑���

//�v���C���[�̏���������
void InitEnemy(void)
{
	int ncountenemy;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy001.jpg",
		&g_pTextureEnemy[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D)*4*MAX_ENEMY,//�m�ۂ������o�b�t�@��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL
	);
	VERTEX2D *pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��


	for (ncountenemy = 0; ncountenemy < MAX_ENEMY; ncountenemy++)
	{
		g_aEnemy[ncountenemy].move = D3DXVECTOR3(0.0f, 9.0f, 0.0f);
		g_aEnemy[ncountenemy].nType = 0;
		g_aEnemy[ncountenemy].nLife = 100;
		g_aEnemy[ncountenemy].statecount = 0;
		g_aEnemy[ncountenemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[ncountenemy].bUse = false;
		g_aEnemy[ncountenemy].atack = 10;
		g_nNumEnemy = 0;
		g_aEnemy[ncountenemy].cooldown = 0;
	}
	for (ncountenemy = 0; ncountenemy < MAX_ENEMY; ncountenemy++)
	{


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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}
//�v���C���[�̏I������
void UninitEnemy(void)
{
	int ncountenemy;
	for (ncountenemy = 0; ncountenemy < ENEMYTYPE_MAX; ncountenemy++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureEnemy[ncountenemy] != NULL)
		{
			g_pTextureEnemy[ncountenemy]->Release();
			g_pTextureEnemy[ncountenemy] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy=NULL;
	}
}
//�v���C���[�̍X�V����
void UpdateEnemy(void)
{
	int ncountenemy;
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
	for (ncountenemy = 0; ncountenemy < MAX_ENEMY; ncountenemy++)
	{
		if (g_aEnemy[ncountenemy].bUse == true)
		{
			switch (g_aEnemy[ncountenemy].state)
			{
			case ENEMYSTATE_NORMAL:
				g_aEnemy[ncountenemy].cooldowncount++;
				if (g_aEnemy[ncountenemy].cooldowncount >= g_aEnemy[ncountenemy].cooldown)
				{
					g_aEnemy[ncountenemy].cooldowncount = 0;
					g_aEnemy[ncountenemy].pos.y += g_aEnemy[ncountenemy].move.y;
				}
				break;
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[ncountenemy].statecount--;
				if (g_aEnemy[ncountenemy].statecount <= 0)
				{
					g_aEnemy[ncountenemy].statecount = 0;
					g_aEnemy[ncountenemy].state = ENEMYSTATE_NORMAL;
					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//RGB�Ɠ����x
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
			}
		}
		//��ڂ̃|���S��
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x - ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y - ENEMY_HEIGHT, 0.0f);//�E���[���Ԗ�
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x + ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y - ENEMY_HEIGHT, 0.0f);//��Ԗ�
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x - ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y + ENEMY_HEIGHT, 0.0f);//��Ԗ�
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x + ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y + ENEMY_HEIGHT, 0.0f);//�O�Ԗ�
		pVtx += 4;
	}
	g_pVtxBuffEnemy->Unlock();
}
//�v���C���[�̕`�揈��
void DrawEnemy(void)
{
	int ncountenemy;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX2D));

	for (ncountenemy = 0; ncountenemy < MAX_ENEMY; ncountenemy++)
	{
		if (g_aEnemy[ncountenemy].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEnemy[0]);//��ڂ̃|���S��
 			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*ncountenemy, 2);
		}
	}
}
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int ncountenemy;
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
	for(ncountenemy=0;ncountenemy<MAX_ENEMY;ncountenemy++)
	{
		if (g_aEnemy[ncountenemy].bUse == false)
		{
			g_aEnemy[ncountenemy].pos = pos;
			g_aEnemy[ncountenemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[ncountenemy].nLife = 100;
			g_aEnemy[ncountenemy].atack = 10;
			g_aEnemy[ncountenemy].nType = nType;
			g_aEnemy[ncountenemy].cooldown = 10;
			//��ڂ̃|���S��
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x-ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y-ENEMY_HEIGHT, 0.0f);//�E���[���Ԗ�
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x+ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y-ENEMY_HEIGHT, 0.0f);//��Ԗ�
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x-ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y+ ENEMY_HEIGHT, 0.0f);//��Ԗ�
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[ncountenemy].pos.x+ENEMY_WIDTH, g_aEnemy[ncountenemy].pos.y+ ENEMY_HEIGHT, 0.0f);//�O�Ԗ�
			g_aEnemy[ncountenemy].bUse = true;
			g_nNumEnemy++;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffEnemy->Unlock();
}
void HitEnemy(int nCntEnemy, int nDamage)
{
	Player* pplayer = GetPlayer();
	WAVE* pwavestate = GetWave();
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife<=0)
	{
		g_nNumEnemy--;
		SetExprotion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(255, 255, 255, 255));
		g_aEnemy[nCntEnemy].bUse = false;
		int drop = rand() % 100 + 1;
		if (drop <= 30)
		{
			int item1 = rand() % (MAX_ITEMTYPE - 1) + 1;
			
			SetItem((ITEM_STATE)item1,g_aEnemy[nCntEnemy].pos);
		}
		if (g_nNumEnemy <= 0)
		{
 			pwavestate->nwavestate++;
			pwavestate->wavestate = (WAVE_STATE)pwavestate->nwavestate;
			pwavestate->waveflag = true;
			pplayer->level++;

			pplayer->nLife = pplayer->level * MIN_LIFE;
			pplayer->atack = pplayer->level * MIN_ATACK;
			pplayer->interval = MIN_INTERVAL / pplayer->level;
			pplayer->way = pplayer->level * MIN_WAY;
		}
 	}
	else
	{
		VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
		pVtx += 4 * nCntEnemy;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].statecount = 5;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);//RGB�Ɠ����x
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		g_pVtxBuffEnemy->Unlock();
	}
}
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}
int GetNumEnemy(void)
{
	return g_nNumEnemy;
}