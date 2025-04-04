//=============================================================================
//
// 3D���f���\������ [mapobjectModel.cpp]
// Author :monden
//
//=============================================================================

#include "main.h"
#include "input.h"
#include "keyboard.h"
#include "polygon.h"
#include "Texture.h"
#include "font.h"
#include "renderer.h"
#include "camera.h"
#include "sprite.h"
#include "mapobjectModel.h"
#include "model.h"
#include "material.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "MapObjectAllUI.h"
#include "polygon.h"
#include "ui.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPolygon(void);

//=============================================================================
// �}�N��
//=============================================================================
DirectWrite* WriteModel;
#define	VALUE_MOVE		(5.0f)					// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)		// ��]��
#define MAX_MAPOBJECTMODEL_NUM (1024)	//3DModel�̍ő吔
#define ROTTOTIME_DI  (9)//�P�����̎��Ԃ𔻒肷�鐔��
int rottotime = 0;//R�����������Ă鎞��
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static DX11_MODEL		g_Model;			// ���f���ǂݍ���

static MAPOBJECTMODEL g_MapObjectModel[MAX_MAPOBJECTMODEL_NUM];
static LIGHT			g_Light;			// ���C�g
static MATERIAL			g_Material;			// �}�e���A���f�[�^

static int				g_MapObjectModelSelect = 0;			//�^�[�Q�b�g����3D���f���̃J�E���g
float					modelspeed = 1.0f;											//���f���̈ړ����̑���


