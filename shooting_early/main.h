//-----------------
// �w�b�_�[�t�@�C��
//-----------------
#ifndef _MAIN_H_					//���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_					//��d�C���N���[�h�̖h�~�p�}�N����`
//--------------------------------------------------------------------------------------------------���K�{
#include <windows.h>
#include "d3dx9.h"					//�_�C���N�g�G�b�N�X�p
//���A�����p--------------------------------------
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "Xinput.h"
#include "xaudio2.h"
#include"stdlib.h"
#include<time.h>
#include<stdio.h>
//------------------------------------------------
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"d3d9.lib")		//�_�C���N�g�G�b�N�X�p
#pragma comment(lib,"d3dx9.lib")		//�_�C���N�g�G�b�N�X�p
#pragma comment(lib,"dxguid.lib")	//�_�C���N�g�G�b�N�X�p
#pragma comment(lib,"xinput.lib")//�Q�[���p�b�h�p
#pragma comment(lib,"winmm.lib")

#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "�E�B���h�E�\������"			//�Q�[����
#define WINDOW_WIDTH (1980)							//�E�B���h�E�̉���
#define WINDOW_HEITH (1080)							//�E�B���h�E�̏c��
//---------------------------------------------------------------------------------------------------
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//���_���
typedef enum
{
	MODE_TITLE = 0,	//�^�C�g�����
	MODE_GAME,		//�Q�[�����
	MODE_RESULT,	//���U���g���
	MODE_MAX
}MODE;
typedef struct//�|���S���`��p�̍\����
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;		//���W�Ԋҗ]�i�ϐ�(1.0f�ŌŒ�)
	D3DCOLOR col;	//���_����O
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX2D;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//�����K�{
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Draw(void);			//�_�C���N�g�G�b�N�X�p
void Update(void);			//�_�C���N�g�G�b�N�X�p
void Uninit(void);			//�_�C���N�g�G�b�N�X�p
void SetMode(MODE mode);	//���[�h�ޓ��p
MODE GetMode(void);			//���[�h�B���p
void delay(int milisecond);
void ToggleFullscreen(HWND hWnd);
#endif