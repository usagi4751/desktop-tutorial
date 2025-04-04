#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include "main.h"
#include "manager.h"
#include <thread>
#include "resource.h"
#include "input.h"
#include "timeapi.h"
#include "ServerManager.h"
#include <nlohmann/json.hpp>
const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "ArcaneRabbit";

//ウィンドウに対しての文字の入力処理
//in WPARAM wParam
//out std::string* instring
void InputChar(WPARAM wParam, std::string* instring);



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



int		g_CountFPS;				// FPS表示用
char	g_DebugStr[2048];		// FPS表示用
bool	g_mouseclip  = false;
bool	g_ShowCursorFlig = false;//カーソル表示非表示bool
HWND g_Window;
HWND g_WndprcWindow;
POINT mousepoint;
RECT rect;//ウィンドウRECT

//前のフレームにIMEの予測がONになっていたか
bool Old_IME_Input = false;
//入力した文字のストック1度使うと消される
std::string* IME_String;
//文字編集してるかのフラグ
bool MOZIHENNSYUU_flug = false;

HWND GetWindow()
{
	return g_Window;
}

HWND GetWndprccWindow()
{
	return g_WndprcWindow;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//メモリリーク検知
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//ランダムシードの初期化
	DWORD dwFrameCount;
	srand((unsigned int)time(NULL));
	WNDCLASSEX wcex;
	{
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = 0;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = (HICON)LoadImageA(hInstance, MAKEINTRESOURCE(IDI_MAINICONEX), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
		wcex.hCursor = nullptr;
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm = nullptr;

		RegisterClassEx(&wcex);

		float windx = 960;
		float windy = 540;

		g_Window = CreateWindowEx(
			0, 
			CLASS_NAME, 
			WINDOW_NAME, 
			WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT, 
			CW_USEDEFAULT,
			windx +GetSystemMetrics(SM_CXDLGFRAME) * 2,
			windy + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
			nullptr, 
			nullptr, 
			hInstance, 
			nullptr);
	}

	CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);


	Manager::Init();
	Input::Init(hInstance, g_Window);


	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);


	//タイトルバーを消す
	SetWindowLongPtr(g_Window, GWL_STYLE, WS_VISIBLE | WS_POPUP);
	//ウィンドウの位置をずらす
	MoveWindow(g_Window, 0,
		0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN), TRUE);

	DWORD dwFPSLastTime;
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = 0;
	dwCurrentTime = dwFrameCount = 0;
	LPCTSTR cursor = MAKEINTRESOURCE(32512);
	SetCursor(LoadCursor(NULL, cursor));
	MSG msg;
	int cursornum = 0;
	while(1)
	{
		
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 1000) {
				g_CountFPS = dwFrameCount;
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;		
				
			}
			
			
			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
			
				dwExecLastTime = dwCurrentTime;
				GetWindowRect(g_Window, &rect);
				GetCursorPos(&mousepoint);
				if (g_mouseclip == false || GetForegroundWindow() != g_Window)
				{
					SetHideCursor(false);
					ClipCursor(NULL);
				}
				else
				{
					SetHideCursor(true);
					ClipCursor(&rect);
				}
				Manager::Update();
				Manager::Draw();
				// デバッグ版の時だけ表示する
					wsprintf(g_DebugStr, "");
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(g_Window, g_DebugStr);
				dwFrameCount++;
			}

			
		}
	}

	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Manager::Uninit();

	CoUninitialize();

	return (int)msg.wParam;
}


