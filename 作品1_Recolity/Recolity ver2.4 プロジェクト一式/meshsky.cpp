//=============================================================================
//
// ���b�V����̏��� [meshsky.cpp]
// Author : 
//
//=============================================================================
#include "meshsky.h"
#include "Texture.h"
#include "input.h"
#include "camera.h"
#include "material.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	SKY_HEIGHT_RATE			(2.0f)		// ��h�[���̍����W��
#define	TEX_COUNT_LOOP			(1)			// �e�N�X�`���̌J��Ԃ���

struct SKY_MESH
{
	ID3D11Buffer	*vertexBuffer;	// ���_�o�b�t�@
	ID3D11Buffer	*indexBuffer;	// �C���f�b�N�X�o�b�t�@
	int				numVertex;		//���_��
	int				numIndex;		//�C���f�b�N�X��

	D3DXMATRIX		mtxWorld;
	D3DXVECTOR3		pos;
	D3DXVECTOR3		rot;

	MATERIAL		material;
};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static SKY_MESH		g_Sky;		//���񕔕�
static SKY_MESH		g_SkyTop;	//�V������
static bool			g_TransParent;
static bool			g_Reverse;

//=============================================================================
// ����������
//=============================================================================
void InitMeshSky(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float radius,
	int numBlockH, int numBlockV, bool reverse)
{
	ID3D11Device* pDevice = GetDevice();

	g_TransParent = false;
	g_Reverse = reverse;

	// �|���S���\���ʒu�̒��S���W��ݒ�
	g_Sky.pos = pos;
	g_Sky.rot = rot;
	g_SkyTop.pos = pos;
	g_SkyTop.rot = rot;

	//�}�e���A���̏�����
	ZeroMemory(&g_Sky.material, sizeof(g_Sky.material));
	g_Sky.material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Sky.material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Sky.material.Emission = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ZeroMemory(&g_SkyTop.material, sizeof(g_SkyTop.material));
	g_SkyTop.material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_SkyTop.material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_SkyTop.material.Emission = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// ���_���̐ݒ�
	g_Sky.numVertex = (numBlockH + 1) * (numBlockV + 1);
	g_SkyTop.numVertex = numBlockH + 1;

	// �C���f�b�N�X���̐ݒ�
	g_Sky.numIndex = (numBlockH * (numBlockV * 2) + numBlockV * 2 + (numBlockV - 1) * 2);
	g_SkyTop.numIndex = numBlockH * 3;

	// �ꎞ���_�z��𐶐�
	VERTEX_3D* pVertexWk = new VERTEX_3D[g_Sky.numVertex];
	VERTEX_3D* pVertexTopWk = new VERTEX_3D[g_SkyTop.numVertex];

	// �ꎞ�C���f�b�N�X�z��𐶐�
	int* pIndexWk = new int[g_Sky.numIndex];
	int* pIndexTopWk = new int[g_SkyTop.numIndex];

	// ���_�z��̒��g�𖄂߂�
	VERTEX_3D* pVtx = pVertexWk;
	const float ANGLE_H = (D3DX_PI * 2) / numBlockH;
	const float ANGLE_V = (D3DX_PI / 8) / (numBlockV + 1);
	const float WIDTH = 1.0f / numBlockH;
	const float HEIGHT = 1.0f / numBlockV;
	float lengthXZ;

	for (int vt = 0; vt < (numBlockV + 1); vt++) {
		lengthXZ = cosf(ANGLE_V * vt) * radius;

		for (int hr = 0; hr < (numBlockH + 1); hr++) {
			// ���_���W�̐ݒ�
			pVtx->Position.x = sinf(ANGLE_H * hr) * lengthXZ;
			if (g_Reverse) {
				pVtx->Position.y = -sinf(ANGLE_V * vt) * radius * SKY_HEIGHT_RATE;
			} else {
				pVtx->Position.y = sinf(ANGLE_V * vt) * radius * SKY_HEIGHT_RATE;
			}
			pVtx->Position.z = cosf(ANGLE_H * hr) * lengthXZ;

			// �@���̐ݒ�
			pVtx->Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���ˌ��̐ݒ�
			if (g_Reverse) {
				pVtx->Diffuse = D3DXCOLOR(0.0625f, 0.0625f, 0.375f, 0.5f);
			} else {
				pVtx->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			// �e�N�X�`�����W�̐ݒ�
			pVtx->TexCoord.x = hr * WIDTH * TEX_COUNT_LOOP;
			if (vt == numBlockV) {
				pVtx->TexCoord.y = 0.01f;
			} else {
				pVtx->TexCoord.y = 1.0f - vt * HEIGHT;
			}

			pVtx++;
		}
	}

	pVtx = pVertexTopWk;

	// ���_���W�̐ݒ�
	pVtx->Position.x = 0.0f;
	if (g_Reverse) {
		pVtx->Position.y = -sinf(ANGLE_V * (numBlockV + 1)) * radius * SKY_HEIGHT_RATE;
	} else {
		pVtx->Position.y = sinf(ANGLE_V * (numBlockV + 1)) * radius * SKY_HEIGHT_RATE;
	}
	pVtx->Position.z = 0.0f;

	// �@���̐ݒ�
	pVtx->Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	if (g_Reverse) {
		pVtx->Diffuse = D3DXCOLOR(0.0675f, 0.0675f, 0.375f, 0.5f);
	} else {
		pVtx->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// �e�N�X�`�����W�̐ݒ�
	pVtx->TexCoord.x = 0.01f;
	pVtx->TexCoord.y = 0.01f;

	pVtx++;

	lengthXZ = cosf(ANGLE_V * numBlockV) * radius;
	for (int hr = 0; hr < numBlockH; hr++ ) {
		// ���_���W�̐ݒ�
		pVtx->Position.x = -sinf(ANGLE_H * hr) * lengthXZ;
		if (g_Reverse) {
			pVtx->Position.y = -sinf(ANGLE_V * numBlockV) * radius * SKY_HEIGHT_RATE;
		} else {
			pVtx->Position.y = sinf(ANGLE_V * numBlockV) * radius * SKY_HEIGHT_RATE;
		}
		pVtx->Position.z = cosf(ANGLE_H * hr) * lengthXZ;

		// �@���̐ݒ�
		pVtx->Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		if (g_Reverse) {
			pVtx->Diffuse = D3DXCOLOR(0.0675f, 0.0675f, 0.375f, 0.5f);
		} else {
			pVtx->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// �e�N�X�`�����W�̐ݒ�
		pVtx->TexCoord.x = 0.01f;
		pVtx->TexCoord.y = 0.01f;

		pVtx++;
	}

	// �C���f�b�N�X�z��̒��g�𖄂߂�
	int* pIdx = pIndexWk;

	for (int vt = 0; vt < numBlockV; vt++) {
		if (vt != 0) {
			*pIdx = vt * (numBlockH + 1);
			pIdx++;
		}

		for (int hr = 0; hr < numBlockH + 1; hr++) {
			*pIdx = vt * (numBlockH + 1) + hr;
			pIdx++;

			*pIdx = (vt + 1) * (numBlockH + 1) + hr;
			pIdx++;
		}

		if (vt != (numBlockV - 1)) {
			*pIdx = (vt + 1) * (numBlockH + 1);
			pIdx++;
		}
	}

	pIdx = pIndexTopWk;
	for (int hr = 1; hr < numBlockH + 1; hr++) {
		*pIdx = 0;
		++pIdx;
		*pIdx = hr;
		++pIdx;
		if (hr < numBlockH) {
			*pIdx = hr + 1;
		} else {
			*pIdx = 1;
		}
		++pIdx;
	}

	//���񕔕��̒��_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�쐬
	{
		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * g_Sky.numVertex;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pVertexWk;

		GetDevice()->CreateBuffer(&bd, &sd, &g_Sky.vertexBuffer);

		// �C���f�b�N�X�o�b�t�@����
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(int) * g_Sky.numIndex;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pIndexWk;

		GetDevice()->CreateBuffer(&bd, &sd, &g_Sky.indexBuffer);
	}

	//�V�������̒��_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�쐬
	{
		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * g_SkyTop.numVertex;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pVertexTopWk;

		GetDevice()->CreateBuffer(&bd, &sd, &g_SkyTop.vertexBuffer);

		// �C���f�b�N�X�o�b�t�@����
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * g_SkyTop.numIndex;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pIndexTopWk;

		GetDevice()->CreateBuffer(&bd, &sd, &g_SkyTop.indexBuffer);
	}

	// �ꎞ�z������
	delete[] pIndexTopWk;
	delete[] pIndexWk;
	delete[] pVertexTopWk;
	delete[] pVertexWk;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshSky(void)
{
	// ���񕔕����b�V���̉��
	if (g_Sky.indexBuffer != NULL)
	{
		g_Sky.indexBuffer->Release();
		g_Sky.indexBuffer = NULL;
	}

	if (g_Sky.vertexBuffer != NULL)
	{
		g_Sky.vertexBuffer->Release();
		g_Sky.vertexBuffer = NULL;
	}

	// �V���������b�V���̉��
	if (g_SkyTop.indexBuffer != NULL)
	{
		g_SkyTop.indexBuffer->Release();
		g_SkyTop.indexBuffer = NULL;
	}

	if (g_SkyTop.vertexBuffer != NULL)
	{
		g_SkyTop.vertexBuffer->Release();
		g_SkyTop.vertexBuffer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshSky(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshSky(void)
{
	if (g_Reverse) 
	{
		SetCullingMode(CULL_MODE_FRONT);	// �O�ʃJ�����O
	}
	else 
	{
		SetCullingMode(CULL_MODE_BACK);		// �w�ʃJ�����O
	}

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(RefImageMaterial().m_Sky));

	//���񕔕��̕`��
	{
		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_Sky.vertexBuffer, &stride, &offset);

		// �C���f�b�N�X�o�b�t�@�ݒ�
		GetDeviceContext()->IASetIndexBuffer(g_Sky.indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �}�e���A���ݒ�
		SetMaterial(g_Sky.material);


		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Sky.mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Sky.rot.y, g_Sky.rot.x, g_Sky.rot.z);
		D3DXMatrixMultiply(&g_Sky.mtxWorld, &g_Sky.mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, g_Sky.pos.x, g_Sky.pos.y, g_Sky.pos.z);
		D3DXMatrixMultiply(&g_Sky.mtxWorld, &g_Sky.mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&g_Sky.mtxWorld);

		// �|���S���̕`��
		GetDeviceContext()->DrawIndexed(g_Sky.numIndex, 0, 0);
	}

	//�V�������̕`��
	{
		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_SkyTop.vertexBuffer, &stride, &offset);

		// �C���f�b�N�X�o�b�t�@�ݒ�
		GetDeviceContext()->IASetIndexBuffer(g_SkyTop.indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// �}�e���A���ݒ�
		SetMaterial(g_SkyTop.material);


		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_SkyTop.mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_SkyTop.rot.y, g_SkyTop.rot.x, g_SkyTop.rot.z);
		D3DXMatrixMultiply(&g_SkyTop.mtxWorld, &g_SkyTop.mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, g_SkyTop.pos.x, g_SkyTop.pos.y, g_SkyTop.pos.z);
		D3DXMatrixMultiply(&g_SkyTop.mtxWorld, &g_SkyTop.mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&g_SkyTop.mtxWorld);

		// �|���S���̕`��
		GetDeviceContext()->DrawIndexed(g_SkyTop.numIndex, 0, 0);
	}

	SetCullingMode(CULL_MODE_BACK);		// �w�ʃJ�����O
}
