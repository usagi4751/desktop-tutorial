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

HRESULT InitMapModelObject(void);
void UninitMapModelObject(void);
void UpdateMapModelObject(void);
void DrawMapModelObject(void);
void SaveModelMap(void);
void LoadModelMap(void);
MAPOBJECTMODEL* GetSelectMapObjectModel(void);
int GetMapModelObjectCount(void);
void DrawMapModelObject2D();
int GetMapModelObjectSelectCont(void);