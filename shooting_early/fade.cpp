#include "fade.h"
#include "main.h"
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	//���_�o�b�t�@�ւ̃|�C���^
FADE g_Fade;
MODE g_modenext;
D3DXCOLOR g_colorFade;
void InitFade(MODE modenext)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();
		//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4,//�m�ۂ������o�b�t�@��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL
	);

	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��

	g_Fade = FADE_IN;

	g_modenext = modenext;

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

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
	pVtx[0].col = D3DCOLOR(g_colorFade);//RGB�Ɠ����x
	pVtx[1].col = D3DCOLOR(g_colorFade);
	pVtx[2].col = D3DCOLOR(g_colorFade);
	pVtx[3].col = D3DCOLOR(g_colorFade);

	g_pVtxBuffFade->Unlock();

	SetMode(g_modenext);
}
void UpdateFade()
{
	if (g_Fade != FADE_NONE)
	{
		if (g_Fade == FADE_IN)
		{
			g_colorFade.a -= 0.03f;

			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_Fade = FADE_NONE;
			}
		}
		else if (g_Fade == FADE_OUT)
		{
			g_colorFade.a += 0.03f;

			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_Fade = FADE_IN;
				SetMode(g_modenext);
			}
		}
		VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR(g_colorFade);//RGB�Ɠ����x
		pVtx[1].col = D3DCOLOR(g_colorFade);
		pVtx[2].col = D3DCOLOR(g_colorFade);
		pVtx[3].col = D3DCOLOR(g_colorFade);

		g_pVtxBuffFade->Unlock();
	}
}
void DrawFade()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);//��ڂ̃|���S��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void UninitFade()
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}
void SetFade(MODE modenext)
{
	g_Fade = FADE_OUT;
	g_modenext = modenext;
}
FADE GetFade(void)
{
	return g_Fade;
}