#pragma once
#include "main.h"

typedef struct {

    bool            use;        //使っているか
    int             num;        //モデルの使用番号
    D3DXVECTOR3     pos;        // ポリゴンの位置
    D3DXVECTOR3     rot;        // ポリゴンの向き(回転)
    D3DXVECTOR3     scl;        // ポリゴンの大きさ(スケール)
    D3DXCOLOR       color;        // ポリゴンのカラー
    D3DXMATRIX      mtxWorld;    // ワールドマトリックス

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