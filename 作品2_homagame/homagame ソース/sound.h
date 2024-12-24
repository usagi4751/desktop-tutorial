/*==============================================================================

   �T�E���h���� [sound.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once	// �C���N���[�h�K�[�h

#include <windows.h>
#include "xaudio2.h"

/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/
bool InitSound(HWND hWnd);
void UninitSound(void);

int LoadSound(char* pFilename);
void PlaySound(int index, int loopCount);
void StopSound(int index);
void StopSoundAll(void);
void SetVolume(int index, float vol);
