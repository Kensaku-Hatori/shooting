#include "input.h"

#define NUM_KEY_MAX (256)//�L�[�̍ő吔
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];
BYTE g_oldstate[NUM_KEY_MAX];
XINPUT_STATE g_joykeystate;
XINPUT_STATE g_oldjoykeystate;

//==================================
// �L�[�{�[�h�̏���������
//==================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	// ���̓f�o�C�X�̐ݒ�
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	// ���̓t�H�[�}�b�g�̐ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// �������[�h�̐ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//==================================
// �L�[�{�[�h�̏I������
//==================================
void UninitKeyboard()
{
	if (g_pDevKeyboard != NULL)
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X����j��
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//==================================
// �L�[�{�[�h�̍X�V����
//==================================
void UpdateKeyboard()
{
	// �L�[�{�[�h�̓��͏��
	byte aKeyState[NUM_KEY_MAX];
	int nCountKey;
	// ���̓f�o�C�X����f�[�^���K��
	for (nCountKey = 0; nCountKey < NUM_KEY_MAX; nCountKey++)
	{
		g_oldstate[nCountKey] = g_aKeyState[nCountKey];
	}
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCountKey = 0; nCountKey < NUM_KEY_MAX;nCountKey++)
		{
			g_aKeyState[nCountKey] = aKeyState[nCountKey];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}
//==================================
// �L�[�{�[�h�̊l������
//==================================
bool GetKeyboard(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true: false;
}
//==================================
// �L�[�{�[�h�̃g���K�[����
//==================================
bool KeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_oldstate[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//==================================
// �L�[�{�[�h�̗��������̏���
//==================================
bool KeyboardRelease(int nKey)
{
	bool Trigger = false;
	if (g_oldstate[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//==================================
// �L�[�{�[�h�̒���������
//==================================
bool KeyboardRepeat(int nKey)
{
	bool Trigger = false;
	if (g_oldstate[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//==================================
// �Q�[���p�b�h�̏���������
//==================================
HRESULT InitJoyPad(void)
{
	// �������̃N���A
	memset(&g_joykeystate, 0, sizeof(XINPUT_STATE));
	memset(&g_oldjoykeystate, 0, sizeof(XINPUT_STATE));


	// Xinput�̃X�e�[�g��ݒ�i�L���j�ɂ���
	XInputEnable(true);

	return S_OK;
}
//==================================
// �Q�[���p�b�h�̏I������
//==================================
void UninitJoyPad(void)
{
	// Xinput�̃X�e�[�g��ݒ�i�����j�ɂ���
	XInputEnable(false);
}
//==================================
// �Q�[���p�b�h�̍X�V����
//==================================
void UpdateJoyPad(void)
{
	// �W���C�p�b�h�̓��͏��
	XINPUT_STATE joykeystate;

	g_oldjoykeystate = g_joykeystate;
	if (XInputGetState(0,&joykeystate) == ERROR_SUCCESS)
	{
		// �Q�[���p�b�h�̃v���X����ێ�
		g_joykeystate = joykeystate;
	}
}
//==================================
// �Q�[���p�b�h�̊l������
//==================================
bool GetJoyPadPress(JOYKEY key)
{
	return (g_joykeystate.Gamepad.wButtons & (0x01 << key)) ? true:false;
}
//==================================
// �Q�[���p�b�h�̃g���K�[����
//==================================
bool JoyPadTrigger(JOYKEY key)
{
	bool Trigger = false;
	if (g_joykeystate.Gamepad.wButtons == (0x01 << key))
	{
		if (g_joykeystate.Gamepad.wButtons != g_oldjoykeystate.Gamepad.wButtons)
		{
			Trigger = true;
		}
	}
	return Trigger;
}