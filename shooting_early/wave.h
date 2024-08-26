#include"main.h"
#include"enemy.h"
#include"game.h"

#define WAVE_ENEMY (1)

typedef enum
{
	NONE_WAVE = 0,
	FIRST_WAVE,
	SECOND_WAVE,
	THIRD_WAVE,
	FOURTH_WAVE,
	FIFTH_WAVE,
	END_WAVE,
	MAX_WAVE
}WAVE_STATE;

typedef struct
{
	bool bUse;				// �E�F�[�u�̎g�p��
	WAVE_STATE wavestate;	// �E�F�[�u�̏��
	int nwavestate;
	int timecount;			// �E�F�[�u�̓G�������Ԋu���J�E���g
	int wavecount;
	bool waveflag;
	int waveenemycount;
}WAVE;


//================
//�v���g�^�C�v�錾
//================
void InitWave(void);	// �E�F�[�u�̏���������
void UninitWave(void);	// �E�F�[�u�̏I������
void UpdateWave(void);	// �E�F�[�u�̍X�V����
void DrawWave(void);	// �E�F�[�u�̕`�揈��
void SetWave();			// �E�F�[�u�̐ݒ菈��
WAVE* GetWave(void);	// �E�F�[�u���̎擾����