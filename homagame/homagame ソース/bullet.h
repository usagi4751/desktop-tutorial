#pragma once
#include "polygon.h"
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "particle.h"
#include "main.h"
#include <math.h>
#include "winuser.h"
#include "enemy.h"
#include "player.h"
#include "sound.h"
#define MAXBULLET  128
typedef struct {
	bool  use;              //�g���Ă��邩
	int   taget;            //�N�ɍU���������邩
	D3DXVECTOR2		pos;	//�ʒu
	D3DXVECTOR2		size;	//�o���b�g�T�C�Y
	float di;               //[����]0�`2�΂̕��� 
	float           range;  //���̎˒�
	float          distance;//���̌��ݔ�񂾋���
	float           speed;  //���̑��x
	int type;               //���̃^�C�v
	float damage;
	float crtdamage;
}BULLET;


void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(int butaget, D3DXVECTOR2 bupos, int butype);
void clearBulletAll();