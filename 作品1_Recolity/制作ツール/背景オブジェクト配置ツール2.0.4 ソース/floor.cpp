#include "floor.h"
#include "polygon.h"
#include "Texture.h"
#include "material.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	FLOOR_SIZE			(100.0f)				// �n�ʂ̃T�C�Y
#define	FLOOR_X_SIZE		(100)					// X�����̃|���S���̃T�C�Y
#define	FLOOR_Z_SIZE		(100)					// Z�����̃|���S���̃T�C�Y
#define	POLYGON_NUM			(10000)					// Z�����̃|���S���̃T�C�Y
void toFloorVertex(int index);
static ID3D11Buffer* g_FloorVertexBuffer = NULL;	// ���_���
static POLYGON				g_FloorPolygon[POLYGON_NUM];			// �|���S���f�[�^
static VERTEX_3D			g_FlootVertexArray[POLYGON_NUM * 4];
static int					g_VertexIndex;		// �e�N�X�`���ԍ�
FLOOR2						g_2floor[100][100];
void InitFloor(void) {

	int index = 0;
	float xpos = FLOOR_X_SIZE * 0.5f;
	float zpos = FLOOR_Z_SIZE * 0.5f;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			g_FloorPolygon[index].pos = D3DXVECTOR3(xpos + FLOOR_X_SIZE * j, 0.0f, zpos + FLOOR_Z_SIZE * i);

			index++;
		}
	}
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	for (int i = 0; i < POLYGON_NUM; i++)
	{
		g_FloorPolygon[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_FloorPolygon[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_FloorPolygon[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	g_VertexIndex = 0;
	for (int i = 0; i < POLYGON_NUM; i++)
	{
		toFloorVertex(i);
	}

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;;
	bd.ByteWidth = sizeof(VERTEX_3D) * POLYGON_NUM * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// �O���[�o���̒��_�z�񂩂璸�_�o�b�t�@������
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = g_FlootVertexArray;
	const char* MapFilePath = "FloorData/flloordata.txt";  // �ۑ���t�@�C���p�X

	std::ifstream ifs(MapFilePath);
	if (ifs.is_open())
	{

		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				int a;
				int b;
				int c;
				int d;
				ifs >> a >> g_2floor[i][j].tex >> b >> c >> d;
				g_2floor[i][j].floor_type = (Floor_Type)a;
			}
		}


		ifs.close();
	}
	GetDevice()->CreateBuffer(&bd, &sd, &g_FloorVertexBuffer);
}
void UnInitFloor(void) {
}
void UpdateFloor(void) {
}
void DrawFloor(void) {
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_FloorVertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	for (int i = 0; i < POLYGON_NUM; i++)
	{
		int tex = 0;
		tex = RefImageMaterial().m_Floor_Image_paper;
		if (g_2floor[i % 100][i / 100].floor_type == Floor_Wall ||
			g_2floor[i % 100][i / 100].floor_type == Floor_Nomal)
		{
			if (RefImageMaterial().Floor_Image[g_2floor[i % 100][i / 100].tex] > -1)
			{
				tex = RefImageMaterial().Floor_Image[g_2floor[i % 100][i / 100].tex];
			}
		}
	
		// �e�N�X�`���ݒ�	
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_FloorPolygon[i].mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, g_FloorPolygon[i].scl.x, g_FloorPolygon[i].scl.y, g_FloorPolygon[i].scl.z);
		D3DXMatrixMultiply(&g_FloorPolygon[i].mtxWorld, &g_FloorPolygon[i].mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_FloorPolygon[i].rot.y, g_FloorPolygon[i].rot.x, g_FloorPolygon[i].rot.z);
		D3DXMatrixMultiply(&g_FloorPolygon[i].mtxWorld, &g_FloorPolygon[i].mtxWorld, &mtxRot);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&g_FloorPolygon[i].mtxWorld);

		// �|���S���`��
		GetDeviceContext()->Draw(4, i * 4);
			
		

	}
}
void toFloorVertex(int index)
{
	//�|�W�V����
	g_FlootVertexArray[g_VertexIndex + 0].Position = D3DXVECTOR3(g_FloorPolygon[index].pos.x - (FLOOR_X_SIZE / 2), 0.0f, g_FloorPolygon[index].pos.z + (FLOOR_Z_SIZE / 2));
	g_FlootVertexArray[g_VertexIndex + 1].Position = D3DXVECTOR3(g_FloorPolygon[index].pos.x + (FLOOR_X_SIZE / 2), 0.0f, g_FloorPolygon[index].pos.z + (FLOOR_Z_SIZE / 2));
	g_FlootVertexArray[g_VertexIndex + 2].Position = D3DXVECTOR3(g_FloorPolygon[index].pos.x - (FLOOR_X_SIZE / 2), 0.0f, g_FloorPolygon[index].pos.z - (FLOOR_Z_SIZE / 2));
	g_FlootVertexArray[g_VertexIndex + 3].Position = D3DXVECTOR3(g_FloorPolygon[index].pos.x + (FLOOR_X_SIZE / 2), 0.0f, g_FloorPolygon[index].pos.z - (FLOOR_Z_SIZE / 2));

	//�@���E�J���[
	for (int i = 0; i < 4; i++)
	{
		g_FlootVertexArray[g_VertexIndex + i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_FlootVertexArray[g_VertexIndex + i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	g_FlootVertexArray[g_VertexIndex + 0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	g_FlootVertexArray[g_VertexIndex + 1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	g_FlootVertexArray[g_VertexIndex + 2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	g_FlootVertexArray[g_VertexIndex + 3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	g_VertexIndex += 4;
}