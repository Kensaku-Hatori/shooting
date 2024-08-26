#ifndef _IN_H_
//このマクロ定義がされていなかったら
#define _IN_H_
//------------------------------------------------
#include "main.h"
typedef enum
{
	JOYKEY_UP =0,// 十字キー（↑）
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
//プロトタイプ宣言
//================
// キーボード初期化処理
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
// キーボード終了処理
void UninitKeyboard(void);
// キーボード更新処理
void UpdateKeyboard(void);
// キーボード獲得処理
bool GetKeyboard(int nKey);
// キーボードトリガー処理
bool KeyboardTrigger(int nKey);
// キーボードを離した時の処理
bool KeyboardRelease(int nKey);
// キーボードの長押し処理
bool KeyboardRepeat(int nKey);


// ゲームパッド初期化処理
HRESULT InitJoyPad(void);
// ゲームパッド終了処理
void UninitJoyPad(void);
// ゲームパッド更新処理
void UpdateJoyPad(void);
// ゲームパッド獲得処理
bool GetJoyPadPress(JOYKEY key);
// ゲームパッドのトリガー処理
bool JoyPadTrigger(JOYKEY key);
#endif