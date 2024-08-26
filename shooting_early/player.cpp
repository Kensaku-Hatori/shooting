#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include"score.h"
#include "exprotion.h"
#include"cusor.h"

LPDIRECT3DTEXTURE9 g_pTexturePlayer1 = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Player g_player;


//�v���C���[�̏���������
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\spaceShips_001.png",
		&g_pTexturePlayer1);

	g_player.pos = D3DXVECTOR3(WINDOW_WIDTH / 2, WINDOW_HEITH, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.nLengthPlayer = sqrtf(Playerwidth * Playerwidth + Playerheight * Playerheight);
	g_player.fAnglePlayer = atan2f(Playerwidth, Playerheight);
	g_player.bUse = true;
	g_player.level = 1;
	g_player.nLife = MIN_LIFE;
	g_player.atack = MIN_ATACK;
	g_player.interval = MIN_INTERVAL;
	g_player.way = MIN_WAY;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D)*4,//�m�ۂ������o�b�t�@��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL
	);
	VERTEX2D *pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��

	//���_���W�̍X�V			
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI + g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.y - 25.0f;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI + g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.x - 150.0f;
	pVtx[0].pos.z = 0.0f;//0.0f;
	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.x + 150.0f;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.y - 25.0f;
	pVtx[1].pos.z = 0.0f;//0.0f;
	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.x - 150.0f;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.y + 25.0f;
	pVtx[2].pos.z = 0.0f;//0.0f;
	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.x + 150.0f;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.fAnglePlayer)) * g_player.nLengthPlayer;//pos.y + 25.0f;
	pVtx[3].pos.z = 0.0f;

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}
//�v���C���[�̏I������
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer1 != NULL)
	{
		g_pTexturePlayer1->Release();
		g_pTexturePlayer1 = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer=NULL;
	}
}
//�v���C���[�̍X�V����
void UpdatePlayer(void)
{
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��

	Cursor *pcursor = GetCursor1();

	if (g_player.intervalcount <= MIN_INTERVAL)
	{
		g_player.intervalcount++;
	}

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_player.statecount--;
		if (g_player.statecount <= 0)
		{
			g_player.statecount = 0;
			g_player.state = PLAYERSTATE_NORMAL;
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//RGB�Ɠ����x
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		break;
	}
		if (KeyboardTrigger(DIK_SPACE) || JoyPadTrigger(JOYKEY_A))
		{
			if (g_player.interval <= g_player.intervalcount)
			{
				g_player.intervalcount = 0;
				for (int i = 0; i < g_player.way; i++)
				{
					SetBullet
					(
						g_player.pos,
						D3DXVECTOR3
						(
							sinf(g_player.rot.z) * 20.0f,
							cosf(g_player.rot.z) * 20.0f,
							0.0f
						),
						BULLETTYPE_PLAYER,
						sqrtf(BULLED_WIDTH * BULLED_WIDTH + BULLED_HEIGHT * BULLED_HEIGHT),
						atan2f(BULLED_WIDTH, BULLED_HEIGHT),
						g_player.rot,
						pcursor->pos
					);
				}
			}
		}

		if (g_player.bUse == true)
		{
			switch (g_player.state)
			{
			case ENEMYSTATE_DAMAGE:
				g_player.statecount--;
				if (g_player.statecount <= 0)
				{
					g_player.state = PLAYERSTATE_NORMAL;
					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//RGB�Ɠ����x
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
			}
		}

		g_player.rot.z = atan2f(pcursor->pos.x - g_player.pos.x, pcursor->pos.y - g_player.pos.y),
		pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z - (D3DX_PI - g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z - (D3DX_PI - g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.fAnglePlayer)) * g_player.nLengthPlayer;
		pVtx[3].pos.z = 0.0f;
		g_pVtxBuffPlayer->Unlock();
}
//�v���C���[�̕`�揈��
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX2D));

	if (g_player.bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer1);//��ڂ̃|���S��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
void HitPlayer(int nDamageEnemy)
{
	g_player.nLife -= nDamageEnemy;
	if (g_player.nLife <= 0)
	{
		SetExprotion(g_player.pos, D3DXCOLOR(255, 255, 255, 255));
		g_player.bUse = false;
	}
	else
	{
		VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.statecount = 5;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);//RGB�Ɠ����x
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		g_pVtxBuffPlayer->Unlock();
	}
}
Player* GetPlayer(void)
{
	return &g_player;
}