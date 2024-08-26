#ifndef _IN_H_
//���̃}�N����`������Ă��Ȃ�������
#define _IN_H_
//------------------------------------------------
#include "main.h"
typedef enum
{
	JOYKEY_UP =0,// �\���L�[�i���j
	JOYKEY_DOWN,
	JOYKEY_RIGHT,
	JOYKEY_LEFT,
	JOYKEY_START,
	JOYKEY_BACK,
	JOYKEY_LEFTSTICK,
	JOYKEY_RIGHTSTICK,
	JOYKEY_L1,
	JOYKEY_R1,
	JOYKEY_L2,
	JOYKEY_R2,
	JOYKEY_A,
	JOYKEY_B,
	JOYKEY_X,
	JOYKEY_Y,
	JOYKEY_MAX
}JOYKEY;


//================
//�v���g�^�C�v�錾
//================
// �L�[�{�[�h����������
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
// �L�[�{�[�h�I������
void UninitKeyboard(void);
// �L�[�{�[�h�X�V����
void UpdateKeyboard(void);
// �L�[�{�[�h�l������
bool GetKeyboard(int nKey);
// �L�[�{�[�h�g���K�[����
bool KeyboardTrigger(int nKey);
// �L�[�{�[�h�𗣂������̏���
bool KeyboardRelease(int nKey);
// �L�[�{�[�h�̒���������
bool KeyboardRepeat(int nKey);


// �Q�[���p�b�h����������
HRESULT InitJoyPad(void);
// �Q�[���p�b�h�I������
void UninitJoyPad(void);
// �Q�[���p�b�h�X�V����
void UpdateJoyPad(void);
// �Q�[���p�b�h�l������
bool GetJoyPadPress(JOYKEY key);
// �Q�[���p�b�h�̃g���K�[����
bool JoyPadTrigger(JOYKEY key);
#endif