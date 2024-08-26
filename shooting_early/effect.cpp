#include "main.h"
#include "player.h"
#include "input.h"
#include "Effect.h"
#include "Exprotion.h"
#include "enemy.h"
#include "effect.h"
#include"bullet.h"
#define MAX_EFFECT (4096)//�e�̍ő吔
#define EFFECT_LIFE (20)
typedef struct
{
	D3DXVECTOR3 pos;//�e�̈ʒu
	D3DXVECTOR3 exprotionpos;
	D3DXVECTOR3 move;//�e�̈ړ���
	int nLife;//�e�̎���
	BULLETTYPE type;
	bool bUse;
	D3DXVECTOR3 rot;
	float fLength;
	float fAngle;
	float faduce;
}EFFECT;

LPDIRECT3DTEXTURE9 g_pTextureEffect1 = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
EFFECT g_aEffect[MAX_EFFECT] = {};
void InitEffect(void)		//�v���C���[�p
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCountEffect;
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect1);
	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		g_aEffect[nCountEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCountEffect].exprotionpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCountEffect].nLife = EFFECT_LIFE;
		g_aEffect[nCountEffect].bUse = false;
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4*MAX_EFFECT,//�m�ۂ������o�b�t�@��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL
	);
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��

	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)//�e�̏������P�Q�W��
	{
		//��ڂ̃|���S��
		pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);//�E���[���Ԗ�
		pVtx[1].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);//��Ԗ�
		pVtx[2].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);//��Ԗ�
		pVtx[3].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);//�O�Ԗ�

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;//�l��1.0f�ŌŒ�
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);//RGB�Ɠ����x
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�o�b�t�@�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
//�v���C���[�̏I������
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect1 != NULL)
	{
		g_pTextureEffect1->Release();
		g_pTextureEffect1 = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
void UpdateEffect(void)
{
	int nCountEffect;

	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��

	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		if (g_aEffect[nCountEffect].bUse == true)//�e���g�p����Ă�����
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);//RGB�Ɠ����x
			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

			//���_���W�̍X�V
			pVtx[0].pos.x = (g_aEffect[nCountEffect].pos.x + sinf(g_aEffect[nCountEffect].rot.z + (D3DX_PI + g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.y - 25.0f;
			pVtx[0].pos.y = (g_aEffect[nCountEffect].pos.y + cosf(g_aEffect[nCountEffect].rot.z + (D3DX_PI + g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.x - 150.0f;
			pVtx[0].pos.z = 0.0f;//0.0f;
			pVtx[1].pos.x = (g_aEffect[nCountEffect].pos.x + sinf(g_aEffect[nCountEffect].rot.z + (D3DX_PI - g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.x + 150.0f;
			pVtx[1].pos.y = (g_aEffect[nCountEffect].pos.y + cosf(g_aEffect[nCountEffect].rot.z + (D3DX_PI - g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.y - 25.0f;
			pVtx[1].pos.z = 0.0f;//0.0f;
			pVtx[2].pos.x = (g_aEffect[nCountEffect].pos.x + sinf(g_aEffect[nCountEffect].rot.z + (0.0f - g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.x - 150.0f;
			pVtx[2].pos.y = (g_aEffect[nCountEffect].pos.y + cosf(g_aEffect[nCountEffect].rot.z + (0.0f - g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.y + 25.0f;
			pVtx[2].pos.z = 0.0f;//0.0f;
			pVtx[3].pos.x = (g_aEffect[nCountEffect].pos.x + sinf(g_aEffect[nCountEffect].rot.z + (0.0f + g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.x + 150.0f;
			pVtx[3].pos.y = (g_aEffect[nCountEffect].pos.y + cosf(g_aEffect[nCountEffect].rot.z + (0.0f + g_aEffect[nCountEffect].fAngle)) * g_aEffect[nCountEffect].fLength);//pos.y + 25.0f;
			pVtx[3].pos.z = 0.0f;

			g_aEffect[nCountEffect].nLife--;
			g_aEffect[nCountEffect].fLength -= 5;
			if (g_aEffect[nCountEffect].nLife <= 0)
			{
				g_aEffect[nCountEffect].bUse = false;
			}
		}
		pVtx += 4;
	}

	g_pVtxBuffEffect->Unlock();
}
//�v���C���[�̕`�揈��
void DrawEffect(void)
{
	int ncount;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX2D));

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (ncount = 0; ncount < MAX_EFFECT; ncount++)
	{
		if (g_aEffect[ncount].bUse == true)
		{
			//�e�N�X�`���̐ݒ� 
			pDevice->SetTexture(0, g_pTextureEffect1);//��ڂ̃|���S��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,ncount*4,2);
		}
	}

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//�e�̐ݒ菈��
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,float fLength,float fAngle,D3DXVECTOR3 rot)
{
	int nCountEffect;
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		if (g_aEffect[nCountEffect].bUse == false)
		{//�e���g�p����Ă��Ȃ�
			g_aEffect[nCountEffect].fLength = fLength,
			g_aEffect[nCountEffect].rot = rot;
			g_aEffect[nCountEffect].fAngle = fAngle;
			g_aEffect[nCountEffect].pos = pos;
			g_aEffect[nCountEffect].type = type;
			g_aEffect[nCountEffect].nLife = EFFECT_LIFE;
			g_aEffect[nCountEffect].bUse = true;//�g�p���Ă����Ԃɂ���

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffEffect->Unlock();
 }