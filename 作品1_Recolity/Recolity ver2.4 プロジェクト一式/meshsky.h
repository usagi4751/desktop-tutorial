//=============================================================================
//
// ���b�V����̏��� [meshsky.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshSky(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
float radius, int numBlockX, int numBlockZ, bool reverse = false);
void UninitMeshSky(void);
void UpdateMeshSky(void);
void DrawMeshSky(void);
