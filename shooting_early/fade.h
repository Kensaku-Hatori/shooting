#ifndef _FADE_H_
#define _FADE_H_
#include"main.h"
typedef enum
{
	FADE_NONE = 0,	//�t�F�[�h�̏��
	FADE_IN,		// �t�F�[�hIN�̏��
	FADE_OUT,		// �t�F�[�hOUT�̏��
	FADE_MAX
}FADE;


//================
//�v���g�^�C�v�錾
//================
void InitFade(MODE modeNext);	// �t�F�[�h�̏���������
void UninitFade(void);			// �t�F�[�h�̏I������
void UpdateFade(void);			// �t�F�[�h�̍X�V����
void DrawFade(void);			// �t�F�[�h�̕`�揈��
void SetFade(MODE modeNext);	// �t�F�[�h�̐ݒ菈��
FADE GetFade(void);				// �t�F�[�h�̏�Ԃ̎擾����
#endif