#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h" 
#define MAX_ENEMY (128)
#define ENEMY_WIDTH (50)
#define ENEMY_HEIGHT (50)
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_MAX
}ENEMYSTATE;

typedef enum
{
	ENEMYTYPE_ONE = 0,
	ENEMYTYPE_TWE,
	ENEMYTYPE_MAX
}ENEMYTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	// �G�̈ʒu
	D3DXVECTOR3 move;	// �G�̈ړ���
	D3DXVECTOR3 rot;	// �G�̌���
	ENEMYSTATE state;	// �G�̏��
	int cooldown;		// �G�̏o���Ԋu
	int cooldowncount;	// �G�̏o���Ԋu�̃J�E���g�_�E��
	int statecount;		// �G�̏�Ԃ̎��Ԃ��J�E���g
	int nLife;			// �G��HP
	int nType;			// �G�̎��
	bool bUse;			// �G�̎g�p��
	int atack;			// �G�̍U����
}Enemy;


//================
//�v���g�^�C�v�錾
//================
void InitEnemy(void);						// �G�̏���������
void UninitEnemy(void);						// �G�̏I������
void UpdateEnemy(void);						// �G�̍X�V����
void DrawEnemy(void);						// �G�̕`�揈��
void SetEnemy(D3DXVECTOR3 pos, int nType);	// �G�̐ݒ菈��
void HitEnemy(int nCntEnemy, int nDamage);	// �G�̃q�b�g����
int GetNumEnemy();							// �G�̑������擾
Enemy* GetEnemy(void);						// �G�̍��W�擾����
#endif