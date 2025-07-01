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
	int no;//ナンバー
	int state;//状態
	int texstate;//テクスチャの状態
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		vel;	//速度ベクトル
	bool use;//そのエネミーが使われているか
	int rote;//向いている方向
	HITBOX hitbox[ENEMYHITBOX];
	int xp;
	float hp;//現在体力
	float maxhp;//最大体力
	float damage;//アイテムのダメージ	
	float attackspeed;//
	float aact;//通常攻撃したときにのクールタイム
	float armor;//
	float movespeed;//
	WEAPONITEM dropitem[4];//アイテムのドロップ品
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
void AddknockBack(int taget, D3DXVECTOR2 vel);//ノックバックを与える
void enemydamage(int n, ENEMY enemy = {});//エネミーがプレイヤーを攻撃したときに使う
void clearEenemyAll();
void addeffectenemy(int n, int efeect);//effect付与


