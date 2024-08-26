#include "main.h"
#include "player.h"
#include "input.h"
#include "Exprotion.h"
#define MAX_Exprotion (128)//�e�̍ő吔
LPDIRECT3DTEXTURE9 g_pTextureExprotion1 = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExprotion = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Exprotion g_aExprotion[MAX_Exprotion];
void InitExprotion(void)		//�v���C���[�p
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCountExprotion;
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExprotion1);
	for (nCountExprotion = 0; nCountExprotion < MAX_Exprotion; nCountExprotion++)
	{
		g_aExprotion[nCountExprotion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExprotion[nCountExprotion].nCountAnim = 0;
		g_aExprotion[nCountExprotion].nPatternAnim = 0;
		g_aExprotion[nCountExprotion].col = D3DCOLOR(0.0);
		g_aExprotion[nCountExprotion].bUse = false;
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4*MAX_Exprotion,//�m�ۂ������o�b�t�@��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExprotion,
		NULL
	);
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffExprotion->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��

	for (nCountExprotion = 0; nCountExprotion < MAX_Exprotion; nCountExprotion++)//�e�̏������P�Q�W��
	{
		//��ڂ̃|���S��
		pVtx[0].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x, g_aExprotion[nCountExprotion].pos.y-50.0f, 0.0f);//�E���[���Ԗ�
		pVtx[1].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x + 100, g_aExprotion[nCountExprotion].pos.y -50.0f, 0.0f);//��Ԗ�
		pVtx[2].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x, g_aExprotion[nCountExprotion].pos.y+30.0f, 0.0f);//��Ԗ�
		pVtx[3].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x + 100, g_aExprotion[nCountExprotion].pos.y+30.0f, 0.0f);//�O�Ԗ�

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;//���_�o�b�t�@�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExprotion->Unlock();
}
//�v���C���[�̏I������
void UninitExprotion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureExprotion1 != NULL)
	{
		g_pTextureExprotion1->Release();
		g_pTextureExprotion1 = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExprotion != NULL)
	{
		g_pVtxBuffExprotion->Release();
		g_pVtxBuffExprotion = NULL;
	}
}
void UpdateExprotion(void)
{
	int nCountExprotion;
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffExprotion->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��

	for (nCountExprotion = 0; nCountExprotion < MAX_Exprotion; nCountExprotion++)
	{
		if (g_aExprotion[nCountExprotion].bUse == true)//�e���g�p����Ă�����
		{
			g_aExprotion[nCountExprotion].nCountAnim++;
			if (g_aExprotion[nCountExprotion].nCountAnim >= 5)
			{
				g_aExprotion[nCountExprotion].nCountAnim = 0;
				g_aExprotion[nCountExprotion].nPatternAnim++;
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f+g_aExprotion[nCountExprotion].nPatternAnim*0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f+g_aExprotion[nCountExprotion].nPatternAnim * 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + g_aExprotion[nCountExprotion].nPatternAnim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + g_aExprotion[nCountExprotion].nPatternAnim * 0.125f, 1.0f);
			}
			if (g_aExprotion[nCountExprotion].nPatternAnim>=8)
			{
				g_aExprotion[nCountExprotion].nPatternAnim = 0;
				g_aExprotion[nCountExprotion].bUse = false;
			}
		}
		pVtx += 4;//���_�o�b�t�@�̃|�C���^���S���i�߂�
	}
	g_pVtxBuffExprotion->Unlock();
}
//�v���C���[�̕`�揈��
void DrawExprotion(void)
{
	int ncount;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffExprotion, 0, sizeof(VERTEX2D));

	for (ncount = 0; ncount < MAX_Exprotion; ncount++)
	{
		if (g_aExprotion[ncount].bUse == true)
		{
			//�e�N�X�`���̐ݒ� 
			pDevice->SetTexture(0, g_pTextureExprotion1);//��ڂ̃|���S��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4*ncount,2);
		}
	}
}
//�e�̐ݒ菈��
void SetExprotion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCountExprotion;
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffExprotion->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
	for (nCountExprotion = 0; nCountExprotion < MAX_Exprotion; nCountExprotion++)
	{
		if (g_aExprotion[nCountExprotion].bUse == false)
		{
			g_aExprotion[nCountExprotion].pos = pos;
			g_aExprotion[nCountExprotion].col = col;
			g_aExprotion[nCountExprotion].bUse = true;
			//��ڂ̃|���S��
			pVtx[0].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x-EXPROSION_WIDTH, g_aExprotion[nCountExprotion].pos.y -EXPROSION_HEITH,0.0f);//�E���[���Ԗ�
			pVtx[1].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x + EXPROSION_WIDTH, g_aExprotion[nCountExprotion].pos.y - EXPROSION_HEITH,0.0f);//��Ԗ�
			pVtx[2].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x- EXPROSION_WIDTH, g_aExprotion[nCountExprotion].pos.y+ EXPROSION_HEITH, 0.0f);//��Ԗ�
			pVtx[3].pos = D3DXVECTOR3(g_aExprotion[nCountExprotion].pos.x + EXPROSION_WIDTH, g_aExprotion[nCountExprotion].pos.y+ EXPROSION_HEITH, 0.0f);//�O�Ԗ�
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffExprotion->Unlock();
}
Exprotion* GetExprosion(void)
{
	return &g_aExprotion[0];
}