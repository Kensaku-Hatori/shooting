#include "bg.h"
#include "bullet.h"
#include "exprotion.h"
#include "game.h"
#include "enemy.h"
#include "player.h"
#include "fade.h"
#include "score.h"
#include"cusor.h"
#include"wave.h"
#include"item.h"
#include"effect.h"


GAMESTATE g_gamestate = GAMESTATE_NONE;
int ncountergamestate = 0;
void InitGame(void)
{
	Initbackground();//�w�i�̏���������
	InitCursor();
	Initscore();
	InitWave();
	InitItem();
	InitEffect();
	InitPlayer();//�v���C���[�̏���������
	InitBullet();//�v���C���[�̏���������
	InitExprotion();//�v���C���[�̏���������
	InitEnemy();//�v���C���[�̏���������
	SetEnemy(D3DXVECTOR3(600.0f, 300.0f, 0.0f), 1);
	//SetEnemy(D3DXVECTOR3(300.0f, 600.0f, 0.0f), 1);
	g_gamestate = GAMESTATE_NORMAL;
	ncountergamestate = 0;
}
void UninitGame(void)
{
	Uninitbackground();//�w�i�̏I������
	UninitCursor();
	Uninitscore();
	UninitWave();
	UninitItem();
	UninitEffect();
	UninitPlayer();//�v���C���[�̏I������
	UninitBullet();//�v���C���[�̏I������
	UninitExprotion();//�v���C���[�̏I������
	UninitEnemy();//�v���C���[�̏I������
}
void UpdateGame(void)
{
	srand((unsigned int)time(NULL));
	Updatebackground();//�w�i�̍X�V����
	UpdateCursor();
	Updatescore();
	UpdateWave();
	UpdateItem();
	UpdatePlayer();//�v���C���[�̍X�V����
	UpdateBullet();//�v���C���[�̍X�V����
	UpdateEffect();
	UpdateExprotion();//�v���C���[�̍X�V����
	UpdateEnemy();//�v���C���[�̍X�V����
	int Num = GetNumEnemy();
	Player* player = GetPlayer();
	if (player->bUse == false)
	{
		g_gamestate = GAMESTATE_END;
	}
	switch (g_gamestate)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_END:
		ncountergamestate++;
		if (ncountergamestate >= 60)
		{
			ncountergamestate = 0;
			g_gamestate = GAMESTATE_NONE;
			SetFade(MODE_RESULT);
		}
		break;
	}
}
void DrawGame(void)
{
	Drawbackground();//�w�i�̕`�揈��
	Drawscore();
	DrawItem();
	DrawEffect();
	DrawPlayer();//�v���C���[�̕`�揈��
	DrawBullet();//�v���C���[�̕`�揈��
	DrawExprotion();//�v���C���[�̕`�揈��
	DrawEnemy();//�v���C���[�̕`�揈��
	DrawCursor();
}
void SetState(GAMESTATE state)
{
	g_gamestate = state;
}
GAMESTATE Getgamestate()
{
	return g_gamestate;
}