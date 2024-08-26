#include"main.h"
#include"enemy.h"
#include"game.h"

#define MAX_ITEM (128)

typedef enum
{
	NONE_ITEM=0,
	BOM_ITEM,
	SCOREUP_ITEM,
	MAX_ITEMTYPE
}ITEM_STATE;

typedef struct
{
	bool bUse;				// �E�F�[�u�̎g�p��
	ITEM_STATE Itemstate;	// �E�F�[�u�̏��
	int ncountItemAnim;			// �E�F�[�u�̓G�������Ԋu���J�E���g
	int ncountItemAnimPetternX;
	int ncountItemAnimPetternY;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
}ITEM;


//================
//�v���g�^�C�v�錾
//================
void InitItem(void);	// �E�F�[�u�̏���������
void UninitItem(void);	// �E�F�[�u�̏I������
void UpdateItem(void);	// �E�F�[�u�̍X�V����
void DrawItem(void);	// �E�F�[�u�̕`�揈��
void SetItem(ITEM_STATE itemtype,D3DXVECTOR3 pos);			// �E�F�[�u�̐ݒ菈��
ITEM* GetItem(void);	// �E�F�[�u���̎擾����