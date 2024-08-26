#include"main.h"
#include"wave.h"
#include"game.h"
#include"enemy.h"
#include"fade.h"

LPDIRECT3DTEXTURE9 g_pTextureWave1 = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWave = NULL;	//���_�o�b�t�@�ւ̃|�C���^
WAVE g_Wave;

void InitWave(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Wave001.jpg",
		&g_pTextureWave1);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4 * MAX_WAVE,//�m�ۂ������o�b�t�@��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWave,
		NULL
	);


	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffWave->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��


	g_Wave.bUse = false;
	g_Wave.wavestate = NONE_WAVE;
	g_Wave.waveenemycount = 0;
	g_Wave.nwavestate = 0;

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
	g_pVtxBuffWave->Unlock();
}
void UninitWave(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWave1 != NULL)
	{
		g_pTextureWave1->Release();
		g_pTextureWave1 = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWave != NULL)
	{
		g_pVtxBuffWave->Release();
		g_pVtxBuffWave = NULL;
	}
}
void UpdateWave(void)
{
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffWave->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
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
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffWave, 0, sizeof(VERTEX2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureWave1);//��ڂ̃|���S��
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
