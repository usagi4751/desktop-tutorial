//=============================================================================
//
// �G�f�ޏ��� [material.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "material.h"
#include "Texture.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Model_Material g_Model_Material;
Image_Material g_Image_Material;

//=============================================================================
// ����������
//=============================================================================
void LoadMaterial(void)
{
	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/yazirusi110_2.obj", &g_Model_Material.Yazirusi);


	//�}�b�v�p���f����txt�œǂݍ��߂�悤��
	//64���܂łɂȂ��Ă邯�ǂ܂�����Ȃɒǉ����Ȃ����
	//����Ȃ������炷�݂܂���ǉ����Ă�������
	const char* ModelFilePath = "data/LoadMODEL.txt";  // �ۑ���t�@�C���p�X
	std::string LoadModel_ [64] = {};  // �ۑ���t�@�C���p�X
	std::ifstream ifsm(ModelFilePath);
	if (ifsm.is_open())
	{

		for (int i = 0; i < 64; i++)
		{
			std::string text;
			ifsm >> text;
			if (text != "")
			{
				LoadModel_[i] = "data/MODEL/";
				LoadModel_[i] += text.c_str();
			}
		}
		ifsm.close();
	}
	for (int i = 0; i < 64; i++)
	{
		if (LoadModel_[i] != "")
		{
			LoadModel((char*)LoadModel_[i].c_str(), &g_Model_Material.MapModel[i]);
		}
	}
	//�摜�̓ǂݍ���

	g_Image_Material.m_Floor_Image_paper = LoadTexture((char*)"data/TEXTURE/tilepaper2.png");
	g_Image_Material.m_cursortex = LoadTexture((char*)"data/TEXTURE/cursor.png");

	//���̃f�[�^�ǂݍ���
	//�ő吔�͂W�ł�����Ȃ�����
	//����͑��̂��̂Ɠ������邽�߂ł�
	//�����͐G��Ȃ���
	const char* MapFilePath = "data/LoadTEXTURE.txt";  // �ۑ���t�@�C���p�X
	std::string Loadtex[8] = { "","" ,"" ,"" ,"" ,"" ,"" ,"" };  // �ۑ���t�@�C���p�X
	std::ifstream ifs(MapFilePath);
	if (ifs.is_open())
	{

		for (int i = 0; i < 8; i++)
		{
			std::string text;
			ifs >> text;
			if (text != "")
			{
				Loadtex[i] = "data/TEXTURE/";
				Loadtex[i] += text.c_str();
			}
		}
		ifs.close();
	}
	for (int i = 0; i < 8; i++)
	{
		if (Loadtex[i] != "")
		{
			g_Image_Material.Floor_Image[i] = LoadTexture((char*)Loadtex[i].c_str());
		}
	}



}

//=============================================================================
// �I������
//=============================================================================
void ReleaseMaterial(void)
{
	//�I������
	//obj���f���̉��

}

//=============================================================================
// ���f���\���̂̃Q�b�^�[
//=============================================================================
Model_Material& RefModelMaterial(void)
{
	return g_Model_Material;
}

//=============================================================================
// �C���[�W�\���̂̃Q�b�^�[
//=============================================================================
Image_Material& RefImageMaterial(void)
{
	return g_Image_Material;
}