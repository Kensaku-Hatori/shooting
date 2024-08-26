#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
typedef enum
{
	GAMESTATE_NONE = 0,	// �������Ă��Ȃ����
	GAMESTATE_NORMAL,	// �ʏ���
	GAMESTATE_END,		// �I�����
	GAMESTATE_MAX
}GAMESTATE;


//================
//�v���g�^�C�v�錾
//================
void InitGame(void);			// �Q�[���̏���������
void UninitGame(void);			// �Q�[���̏I������
void UpdateGame(void);			// �Q�[���̍X�V����
void DrawGame(void);			// �Q�[���̕`�揈��
void SetState(GAMESTATE state);	// �Q�[���̐ݒ菈��
GAMESTATE GetState(void);		// �Q�[���̏�Ԃ��擾����
#endif // !_GAME_H_