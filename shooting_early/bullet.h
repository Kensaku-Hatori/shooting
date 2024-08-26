#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"

#define BULLED_WIDTH (100)
#define BULLED_HEIGHT (100)
typedef enum
{
	BULLETTYPE_PLAYER=0,// �e�̑������v���C���[�̎�
	BULLETTYPE_ENEMY,	// �e�̑������G�̎�
	BULLETTYPE_MAX
}BULLETTYPE;


//================
//�v���g�^�C�v�錾
//================
void InitBullet(void);		// �e�̏���������
void UninitBullet(void);	// �e�̏I������
void UpdateBullet(void);	// �e�X�V����
void DrawBullet(void);		// �e�̕`�揈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,float fLength, float fAngle, D3DXVECTOR3 rot,D3DXVECTOR3 expos);// �e�̐ݒ菈��
#endif