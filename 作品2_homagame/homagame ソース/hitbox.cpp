//===========================================================
// hitbox.cpp
// 
//===========================================================
#include "main.h"
#include <time.h>
#include "hitbox.h"
#include "renderer.h"
#include "input.h"
#include "polygon.h"
#include "texture.h"
#include "sprite.h"
#include "particle.h"
#include "enemy.h"
#include "player.h"
static int g_hitbox = 0;

void Inithitbox(void) {

	g_hitbox = LoadTexture((char*)"data/TEXTURE/hitbox.png");

}
void Drawhitbox(void) {
	if (HitBoxswith() == true)
	{
		PLAYER player = SetPlayerStatus();
		ENEMY enemy = {};
		D3DXVECTOR2 camera = Getcamera();
		D3DXVECTOR2 corsor = Getcorsor();
		//プレイヤーヒットボックス
		for (int i = 0; i < 16; i++)
		{
			if (player.hitbox[i].use == true)
			{
				DrawSpriteColorRotate(g_hitbox,
					(SCREEN_WIDTH * 0.5f + camera.x * 1500.0f) - (corsor.x - (SCREEN_WIDTH * 0.5f + camera.x * 1500.0f)) * 0.1f + player.hitbox[i].pos.x, player.pos.y + player.hitbox[i].pos.y,
					player.hitbox[i].size.x, player.hitbox[i].size.y,
					0, 0,
					1, 1,
					1.0f, 1.0f, 1.0f, 0.5f,
					0);
			}

		}
		for (int i = 0; i < MAXENEMY; i++)
		{
			enemy = GetEnemy(i);

		

			
				for (int j = 0; j < 16; j++)
				{
					if (enemy.use == true && enemy.hitbox[j].use == true)
					{
						//				SCREEN_WIDTH * 0.5f + (enemy.pos.x - playerpos.x) * 4.7 - (playercorsor.x - SCREEN_WIDTH * 0.5) * 0.10 + playercamera.x * 1650, enemy.pos.y,
						DrawSpriteColorRotate(g_hitbox,
							SCREEN_WIDTH * 0.5f + (enemy.pos.x - player.pos.x) * 4.7f - (corsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + camera.x * 1650 + enemy.hitbox[j].pos.x, enemy.pos.y + enemy.hitbox[j].pos.y,
							enemy.hitbox[j].size.x, enemy.hitbox[j].size.y,
							0, 0,
							1, 1,
							1.0f, 1.0f - (float)enemy.hitbox[j].type * 0.7f, 1.0f - (float)enemy.hitbox[j].type * 0.7f, 0.5f,
							0);
					}
				}
			
		}
	}
	

}