//====================
//WSAAsyncSelectこれ

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


	g_WndprcWindow = hWnd;
	int nEvent;//ウィンドウに届いたイベント
	int aa = FD_READ;
	switch(uMsg)
	{
	case MY_MSG:
		nEvent = WSAGETSELECTEVENT(lParam);//LPARAMをWinsokのイベントに変換
		switch (nEvent)
		{
		case FD_READ://データが届いた時
			ServerManager::RecvMassage();
			break;
		default:
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		InputChar(wParam, IME_String);
		switch(wParam)
		{
		case VK_BACK:
			StdPopBack(IME_String);
			break;
		case VK_F5:
			int id;
			
			SetHideCursor(false);
			ClipCursor(NULL);
			g_mouseclip = false;
			id = MessageBox(NULL, TEXT("ゲームを閉じますか?"),
				TEXT(""), MB_OKCANCEL | MB_ICONQUESTION);

			switch (id)
			{
			case IDOK:
				DestroyWindow(hWnd);
				break;
			case IDCANCEL:
				MessageBox(NULL, TEXT("[キャンセル] しました"),
					TEXT("結果"), MB_ICONINFORMATION);
				break;
			}
	
			break;
		case VK_ESCAPE:DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_IME_COMPOSITION:
		Old_IME_Input = true;
		MOZIHENNSYUU_flug = true;

		break;
	case WM_IME_ENDCOMPOSITION:
		if (Old_IME_Input == true )
		{
			Old_IME_Input = false;
			HIMC hImc;
			ImmGetContext(g_Window);//HIMCを取得
			hImc = ImmGetContext(g_Window);//HIMCを取得
			bool IMEOpen = ImmGetOpenStatus(hImc);
		
			if (IMEOpen && IME_String != nullptr) {
				char chtext[512];
				ImmSetOpenStatus(hImc, TRUE);
				memset(chtext, '\0', 512);
				ImmGetCompositionString(hImc, GCS_RESULTSTR, chtext, 512);
				std::string rentext(chtext);
				*IME_String += rentext;
			}
		}
		MOZIHENNSYUU_flug = false;
	break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

float GetDPI() { return (float)GetDpiForWindow(g_Window); }
float frand(void) { return (float)rand() / RAND_MAX; }

float D3DXVec3LengthSq(XMFLOAT3* pV)
{
	return pV->x * pV->x + pV->y * pV->y + pV->z * pV->z;
};
void MouseClip(bool clip) { 
	g_mouseclip = clip; }




void InputChar(WPARAM wParam, std::string* instring)
{
	if (instring == nullptr)
	{
		return;
	}
	if (instring->size() > 511)
	{
		return;
	}
	//シフトの取得文字入力に使う
	int IsShiftNumber = 0;
	int IsShiftEnglish = 0;
	if (Input::GetKeyPress(VK_RSHIFT) || Input::GetKeyPress(VK_LSHIFT))
	{
		IsShiftEnglish = 32;
		IsShiftNumber = 16;
	}
	switch (wParam)
	{
	case VK_SPACE:*instring += ' '; break;
	case '0':*instring += '0'; break;
	case '1':*instring += '1' - IsShiftNumber; break;
	case '2':*instring += '2' - IsShiftNumber; break;
	case '3':*instring += '3' - IsShiftNumber; break;
	case '4':*instring += '4' - IsShiftNumber; break;
	case '5':*instring += '5' - IsShiftNumber; break;
	case '6':*instring += '6' - IsShiftNumber; break;
	case '7':*instring += '7' - IsShiftNumber; break;
	case '8':*instring += '8' - IsShiftNumber; break;
	case '9':*instring += '9' - IsShiftNumber; break;
	case 'A':*instring += 'a' - IsShiftEnglish; break;
	case 'B':*instring += 'b' - IsShiftEnglish; break;
	case 'C':*instring += 'c' - IsShiftEnglish; break;
	case 'D':*instring += 'd' - IsShiftEnglish; break;
	case 'E':*instring += 'e' - IsShiftEnglish; break;
	case 'F':*instring += 'f' - IsShiftEnglish; break;
	case 'G':*instring += 'g' - IsShiftEnglish; break;
	case 'H':*instring += 'h' - IsShiftEnglish; break;
	case 'I':*instring += 'i' - IsShiftEnglish; break;
	case 'J':*instring += 'j' - IsShiftEnglish; break;
	case 'K':*instring += 'k' - IsShiftEnglish; break;
	case 'L':*instring += 'l' - IsShiftEnglish; break;
	case 'M':*instring += 'm' - IsShiftEnglish; break;
	case 'N':*instring += 'n' - IsShiftEnglish; break;
	case 'O':*instring += 'o' - IsShiftEnglish; break;
	case 'P':*instring += 'p' - IsShiftEnglish; break;
	case 'Q':*instring += 'q' - IsShiftEnglish; break;
	case 'R':*instring += 'r' - IsShiftEnglish; break;
	case 'S':*instring += 's' - IsShiftEnglish; break;
	case 'T':*instring += 't' - IsShiftEnglish; break;
	case 'U':*instring += 'u' - IsShiftEnglish; break;
	case 'V':*instring += 'v' - IsShiftEnglish; break;
	case 'W':*instring += 'w' - IsShiftEnglish; break;
	case 'X':*instring += 'x' - IsShiftEnglish; break;
	case 'Y':*instring += 'y' - IsShiftEnglish; break;
	case 'Z':*instring += 'z' - IsShiftEnglish; break;
	case 190:*instring += '.'; break;
	default:
		break;
	}

}

void SetHideCursor(bool flug) {
	//flugがtrueなら表示しないfalseなら表示する
	if (g_ShowCursorFlig != flug)
	{
	g_ShowCursorFlig = flug;
	// マウス情報の取得
	//ci.flags    カーソルが表示されているかのフラグ
		CURSORINFO ci = { sizeof(CURSORINFO) };
		GetCursorInfo(&ci);
		if (flug == true && ci.flags == true)
		{
			int ShowCursorNum = ShowCursor(false);
			while (ShowCursorNum > -1)
			{
				ShowCursorNum = ShowCursor(false);
			}
		}

		if (flug == false && ci.flags == false)
		{
			int ShowCursorNum = ShowCursor(true);
			while (ShowCursorNum < -1)
			{
				ShowCursorNum = ShowCursor(true);
			}
		}
	}
	


};
XMFLOAT2 MousePos()
{
	XMFLOAT2 mousepos;
	mousepos.x = (float)mousepoint.x * SCREEN_WIDTH / (rect.right - rect.left) - rect.left * 2;
	mousepos.y = (float)mousepoint.y * SCREEN_HEIGHT / (rect.bottom - rect.top) - rect.top * 2;

	return mousepos;
}

void GetInputTextString(std::string* t)
{
	IME_String = t;
}

void CloseInputTextString()
{
	IME_String = nullptr;
}

void StdPopBack(std::string* t)
{
	if (t == nullptr) {
		return;
	}
	//テキストのサイズ
	int size = t->size();
	//最後の2バイト文字の場所
	int LargeChr = 0;
	//index
	int num = 0;
	while (num < size)
	{
		if (num >= LargeChr)
		{
			if (t->at(num) < 0)
			{
				LargeChr = num + 2;
			}
		}


		num++;
	}
	if (size > 1)
	{

		if ((t->at(size - 2) < 0) && size - 2 != LargeChr - 1)
		{
			t->pop_back();
			t->pop_back();
		}
		else
		{
			t->pop_back();
		}

	}
	else if (size > 0)
	{
		t->pop_back();
	}
}
