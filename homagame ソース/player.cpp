/*==============================================================================

   頂点管理 [player.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygon.h"
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "particle.h"
#include "main.h"
#include <math.h>
#include "winuser.h"
#include "player.h"
#include "sound.h"
#include "bullet.h"
#include "skill.h"

PLAYER player;
int tic = 0;//スロウのパーティクル作成のために作成
static int g_music[16] = {};
int gbbufficon = 0;
int g_TexNo  = 0;
int helmet[1] = {};
int aact = 0;
int aacttimr = 1;
int inventslot = 0;
int itemhavena = -1;
int shopcelectitemna = -1;
int junpcount = 0;
bool hitboxsw = false;
WEAPONITEM dummy = {};
DROPITEM dropitem[DROPMAX] = {};
int dgui3 = 0;
//プレイヤーの状態
//0: スロウ状態
//1: 移動速度増加
//2: 体力増強
//3: スロウ耐性
//4: ノックバック耐性
//5: クリティカル率増加
//6: クリティカルダメージ増加
//7: 防御力増加
//8: HP自動回復
//9: STR増加
//10: なし
//11: なし
//12: なし
//13: なし
//14: なし
//15: なし
int playereffect[MAXEFFECT] = {};
//プレイヤーの金
int gold = 0;
//バフアイコン
int bufficon[16] = {};
//レベルアップの描画タイマー
int lvuptext = 150;
//1フレーム前のレベル
int oldlv;
void InitPlayer(void) {
	g_music[0] = LoadSound((char*)"data/SOUND/sweep.wav");
	g_music[1] = LoadSound((char*)"data/SOUND/button.wav");
	g_music[2] = LoadSound((char*)"data/SOUND/click.wav");
	g_music[3] = LoadSound((char*)"data/SOUND/inventclick.wav");
	g_music[4] = LoadSound((char*)"data/SOUND/spellsound.wav");
	g_music[5] = LoadSound((char*)"data/SOUND/stageclrear.wav");
	g_music[6] = LoadSound((char*)"data/SOUND/stageload.wav");
	g_music[7] = LoadSound((char*)"data/SOUND/summon1.wav");
	g_music[8] = LoadSound((char*)"data/SOUND/walk.wav");
	g_music[9] = LoadSound((char*)"data/SOUND/tp.wav");
	g_music[10] = LoadSound((char*)"data/SOUND/spallcast.wav");
	g_music[11] = LoadSound((char*)"data/SOUND/pikopikobino.wav");
	g_music[12] = LoadSound((char*)"data/SOUND/morinoyoukan.wav");
	g_music[13] = LoadSound((char*)"data/SOUND/akuma.wav");
	g_music[14] = LoadSound((char*)"data/SOUND/sweeep.wav");
	g_TexNo = LoadTexture((char*)"data/TEXTURE/homa6.png");
	dgui3 = LoadTexture((char*)"data/TEXTURE/gui3.png");
	helmet[0] = LoadTexture((char*)"data/TEXTURE/leatherhelmet.png");
	gbbufficon = LoadTexture((char*)"data/TEXTURE/buffwaku.png");
	bufficon[0] = LoadTexture((char*)"data/TEXTURE/slowwness.png");
	bufficon[1] = LoadTexture((char*)"data/TEXTURE/speed.png");
	bufficon[2] = LoadTexture((char*)"data/TEXTURE/hpboost.png");
	bufficon[3] = LoadTexture((char*)"data/TEXTURE/slowresist.png");
	bufficon[4] = LoadTexture((char*)"data/TEXTURE/knockbackrest.png");
	bufficon[5] = LoadTexture((char*)"data/TEXTURE/critup.png");
	bufficon[6] = LoadTexture((char*)"data/TEXTURE/critdamagebuff.png");
	bufficon[7] = LoadTexture((char*)"data/TEXTURE/defbuff.png");
	bufficon[8] = LoadTexture((char*)"data/TEXTURE/potion.png");
	bufficon[9] = LoadTexture((char*)"data/TEXTURE/potion5.png");
	
	player.oldpos = player.pos = { 600,800 };
	player.vel = { 0,0 };
	for (int i = 0; i < INBENTMAX; i++)
	{
		player.inventory[i] = {};
		player.inventory[i].autoattack = 1;
		player.inventory[i].attackspeed = 0;
	}
	for (int i = 0; i < 16; i++)
	{
		player.hitbox[i].pos = { 0,0 };
		player.hitbox[i].size = { 0,0 };
		player.hitbox[i].type = 0;
		player.hitbox[i].use = false;
	}
	player.totalxp = 0;
	player.movespeed = 1.0f;
	player.color = { 1.0f,1.0f ,1.0f ,1.0f };
	player = SetPlayerStatus();
	player.nowhp = player.maxhp;
	player.hitbox[0].pos = { 0,0 };
	player.hitbox[0].size = { 100,100 };
	player.hitbox[0].type = 0;
	player.hitbox[0].use = true;
	oldlv =0;



		player.inventory[0] = PresetItem(1);
	
	


	
}
void UninitPlayer(void) {

}
void UpdatePlayer(void) {
	tic++;
	D3DXVECTOR2 camera = Getcamera();
	D3DXVECTOR2 corsor = Getcorsor();
	D3DXVECTOR2 nowcorsor = GetNowcorsor();
	bool inventopen = gettabopen();
	bool shopopen = shopbopen();
	player = SetPlayerStatus();
	if (oldlv != player.lv)
	{
		lvuptext = 0;
	}
	oldlv = player.lv;
	if (playereffect[8]  > 0 && playereffect[8] % 15 == 0)
	{
		player.nowhp +=  0.25f / 4.0f;
	}
	lvuptext++;

	player.vel.y += 1.0f;
	player.pos.y += player.vel.y;
	player.pos.x += player.vel.x;
	if (player.vel.x != 0)
	{
		player.vel.x *= 0.98f;
		if (playereffect[4] > 0)
		{
			player.vel.x *= 0.98f;
		}
	}if (player.vel.x != 0 && (player.vel.x < 0.01 && player.vel.x > -0.01))
	{
		player.vel.x = 0;
	}
	for (int i = 0; i < INBENTMAX; i++)
	{//インベントリのが空だった場合aaを設定する
		if (player.inventory[i].itemno == 0)
		{
			player.inventory[i].autoattack = 1;
		}
		if (player.inventory[i].skillct  > 0)
		{
			player.inventory[i].skillct--;	
		}
	}
	for (int i = 0; i < DROPMAX; i++)
	{
		//アイテムドロップ
		if (dropitem[i].use == true) {
			dropitem[i].droptime++;
			dropitem[i].pos.y -= dropitem[i].vel.y;
			dropitem[i].pos.x -= dropitem[i].vel.x;
			if (dropitem[i].pos.y < 840)
			{
				dropitem[i].vel.y -= +0.5f;
			}
			if (dropitem[i].vel.y < -10 )
			{
				dropitem[i].vel.y = -10.0f;
			}
			if (dropitem[i].pos.y > 840)
			{
				dropitem[i].pos.y = 840;
				dropitem[i].vel.y = 0.0f;
				dropitem[i].vel.x = 0.0f;
			}
			if (player.pos.x + 20 > dropitem[i].pos.x && 
				player.pos.x - 20 < dropitem[i].pos.x && 
				player.pos.y + 80 > dropitem[i].pos.y &&
				player.pos.y - 80 < dropitem[i].pos.y &&
				dropitem[i].droptime > 90)
			{
				if (player.pos.x  < dropitem[i].pos.x)
				{
					dropitem[i].pos.x -= 3.0f;
				}
				else
				{
					dropitem[i].pos.x += 3.0f;
				}
			}
			if (player.pos.x + 10 > dropitem[i].pos.x &&
				player.pos.x - 10 < dropitem[i].pos.x &&
				player.pos.y + 50 > dropitem[i].pos.y &&
				player.pos.y - 50 < dropitem[i].pos.y &&
				dropitem[i].droptime > 90)
			{
				Getitem(dropitem[i].item);
				dropitem[i].use = false;
			}
		}
	}
	//ジャンプ
	if (player.pos.y > 800.0f)
	{
		player.vel.y = 0.0f;
		player.pos.y = 800.0f;
		junpcount = 1 ;
	}
	if (GetKeyboardTrigger(DIK_SPACE) && junpcount  > 0&& gettabopen() ==false && shopopen == false && *craftpopen() == false)
	{
		junpcount--;
		player.vel.y = -20.0f;
		PlaySound(g_music[0], 0);
		SetVolume(g_music[0], 0.1f);
	}
	//エフェクト更新処理
	for (int i = 0; i < MAXEFFECT; i++)
	{
		if (playereffect[i] > 0)
		{
			playereffect[i]--;
		}
		if (playereffect[i] < 0)
		{
			playereffect[i] = 0;
		}
	}
	if (playereffect[0] > 0 && tic % 20 == 0)
	{
		setparticle(
			3,
			player.pos.x, player.pos.y - 100,
			12.0f, 50.0f,
			0.6f, 1, 25,
			0.5f, 0.0f,
			0.05f, 0.0f,
			1.1f, 0.3f,
			0.0f, 0.0f,
			0.2f, 0.2f, 0.8f);
	}
	//移動
	if (GetKeyboardPress(DIK_D) && gettabopen() == false && shopopen == false && *craftpopen() == false && pGetportal()->open == false)
	{
		if (player.movespeed * 0.01f > 0)
		{
			player.pos.x += 1.5f * player.movespeed * 0.01f;
		}
		
	} 
	if (GetKeyboardPress(DIK_A) && gettabopen() == false && shopopen == false && *craftpopen() == false && pGetportal()->open == false)
	{
		if (player.movespeed * 0.01f > 0)
		{
			player.pos.x -= 1.5f * player.movespeed * 0.01f;
		}
	
	}

	
	if (GetKeyboardPress(DIK_RIGHT) && gettabopen() == false && *craftpopen() == false && pGetportal()->open == false)
	{

		player.pos.x += 0.05f;
	}
	if (GetKeyboardPress(DIK_LEFT) && gettabopen() == false && *craftpopen() == false && pGetportal()->open == false)
	{

		player.pos.x -= 0.05f;
	}
	if (GetKeyboardTrigger  (DIK_F11) )
	{

		hitboxsw = !hitboxsw;
	}
	if (inventopen == false && itemhavena > -1)
	{
		player.inventory[itemhavena] = dummy;
		dummy = {};
		itemhavena = -1;
		GetItem({});
	}
	//ショップのアイテム選択
	if (IsMouseLeftTriggered() && shopopen == true && *craftpopen() == false && pGetportal()->open == false)
	{

		PlaySound(3, 0);
		SetVolume(3, 0.1f);
		if (*shopmoder() == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				for (int h = 0; h < 3; h++)
				{

					if (nowcorsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && nowcorsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&
						nowcorsor.y >  310.0f + 140.0f * h - 60 && nowcorsor.y < 310.0f + 140.0f * h + 60)
					{
						shopcelectitemna = player.inventory[5 * h + i + 5].itemno;
						if (player.inventory[5 * h + i + 5].itemno < 1)
						{
							shopcelectitemna = -1;
						}
					}

				}
				if (nowcorsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && nowcorsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&
					nowcorsor.y >  810.0f - 60 && nowcorsor.y < 810.0f + 60)
				{
					shopcelectitemna = player.inventory[i].itemno;
					if (player.inventory[i].itemno < 1)
					{
						shopcelectitemna = -1;
					}
				}

			}
			if (nowcorsor.x > 1650 - 150 && nowcorsor.x < 1650 + 150 &&
				nowcorsor.y >  800 - 50 && nowcorsor.y < 800 + 50)
			{
				//選択しているアイテムがあった場合数を減らし

				for (int g = 0; g < INBENTMAX; g++)
				{
					if (player.inventory[g].itemno == shopcelectitemna && shopcelectitemna != 7)
					{
						player.inventory[g].count--;
						gold += itemselltable(shopcelectitemna);
						//０個になった場合消す
						if (player.inventory[g].count <= 0)
						{
							player.inventory[g] = {};
						}
						break;
					}

				}
			}
			
		}
		if (*shopmoder() == 1)
		{
			if (nowcorsor.x > 1284 - 30 && nowcorsor.x < 1284 + 30 &&
				nowcorsor.y >  870 - 40 && nowcorsor.y < 870 + 40 && *shopppage() > 0)
			{
				*shopppage() -= 1;
				*shoppclect() = -1;
			}
			if (nowcorsor.x > 1348 - 30 && nowcorsor.x < 1348 + 30 &&
				nowcorsor.y >  870 - 40 && nowcorsor.y < 870 + 40)
			{
				*shopppage() += 1;
				*shoppclect() = -1;

			}
			for (int r = 0; r < 4; r++)
			{
				if (nowcorsor.x > 900 - 440 && nowcorsor.x < 900 + 440 &&
					nowcorsor.y >   390 + r * 120 - 58 && nowcorsor.y < 390 + r * 120 + 58 ) 
				{
					*shoppclect() = r ;
					if (shopitem(*shoppclect() + 4 * *shopppage()).itemno < 1)
					{
						*shoppclect() = -1;
					}
				}
			
			}
			if (nowcorsor.x > 1630 - 150 && nowcorsor.x < 1630 + 150 &&
				nowcorsor.y >  850 - 60 && nowcorsor.y < 850 + 60 && shopitem(*shoppclect() + 4 * *shopppage()).itemno > 0 &&
				itembuytable(shopitem(*shoppclect() + 4 * *shopppage()).itemno) < gold)
			{

				Getitem(shopitem(*shoppclect() + 4 * *shopppage()));
				gold -= itembuytable(shopitem(*shoppclect() + 4 * *shopppage()).itemno);
			}
		}
		if (nowcorsor.x > 730 - 150 && nowcorsor.x < 730 + 150 &&
			nowcorsor.y >  150 - 60 && nowcorsor.y < 150 + 60)
		{
			int* buymode = shopmoder();
			*buymode = 1;
			*shopppage() = 0;
		}
		if (nowcorsor.x > 1030 - 150 && nowcorsor.x < 1030 + 150 &&
			nowcorsor.y >  150 - 60 && nowcorsor.y < 150 + 60)
		{
			int* buymode = shopmoder();
			*buymode = 0;
		}

	}//通常攻撃　: 左クリック
	//インベントリ移動
	if (IsMouseLeftTriggered() && inventopen == true && *craftpopen() == false && pGetportal()->open == false)
	{
		PlaySound(3, 0);
		SetVolume(3, 0.1f);
		for (int i = 0; i < 5; i++)
		{
			for (int h = 0; h < 3; h++)
			{

				//インベントリ移動
				if (nowcorsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && nowcorsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&
					nowcorsor.y >  310.0f + 140.0f * h - 60 && nowcorsor.y < 310.0f + 140.0f * h + 60)
				{
					while (1)
					{
						if (itemhavena == -1)
						{
							GetItem(player.inventory[5 * h + i + 5]);
							dummy = player.inventory[5 * h + i + 5];
							player.inventory[5 * h + i + 5] = {};
							itemhavena = 5 * h + i + 5;
							break;
						}
						if (itemhavena > -1)
						{
							player.inventory[itemhavena] = player.inventory[5 * h + i + 5];
							
							
							player.inventory[5 * h + i + 5] = dummy;
							dummy = {};
							itemhavena = -1;
							GetItem({});
							break;
						}
					}
					
				
				}

			}

			if (nowcorsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && nowcorsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&
				nowcorsor.y >  810.0f - 60 && nowcorsor.y < 810.0f + 60)
			{
				//インベントリ移動
				while (true)
				{
					if (itemhavena == -1)
					{
						GetItem(player.inventory[i]);
						dummy = player.inventory[i];
						player.inventory[i] = {};
						itemhavena = i;
						break;
					}
					if (itemhavena > -1)
					{
						player.inventory[itemhavena] = player.inventory[i];


						player.inventory[i] = dummy;
						dummy = {};
						itemhavena = -1;
						GetItem({});
						break;
					}
				}
			}
			
		}
		//アイテムをインベントリの外にするとアイテムを捨てる
		if ((nowcorsor.x < SCREEN_WIDTH * 0.5f - 400 ||nowcorsor.x > SCREEN_WIDTH * 0.5f + 400||
			nowcorsor.y < 450.0f - 250.0f|| nowcorsor.y > 810.0f + 100.0f)&& itemhavena > -1)
		{
			Dropitem(player.pos,dummy);
			dummy = {};
			itemhavena = -1;
			GetItem({});
		}
	}//通常攻撃　: 左クリック
	//クラフト
	if (IsMouseLeftTriggered() && shopopen == false && *craftpopen() == true && pGetportal()->open == false)
	{
		//ページマイナス
		if (nowcorsor.x > 300 - 60 && nowcorsor.x < 300 + 60 &&
			nowcorsor.y >  900 - 40 && nowcorsor.y < 900 + 40)
		{
			*craftppage() -= 1;
		}
		//ページプラス
		if (nowcorsor.x > 700 - 60 && nowcorsor.x < 700 + 60 &&
			nowcorsor.y >  900 - 40 && nowcorsor.y < 900 + 40)
		{
			*craftppage() += 1;
		}
		if (*craftppage() < 0)
		{
			*craftppage() = 0;
		}
		//アイテムセレクト
		for (int r = 0; r < 6; r++)
		{
			if (nowcorsor.x > 500 - 380 && nowcorsor.x < 500 + 380 &&
				nowcorsor.y >   190 + r * 120 - 58 && nowcorsor.y < 190 + r * 120 + 58)
			{
				*craftpcelct() = *craftppage() * 6 + r;
			}
		}
		//必要アイテムがあった場合アイテムが作れる
		bool craftflag[4] = { false,false ,false ,false };
		for (int i = 0; i < 4; i++)
		{
			if (craftitemnam(*craftpcelct(), i) > -1 && craftitemcount(*craftpcelct(), i) > -1)
			{
				int hubitem = 0;
				for (int j = 0; j < INBENTMAX; j++)
				{
					if (player.inventory[j].itemno > 0 && player.inventory[j].itemno == craftitemnam(*craftpcelct(), i))
					{
						hubitem += player.inventory[j].count;
					}

				}
				if (craftitemcount(*craftpcelct(), i) <= hubitem)
				{
					craftflag[i] = true;
				}
			}
			if (craftitemnam(*craftpcelct(), i) < 0)
			{
				craftflag[i] = true;
			}
		}

		if (craftflag[0] == true && craftflag[1] == true&& craftflag[2] == true&& craftflag[3] == true&&
			nowcorsor.x > 1450 - 400 && nowcorsor.x < 1450 + 400 &&
			nowcorsor.y >  935 - 70 && nowcorsor.y < 935 + 70 && craftitemnom(*craftpcelct()).itemno > 0
			)
		{
			WEAPONITEM craftitemudummy = craftitemnom(*craftpcelct());
			for (int i = 0; i < 4; i++)
			{
				if (frand() < 0.25)
				{
					switch ((int)(frand() * 6))
					{
					case 0:craftitemudummy.armor += 2;
						break;
					case 1:craftitemudummy.dex += 1;
						break;
					case 2:craftitemudummy.maxhp += 3;
						break;
					case 3:craftitemudummy.movespeed += 1;
						break;
					case 4:craftitemudummy.str += 1;
						break;
					case 5:craftitemudummy.vit += 1;
						break;
					default:
						break;
					}
				}
			}
			Getitem(craftitemudummy);
			for (int k = 0; k < 4;k++)
			{
				for (int j = 0; j < INBENTMAX; j++)
				{
					if (player.inventory[j].itemno > 0 && player.inventory[j].itemno == craftitemnam(*craftpcelct(),k))
					{
						player.inventory[j].count -= craftitemcount(*craftpcelct(), k);
						if (player.inventory[j].count < 1)
						{
							player.inventory[j] = {};
						}
						break;
					}
				}
			}
		}
	}
	//ポータル
	if (IsMouseLeftTriggered() && pGetportal()->open == true && shopopen == false)
	{
		if (nowcorsor.x > 1600 - 25 && nowcorsor.x < 1600 + 25 &&
			nowcorsor.y >  750 - 100 && nowcorsor.y < 750 + 100 && pGetportal()->page < 1)
		{
			pGetportal()->page = 1;
		
		}
		if (nowcorsor.x > 1600 - 25 && nowcorsor.x < 1600 + 25 &&
			nowcorsor.y >  350 - 100 && nowcorsor.y < 350 + 100 && pGetportal()->page > 0)
		{
			pGetportal()->page = 0;
			
		}
		for (int i = 0; i < 5; i++)
		{
			if (nowcorsor.x > 1250 - 300 && nowcorsor.x < 1250 + 300 &&
				nowcorsor.y > i * 150 - 70 + 250 && nowcorsor.y < i * 150 + 70 + 250 && Getstageflag(pGetportal()->dangionselect + pGetportal()->dangionpage * 4, pGetportal()->page * 5 + i) > -1)
			{
				Setmap((pGetportal()->dangionselect + pGetportal()->dangionpage * 4)*10 + pGetportal()->page * 5 + i + 1);
				pGetportal()->open = false;
			}
		}
	}
	//通常攻撃
	if (IsMouseLeftTriggered() && inventopen == false && aact == 0 && shopopen == false && *craftpopen() == false && pGetportal()->open == false)
	{

	
		PlaySound(14, 0);
		if ((int)player.inventory[haveitem()].attackspeed == 0)
		{
			aact += (int)(6000.0f / 100.0f);
			aacttimr = (int)(6000.0f / 100.0f);
		}
		else
		{
		aact += (int)(6000 / (player.inventory[haveitem()].attackspeed * (1.0f + (player.dex * 0.01f))));
     	aacttimr = (int)(6000 / (player.inventory[haveitem()].attackspeed * (1.0f + (player.dex * 0.01f))));
		}
		atack(player.inventory[haveitem()].autoattack);
	

	}
	//右クリック ::スキル
	if (IsMouseRightTriggered() && inventopen == false && player.inventory[haveitem()].skillct <= 0 && shopopen == false && *craftpopen() == false && pGetportal()->open == false)
	{
		UseSkill(player.inventory[haveitem()].skill);
		for (int i = 0; i < INBENTMAX; i++)
		{

		}
		player.inventory[haveitem()].skillct = Getskillct(player.inventory[haveitem()].skill);
	}
	//右クリック ::ポーションなどの消耗品
	if (IsMouseRightTriggered() && inventopen == false&& shopopen == false && *craftpopen() == false &&
		((player.inventory[haveitem()].itemno >=  8 && player.inventory[haveitem()].itemno <= 13 )||player.inventory[haveitem()].itemno == 31) && pGetportal()->open == false)
	{
		
		switch (player.inventory[haveitem()].itemno)
		{
		case 8:
			player.nowhp += 6;
			break;
		case 9:player.nowhp += 10;
			break;
		case 10:player.nowhp += 18;
			break;
		case 11:player.nowhp += 35;
			break;
		case 12:seteffect(10);
			break;
		case 13:seteffect(11);
			break;
		case 31:
			switch ((int)(frand() * 10))
			{
			case 0:Getitem(PresetItem(20));
				break;
			case 1:Getitem(PresetItem(21));
				break;
			case 2:Getitem(PresetItem(22));
				break;
			case 3:Getitem(PresetItem(23));
				break;
			case 4:Getitem(PresetItem(23));
				break;
			case 5:Getitem(PresetItem(32));
				break;
			case 6:Getitem(PresetItem(33));
				break;
			case 7:Getitem(PresetItem(33));
				break;
			case 8:Getitem(PresetItem(33));
				break;
			case 9:Getitem(PresetItem(33));
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		player.inventory[haveitem()] = {};
	}



	if (aact > 0)
	{
		aact -= 1;
	}
	if (aact < 0)
	{
		aact = 0;
	}
	if (player.pos.x < 0)
	{
		player.pos.x = 0.0f;
	}
	if (player.pos.x > GetmapMaxXpos())
	{
		player.pos.x = GetmapMaxXpos();
	}
	if (player.nowhp > player.maxhp)
	{
		player.nowhp = player.maxhp;
	}
	if (GetKeyboardPress(DIK_H) && GetKeyboardPress(DIK_A) && GetKeyboardPress(DIK_N) && GetKeyboardPress(DIK_Y) && GetKeyboardPress(DIK_M))
	{
		player.inventory[0] = PresetItem(1);
		player.inventory[1] = PresetItem(2);
		player.inventory[3] = PresetItem(7);
		player.inventory[3].skill = 1;
		player.inventory[4] = PresetItem(7);
		player.inventory[4].skill = 7;
		player.inventory[5] = PresetItem(7);
		player.inventory[5].skill = 9;

		player.inventory[6] = PresetItem(31);
		player.inventory[7] = PresetItem(25);
		player.inventory[8] = PresetItem(21);
		player.inventory[9] = PresetItem(12);
		player.inventory[10] = PresetItem(13);
		player.inventory[11] = PresetItem(5);
	}
}
void DrawPlayer(void) {

	D3DXVECTOR2 camera = Getcamera();
	D3DXVECTOR2 corsor = Getcorsor();
	int plhaveitem;//現在持っているアイテム
	plhaveitem = haveitem();

	//プレイヤーの描画
	if (lvuptext < 150)
	{
		SetText("LV UP", (SCREEN_WIDTH * 0.5f + camera.x * 1500.0f) - (corsor.x - (SCREEN_WIDTH * 0.5f + camera.x * 1500.0f)) * 0.1f - 50, player.pos.y -200 -lvuptext * 0.5f, 40, 1.0f, 1.0f, 1.0f, 1.0f, 1);
	}
	
	DrawSpriteColorRotate(g_TexNo,
		(SCREEN_WIDTH * 0.5f + camera.x * 1500.0f) - (corsor.x - (SCREEN_WIDTH * 0.5f + camera.x * 1500.0f)) * 0.1f, player.pos.y,
		100.0f, 100.0f,
		0.0f / 3, 0.0f / 2,
		1.0f / 3, 1.0f / 2,
		player.color.r, player.color.g, player.color.b, player.color.a,
		0);
	//プレイヤーの装備品の描画
	if (player.inventory[8].itemno ==HOM_LEATHERHELMET)
	{
		DrawSpriteColorRotate(helmet[0],
			(SCREEN_WIDTH * 0.5f + camera.x * 1500.0f) - (corsor.x - (SCREEN_WIDTH * 0.5f + camera.x * 1500.0f)) * 0.1f, player.pos.y - 37,
			100.0f, 100.0f,
			0.0f, 0.0f,
			1.0f , 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0);
	}
	//ドロップしているアイテム表示
	for (int i = 0; i < DROPMAX; i++)
	{
		if (dropitem[i].use == true)
		{
			DrawSpriteColorRotate(GetItemtex(dropitem[i].item.itemtex-1),
				SCREEN_WIDTH * 0.5f + (dropitem[i].pos.x - player.pos.x) * 4.7f - (corsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + camera.x * 1650, dropitem[i].pos.y - 35.0f,
				75, 75,
				0.0f, 0.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0);
		}
	}
	if (player.inventory[plhaveitem].itemno > 0)
	{
		int dir = 0;
		if ((SCREEN_WIDTH * 0.5f + camera.x * 1500.0f) - (corsor.x - (SCREEN_WIDTH * 0.5f + camera.x * 1500.0f)) * 0.1f > corsor.x)
		dir = 0;
		else
		dir = -1;
		DrawSpriteColorRotateAxis(GetItemtex(player.inventory[plhaveitem].itemtex - 1),
			(SCREEN_WIDTH * 0.5f + camera.x * 1500.0f) - (corsor.x - (SCREEN_WIDTH * 0.5f + camera.x * 1500.0f)) * 0.1f - 40 - player.inventory[plhaveitem].size - dir * (player.inventory[plhaveitem].size + 80) + player.inventory[plhaveitem].size * 0.5f, player.pos.y - 20 - player.inventory[plhaveitem].size * 0.5f,
			player.inventory[plhaveitem].size, player.inventory[plhaveitem].size,
			player.inventory[plhaveitem].size * 0.5f+ player.inventory[plhaveitem].size * (float)dir, player.inventory[plhaveitem].size * 0.5f,
			(float)(dir * -1), 0,
			1.0f + dir * 2, 1.0f,
			player.color.r, player.color.g, player.color.b, player.color.a,
			(float)((float)aact / (float)aacttimr) * -(dir * 2 + 1));
	}
	int sw = 0;
	for (int i = 0; i < MAXEFFECT; i++)
	{
		if (playereffect[i] > 0)
		{
			DrawSprite(gbbufficon,
				1885 - sw * 70, 35,
				70, 70,
				1.0f, 1.0f, 1.0f, 1.0f);
			DrawSprite(bufficon[i],
				1885-sw*70,35,
				60, 60,
				1.0f, 1.0f, 1.0f, 1.0f);
			SetText(std::to_string((int)(playereffect[i] / 60)), 1885 - sw * 70, 15, 20, 1.0f, 1.0f, 1.0f, 1.0f,1);
			sw++;
		}
	}

}

PLAYER* GetPlayerStatus() {

	return &player;
}
PLAYER SetPlayerStatus() {
	//=========================================
	// 経験値テーブル
	//
	//=========================================
	PLAYER playerstatus;
	float xptable[10] = {5, 12,25,50,85,140,250,350,450,600};
	int nowlv = 0;
	for (int i = 0; i < 10; i++)
	{
		//xptablよりplayerのxpが低かった場合レベルが決定される
		if (player.totalxp < xptable[i]) {
			playerstatus.lv = i;
			nowlv = i;
			break;
		}
	}
	int itematk = 0;
	int itemdex = 0;
	int itemvit = 0;
	float itemhp = 0.0f;
	float itemdef = 0.0f;
	float itemmove = 0.0f;
	if (player.inventory[9].itemno > 15 && player.inventory[9].itemno < 24 )
	{
		itematk += player.inventory[9].str;
		itemdex += player.inventory[9].dex;
		itemvit += player.inventory[9].vit;
		itemhp += player.inventory[9].maxhp;
		itemdef += player.inventory[9].armor;
		itemmove += player.inventory[9].movespeed;
	}
	if (player.inventory[8].itemno > 23 && player.inventory[8].itemno < 28)
	{
		itematk += player.inventory[8].str;
		itemdex += player.inventory[8].dex;
		itemvit += player.inventory[8].vit;
		itemhp += player.inventory[8].maxhp;
		itemdef += player.inventory[8].armor;
		itemmove += player.inventory[8].movespeed;
	}
	float slowness = 0;
	if (playereffect[0] > 0)
	{
		if (slowness < 0.4f)
		{
			slowness = 0.4f;
		}
	}
	if (playereffect[3] > 0)
	{
		slowness *= 0.5f;
	}

	playerstatus.str = player.inventory[haveitem()].str + itematk;
	playerstatus.dex = player.inventory[haveitem()].dex + itemdex;
	playerstatus.vit = player.inventory[haveitem()].vit + itemvit;
	playerstatus.maxhp = nowlv * 6 + player.inventory[haveitem()].maxhp + 20 + itemhp;
	playerstatus.def = 1 + nowlv * 1 + player.inventory[haveitem()].armor + itemdef;
	playerstatus.movespeed = (100.0f + player.inventory[haveitem()].movespeed + itemmove)*(1.0f - slowness);
	playerstatus.critcalrete = player.dex * 1.6f;
	if (playereffect[9] > 0)
	{
		playerstatus.str += 20;
	}
	if (playereffect[5] > 0)
	{
		playerstatus.critcalrete += 30;
	}
	if (playereffect[7] > 0)
	{
		playerstatus.def *= 1.3f;
	}
	if (playerstatus.critcalrete > 100)
	{
		playerstatus.critcalrete = 100.0f;
	}
	if (playerstatus.critcalrete < 0)
	{
		playerstatus.critcalrete = 0.0f;
	}
	if (playereffect[1] > 0)
	{
		playerstatus.movespeed *= 1.3f;
	}
	if (playereffect[2] > 0)
	{
		playerstatus.maxhp *= 1.3f;
		playerstatus.maxhp += nowlv * 6;
	}
	playerstatus.critcaldamage = 50.0f;
	if (playereffect[6] > 0)
	{
		playerstatus.critcaldamage += 25;
	}
	playerstatus.oldpos = playerstatus.pos = player.pos;
	playerstatus.vel = player.vel;
	for (int i = 0; i < INBENTMAX; i++)
	{
		playerstatus.inventory[i] = player.inventory[i];
	}
	playerstatus.nowhp = player.nowhp;
	playerstatus.totalxp = player.totalxp;

	playerstatus.color = player.color;
	for (int i = 0; i < 16; i++)
	{
		playerstatus.hitbox[i].pos = player.hitbox[i].pos;
		playerstatus.hitbox[i].size = player.hitbox[i].size;
		playerstatus.hitbox[i].use = player.hitbox[i].use;
		playerstatus.hitbox[i].type = player.hitbox[i].type;
	}

	return playerstatus;
}
int hubna() {
	return itemhavena;
}
bool HitBoxswith() {
	
	return hitboxsw;
}
void Getitem(WEAPONITEM item) {
	if (item.itemno > 0)
	{
		//スタックするアイテム
		if (item.itemno >= 14 && item.itemno <= 15 || item.itemno >= 28 && item.itemno <= 30)
		{
			bool itemloop = true;
			PlaySound(1, 0);
			SetVolume(1, 0.03f);
			while (item.count > 0 && itemloop == true)
			{
				itemloop = false;
				for (int i = 0; i < INBENTMAX; i++)
				{
					if (player.inventory[i].itemno == item.itemno && player.inventory[i].count < 99 && item.count > 0 && itemhavena != i)
					{
						itemloop = true;
						player.inventory[i].count += item.count;
						item.count = 0;
						if (player.inventory[i].count >= 100)
						{
							item.count = player.inventory[i].count - 99;
							player.inventory[i].count = 99;

						}

					}
				}
				for (int i = 0; i < INBENTMAX; i++)
				{
					if (player.inventory[i].itemno == 0 && item.count > 0 && itemhavena != i)
					{
						itemloop = true;
						player.inventory[i] = item;
						item.count = 0;
						if (player.inventory[i].count >= 100)
						{
							item.count = player.inventory[i].count - 99;
							player.inventory[i].count = 99;

						}
					}
				}
			}
		}
		//スタックしないアイテム
		if ((item.itemno >= 1 && item.itemno <= 13) ||(item.itemno >= 16 && item.itemno <= 27) || item.itemno >= 31)
		{
			bool itemloop = true;
			PlaySound(1, 0);
			SetVolume(1, 0.03f);
			while (item.count > 0 && itemloop == true)
			{
				itemloop = false;

				for (int i = 0; i < INBENTMAX; i++)
				{

					if (player.inventory[i].itemno == 0 && item.count > 0 && itemhavena != i)
					{
						itemloop = true;
						player.inventory[i] = item;
						item.count = 0;

					}
				}
			}
		}
		if (item.count > 0)
		{
			Dropitem(player.pos, item);
		}
	}
	
}
void atack(int n) {
	D3DXVECTOR2 camera = Getcamera();
	D3DXVECTOR2 corsor = Getcorsor();
	D3DXVECTOR2 nowcorsor = GetNowcorsor();
	int dir = 0;
	if ((SCREEN_WIDTH * 0.5f + camera.x * 1500.0f) - (corsor.x - (SCREEN_WIDTH * 0.5f + camera.x * 1500.0f)) * 0.1f > corsor.x)
		dir = 0;
	else
		dir = -1;
	if (n == 0)
	{
		SetBullet(1, { player.pos.x - 20 - dir * 40,player.pos.y - 40 }, 0);
	}
	if (n == 1)
	{
		SetBullet(1, { player.pos.x - 20 - dir * 40,player.pos.y - 40 }, 1);
	}

}
void Dropitem(D3DXVECTOR2 dppos , WEAPONITEM dpitem) {

	for (int i = 0; i < DROPMAX; i++)
	{
		if (dropitem[i].use == false)
		{
			dropitem[i].use = true;
			dropitem[i].item = dpitem;
			dropitem[i].pos = dppos;
			dropitem[i].droptime = 0;
			dropitem[i].vel = {frand() * 0.5f,5.0f};
			break;
		}
	}
}
WEAPONITEM PresetItem(int n) {
	WEAPONITEM retyitem = {};
	retyitem.size = 80.0f;
	retyitem.autoattack = 1;
	retyitem.count = 1;
	retyitem.range = 100;
	switch (n)
	{

	case 1:
		retyitem.itemno = 1;
		retyitem.itemtex = 10;
		retyitem.name = "short sword";
		retyitem.damage = 2.0f;
		retyitem.attackspeed = 100;
		retyitem.autoattack = 1;
		
		break;
	case 2:
		retyitem.itemno = 2;
		retyitem.itemtex =9;
		retyitem.name = "slime axe";
		retyitem.damage = 5.25f;
		retyitem.attackspeed = 66;
		retyitem.autoattack = 1;
		break;
	case 3:
		retyitem.itemno = 3;
		retyitem.itemtex = 11;
		retyitem.name = "slime sword";
		retyitem.damage = 2.6f;
		retyitem.attackspeed = 115;
		retyitem.autoattack = 1;
		break;
	case 4:
		retyitem.itemno = 4;
		retyitem.itemtex = 12;
		retyitem.name = "great axe";
		retyitem.damage = 16.0f;
		retyitem.attackspeed = 50;
		retyitem.size = 160.0f;
		retyitem.autoattack = 1;

		break;
	case 5:
		retyitem.itemno = 5;
		retyitem.itemtex = 1;
		retyitem.name = "Rigid sword";
		retyitem.damage = 6.5f;
		retyitem.attackspeed = 100;
		retyitem.autoattack = 1;
		break;
	case 6:
		retyitem.itemno = 6;
		retyitem.itemtex = 11;
		retyitem.name = "slime sword+";
		retyitem.damage = 4.0f;
		retyitem.attackspeed = 125;
		retyitem.autoattack = 1;
		break;
	case 7:
		retyitem.itemno = 7;
		retyitem.itemtex = 13;
		retyitem.name = "skill rod";
		retyitem.showtext[0] = "Unsellable items";
		retyitem.damage = 2.0f;
		retyitem.attackspeed = 50;
		retyitem.autoattack = 1;
		break;
	case 8:
		retyitem.itemno = 8;
		retyitem.itemtex = 6;
		retyitem.name = "Heal potion";
		retyitem.showtext[0] = { "If you right-click" };
		retyitem.showtext[1] = { "HP increases by 6" };
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 9:
		retyitem.itemno = 9;
		retyitem.itemtex = 6;
		retyitem.name = "Heal potion+";
		retyitem.showtext[0] = { "If you right-click" };
		retyitem.showtext[1] = { "HP increases by 10" };
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 10:
		retyitem.itemno = 10;
		retyitem.itemtex = 6;
		retyitem.name = "Heal potion++";
		retyitem.showtext[0] = { "If you right-click" };
		retyitem.showtext[1] = { "HP increases by 18" };
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 11:
		retyitem.itemno = 11;
		retyitem.itemtex = 6;
		retyitem.name = "Heal potion+++";
		retyitem.showtext[0] = { "If you right-click" };
		retyitem.showtext[1] = { "HP increases by 35" };
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 12:
		retyitem.itemno = 12;
		retyitem.itemtex = 7;
		retyitem.name = "regeneration potion";
		retyitem.showtext[0] = { "If you right-click" };
		retyitem.showtext[1] = { "HP increases by 0.25/s" };
		retyitem.showtext[2] = { "Duration 240 sec" };
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 13:
		retyitem.itemno = 13;
		retyitem.itemtex = 8;
		retyitem.name = "power potion";
		retyitem.showtext[0] = { "If you right-click" };
		retyitem.showtext[1] = { "Strength is increased by 20" };
		retyitem.showtext[2] = { "Duration 120 sec" };
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 14:
		retyitem.itemno = 14;
		retyitem.itemtex = 15;
		retyitem.name = "Iron Ore";
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 15:
		retyitem.itemno = 15;
		retyitem.itemtex = 14;
		retyitem.name = "Blue Crystal";
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 16:
		retyitem.itemno = 16;
		retyitem.itemtex = 16;
		retyitem.name = "Iron Ring";
		retyitem.armor = 5;
		retyitem.maxhp = 10;
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 17:
		retyitem.itemno = 17;
		retyitem.itemtex = 16;
		retyitem.name = "Iron Ring + ";
		retyitem.armor = 8;
		retyitem.maxhp = 10;
		retyitem.dex = 2;
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 18:
		retyitem.itemno = 18;
		retyitem.itemtex = 17;
		retyitem.name = "Crystal Ring";
		retyitem.movespeed = 3;
		retyitem.dex = 5;
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 19:
		retyitem.itemno = 19;
		retyitem.itemtex = 17;
		retyitem.name = "Slime Ring";
		retyitem.maxhp = 15;
		retyitem.str = 5;
		retyitem.dex = 2;
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 20:
		retyitem.itemno = 20;
		retyitem.itemtex = 18;
		retyitem.name = "Pyro";
		retyitem.dex = 12;
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 21:
		retyitem.itemno = 21;
		retyitem.itemtex = 19;
		retyitem.name = "Hurricane";
		retyitem.str = 10;
		retyitem.dex = 10;
		retyitem.maxhp = 15;
		retyitem.movespeed = 5;
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 22:
		retyitem.itemno = 22;
		retyitem.itemtex = 19;
		retyitem.name = "Tempest";
		retyitem.str = 20;
		retyitem.dex = 10;
		retyitem.maxhp = 30;
		retyitem.movespeed = 8;
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 23:
		retyitem.itemno = 23;
		retyitem.itemtex = 20;
		retyitem.name = "Fortress";
		retyitem.armor = 40;
		retyitem.vit = 15;
		retyitem.maxhp = 60;
		retyitem.movespeed = -3;
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 24:
		retyitem.itemno = 24;
		retyitem.itemtex = 21;
		retyitem.name = "leather helmet";
		retyitem.armor = 15;
		retyitem.vit = 5;
		retyitem.maxhp = 10;
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 25:
		retyitem.itemno = 25;
		retyitem.itemtex = 21;
		retyitem.name = "Hard leather helmet";
		retyitem.armor = 30;
		retyitem.vit = 10;
		retyitem.maxhp = 35;
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 26:
		retyitem.itemno = 26;
		retyitem.itemtex = 22;
		retyitem.name = "Iron helmet";
		retyitem.armor = 50;
		retyitem.vit = 20;
		retyitem.maxhp = 85;
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 27:
		retyitem.itemno = 27;
		retyitem.itemtex = 22;
		retyitem.name = "Steel helmet";
		retyitem.armor = 70;
		retyitem.vit = 25;
		retyitem.maxhp = 110;
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 28:
		retyitem.itemno = 28;
		retyitem.itemtex = 3;
		retyitem.name = "stick";
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 29:
		retyitem.itemno = 29;
		retyitem.itemtex = 23;
		retyitem.name = "leather";
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 30:
		retyitem.itemno = 30;
		retyitem.itemtex = 24;
		retyitem.name = "dark iron";
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 31:
		retyitem.itemno = 31;
		retyitem.itemtex = 25;
		retyitem.name = "Magic Treasure Box";
		retyitem.showtext[0] = "Right-click to open";
		retyitem.autoattack = 1;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 32:
		retyitem.itemno = 32;
		retyitem.itemtex = 26;
		retyitem.name = "shot gun";
		retyitem.autoattack = 1;
		retyitem.skill = 4;
		retyitem.damage = 2.5f;
		retyitem.size = 160.0f;
		retyitem.attackspeed = 75;
		retyitem.range = 0;
		retyitem.count = 1;
		break;
	case 33:
		retyitem.itemno = 33;
		retyitem.itemtex = 1;
		retyitem.name = "meteor sword";
		retyitem.damage = 4.5f;
		retyitem.maxhp = 10;
		retyitem.attackspeed = 100;
		retyitem.autoattack = 1;
		break;
	/*case 3:
		retyitem.itemno = 3;
		retyitem.itemtex = 3;
		retyitem.name = "shabby rod";

		
	
		break;
	case 4:
		retyitem.itemno = 4;
		retyitem.itemtex = 4;
		retyitem.name = "slimegel";
		break;
	case 5:
		retyitem.itemno = 5;
		retyitem.itemtex = 6;
		retyitem.name = "red potion";

		break;
	case 6:
		retyitem.itemno = 6;
		retyitem.itemtex = 7;
		retyitem.name = "red potion +";
		break;


		break;*/
	default:
		break;
	}
	return retyitem;
}
void seteffect(int n) {
	float addeffect[MAXEFFECT] = {};
	switch (n)
	{
	case 1:addeffect[0] = 300;//sloww
		break;
	case 2:addeffect[0] = 60;//sloww
		break;
	case 3:addeffect[1] = 60 * 15;//speed
		break;
	case 4:addeffect[2] = 60 * 60;//hpバフ
		break;
	case 5:addeffect[3] = 60 * 60;//slow耐性
		break;
	case 6:addeffect[4] = 60 * 60;//ノックバック耐性
		break;
	case 7:addeffect[5] = 60 * 15;//クリ率UP
		break;
	case 8:addeffect[6] = 60 * 15;//クリダメUP
		break;
	case 9:addeffect[7] = 60 * 15;//defUP
		break;
	case 10:addeffect[8] = 60 * 240;//再生
		break;
	case 11:addeffect[9] = 60 * 120;//STRUP
		break;
	default:
		break;
	}
	for (int i = 0; i < MAXEFFECT; i++)
	{
		if (addeffect[i] > playereffect[i])
		{
			playereffect[i] = addeffect[i];
		}
	}

}
void playerknockBack(D3DXVECTOR2 vel) {
	player.vel += vel;
	junpcount--;

}
void clearPlayerAll() {
	//地面に落ちてるアイテムを消す
	for (int i = 0; i < DROPMAX; i++)
	{
		dropitem[i].use = false;
	}
	//エフェクトを消す
	for (int i = 0; i < MAXEFFECT; i++)
	{
		playereffect[i] = 0;
	}
aact = 0;
aacttimr = 1;
player.nowhp = player.maxhp;
}
int shopcelectna() {
	return shopcelectitemna;
}
int getgold() {

	return gold;
}
int itemselltable(int n) {
	int cellgold = 0;
	switch (n)
	{
	case 1:
		cellgold = 1;
		break;
	case 2:
		cellgold = 5;
		break;
	case 3:
		cellgold = 5;
		break;
	case 4:
		cellgold = 25;
		break;
	case 5:
		cellgold = 25;
		break;
	case 6:
		cellgold = 25;
		break;
	case 7:
		cellgold = 5;
		break;
	case 8:
		cellgold = 2;
		break;
	case 9:
		cellgold = 5;
		break;
	case 10:
		cellgold = 15;
		break;
	case 11:
		cellgold = 50;
		break;
	case 12:
		cellgold = 1;
		break;
	case 13:
		cellgold = 5;
		break;
	case 14:
		cellgold = 3;
		break;
	case 15:
		cellgold = 5;
		break;
	case 16:
		cellgold = 5;
		break;
	case 17:
		cellgold = 5;
		break;
	case 18:
		cellgold = 5;
		break;
	case 19:
		cellgold = 5;
		break;
	case 20:
		cellgold = 5;
		break;
	case 21:
		cellgold = 5;
		break;
	case 22:
		cellgold = 5;
		break;
	case 23:
		cellgold = 5;
		break;
	case 24:
		cellgold = 2;
		break;
	case 25:
		cellgold = 5;
		break;
	case 26:
		cellgold = 15;
		break;
	case 27:
		cellgold = 30;
		break;
	case 28:
		cellgold = 1;
		break;
	case 29:
		cellgold = 1;
		break;
	case 30:
		cellgold = 5;
		break;
	case 31:
		cellgold = 1;
		break;
	case 32:
		cellgold = 15;
		break;
	case 33:
		cellgold = 10;
		break;
	default:
		break;
	}
	return cellgold;
}
int itembuytable(int n) {
	int buygold = 0;
	switch (n)
	{
	case 1:
		buygold = 5;
		break;
	case 8:
		buygold = 10;
		break;
	case 9:
		buygold = 25;
		break;
	case 10:
		buygold = 60;
		break;
	case 11:
		buygold = 180;
		break;
	case 12:
		buygold = 5;
		break;
	case 13:
		buygold = 300;
		break;

		
	default:
		break;
	}
	return buygold;
}
WEAPONITEM shopitem(int n) {
	if (n == 0)
	{
		return PresetItem(8);
	}
	if (n == 1)
	{
		return PresetItem(9);
	}
	if (n == 2)
	{
		return PresetItem(10);
	}
	if (n == 3)
	{
		return PresetItem(11);
	}
	if (n == 4)
	{
		return PresetItem(12);
	}
	if (n == 5)
	{
		return PresetItem(13);
	}
	if (n == 6)
	{
		return PresetItem(1);
	}
	return {};
}
WEAPONITEM craftitemnom(int n) {
	switch (n)
	{
	case 0:return PresetItem(2);
		break;
	case 1:return PresetItem(3);
		break;
	case 2:return PresetItem(4);
		break;
	case 3:return PresetItem(5);
		break;
	case 4:return PresetItem(6);
		break;
	case 5:return PresetItem(24);
		break;
	case 6:return PresetItem(25);
		break;
	case 7:return PresetItem(26);
		break;
	case 8:return PresetItem(27);
		break;
	case 9:return PresetItem(16);
		break;
	case 10:return PresetItem(17);
		break;
	case 11:return PresetItem(18);
		break;
	default:
		break;
	}
	return {};
}
int craftitemnam(int n, int s) {
	int retnam = -1;
	switch (n)
	{
	case 0:
		switch (s)
		{
		case 0:retnam = 28;
			break;
		case 1:retnam = 14;
			break;
		case 2:retnam = 1;
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (s)
		{
		case 0:retnam = 28;
			break;
		case 1:retnam = 14;
			break;
		case 2:retnam = 1;
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (s)
		{
		case 0:retnam = 15;
			break;
		case 1:retnam = 30;
			break;
		case 2:retnam = 2;
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (s)
		{
		case 0:retnam = 15;
			break;
		case 1:retnam = 30;
			break;
		case 2:retnam = 3;
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (s)
		{
		case 0:retnam = 15;
			break;
		case 1:retnam = 30;
			break;
		case 2:retnam = 3;
			break;
		default:
			break;
		}
		break;
	case 5:
		switch (s)
		{
		case 0:retnam = 29;
			break;
		default:
			break;
		}
		break;
	case 6:
		switch (s)
		{
		case 0:retnam = 29;
			break;
		case 1:retnam = 24;
			break;
		default:
			break;
		}
		break;
	case 7:
		switch (s)
		{
		case 0:retnam = 14;
			break;
		case 1:retnam = 25;
			break;
		default:
			break;
		}
		break;
	case 8:
		switch (s)
		{
		case 0:retnam = 30;
			break;
		case 1:retnam = 26;
			break;
		default:
			break;
		}
		break;
	case 9:
		switch (s)
		{
		case 0:retnam = 14;
			break;
		default:
			break;
		}
		break;
	case 10:
		switch (s)
		{
		case 0:retnam = 14;
			break;
		case 1:retnam = 16;
			break;
		default:
			break;
		}
		break;
	case 11:
		switch (s)
		{
		case 0:retnam = 15;
			break;
		case 1:retnam = 17;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return retnam;
}
int craftitemcount(int n, int s) {

	int retnam = -1;
	switch (n)
	{
	case 0:
		switch (s)
		{
		case 0:retnam = 13;
			break;
		case 1:retnam = 5;
			break;
		case 2:retnam = 1;
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (s)
		{
		case 0:retnam = 13;
			break;
		case 1:retnam = 5;
			break;
		case 2:retnam = 1;
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (s)
		{
		case 0:retnam = 5;
			break;
		case 1:retnam = 7;
			break;
		case 2:retnam = 1;
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (s)
		{
		case 0:retnam = 5;
			break;
		case 1:retnam = 7;
			break;
		case 2:retnam = 1;
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (s)
		{
		case 0:retnam = 5;
			break;
		case 1:retnam = 7;
			break;
		case 2:retnam = 1;
			break;
		default:
			break;
		}
		break;
	case 5:
		switch (s)
		{
		case 0:retnam = 5;
			break;
	
		default:
			break;
		}
		break;
	case 6:
		switch (s)
		{
		case 0:retnam = 11;
			break;
		case 1:retnam = 1;
			break;
		default:
			break;
		}
		break;
	case 7:
		switch (s)
		{
		case 0:retnam = 8;
			break;
		case 1:retnam = 1;
			break;
		default:
			break;
		}
		break;
	case 8:
		switch (s)
		{
		case 0:retnam = 5;
			break;
		case 1:retnam = 1;
			break;
		default:
			break;
		}
		break;
	case 9:
		switch (s)
		{
		case 0:retnam = 3;
			break;
		case 1:retnam = 1;
			break;
		default:
			break;
		}
		break;
	case 10:
		switch (s)
		{
		case 0:retnam = 6;
			break;
		case 1:retnam = 1;
			break;
		default:
			break;
		}
		break;
	case 11:
		switch (s)
		{
		case 0:retnam = 3;
			break;
		case 1:retnam = 1;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return retnam;
}
