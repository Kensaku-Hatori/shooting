#include "title.h"
#include "input.h"
#include "game.h"
#include"fade.h"
#include"sound.h"

LPDIRECT3DTEXTURE9 g_pTextureTitle1[TYPE_TITLE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;	//���_�o�b�t�@�ւ̃|�C���^
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title.png",
		&g_pTextureTitle1[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title1.png",
		&g_pTextureTitle1[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4*TYPE_TITLE,//�m�ۂ������o�b�t�@��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL
	);
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��


	//��ڂ̃|���S��
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E���[���Ԗ�
	pVtx[1].pos = D3DXVECTOR3(WINDOW_WIDTH, 0.0f, 0.0f);//��Ԗ�
	pVtx[2].pos = D3DXVECTOR3(0.0f, WINDOW_HEITH, 0.0f);//��Ԗ�
	pVtx[3].pos = D3DXVECTOR3(WINDOW_WIDTH,WINDOW_HEITH, 0.0f);//�O�Ԗ�

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
	g_pVtxBuffTitle->Unlock();
	PlaySound(SOUND_LABEL_BGM);
}
void UninitTitle(void)
{
	StopSound();
	//�e�N�X�`���̔j��
	for (int i = 0; i < TYPE_TITLE; i++)
	{
		if (g_pTextureTitle1[i] != NULL)
		{
			g_pTextureTitle1[i]->Release();
			g_pTextureTitle1[i] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
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
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX2D));

	for (int i= 0; i < TYPE_TITLE; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle1[i]);//��ڂ̃|���S��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}