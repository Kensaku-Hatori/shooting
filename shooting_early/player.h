#ifndef _PALYER_H_
#define _PLAYER_H_
#define Playerwidth (100)
#define Playerheight (100)
#define MIN_LIFE (100)
#define MIN_ATACK (10)
#define MIN_INTERVAL (6)
#define MIN_WAY (1)
typedef enum
{
	PLAYERSTATE_NORMAL = 0,	// �v���C���[���������Ă��Ȃ��Ƃ��̏��
	PLAYERSTATE_DAMAGE,		// �v���C���[���_���[�W��H������Ƃ�
	PLAYERSTATE_MAX
}PLAYERSTATE;
typedef struct
{
	D3DXVECTOR3 pos;		// �ꏊ
	D3DXVECTOR3 rot;		// ����
	PLAYERSTATE state;		// ���
	int cooldown;
	int statecount;
	int nCountAnimPlayer;	// �A�j���[�V�����J�E���g
	int nPatternAnimPlayer;	// �A�j���[�V�����p�^�[��No
	float nLengthPlayer;	// �Ίp���̒���
	float fAnglePlayer;		// �Ίp���̊p�x
	bool bUse;				// �v���C���[�̎g�p���
	int level;				// �v���C���[�̃��x��
	int nLife;				// �v���C���[��HP
	int atack;				// �v���C���[�̍U����
	int interval;			// �v���C���[�̍U���Ԋu
	int way;				// �v���C���[�����˂���ʂ̐�
	int intervalcount;
}Player;


//================
//�v���g�^�C�v�錾
//================
void InitPlayer(void);				// �v���C���[�̏���������
void UninitPlayer(void);			// �v���C���[�̏I������
void UpdatePlayer(void);			// �v���C���[�X�V����
void DrawPlayer(void);				// �v���C���[�̕`�揈��
void HitPlayer(int nDamageEnemy);	// �v���C���[�̃q�b�g����
Player*GetPlayer(void);				// �v���C���[�̍��W�̎擾����
#endif