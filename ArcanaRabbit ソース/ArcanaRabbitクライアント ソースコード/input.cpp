

#include "input.h"
#include "material.h"



BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];

DIMOUSESTATE2 Input::mouseState;
DIMOUSESTATE2 Input::mouseTrigger;

LPDIRECTINPUT8 Input::g_pDInput;
LPDIRECTINPUTDEVICE8 Input::pMouse;

XMFLOAT2 Input::m_nowmousepointer;
bool Input::m_DrawMouseFlag;
void Input::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if (!g_pDInput)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&g_pDInput, NULL);
	}
	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );

	 //�}�E�X�̏�����
	InitializeMouse(hInst, hWnd);
}

void Input::Uninit()
{
	// �}�E�X�̏I������
	UninitMouse();

}

void Input::Update()
{

	memcpy( m_OldKeyState, m_KeyState, 256 );

	GetKeyboardState( m_KeyState );

	// �}�E�X�̍X�V
	UpdateMouse();
}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}







//=============================================================================
// �}�E�X�֌W�̏���
//=============================================================================
// �}�E�X�̏�����
HRESULT Input::InitializeMouse(HINSTANCE hInst, HWND hWindow)
{
	HRESULT result;
	// �f�o�C�X�쐬
	result = g_pDInput->CreateDevice(GUID_SysMouse, &pMouse, NULL);
	if (FAILED(result) || pMouse == NULL)
	{
		MessageBox(hWindow, "No mouse", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}
	// �f�[�^�t�H�[�}�b�g�ݒ�
	result = pMouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(result))
	{
		MessageBox(hWindow, "Can't setup mouse", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}
	// ���̃A�v���Ƌ������[�h�ɐݒ�
	result = pMouse->SetCooperativeLevel(hWindow, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(result))
	{
		MessageBox(hWindow, "Mouse mode error", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD prop;

	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = DIPROPAXISMODE_REL;		// �}�E�X�̈ړ��l�@���Βl

	result = pMouse->SetProperty(DIPROP_AXISMODE, &prop.diph);
	if (FAILED(result))
	{
		MessageBox(hWindow, "Mouse property error", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}

	// �A�N�Z�X���𓾂�
	pMouse->Acquire();
	return result;
}

//---------------------------------------------------------
void Input::UninitMouse()
{
	if (pMouse)
	{
		pMouse->Unacquire();
		pMouse->Release();
		pMouse = NULL;
	}

}
//-----------------------------------------------------------
HRESULT Input::UpdateMouse()
{
	HRESULT result;
	// �O��̒l�ۑ�
	DIMOUSESTATE2 lastMouseState = mouseState;
	// �f�[�^�擾
	result = pMouse->GetDeviceState(sizeof(mouseState), &mouseState);
	if (SUCCEEDED(result))
	{
		mouseTrigger.lX = mouseState.lX;
		mouseTrigger.lY = mouseState.lY;
		mouseTrigger.lZ = mouseState.lZ;
		// �}�E�X�̃{�^�����
		for (int i = 0; i < 8; i++)
		{
			mouseTrigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^
				mouseState.rgbButtons[i]) & mouseState.rgbButtons[i]);
		}
	}
	else	// �擾���s
	{
		// �A�N�Z�X���𓾂Ă݂�
		result = pMouse->Acquire();
	}
	m_nowmousepointer.x = MousePos().x;
	m_nowmousepointer.y = MousePos().y;
	if (m_nowmousepointer.x < 0)
	{
		m_nowmousepointer.x = 0;
	}
	if (m_nowmousepointer.y < 0)
	{
		m_nowmousepointer.y = 0;
	}
	if (m_nowmousepointer.x > 1920)
	{
		m_nowmousepointer.x = 1920;
	}
	if (m_nowmousepointer.y > 1080)
	{
		m_nowmousepointer.y = 1080;
	}
	if (m_DrawMouseFlag  ==true)
	{
		//Draw2d::SetUI(GetImage().m_System_Cursor, { 1.0f,1.0f ,1.0f ,1.0f }, { m_nowmousepointer.x + 32.0f ,m_nowmousepointer.y + 32.0f }, { 64,64 }, { 0.0f,0.0f }, { 1.0f,1.0f }, { 0.0f,0.0f }, 0.0f, 50.0f);
	}
	
	//Draw2d::SetText("x" + std::to_string(m_nowmousepointer.x) + "y" + std::to_string(m_nowmousepointer.y), { 0,180,10000,10000 }, 30, { 1.0f,1.0f ,1.0f ,1.0f }, 3.0f);
	return result;

}