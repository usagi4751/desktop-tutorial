#include "bullet.h"
#include <iostream>
#include <cmath>
BULLET bullet[MAXBULLET];
int bullettex[3] = {};
int cro = 0;
void InitBullet(void) {
	bullettex[0] = LoadTexture((char*)"data/TEXTURE/glint.png");
	bullettex[1] = LoadTexture((char*)"data/TEXTURE/crit.hit.png");
	bullettex[2] = LoadTexture((char*)"data/TEXTURE/ise.png");
	for (int i = 0; i < MAXBULLET; i++)
	{
		bullet[i].di = 0.0f;
		bullet[i].distance = 0.0f;
		bullet[i].pos = { 0.0f,0.0f };
		bullet[i].range = 0.0f;
		bullet[i].size = { 0.0f,0.0f };
		bullet[i].speed = 0.0f;
		bullet[i].taget = 0;
		bullet[i].type = 0;
		bullet[i].use = false;

	}
}
void UninitBullet(void) {

}
void UpdateBullet(void) {

	PLAYER playerpos = *GetPlayerStatus();
	D3DXVECTOR2 playercamera = Getcamera();
	D3DXVECTOR2 playercorsor = Getcorsor();
	cro++;
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (bullet[i].use == true)
		{
			bullet[i].distance += bullet[i].speed * 5.0f;
			bullet[i].pos.x += std::cos(PAI * bullet[i].di / 1) * bullet[i].speed;
			bullet[i].pos.y += std::sin(PAI * bullet[i].di / 1) * 4.5f * bullet[i].speed;
			if ( bullet[i].type == 0 && cro % 3 == 0)
			{
				setparticle(
					0,//ナンバー
					bullet[i].pos.x , bullet[i].pos.y,//pos x y
					0.0f, 0.0f,//dx dy
					0.9f, 1, 20, //スピード 数 サイズ
					0, 1.0f,//方向 　収束率
					0.04f, 0.0f,//減速率 重力
					0.9f, 0.3f,//表示時間　表示時間率
					0.8f, 0.0f,//スピードランダム　サイズランダム
					0.3f, 0.3f, 1.0f);//カラー
			}
			if (bullet[i].type == 6 && cro % 3 == 0)
			{
				setparticle(
					0,//ナンバー
					bullet[i].pos.x, bullet[i].pos.y,//pos x y
					0.0f, 0.0f,//dx dy
					0.9f, 1, 20, //スピード 数 サイズ
					0, 1.0f,//方向 　収束率
					0.04f, 0.0f,//減速率 重力
					0.9f, 0.3f,//表示時間　表示時間率
					0.8f, 0.0f,//スピードランダム　サイズランダム
					0.7f, 0.7f, 1.0f);//カラー
			}
			if (bullet[i].type == 2   )
			{
				setparticle(
					4,//ナンバー
					bullet[i].pos.x, bullet[i].pos.y,//pos x y
					0.0f, 0.0f,//dx dy
					0.01f, 1, 10, //スピード 数 サイズ
					0, 1.0f,//方向 　収束率
					0.04f, 0.0f,//減速率 重力
					0.6f, 0.3f,//表示時間　表示時間率
					0.8f, 0.0f,//スピードランダム　サイズランダム
					0.4f, 0.4f, 0.4f);//カラー
			}
			if (bullet[i].type == 1)
			{
				int dir = 0;
				if ((SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f) - (playercorsor.x - (SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f)) * 0.1f > playercorsor.x)
					dir = 0;
				else
					dir = -1;
					setparticle(
						2,//ナンバー
						bullet[i].pos.x , bullet[i].pos.y - 50 ,//pos x y
						0.0f, 0.0f,//dx dy
						0.0f, 1, 100, //スピード 数 サイズ
						(float)dir  + 1.0f, 0.0f,//方向 　収束率
						0.03f, 0.0f,//減速率 重力
						0.30f, 0.0f,//表示時間　表示時間率
						0.8f, 0.0f,//スピードランダム　サイズランダム
						0.6f, 0.6f, 0.6f);//カラー
				
				
			}
			bool onehit = true;
			for (int j = 0; j < MAXENEMY; j++)
			{
				if (onehit == false)
				{
					break;
				}
				ENEMY ememy = GetEnemy(j);
				for (int k = 0; k < ENEMYHITBOX; k++)
				{
					if (ememy.hitbox[k].use == true && ememy.use == true && bullet[i].use == true&&
						ememy.pos.x + ememy.hitbox[k].pos.x * 0.21256f + ememy.hitbox[k].size.x * 0.10628f + bullet[i].size.x * 0.10628f > bullet[i].pos.x &&
						ememy.pos.x + ememy.hitbox[k].pos.x * 0.21256f - ememy.hitbox[k].size.x * 0.10628f - bullet[i].size.x * 0.10628f < bullet[i].pos.x&&
						ememy.pos.y + ememy.hitbox[k].pos.y  + ememy.hitbox[k].size.y * 0.51f + bullet[i].size.y * 0.51f > bullet[i].pos.y &&
						ememy.pos.y + ememy.hitbox[k].pos.y  - ememy.hitbox[k].size.y * 0.51f - bullet[i].size.y * 0.51f < bullet[i].pos.y)
					{
						float headshotre = 1.0f;
						int type = 1;
						
						D3DXCOLOR		color{1.0f,0.4f,0.36f,1.0f};	//頂点カラー
						if (bullet[i].type == 1 && ememy.no != 3)
						{
							int dir = 0;
							if ((SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f) - (playercorsor.x - (SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f)) * 0.1f > playercorsor.x)
								dir = 0;
							else
								dir = -1;
							AddknockBack(j, { (float)dir * -3.0f - 1.5f  ,  0.0f });
						}

						if (ememy.hitbox[k].type == 0 && bullet[i].type == 0)
						{
						
							color = { 1.0f,0.65f,0.46f,1.0f };
							type = 2;
							headshotre = 1.5f;
						}
						if (ememy.hitbox[k].type == 0 && bullet[i].type == 2)
						{

							color = { 1.0f,0.65f,0.46f,1.0f };
							type = 2;
							headshotre = 1.5f;
						}
						if (ememy.hitbox[k].type == 0 && bullet[i].type == 6)
						{

							color = { 1.0f,0.65f,0.46f,1.0f };
							type = 2;
							headshotre = 1.5f;
						
						}
						if (bullet[i].type == 6)
						{
							addeffectenemy(j, 1);
						}
						if (ememy.hitbox[k].type == 1)
						{
							headshotre = 1.0f;
						}
					
						if ((bullet[i].damage * headshotre * bullet[i].crtdamage) > 0)
						{
							if (bullet[i].crtdamage > 1)
							{
								type = 3;
								color = { 1.0f,0.20f,0.0f,1.0f };
							}
							
							SetDamage(bullet[i].damage * headshotre * bullet[i].crtdamage, { ememy.pos.x - 10 ,ememy.pos.y - 50 }, color, type, (int)(ememy.rote * 2.0f + 1.0f));
							AddDamageenemy(j,  bullet[i].damage * headshotre * bullet[i].crtdamage);
						}
						else
						{
							SetDamage(0.0f, { ememy.pos.x - 10 ,ememy.pos.y - 50 }, color, type, (int)(ememy.rote * 2.0f + 1.0f));
							AddDamageenemy(j,0);
						}
		
						if (bullet[i].type == 0 || bullet[i].type == 2 || bullet[i].type == 6)
						{
							bullet[i].use = false;
							onehit = false;
							break; 
						
						}
						break;
					}

					if ((bullet[i].type == 1 || bullet[i].type == 3) && j == MAXENEMY - 1)
					{
						bullet[i].use = false;
						
					}
				}
			
			}
		}
		if (bullet[i].range <= bullet[i].distance)
		{
			bullet[i].use = false;
		}
	}
}
void DrawBullet(void) {
	PLAYER playerpos = *GetPlayerStatus();
	D3DXVECTOR2 playercamera = Getcamera();
	D3DXVECTOR2 playercorsor = Getcorsor();
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (bullet[i].use == true)
		{
			int butex = -1;
			D3DXCOLOR bucolor = {};	//頂点カラー
			if (bullet[i].type == 0)
			{
				butex = 0;
				bucolor = { 1.0f,1.0f ,0.0f ,1.0f };
			}
			if (bullet[i].type == 1)
			{
				butex = 0;
				bucolor = { 1.0f,1.0f ,0.0f ,1.0f };
			}
			if (bullet[i].type == 6)
			{
				butex = 2;
				bucolor = { 1.0f,1.0f ,1.0f ,1.0f };
				DrawSpriteColorRotate(bullettex[butex],
					SCREEN_WIDTH * 0.5f + (bullet[i].pos.x - playerpos.pos.x) * 4.7f - (playercorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + playercamera.x * 1650.0f, bullet[i].pos.y,
					40, 40,
					1.0f, 1.0f, 1.0f, 1.0f,
					bucolor.r, bucolor.g, bucolor.b, bucolor.a,
					(bullet[i].di-0.5f) * PAI);
				butex = -1;
			}
			if (butex > -1)
			{
				DrawSpriteColorRotate(bullettex[butex],
					SCREEN_WIDTH * 0.5f + (bullet[i].pos.x - playerpos.pos.x) * 4.7f - (playercorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + playercamera.x * 1650.0f, bullet[i].pos.y,
					bullet[i].size.x, bullet[i].size.y,
					0.0f, 0.0f, 1.0f, 1.0f,
					bucolor.r, bucolor.g, bucolor.b, bucolor.a,
					0);
			}
		
		}
	}
}
void SetBullet(int butaget, D3DXVECTOR2 bupos, int butype) {
	if (butype == 4)
	{
		for (int j= 0; j < 6; j++)
		{
			for (int i = 0; i < MAXBULLET; i++)
			{
				if (bullet[i].use == false)
				{
					PLAYER playerpos = *GetPlayerStatus();
					D3DXVECTOR2 playercamera = Getcamera();
					D3DXVECTOR2 playercorsor = Getcorsor();
					bullet[i].taget = butaget;
					bullet[i].pos = bupos;
					bullet[i].type = butype;
					bullet[i].crtdamage = 1.0f;
					
					if (bullet[i].type == 4)
					{
						bullet[i].type = 2;
						int dir = 0;
						if ((SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f) - (playercorsor.x - (SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f)) * 0.1f > playercorsor.x)
							dir = 0;
						else
							dir = -1;
						setparticle(
							4,//ナンバー
							bullet[i].pos.x, bullet[i].pos.y,//pos x y
							0.0f, 0.0f,//dx dy
							15.5f, 20, 10, //スピード 数 サイズ
							((float)atan2(playerpos.pos.y - playercorsor.y, SCREEN_WIDTH * 0.5f + (playercamera.x * 10.0f) - playercorsor.x - 70 - dir * 140))  / PAI + 1.0f , 0.125f,//方向 　収束率
							0.12f, 0.0f,//減速率 重力
							0.6f, 0.3f,//表示時間　表示時間率
							0.3f, 0.0f,//スピードランダム　サイズランダム
							0.6f, 0.6f, 0.6f);//カラー
						bullet[i].size = { 10.0f,10.0f };
						bullet[i].di = ((float)atan2(playerpos.pos.y - playercorsor.y, SCREEN_WIDTH * 0.5f + (playercamera.x * 10.0f) - playercorsor.x - 70 - dir * 140)) / PAI + 1.0f - 0.25 * 0.5f + j * 0.1f * 0.5f;
						bullet[i].range = 400;
						bullet[i].speed = 10.5f;
						bullet[i].damage = 3.0f * (1.0f + playerpos.str * 0.01f);
						bullet[i].crtdamage = 1.0f;
						if (playerpos.critcalrete * 0.01f > frand())
						{
							bullet[i].crtdamage = 1.0f + playerpos.critcaldamage * 0.01f;
						}



					}
					
					bullet[i].distance = 0.0f;

					bullet[i].use = true;
					break;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < MAXBULLET; i++)
		{
			if (bullet[i].use == false)
			{
				PLAYER playerpos = *GetPlayerStatus();
				D3DXVECTOR2 playercamera = Getcamera();
				D3DXVECTOR2 playercorsor = Getcorsor();
				bullet[i].taget = butaget;
				bullet[i].pos = bupos;
				bullet[i].type = butype;
				bullet[i].crtdamage = 1.0f;
				if (bullet[i].type == 0)
				{
					int dir = 0;
					if ((SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f) - (playercorsor.x - (SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f)) * 0.1f > playercorsor.x)
						dir = 0;
					else
						dir = -1;
					bullet[i].size = { 10.0f,10.0f };
					bullet[i].di = ((float)atan2(playerpos.pos.y - playercorsor.y, SCREEN_WIDTH * 0.5f + (playercamera.x * 10.0f) - playercorsor.x - 70 - dir * 140)) / PAI + 1.0f;
					bullet[i].range = 600;
					bullet[i].speed = 2.5f;
					bullet[i].damage = 2.0f * (1.0f + playerpos.str * 0.01f);
					bullet[i].crtdamage = 1.0f;
					if (playerpos.critcalrete * 0.01f > frand())
					{
						bullet[i].crtdamage = 1.0f + playerpos.critcaldamage * 0.01f;
					}
				}
				if (bullet[i].type == 2)
				{
					bullet[i].type = 0;
					int dir = 0;
					if ((SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f) - (playercorsor.x - (SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f)) * 0.1f > playercorsor.x)
						dir = 0;
					else
						dir = -1;
					bullet[i].size = { 10.0f,10.0f };
					bullet[i].di = ((float)atan2(playerpos.pos.y - playercorsor.y, SCREEN_WIDTH * 0.5f + (playercamera.x * 10.0f) - playercorsor.x - 70 - dir * 140)) / PAI + 1.0f;
					bullet[i].range = 600;
					bullet[i].speed = 2.5f;
					bullet[i].damage = 3.0f * (1.0f + playerpos.str * 0.01f);
					bullet[i].crtdamage = 1.0f;
					if (playerpos.critcalrete * 0.01f > frand())
					{
						bullet[i].crtdamage = 1.0f + playerpos.critcaldamage * 0.01f;
					}
				}
				if (bullet[i].type == 3)
				{
					bullet[i].type = 0;
					int dir = 0;
					if ((SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f) - (playercorsor.x - (SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f)) * 0.1f > playercorsor.x)
						dir = 0;
					else
						dir = -1;
					bullet[i].size = { 10.0f,10.0f };
					bullet[i].di = ((float)atan2(playerpos.pos.y - playercorsor.y, SCREEN_WIDTH * 0.5f + (playercamera.x * 10.0f) - playercorsor.x - 70 - dir * 140)) / PAI + 1.0f;
					bullet[i].range = 600;
					bullet[i].speed = 2.5f;
					bullet[i].damage = 3.0f * (1.0f + playerpos.str * 0.01f);
					bullet[i].crtdamage = 1.0f;
					if (playerpos.critcalrete * 0.01f > frand())
					{
						bullet[i].crtdamage = 1.0f + playerpos.critcaldamage * 0.01f;
					}
				}
				if (bullet[i].type == 1)
				{
					int dir = 0;
					if ((SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f) - (playercorsor.x - (SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f)) * 0.1f > playercorsor.x)
						dir = 0;
					else
						dir = -1;
					bullet[i].pos.y += 30;
					bullet[i].pos.x += -dir * 30 - 15;
					bullet[i].size = { 100.0f,100.0f };
					bullet[i].di = ((float)atan2(playerpos.pos.y - playercorsor.y, SCREEN_WIDTH * 0.5f + (playercamera.x * 10.0f) - playercorsor.x - 100 - dir * 200)) / PAI + 1.0f;
					bullet[i].range = 1.0f;
					bullet[i].speed = 0.5f;
					bullet[i].damage = playerpos.inventory[haveitem()].damage * (1.0f + playerpos.str * 0.01f);
					bullet[i].crtdamage = 1.0f;
					if (playerpos.critcalrete * 0.01f > frand())
					{
						bullet[i].crtdamage = 1.0f + playerpos.critcaldamage * 0.01f;
					}
				}
				if (bullet[i].type == 5)
				{
					bullet[i].type = 3;
					bullet[i].pos.y = bupos.y;
					bullet[i].pos.x = bupos.x;
					bullet[i].size = { 40.0f,40.0f };
					bullet[i].di = 0;
					bullet[i].range = 1.0f;
					bullet[i].speed = 0.5f;
					bullet[i].damage = 0.2f;
					bullet[i].crtdamage = 1.0f;
					if (playerpos.critcalrete * 0.01f > frand())
					{
						bullet[i].crtdamage = 1.0f + playerpos.critcaldamage * 0.01f;
					}
				}
				if (bullet[i].type == 6)
				{
					int dir = 0;
					if ((SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f) - (playercorsor.x - (SCREEN_WIDTH * 0.5f + playercamera.x * 1500.0f)) * 0.1f > playercorsor.x)
						dir = 0;
					else
						dir = -1;
					bullet[i].size = { 10.0f,10.0f };
					bullet[i].di = ((float)atan2(playerpos.pos.y - playercorsor.y, SCREEN_WIDTH * 0.5f + (playercamera.x * 10.0f) - playercorsor.x - 70 - dir * 140)) / PAI + 1.0f;
					bullet[i].range = 600;
					bullet[i].speed = 2.5f;
					bullet[i].damage = 2.0f * (1.0f + playerpos.str * 0.01f);
					bullet[i].crtdamage = 1.0f;
					if (playerpos.critcalrete * 0.01f > frand())
					{
						bullet[i].crtdamage = 1.0f + playerpos.critcaldamage * 0.01f;
					}
				}
				bullet[i].distance = 0.0f;

				bullet[i].use = true;
				break;
			}
		}
	}
	
	


}
void clearBulletAll() {
	for (int i = 0; i < MAXBULLET; i++)
	{
		bullet[i].use = false;
	}
	
}