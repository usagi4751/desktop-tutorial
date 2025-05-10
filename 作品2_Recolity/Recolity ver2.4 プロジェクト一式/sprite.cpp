//=============================================================================
//
// �X�v���C�g���� [sprite.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "base_object.h"
#include "sprite.h"
#include "renderer.h"
#include "Texture.h"
#include "camera.h"
#include "material.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_2DVERTEX		(4)							// ���_��
#define CIRCLE_VERTEX		360							// �T�[�N�����_��
#define CIRCLE_INDEX		360*3						// �T�[�N������


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;	// ���_���
static ID3D11Buffer* g_IndexBuffer = NULL; // �C���f�b�N�X���

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSprite(void)
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_2DVERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	// �C���f�b�N�X�o�b�t�@����
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned short) * CIRCLE_INDEX;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_IndexBuffer);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSprite(void)
{
	//	�C���f�b�N�X�o�b�t�@�̉��
	if (g_IndexBuffer) {
		g_IndexBuffer->Release();
		g_IndexBuffer = NULL;
	}

	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}


//=============================================================================
// ��ʕ`��(���S�w��)
//=============================================================================
void DrawScreen(UI& ui, int& tex)
{

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;


	float hw, hh;
	hw = ui.m_Scl.x * 0.5f;
	hh = ui.m_Scl.y * 0.5f;

	// ���W�ϊ�
	pVtx[0].Position.x = (-hw) * cosf(ui.m_Rot) - (-hh) * sinf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[0].Position.y = (-hw) * sinf(ui.m_Rot) + (-hh) * cosf(ui.m_Rot) + ui.m_Pos.y;
	pVtx[1].Position.x = (hw)*cosf(ui.m_Rot) - (-hh) * sinf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[1].Position.y = (hw)*sinf(ui.m_Rot) + (-hh) * cosf(ui.m_Rot) + ui.m_Pos.y;
	pVtx[2].Position.x = (-hw) * cosf(ui.m_Rot) - (hh)*sinf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[2].Position.y = (-hw) * sinf(ui.m_Rot) + (hh)*cosf(ui.m_Rot) + ui.m_Pos.y;
	pVtx[3].Position.x = (hw)*cosf(ui.m_Rot) - (hh)*sinf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[3].Position.y = (hw)*sinf(ui.m_Rot) + (hh)*cosf(ui.m_Rot) + ui.m_Pos.y;

	pVtx[0].Diffuse = D3DXCOLOR(ui.m_Color.r, ui.m_Color.g, ui.m_Color.b, ui.m_Color.a);
	pVtx[1].Diffuse = D3DXCOLOR(ui.m_Color.r, ui.m_Color.g, ui.m_Color.b, ui.m_Color.a);
	pVtx[2].Diffuse = D3DXCOLOR(ui.m_Color.r, ui.m_Color.g, ui.m_Color.b, ui.m_Color.a);
	pVtx[3].Diffuse = D3DXCOLOR(ui.m_Color.r, ui.m_Color.g, ui.m_Color.b, ui.m_Color.a);

	pVtx[0].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x, ui.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x + ui.m_Uv_f.x, ui.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x, ui.m_Uv_v.y + ui.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x + ui.m_Uv_f.x, ui.m_Uv_v.y + ui.m_Uv_f.y);

	pVtx[0].Normal = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f,0.0f,-1.0f);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT	 stride = sizeof(VERTEX_3D);
	UINT	 offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));

	// �}�e���A���̃Z�b�g
	MATERIAL mtl;
	mtl.Diffuse = {0.0f,0.0f,0.0f,1.0f};
	mtl.Ambient = {0.0f,0.0f,0.0f,1.0f};
	mtl.Emission = ui.m_Color;
	mtl.noTexSampling = 0;
	SetMaterial(mtl);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	// Z��r����
	SetDepthEnable(true);
}

