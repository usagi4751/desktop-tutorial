#pragma once
#include "Texture.h"
struct POLYGON
{

	D3DXVECTOR3		pos;		// �|���S���̈ʒu
	D3DXVECTOR3		rot;		// �|���S���̌���(��])
	D3DXVECTOR3		scl;		// �|���S���̑傫��(�X�P�[��)
	D3DXCOLOR		color;		// �|���S���̃J���[

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};
enum Floor_Type
{
	Floor_Wall = 0,
	Floor_Nomal,
	Floor_Paper,
};
enum Floor_Adhere
{
	Floor_None = 0,
	Floor_flame,
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
Floor_Type GetNowFloor(D3DXVECTOR3 pos);
Floor_Adhere GetNowAdhere(D3DXVECTOR3 pos);
void SetAdhere(D3DXVECTOR3 pos,Floor_Adhere ad, int time);