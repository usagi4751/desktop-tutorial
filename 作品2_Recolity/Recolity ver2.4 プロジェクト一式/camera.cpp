//=============================================================================
//
// �J�������� [camera.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "Game.h"
#include "input.h"
#include "card.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	POS_X_CAM		(0.0f)			// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(200.0f)		// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(-400.0f)		// �J�����̏����ʒu(Z���W)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(40000.0f)										// �r���[���ʂ�FarZ�l

#define	VALUE_MOVE_CAMERA	(20.0f)										// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// �J�����̉�]��

#define VALUE_MOUSE_RATE	(5.0f)		//�}�E�X�̈ړ��ʔ{��
#define CAMERA_VEL		(10.0f)			//�J�����̈ړ����x
#define JUMP_VEL		(10.0f)			//�J�����̃W�����v���x


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
float CameraMouse(long value, float rate);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAMERA			g_Camera;		// �J�����f�[�^
static CAMERA			g_oldCamera;		// �J�����f�[�^
POINT					g_Point;
POINT					g_oldPoint;
DIMOUSESTATE2			g_CurrentMouse;
bool					g_JumpTrigger;
unsigned int			g_FrameCount;
float					g_Jumprot;
float					g_MouseKando = 5.0f;

//=============================================================================
// ����������
//=============================================================================
void InitCamera(void)
{
	
	g_Camera.pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	g_Camera.at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_oldCamera = g_Camera;

	// ���_�ƒ����_�̋������v�Z
	float vx, vz;
	vx = g_Camera.pos.x - g_Camera.at.x;
	vz = g_Camera.pos.z - g_Camera.at.z;
	g_Camera.len = sqrtf(vx * vx + vz * vz);

	g_JumpTrigger = false;
	g_FrameCount = 0;
	g_Jumprot = D3DXToRadian(90);
}


//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}


//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	if (g_MouseKando < 0.1f)
	{
		g_MouseKando = 0.1f;
	}
	if (GetCardflug() == false)
	{
		//�}�E�X�̎��_�ړ�����
		g_CurrentMouse.lX = GetMouseX();
		g_CurrentMouse.lY = GetMouseY();
		//����]
		if (g_CurrentMouse.lX != 0)
		{
			if (g_CurrentMouse.lX > 0)
			{
				g_Camera.rot.y += CameraMouse(g_CurrentMouse.lX, g_MouseKando);
				if (g_Camera.rot.y > D3DX_PI)
				{
					g_Camera.rot.y -= D3DX_PI * 2.0f;
				}
			}
			else
			{
				g_Camera.rot.y -= CameraMouse(g_CurrentMouse.lX, g_MouseKando);
				if (g_Camera.rot.y < -D3DX_PI)
				{
					g_Camera.rot.y += D3DX_PI * 2.0f;
				}
			}
		}
		//�c��]
		if (g_CurrentMouse.lY != 0)
		{
			if (g_CurrentMouse.lY > 0)
			{
				g_Camera.rot.x -= CameraMouse(g_CurrentMouse.lY, g_MouseKando);
				if (g_Camera.rot.x < (-D3DX_PI / 2 + 0.01f))
				{
					g_Camera.rot.x = (-D3DX_PI / 2 + 0.01f);
				}
			}
			else
			{
				g_Camera.rot.x += CameraMouse(g_CurrentMouse.lY, g_MouseKando);
				if (g_Camera.rot.x > (D3DX_PI / 2 - 0.01f))
				{
					g_Camera.rot.x = (D3DX_PI / 2 - 0.01f);
				}
			}

		}



		g_Camera.pos = GetPlayer()->GetPos();
		g_Camera.pos.y = GetPlayer()->GetPos().y - (50.0f * (float)GetPlayer()->Get_Sneak());
		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * cosf(g_Camera.rot.x) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * cosf(g_Camera.rot.x) * g_Camera.len;
		g_Camera.at.y = g_Camera.pos.y + sinf(g_Camera.rot.x) * g_Camera.len;
	}
	

}


//=============================================================================
// �J�����̍X�V
//=============================================================================
void SetCamera(void) 
{
	// �r���[�}�g���b�N�X�ݒ�
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.pos, &g_Camera.at, &g_Camera.up);

	SetViewMatrix(&g_Camera.mtxView);
	

	float det;
	D3DXMatrixInverse(&g_Camera.mtxInvView, &det, &g_Camera.mtxView);


	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, 1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);

	SetProjectionMatrix(&g_Camera.mtxProjection);
}


//=============================================================================
// �J�����̎擾
//=============================================================================
CAMERA *GetCamera(void) 
{
	return &g_Camera;
}

//=============================================================================
// �J�����̎��_�ƒ����_���Z�b�g
//=============================================================================
void SetCameraAT(D3DXVECTOR3 pos)
{
	// �J�����̒����_���v���C���[�̍��W�ɂ��Ă݂�
	g_Camera.at = pos;

	// �J�����̎��_���J������Y����]�ɑΉ������Ă���
	g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
	g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
}

//=============================================================================
// �}�E�X���g�����J�����̈ړ�
// value	�ړ���
// rate		�{��
//=============================================================================
float CameraMouse(long value,float rate)
{
	value = (long)fabs(value);
	rate = (float)fabs(rate);

	if (value > 360)
	{
		value = 360;
	}
	if (rate > 100)
	{
		rate = 100;
	}

	rate /= 100.0f;

	return D3DXToRadian(value) * rate;
}


// �J�����ƑΛ������]�s����擾
D3DXMATRIX GetInvRotateMat()
{
	D3DXMATRIX Inv;
	D3DXVECTOR3 pos = D3DXVECTOR3(0, 0, 0);
	D3DXMatrixIdentity(&Inv);
	D3DXMatrixLookAtLH(&Inv, &pos, &g_Camera.at, &g_Camera.up);
	D3DXMatrixInverse(&Inv, NULL, &Inv);

	return Inv;
}

float* GetMouseKando() {
	return &g_MouseKando;
}