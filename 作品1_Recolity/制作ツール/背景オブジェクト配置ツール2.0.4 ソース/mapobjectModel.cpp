//=============================================================================
//
// 3Dモデル表示処理 [mapobjectModel.cpp]
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
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPolygon(void);

//=============================================================================
// マクロ
//=============================================================================
DirectWrite* WriteModel;
#define	VALUE_MOVE		(5.0f)					// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)		// 回転量
#define MAX_MAPOBJECTMODEL_NUM (1024)	//3DModelの最大数
#define ROTTOTIME_DI  (9)//単押しの時間を判定する数字
int rottotime = 0;//Rを押し続けてる時間
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static DX11_MODEL		g_Model;			// モデル読み込み

static MAPOBJECTMODEL g_MapObjectModel[MAX_MAPOBJECTMODEL_NUM];
static LIGHT			g_Light;			// ライト
static MATERIAL			g_Material;			// マテリアルデータ

static int				g_MapObjectModelSelect = 0;			//ターゲット中の3Dモデルのカウント
float					modelspeed = 1.0f;											//モデルの移動時の速さ


DIMOUSESTATE2			g_ObjCurrentMouse;

//=============================================================================
// 初期化処理
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
// MapObjectの終了処理
//=============================================================================
void UninitMapModelObject(void)
{
	//objモデルの解放
	UnloadModel(&g_Model);
}


//=============================================================================
// MapObjectの更新処理
//=============================================================================
void UpdateMapModelObject(void)
{
	//マウスの視点移動処理
	g_ObjCurrentMouse.lX = GetMouseX();
	g_ObjCurrentMouse.lY = GetMouseY();
	//************モデルの移動速度の変更
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
	//**********オブジェクトの追加
	//Ｏを押すと新しいオブジェクトが0,0,0に新しく生成されます
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
	//***********選択しているオブジェクトの削除
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
	//***********テクスチャの変更
	//N M キーでテクスチャの変更ができる
	//nが-方向にテクスチャを変える
	//Mが+方向にテクスチャを変える
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
	//*************選択しているオブジェクトのコピー
	//Cを押すと選択しているオブジェクトと同じデータの物がもう1つできる
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
	//******************選択しているオブジェクトの切り替え
	//1,2キーで選択しているオブジェクトを切り替える
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
	//**********移動処理
	//十字キーでXZ軸移動
	//Qを押しながらだとXZ軸移動ができなくなりY軸のみ移動できるようになる
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
	//**************スケール変更処理
	//シフトを押しながら
	//十字キーの上下を押して固定値変更と
	//マウスの相対値でサイズを変更が可能
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

	//***********回転処理
	//Rを押しながらマウスの相対値でフリー回転と
	//単押しで90度固定回転
	{
		if (GetKeyboardPress(DIK_R) )
		{
			//ここでRを押し続けてる時間を加算している
			rottotime++;
			if (IsMouseLeftPressed())
			{
				//横フリー回転処理
				if (g_ObjCurrentMouse.lX != 0 && !IsMouseCenterPressed())
				{
					if (g_ObjCurrentMouse.lX > 0)
					{
						//カメラの相対値で回転
						g_MapObjectModel[g_MapObjectModelSelect].rot.y += CameraMouse(g_ObjCurrentMouse.lX, VALUE_MOUSE_RATE);
						if (g_MapObjectModel[g_MapObjectModelSelect].rot.y > D3DX_PI)
						{
							//PIを超えたらーPI＊２して反転
							g_MapObjectModel[g_MapObjectModelSelect].rot.y -= D3DX_PI * 2.0f;
						}
					}
					else
					{
						//カメラの相対値で回転
						g_MapObjectModel[g_MapObjectModelSelect].rot.y -= CameraMouse(g_ObjCurrentMouse.lX, VALUE_MOUSE_RATE);
						if (g_MapObjectModel[g_MapObjectModelSelect].rot.y < -D3DX_PI)
						{
							//PIを超えたら+PI＊２して反転
							g_MapObjectModel[g_MapObjectModelSelect].rot.y += D3DX_PI * 2.0f;
						}
					}
				}

				if (IsMouseCenterPressed())
				{
					if (g_ObjCurrentMouse.lY > 0)
					{
						//カメラの相対値で回転
						g_MapObjectModel[g_MapObjectModelSelect].rot.x += CameraMouse(g_ObjCurrentMouse.lY, VALUE_MOUSE_RATE);
						if (g_MapObjectModel[g_MapObjectModelSelect].rot.x > D3DX_PI)
						{
							//PIを超えたらーPI＊２して反転
							g_MapObjectModel[g_MapObjectModelSelect].rot.x -= D3DX_PI * 2.0f;
						}
					}
					else
					{
						//カメラの相対値で回転
						g_MapObjectModel[g_MapObjectModelSelect].rot.x -= CameraMouse(g_ObjCurrentMouse.lY, VALUE_MOUSE_RATE);
						if (g_MapObjectModel[g_MapObjectModelSelect].rot.x < -D3DX_PI)
						{
							//PIを超えたら+PI＊２して反転
							g_MapObjectModel[g_MapObjectModelSelect].rot.x += D3DX_PI * 2.0f;
						}
					}
				}
			}
			
		}
		//90度固定回転処理
		//押し続けてる時間が"ROTTOTIME_DI"より短かった場合90度右回転する
		//左回転は未作成
		//IF分の最後で押し続けてる時間リセット
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
			//リセット
			rottotime = 0;
		}
	}
