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
	Floor_Type floor_type;//���̃^�C�v
	Floor_Adhere Adhere;//�t�����Ă��鑮��
	int				tex;//�e�N�X�`��
	int time;//�������t�����Ă��鎞��
}FLOOR2;

void InitFloor(void);
void UnInitFloor(void);
void UpdateFloor(void);
void DrawFloor(void);