//=============================================================================
//
// MAP�̃I�u�W�F�N�g�ǉ��S�ʃC���^�[�t�F�C�Y�Ǘ�[MapObjectAllUI.cpp]
// Author :monden
//
//=============================================================================
#include "MapObjectAllUI.h"
#include "mapobjectModel.h"
#include "sprite.h"
#include "renderer.h"
#include "font.h"
#include "input.h"
#include "ui.h"
#include "material.h"
#include "polygon.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

//=============================================================================
// �}�N��
//=============================================================================
DirectWrite* Write;
#define MAX_OBJECT_NUM (1000)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
bool g_SelectModelMode = false;
bool g_SelectPolygonMode = false;
int g_AllMapObjectSelect = 0;
int* g_AllObject[MAX_OBJECT_NUM] = {};

bool g_saveflag=false;
bool g_loadflag = false;

int g_PolygonCount=0;
int g_ModelCount=0;

int flamecont[2] = {};

MAPOBJECTMODEL* g_pSelectMapObjectModel;



//=============================================================================
// ����������
//=============================================================================
void InitMapObjectAllUI()
{
	g_SelectPolygonMode = false;
	g_SelectModelMode = true;
	InitMapModelObject();


	//�t�H���g�f�[�^�̏�����
	FontData* fodata = new  FontData();
	fodata->fontSize = 15;
	fodata->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
	Write = new DirectWrite(fodata);
	Write->TextInit();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMapObjectAllUI()
{



	g_pSelectMapObjectModel = GetSelectMapObjectModel();

	
	//�Z�[�u�����[�h����
	if (GetKeyboardTrigger(DIK_F1))
	{
		SaveModelMap();
		g_saveflag = true;
	}
	if (GetKeyboardTrigger(DIK_F2))
	{
		LoadModelMap();
		g_loadflag = true;
	}


	if (!g_SelectPolygonMode && g_SelectModelMode)
	{
		UpdateMapModelObject();
		g_AllMapObjectSelect = GetMapModelObjectSelectCont();

	}

	if (g_saveflag)
	{
		if (flamecont[0] < 60)
		{
			flamecont[0]++;
		}
		else
		{
			g_saveflag = false;
			flamecont[0] = 0;
		}
	}
	if (g_loadflag)
	{
		if (flamecont[1] < 60)
		{
			flamecont[1]++;
		}
		else
		{
			g_loadflag = false;
			flamecont[1] = 0;
		}

	}


}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawMapObjectAllUI()
{

	DrawMapModelObject();

	//�^�[�Q�b�g���I�u�W�F�N�g�\��
	std::string targetobject = "�^�[�Q�b�g���I�u�W�F�N�g: ";




	std::string objectmax = "�I�u�W�F�N�g����"+ std::to_string(GetMapModelObjectCount());

	double posX = 0.0;
	double posY = 0.0;
	double posZ = 0.0;


	if (!g_SelectPolygonMode && g_SelectModelMode)
	{
		if (g_pSelectMapObjectModel != NULL)
		{
			posX = g_pSelectMapObjectModel->pos.x;
			posY = g_pSelectMapObjectModel->pos.y;
			posZ = g_pSelectMapObjectModel->pos.z;
		}

	}

	std::ostringstream oss;
	//ostringstream���g���ĕ�������������ĂP���ɂ���
	// fixed�ŌŒ菬���_�ɕϊ����āA
	//setprexision�ŏ����_����܂łɐݒ肵�Ă�
	oss << "pos.x " << std::fixed << std::setprecision(1) << posX << "\n"
		<< "pos.y " << std::fixed << std::setprecision(1) << posY << "\n"
		<< "pos.z " << std::fixed << std::setprecision(1) << posZ;

	std::string targetobjectdata = oss.str();
	D2D1_RECT_F a = { 1200, 0, 2000, 200 };
	D2D1_RECT_F b = { 1200, 30, 1500, 200 };
	SetText(targetobject, { 1375,150 }, TextSc_3);
	Write->DrawString(objectmax, b, D2D1_DRAW_TEXT_OPTIONS_CLIP);





	std::string save = "�Z�[�u����";
	std::string load = "���[�h����";
	D2D1_RECT_F e = { 0, 150, 1500, 1000 };
	if (g_saveflag)
	{
		Write->DrawString(save, e, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
	D2D1_RECT_F f = { 0, 200, 1500, 1000 };
	if (g_loadflag)
	{
		Write->DrawString(load, f, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}


	std::string readme =
		"�\���L�[�㉺y��\n"
		"�\���L�[���Ex��\n"
		"R�L�[ + �}�E�X���E��]"
		"�V�t�g�L�[ + �\���L�[�㉺ �T�C�Y�ύX\n"
		"�V�t�g�@�{�@�}�E�X�㉺ �T�C�Y�ύX\n"
		"F1 �ۑ�\n"
		"F2 ���[�h\n"
		"o �V�����I�u�W�F�N�g����\n"
		"back space �I�𒆂̃I�u�W�F�N�g���폜\n"

		;
	if (!g_saveflag &&!g_loadflag)
	{
		D2D1_RECT_F g = { 0,0, 1500, 5000 };
		Write->DrawString(readme, g, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
	
	SetText("�ړ�\n��]\n�X�P�[��", { 1400,200 }, TextSc_2);
	{std::string text = "x" + std::to_string(g_pSelectMapObjectModel->pos.x ).substr(0,5)+ "\n"; 
	text += "x" + std::to_string(g_pSelectMapObjectModel->rot.x * 57.29579f).substr(0, 5) + "\n";
	text += "x" + std::to_string(g_pSelectMapObjectModel->scl.x).substr(0, 5) + "\n";
	SetText(text, { 1560,200 }, TextSc_2); 
	}
	{std::string text = "y" + std::to_string(g_pSelectMapObjectModel->pos.y ).substr(0, 5) + "\n";
	text += "y" + std::to_string(g_pSelectMapObjectModel->rot.y*57.29579f ).substr(0, 5) + "\n";
	text += "y" + std::to_string(g_pSelectMapObjectModel->scl.y ).substr(0, 5) + "\n";
	SetText(text, { 1640,200 }, TextSc_2);
	}
	{std::string text = "z" + std::to_string(g_pSelectMapObjectModel->pos.z ).substr(0, 5) + "\n";
	text += "z" + std::to_string(g_pSelectMapObjectModel->rot.z / 10.0f).substr(0, 5) + "\n";
	text += "z" + std::to_string(g_pSelectMapObjectModel->scl.z ).substr(0, 5) + "\n";
	SetText(text, { 1720,200 }, TextSc_2);
	}
	
	


	DrawScreen2(UI2{ {GetMousePos().x + 8,GetMousePos().y + 22},
	D3DXVECTOR2(50 ,50),
	D3DXVECTOR2(0.0f,0.0f),
	D3DXVECTOR2(1.0f,1.0f),
	D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),
	-0.3f }, RefImageMaterial().m_cursortex);


}

void UninitMapObjectAllUI()
{
	UninitMapModelObject();

}
int celectObject() {
	return g_AllMapObjectSelect;
}
