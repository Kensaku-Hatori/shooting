#ifndef _SCORE_H_
//==============
// �}�N����`
//==============
#define _SCORE_H_

#include"main.h"

//======================
// �v���g�^�C�v�錾
//======================
// �X�R�A�̏���������
void Initscore(void);
// �X�R�A�̏I������
void Uninitscore(void);
// �X�R�A�̍X�V����
void Updatescore(void);
// �X�R�A�̕`�揈��
void Drawscore(void);
// �X�R�A�̐ݒ菈��
void Setscore(int score);
// �X�R�A�̉��Z����
void Addscore(int nvalue);
// �X�R�A�̌����𐔂��鏈��
int score(int score);
#endif