//=============================================================================
//
// ���C������ [main.cpp]
// Author : 
//
//=============================================================================
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "main.h"
#include "material.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "sound.h"
#include "scene.h"
#include "fade.h"
#include "sprite.h"
#include "text.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"Recolity"		// �E�C���h�E�̃L���v�V������
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
long g_MouseX = 0;
long g_MouseY = 0;
MSG g_msg;
HWND hWnd;
int obi = 0;
int cd = 0;
POINT p;
RECT rect;
D3DXVECTOR2 mosepos;
float g_Dpi;
bool corsorlock = false;
#ifdef _DEBUG
int		g_CountFPS;							// FPS�J�E���^
char	g_DebugStr[2048] = WINDOW_NAME;		// �f�o�b�O�����\���p

#endif


//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//���������[�N���m
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// ���Ԍv���p
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;


	//�����_���V�[�h�̏�����
	srand((unsigned int)time(NULL));

	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	int window_width = 960;
	int window_height = 540;

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// �E�B���h�E�̍����W
		CW_USEDEFAULT,																		// �E�B���h�E�̏���W
		window_width + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// �E�B���h�E����
		window_height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
		NULL,
		NULL,
		hInstance,
		NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	g_Dpi = (float)GetDpiForWindow(hWnd);

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	RECT wndrect;
	int cursornum = 0;
	// ���b�Z�[�W���[�v
	while(1)
	{
		obi = GetSystemMetrics(SM_CYCAPTION);
		GetWindowRect(hWnd, &wndrect);
		if (corsorlock)
		{
			SetCursorPos((int)((wndrect.right - wndrect.left) * 0.5) + wndrect.left, (int)((wndrect.bottom - wndrect.top) * 0.5) + wndrect.top);
			if (cursornum >= 0)
			{
				cursornum = ShowCursor(false);
			}
			
		}
		else
		{
			if (cursornum < 0)
			{
				cursornum = ShowCursor(true);
			}
			
		}

        if(PeekMessage(&g_msg, NULL, 0, 0, PM_REMOVE))
		{
			if(g_msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&g_msg);
				DispatchMessage(&g_msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

#ifdef _DEBUG	// �f�o�b�O�ł̎�����FPS��\������
				wsprintf(g_DebugStr, WINDOW_NAME);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
#endif
				GetWindowRect(hWnd, &rect);
				GetCursorPos(&p);
				Update();			// �X�V����
				Draw();				// �`�揈��
				cd > 0 ? cd-- : cd = 0;

				CheckScene();
				


#ifdef _DEBUG	// �f�o�b�O�ł̎������\������
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], "windowRECT top%dbottom%dleft%dright%d", wndrect.top, wndrect.bottom, wndrect.left, wndrect.right);
				SetWindowText(hWnd, g_DebugStr);
#endif

				dwFrameCount++;
			}
		}
	}

	timeEndPeriod(1);				// ����\��߂�

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();
	return (int)g_msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_F5:
			DestroyWindow(hWnd);
			break;
		}
		break;

	case WM_MOUSEMOVE:
		g_MouseX = LOWORD(lParam);
		g_MouseY = HIWORD(lParam);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	InitRenderer(hInstance, hWnd, bWindow);
	InitInput(hInstance, hWnd);
	InitSound(hWnd);
	LoadMaterial();
	InitSprite();
	InitFade();
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);
	SetCullingMode(CULL_MODE_BACK);
	SetFadeColor(0.0f, 0.0f, 0.0f);
	SceneFadeIn(SCENE_TITLE);
	ShowCursor(false);
	InitText();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	UninitText();
	UninitScene();
	ShowCursor(true);
	UninitFade();
	UninitTexture();
	UninitSprite();
	UninitSound();
	ReleaseMaterial();
	UninitInput();
	UninitRenderer();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// ���͂̍X�V����
	UpdateInput();
	
	UpdateScene();

}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@�N���A
	Clear();

	// �V�[���̕`�揈��
	DrawScene();

	// �o�b�N�o�b�t�@�A�t�����g�o�b�t�@����ւ�
	Present();
}


long GetMousePosX(void)
{
	return g_MouseX;
}


long GetMousePosY(void)
{
	return g_MouseY;
}


#ifdef _DEBUG
char* GetDebugStr(void)
{
	return g_DebugStr;
}
MSG* GetMsg() {
	return &g_msg;
}
#endif
float frand(void)
{

	return (float)rand() / RAND_MAX;
}
void CursprLock(bool swith) {
	corsorlock = swith;
}
D3DXVECTOR2 GetMousePos() {

	mosepos.x = (float)p.x * SCREEN_WIDTH / (rect.right - rect.left) - rect.left * 2;
	mosepos.y = (float)p.y * SCREEN_HEIGHT / (rect.bottom ) - rect.top * 2;

	return mosepos;
}

bool WndYesorNo(std::string text) {
	if (cd == 0)
	{
		cd = 2;
		return MessageBox(hWnd, (LPCTSTR)text.c_str(), "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK;
	}
	return false;
}
float GeyDPI() {
	return (float)GetDpiForWindow(hWnd);
}