DIMOUSESTATE2			g_ObjCurrentMouse;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMapModelObject(void)
{



	for (int i = 1; i <= MAX_MAPOBJECTMODEL_NUM; i++)
	{
		g_MapObjectModel[i].pos = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		g_MapObjectModel[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MapObjectModel[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_MapObjectModel[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_MapObjectModel[i].use = false;

	}

	FontData* fodata = new  FontData();
	fodata->fontSize = 10;
	fodata->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
	WriteModel = new DirectWrite(fodata);
	WriteModel->TextInit();



	return S_OK;
}

//=============================================================================
// MapObject�̏I������
//=============================================================================
void UninitMapModelObject(void)
{
	//obj���f���̉��
	UnloadModel(&g_Model);
}


//=============================================================================
// MapObject�̍X�V����
//=============================================================================
void UpdateMapModelObject(void)
{
	//�}�E�X�̎��_�ړ�����
	g_ObjCurrentMouse.lX = GetMouseX();
	g_ObjCurrentMouse.lY = GetMouseY();
	//************���f���̈ړ����x�̕ύX
	if (GetKeyboardTrigger(DIK_K))
	{
		modelspeed -= 0.05f;
		if (modelspeed < 0)
		{
			modelspeed = 0.0f;
		}
	}
	if (GetKeyboardTrigger(DIK_L))
	{
		modelspeed += 0.05f;
	}
	//**********�I�u�W�F�N�g�̒ǉ�
	//�n�������ƐV�����I�u�W�F�N�g��0,0,0�ɐV������������܂�
	if (GetKeyboardTrigger(DIK_O))
	{
		for (int  i = 0; i < MAX_MAPOBJECTMODEL_NUM; i++)
		{
			if (g_MapObjectModel[i].use ==false)
			{
				g_MapObjectModel[i].use = true;
				g_MapObjectModel[i].pos = { 0.0f,0.0f ,0.0f };
				g_MapObjectModel[i].rot = { 0.0f,0.0f ,0.0f };
				g_MapObjectModel[i].scl = { 1.0f,1.0f ,1.0f };
				g_MapObjectModel[i].color = { 1.0f,1.0f ,1.0f,1.0f };
				g_MapObjectModel[i].num = 0;
				g_MapObjectModelSelect = i;
				break;
			}
		}

	}
	//***********�I�����Ă���I�u�W�F�N�g�̍폜
	// 
	if (GetKeyboardTrigger(DIK_BACK))
	{
		g_MapObjectModel[g_MapObjectModelSelect].use			 = false;
		for (int i = 0; i < MAX_MAPOBJECTMODEL_NUM + 1; i++)
		{
			g_MapObjectModelSelect += 1;
			if (g_MapObjectModelSelect > MAX_MAPOBJECTMODEL_NUM - 1)
			{
				g_MapObjectModelSelect = 0;
			}
			if (g_MapObjectModel[g_MapObjectModelSelect].use == true)
			{
				break;

			}

		}
	}
	//***********�e�N�X�`���̕ύX
	//N M �L�[�Ńe�N�X�`���̕ύX���ł���
	//n��-�����Ƀe�N�X�`����ς���
	//M��+�����Ƀe�N�X�`����ς���
	{
		if (GetKeyboardTrigger(DIK_N))
		{
			for (int i = 0; i < 65; i++)
			{
				g_MapObjectModel[g_MapObjectModelSelect].num--;
				if (g_MapObjectModel[g_MapObjectModelSelect].num < 0)
				{
					g_MapObjectModel[g_MapObjectModelSelect].num = 64 - 1;
				}

				if ((int)RefModelMaterial().MapModel[g_MapObjectModel[g_MapObjectModelSelect].num].SubsetNum != 0)
				{
					break;
				}
			}

		}
		if (GetKeyboardTrigger(DIK_M))
		{
			for (int i = 0; i < 65; i++)
			{
				g_MapObjectModel[g_MapObjectModelSelect].num++;
				if (g_MapObjectModel[g_MapObjectModelSelect].num > 64 - 1)
				{
					g_MapObjectModel[g_MapObjectModelSelect].num = 0;
				}

				if ((int)RefModelMaterial().MapModel[g_MapObjectModel[g_MapObjectModelSelect].num].SubsetNum != 0)
				{
					break;
				}
			}
		}
	}
	//*************�I�����Ă���I�u�W�F�N�g�̃R�s�[
	//C�������ƑI�����Ă���I�u�W�F�N�g�Ɠ����f�[�^�̕�������1�ł���
	if (GetKeyboardTrigger(DIK_C))
	{
	
		for (int i = 0; i < MAX_MAPOBJECTMODEL_NUM; i++)
		{
			if (g_MapObjectModel[i].use == false)
			{
				g_MapObjectModel[i].use = true;
				g_MapObjectModel[i].pos = g_MapObjectModel[g_MapObjectModelSelect].pos;
				g_MapObjectModel[i].rot = g_MapObjectModel[g_MapObjectModelSelect].rot;
				g_MapObjectModel[i].scl = g_MapObjectModel[g_MapObjectModelSelect].scl;
				g_MapObjectModel[i].color = g_MapObjectModel[g_MapObjectModelSelect].color;
				g_MapObjectModel[i].num = g_MapObjectModel[g_MapObjectModelSelect].num;
				break;
			}
		}

	}
	//******************�I�����Ă���I�u�W�F�N�g�̐؂�ւ�
	//1,2�L�[�őI�����Ă���I�u�W�F�N�g��؂�ւ���
	{
		
			if (GetKeyboardTrigger(DIK_1))
			{
				for (int i = 0; i < MAX_MAPOBJECTMODEL_NUM + 1; i++)
				{
					g_MapObjectModelSelect += 1;
					if (g_MapObjectModelSelect > MAX_MAPOBJECTMODEL_NUM - 1)
					{
						g_MapObjectModelSelect = 0;
					}
					if (g_MapObjectModel[g_MapObjectModelSelect].use == true)
					{
						break;

					}

				}

			}
			if (GetKeyboardTrigger(DIK_2))
			{
				for (int i = 0; i < MAX_MAPOBJECTMODEL_NUM + 1; i++)
				{
					g_MapObjectModelSelect -= 1;
					if (g_MapObjectModelSelect < 0)
					{
						g_MapObjectModelSelect = MAX_MAPOBJECTMODEL_NUM - 1;
					}
					if (g_MapObjectModel[g_MapObjectModelSelect].use == true)
					{
						break;

					}

				}
			}

		
	}
	//**********�ړ�����
	//�\���L�[��XZ���ړ�
	//Q�������Ȃ��炾��XZ���ړ����ł��Ȃ��Ȃ�Y���݈̂ړ��ł���悤�ɂȂ�
	{
		if (!GetKeyboardPress(DIK_Q) && !GetKeyboardPress(DIK_LSHIFT))
		{
			if (GetKeyboardPress(DIK_UP) && !GetKeyboardPress(DIK_Z))
			{
				g_MapObjectModel[g_MapObjectModelSelect].pos.z += 10 * modelspeed;
			
			}
			if (GetKeyboardTrigger(DIK_UP) && GetKeyboardPress(DIK_Z))
			{		
					g_MapObjectModel[g_MapObjectModelSelect].pos.z = (float)((int)g_MapObjectModel[g_MapObjectModelSelect].pos.z - (int)g_MapObjectModel[g_MapObjectModelSelect].pos.z % 50 ) + 50.0000f;
			}
			if (GetKeyboardPress(DIK_DOWN) && !GetKeyboardPress(DIK_Z))
			{
				g_MapObjectModel[g_MapObjectModelSelect].pos.z -= 10 * modelspeed;
			}
			if (GetKeyboardTrigger(DIK_DOWN) && GetKeyboardPress(DIK_Z))
			{
				g_MapObjectModel[g_MapObjectModelSelect].pos.z = (float)((int)g_MapObjectModel[g_MapObjectModelSelect].pos.z - (int)g_MapObjectModel[g_MapObjectModelSelect].pos.z % 50) - 50.0000f;
			}
			if (GetKeyboardPress(DIK_LEFT) && !GetKeyboardPress(DIK_Z))
			{
				g_MapObjectModel[g_MapObjectModelSelect].pos.x -= 10 * modelspeed;
			}
			if (GetKeyboardTrigger(DIK_LEFT) && GetKeyboardPress(DIK_Z))
			{
				g_MapObjectModel[g_MapObjectModelSelect].pos.x = (float)((int)g_MapObjectModel[g_MapObjectModelSelect].pos.x - (int)g_MapObjectModel[g_MapObjectModelSelect].pos.x % 50) - 50.0000f;
			}
			if (GetKeyboardPress(DIK_RIGHT) && !GetKeyboardPress(DIK_Z))
			{
				g_MapObjectModel[g_MapObjectModelSelect].pos.x += 10 * modelspeed;
			}
			if (GetKeyboardTrigger(DIK_RIGHT) && GetKeyboardPress(DIK_Z))
			{
				g_MapObjectModel[g_MapObjectModelSelect].pos.x = (float)((int)g_MapObjectModel[g_MapObjectModelSelect].pos.x - (int)g_MapObjectModel[g_MapObjectModelSelect].pos.x % 50) + 50.0000f;
			}
		}
		else if (GetKeyboardPress(DIK_Q))
		{
			if (GetKeyboardPress(DIK_UP))
			{
				g_MapObjectModel[g_MapObjectModelSelect].pos.y += 10 * modelspeed;
			}
			if (GetKeyboardPress(DIK_DOWN))
			{
				g_MapObjectModel[g_MapObjectModelSelect].pos.y -= 10 * modelspeed;
			}
		}
	}
	//**************�X�P�[���ύX����
	//�V�t�g�������Ȃ���
	//�\���L�[�̏㉺�������ČŒ�l�ύX��
	//�}�E�X�̑��Βl�ŃT�C�Y��ύX���\
	{
		if (GetKeyboardPress(DIK_LSHIFT))
		{
			if (GetKeyboardPress(DIK_UP))
			{
				g_MapObjectModel[g_MapObjectModelSelect].scl.x += 0.005f;
				g_MapObjectModel[g_MapObjectModelSelect].scl.y += 0.005f;
				g_MapObjectModel[g_MapObjectModelSelect].scl.z += 0.005f;
			}
			if (GetKeyboardPress(DIK_DOWN))
			{

				g_MapObjectModel[g_MapObjectModelSelect].scl.x -= 0.005f;
				g_MapObjectModel[g_MapObjectModelSelect].scl.y -= 0.005f;
				g_MapObjectModel[g_MapObjectModelSelect].scl.z -= 0.005f;

			}
			if (IsMouseRightPressed())
			{
				float moseyscl = 0.03f;
				g_MapObjectModel[g_MapObjectModelSelect].scl.x -= moseyscl * GetMouseY();
				g_MapObjectModel[g_MapObjectModelSelect].scl.y -= moseyscl * GetMouseY();
				g_MapObjectModel[g_MapObjectModelSelect].scl.z -= moseyscl * GetMouseY();
			}

			if (g_MapObjectModel[g_MapObjectModelSelect].scl.x < 0.1f)
			{
				g_MapObjectModel[g_MapObjectModelSelect].scl.x = 0.1f;
			}
			if (g_MapObjectModel[g_MapObjectModelSelect].scl.y < 0.1f)
			{
				g_MapObjectModel[g_MapObjectModelSelect].scl.y = 0.1f;
			}
			if (g_MapObjectModel[g_MapObjectModelSelect].scl.z < 0.1f)
			{
				g_MapObjectModel[g_MapObjectModelSelect].scl.z = 0.1f;
			}
		}
	}

	//***********��]����
	//R�������Ȃ���}�E�X�̑��Βl�Ńt���[��]��
	//�P������90�x�Œ��]
	{
		if (GetKeyboardPress(DIK_R) )
		{
			//������R�����������Ă鎞�Ԃ����Z���Ă���
			rottotime++;
			if (IsMouseLeftPressed())
			{
				//���t���[��]����
				if (g_ObjCurrentMouse.lX != 0 && !IsMouseCenterPressed())
				{
					if (g_ObjCurrentMouse.lX > 0)
					{
						//�J�����̑��Βl�ŉ�]
						g_MapObjectModel[g_MapObjectModelSelect].rot.y += CameraMouse(g_ObjCurrentMouse.lX, VALUE_MOUSE_RATE);
						if (g_MapObjectModel[g_MapObjectModelSelect].rot.y > D3DX_PI)
						{
							//PI�𒴂�����[PI���Q���Ĕ��]
							g_MapObjectModel[g_MapObjectModelSelect].rot.y -= D3DX_PI * 2.0f;
						}
					}
					else
					{
						//�J�����̑��Βl�ŉ�]
						g_MapObjectModel[g_MapObjectModelSelect].rot.y -= CameraMouse(g_ObjCurrentMouse.lX, VALUE_MOUSE_RATE);
						if (g_MapObjectModel[g_MapObjectModelSelect].rot.y < -D3DX_PI)
						{
							//PI�𒴂�����+PI���Q���Ĕ��]
							g_MapObjectModel[g_MapObjectModelSelect].rot.y += D3DX_PI * 2.0f;
						}
					}
				}

				if (IsMouseCenterPressed())
				{
					if (g_ObjCurrentMouse.lY > 0)
					{
						//�J�����̑��Βl�ŉ�]
						g_MapObjectModel[g_MapObjectModelSelect].rot.x += CameraMouse(g_ObjCurrentMouse.lY, VALUE_MOUSE_RATE);
						if (g_MapObjectModel[g_MapObjectModelSelect].rot.x > D3DX_PI)
						{
							//PI�𒴂�����[PI���Q���Ĕ��]
							g_MapObjectModel[g_MapObjectModelSelect].rot.x -= D3DX_PI * 2.0f;
						}
					}
					else
					{
						//�J�����̑��Βl�ŉ�]
						g_MapObjectModel[g_MapObjectModelSelect].rot.x -= CameraMouse(g_ObjCurrentMouse.lY, VALUE_MOUSE_RATE);
						if (g_MapObjectModel[g_MapObjectModelSelect].rot.x < -D3DX_PI)
						{
							//PI�𒴂�����+PI���Q���Ĕ��]
							g_MapObjectModel[g_MapObjectModelSelect].rot.x += D3DX_PI * 2.0f;
						}
					}
				}
			}
			
		}
		//90�x�Œ��]����
		//���������Ă鎞�Ԃ�"ROTTOTIME_DI"���Z�������ꍇ90�x�E��]����
		//����]�͖��쐬
		//IF���̍Ō�ŉ��������Ă鎞�ԃ��Z�b�g
		if (GetKeyboardRelease(DIK_R))
		{
			if (rottotime < ROTTOTIME_DI)
			{

				g_MapObjectModel[g_MapObjectModelSelect].rot.y += D3DX_PI * 0.5f + 0.0000001f;
				if (g_MapObjectModel[g_MapObjectModelSelect].rot.y > D3DX_PI)
				{
					g_MapObjectModel[g_MapObjectModelSelect].rot.y -= D3DX_PI * 2.0f;
				}
				float* rot = &g_MapObjectModel[g_MapObjectModelSelect].rot.y;
				if (*rot > 0)
				{
					*rot > D3DX_PI * 0.5f ? *rot = D3DX_PI * 0.5f : *rot = 0;
				}
				else
				{
					*rot > -D3DX_PI * 0.5f ? *rot = -D3DX_PI * 0.5f : *rot = -D3DX_PI;
				}
			}
			//���Z�b�g
			rottotime = 0;
		}
	}
#ifdef _DEBUG	// �f�o�b�O����\������
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], " rotX:%.2f rotY:%.2f", g_MapObjectModel[g_MapObjectModelSelect].rot.x, g_MapObjectModel[g_MapObjectModelSelect].rot.y);

#endif
}

//=============================================================================
// MapObject�`��
//=============================================================================
void DrawMapModelObject()
{
	/*SetDepthEnable(true);*/
	SetAlphaTestEnable(true);

	for (int i = 0; i <= MAX_MAPOBJECTMODEL_NUM; i++)
	{
		if (g_MapObjectModel[i].use == true)
		{
			SetLightEnable(false);
			MATERIAL mtl;
			ZeroMemory(&mtl, sizeof(mtl));
			mtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�g�U�F
			mtl.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//���F
			mtl.Emission = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//���Ȕ����F
			mtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//���X�y�L�����[�͖��Ή�
			mtl.Shininess = 20;                            //���X�y�L�����[�͖��Ή�
			mtl.noTexSampling = 0;                            //�e�N�X�`���L��:0 or �e�N�X�`������:1
			D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
			D3DXMATRIX mtxWorld;
			SetMaterial(mtl);
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
			DrawModel(&RefModelMaterial().MapModel[g_MapObjectModel[i].num]);
		}
	}
	{
		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
		SetDepthEnable(false);
		MATERIAL mtl;
		ZeroMemory(&mtl, sizeof(mtl));
		mtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�g�U�F
		mtl.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//���F
		mtl.Emission = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//���Ȕ����F
		mtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//���X�y�L�����[�͖��Ή�
		mtl.Shininess = 20;                            //���X�y�L�����[�͖��Ή�
		mtl.noTexSampling = 0;                            //�e�N�X�`���L��:0 or �e�N�X�`������:1
		D3DXMATRIX mtxWorld;
		D3DXMATRIX	world;
		SetMaterial(mtl);
		// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
		D3DXMatrixIdentity(&world);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, 0.3f, 0.3f, 0.3f);

		//��1���� ��          ��2����      ��    ��3����
		D3DXMatrixMultiply(&world, &world, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&world, &world, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, g_MapObjectModel[g_MapObjectModelSelect].pos.x, g_MapObjectModel[g_MapObjectModelSelect].pos.y, g_MapObjectModel[g_MapObjectModelSelect].pos.z);
		D3DXMatrixMultiply(&world, &world, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&world);

		//obj���f���̕`��
		DrawModel(&RefModelMaterial().Yazirusi);
		SetDepthEnable(true);
	}
}
void DrawMapModelObject2D() {
	SetText("modelspd: " + std::to_string(modelspeed).substr(0, 4), { 1350,100 });
}
//=============================================================================
//�Z�[�u����
//=============================================================================
void SaveModelMap(void)
{
	const char* MapFilePath = "data/MAP/MapFileModel.txt";  // �ۑ���t�@�C���p�X

	std::ofstream ofs(MapFilePath);

	if (!ofs.is_open())
	{
		MessageBoxA(NULL, "�t�@�C���ۑ��Ɏ��s���܂����I", "�G���[", MB_ICONERROR | MB_OK);
	}
	else if (ofs.is_open())
	{
		ofs << MAX_MAPOBJECTMODEL_NUM << std::endl;
		for (int i = 0; i <= MAX_MAPOBJECTMODEL_NUM; i++)
		{
			
			//use
			ofs << g_MapObjectModel[i].use << std::endl;
			// pos
			ofs << g_MapObjectModel[i].pos.x << "\t" << g_MapObjectModel[i].pos.y << "\t" << g_MapObjectModel[i].pos.z << std::endl;
			// rot
			ofs << g_MapObjectModel[i].rot.x << "\t" << g_MapObjectModel[i].rot.y << "\t" << g_MapObjectModel[i].rot.z << std::endl;
			// scl
			ofs << g_MapObjectModel[i].scl.x << "\t" << g_MapObjectModel[i].scl.y << "\t" << g_MapObjectModel[i].scl.z << std::endl;
			// color
			ofs << g_MapObjectModel[i].color.r << "\t" << g_MapObjectModel[i].color.g << "\t" << g_MapObjectModel[i].color.b << "\t" << g_MapObjectModel[i].color.a << std::endl;

			// mtxWorld
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					ofs << g_MapObjectModel[i].mtxWorld(j, k) << ' ';
				}
			}
			ofs << g_MapObjectModel[i].num << std::endl;
			ofs << std::endl;
		}
		ofs.close();
	}
}
//=============================================================================
//���[�h����
//=============================================================================
void LoadModelMap(void)
{
	const char* MapFilePath = "data/MAP/MapFileModel.txt";  // �t�@�C���p�X

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
			ifs >> g_MapObjectModel[i].pos.x >>g_MapObjectModel[i].pos.y >> g_MapObjectModel[i].pos.z;
			ifs >> g_MapObjectModel[i].rot.x >>g_MapObjectModel[i].rot.y >> g_MapObjectModel[i].rot.z;
			ifs >> g_MapObjectModel[i].scl.x >>g_MapObjectModel[i].scl.y >> g_MapObjectModel[i].scl.z;
			ifs >> g_MapObjectModel[i].color.r >> g_MapObjectModel[i].color.g >> g_MapObjectModel[i].color.b >> g_MapObjectModel[i].color.a;

			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					ifs >> g_MapObjectModel[i].mtxWorld(row, col);
				}
			}
			ifs >> g_MapObjectModel[i].num ;
		}
		ifs.close();
	}
}




MAPOBJECTMODEL* GetSelectMapObjectModel(void)
{
	return &g_MapObjectModel[g_MapObjectModelSelect];
}


int GetMapModelObjectSelectCont(void)
{
	return g_MapObjectModelSelect;
}
int GetMapModelObjectCount(void) {
	int count = 0;
	for (int i = 0; i < MAX_MAPOBJECTMODEL_NUM; i++)
	{
		if (g_MapObjectModel[i].use == true)
		{
			count++;
		}
	}
	return count;
}