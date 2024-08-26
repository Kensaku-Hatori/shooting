#include "score.h"
//===========================
// �}�E����`
//===========================
#define MAX_DIGIT (8)
#define uunti (10)


typedef struct
{
	bool buse;
}DIGIT;
//=================
// �O���[�o���ϐ�
//=================
LPDIRECT3DTEXTURE9 g_pTextureScore1 = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posscore;// �X�R�A�̍��W
int g_nscore;// �X�R�A�����߂�ϐ�
DIGIT g_score[MAX_DIGIT];

//===========================
// �X�R�A�̏���������
//===========================
void Initscore()
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&g_pTextureScore1);


	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4*MAX_DIGIT,//�m�ۂ������o�b�t�@��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL
	);


	g_posscore = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_nscore = 0;


	// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);


	for (int ncount = 0; ncount < MAX_DIGIT; ncount++, pVtx += 4)
	{
		//��ڂ̃|���S��
		pVtx[0].pos = D3DXVECTOR3(0.0f + ncount * 100.0f, 0.0f, 0.0f);//�E���[���Ԗ�
		pVtx[1].pos = D3DXVECTOR3(100.0f + ncount * 100.0f, 0.0f, 0.0f);//��Ԗ�
		pVtx[2].pos = D3DXVECTOR3(0.0f + ncount * 100.0f, 100.0f, 0.0f);//��Ԗ�
		pVtx[3].pos = D3DXVECTOR3(100.0f + ncount * 100.0f, 100.0f, 0.0f);//�O�Ԗ�

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;//�l��1.0f�ŌŒ�
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//RGB�Ɠ����x
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//===========================
// �X�R�A�̏I������
//===========================
void Uninitscore()
{
	// �e�N�X�`���̔j��
	if (g_pTextureScore1 != NULL)
	{
		g_pTextureScore1->Release();
		g_pTextureScore1 = NULL;
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
//===========================
// �X�R�A�̍X�V����
//===========================
void Updatescore()
{
	int ndata=0, ndata1=0;
	ndata = score(g_nscore);

	// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);


	for (ndata1 = 0; ndata1 < MAX_DIGIT; ndata1++)
	{
		if (ndata1 >= MAX_DIGIT - ndata)
		{
			g_score[ndata1].buse = true;
		}
		else
		{
			g_score[ndata1].buse = false;
		}
	}
}
//===========================
// �X�R�A�̕`�揈��
//===========================
void Drawscore()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX2D));


	for (int ncount = 0; ncount < MAX_DIGIT; ncount++)
	{
		if (g_score[ncount].buse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureScore1);//��ڂ̃|���S��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * ncount, 2);
		}
	}
}
//===========================
// �X�R�A�̐ݒ菈��
//===========================
void Setscore(int nscore)
{
	int apostexu[MAX_DIGIT];
	g_nscore = nscore;
}
//===========================
// �X�R�A�̉��Z����
//===========================
void Addscore(int nvalue)
{
	int apostexu[MAX_DIGIT],ncount,unti,unti1;
	unti = 100000000, unti1 = 10000000;
	g_nscore += nvalue;
	// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (ncount = 0; ncount < MAX_DIGIT; ncount++)
	{
		apostexu[ncount]=g_nscore%unti/unti1;
		unti = unti / uunti;
		unti1 = unti1 / uunti;
	}
	for (ncount = 0; ncount < MAX_DIGIT; ncount++, pVtx += 4)
	{
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + apostexu[ncount] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + apostexu[ncount] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + apostexu[ncount] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + apostexu[ncount]*0.1f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
int score(int score)
{
	int score1 = score;
	int digit=0;
	while (score1!=0)
	{
		score1/=uunti;
		digit++;
	}
	if (score == 0)
	{
		digit = 1;
	}
	return digit;
}