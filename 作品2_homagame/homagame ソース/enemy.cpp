//=======================================================
// enemy.cpp
// 
//=======================================================
#include "main.h"
#include "sprite.h"
#include "renderer.h"
#include "texture.h"
#include "particle.h"
#include "polygon.h"
#include <iostream>
#include <cmath>
#include "enemy.h"
#include "winuser.h"
#include "input.h"
#include "polygon.h"
#include "player.h"
#include "sound.h"
#include "skill.h"
ENEMY enemy[MAXENEMY] = {};
enum {
	STOP = 0,
	WALK,
	ATTACK,


};
int g_enemytex[4];//敵のテクスチャ
int hpbar = 0;//エネミーのHPバー
float ccc;//歩くテクスチャに使う
int tt;//歩くテクスチャに使う
int bossskillct[2] = { 0,0};//ボスのスキルのクールタイム
int tptimer = 0;//ｔｐのモーションで使う
int motionct = 0;//攻撃後の硬直ct
int summonmotion = 0;
int bossspellcast = 0;
int bossspellcastmotion = 0;
void InitEnemy()
{
	g_enemytex[0] = LoadTexture((char*)"data/TEXTURE/slime.png");
	g_enemytex[1] = LoadTexture((char*)"data/TEXTURE/skeleton.png");
	g_enemytex[2] = LoadTexture((char*)"data/TEXTURE/mageske.png");
	g_enemytex[3] = LoadTexture((char*)"data/TEXTURE/ore.png");
	hpbar = LoadTexture((char*)"data/TEXTURE/hpbar2.png");
	for (int i = 0; i < MAXENEMY; i++)
	{
		enemy[i].pos = { 0.0f,0.0f };
		enemy[i].vel = { 0.0f,0.0f };
		enemy[i].use = false;
		enemy[i].rote = 0;
		for (int j = 0; j < 16; j++)
		{
			enemy[i].hitbox[j].pos = { 0,0 };
			enemy[i].hitbox[j].size = { 0,0 };
			enemy[i].hitbox[j].type = 0;
			enemy[i].hitbox[j].use = false;
		}

	}

	//PresetEnemy(3, { 100.0f,600.0f });
	//PresetEnemy(2, { 400.0f,600.0f });
	//PresetEnemy(2, { 500.0f,600.0f });




}
void UninitEnemy() {


}
void UpdateEnemy() {
	
	PLAYER playerpos = *GetPlayerStatus();
	D3DXVECTOR2 playercamera = Getcamera();
	D3DXVECTOR2 playercorsor = Getcorsor();
	//スライムの挙動用のタイマー
	tt++;
	if ((int)tt % 15 == 0)
	{
		
		ccc++;
	}

	if (ccc > 1)
	{
		ccc = 0;
	}
	if (motionct > 0)
	{
		motionct--;
	}
	for (int z = 0; z < 2; z++)
	{
		if (bossskillct[z] > 0)
		{
			bossskillct[z]--;
		}
		if (bossskillct[z] < 0)
		{
			bossskillct[z] = 0;
		}
	}
	for (int i = 0; i < MAXENEMY; i++)
	{
		float slow = 1.0f;
		if (enemy[i].slowness > 0)
		{
			enemy[i].slowness--;
			slow = 0.7f;
		}
		//エネミーを倒した時の処理
		if (enemy[i].hp <=  0 && enemy[i].use == true)
		{
			for (int j = 0; j < 4; j++)
			{
				//敵が死んだ時にアイテムを落とす
				if (enemy[i].dropitem[j].itemno > 0 && frand() < enemy[i].droprate[j])
				{
					Dropitem(enemy[i].pos, enemy[i].dropitem[j]);
				
				}
				if (enemy[i].no == 3 )
				{
					*Getgoalpos() = 1616;
				}
			}
			GetPlayerStatus()->totalxp += enemy[i].xp;
			enemy[i].use = false;
		}
		if (enemy[i].use == true)
		{
			//エネミーの移動
			enemy[i].vel.y += 1.0f;
			enemy[i].vel.x *= 0.97f;
			enemy[i].pos.y += enemy[i].vel.y;
			enemy[i].pos.x += enemy[i].vel.x;
			if (enemy[i].pos.y >= 800)
			{
				enemy[i].pos.y = 800.0f;
				enemy[i].vel.y = 0.0f;
				enemy[i].vel.x *= 0.98f;
			}
			if (enemy[i].vel.x < 0.1 && enemy[i].vel.x > -0.1)
			{
				enemy[i].vel.x = 0.0f;
			}

			//エネミーがプレイヤーの方向を向くようにする
			if (enemy[i].pos.x < playerpos.pos.x && enemy[i].use == true && enemy[i].state != 2)
			{
				enemy[i].rote = 0;
			}
			if (enemy[i].pos.x > playerpos.pos.x && enemy[i].use == true)
			{
				enemy[i].rote = -1;
			}
			//プレイヤーに向かって移動する
			if ((enemy[i].pos.x < playerpos.pos.x - 25 || enemy[i].pos.x > playerpos.pos.x + 25) &&
				(enemy[i].pos.x > playerpos.pos.x - 159 && enemy[i].pos.x < playerpos.pos.x + 159) &&
				enemy[i].use == true && enemy[i].state != 2 && (enemy[i].no != 3 && enemy[i].no != 4))
			{
				enemy[i].state = WALK;
				enemy[i].pos.x += (enemy[i].movespeed * 0.01f * slow) * (enemy[i].rote * 2 + 1.0f);
				enemy[i].texstate = ccc;
			}
			else if (enemy[i].state != 2)
			{
				enemy[i].state = STOP;
				enemy[i].texstate = 0;
			}
			if (enemy[i].aact <= 0 && (enemy[i].no == 1) &&
				enemy[i].pos.x > playerpos.pos.x - 26 &&
				enemy[i].pos.x < playerpos.pos.x + 26 &&
				enemy[i].pos.y > playerpos.pos.y - 40 &&
				enemy[i].pos.y < playerpos.pos.y + 40
				)
			{
			
				enemydamage(1, enemy[i]);
				enemy[i].aact = 60.0f / enemy[i].attackspeed;
		
			}
			if (enemy[i].aact <= 0 && (enemy[i].no == 2) &&
				enemy[i].pos.x > playerpos.pos.x - 26 &&
				enemy[i].pos.x < playerpos.pos.x + 26 &&
				enemy[i].pos.y > playerpos.pos.y - 40 &&
				enemy[i].pos.y < playerpos.pos.y + 40 && enemy[i].state != 2
				)
			{
				enemy[i].state = 2;
			
				enemy[i].aact = 60.0f / enemy[i].attackspeed;

			}
			if (enemy[i].state == 2&& enemy[i].no == 2 )
			{
				
				enemy[i].texstate = 2 + 16 - (16 * (enemy[i].aact / (60.0f / (enemy[i].attackspeed ))));
				if (enemy[i].texstate < 3)
				{
					enemy[i].texstate = 2;
				}
				if (enemy[i].pos.x > playerpos.pos.x - 46 - (35.0f + (float)enemy[i].rote * 70.0f )
					&&enemy[i].pos.x < playerpos.pos.x + 46 - (35.0f + (float)enemy[i].rote * 70.0f)
					&&enemy[i].pos.y > playerpos.pos.y - 190 &&enemy[i].pos.y < playerpos.pos.y + 190 && 
					enemy[i].texstate > 5)
				{
					enemydamage(1, enemy[i]);
				}
				
				if (enemy[i].texstate > 5)
				{
					enemy[i].state = 0;
				}
			}
			//ボスのモーション
			if (enemy[i].no == 3)
			{
				//歩く
				if ((enemy[i].state == 0 || enemy[i].state == 1) &&
					(enemy[i].pos.x > playerpos.pos.x - 129 && enemy[i].pos.x < playerpos.pos.x + 129))
				{
					enemy[i].state = 1;
					enemy[i].texstate = (int)((tt % 50) / 26);
					enemy[i].pos.x -= (enemy[i].movespeed * 0.01f * slow) * (enemy[i].rote * 2 + 1.0f);
				}
				if (enemy[i].state == 1 && (int)tt % 60 == 0)
				{
					PlaySound(8, 0);
					SetVolume(8, 0.1f);
				}
				//テレポートする
				if ((enemy[i].pos.x < 50 || enemy[i].pos.x > GetmapMaxXpos() - 50 ||
					enemy[i].pos.x > playerpos.pos.x - 60 &&
					enemy[i].pos.x < playerpos.pos.x + 60) && bossskillct[0] == 0 && tt % 15 == 0&&
					(enemy[i].state == 0 || enemy[i].state == 1))
				{
					if (frand() < 0.1)
					{
						enemy[i].state = 2;
						enemy[i].texstate = 2;
						bossskillct[0] = 300;
						motionct = 60;
						tptimer = 0;
						PlaySound(9, 0);
						SetVolume(9, 0.1f);
					}
				}
				if (enemy[i].texstate == 2)
				{
					tptimer++;
					if (tptimer > 40 && enemy[i].pos.x < 50)
					{
						enemy[i].pos.x = 300;
						enemy[i].texstate = 3;
						
					}
					else if (tptimer > 40 && enemy[i].pos.x > GetmapMaxXpos() - 50)
					{
						enemy[i].pos.x = GetmapMaxXpos() - 300;
						enemy[i].texstate = 3;

					}
					else if (tptimer > 40)
					{
						float tprand = 0;
						if ((int)rand() % 2 == 0)
						{
							tprand = 150.0f * frand()+ 100;

						}
						else {
							 tprand = -150.0f * frand() - 100;
						}
						enemy[i].pos.x = playerpos.pos.x + tprand;
						enemy[i].texstate = 3;
					}
				}
				//召喚
				if (bossskillct[1] == 0 && (enemy[i].state == 0 || enemy[i].state == 1))
				{
					enemy[i].state = 2;
					enemy[i].texstate = 4;
					bossskillct[1] = 1200;
					if (frand() < 0.4)
					{
						bossskillct[1] = 0;
					}
					motionct = 120;
					summonmotion = 0;
			
				}
				if (enemy[i].texstate >= 4 && enemy[i].texstate <= 6)
				{
					summonmotion++;
					if (summonmotion < 80 && summonmotion > 40)
					{
						setparticle(
							0,
							enemy[i].pos.x + 50 + enemy[i].rote * 100, 1200.0f - summonmotion*8.0f,
							12.5f, 20.0f,
							0.8f, 10, 20,
							0, 1.0f,
							0.03f, 0.0f,
							0.6f, 0.3f,
							0.8f, 0.0f,
							0.15f, 0.0f, 0.3f);
					}
				
					if (summonmotion > 20)
					{
				
						enemy[i].texstate = 5;
					
					}
					if (summonmotion == 20)
					{

						PlaySound(7, 0);
						SetVolume(7, 0.1f);
					}
					if (summonmotion == 40)
					{
						PlaySound(4, 0);
						SetVolume(4, 0.1f);
					}
					if (summonmotion > 50)
					{
						enemy[i].texstate = 6;

					}
					if (summonmotion == 80)
					{
						setparticle(
							0,
							enemy[i].pos.x + 50 + enemy[i].rote * 100, 720,
							12.5f, 140.0f,
							0.8f, 50, 20,
							0, 1.0f,
							0.03f, 0.0f,
							0.6f, 0.3f,
							0.8f, 0.0f,
							0.3f, 0.3f, 0.40f);
						setparticle(
							0,
							enemy[i].pos.x + 50 + enemy[i].rote * 100, 720,
							12.5f, 140.0f,
							0.8f, 50, 20,
							0, 1.0f,
							0.03f, 0.0f,
							0.6f, 0.3f,
							0.8f, 0.0f,
							1.0f, 0.3f, 1.0f);
						PresetEnemy(4, { enemy[i].pos.x + 50 + enemy[i].rote * 100,720 });
						enemy[i].texstate = 0;
					}
					
					
				}
			
				//通常攻撃
				if (enemy[i].aact == 0 && (enemy[i].state == 0 || enemy[i].state == 1))
				{
					enemy[i].state = 2;
					enemy[i].texstate = 7;
					enemy[i].aact = 240 + 180 * frand();
					motionct = 180;
					bossspellcast = (int)(frand() * 4);
					if (bossspellcast == 2 && 
						(enemy[i].pos.x < playerpos.pos.x - 110 || enemy[i].pos.x > playerpos.pos.x + 110))
					{
					bossspellcast = 0;
					}
					bossspellcastmotion = 0;
					PlaySound(10, 0);
					SetVolume(10, 0.1f);
				}
				if (enemy[i].texstate == 7 )
				{
					bossspellcastmotion++;
					//詠唱中のパーティクル
					if (bossspellcastmotion <= 40)
					{
						float coler[3] = {};
						switch (bossspellcast)
						{
						case 0:coler[0] = 1.0f;
							break;
						case 1:coler[0] = 0.9f;
							coler[1] = 0.9f;
							coler[2] = 1.0f;
							break;
						case 2:
							coler[0] = 0.6f;
							coler[1] = 0.15f;
							coler[2] = 0.1f;
							break;
						case 3:
							coler[0] = 0.1f;
							coler[1] = 0.1f;
							coler[2] = 0.2f;
							break;
						default:
							break;
						}
						setparticle(
							0,
							enemy[i].pos.x, 680,
							0.0f, 0.0f,
							1.5f, 4, 15,
							0, 1.0f,
							0.06f, 0.0f,
							0.6f, 0.3f,
							0.8f, 0.0f,
							coler[0], coler[1], coler[2]);
						setparticle(
							0,
							enemy[i].pos.x, 680,
							0.0f, 0.0f,
							1.5f, 1, 15,
							0, 1.0f,
							0.06f, 0.0f,
							0.6f, 0.3f,
							0.8f, 0.0f,
							coler[0] + 0.2f, coler[1] + 0.2f, coler[2] + 0.2f);
					}
					//詠唱後のパーティクル
					if (bossspellcastmotion == 80)
					{
						float coler[3] = {};
						switch (bossspellcast)
						{
						case 0:coler[0] = 1.0f;
							break;
						case 1:coler[0] = 0.9f;
							coler[1] = 0.9f;
							coler[2] = 1.0f;
							break;
						case 2:
							coler[0] = 0.6f;
							coler[1] = 0.15f;
							coler[2] = 0.1f;
							break;
						case 3:
							coler[0] = 0.1f;
							coler[1] = 0.1f;
							coler[2] = 0.2f;
							break;
						default:
							break;
						}			
						setparticle(
							0,
							enemy[i].pos.x, 680,
							0.0f, 0.0f,
							6.5f, 100, 15,
							0, 1.0f,
							0.12f, 0.0f,
							0.6f, 0.3f,
							0.8f, 0.0f,
							coler[0], coler[1], coler[2]);
					}
					if (bossspellcastmotion == 85 && bossspellcast ==0)
					{
						EnemyUseSkill(2, enemy[i].pos);
					}
					if (bossspellcastmotion == 85 && bossspellcast == 1)
					{
						EnemyUseSkill(1,enemy[i].pos);
					}	
					if (bossspellcastmotion == 85 && bossspellcast == 2)
					{
						EnemyUseSkill(3, enemy[i].pos);
					}
					if (bossspellcastmotion == 85 && bossspellcast == 3  )
					{
						seteffect(1);
						setparticle(
							3,
							playerpos.pos.x, playerpos.pos.y - 100,
							12.0f, 50.0f,
							0.6f, 10, 25,
							0.5f, 0.0f,
							0.05f, 0.0f,
							1.1f, 0.3f,
							0.0f, 0.0f,
							0.2f, 0.2f, 0.8f);
						setparticle(
							0,
							playerpos.pos.x, playerpos.pos.y,
							0.0f, 0.0f,
							1.5f, 120, 15,
							0, 1.0f,
							0.06f, 0.0f,
							0.6f, 0.3f,
							0.8f, 0.0f,
							0.0f, 0.0f, 0.0f);
					}
				}
				//モーション硬直がない場合状態を何もない状態に
				if (motionct == 0 )
				{
					enemy[i].state = 0;
					
				}
			}
			if (enemy[i].no == 4)
			{
				enemy[i].vel = {0.0f,0.0f};
			}
		
			if (enemy[i].aact > 0)
			{
				enemy[i].aact -= 1.0f;
			}
			if (enemy[i].aact < 0)
			{
				enemy[i].aact = 0;
			}
			if (enemy[i].pos.x <0)
			{
				enemy[i].pos.x = 0;
			}
			if (enemy[i].pos.x > GetmapMaxXpos())
			{
				enemy[i].pos.x = GetmapMaxXpos();
			}
		}
		
	}


}
void DrawEnemy() {
	PLAYER playerpos = *GetPlayerStatus();
	D3DXVECTOR2 playercamera = Getcamera();
	D3DXVECTOR2 playercorsor = Getcorsor();
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (enemy[i].use == true)
		{
			float hpbarpos = 0.0f;
			if (enemy[i].no == 1)
			{
				//SCREEN_WIDTH * 0.5f + (enemy[i].pos.x - playerpos.x) * 4.7 - (playercorsor.x - SCREEN_WIDTH * 0.5) * 0.10 + playercamera.x * 1650, enemy[i].pos.y,
				DrawSpriteColorRotate(g_enemytex[0],
					SCREEN_WIDTH * 0.5f + (enemy[i].pos.x - playerpos.pos.x) * 4.7f - (playercorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + playercamera.x * 1650, enemy[i].pos.y - 30.0f,
					150, 150,
					((int)ccc % 3) / 3.0f - enemy[i].rote / 3.0f, (int)(ccc / 3) / 3.0f, 1.0f / 3.0f + (float)enemy[i].rote * 2 / 3.0f, 1.0f / 3.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0);
			}
			if (enemy[i].no == 2)
			{
				hpbarpos = -180 + 75;
				//SCREEN_WIDTH * 0.5f + (enemy[i].pos.x - playerpos.x) * 4.7 - (playercorsor.x - SCREEN_WIDTH * 0.5) * 0.10 + playercamera.x * 1650, enemy[i].pos.y,
				// 				//下半身
				int walktex = 0;
				if (enemy[i].texstate > 2)
				{
					walktex = 2;

				}
				else
				{
					walktex = enemy[i].texstate;
				}
				DrawSpriteColorRotate(g_enemytex[1],
					SCREEN_WIDTH * 0.5f + (enemy[i].pos.x - playerpos.pos.x) * 4.7f - (playercorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + playercamera.x * 1650, enemy[i].pos.y - 88.0f + 75,
					380, 380,
					(walktex % 3) / 3.0f - enemy[i].rote / 3.0f, 2.0f / 3.0f,
					1.0f / 3.0f + (float)enemy[i].rote * 2 / 3.0f, 1.0f / 3.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0);
				//上半身
				DrawSpriteColorRotate(g_enemytex[1],
					SCREEN_WIDTH * 0.5f + (enemy[i].pos.x - playerpos.pos.x) * 4.7f - (playercorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + playercamera.x * 1650, enemy[i].pos.y - 78.0f ,
					380, 380,
					(enemy[i].texstate %3) / 3.0f - enemy[i].rote / 3.0f, (int)(enemy[i].texstate / 3.0f)/3.0f,
					1.0f / 3.0f + (float)enemy[i].rote * 2 / 3.0f, 1.0f / 3.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0);

			}
			if (enemy[i].no == 3)
			{
				DrawSpriteColorRotate(g_enemytex[2],
					SCREEN_WIDTH * 0.5f + (enemy[i].pos.x - playerpos.pos.x) * 4.7f - (playercorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + playercamera.x * 1650, enemy[i].pos.y - 180.0f,
					450, 450,
					((int)enemy[i].texstate %4) / 4.0f - enemy[i].rote / 4.0f , 0.0f + (int)(enemy[i].texstate / 4.0f) * 0.5f,
					1.0f / 4.0f + (float)enemy[i].rote * 2 / 4.0f, 1.0f / 2.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0);
			}
			if (enemy[i].no ==4)
			{
				DrawSpriteColorRotate(g_enemytex[3],
					SCREEN_WIDTH * 0.5f + (enemy[i].pos.x - playerpos.pos.x) * 4.7f - (playercorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + playercamera.x * 1650, enemy[i].pos.y ,
					120, 120,
					0.0f,0.0f,
					1.0f,1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0);
			}

			//HPバー表示
			DrawSpriteColorRotate(hpbar,
				SCREEN_WIDTH * 0.5f + (enemy[i].pos.x - playerpos.pos.x) * 4.7f - (playercorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + playercamera.x * 1650, enemy[i].pos.y - 35.0f + hpbarpos,
				100, 16,
				0,0, 1,1,
				0.3f, 0.3f, 0.3f, 1.0f,
				0);
			DrawSpriteColorRotate(hpbar,
				SCREEN_WIDTH * 0.5f + (enemy[i].pos.x - playerpos.pos.x) * 4.7f - (playercorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + playercamera.x * 1650 - (1 - enemy[i].hp / enemy[i].maxhp) * 50 ,
				enemy[i].pos.y - 35.0f + hpbarpos,
				100 * (enemy[i].hp / enemy[i].maxhp), 16,
				0, 0, 1, 1,
				0.6f, 0.16f, 0.16f, 1.0f,
				0);
		}

	}
}
ENEMY GetEnemy(int n) {

	return enemy[n];

}
void AddDamageenemy(int n,float damage) {
	enemy[n].hp -= damage;
}
void PresetEnemy(int n, D3DXVECTOR2 pos) {

	for (int  i = 0; i < MAXENEMY; i++)
	{
		if (enemy[i].use == false )
		{
			ENEMY dummy = {};
			switch (n)
			{
			case 1:
				//slime
				dummy.no = 1;
				dummy.state = 0;
				dummy.pos = pos;
				dummy.vel = { 0.0f,0.0f};
				dummy.use = true;
				dummy.rote = 0;
				dummy.maxhp = dummy.hp = 10.0f;
				dummy.damage = 1.0f;
				dummy.movespeed = 100.0f;
				dummy.armor = 0.0f;
				dummy.attackspeed = 1.0f;
				dummy.xp = 1;
				dummy.hitbox[0].pos = { 0 ,-15 };
				dummy.hitbox[0].size = { 75,15 };
				dummy.hitbox[0].type = 0;
				dummy.hitbox[0].use = true;
				dummy.hitbox[1].pos = { 0,15 };
				dummy.hitbox[1].size = { 150,60 };
				dummy.hitbox[1].type = 1;
				dummy.hitbox[1].use = true;
				dummy.dropitem[0] = PresetItem(28);
				dummy.droprate[0] = 0.7f;
				dummy.dropitem[1] = PresetItem(29);
				dummy.droprate[1] = 0.7f;
				dummy.dropitem[2] = PresetItem(7);
				switch ((int)(frand() * 10.0f))
				{
				case 0:
					dummy.dropitem[2].skill = 1;
					break;
				case 1:
					dummy.dropitem[2].skill = 1;
					break;
				case 2:
					dummy.dropitem[2].skill = 1;
					break;
				case 3:
					dummy.dropitem[2].skill = 2;
					break;
				case 4:
					dummy.dropitem[2].skill = 6;
					break;
				case 5:
					dummy.dropitem[2].skill = 7;
					break;
				case 6:
					dummy.dropitem[2].skill = 7;
					break;
				case 7:
					dummy.dropitem[2].skill = 8;
					break;
				case 8:
					dummy.dropitem[2].skill = 11;
					break;
				case 9:
					dummy.dropitem[2].skill = 13;
					break;
				default:
					break;
				}
				dummy.droprate[2] = 0.1f;
				dummy.dropitem[3] = PresetItem(31);
				dummy.droprate[3] = 0.02f;
				break;
			case 2:
				//skeleton
				dummy.no = 2;
				dummy.state = 0;
				dummy.pos = pos;
				dummy.vel = { 0.0f,0.0f };
				dummy.use = true;
				dummy.rote = 0;
				dummy.maxhp = dummy.hp = 45.0f;
				dummy.damage = 3.0f;
				dummy.movespeed = 90.0f;
				dummy.armor = 0.0f;
				dummy.attackspeed = 1.0f;
				dummy.xp = 3;
				dummy.hitbox[0].pos = { 0 ,-110 };
				dummy.hitbox[0].size = { 45,40 };
				dummy.hitbox[0].type = 0;
				dummy.hitbox[0].use = true;
				dummy.hitbox[1].pos = { 0,-23 };
				dummy.hitbox[1].size = { 120,125 };
				dummy.hitbox[1].type = 1;
				dummy.hitbox[1].use = true;
				dummy.dropitem[0] = PresetItem(30);
				dummy.droprate[0] = 0.25f;
				dummy.dropitem[1] = PresetItem(14);
				dummy.droprate[1] = 0.4f;
				dummy.dropitem[2] = PresetItem(7);
				switch ((int)(frand() * 10.0f))
				{
				case 0:
					dummy.dropitem[2].skill = 2;//bullet+
					break;
				case 1:
					dummy.dropitem[2].skill = 2;//bullet+
					break;
				case 2:
					dummy.dropitem[2].skill = 2;//bullet+
					break;
				case 3:
					dummy.dropitem[2].skill = 3;//bullet++
					break;
				case 4:
					dummy.dropitem[2].skill = 5;//棘
					break;
				case 5:
					dummy.dropitem[2].skill = 8;//HPboost
					break;
				case 6:
					dummy.dropitem[2].skill = 9;//スロウ耐性
					break;
				case 7:
					dummy.dropitem[2].skill = 10;//ノックバック耐性
					break;
				case 8:
					dummy.dropitem[2].skill = 12;//クリダメup
					break;
				case 9:
					dummy.dropitem[2].skill = 5;//棘
					break;
				default:
					break;
				}
				dummy.droprate[2] = 0.1f;
				dummy.dropitem[3] = PresetItem(31);
				dummy.droprate[3] = 0.02f;
				break;
			case 3:
				//skeletonmage
				dummy.no = 3;
				dummy.state = 0;
				dummy.pos = pos;
				dummy.vel = { 0.0f,0.0f };
				dummy.use = true;
				dummy.rote = 0;
				dummy.maxhp = dummy.hp = 1200.0f;
				dummy.damage = 1.0f;
				dummy.movespeed = 90.0f;
				dummy.armor = 0.0f;
				dummy.attackspeed = 1.0f;
				dummy.xp = 100;
				dummy.hitbox[0].pos = { 0 ,-200 };
				dummy.hitbox[0].size = { 45,40 };
				dummy.hitbox[0].type = 0;
				dummy.hitbox[0].use = true;
				dummy.hitbox[1].pos = { 0,-63 };
				dummy.hitbox[1].size = { 120,225 };
				dummy.hitbox[1].type = 1;
				dummy.hitbox[1].use = true;


				break;
			case 4:
				//skeleton
				//ボス召喚スケルトン
				dummy.no = 2;
				dummy.state = 0;
				dummy.pos = pos;
				dummy.vel = { 0.0f,0.0f };
				dummy.use = true;
				dummy.rote = 0;
				dummy.maxhp = dummy.hp = 42.0f;
				dummy.damage = 5.5f;
				dummy.movespeed = 105.0f;
				dummy.armor = 0.0f;
				dummy.attackspeed = 1.6f;
				dummy.hitbox[0].pos = { 0 ,-110 };
				dummy.hitbox[0].size = { 45,40 };
				dummy.hitbox[0].type = 0;
				dummy.hitbox[0].use = true;
				dummy.hitbox[1].pos = { 0,-23 };
				dummy.hitbox[1].size = { 120,125 };
				dummy.hitbox[1].type = 1;
				dummy.hitbox[1].use = true;
			


				break;
			case 5:
				//鉱石
				dummy.no = 4;
				dummy.state = 0;
				dummy.pos = pos;
				dummy.vel = { 0.0f,0.0f };
				dummy.use = true;
				dummy.rote = 0;
				dummy.maxhp = dummy.hp = 30.0f;
				dummy.damage = 1.5f;
				dummy.movespeed = 80.0f;
				dummy.armor = 0.0f;
				dummy.attackspeed = 1.3f;
				dummy.hitbox[1].pos = { 0,-23 };
				dummy.hitbox[1].size = { 120,125 };
				dummy.hitbox[1].type = 1;
				dummy.hitbox[1].use = true;
				dummy.dropitem[0] = PresetItem(14);
				dummy.droprate[0] = 0.5f;
				dummy.dropitem[1] = PresetItem(15);
				dummy.droprate[1] = 0.15f;

				break;
				
				case 6:
					//skeleton
					dummy.no = 2;
					dummy.state = 0;
					dummy.pos = pos;
					dummy.vel = { 0.0f,0.0f };
					dummy.use = true;
					dummy.rote = 0;
					dummy.maxhp = dummy.hp = 65.0f;
					dummy.damage = 6.0f;
					dummy.movespeed = 120.0f;
					dummy.armor = 0.0f;
					dummy.attackspeed = 1.0f;
					dummy.hitbox[0].pos = { 0 ,-110 };
					dummy.hitbox[0].size = { 45,40 };
					dummy.hitbox[0].type = 0;
					dummy.hitbox[0].use = true;
					dummy.hitbox[1].pos = { 0,-23 };
					dummy.hitbox[1].size = { 120,125 };
					dummy.hitbox[1].type = 1;
					dummy.hitbox[1].use = true;
					dummy.dropitem[0] = PresetItem(30);
					dummy.droprate[0] = 0.5f;
					dummy.dropitem[1] = PresetItem(14);
					dummy.droprate[1] = 0.8f;
					dummy.dropitem[2] = PresetItem(7);
					switch ((int)(frand() * 10.0f))
					{
					case 0:
						dummy.dropitem[2].skill = 2;//bullet+
						break;
					case 1:
						dummy.dropitem[2].skill = 2;//bullet+
						break;
					case 2:
						dummy.dropitem[2].skill = 2;//bullet+
						break;
					case 3:
						dummy.dropitem[2].skill = 3;//bullet++
						break;
					case 4:
						dummy.dropitem[2].skill = 5;//棘
						break;
					case 5:
						dummy.dropitem[2].skill = 8;//HPboost
						break;
					case 6:
						dummy.dropitem[2].skill = 9;//スロウ耐性
						break;
					case 7:
						dummy.dropitem[2].skill = 10;//ノックバック耐性
						break;
					case 8:
						dummy.dropitem[2].skill = 5;//棘
						break;
					case 9:
						dummy.dropitem[2].skill = 5;//棘
						break;
					default:
						break;
					}
					dummy.droprate[2] = 0.15f;
					dummy.dropitem[3] = PresetItem(31);
					dummy.droprate[3] = 0.015f;
					break;
			default:
				break;
			}
			enemy[i] = dummy;
			break;
		}
	}

}
void AddknockBack(int taget, D3DXVECTOR2 vel) {

	enemy[taget].vel = vel;

}
void enemydamage(int n, ENEMY enemy) {
	PLAYER *pplayer = GetPlayerStatus();
	float adddamage = 0.0f;
	if (enemy.no == 1 )
	{
		adddamage = enemy.damage ;
	}
	if (enemy.no == 2 )
	{
		adddamage = enemy.damage;
	}
	if ( n == 2 )
	{
		adddamage = 2;
	}
	if (pplayer->vit *0.534f < 90)
	{
		pplayer->nowhp -= adddamage * (1 - pplayer->vit * 0.00534f) * (50.0f / (50.0f + pplayer->def));
	}
	else
	{
		pplayer->nowhp -= adddamage * (1.0f - 0.9f) * (50.0f / (50.0f + pplayer->def));
	}
	
}
void clearEenemyAll() {

	for (int i = 0; i < MAXENEMY; i++)
	{
		enemy[i].use = false;
	}
     bossskillct[0] = 0;//ボスのスキルのクールタイム
	 bossskillct[1] = 0;//ボスのスキルのクールタイム
	 tptimer = 0;//ｔｐのモーションで使う
	 motionct = 0;//攻撃後の硬直ct
	 summonmotion = 0;
	 bossspellcast = 0;
	 bossspellcastmotion = 0;
}
void addeffectenemy(int n, int efeect) {
	if (efeect == 1)
	{
		enemy[n].slowness = 60;
	}

}

