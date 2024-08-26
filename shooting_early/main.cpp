#include "main.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include"score.h"

//�O���[�o���ϐ��錾
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
MODE g_mode = MODE_TITLE;//���݂̃��[�h
bool g_isFullscreen = false;// �E�B���h�E��؂�ւ��邽�߂̃t���O
RECT g_windowRect;// �E�B���h�E��؂�ւ��邽�߂̕ϐ�

void ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}
//--------------------
//���C���֐�
//--------------------
int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_ HINSTANCE hInstacePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//���̃A�v���P�[�V�����̃C���X�^���X,��ɓh��,�����Ŏ󂯎�����|�C���^,�E�B���h�̕\�����@
{
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	WNDCLASSEX wcex =//�\����
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
	HWND hWnd;//�E�B���h�E�n���h��
	MSG msg;  //���b�Z�[�W�p�ϐ�
	RECT rect = {0, 0, WINDOW_WIDTH, WINDOW_HEITH};
	RegisterClassEx(&wcex);
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindowEx(0,						//�g���E�B���h�E
				   		  CLASS_NAME,				//�E�B���h�E�̃N���X
					      WINDOW_NAME,				//�E�B���h�E�̖��O
						  WS_OVERLAPPEDWINDOW,		//�E�B���h�E�̃X�^�C��
						  CW_USEDEFAULT,			//�E�B���h�E�̍��[
						  CW_USEDEFAULT,			//" "
						  (rect.right - rect.left),	//" "
						  (rect.bottom - rect.top),	//" "
				   		  NULL,						//�e�E�B�h�E�̃n���h��
						  NULL,						//���j���[�n���h��
						  hInstance,				//�C���X�^���X�n���h��
						  NULL);					//�E�B���h�E�쐬�e�X�g
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	ShowWindow(hWnd, nCmdShow);					//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);//�N���C�A���g�̈���X�V
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
				TranslateMessage(&msg);//���z�L�[���b�Z�[�W�𕶎����b�Z�W�[�֕ϊ�
				DispatchMessage(&msg); //�E�B���h�E�v���V�[�W���փ��b�Z�[�W��ԐM
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
	//�E�B���h�E�N���X�̓o�^������
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
	case WM_KEYDOWN://�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE://[ESC]�L�[�������ꂽ��
			nID = MessageBox(hWnd, "�I�����܂���?", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION);//���b�Z�[�W�{�b�N�X���o��
			if (nID == IDYES)//Yes�������ꂽ��
			{
				DestroyWindow(hWnd);//�E�B���h�E��j������
				break;
			}
		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//����̏�����n��
}
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)//����������
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3d�I�u�W�F�N�g�𐶐�
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���K��
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	ZeroMemory(&d3dpp, sizeof(d3dpp));							//�p�����[�^�[�̃[���N���A
	d3dpp.BackBufferWidth = WINDOW_WIDTH;						//�Q�[���T�C�Y(��)
	d3dpp.BackBufferHeight = WINDOW_HEITH;						//�Q�[���T�C�Y(�c)
	d3dpp.BackBufferFormat = d3ddm.Format;						//�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									//�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//�_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;						//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;									//�E�B���h���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//�C���^�[�o��
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
	//�����_�[�X�e�[�g�̐���
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			//�ȃ����O���[�h�ɂ���(������`�悵�Ȃ�)
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);			//�A���t�@�l��L���ɂ���
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);		//�A���t�@�l��L���ɂ���
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);	//�A���t�@�l��L���ɂ���
	//�T���v���[�X�e�[�g�̐ݒ�
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
void Update()//�X�V����
{
	UpdateKeyboard();//�L�[�{�[�h�̍X�V����
	UpdateJoyPad();
	switch (g_mode)
	{
	case MODE_TITLE://�^�C�g�����
		UpdateTitle();
		break;
	case MODE_GAME://�Q�[�����
		UpdateGame();
		break;
	case MODE_RESULT://���U���g���
		UpdateResult();
		break;
	default:
		break;
	}
	UpdateFade();
}
void Draw()//�`�揈��
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
		////�����Ƀ|���S���̕`�揈����ǉ����Ă���
		g_pD3DDevice->EndScene();
	}
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
void Uninit(void)//�j������
{
	// �^�C�g����ʂ̏I������
	UninitTitle();
	// �Q�[����ʂ̏I��
	UninitGame();
	// ���U���g��ʂ̏I������
	UninitResult();
	// �t�F�C�h�̏I������
	UninitFade();
	// �T�E���h�̏I������
	UninitSound();
	// �L�[�{�[�h�̏I������
	UninitKeyboard();
	// �Q�[���p�b�h�̏I������
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