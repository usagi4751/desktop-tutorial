/*==============================================================================

   �e�N�X�`���̕`�� [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>
#include <string>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>
#include <math.h>
#include <imm.h>
#include <string.h>
#include <WinUser.h>
#pragma comment(lib,"d2d1.lib")//�e�L�X�g�\���Œǉ�
#pragma comment(lib,"dwrite.lib")//�e�L�X�g�\���Œǉ�

#include <d2d1.h>//�e�L�X�g�\���Œǉ�
#include <dwrite.h>//�e�L�X�g�\���Œǉ�
#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)


//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "Imm32.lib")


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1920)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(1080)				// �E�C���h�E�̍���


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
float frand(void);
std::string Gettextstring();
void Gettextstringclose();
D3DXVECTOR2 GetMousePos();
int GetGameFlame();
float GeyDPI();