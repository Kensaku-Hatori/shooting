#ifndef _CURSOR_H_
#define _CURSOR_H_
#include"main.h"
#define Cursorwidth (50)
#define Cursorheight (50)
#define CURSOR_MOVE_X (6)
#define CURSOR_MOVE_Y (6)

typedef struct
{
	D3DXVECTOR3 pos;		// �J�[�\���̏ꏊ
	D3DXVECTOR3 move;		// �J�[�\���̈ړ���
	D3DXVECTOR3 rot;		// �J�[�\���̌���
	float nLengthCusor;		// �Ίp���̒���
	float fAngleCusor;		// �Ίp���̊p�x
	bool bUse;				// �J�[�\���̎g�p��
}Cursor;


//================
//�v���g�^�C�v�錾
//================
void InitCursor(void);		// �J�[�\���̏���������
void UninitCursor(void);	// �J�[�\���̏I������
void UpdateCursor(void);	// �J�[�\���̍X�V����
void DrawCursor(void);		// �J�[�\���̕`�揈��
Cursor* GetCursor1(void);	// �J�[�\���̍��W�̎擾����
#endif