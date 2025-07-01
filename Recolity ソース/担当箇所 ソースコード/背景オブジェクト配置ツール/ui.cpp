//=============================================================================
//
// ���[�U�[�C���^�[�t�F�[�X�\������ [ui.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "ui.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��

#define	SCALE_X			(57.0f * 3.0f)
#define	SCAlE_Y			(89.0f * 3.0f)

#define	NUM_VERTEX		(4)						// ���_��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���


//=============================================================================
// ����������
//=============================================================================
HRESULT InitUI(void)
{
	
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUI(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUI(void)
{
	CAMERA *cam = GetCamera();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUI(void)
{
	// ���C�g
	SetLightEnable(false);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	for (int i = 0; i < 5; i++)
	{
		//DrawScreen(&g_Card[i], g_TexNo);
	}


	// Z��r����
	SetDepthEnable(true);

	// ���C�g
	SetLightEnable(false);
}

//=============================================================================
// 2D���_�ݒ�
//=============================================================================
void DrawScreen2(UI2 pol,int tex)
{

	//�t�B���^�����O���[�h�F�|�C���g�t�B���^�i�t�B���^�����O�����@�s�N�Z�����������茩����j
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);
	// ���C�g
	SetLightEnable(false);
	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;


	float hw, hh;
	hw = pol.m_Scl.x * 0.5f;
	hh = pol.m_Scl.y * 0.5f;

	// ���W�ϊ�
	pVtx[0].Position.x = (-hw) * cosf(pol.m_Rot) - (-hh) * sinf(pol.m_Rot) + pol.m_Pos.x;
	pVtx[0].Position.y = (-hw) * sinf(pol.m_Rot) + (-hh) * cosf(pol.m_Rot) + pol.m_Pos.y;
	pVtx[1].Position.x = ( hw) * cosf(pol.m_Rot) - (-hh) * sinf(pol.m_Rot) + pol.m_Pos.x;
	pVtx[1].Position.y = ( hw) * sinf(pol.m_Rot) + (-hh) * cosf(pol.m_Rot) + pol.m_Pos.y;
	pVtx[2].Position.x = (-hw) * cosf(pol.m_Rot) - ( hh) * sinf(pol.m_Rot) + pol.m_Pos.x;
	pVtx[2].Position.y = (-hw) * sinf(pol.m_Rot) + ( hh) * cosf(pol.m_Rot) + pol.m_Pos.y;
	pVtx[3].Position.x = ( hw) * cosf(pol.m_Rot) - ( hh) * sinf(pol.m_Rot) + pol.m_Pos.x;
	pVtx[3].Position.y = ( hw) * sinf(pol.m_Rot) + ( hh) * cosf(pol.m_Rot) + pol.m_Pos.y;
	
	pVtx[0].Diffuse = D3DXCOLOR(pol.m_Color.r, pol.m_Color.g, pol.m_Color.b, pol.m_Color.a);
	pVtx[1].Diffuse = D3DXCOLOR(pol.m_Color.r, pol.m_Color.g, pol.m_Color.b, pol.m_Color.a);
	pVtx[2].Diffuse = D3DXCOLOR(pol.m_Color.r, pol.m_Color.g, pol.m_Color.b, pol.m_Color.a);
	pVtx[3].Diffuse = D3DXCOLOR(pol.m_Color.r, pol.m_Color.g, pol.m_Color.b, pol.m_Color.a);
	
	pVtx[0].TexCoord = D3DXVECTOR2(pol.m_Uv_v.x, pol.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(pol.m_Uv_v.x + pol.m_Uv_f.x, pol.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(pol.m_Uv_v.x, pol.m_Uv_v.y + pol.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(pol.m_Uv_v.x + pol.m_Uv_f.x, pol.m_Uv_v.y + pol.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));

	// ���[�U�[�C���^�[�t�F�[�X�`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

	// Z��r����
	SetDepthEnable(true);
}
