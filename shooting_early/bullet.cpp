#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "Exprotion.h"
#include "enemy.h"
#include"effect.h"
#define MAX_Bullet (128)//�e�̍ő吔
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
}Bullet;

LPDIRECT3DTEXTURE9 g_pTextureBullet1 = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_Bullet] = {};
void InitBullet(void)		//�v���C���[�p
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCountBullet;
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bullet.png",
		&g_pTextureBullet1);
	for (nCountBullet = 0; nCountBullet < MAX_Bullet; nCountBullet++)
	{
		g_aBullet[nCountBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCountBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCountBullet].exprotionpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCountBullet].fAngle = 0.0f;
		g_aBullet[nCountBullet].fLength = 0.0f;
		g_aBullet[nCountBullet].nLife = 0;
		g_aBullet[nCountBullet].bUse = false;
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4*MAX_Bullet,//�m�ۂ������o�b�t�@��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL
	);
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��

	for (nCountBullet = 0; nCountBullet < MAX_Bullet; nCountBullet++)//�e�̏������P�Q�W��
	{
		//��ڂ̃|���S��
		pVtx[0].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z - (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y - 25.0f;
		pVtx[0].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z - (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x - 150.0f;
		pVtx[0].pos.z = 0.0f;//0.0f;
		pVtx[1].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z + (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x + 150.0f;
		pVtx[1].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z + (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y - 25.0f;
		pVtx[1].pos.z = 0.0f;//0.0f;
		pVtx[2].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z + (0.0f - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x - 150.0f;
		pVtx[2].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z + (0.0f - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y + 25.0f;
		pVtx[2].pos.z = 0.0f;//0.0f;
		pVtx[3].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z + (0.0f + g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x + 150.0f;
		pVtx[3].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z + (0.0f + g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y + 25.0f;
		pVtx[3].pos.z = 0.0f;


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
	g_pVtxBuffBullet->Unlock();
}
//�v���C���[�̏I������
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet1 != NULL)
	{
		g_pTextureBullet1->Release();
		g_pTextureBullet1 = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
void UpdateBullet(void)
{
	int nCountBullet;
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��

	for (nCountBullet = 0; nCountBullet < MAX_Bullet; nCountBullet++)
	{
		if (g_aBullet[nCountBullet].bUse == true)//�e���g�p����Ă�����
		{
			if (g_aBullet[nCountBullet].type == BULLETTYPE_PLAYER)
			{
				int ncountenemy;
				Player* pPlayer = GetPlayer();
				Enemy* pEnemy = GetEnemy();
				Exprotion* pExprotion = GetExprosion();
				for (ncountenemy = 0; ncountenemy < MAX_ENEMY; ncountenemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (g_aBullet[nCountBullet].pos.x >= g_aBullet[nCountBullet].exprotionpos.x - EXPROSION_WIDTH
							&& g_aBullet[nCountBullet].pos.x <= g_aBullet[nCountBullet].exprotionpos.x + EXPROSION_WIDTH
							&& g_aBullet[nCountBullet].pos.y >= g_aBullet[nCountBullet].exprotionpos.y - EXPROSION_HEITH
							&& g_aBullet[nCountBullet].pos.y <= g_aBullet[nCountBullet].exprotionpos.y + EXPROSION_HEITH
							)
						{
							SetExprotion(g_aBullet[nCountBullet].exprotionpos, D3DXCOLOR(255, 255, 255, 255));
							g_aBullet[nCountBullet].bUse = false;
							if (pExprotion->pos.x >= pEnemy->pos.x - ENEMY_WIDTH*2
								&& pExprotion->pos.x <= pEnemy->pos.x + ENEMY_WIDTH*2
								&& pExprotion->pos.y >= pEnemy->pos.y - ENEMY_HEIGHT*2
								&& pExprotion->pos.y <= pEnemy->pos.y + ENEMY_HEIGHT*2
								)
							{
								HitEnemy(ncountenemy, pPlayer->atack);
							}
						}
					}
					pEnemy++;
					pExprotion++;
				}
			}
			else if (g_aBullet[nCountBullet].type == BULLETTYPE_ENEMY)
			{
				Player* pPlayer = GetPlayer();
				Enemy* pEnemy = GetEnemy();
				//if (pPlayer->bUse == true)
				//{
				//	if (g_aBullet[nCountBullet].pos.x >= pPlayer->pos.x - 100
				//		&& g_aBullet[nCountBullet].pos.x <= pPlayer->pos.x + 100
				//		&& g_aBullet[nCountBullet].pos.y >= pPlayer->pos.y - 50
				//		&& g_aBullet[nCountBullet].pos.y <= pPlayer->pos.y + 50
				//		)
				//	{
				//		HitPlayer(pEnemy->atack);
				//		g_aBullet[nCountBullet].bUse = false;
				//	}
				//}
			}
			g_aBullet[nCountBullet].pos.x += g_aBullet[nCountBullet].move.x;
			g_aBullet[nCountBullet].pos.y += g_aBullet[nCountBullet].move.y;

			//���_���W�̍X�V
			pVtx[0].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z - (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y - 25.0f;
			pVtx[0].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z - (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x - 150.0f;
			pVtx[0].pos.z = 0.0f;//0.0f;
			pVtx[1].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z + (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x + 150.0f;
			pVtx[1].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z + (D3DX_PI - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y - 25.0f;
			pVtx[1].pos.z = 0.0f;//0.0f;
			pVtx[2].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z + (0.0f - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x - 150.0f;
			pVtx[2].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z + (0.0f - g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y + 25.0f;
			pVtx[2].pos.z = 0.0f;//0.0f;
			pVtx[3].pos.x = g_aBullet[nCountBullet].pos.x + sinf(g_aBullet[nCountBullet].rot.z + (0.0f + g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.x + 150.0f;
			pVtx[3].pos.y = g_aBullet[nCountBullet].pos.y + cosf(g_aBullet[nCountBullet].rot.z + (0.0f + g_aBullet[nCountBullet].fAngle)) * g_aBullet[nCountBullet].fLength;//pos.y + 25.0f;
			pVtx[3].pos.z = 0.0f;

			SetEffect(g_aBullet[nCountBullet].pos,
				g_aBullet[nCountBullet].move,
				BULLETTYPE_PLAYER,
				90,
				g_aBullet[nCountBullet].fAngle,
				g_aBullet[nCountBullet].rot);

			if (g_aBullet[nCountBullet].pos.x >= WINDOW_WIDTH||g_aBullet[nCountBullet].pos.x<=0|| g_aBullet[nCountBullet].pos.y >= WINDOW_HEITH || g_aBullet[nCountBullet].pos.y <= 40)
			{
				SetExprotion(g_aBullet[nCountBullet].pos,D3DXCOLOR(255,255,255,255));
				g_aBullet[nCountBullet].bUse = false;
			}
		}
		pVtx += 4;//���_�o�b�t�@�̃|�C���^���S���i�߂�
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		Enemy* pEnemy = GetEnemy();
		if (pEnemy->bUse == true)
		{
			if (pEnemy->pos.y + ENEMY_HEIGHT >= WINDOW_HEITH)
			{
				HitEnemy(i,9999);
				HitPlayer(1);
			}
		}
		pEnemy++;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}
//�v���C���[�̕`�揈��
void DrawBullet(void)
{
	int ncount;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX2D));

	for (ncount = 0; ncount < MAX_Bullet; ncount++)
	{
		if (g_aBullet[ncount].bUse == true)
		{
			//�e�N�X�`���̐ݒ� 
			pDevice->SetTexture(0, g_pTextureBullet1);//��ڂ̃|���S��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,ncount*4,2);
		}
	}
}
//�e�̐ݒ菈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,float fLength,float fAngle,D3DXVECTOR3 rot,D3DXVECTOR3 expos)
{
	int nCountBullet;
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
	for (nCountBullet = 0; nCountBullet < MAX_Bullet; nCountBullet++)
	{
		if (g_aBullet[nCountBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ�
			g_aBullet[nCountBullet].rot = rot;
			g_aBullet[nCountBullet].fLength = fLength;
			g_aBullet[nCountBullet].fAngle = fAngle;
			g_aBullet[nCountBullet].pos = pos;
			g_aBullet[nCountBullet].move = move;
			g_aBullet[nCountBullet].type = type;
			g_aBullet[nCountBullet].exprotionpos = expos;
			g_aBullet[nCountBullet].bUse = true;//�g�p���Ă����Ԃɂ���

			pVtx[0].pos.x = pos.x + sinf(rot.z - (D3DX_PI - fAngle)) * fLength;//pos.y - 25.0f;
			pVtx[0].pos.y = pos.y + cosf(rot.z - (D3DX_PI - fAngle)) * fLength;//pos.x - 150.0f;
			pVtx[0].pos.z = 0.0f;//0.0f;
			pVtx[1].pos.x = pos.x + sinf(rot.z + (D3DX_PI - fAngle)) * fLength;//pos.x + 150.0f;
			pVtx[1].pos.y = pos.y + cosf(rot.z + (D3DX_PI - fAngle)) * fLength;//pos.y - 25.0f;
			pVtx[1].pos.z = 0.0f;//0.0f;
			pVtx[2].pos.x = pos.x + sinf(rot.z + (0.0f - fAngle)) * fLength;//pos.x - 150.0f;
			pVtx[2].pos.y = pos.y + cosf(rot.z + (0.0f - fAngle)) * fLength;//pos.y + 25.0f;
			pVtx[2].pos.z = 0.0f;//0.0f;
			pVtx[3].pos.x = pos.x + sinf(rot.z + (0.0f + fAngle)) * fLength;//pos.x + 150.0f;
			pVtx[3].pos.y = pos.y + cosf(rot.z + (0.0f + fAngle)) * fLength;//pos.y + 25.0f;
			pVtx[3].pos.z = 0.0f;

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
 }