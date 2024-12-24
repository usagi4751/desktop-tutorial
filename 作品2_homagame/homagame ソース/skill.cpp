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
#include "bullet.h"
#include "skill.h"
NAOBJECT skillobject[MAXOBJECT] = {};
int texter[3] = {};
void InitSkill(void) {
	texter[0] = LoadTexture((char*)"data/TEXTURE/ise.png");
	texter[1] = LoadTexture((char*)"data/TEXTURE/fireball.png");
	texter[2] = LoadTexture((char*)"data/TEXTURE/dirtspike.png");
}
void UninitSkill(void) {

}
void UpdateSkill(void) {
	PLAYER player = *GetPlayerStatus();
	D3DXVECTOR2 camera = Getcamera();
	D3DXVECTOR2 playercamera = Getcamera();
	D3DXVECTOR2 playercorsor = Getcorsor();
	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (skillobject[i].use == true && skillobject[i].component == 1)
		{
			skillobject[i].timer++;
			if (skillobject[i].timer > 150)
			{
				skillobject[i].use = false;
			}
			if (skillobject[i].pos.y < 800 && skillobject[i].timer > 80)
			{
				skillobject[i].vel.y++;
			}
			skillobject[i].pos.x += skillobject[i].vel.x ;
			skillobject[i].pos.y += skillobject[i].vel.y ;
			if (skillobject[i].pos.y > 800)
			{
				skillobject[i].pos.y = 800.0f;
			}
			if (skillobject[i].pos.x  + 20.0f  > player.pos.x &&
				skillobject[i].pos.x  - 20.0f  < player.pos.x &&
				skillobject[i].pos.y + player.hitbox[0].pos.y + 50.0f > player.pos.y &&
				skillobject[i].pos.y - player.hitbox[0].pos.y - 50.0f < player.pos.y)
			{
				skillobject[i].use = false;
				seteffect(2);
				enemydamage(12);
				setparticle(
					0,
					player.pos.x, player.pos.y,
					0.0f, 0.0f,
					1.0f, 15, 15,
					0, 1.0f,
					0.06f, 0.0f,
					0.6f, 0.3f,
					0.8f, 0.0f,
					0.9f, 0.9f, 1.0f);
			}
		}
		if (skillobject[i].use == true && skillobject[i].component == 2)
		{
			skillobject[i].timer++;
			if (skillobject[i].timer > 600)
			{
				skillobject[i].use = false;
			}
		
			skillobject[i].pos.x += skillobject[i].vel.x * 3;
			skillobject[i].pos.y += skillobject[i].vel.y * 3;
			for (int j = 0; j < 3; j++)
			{
				setparticle(
					4,
					skillobject[i].pos.x, skillobject[i].pos.y,
					10.0f, 30.0f,
					1.0f, j+1, 15,
					0, 1.0f,
					0.06f, 0.0f,
					0.6f, 0.3f,
					0.8f, 0.0f,
					1.0f, (0.2f + (j * 0.3f)), 0.0f);
			}

			if (skillobject[i].pos.x + 20.0f > player.pos.x &&
				skillobject[i].pos.x - 20.0f < player.pos.x &&
				skillobject[i].pos.y + player.hitbox[0].pos.y + 50.0f > player.pos.y &&
				skillobject[i].pos.y - player.hitbox[0].pos.y - 50.0f < player.pos.y)
			{
				skillobject[i].use = false;
				seteffect(2);
				enemydamage(5);
				if (skillobject[i].vel.x > 0)
				{
					playerknockBack({ 2 , -9 });
				}	
				if (skillobject[i].vel.x < 0)
				{
					playerknockBack({ -2 , -9 });
				}
			}
		}
		if (skillobject[i].use == true && skillobject[i].component == 3)
		{
			skillobject[i].timer++;
			if (skillobject[i].timer > 120)
			{
				skillobject[i].use = false;
			}

			if (skillobject[i].pos.x + 20.0f > player.pos.x &&
				skillobject[i].pos.x - 20.0f < player.pos.x &&
				skillobject[i].pos.y + player.hitbox[0].pos.y + 50.0f > player.pos.y &&
				skillobject[i].pos.y - player.hitbox[0].pos.y - 50.0f < player.pos.y)
			{
				skillobject[i].use = false;
				enemydamage(2);
				setparticle(
					4,
					player.pos.x, player.pos.y,
					0.0f, 0.0f,
					1.0f, 15, 15,
					0, 1.0f,
					0.06f, 0.0f,
					0.6f, 0.3f,
					0.8f, 0.0f,
					0.7f, 0.2f, 0.2f);
			}
		}
		if (skillobject[i].use == true && skillobject[i].component == 4)
		{
			skillobject[i].timer++;
			if (skillobject[i].timer > 120)
			{
				skillobject[i].use = false;
			}
			if (skillobject[i].timer % 15 == 1)
			{
				SetBullet(1, { skillobject[i].pos.x,skillobject[i].pos.y }, 5);
			}
			
		}
	}


}



