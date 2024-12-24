//=============================================================================
//
// 絵素材処理 [material.cpp]
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
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
Model_Material g_Model_Material;
Image_Material g_Image_Material;

//=============================================================================
// 初期化処理
//=============================================================================
void LoadMaterial(void)
{
	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/yazirusi110_2.obj", &g_Model_Material.Yazirusi);


	//マップ用モデルをtxtで読み込めるように
	//64こまでになってるけどまあそんなに追加しないよね
	//足りなかったらすみません追加してください
	const char* ModelFilePath = "data/LoadMODEL.txt";  // 保存先ファイルパス
	std::string LoadModel_ [64] = {};  // 保存先ファイルパス
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
	//画像の読み込み

	g_Image_Material.m_Floor_Image_paper = LoadTexture((char*)"data/TEXTURE/tilepaper2.png");
	g_Image_Material.m_cursortex = LoadTexture((char*)"data/TEXTURE/cursor.png");

	//床のデータ読み込み
	//最大数は８でいじらないこと
	//これは他のものと統合するためです
	//ここは触らないで
	const char* MapFilePath = "data/LoadTEXTURE.txt";  // 保存先ファイルパス
	std::string Loadtex[8] = { "","" ,"" ,"" ,"" ,"" ,"" ,"" };  // 保存先ファイルパス
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
// 終了処理
//=============================================================================
void ReleaseMaterial(void)
{
	//終了処理
	//objモデルの解放

}

//=============================================================================
// モデル構造体のゲッター
//=============================================================================
Model_Material& RefModelMaterial(void)
{
	return g_Model_Material;
}

//=============================================================================
// イメージ構造体のゲッター
//=============================================================================
Image_Material& RefImageMaterial(void)
{
	return g_Image_Material;
}