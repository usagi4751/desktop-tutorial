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
	bool  use;              //使っているか
	int   taget;            //誰に攻撃が当たるか
	D3DXVECTOR2		pos;	//位置
	D3DXVECTOR2		size;	//バレットサイズ
	float di;               //[方向]0～2πの方向 
	float           range;  //球の射程
	float          distance;//球の現在飛んだ距離
	float           speed;  //球の速度
	int type;               //球のタイプ
	float damage;
	float crtdamage;
}BULLET;


void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(int butaget, D3DXVECTOR2 bupos, int butype);
void clearBulletAll();