#include"cusor.h"
#include"main.h"
#include"input.h"
#include"bullet.h"
#include"player.h"

LPDIRECT3DTEXTURE9 g_pTextureCusor1 = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCusor = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Cursor g_Cusor;

void InitCursor()		//�v���C���[�p
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Cursor.png",
		&g_pTextureCusor1);

	g_Cusor.pos = D3DXVECTOR3(WINDOW_WIDTH / 2, WINDOW_HEITH / 2, 0.0f);
	g_Cusor.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Cusor.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Cusor.nLengthCusor = sqrtf(Cursorwidth * Cursorwidth + Cursorheight * Cursorheight / 2);
	g_Cusor.fAngleCusor = atan2f(Cursorwidth, Cursorheight);
	g_Cusor.bUse = true;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * 4,//�m�ۂ������o�b�t�@��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCusor,
		NULL
	);
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffCusor->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��


	pVtx[0].pos.x = g_Cusor.pos.x + sinf(g_Cusor.rot.z + (D3DX_PI + g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[0].pos.y = g_Cusor.pos.y + cosf(g_Cusor.rot.z + (D3DX_PI + g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_Cusor.pos.x + sinf(g_Cusor.rot.z + (D3DX_PI - g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[1].pos.y = g_Cusor.pos.y + cosf(g_Cusor.rot.z + (D3DX_PI - g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_Cusor.pos.x + sinf(g_Cusor.rot.z + (0.0f - g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[2].pos.y = g_Cusor.pos.y + cosf(g_Cusor.rot.z + (0.0f - g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_Cusor.pos.x + sinf(g_Cusor.rot.z + (0.0f + g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[3].pos.y = g_Cusor.pos.y + cosf(g_Cusor.rot.z + (0.0f + g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
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
	g_pVtxBuffCusor->Unlock();
}
void UninitCursor()	//�v���C���[�p
{
	//�e�N�X�`���̔j��
	if (g_pTextureCusor1 != NULL)
	{
		g_pTextureCusor1->Release();
		g_pTextureCusor1 = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCusor != NULL)
	{
		g_pVtxBuffCusor->Release();
		g_pVtxBuffCusor = NULL;
	}
}
void UpdateCursor(void)	//�v���C���[�p
{
	VERTEX2D* pVtx;//���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffCusor->Lock(0, 0, (void**)&pVtx, 0);//���_�o�b�t�@�����b�N���A���_�ւ̃|�C���^���K��


	if (GetKeyboard(DIK_A) || GetJoyPadPress(JOYKEY_LEFT))
	{
		if (GetKeyboard(DIK_W) || GetJoyPadPress(JOYKEY_UP))
		{
			g_Cusor.move.x -= CURSOR_MOVE_X;
			g_Cusor.move.y -= CURSOR_MOVE_Y;
		}
		else if (GetKeyboard(DIK_S) || GetJoyPadPress(JOYKEY_DOWN))
		{
			g_Cusor.move.x -= CURSOR_MOVE_X;
			g_Cusor.move.y += CURSOR_MOVE_Y;
		}
		else
		{
			g_Cusor.move.x -= CURSOR_MOVE_X;
		}
	}
	else if (GetKeyboard(DIK_D) || GetJoyPadPress(JOYKEY_LEFT))
	{
		if (GetKeyboard(DIK_W) || GetJoyPadPress(JOYKEY_UP))
		{
			g_Cusor.move.x += CURSOR_MOVE_X;
			g_Cusor.move.y -= CURSOR_MOVE_Y;
		}
		else if (GetKeyboard(DIK_S) || GetJoyPadPress(JOYKEY_DOWN))
		{
			g_Cusor.move.x += CURSOR_MOVE_X;
			g_Cusor.move.y += CURSOR_MOVE_Y;
		}
		else
		{
			g_Cusor.move.x += CURSOR_MOVE_X;
		}
	}
	else if (GetKeyboard(DIK_W) || GetJoyPadPress(JOYKEY_UP))
	{
		g_Cusor.move.y -= CURSOR_MOVE_Y;
	}
	else if (GetKeyboard(DIK_S) || GetJoyPadPress(JOYKEY_DOWN))
	{
		g_Cusor.move.y += CURSOR_MOVE_Y;
	}
	g_Cusor.pos.x += g_Cusor.move.x;
	g_Cusor.pos.y += g_Cusor.move.y;
	pVtx[0].pos.x = g_Cusor.pos.x + sinf(g_Cusor.rot.z + (D3DX_PI + g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[0].pos.y = g_Cusor.pos.y + cosf(g_Cusor.rot.z + (D3DX_PI + g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_Cusor.pos.x + sinf(g_Cusor.rot.z + (D3DX_PI - g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[1].pos.y = g_Cusor.pos.y + cosf(g_Cusor.rot.z + (D3DX_PI - g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_Cusor.pos.x + sinf(g_Cusor.rot.z + (0.0f - g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[2].pos.y = g_Cusor.pos.y + cosf(g_Cusor.rot.z + (0.0f - g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_Cusor.pos.x + sinf(g_Cusor.rot.z + (0.0f + g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[3].pos.y = g_Cusor.pos.y + cosf(g_Cusor.rot.z + (0.0f + g_Cusor.fAngleCusor)) * g_Cusor.nLengthCusor;
	pVtx[3].pos.z = 0.0f;
	g_Cusor.move.x += (0.0f - g_Cusor.move.x) * 0.5f;
	g_Cusor.move.y += (0.0f - g_Cusor.move.y) * 0.5f;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCusor->Unlock();
}
//�v���C���[�̕`�揈��
void DrawCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, g_pVtxBuffCusor, 0, sizeof(VERTEX2D));

	if (g_Cusor.bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureCusor1);//��ڂ̃|���S��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
Cursor* GetCursor1(void)
{
	return &g_Cusor;
}