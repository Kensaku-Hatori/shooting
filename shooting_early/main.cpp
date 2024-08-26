#include "main.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include"score.h"

//グローバル変数宣言
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
MODE g_mode = MODE_TITLE;//現在のモード
bool g_isFullscreen = false;// ウィンドウを切り替えるためのフラグ
RECT g_windowRect;// ウィンドウを切り替えるための変数

void ToggleFullscreen(HWND hWnd)
{
	// 現在のウィンドウスタイルを取得
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// ウィンドウモードに切り替え
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// フルスクリーンモードに切り替え
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}
//--------------------
//メイン関数
//--------------------
int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_ HINSTANCE hInstacePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//このアプリケーションのインスタンス,常に塗る,引数で受け取ったポインタ,ウィンドの表示方法
{
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	WNDCLASSEX wcex =//構造体
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};
	HWND hWnd;//ウィンドウハンドル
	MSG msg;  //メッセージ用変数
	RECT rect = {0, 0, WINDOW_WIDTH, WINDOW_HEITH};
	RegisterClassEx(&wcex);
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindowEx(0,						//拡張ウィンドウ
				   		  CLASS_NAME,				//ウィンドウのクラス
					      WINDOW_NAME,				//ウィンドウの名前
						  WS_OVERLAPPEDWINDOW,		//ウィンドウのスタイル
						  CW_USEDEFAULT,			//ウィンドウの左端
						  CW_USEDEFAULT,			//" "
						  (rect.right - rect.left),	//" "
						  (rect.bottom - rect.top),	//" "
				   		  NULL,						//親ウィドウのハンドル
						  NULL,						//メニューハンドル
						  hInstance,				//インスタンスハンドル
						  NULL);					//ウィンドウ作成テスト
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	ShowWindow(hWnd, nCmdShow);					//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);//クライアント領域を更新
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);//仮想キーメッセージを文字メッセジーへ変換
				DispatchMessage(&msg); //ウィンドウプロシージャへメッセージを返信
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;
				Update();
				Draw();
			}
		}
	}
	Uninit();
	timeEndPeriod(1);
	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME,wcex.hInstance);
	return (int)msg.wParam;
	return 0;
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN://キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE://[ESC]キーが押されたら
			nID = MessageBox(hWnd, "終了しますか?", "終了メッセージ", MB_YESNO | MB_ICONQUESTION);//メッセージボックスを出す
			if (nID == IDYES)//Yesが押されたら
			{
				DestroyWindow(hWnd);//ウィンドウを破棄する
				break;
			}
		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//既定の処理を渡す
}
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)//初期化処理
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3dオブジェクトを生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを習得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	ZeroMemory(&d3dpp, sizeof(d3dpp));							//パラメーターのゼロクリア
	d3dpp.BackBufferWidth = WINDOW_WIDTH;						//ゲームサイズ(幅)
	d3dpp.BackBufferHeight = WINDOW_HEITH;						//ゲームサイズ(縦)
	d3dpp.BackBufferFormat = d3ddm.Format;						//バッファの形式
	d3dpp.BackBufferCount = 1;									//バッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//ダブルバッファの切り替え
	d3dpp.EnableAutoDepthStencil = TRUE;						//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;									//ウィンドモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//インターバル
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//レンダーステートの生成
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			//科リングモードにする(裏側を描画しない)
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);			//アルファ値を有効にする
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);		//アルファ値を有効にする
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);	//アルファ値を有効にする
	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	if (FAILED(InitJoyPad()))
	{
		return E_FAIL;
	}	
	InitSound(hWnd);

	InitFade(g_mode);
	SetMode(g_mode);
	return S_OK;
}
void Update()//更新処理
{
	UpdateKeyboard();//キーボードの更新処理
	UpdateJoyPad();
	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
		UpdateTitle();
		break;
	case MODE_GAME://ゲーム画面
		UpdateGame();
		break;
	case MODE_RESULT://リザルト画面
		UpdateResult();
		break;
	default:
		break;
	}
	UpdateFade();
}
void Draw()//描画処理
{
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0,0,0,0),1.0f,0);
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_GAME:
			DrawGame();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		default:
			break;
		}
		DrawFade();
		////ここにポリゴンの描画処理を追加していく
		g_pD3DDevice->EndScene();
	}
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
void Uninit(void)//破棄する
{
	// タイトル画面の終了処理
	UninitTitle();
	// ゲーム画面の終了
	UninitGame();
	// リザルト画面の終了処理
	UninitResult();
	// フェイドの終了処理
	UninitFade();
	// サウンドの終了処理
	UninitSound();
	// キーボードの終了処理
	UninitKeyboard();
	// ゲームパッドの終了処理
	UninitJoyPad();
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	default:
		break;
	}
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	default:
		break;
	}
	g_mode = mode;
}
MODE GetMode(void)
{
	return g_mode;
}
void delay(int milisecond)
{
}