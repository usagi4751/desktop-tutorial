#pragma once
#include "main.h"
#include "renderer.h"

//======================
//�e�N�X�`���̓ǂݍ��݋@�\
//======================

//�ǂݍ���
int LoadTexture(const wchar_t* fileName);

//�����[�X
void UninitTexture(void);

//�Ăяo��
ID3D11ShaderResourceView** GetTexture(int index);
