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
#include "winuser.h"
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
#define SCREEN_WIDTH	(1920)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(1080)				// �E�C���h�E�̍���

enum
{
    LibCur_ARROW = 0,
    LibCur_IBEAM = 1,
    LibCur_WAIT = 2,
    LibCur_CROSS = 3,
    LibCur_UPARROW = 4,
    LibCur_SIZE = 128,
    LibCur_ICON,
    LibCur_SIZENWSE,
    LibCur_SIZENESW,
    LibCur_SIZEWE,
    LibCur_SIZENS,
    LibCur_SIZEALL,
    LibCur_NO,
    LibCur_HAND,
    LibCur_APPSTARTING,
    LibCur_HELP


};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//�����_���쐬0-1�̊�
float frand(void);
HWND GetHwnd(void);