#ifdef _DEBUG	// デバッグ情報を表示する
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], " rotX:%.2f rotY:%.2f", g_MapObjectModel[g_MapObjectModelSelect].rot.x, g_MapObjectModel[g_MapObjectModelSelect].rot.y);

#endif
}

//=============================================================================
// MapObject描画
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
			mtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//拡散色
			mtl.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//環境色
			mtl.Emission = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//自己発光色
			mtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//※スペキュラーは未対応
			mtl.Shininess = 20;                            //※スペキュラーは未対応
			mtl.noTexSampling = 0;                            //テクスチャ有り:0 or テクスチャ無し:1
			D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
			D3DXMATRIX mtxWorld;
			SetMaterial(mtl);
			// ワールドマトリックスの初期化（単位行列を作る関数）
			D3DXMatrixIdentity(&g_MapObjectModel[i].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_MapObjectModel[i].scl.x, g_MapObjectModel[i].scl.y, g_MapObjectModel[i].scl.z);

			//第1引数 ＝          第2引数      ＊    第3引数
			D3DXMatrixMultiply(&g_MapObjectModel[i].mtxWorld, &g_MapObjectModel[i].mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MapObjectModel[i].rot.y, g_MapObjectModel[i].rot.x, g_MapObjectModel[i].rot.z);
			D3DXMatrixMultiply(&g_MapObjectModel[i].mtxWorld, &g_MapObjectModel[i].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_MapObjectModel[i].pos.x, g_MapObjectModel[i].pos.y, g_MapObjectModel[i].pos.z);
			D3DXMatrixMultiply(&g_MapObjectModel[i].mtxWorld, &g_MapObjectModel[i].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			SetWorldMatrix(&g_MapObjectModel[i].mtxWorld);

			//objモデルの描画
			DrawModel(&RefModelMaterial().MapModel[g_MapObjectModel[i].num]);
		}
	}
	{
		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
		SetDepthEnable(false);
		MATERIAL mtl;
		ZeroMemory(&mtl, sizeof(mtl));
		mtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//拡散色
		mtl.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//環境色
		mtl.Emission = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//自己発光色
		mtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//※スペキュラーは未対応
		mtl.Shininess = 20;                            //※スペキュラーは未対応
		mtl.noTexSampling = 0;                            //テクスチャ有り:0 or テクスチャ無し:1
		D3DXMATRIX mtxWorld;
		D3DXMATRIX	world;
		SetMaterial(mtl);
		// ワールドマトリックスの初期化（単位行列を作る関数）
		D3DXMatrixIdentity(&world);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, 0.3f, 0.3f, 0.3f);

		//第1引数 ＝          第2引数      ＊    第3引数
		D3DXMatrixMultiply(&world, &world, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&world, &world, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_MapObjectModel[g_MapObjectModelSelect].pos.x, g_MapObjectModel[g_MapObjectModelSelect].pos.y, g_MapObjectModel[g_MapObjectModelSelect].pos.z);
		D3DXMatrixMultiply(&world, &world, &mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&world);

		//objモデルの描画
		DrawModel(&RefModelMaterial().Yazirusi);
		SetDepthEnable(true);
	}
}
void DrawMapModelObject2D() {
	SetText("modelspd: " + std::to_string(modelspeed).substr(0, 4), { 1350,100 });
}
//=============================================================================
//セーブ処理
//=============================================================================
void SaveModelMap(void)
{
	const char* MapFilePath = "data/MAP/MapFileModel.txt";  // 保存先ファイルパス

	std::ofstream ofs(MapFilePath);

	if (!ofs.is_open())
	{
		MessageBoxA(NULL, "ファイル保存に失敗しました！", "エラー", MB_ICONERROR | MB_OK);
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
//ロード処理
//=============================================================================
void LoadModelMap(void)
{
	const char* MapFilePath = "data/MAP/MapFileModel.txt";  // ファイルパス

	std::ifstream ifs(MapFilePath);

	if (!ifs.is_open())
	{
		MessageBoxA(NULL, "ファイルを開けませんでした！", "エラー", MB_ICONERROR | MB_OK);
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