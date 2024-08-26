#include "main.h"
#include "player.h"
#define NUM_BG (3)
LPDIRECT3DTEXTURE9 g_pTextureBackground[NUM_BG] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBackground = NULL;	//���_�o�b�t�@�ւ̃|�C���^
float g_aPosTexU[NUM_BG];

void Initbackground(void)//�w�i�̏���������
{
	int ncountBG;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg100.png",
		&g_pTextureBackground[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg101.png",
		&g_pTextureBackground[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg102.png",
		&g_pTextureBackground[2]);
	for (ncountBG = 0; ncountBG < NUM_BG; ncountBG++)
	{
		g_aPosTexU[ncountBG] = 0.0f;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4*NUM_BG,//�m�ۂ������o�b�t�@��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBackground,
		NULL
	);
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��

	for (ncountBG = 0; ncountBG < NUM_BG; ncountBG++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E���[���Ԗ�
		pVtx[1].pos = D3DXVECTOR3(WINDOW_WIDTH, 0.0f, 0.0f);//��Ԗ�
		pVtx[2].pos = D3DXVECTOR3(0.0f, WINDOW_HEITH, 0.0f);//��Ԗ�
		pVtx[3].pos = D3DXVECTOR3(WINDOW_WIDTH, WINDOW_HEITH, 0.0f);//�O�Ԗ�

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
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[ncountBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[ncountBG]+1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[ncountBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[ncountBG]+1.0f, 1.0f);
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBackground->Unlock();
}
void Uninitbackground(void)//�w�i�̔j��
{
	int ncountbg;
	//�e�N�X�`���̔j��
	for (ncountbg =0; ncountbg < NUM_BG; ncountbg++)
	{
		if (g_pTextureBackground[ncountbg] != NULL)
		{
			g_pTextureBackground[ncountbg]->Release();
			g_pTextureBackground[ncountbg] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBackground != NULL)
	{
		g_pVtxBuffBackground->Release();
		g_pVtxBuffBackground = NULL;
	}
}
void Updatebackground(void)//�w�i�̍X�V����
{
	int ncountbg;
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
	for (ncountbg = 0; ncountbg < NUM_BG; ncountbg++)
	{
		g_aPosTexU[ncountbg]+=0.001f*(ncountbg+1);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[ncountbg], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[ncountbg] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[ncountbg], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[ncountbg] + 1.0f, 1.0f);
		pVtx += 4;
	}
	g_pVtxBuffBackground->Unlock();
}
void Drawbackground(void)//�w�i�̕`�揈��
{
	int ncountbg;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffBackground, 0, sizeof(VERTEX2D));

	for (ncountbg = 0; ncountbg < NUM_BG; ncountbg++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBackground[ncountbg]);//��ڂ̃|���S��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*ncountbg, 2);
	}
}