//=============================================================================
// ��ʕ`��(����w��)
//=============================================================================
void DrawScreenLT(UI& ui, int& tex)
{

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;


	float hw, hh;
	hw = ui.m_Scl.x;
	hh = ui.m_Scl.y;

	// ���W�ϊ�
	pVtx[0].Position.x = ui.m_Pos.x;
	pVtx[0].Position.y = ui.m_Pos.y;
	pVtx[1].Position.x = (hw)*cosf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[1].Position.y = (hw)*sinf(ui.m_Rot) + ui.m_Pos.y;
	pVtx[2].Position.x = - (hh)*sinf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[2].Position.y = + (hh)*cosf(ui.m_Rot) + ui.m_Pos.y;
	pVtx[3].Position.x = (hw)*cosf(ui.m_Rot) - (hh)*sinf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[3].Position.y = (hw)*sinf(ui.m_Rot) + (hh)*cosf(ui.m_Rot) + ui.m_Pos.y;

	pVtx[0].Diffuse = D3DXCOLOR(ui.m_Color.r, ui.m_Color.g, ui.m_Color.b, ui.m_Color.a);
	pVtx[1].Diffuse = D3DXCOLOR(ui.m_Color.r, ui.m_Color.g, ui.m_Color.b, ui.m_Color.a);
	pVtx[2].Diffuse = D3DXCOLOR(ui.m_Color.r, ui.m_Color.g, ui.m_Color.b, ui.m_Color.a);
	pVtx[3].Diffuse = D3DXCOLOR(ui.m_Color.r, ui.m_Color.g, ui.m_Color.b, ui.m_Color.a);

	pVtx[0].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x, ui.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x + ui.m_Uv_f.x, ui.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x, ui.m_Uv_v.y + ui.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x + ui.m_Uv_f.x, ui.m_Uv_v.y + ui.m_Uv_f.y);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT	 stride = sizeof(VERTEX_3D);
	UINT	 offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));

	// �}�e���A���̃Z�b�g
	MATERIAL mtl;
	mtl.Diffuse = { 0.0f,0.0f,0.0f,1.0f };
	mtl.Ambient = { 0.0f,0.0f,0.0f,1.0f };
	mtl.Emission = ui.m_Color;
	mtl.noTexSampling = 0;
	SetMaterial(mtl);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	// Z��r����
	SetDepthEnable(true);

}

