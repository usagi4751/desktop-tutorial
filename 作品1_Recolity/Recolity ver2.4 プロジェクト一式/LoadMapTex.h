#pragma once
#include "main.h"


typedef struct {

	bool            use;        //�g���Ă��邩
	int             num;        //���f���̎g�p�ԍ�
	D3DXVECTOR3     pos;        // �|���S���̈ʒu
	D3DXVECTOR3     rot;        // �|���S���̌���(��])
	D3DXVECTOR3     scl;        // �|���S���̑傫��(�X�P�[��)
	D3DXCOLOR       color;        // �|���S���̃J���[
	D3DXMATRIX      mtxWorld;    // ���[���h�}�g���b�N�X

}MAPOBJECTMODEL;
#define MAX_MAPOBJECTMODEL_NUM (1024)	//3DModel�̍ő吔
HRESULT InitMapModelObject(void);
void LoadModelMap(void);
void DrawMapModelObject();

