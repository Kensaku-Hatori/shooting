#include "result.h"
#include "input.h"
#include "main.h"
#include "fade.h"
LPDIRECT3DTEXTURE9 g_pTextureResult1 = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//���_�o�b�t�@�ւ̃|�C���^
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\result000.png",
		&g_pTextureResult1);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4,//�m�ۂ������o�b�t�@��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL
	);
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��

	//��ڂ̃|���S��
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E���[���Ԗ�
	pVtx[1].pos = D3DXVECTOR3(WINDOW_WIDTH, 0.0f, 0.0f);//��Ԗ�
	pVtx[2].pos = D3DXVECTOR3(0.0f,WINDOW_HEITH, 0.0f);//��Ԗ�
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
	g_pVtxBuffResult->Unlock();
}
void UninitResult(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureResult1 != NULL)
	{
		g_pTextureResult1->Release();
		g_pTextureResult1 = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}
void UpdateResult(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(MODE_TITLE);
	}
}
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult1);//��ڂ̃|���S��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}