//=============================================================================
// �|���S���`��(���S���w��)
//=============================================================================
void DrawPolygon(Base_Object& obj,const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, obj.RefScl().y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, obj.RefScl().y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���`��(���S�w��)
//=============================================================================
void DrawPolygonCR(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, obj.RefScl().y * 0.5f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, obj.RefScl().y * 0.5f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, -obj.RefScl().y * 0.5f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, -obj.RefScl().y * 0.5f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);

}

//=============================================================================
// �|���S���`��(����w��)
//=============================================================================
void DrawPolygonLT(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x, 0.0f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(0.0f, -obj.RefScl().y, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x, -obj.RefScl().y, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���r���{�[�h�`��(���S���w��)
//=============================================================================
void DrawPolygonBill(Base_Object& obj,const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, obj.RefScl().y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, obj.RefScl().y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	CAMERA* pCam = GetCamera();
	//�r���[�}�g���b�N�X�̋t�s����擾
	*obj.GetMtx() = pCam->mtxInvView;
	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
//=============================================================================
// �|���S���r���{�[�h�`��(���S�w��)
//	X�����ɐL�тĂ����r���{�[�h
//=============================================================================

void DrawPolygonBillX(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f, float WID_X)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f + WID_X, obj.RefScl().y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f + WID_X, obj.RefScl().y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f + WID_X, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f + WID_X, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	CAMERA* pCam = GetCamera();
	//�r���[�}�g���b�N�X�̋t�s����擾
	*obj.GetMtx() = pCam->mtxInvView;
	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���r���{�[�h�`��(���S�w��)
//=============================================================================
void DrawPolygonBillCR(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, obj.RefScl().y * 0.5f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, obj.RefScl().y * 0.5f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, -obj.RefScl().y * 0.5f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, -obj.RefScl().y * 0.5f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	CAMERA* pCam = GetCamera();
	//�r���[�}�g���b�N�X�̋t�s����擾
	*obj.GetMtx() = pCam->mtxInvView;
	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���r���{�[�h�`��(����w��)
//=============================================================================
void DrawPolygonBillLT(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x, 0.0f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(0.0f, -obj.RefScl().y, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x, -obj.RefScl().y, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	CAMERA* pCam = GetCamera();
	//�r���[�}�g���b�N�X�̋t�s����擾
	*obj.GetMtx() = pCam->mtxInvView;
	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���r���{�[�h�`��(���S���w��)
//=============================================================================
void DrawPolygonAnyBill(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f, bool InX, bool InY, bool InZ)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, obj.RefScl().y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, obj.RefScl().y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	CAMERA* pCam = GetCamera();
	//�C�ӂ̎��̓]�u�s��
	if (InX)
	{
		obj.GetMtx()->_11 = pCam->mtxView._11;
		obj.GetMtx()->_12 = pCam->mtxView._21;
		obj.GetMtx()->_13 = pCam->mtxView._31;
	}
	if (InY)
	{
		obj.GetMtx()->_21 = pCam->mtxView._12;
		obj.GetMtx()->_22 = pCam->mtxView._22;
		obj.GetMtx()->_23 = pCam->mtxView._32;
	}
	if (InZ)
	{
		obj.GetMtx()->_31 = pCam->mtxView._13;
		obj.GetMtx()->_32 = pCam->mtxView._23;
		obj.GetMtx()->_33 = pCam->mtxView._33;
	}


	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���r���{�[�h�`��(���S�w��)
//=============================================================================
void DrawPolygonAnyBillCR(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f, bool InX, bool InY, bool InZ)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, obj.RefScl().y * 0.5f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, obj.RefScl().y * 0.5f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, -obj.RefScl().y * 0.5f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, -obj.RefScl().y * 0.5f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	CAMERA* pCam = GetCamera();
	//�C�ӂ̎��̓]�u�s��
	if (InX)
	{
		obj.GetMtx()->_11 = pCam->mtxView._11;
		obj.GetMtx()->_12 = pCam->mtxView._21;
		obj.GetMtx()->_13 = pCam->mtxView._31;
	}
	if (InY)
	{
		obj.GetMtx()->_21 = pCam->mtxView._12;
		obj.GetMtx()->_22 = pCam->mtxView._22;
		obj.GetMtx()->_23 = pCam->mtxView._32;
	}
	if (InZ)
	{
		obj.GetMtx()->_31 = pCam->mtxView._13;
		obj.GetMtx()->_32 = pCam->mtxView._23;
		obj.GetMtx()->_33 = pCam->mtxView._33;
	}


	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���r���{�[�h�`��(����w��)
//=============================================================================
void DrawPolygonAnyBillLT(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f, bool InX, bool InY, bool InZ)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x, 0.0f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(0.0f, -obj.RefScl().y, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x, -obj.RefScl().y, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	CAMERA* pCam = GetCamera();
	//�C�ӂ̎��̓]�u�s��
	if (InX)
	{
		obj.GetMtx()->_11 = pCam->mtxView._11;
		obj.GetMtx()->_12 = pCam->mtxView._21;
		obj.GetMtx()->_13 = pCam->mtxView._31;
	}
	if (InY)
	{
		obj.GetMtx()->_21 = pCam->mtxView._12;
		obj.GetMtx()->_22 = pCam->mtxView._22;
		obj.GetMtx()->_23 = pCam->mtxView._32;
	}
	if (InZ)
	{
		obj.GetMtx()->_31 = pCam->mtxView._13;
		obj.GetMtx()->_32 = pCam->mtxView._23;
		obj.GetMtx()->_33 = pCam->mtxView._33;
	}


	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// ���f���`��
//=============================================================================
void Draw3DModel(Base_Object& obj, DX11_MODEL& model)
{
	// �}�e���A���ݒ�
	SetMaterial(*obj.GetMaterial());

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &model.VertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	GetDeviceContext()->IASetIndexBuffer(model.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
	D3DXMatrixIdentity(obj.GetMtx());

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.RefScl().x, obj.RefScl().y, obj.RefScl().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	for (unsigned short i = 0; i < model.SubsetNum; i++)
	{

		// �e�N�X�`���ݒ�
		if (model.SubsetArray[i].Material.Material.noTexSampling == 0)
			GetDeviceContext()->PSSetShaderResources(0, 1, &model.SubsetArray[i].Material.Texture);

		// �|���S���`��
		GetDeviceContext()->DrawIndexed(model.SubsetArray[i].IndexNum, model.SubsetArray[i].StartIndex, 0);
	}
}

//---------------------------------
// �f�o�b�N�p
//---------------------------------
void DrawPolygon(Object& obj, const int& tex)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, obj.m_Scl.y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, obj.m_Scl.y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonCR(Object& obj, const int& tex)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, -obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, -obj.m_Scl.y * 0.5f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonLT(Object& obj, const int& tex)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x, 0.0f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(0.0f, -obj.m_Scl.y, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x, -obj.m_Scl.y, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonBill(Object& obj, const int& tex)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, obj.m_Scl.y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, obj.m_Scl.y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	CAMERA* pCam = GetCamera();
	//�r���[�}�g���b�N�X�̋t�s����擾
	obj.m_Mtx = pCam->mtxInvView;
	obj.m_Mtx._41 = 0.0f;
	obj.m_Mtx._42 = 0.0f;
	obj.m_Mtx._43 = 0.0f;



	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonBillX(Object& obj, const int& tex, float WID_X) {
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f + WID_X, obj.m_Scl.y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f + WID_X, obj.m_Scl.y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f + WID_X, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f + WID_X, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	CAMERA* pCam = GetCamera();
	//�r���[�}�g���b�N�X�̋t�s����擾
	obj.m_Mtx = pCam->mtxInvView;
	obj.m_Mtx._41 = 0.0f;
	obj.m_Mtx._42 = 0.0f;
	obj.m_Mtx._43 = 0.0f;

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXVECTOR3 range = { 0.0f,0.0f,0.0f };
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonBillXY(Object& obj, const int& tex, float WID_X , float WID_Y) {
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f + WID_X, obj.m_Scl.y + WID_Y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f + WID_X, obj.m_Scl.y + WID_Y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f + WID_X, 0.0f + WID_Y, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f + WID_X, 0.0f + WID_Y, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	CAMERA* pCam = GetCamera();
	//�r���[�}�g���b�N�X�̋t�s����擾
	obj.m_Mtx = pCam->mtxInvView;
	obj.m_Mtx._41 = 0.0f;
	obj.m_Mtx._42 = 0.0f;
	obj.m_Mtx._43 = 0.0f;

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXVECTOR3 range = { 0.0f,0.0f,0.0f };
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonBillCR(Object& obj, const int& tex)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, -obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, -obj.m_Scl.y * 0.5f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	CAMERA* pCam = GetCamera();
	//�r���[�}�g���b�N�X�̋t�s����擾
	obj.m_Mtx = pCam->mtxInvView;
	obj.m_Mtx._41 = 0.0f;
	obj.m_Mtx._42 = 0.0f;
	obj.m_Mtx._43 = 0.0f;



	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonBillLT(Object& obj, const int& tex)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x, 0.0f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(0.0f, -obj.m_Scl.y, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x, -obj.m_Scl.y, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	CAMERA* pCam = GetCamera();
	//�r���[�}�g���b�N�X�̋t�s����擾
	obj.m_Mtx = pCam->mtxInvView;
	obj.m_Mtx._41 = 0.0f;
	obj.m_Mtx._42 = 0.0f;
	obj.m_Mtx._43 = 0.0f;

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonAnyBill(Object& obj, const int& tex, bool InX, bool InY, bool InZ)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, obj.m_Scl.y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, obj.m_Scl.y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	CAMERA* pCam = GetCamera();
	//�C�ӂ̎��̓]�u�s��
	if (InX)
	{
		obj.m_Mtx._11 = pCam->mtxView._11;
		obj.m_Mtx._12 = pCam->mtxView._21;
		obj.m_Mtx._13 = pCam->mtxView._31;
	}
	if (InY)
	{
		obj.m_Mtx._21 = pCam->mtxView._12;
		obj.m_Mtx._22 = pCam->mtxView._22;
		obj.m_Mtx._23 = pCam->mtxView._32;
	}
	if (InZ)
	{
		obj.m_Mtx._31 = pCam->mtxView._13;
		obj.m_Mtx._32 = pCam->mtxView._23;
		obj.m_Mtx._33 = pCam->mtxView._33;
	}

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonAnyBillCR(Object& obj, const int& tex, bool InX, bool InY, bool InZ)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, -obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, -obj.m_Scl.y * 0.5f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	CAMERA* pCam = GetCamera();
	//�C�ӂ̎��̓]�u�s��
	if (InX)
	{
		obj.m_Mtx._11 = pCam->mtxView._11;
		obj.m_Mtx._12 = pCam->mtxView._21;
		obj.m_Mtx._13 = pCam->mtxView._31;
	}
	if (InY)
	{
		obj.m_Mtx._21 = pCam->mtxView._12;
		obj.m_Mtx._22 = pCam->mtxView._22;
		obj.m_Mtx._23 = pCam->mtxView._32;
	}
	if (InZ)
	{
		obj.m_Mtx._31 = pCam->mtxView._13;
		obj.m_Mtx._32 = pCam->mtxView._23;
		obj.m_Mtx._33 = pCam->mtxView._33;
	}

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonAnyBillLT(Object& obj, const int& tex, bool InX, bool InY, bool InZ)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x, 0.0f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(0.0f, -obj.m_Scl.y, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x, -obj.m_Scl.y, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	CAMERA* pCam = GetCamera();
	//�C�ӂ̎��̓]�u�s��
	if (InX)
	{
		obj.m_Mtx._11 = pCam->mtxView._11;
		obj.m_Mtx._12 = pCam->mtxView._21;
		obj.m_Mtx._13 = pCam->mtxView._31;
	}
	if (InY)
	{
		obj.m_Mtx._21 = pCam->mtxView._12;
		obj.m_Mtx._22 = pCam->mtxView._22;
		obj.m_Mtx._23 = pCam->mtxView._32;
	}
	if (InZ)
	{
		obj.m_Mtx._31 = pCam->mtxView._13;
		obj.m_Mtx._32 = pCam->mtxView._23;
		obj.m_Mtx._33 = pCam->mtxView._33;
	}

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void Draw3DModel(Object& obj, DX11_MODEL& model)
{
	// �}�e���A���ݒ�
	SetMaterial(obj.m_Material);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &model.VertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	GetDeviceContext()->IASetIndexBuffer(model.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
	D3DXMatrixIdentity(&obj.m_Mtx);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	for (unsigned short i = 0; i < model.SubsetNum; i++)
	{
		// �e�N�X�`���ݒ�
		if (model.SubsetArray[i].Material.Material.noTexSampling == 0)
			GetDeviceContext()->PSSetShaderResources(0, 1, &model.SubsetArray[i].Material.Texture);

		// �|���S���`��
		GetDeviceContext()->DrawIndexed(model.SubsetArray[i].IndexNum, model.SubsetArray[i].StartIndex, 0);
	}
}
void DrawNomber(D3DXVECTOR3 pos, float size, int Drawtext) {
	Object aa;
	// �}�e���A���ݒ�
	ZeroMemory(&aa.m_Material, sizeof(aa.m_Material));
	aa.m_Material.Ambient = { 1.0f,1.0f ,1.0f ,1.0f };
	aa.m_Material.Diffuse = { 1.0f,1.0f ,1.0f ,1.0f };
	aa.m_Material.noTexSampling = 0;
	aa.m_Material.Emission = { 1.0f,1.0f ,1.0f ,1.0f };
	//�|�W�V�����@�T�C�Y�ݒ�
	aa.m_Pos = pos;
	float scl = size;
	aa.m_Scl = { scl,scl * 1.45f,scl };
	aa.m_Uv_f = { 0.2f,0.5f };
	//�\��������������ϊ�
	std::string text = std::to_string(Drawtext);
	float textlength = 0.0f;
	//�����̑�����������
	for (char a : text)
	{
		switch (a)
		{
		case 0x30:textlength += size * 0.78f;
			break;
		case 0x31:textlength += size * 0.65f;
			break;
		case 0x32:textlength += size * 0.86f;
			break;
		case 0x33:textlength += size * 0.78f;
			break;
		case 0x34:textlength += size * 0.78f;
			break;
		case 0x35:textlength += size * 0.73f;
			break;
		case 0x36:textlength += size * 0.82f;
			break;
		case 0x37:textlength += size * 0.72f;
			break;
		case 0x38:textlength += size * 0.78f;
			break;
		case 0x39:textlength += size * 0.78f;
			break;
		default:
			break;
		}
	}
	textlength *= 0.5f;
	float hufsize = size * 0.5f;
	for (char b : text) {
		switch (b)
		{
		case 0x30:aa.m_Uv_v = { 0.8f,0.5f }; textlength -= hufsize * 0.78f;
			break;
		case 0x31:aa.m_Uv_v = { 0.0f,0.0f }; textlength -= hufsize * 0.65f;
			break;
		case 0x32:aa.m_Uv_v = { 0.2f,0.0f }; textlength -= hufsize * 0.86f;
			break;
		case 0x33:aa.m_Uv_v = { 0.4f,0.0f }; textlength -= hufsize * 0.78f;
			break;
		case 0x34:aa.m_Uv_v = { 0.6f,0.0f }; textlength -= hufsize * 0.78f;
			break;
		case 0x35:aa.m_Uv_v = { 0.8f,0.0f }; textlength -= hufsize * 0.73f;
			break;
		case 0x36:aa.m_Uv_v = { 0.0f,0.5f }; textlength -= hufsize * 0.82f;
			break;
		case 0x37:aa.m_Uv_v = { 0.2f,0.5f }; textlength -= hufsize * 0.72f;
			break;
		case 0x38:aa.m_Uv_v = { 0.4f,0.5f }; textlength -= hufsize * 0.78f;
			break;
		case 0x39:aa.m_Uv_v = { 0.6f,0.5f }; textlength -= hufsize * 0.78f;
			break;
		default:
			break;
		}
		DrawPolygonBillX(aa, RefImageMaterial().m_Suzi, -textlength);
		switch (b)
		{
		case 0x30:aa.m_Uv_v = { 0.8f,0.5f }; textlength -= hufsize * 0.78f;
			break;
		case 0x31:aa.m_Uv_v = { 0.0f,0.0f }; textlength -= hufsize * 0.65f;
			break;
		case 0x32:aa.m_Uv_v = { 0.2f,0.0f }; textlength -= hufsize * 0.86f;
			break;
		case 0x33:aa.m_Uv_v = { 0.4f,0.0f }; textlength -= hufsize * 0.78f;
			break;
		case 0x34:aa.m_Uv_v = { 0.6f,0.0f }; textlength -= hufsize * 0.78f;
			break;
		case 0x35:aa.m_Uv_v = { 0.8f,0.0f }; textlength -= hufsize * 0.73f;
			break;
		case 0x36:aa.m_Uv_v = { 0.0f,0.5f }; textlength -= hufsize * 0.82f;
			break;
		case 0x37:aa.m_Uv_v = { 0.2f,0.5f }; textlength -= hufsize * 0.72f;
			break;
		case 0x38:aa.m_Uv_v = { 0.4f,0.5f }; textlength -= hufsize * 0.78f;
			break;
		case 0x39:aa.m_Uv_v = { 0.6f,0.5f }; textlength -= hufsize * 0.78f;
			break;
		default:
			break;
		}
	}

}

void DrawScreenCircle(D3DXVECTOR2 pos, D3DXVECTOR2 tex_pos, float radius, float rate, D3DXCOLOR color, int& tex)
{
	if (rate < 0 || rate>1)
		return;

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	ID3D11Device* pDevice = GetDevice();

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * CIRCLE_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pDevice->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	int count = 360;
	int num = (count - 2) * 3;
	{//���_�o�b�t�@�̒��g�𖄂߂�
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
		float angle = D3DXToRadian(-90);

		for (int i = 0; i < count; i++)
		{
			vertex[i].Position = { pos.x + radius * cosf(angle) ,pos.y + radius * sinf(angle),0 };
			vertex[i].TexCoord = { cosf(angle) * rate + tex_pos.x,(sinf(angle) * rate) + tex_pos.y };
			vertex[i].Diffuse = color;
			vertex[i].Normal = { 0.0f,0.0f,-1.0f };

			angle += D3DXToRadian(1);
		}

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�

		// �C���f�b�N�X�o�b�t�@�̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_IndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		unsigned short* pIdx = (unsigned short*)msr.pData;

		for (int i = 0; i < num; i++)
		{
			int rem = i % 3;
			if (rem == 0)
				pIdx[i] = 0;
			else if (rem == 1)
				pIdx[i] = 1 + i / 3;
			else
				pIdx[i] = 2 + i / 3;
		}

		GetDeviceContext()->Unmap(g_IndexBuffer, 0);
	}

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	GetDeviceContext()->IASetIndexBuffer(g_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));

	// �}�e���A���̃Z�b�g
	MATERIAL mtl;
	mtl.Diffuse = { 0.0f,0.0f,0.0f,1.0f };
	mtl.Ambient = { 0.0f,0.0f,0.0f,1.0f };
	mtl.Emission = color;
	mtl.noTexSampling = 0;
	SetMaterial(mtl);

	// �|���S���`��
	GetDeviceContext()->DrawIndexed(num, 0, 0);

	// Z��r����
	SetDepthEnable(true);
}