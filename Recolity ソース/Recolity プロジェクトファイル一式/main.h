//=============================================================================
//
// ���C������ [main.h]
// Author : 
//
//=============================================================================
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>
#pragma comment(lib,"d2d1.lib")//�e�L�X�g�\���Œǉ�
#pragma comment(lib,"dwrite.lib")//�e�L�X�g�\���Œǉ�
#include <string>//�e�L�X�g�\���Œǉ�
#include <string.h>//�e�L�X�g�\���Œǉ�
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


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1920)			// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(1080)			// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W

#define DIK_COLER_WHITE {1.0f,1.0f,1.0f,1.0f}
#define DIK_COLER_GRAY {0.6f,0.6f,0.6f,1.0f}
#define DIK_COLER_YELOW {1.5f,1.5f,0.0f,1.0f}
#define DIK_COLER_BLUE {0.2f,0.2f,1.0f,1.0f}
#define DIK_COLER_DRAKGRAY {0.2f,0.2f,0.2f,1.0f}
#define DIK_COLER_LIGHTRED {219.0f / 255.0f,79.0f /255.0f,46.0f /255.0f,1.0f}
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
long GetMousePosX(void);
long GetMousePosY(void);
char* GetDebugStr(void);
float frand(void);
float GeyDPI();
void CursprLock(bool swith);
D3DXVECTOR2 GetMousePos();