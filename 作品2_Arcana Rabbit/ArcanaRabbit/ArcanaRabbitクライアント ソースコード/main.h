#pragma once
#include"pch.h"
#define MY_MSG (WM_USER + 1)
/*#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <functional>
#include <fstream>
#include <d3d11.h>
#include <imm.h>
#pragma comment (lib, "d3d11.lib")

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment (lib, "Imm32.lib")//ImmGetContext�Ȃǂ��g����悤��
#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"

#include <DirectXMath.h>
using namespace DirectX;


#include "DirectXTex.h"
#pragma warning(disable : 4996)
#pragma comment(lib,"d2d1.lib")//�e�L�X�g�\���Œǉ�
#pragma comment(lib,"dwrite.lib")//�e�L�X�g�\���Œǉ�
#include <string>//�e�L�X�g�\���Œǉ�
#include <string.h>//�e�L�X�g�\���Œǉ�
#include <d2d1.h>//�e�L�X�g�\���Œǉ�
#include <dwrite.h>//�e�L�X�g�\���Œǉ�
#if _DEBUG
#pragma comment(lib,"DirectXTex_Debug.lib")
#else
#pragma comment(lib,"DirectXTex_Release.lib")
#endif
*/
#pragma warning(disable : 4996)
#pragma comment (lib, "Ws2_32.lib")//udp




//#include <windowsx.h>//udp
//#include <winsock2.h>//udp


#pragma warning(pop)

#define SCREEN_WIDTH	(1920)
#define SCREEN_HEIGHT	(1080)
#define MAX_RECORD 64 * 1024

//HWND �̎擾
HWND GetWindow();

//HWND �̎擾
HWND GetWndprccWindow();

//��
//void Invoke(std::function<void()> Function, int Time);


//�E�B���h�E��DPI�̎擾
float GetDPI();
//0�`1��float�^�̃����_���Ȑ�
float frand(void);

//D3dx9.lib���玝���Ă���
float D3DXVec3LengthSq(XMFLOAT3* pV);

//�J�[�\���̕\���̐؂�ւ�
//flug true     �J�[�\���̕\�����Ȃ���
//flug false    �J�[�\���̕\��������
void SetHideCursor(bool flug);

//�}�E�X�̉�ʒ����Œ�
//clip true     �����Œ�ON
//clip false    �����Œ�OFF
void MouseClip(bool clip);

//�}�E�X�|�C���^�̃E�B���h�E�ł̍��W�擾
XMFLOAT2 MousePos();

//�������͂��I���ɂ��Ď擾����
void GetInputTextString(std::string* t);
//�������͂����
void CloseInputTextString();

//2�o�C�g�����ɑΉ�����popback
void StdPopBack(std::string* t);

