#include "floor.h"
#include "Texture.h"
#include "material.h"
#include "renderer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "card.h"
#include "Game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	FLOOR_SIZE			(100.0f)				// �n�ʂ̃T�C�Y
#define	FLOOR_X_SIZE		(100)					// X�����̃|���S���̃T�C�Y
#define	FLOOR_Z_SIZE		(100)					// Z�����̃|���S���̃T�C�Y
#define POLYGON_NUM			(10000)
void toFloorVertex(int index);
ID3D11Buffer* g_FloorVertexBuffer = NULL;	// ���_���
POLYGON				g_FloorPolygon[POLYGON_NUM];			// �|���S���f�[�^
VERTEX_3D			g_FlootVertexArray[POLYGON_NUM * 4];
int					g_VertexIndex;		// �e�N�X�`���ԍ�
FLOOR2						g_2floor[100][100];

bool g_initr = false;//1�x�̂ݓ����悤��


void InitFloor(void) {
	if (g_initr == false)
	{
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

		GetDevice()->CreateBuffer(&bd, &sd, &g_FloorVertexBuffer);
	}
	g_initr = true;

	const char* MapFilePath = "";// �ۑ���t�@�C���p�X
	if (GetStageSelect() == Tutorial)
	{
		MapFilePath = "FloorData/flloordata_tutorial.txt";
	}
	if (GetStageSelect() == Stage1)
	{
		MapFilePath = "FloorData/flloordata_stage1.txt";
	}
	if (GetStageSelect() == Stage2)
	{
		MapFilePath = "FloorData/flloordata_stage2.txt";
	}
	std::ifstream ifs(MapFilePath);
	if (ifs.is_open())
	{

		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				int a;
				int no = -1;
				int rank = 1;
				int enemy = -1;
				ifs >> a >> g_2floor[i][j].tex >> no >> rank >> enemy;
				g_2floor[i][j].floor_type = (Floor_Type)a;
				g_2floor[i][j].Adhere = Floor_None;
				if (no > -1)
				{
					PGetDropCard()->SetDropCard(no, (Card_Rank)rank, { (float)(50 + 100 * i),0,(float)(0,50 + 100 * j) });
				}
				if (enemy > -1)
				{
					Enemy_Type type = none_enemy;
					if (enemy == 0)
					{
						type = normal_enemy;
					}
					if (enemy == 1)
					{
						type = patrol_enemy;
					}
					if (enemy == 2)
					{
						type = bullet_enemy;
					}
					if (enemy == 3)
					{
						type = boss_enemy;
					}
					if (enemy == 4)
					{
						type = scorpion_enemy;
					}
					if (enemy == 5)
					{
						type = spider_enemy;
					}
					if (enemy == 6)
					{
						type = boss2;
					}
					GetEnemymanager()->Create(type, { (float)(50 + i * 100) ,0,(float)(50 + j * 100) });
				}
			}
		}


		ifs.close();
	}
	
}
void UnInitFloor(void) {
}
void UpdateFloor(void) {
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (g_2floor[i][j].time <= 0)
			{
				g_2floor[i][j].Adhere = Floor_None;
			}
			if (g_2floor[i][j].Adhere == Floor_flame || g_2floor[i][j].Adhere == Floor_Water  || g_2floor[i][j].Adhere == Floor_Wind)
			{
				g_2floor[i][j].time--;
			}
		
		}
	}
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
		if (g_2floor[i % 100][i / 100].Adhere == Floor_flame)
		{
			tex = RefImageMaterial().m_Floor_Image_paper_flame;
		}

		if (g_2floor[i % 100][i / 100].Adhere == Floor_Water)
		{
			tex = RefImageMaterial().m_Floor_Image_paper_water;
		}
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
Floor_Type GetNowFloor(D3DXVECTOR3 pos) {
	if (pos.x > 0 && pos.x < 10000 && pos.z > 0 && pos.z < 10000)
	{
		return g_2floor[(int)(pos.x / 100.0f)][(int)(pos.z / 100.0f)].floor_type;
	}
	return Floor_Wall;
}
Floor_Adhere GetNowAdhere(D3DXVECTOR3 pos) {
	if (pos.x > 0 && pos.x < 10000 && pos.z > 0 && pos.z < 10000)
	{
		if (g_2floor[(int)(pos.x / 100.0f)][(int)(pos.z / 100.0f)].floor_type == Floor_Paper)
		{
			return g_2floor[(int)(pos.x / 100.0f)][(int)(pos.z / 100.0f)].Adhere;
		}
		return  Floor_None;
	}
	return  Floor_None;
}
void SetAdhere(D3DXVECTOR3 pos, Floor_Adhere ad, int time) {
	if (pos.x > 0 && pos.x < 10000&& pos.z > 0&& pos.z < 10000)
	{
		g_2floor[(int)(pos.x / 100.0f)][(int)(pos.z / 100.0f)].Adhere = ad;
		g_2floor[(int)(pos.x / 100.0f)][(int)(pos.z / 100.0f)].time = time;
	}

}