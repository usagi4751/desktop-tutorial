#pragma once
#include "Texture.h"
enum Floor_Type
{
	Floor_Wall = 0,
	Floor_Nomal,
	Floor_Paper,
};
enum Floor_Adhere
{
	Floor_flame = 0,
	Floor_Water,
	Floor_Wind,
};
typedef struct {
	Floor_Type floor_type;//床のタイプ
	Floor_Adhere Adhere;//付着している属性
	int				tex;//テクスチャ
	int time;//属性が付着している時間
}FLOOR2;

void InitFloor(void);
void UnInitFloor(void);
void UpdateFloor(void);
void DrawFloor(void);