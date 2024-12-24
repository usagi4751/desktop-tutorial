//=============================================================================
//
// �J�������� [camera.cpp]
// Author :
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	POS_X_CAM		(0.0f)			// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(200.0f)		// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(-400.0f)		// �J�����̏����ʒu(Z���W)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(30000.0f)										// �r���[���ʂ�FarZ�l

#define	VALUE_MOVE_CAMERA	(20.0f)										// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// �J�����̉�]��

#define CAMERA_VEL		(10.0f)			//�J�����̈ړ����x
#define JUMP_VEL		(10.0f)			//�J�����̃W�����v���x

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CAMERA			g_Camera;		// �J�����f�[�^
CAMERA			g_oldCamera;		// �J�����f�[�^
POINT					g_Point;
POINT					g_oldPoint;
DIMOUSESTATE2			g_InitMouse;
DIMOUSESTATE2			g_CurrentMouse;
bool					g_JumpTrigger;
unsigned int			g_FrameCount;
float					g_Jumprot;


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

	//�}�E�X�̏�����
	g_InitMouse.lX = GetMouseX();
	g_InitMouse.lY = GetMouseY();
	g_InitMouse.lZ = GetMouseZ();
	g_CurrentMouse.lX = g_InitMouse.lX;
	g_CurrentMouse.lY = g_InitMouse.lY;
	g_CurrentMouse.lZ = g_InitMouse.lZ;

	//�}�E�X�̌��ݍ��W�̎擾
	GetCursorPos(&g_Point);
	g_oldPoint = g_Point;

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



	//�}�E�X�̎��_�ړ�����
	g_CurrentMouse.lX = GetMouseX();
	g_CurrentMouse.lY = GetMouseY();
	//TAB�������Ă���Ǝ��_����]���Ȃ��Ȃ�
	if (!GetKeyboardPress(DIK_TAB))
	{
		//����]
		if (g_CurrentMouse.lX != 0)
		{
			if (g_CurrentMouse.lX > 0)
			{
				g_Camera.rot.y += CameraMouse(g_CurrentMouse.lX, VALUE_MOUSE_RATE);
				if (g_Camera.rot.y > D3DX_PI)
				{
					g_Camera.rot.y -= D3DX_PI * 2.0f;
				}
			}
			else
			{
				g_Camera.rot.y -= CameraMouse(g_CurrentMouse.lX, VALUE_MOUSE_RATE);
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
				g_Camera.rot.x -= CameraMouse(g_CurrentMouse.lY, VALUE_MOUSE_RATE);
				if (g_Camera.rot.x < (-D3DX_PI / 2 + 0.01f))
				{
					g_Camera.rot.x = (-D3DX_PI / 2 + 0.01f);
				}
			}
			else
			{
				g_Camera.rot.x += CameraMouse(g_CurrentMouse.lY, VALUE_MOUSE_RATE);
				if (g_Camera.rot.x > (D3DX_PI / 2 - 0.01f))
				{
					g_Camera.rot.x = (D3DX_PI / 2 - 0.01f);
				}
			}

		}
	}

	//�����_�̃Z�b�g
	g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * cosf(g_Camera.rot.x) * g_Camera.len;
	g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * cosf(g_Camera.rot.x) * g_Camera.len;
	g_Camera.at.y = g_Camera.pos.y + sinf(g_Camera.rot.x) * g_Camera.len;

	//���_�ړ�
	if (GetKeyboardPress(DIK_W))
	{
		g_Camera.pos.z += CAMERA_VEL * cosf(g_Camera.rot.y);
		g_Camera.at.z += CAMERA_VEL * cosf(g_Camera.rot.y);

		g_Camera.pos.x += CAMERA_VEL * sinf(g_Camera.rot.y);
		g_Camera.at.x += CAMERA_VEL * sinf(g_Camera.rot.y);
	}
	if (GetKeyboardPress(DIK_S))
	{
		g_Camera.pos.z -= CAMERA_VEL * cosf(g_Camera.rot.y);
		g_Camera.at.z -= CAMERA_VEL * cosf(g_Camera.rot.y);

		g_Camera.pos.x -= CAMERA_VEL * sinf(g_Camera.rot.y);
		g_Camera.at.x -= CAMERA_VEL * sinf(g_Camera.rot.y);
	}
	if (GetKeyboardPress(DIK_A))
	{
		g_Camera.pos.z += CAMERA_VEL * sinf(g_Camera.rot.y);
		g_Camera.at.z += CAMERA_VEL * sinf(g_Camera.rot.y);

		g_Camera.pos.x -= CAMERA_VEL * cosf(g_Camera.rot.y);
		g_Camera.at.x -= CAMERA_VEL * cosf(g_Camera.rot.y);
	}
	if (GetKeyboardPress(DIK_D))
	{
		g_Camera.pos.z -= CAMERA_VEL * sinf(g_Camera.rot.y);
		g_Camera.at.z -= CAMERA_VEL * sinf(g_Camera.rot.y);

		g_Camera.pos.x += CAMERA_VEL * cosf(g_Camera.rot.y);
		g_Camera.at.x += CAMERA_VEL * cosf(g_Camera.rot.y);
	}
	if (GetKeyboardPress(DIK_SPACE))
	{
		g_Camera.pos.y += 10;
	}
	if (GetKeyboardPress(DIK_LCONTROL))
	{
		g_Camera.pos.y -= 10;
	}
	float brinc = 1000.0f;
	if (IsMouseSide4Triggered())
	{
		g_Camera.pos.x +=  sinf(g_Camera.rot.y) * cosf(g_Camera.rot.x) * brinc;
		g_Camera.pos.z += cosf(g_Camera.rot.y) * cosf(g_Camera.rot.x) * brinc;
		g_Camera.pos.y += sinf(g_Camera.rot.x) * brinc;


		g_Camera.at.x += sinf(g_Camera.rot.y) * cosf(g_Camera.rot.x) * brinc;
		g_Camera.at.z += cosf(g_Camera.rot.y) * cosf(g_Camera.rot.x) * brinc;
		g_Camera.at.y += sinf(g_Camera.rot.x) * brinc;
	}
	g_Camera.at.y = g_Camera.pos.y + sinf(g_Camera.rot.x) * g_Camera.len;




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


// �J�����̎��_�ƒ����_���Z�b�g
void SetCameraAT(D3DXVECTOR3 pos)
{
	// �J�����̒����_���v���C���[�̍��W�ɂ��Ă݂�
	g_Camera.at = pos;

	// �J�����̎��_���J������Y����]�ɑΉ������Ă���
	g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
	g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
}

float CameraMouse(long value, float rate)
{
	value = (long)fabs(value);
	rate = (float)fabs(rate);

	if (value > 360)
	{
		value = 360;
	}

	if (rate > 100)
	{
		rate = 100.0f;

	}


	rate /= 100.0f;
	return D3DXToRadian(value) * rate;

}