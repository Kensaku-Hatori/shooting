#ifndef _EXPROTION_H_
#define _EXPROTION_H_
#include "main.h"
#define EXPROSION_WIDTH (100)
#define EXPROSION_HEITH (100)

typedef struct
{
	D3DXVECTOR3 pos;	// �����̈ʒu
	D3DXCOLOR col;		// �����̐F
	int nCountAnim;		// �����̃A�j���[�V�����̊Ԋu
	int nPatternAnim;	// �����̃A�j���[�V�����̑���
	bool bUse;			// �����̎g�p��
}Exprotion;


//================
//�v���g�^�C�v�錾
//================
void InitExprotion(void);							// �����̏���������
void UninitExprotion(void);							// �����̏I������
void UpdateExprotion(void);							// �����̍X�V����
void DrawExprotion(void);							// �����̕`�揈��
void SetExprotion(D3DXVECTOR3 pos, D3DXCOLOR col);	// �����̐ݒ菈��
Exprotion *GetExprosion(void);						// �����̍��W�擾����
#endif