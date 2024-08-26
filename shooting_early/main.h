//-----------------
// ヘッダーファイル
//-----------------
#ifndef _MAIN_H_					//このマクロ定義がされていなかったら
#define _MAIN_H_					//二重インクルードの防止用マクロ定義
//--------------------------------------------------------------------------------------------------↓必須
#include <windows.h>
#include "d3dx9.h"					//ダイレクトエックス用
//入植処理用--------------------------------------
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "Xinput.h"
#include "xaudio2.h"
#include"stdlib.h"
#include<time.h>
#include<stdio.h>
//------------------------------------------------
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"d3d9.lib")		//ダイレクトエックス用
#pragma comment(lib,"d3dx9.lib")		//ダイレクトエックス用
#pragma comment(lib,"dxguid.lib")	//ダイレクトエックス用
#pragma comment(lib,"xinput.lib")//ゲームパッド用
#pragma comment(lib,"winmm.lib")

#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "ウィンドウ表示処理"			//ゲーム名
#define WINDOW_WIDTH (1980)							//ウィンドウの横幅
#define WINDOW_HEITH (1080)							//ウィンドウの縦幅
//---------------------------------------------------------------------------------------------------
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//頂点情報
typedef enum
{
	MODE_TITLE = 0,	//タイトル画面
	MODE_GAME,		//ゲーム画面
	MODE_RESULT,	//リザルト画面
	MODE_MAX
}MODE;
typedef struct//ポリゴン描画用の構造体
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;		//座標返還余殃変数(1.0fで固定)
	D3DCOLOR col;	//頂点から＾
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX2D;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//多分必須
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Draw(void);			//ダイレクトエックス用
void Update(void);			//ダイレクトエックス用
void Uninit(void);			//ダイレクトエックス用
void SetMode(MODE mode);	//モード窃盗用
MODE GetMode(void);			//モード州直用
void delay(int milisecond);
void ToggleFullscreen(HWND hWnd);
#endif