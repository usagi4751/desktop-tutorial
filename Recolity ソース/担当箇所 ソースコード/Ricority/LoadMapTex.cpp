#include "LoadMapTex.h"
#include "model.h"
#include "material.h"
#include "sprite.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Game.h"
#define	VALUE_MOVE		(5.0f)					// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)		// ��]��
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static DX11_MODEL		g_Model;			// ���f���ǂݍ���
static MAPOBJECTMODEL g_MapObjectModel[MAX_MAPOBJECTMODEL_NUM];
static int				g_MapObjectModelCount = 0;		//3D���f���̌��J�E���g
static int				g_MapObjectModelSelect = 0;			//�^�[�Q�b�g����3D���f���̃J�E���g
HRESULT InitMapModelObject(void)
{
	//char filePath[] = "data/MODEL/Lowpoly_tree_sample.obj";


	for (int i = 1; i <= MAX_MAPOBJECTMODEL_NUM; i++)
	{
		//g_MapObjectModel[i].modelpass = filePath;
		g_MapObjectModel[i].pos = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		g_MapObjectModel[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MapObjectModel[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_MapObjectModel[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_MapObjectModel[i].use = false;

	}





	return S_OK;
}
void LoadModelMap(void)
{
	const char* MapFilePath = "";  // �t�@�C���p�X
	if (GetStageSelect() == Tutorial)
	{
		MapFilePath = "data/MAP/MapFileModel_tutorial.txt";  // �t�@�C���p�X
	}
	if (GetStageSelect() == Stage1)
	{
		MapFilePath = "data/MAP/MapFileModel_stage1.txt";  // �t�@�C���p�X
	}
	if (GetStageSelect() == Stage2)
	{
		MapFilePath = "data/MAP/MapFileModel_stage2.txt";  // �t�@�C���p�X
	}
	std::ifstream ifs(MapFilePath);

	if (!ifs.is_open())
	{
		MessageBoxA(NULL, "�t�@�C�����J���܂���ł����I", "�G���[", MB_ICONERROR | MB_OK);
	}
	else if (ifs.is_open())
	{
		int nua = 0;
		ifs >> nua;
		for (int i = 0; i <= MAX_MAPOBJECTMODEL_NUM; i++)
		{

			ifs >> g_MapObjectModel[i].use;
			ifs >> g_MapObjectModel[i].pos.x >> g_MapObjectModel[i].pos.y >> g_MapObjectModel[i].pos.z;
			ifs >> g_MapObjectModel[i].rot.x >> g_MapObjectModel[i].rot.y >> g_MapObjectModel[i].rot.z;
			ifs >> g_MapObjectModel[i].scl.x >> g_MapObjectModel[i].scl.y >> g_MapObjectModel[i].scl.z;
			ifs >> g_MapObjectModel[i].color.r >> g_MapObjectModel[i].color.g >> g_MapObjectModel[i].color.b >> g_MapObjectModel[i].color.a;



			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					ifs >> g_MapObjectModel[i].mtxWorld(row, col);
				}
			}
			ifs >> g_MapObjectModel[i].num;
		}
		ifs.close();
	}
}
void DrawMapModelObject()
{
	SetAlphaTestEnable(true);
	MATERIAL mtl;
	ZeroMemory(&mtl, sizeof(mtl));
	mtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�g�U�F
	mtl.Ambient = D3DXCOLOR(1.0f, 1.0f,	1.0f, 1.0f) * 0.3f;//���F
	mtl.Emission = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) * 0.3f;//�e�̂Ƃ���F
	mtl.noTexSampling = 0;							//�e�N�X�`���L��:0 or �e�N�X�`������:1
	
	for (int i = 0; i <= MAX_MAPOBJECTMODEL_NUM; i++)
	{
		if (g_MapObjectModel[i].use == true)
		{

			D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
			D3DXMATRIX mtxWorld;
			// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
			D3DXMatrixIdentity(&g_MapObjectModel[i].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_MapObjectModel[i].scl.x, g_MapObjectModel[i].scl.y, g_MapObjectModel[i].scl.z);

			//��1���� ��          ��2����      ��    ��3����
			D3DXMatrixMultiply(&g_MapObjectModel[i].mtxWorld, &g_MapObjectModel[i].mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MapObjectModel[i].rot.y, g_MapObjectModel[i].rot.x, g_MapObjectModel[i].rot.z);
			D3DXMatrixMultiply(&g_MapObjectModel[i].mtxWorld, &g_MapObjectModel[i].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_MapObjectModel[i].pos.x, g_MapObjectModel[i].pos.y, g_MapObjectModel[i].pos.z);
			D3DXMatrixMultiply(&g_MapObjectModel[i].mtxWorld, &g_MapObjectModel[i].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&g_MapObjectModel[i].mtxWorld);

			//obj���f���̕`��
			DrawModel(&RefModelMaterial().MapModel[g_MapObjectModel[i].num],mtl);
		}
	}

}
