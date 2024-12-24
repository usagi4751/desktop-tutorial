#pragma once

#define MAXOBJECT (128)
typedef struct {
	bool use;//使っているか
	D3DXVECTOR2		pos;	//位置
	D3DXVECTOR2     vel;    //ベクトル
	int component; //オブジェクトの元となる部分
	int timer;//時間計測用
	
}NAOBJECT;


void InitSkill(void);
void UninitSkill(void);
void UpdateSkill(void);
void DrawSkill(void);
void UseSkill(int n);
void EnemyUseSkill(int n, D3DXVECTOR2 enemypos);
void clearSkillAll();