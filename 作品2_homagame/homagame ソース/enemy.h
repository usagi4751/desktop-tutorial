//=======================================================
// enemy.h
// 
//=======================================================
#pragma once

#define MAXENEMY 128
#define ENEMYHITBOX 16
#include "hitbox.h"
#include "player.h"
typedef struct {
	int no;//�i���o�[
	int state;//���
	int texstate;//�e�N�X�`���̏��
	D3DXVECTOR2		pos;	//�ʒu�x�N�g��
	D3DXVECTOR2		vel;	//���x�x�N�g��
	bool use;//���̃G�l�~�[���g���Ă��邩
	int rote;//�����Ă������
	HITBOX hitbox[ENEMYHITBOX];
	int xp;
	float hp;//���ݑ̗�
	float maxhp;//�ő�̗�
	float damage;//�A�C�e���̃_���[�W	
	float attackspeed;//
	float aact;//�ʏ�U�������Ƃ��ɂ̃N�[���^�C��
	float armor;//
	float movespeed;//
	WEAPONITEM dropitem[4];//�A�C�e���̃h���b�v�i
	float droprate[4];
	int slowness;
}ENEMY;


void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY GetEnemy(int n);
void AddDamageenemy(int n, float damage);
void PresetEnemy(int n, D3DXVECTOR2 pos);
void AddknockBack(int taget, D3DXVECTOR2 vel);//�m�b�N�o�b�N��^����
void enemydamage(int n, ENEMY enemy = {});//�G�l�~�[���v���C���[���U�������Ƃ��Ɏg��
void clearEenemyAll();
void addeffectenemy(int n, int efeect);//effect�t�^


