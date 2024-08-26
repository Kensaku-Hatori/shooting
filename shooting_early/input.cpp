#include "input.h"

#define NUM_KEY_MAX (256)//キーの最大数
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];
BYTE g_oldstate[NUM_KEY_MAX];
XINPUT_STATE g_joykeystate;
XINPUT_STATE g_oldjoykeystate;

//==================================
// キーボードの初期化処理
//==================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	// 入力デバイスの設定
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	// 入力フォーマットの設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// 協調モードの設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//==================================
// キーボードの終了処理
//==================================
void UninitKeyboard()
{
	if (g_pDevKeyboard != NULL)
	{
		// キーボードへのアクセス権を破棄
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
// キーボードの更新処理
//==================================
void UpdateKeyboard()
{
	// キーボードの入力情報
	byte aKeyState[NUM_KEY_MAX];
	int nCountKey;
	// 入力デバイスからデータを習得
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
// キーボードの獲得処理
//==================================
bool GetKeyboard(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true: false;
}
//==================================
// キーボードのトリガー処理
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
// キーボードの離した時の処理
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
// キーボードの長押し処理
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
// ゲームパッドの初期化処理
//==================================
HRESULT InitJoyPad(void)
{
	// メモリのクリア
	memset(&g_joykeystate, 0, sizeof(XINPUT_STATE));
	memset(&g_oldjoykeystate, 0, sizeof(XINPUT_STATE));


	// Xinputのステートを設定（有効）にする
	XInputEnable(true);

	return S_OK;
}
//==================================
// ゲームパッドの終了処理
//==================================
void UninitJoyPad(void)
{
	// Xinputのステートを設定（無効）にする
	XInputEnable(false);
}
//==================================
// ゲームパッドの更新処理
//==================================
void UpdateJoyPad(void)
{
	// ジョイパッドの入力情報
	XINPUT_STATE joykeystate;

	g_oldjoykeystate = g_joykeystate;
	if (XInputGetState(0,&joykeystate) == ERROR_SUCCESS)
	{
		// ゲームパッドのプレス情報を保持
		g_joykeystate = joykeystate;
	}
}
//==================================
// ゲームパッドの獲得処理
//==================================
bool GetJoyPadPress(JOYKEY key)
{
	return (g_joykeystate.Gamepad.wButtons & (0x01 << key)) ? true:false;
}
//==================================
// ゲームパッドのトリガー処理
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