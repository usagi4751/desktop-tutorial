/*==============================================================================

   頂点管理[player.h]
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

//アイテムのパラメータの構造体
typedef struct {
	std::string name;//アイテムの名前
	std::string showtext[4];//名前の下に書かれるテキスト
	int autoattack;//aaの種類
	int skill;//スキル
	int skillct;//スキルクールタイム 同じスキルがあった場合ほかのアイテムもクールタイムになる
	int count;//アイテムのカウント
	float size;//アイテムを持った時の大きさ
	int itemno;//アイテムのナンバー
	int itemtex;//アイテムのテクスチャ
	float damage;//アイテムのダメージ	
	float maxhp;//最大体力
	float range;//攻撃レンジ
	float attackspeed;//攻撃速度
	float armor;//防御力
	float movespeed;//移動速度
	int str;//ステータスのstrngth
	int dex;//ステータスのdex
	int vit;//ステータスのvit
}WEAPONITEM;

//プレイヤーのパラメータの構造体
typedef struct  {
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		oldpos;	//1フレーム前位置ベクトル
	D3DXVECTOR2		vel;	//速度ベクトル
	D3DXCOLOR		color;	//頂点カラー
	int lv;//プレイヤーのレベル
	int str;//ステータスのstrngth
	int dex;//ステータスのdex
	int vit;//ステータスのvit
	float def;
	float maxhp;
	float nowhp;
	float movespeed;//移動速度
	float totalxp;//合計xp
	float critcalrete;//会心率
	float critcaldamage;//クリダメ
	WEAPONITEM inventory[20];
	HITBOX hitbox[16];
}PLAYER;

//落ちているアイテムの構造体
typedef struct {
	WEAPONITEM  item;
	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXVECTOR2	vel;	//速度ベクトル
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
PLAYER* GetPlayerStatus();//プレイヤーのステータスの入手
PLAYER SetPlayerStatus();//プレイヤーステータスの計算
int hubna();//持っているアイテムの座標
int shopcelectna();//ショップで選択しているアイテムの番号
bool HitBoxswith();//ヒットボックスをを表示するかのboolを返す
void atack(int n);//通常攻撃
void Getitem(WEAPONITEM item);//アイテム取得
void Dropitem(D3DXVECTOR2 dppos, WEAPONITEM dpitem);
WEAPONITEM PresetItem(int n);//設定されたアイテム
void seteffect(int n);//プレイヤーへのエフェクト効果を付与する
void playerknockBack(D3DXVECTOR2 vel);
void clearPlayerAll();//すべてのドロップ品エフェクト効果AACTを消す
int getgold();
int itemselltable(int n);//売るときのテーブル
int itembuytable(int n);//買うときのねだん
WEAPONITEM shopitem(int n);
WEAPONITEM craftitemnom(int n);
int craftitemnam(int n, int s);
int craftitemcount(int n, int s);
