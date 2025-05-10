#pragma once

#define MAXOBJECT (128)
typedef struct {
	bool use;//�g���Ă��邩
	D3DXVECTOR2		pos;	//�ʒu
	D3DXVECTOR2     vel;    //�x�N�g��
	int component; //�I�u�W�F�N�g�̌��ƂȂ镔��
	int timer;//���Ԍv���p
	
}NAOBJECT;


void InitSkill(void);
void UninitSkill(void);
void UpdateSkill(void);
void DrawSkill(void);
void UseSkill(int n);
void EnemyUseSkill(int n, D3DXVECTOR2 enemypos);
void clearSkillAll();