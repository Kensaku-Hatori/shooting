#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
#include"bullet.h"
#define EFFECT_WIDTH (100)
#define EFFECT_HEIGHT (100)


//================
//�v���g�^�C�v�錾
//================
void InitEffect(void);		// �e�̏���������
void UninitEffect(void);	// �e�̏I������
void UpdateEffect(void);	// �e�X�V����
void DrawEffect(void);		// �e�̕`�揈��
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,float fLength, float fAngle, D3DXVECTOR3 rot);// �e�̐ݒ菈��
#endif