void DrawSkill(void) {
	PLAYER player = *GetPlayerStatus();
	D3DXVECTOR2 camera = Getcamera();
	D3DXVECTOR2 playercamera = Getcamera();
	D3DXVECTOR2 playercorsor = Getcorsor();
	
	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (skillobject[i].use == true && skillobject[i].component == 1)
		{
			int size = skillobject[i].timer;
			if (size > 60)
			{
				size = 60;
			}
			DrawSpriteColorRotate(texter[0],
				SCREEN_WIDTH * 0.5f + (skillobject[i].pos.x - player.pos.x) * 4.7f - (playercorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + playercamera.x * 1650, skillobject[i].pos.y,
				40 + size,40+ size,
				0,0,
				1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0);
		}
		if (skillobject[i].use == true && skillobject[i].component == 2)
		{
		
			DrawSpriteColorRotate(texter[1],
				SCREEN_WIDTH * 0.5f + (skillobject[i].pos.x - player.pos.x) * 4.7f - (playercorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + playercamera.x * 1650, skillobject[i].pos.y,
				100, 100,
				0, 0,
				1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0);
		}
		if (skillobject[i].use == true && skillobject[i].component == 3)
		{

			DrawSpriteColorRotate(texter[2],
				SCREEN_WIDTH * 0.5f + (skillobject[i].pos.x - player.pos.x) * 4.7f - (playercorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + playercamera.x * 1650, skillobject[i].pos.y,
				100, 100,
				0, 0,
				1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0);
		}
		if (skillobject[i].use == true && skillobject[i].component == 4)
		{

			DrawSpriteColorRotate(texter[2],
				SCREEN_WIDTH * 0.5f + (skillobject[i].pos.x - player.pos.x) * 4.7f - (playercorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + playercamera.x * 1650, skillobject[i].pos.y,
				100, 100,
				0, 0,
				1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0);
		}
	}
}

void UseSkill(int n) {
	PLAYER player = *GetPlayerStatus();
	D3DXVECTOR2 camera = Getcamera();
	D3DXVECTOR2 corsor = GetNowcorsor();
	D3DXVECTOR2 nowcorsor = GetNowcorsor();
	NAOBJECT dummy = { false,{0.0f,0.0f},{0.0f,0.0f} };
	int dir = 0;
	if ((SCREEN_WIDTH * 0.5f + camera.x * 1500.0f) - (corsor.x - (SCREEN_WIDTH * 0.5f + camera.x * 1500.0f)) * 0.1f > corsor.x)
		dir = 0;
	else
		dir = -1;
	switch (n)
	{
	case 1:	SetBullet(1, { player.pos.x - 20 - dir * 40,player.pos.y - 40 }, 0);
		break;
	case 2:	SetBullet(1, { player.pos.x - 20 - dir * 40,player.pos.y - 40 }, 2);
		break;
	case 3:	SetBullet(1, { player.pos.x - 20 - dir * 40,player.pos.y - 40 }, 3);

		break;
	case 4:	SetBullet(1, { player.pos.x - 20 - dir * 40,player.pos.y - 40 }, 4);

		break;
	case 5:
		dummy.pos.x = player.pos.x - 37.5f;;
		dummy.pos.y = player.pos.y;
		dummy.component = 4;
		dummy.use = true;
		dummy.vel = { 0.0f,0.0f };
		for (int j = 0; j < 5; j++)
		{
			for (int i = 0; i < MAXOBJECT; i++)
			{
				if (skillobject[i].use == false)
				{
					skillobject[i] = dummy;

					skillobject[i].pos.x += 15.0f * j;
					skillobject[i].pos.x -= 43 + dir * 100;
					break;
				}
			}
		}
		break;
	case 6:SetBullet(1, { player.pos.x - 20 - dir * 40,player.pos.y - 40 }, 6);
		break;
	case 7:seteffect(3);//speed
		break;
	case 8:seteffect(4);//hp
		break;
	case 9:seteffect(5);//slow耐性
		break;
	case 10:seteffect(6);//ノックバック耐性
		break;
	case 11:seteffect(7);//クリ率
		break;
	case 12:seteffect(8);//クリダメ
		break;
	case 13:seteffect(9);//defup
		break;
	default:
		break;
	}
}
void EnemyUseSkill(int n, D3DXVECTOR2 enemypos) {
	PLAYER player = *GetPlayerStatus();
	D3DXVECTOR2 camera = Getcamera();
	D3DXVECTOR2 corsor = Getcorsor();
	D3DXVECTOR2 nowcorsor = GetNowcorsor();
	NAOBJECT dummy = { false,{0.0f,0.0f},{0.0f,0.0f} };
	float vac[2] = { (player.pos.x - enemypos.x), (player.pos.y - 650) };
	for (int i = 0; i < 2; i++)
	{
		if (vac[i] < 0)
		{
			vac[i] *= -1;
		}
	}
	switch (n)
	{
	case 1:
	
		dummy.pos.x = player.pos.x - 37.5f;;
		dummy.pos.y = 50;
		dummy.component = 1;
		dummy.use = true;
		dummy.vel = { 0.0f,0.0f };
		for (int j = 0; j < 5; j++)
		{
			for (int i = 0; i < MAXOBJECT; i++)
			{
				if (skillobject[i].use == false)
				{
					skillobject[i] = dummy;
					skillobject[i].pos.x += 15.0f * j;
					break;
				}
			}
		}
		
		break;
	case 2:

		dummy.pos.x = enemypos.x ;
		dummy.pos.y = 650;
		dummy.component = 2;
		dummy.use = true;
		
		dummy.vel = { (player.pos.x - enemypos.x) /(vac[1] + vac[0]),(player.pos.y - 650) / (vac[1] + vac[0]) };
		
			for (int i = 0; i < MAXOBJECT; i++)
			{
				if (skillobject[i].use == false)
				{
					skillobject[i] = dummy;
					break;
				}
			}
		

		break;
	case 3:

		dummy.pos.x = enemypos.x;
		dummy.pos.y = 800;
		dummy.component = 3;
		dummy.use = true;

		dummy.vel = { (player.pos.x - enemypos.x) / (vac[1] + vac[0]),(player.pos.y - 650) / (vac[1] + vac[0]) };

		for (int j = 0; j < 7; j++)
		{
			for (int i = 0; i < MAXOBJECT; i++)
			{
				if (skillobject[i].use == false)
				{
					skillobject[i] = dummy;
					skillobject[i].pos.x += 15.0f * j;
					break;
				}
			
			}
			for (int i = 0; i < MAXOBJECT; i++)
			{
				if (skillobject[i].use == false)
				{
					skillobject[i] = dummy;
					skillobject[i].pos.x -= 15.0f * j;
					break;
				}

			}
		}


		break;
	default:
		break;
	}

}
void clearSkillAll() {
	for (int i = 0; i < MAXOBJECT; i++)
	{
		skillobject[i].use = false;
	}


}