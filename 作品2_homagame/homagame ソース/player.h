/*==============================================================================

   ���_�Ǘ�[player.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#define INBENTMAX  20
#define DROPMAX 256
#define MAXEFFECT 16
#include "main.h"
#include "renderer.h"
#include "hitbox.h"
#include "map.h"
typedef struct {
	std::string name;//�A�C�e���̖��O
	std::string showtext[4];//���O�̉��ɏ������e�L�X�g
	int autoattack;//aa�̎��
	int skill;//�X�L��
	int skillct;//�X�L���N�[���^�C�� �����X�L�����������ꍇ�ق��̃A�C�e�����N�[���^�C���ɂȂ�
	int count;//�A�C�e���̃J�E���g
	float size;//�A�C�e�������������̑傫��
	int itemno;//�A�C�e���̃i���o�[
	int itemtex;//�A�C�e���̃e�N�X�`��
	float damage;//�A�C�e���̃_���[�W	
	float maxhp;//
	float range;//
	float attackspeed;//
	float armor;//
	float movespeed;//
	int str;//�X�e�[�^�X��strngth
	int dex;//�X�e�[�^�X��dex
	int vit;//�X�e�[�^�X��vit
}WEAPONITEM;

typedef struct  {
	D3DXVECTOR2		pos;	//�ʒu�x�N�g��
	D3DXVECTOR2		oldpos;	//1�t���[���O�ʒu�x�N�g��
	D3DXVECTOR2		vel;	//���x�x�N�g��
	D3DXCOLOR		color;	//���_�J���[
	int lv;
	int str;//�X�e�[�^�X��strngth
	int dex;//�X�e�[�^�X��dex
	int vit;//�X�e�[�^�X��vit
	float def;
	float maxhp;
	float nowhp;
	float movespeed;//�ړ����x
	float totalxp;//���vxp
	float critcalrete;//��S��
	float critcaldamage;//�N���_��
	WEAPONITEM inventory[20];
	HITBOX hitbox[16];
}PLAYER;

typedef struct {
	WEAPONITEM  item;
	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
	D3DXVECTOR2	vel;	//���x�x�N�g��
	int         droptime;
	bool use;
    
}DROPITEM;
enum {
	HOM_WOOD_WAND = 1,
	HOM_IRON_SWORD,
	HOM_ROD,
	HOM_SLIMEGEL,
	HOM_LEATHERHELMET,
};
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER* GetPlayerStatus();
PLAYER SetPlayerStatus();
int hubna();//�����Ă���A�C�e���̍��W
int shopcelectna();//�V���b�v�őI�����Ă���A�C�e���̔ԍ�
bool HitBoxswith();
void atack(int n);//�ʏ�U��
void Getitem(WEAPONITEM item);//�A�C�e���擾
void Dropitem(D3DXVECTOR2 dppos, WEAPONITEM dpitem);
WEAPONITEM PresetItem(int n);//�ݒ肳�ꂽ�A�C�e��
void seteffect(int n);//�v���C���[�ւ̃G�t�F�N�g���ʂ�t�^����
void playerknockBack(D3DXVECTOR2 vel);
void clearPlayerAll();//���ׂẴh���b�v�i�G�t�F�N�g����AACT������
int getgold();
int itemselltable(int n);//����Ƃ��̃e�[�u��
int itembuytable(int n);//�����Ƃ��̂˂���
WEAPONITEM shopitem(int n);
WEAPONITEM craftitemnom(int n);
int craftitemnam(int n, int s);
int craftitemcount(int n, int s);
