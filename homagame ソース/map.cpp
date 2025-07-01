//===================================
// マップの設定
//===================================
#include "polygon.h"
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "particle.h"
#include "main.h"
#include <math.h>
#include "winuser.h"
#include "player.h"
#include "enemy.h"
#include "player.h"
#include "sound.h"
#include "bullet.h"
#include "particle.h"
#include "map.h"
#include "skill.h"
//bgが決まる
int nowmap = 1;
float maxxpos = 1617;
std::string  mapname = "";
float goalpos = -1;
int gomap = 0;//挑戦中のマップ
void InitMap(void) {
	nowmap = 1;
	gomap = 0;
	for (int i = 0; i < 14; i++)
	{
		SetVolume(i, 0);
	}
}
void UninitMap(void) {

}
void UpdateMap(void) {

}
void Setmap(int n) {
	//マップ選択時にすべてのアイテムを消去する
	clearEenemyAll();
	clearBulletAll();
	clearparticleAll();
	clearSkillAll();
	clearPlayerAll();
	clearPorigon();
	PLAYER *player = GetPlayerStatus();
	player->pos.x = 0;

	gomap = n;
	if (n == 0)//町
	{
		goalpos = -1;
		mapname = "Homa town";
		nowmap = 1;
		maxxpos = 625;
		PlaySound(11, 0);
	}	
	if (n == 1)//1F
	{
		PlaySound(6, 0);
		PlaySound(12, -1);
		goalpos = 850;
		mapname = std::to_string(n) + "F";
		nowmap = 0;
		maxxpos = 1617;
		PresetEnemy(1, { 170 , 800 });
		PresetEnemy(1, { 350 , 800 });
		PresetEnemy(1, { 400 , 800 });
		PresetEnemy(1, { 700 , 800 });
	}
	if (n == 2)//2F
	{
		goalpos = 1000;
		PlaySound(12, -1);
		PlaySound(6, 0);
		mapname = std::to_string(n) + "F";
		nowmap = 0;
		maxxpos = 1617;
		PresetEnemy(1, { 170 , 800 });
		PresetEnemy(1, { 320 , 800 });
		PresetEnemy(1, { 350 , 800 });
		PresetEnemy(1, { 400 , 800 });
		PresetEnemy(5, { 450 , 800 });
		PresetEnemy(1, { 700 , 800 });
		PresetEnemy(1, { 730 , 800 });
		PresetEnemy(1, { 760 , 800 });
	}
	if (n == 3)//3F
	{
		goalpos = 1000;
		PlaySound(12, -1);
		PlaySound(6, 0);
		mapname = std::to_string(n) + "F";
		nowmap = 0;
		maxxpos = 1617;
		PresetEnemy(1, { 200 , 800 });
		PresetEnemy(1, { 220 , 800 });
		PresetEnemy(5, { 450 , 800 });
		PresetEnemy(1, { 350 , 800 });
		PresetEnemy(1, { 400 , 800 });
		PresetEnemy(5, { 750 , 800 });
		PresetEnemy(1, { 800 , 800 });
		PresetEnemy(1, { 830 , 800 });
		PresetEnemy(1, { 860 , 800 });
	}
	if (n == 4)//4F
	{
		goalpos = 1000;
		PlaySound(12, -1);
		PlaySound(6, 0);
		mapname = std::to_string(n) + "F";
		nowmap = 0;
		maxxpos = 1617;
		PresetEnemy(1, { 200 , 800 });
		PresetEnemy(1, { 250 , 800 });
		PresetEnemy(1, { 300 , 800 });
		PresetEnemy(5, { 650 , 800 });
		PresetEnemy(5, { 650 , 800 });
		PresetEnemy(5, { 650 , 800 });
		PresetEnemy(2, { 850 , 800 });
		PresetEnemy(1, { 820 , 800 });
		PresetEnemy(1, { 860 , 800 });
	}
	if (n == 5)//5F
	{
		goalpos = 1000;
		PlaySound(12, -1);
		PlaySound(6, 0);
		PresetEnemy(5, { 200 , 800 });
		PresetEnemy(1, { 230 , 800 });
		PresetEnemy(2, { 270 , 800 });
		PresetEnemy(2, { 330 , 800 });
		PresetEnemy(5, { 450 , 800 });
		PresetEnemy(5, { 500 , 800 });
		PresetEnemy(5, { 530 , 800 });
		PresetEnemy(1, { 630 , 800 });
		PresetEnemy(2, { 670 , 800 });
		PresetEnemy(2, { 730 , 800 });
		PresetEnemy(1, { 830 , 800 });
		PresetEnemy(1, { 890 , 800 });
		PresetEnemy(5, { 900 , 800 });
		PresetEnemy(5, { 930 , 800 });
		mapname = std::to_string(n) + "F";
		nowmap = 0;
		maxxpos = 1617;
	}
	if (n == 6)//6F
	{
		for (int i = 0; i < 3; i++)
		{
			PresetEnemy(2, { 300 + +i * 200.0f, 800 });
				PresetEnemy(2, { 270 +  + i * 200.0f, 800 });
				PresetEnemy(1, { 230 + +i * 200.0f, 800 });
			for (int j = 0; j < 2; j++)
			{
				PresetEnemy(5, { 200 + j * 50.0f + i * 200.0f, 800 });
			}
		}
		goalpos = 1000;

		mapname = std::to_string(n) + "F";
		nowmap = 0;
		maxxpos = 1617;
	}
	if (n == 7)//7F
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				PresetEnemy(2, { 350 + j * 25.0f + i * 150.0f, 800 });
			}
			for (int j = 0; j < 2; j++)
			{
				PresetEnemy(5, { 320 + j * 25.0f + i * 150.0f, 800 });
			}
		}
		goalpos = 1000;
		PlaySound(12, -1);
		PlaySound(6, 0);
		mapname = std::to_string(n) + "F";
		nowmap = 0;
		maxxpos = 1617;
	}
	if (n == 8)//8F
	{
		goalpos = 1000;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				PresetEnemy(2, { 270 + j * 25.0f + i * 150.0f, 800 });
			}
		}
		PlaySound(12, -1);
		PlaySound(6, 0);
		mapname = std::to_string(n) + "F";
		nowmap = 0;
		maxxpos = 1617;
	}
	if (n == 9)//9F
	{
		for (int i = 0; i < 4; i++)
		{
			
				PresetEnemy(6, { 270  + i * 150.0f, 800 });
			
		}
		goalpos = 1000;
		PlaySound(12, -1);
		PlaySound(6, 0);
		mapname = std::to_string(n) + "F";
		nowmap = 0;
		maxxpos = 1617;
	}
	if (n == 10)//10F
	{
		goalpos = -1;
		PlaySound(13, -1);
		mapname = std::to_string(n) + "F";
		nowmap = 0;
		maxxpos = 1617;
		PresetEnemy(3, { 170 , 800 });
	}
}
float GetmapMaxXpos() {
	return maxxpos;
}
int Getmaptex() {
	return nowmap;
}
std::string Getmapname() {
	return mapname;
}
float* Getgoalpos() {
	return &goalpos;
}
int Getgomap() {
	return gomap;
}