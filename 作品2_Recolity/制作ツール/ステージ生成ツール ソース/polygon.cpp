/*==============================================================================

   頂点管理 [polygon.cpp]
														 Author :
														 Date   :

	床制作ツール
	床には壁　通常　紙がある
	テクスチャは通常用もしくは壁用のテクスチャ
--------------------------------------------------------------------------------

==============================================================================*/
#include <stdio.h>
#include <memory.h>
#include <list>
#include <queue>
#include <vector>
#include <math.h>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "polygon.h"
#include "main.h"
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "particle.h"
#include "font.h"
#include "material.h"
#include <math.h>
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_POLYGON 100	//表示するポリゴンの数
#define PTN_WIDTH (1.0f / 5)
#define PTN_HEIGHT (1.0f / 2)






enum Tile
{
	Wall = 0,
	Nomal,
	Paper
	
};
typedef struct {
	Tile					state;		//属性:
	int						tex;		//床のテクスチャ
	int						cardno;		//カードのナンバー
	int						cardrank;		//カードのランク
	int						enemyno;	//enemyのナンバー
}FLOOR;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int XYGAP(D3DXVECTOR2 num1, D3DXVECTOR2 num2);
void Setflor(int x, int y, int type);
void UiDescription(D3DXVECTOR2 pos);
void UiDescriptionSelect(D3DXVECTOR2 pos);
void SetflorTex(int x, int y, int tex);
void SetCard(int x, int y, int no, int rank);
void SetflorEnemy(int x, int y, int enemy);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
DirectWrite* Write;
DirectWrite* Write2;
//テクスチャ
static int g_Flortex = 0;
static int g_Flortexwall = 0;
static int g_Flortexpaper = 0;
static int g_Flortexcursor= 0;
static int g_TexMozi = 0;
static int g_player[1] = {};
int g_cardno = 0;
int g_cardrank = 1;
int g_enemyno = -1;
static int g_uitex = 0;
static int g_uitex2 = 0;
static int g_uitex3 = 0;
//A*
//マップサイズ
const int MapWidth = 100;
const int MapHeight = 100;
std::string testtext ;
bool texton = false;
int g_mode = 0;//床を塗るモード選択
int g_texmode = 0;
bool g_cardpv = false;//カードのプレビュー
//床情報
static FLOOR g_flor[MapWidth][MapHeight] = {};
int g_cardtex;
float loop = 0;
int g_enemytex;
//=============================================================================
// 初期化処理
//=============================================================================
void InitPolygon(void)
{


	g_TexMozi = LoadTexture((char*)"data/System/mozi4.png");
	g_player[0] = LoadTexture((char*)"data/System/usagin1.png");
	g_Flortex = LoadTexture((char*)"data/System/tile.png");
	g_Flortexwall = LoadTexture((char*)"data/System/tilewall.png");
	g_Flortexpaper = LoadTexture((char*)"data/System/tilepaper.png");
	g_Flortexcursor = LoadTexture((char*)"data/System/tilecherect.png");
	g_uitex = LoadTexture((char*)"data/System/buffwaku.png");
	g_uitex2 = LoadTexture((char*)"data/System/shopui.png");
	g_uitex3 = LoadTexture((char*)"data/System/hpber.png");
	g_cardtex = LoadTexture((char*)"data/System/Card_back.png");
	g_enemytex = LoadTexture((char*)"data/System/enemy.png");
	const char* MapFilePath = "FloorData/flloordata.txt";  // 保存先ファイルパス

	std::ifstream ifs(MapFilePath);
	if (ifs.is_open())
	{
		
		for (int i = 0; i < MapWidth; i++)
		{
			for (int j = 0; j < MapHeight; j++)
			{
				int a;
				ifs >> a >> g_flor[i][j].tex >> g_flor[i][j].cardno >> g_flor[i][j].cardrank >> g_flor[i][j].enemyno;
				g_flor[i][j].state = (Tile)a;
			}
		}


		ifs.close();
	}

	FontData* fodata = new  FontData();
	
	fodata->fontSize = 20;
	fodata->fontWeight = DWRITE_FONT_WEIGHT_BOLD;


	Write = new DirectWrite(fodata);
	Write->TextInit();


	FontData* fodata2 = new  FontData();

	fodata2->fontSize = 10;
	fodata2->fontWeight = DWRITE_FONT_WEIGHT_BOLD;


	Write2 = new DirectWrite(fodata2);
	Write2->TextInit();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{
	loop += 0.05f;
	float texsize = 0;
	MapWidth > MapHeight ? texsize = 1000.0f / (float)MapWidth : texsize = 1000.0f / (float)MapHeight;
	if (GetKeyboardTrigger(DIK_1))
	{
		g_mode = 0;
	}
	if (GetKeyboardTrigger(DIK_2))
	{
		g_mode = 1;
	}
	if (GetKeyboardTrigger(DIK_3))
	{
		g_mode = 2;
	}
	if (GetKeyboardTrigger(DIK_4))
	{
		g_mode = 3;
	}
	if (GetKeyboardTrigger(DIK_5))
	{
		g_mode = 4;
	}
	if (GetKeyboardTrigger(DIK_6))
	{
		g_mode = 5;
	}
	if (GetKeyboardTrigger(DIK_F1))
	{
		const char* MapFilePath = "FloorData/flloordata.txt";  // 保存先ファイルパス

		std::ofstream ofs(MapFilePath);
		if (ofs.is_open())
		{
			for (int i = 0; i < MapWidth; i++)
			{
				for (int j = 0; j < MapHeight; j++)
				{
					ofs << std::to_string(g_flor[i][j].state) << "\t" << std::to_string(g_flor[i][j].tex)<< "\t" << std::to_string(g_flor[i][j].cardno)<< "\t" << std::to_string(g_flor[i][j].cardrank)<< "\t" << std::to_string(g_flor[i][j].enemyno) << std::endl;
				}
			}
			
			
			ofs.close();
		}
	}
	//壁とかを生成する処理
	{
		int xnum = (GetMousePos().x - 456) / texsize;
		if (xnum > MapWidth -1 )
		{
			xnum = MapWidth -1 ;
		}
		if (xnum < 0)
		{
			xnum = 0;
		}
		int ynum = (GetMousePos().y - 45) / texsize;
		if (ynum > MapHeight - 1)
		{
			ynum = MapHeight - 1;
		}
		if (ynum < 0)
		{
			ynum = 0;
		}
		if (GetMousePos().x > 456 &&  GetMousePos().x < 1456 && 
			GetMousePos().y > 44  && GetMousePos().y < 1046)
		{
			Tile mod = Wall;
			if (g_mode == 1)
			{
				mod = Nomal;
			}	
			if (g_mode == 2)
			{
				mod = Paper;
			}
			if (IsMouseLeftPressed() )
			{
				if (g_mode < 3)
				{
					Setflor(ynum, xnum, mod);
					SetflorTex(ynum, xnum, 0);

					if (GetKeyboardPress(DIK_LSHIFT))
					{
						int plus = 0;
						if (GetKeyboardPress(DIK_LCONTROL))
						{
							plus = 2;
						}
						for (int d = 0; d < 3 + plus; d++)
						{
							for (int c = 0; c < 3 + plus; c++)
							{
								Setflor(ynum - 1 + d - plus / 2, xnum - 1 + c - plus / 2, mod);
								SetflorTex(ynum - 1 + d - plus / 2, xnum - 1 + c - plus / 2, 0);
							}
						}
					}
				}
				if (g_mode == 3)
				{
					SetflorTex(ynum, xnum, g_texmode);
					if (GetKeyboardPress(DIK_LSHIFT))
					{
						int plus = 0;
						if (GetKeyboardPress(DIK_LCONTROL))
						{
							plus = 2;
						}
						for (int d = 0; d < 3+ plus; d++)
						{
							for (int c = 0; c < 3+ plus; c++)
							{
								
								SetflorTex(ynum - 1 + d-plus /2, xnum - 1 + c - plus / 2, g_texmode);
							}
						}
					}
				}
				if (g_mode == 4)
				{
					SetCard(ynum , xnum , g_cardno, g_cardrank);
				}
				if (g_mode == 5)
				{
					SetflorEnemy(ynum, xnum, g_enemyno);
				}
			}
			
		}
		
	}
	if (GetKeyboardTrigger(DIK_N) && g_cardno > -1)
	{
		g_cardno--;
	}
	if (GetKeyboardTrigger(DIK_M) )
	{
		g_cardno++;
	}
	if (GetKeyboardTrigger(DIK_K) && g_cardrank > 1)
	{
		g_cardrank--;
	}
	if (GetKeyboardTrigger(DIK_L) && g_cardrank < 3)
	{
		g_cardrank++;
	}
	if (GetKeyboardTrigger(DIK_O) && g_enemyno > -1)
	{
		g_enemyno--;
	}
	if (GetKeyboardTrigger(DIK_P))
	{
		g_enemyno++;
	}
	if (GetKeyboardTrigger(DIK_RSHIFT))
	{
		g_cardpv = !g_cardpv;
	}
	//pos.x + (i % 2) * 100.0f + 30, pos.y + (float)(i / 2) * 150.0f + 370,
	//1700.0f,30.0f
	for (int i = 0; i < 8; i++)
	{
		if (IsMouseLeftTriggered() &&
			1700 + (i % 2) * 100.0f + 30 - 35 < GetMousePos().x && 
			1700 + (i % 2) * 100.0f + 30 + 35 > GetMousePos().x && 
			30.0f + (float)(i / 2) * 150.0f + 370 - 35 < GetMousePos().y &&
			30.0f + (float)(i / 2) * 150.0f + 370 + 35 > GetMousePos().y &&
			RefImageMaterial().Floor_Image[i] != -1)
		{
			g_texmode = i;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{

	//SetText("X" + std::to_string((int)GetMousePos().x) + "Y" + std::to_string((int)GetMousePos().y), 10, 10, 20, DIK_COLER_WHITE);
	//SetText("saX" + std::to_string(goalpos.x - startpos.x < 0 ? startpos.x -goalpos.x: goalpos.x - startpos.x) + "saY" + std::to_string(goalpos.y - startpos.y < 0 ? startpos.y - goalpos.y : goalpos.y - startpos.y), 10, 50, 20, DIK_COLER_WHITE);
	//SetText("totalsa" + std::to_string(XYGAP(goalpos, startpos)) , 10, 90, 20, DIK_COLER_WHITE);
	SetText("DPI" + std::to_string(GeyDPI()), 10, 400, 20, DIK_COLER_WHITE);
	for (int i = 0; i < MapWidth; i++)
	{
		for (int j = 0; j < MapHeight; j++)
		{
			D3DXCOLOR coler = { 1.0f,1.0f,1.0f,1.0f };
			switch (g_flor[i][j].tex)
			{
			case 1:coler = { 1.0f,0.0f,0.0f,1.0f };
				  break;
			case 2:coler = { 1.0f,0.0f,1.0f,1.0f };
				  break;
			case 3:coler = { 0.0f,0.0f,1.0f,1.0f };
				  break;
			case 4:coler = { 1.0f,0.5f,0.0f,1.0f };
				  break;
			case 5:coler = { 1.0f,1.0f,0.0f,1.0f };
				  break;
			case 6:coler = { 0.5f,0.5f,0.5f,1.0f };
				  break;
			case 7:coler = { 0.5f,0.75f,1.0f,1.0f };
				  break;
			default:
				break;
			}
			float texsize = 0;

			MapWidth > MapHeight ? texsize = 1000.0f / (float)MapWidth : texsize = 1000.0f / (float)MapHeight;

			if (g_flor[i][j].state == 0)
			{
				DrawSpriteColor(g_Flortexwall,
					460 + (int)((j)*texsize), 50 + (int)(i * texsize),
					texsize, texsize,
					0.0f, 0.0f,
					1.0f, 1.0f,
					coler
				);
			}
			if (g_flor[i][j].state == 1)
			{
				if (GetKeyboardPress(DIK_Q))
				{
				DrawSpriteColor4(g_Flortex,
				460 + (int)((j)*texsize), 50 + (int)(i * texsize),
				texsize, texsize,
				{ sinf(loop),sinf(loop * 2.0f),0.0f,1.0f },
				{ sinf(loop + 0.3f),sinf(loop * 2.0f + 0.3f),cosf(loop * 2.0f + 0.6f),1.0f },
				{ sinf(loop + 0.3f),sinf(loop * 2.0f + 0.3f),cosf(loop * 2.0f + 0.6f),1.0f },
				{ sinf(loop + 0.6f),sinf(loop * 2.0f + 0.6f),cosf(loop * 2.0f + 0.6f),1.0f }
				);
				}
				else
				{
					DrawSpriteColor(g_Flortex,
						460 + (int)((j)*texsize), 50 + (int)(i * texsize),
						texsize, texsize,
						0.0f, 0.0f,
						1.0f, 1.0f,
						coler
					);
				}
				
			}
			if (g_flor[i][j].state == 2)
			{
				if (GetKeyboardPress(DIK_Q))
				{
					DrawSpriteColor4(g_Flortexpaper,
						460 + (int)((j)*texsize), 50 + (int)(i * texsize),
						texsize, texsize,
						{ sinf(loop),sinf(loop * 2.0f),0.0f,1.0f },
						{ sinf(loop + 0.3f),sinf(loop * 2.0f + 0.3f),cosf(loop * 2.0f + 0.6f),1.0f },
						{ sinf(loop + 0.3f),sinf(loop * 2.0f + 0.3f),cosf(loop * 2.0f + 0.6f),1.0f },
						{ sinf(loop + 0.6f),sinf(loop * 2.0f + 0.6f),cosf(loop * 2.0f + 0.6f),1.0f }
					);
				}
				else
				{
					DrawSpriteColor(g_Flortexpaper,
						460 + (int)((j)*texsize), 50 + (int)(i * texsize),
						texsize, texsize,
						0.0f, 0.0f,
						1.0f, 1.0f,
						coler
					);
				}
			}
			//DrawSpriteColor4(g_Flortex,
			//	460 + (int)((j)*texsize), 50 + (int)(i * texsize),
			//	texsize, texsize,
			//	{ sinf(loop),sinf(loop * 2.0f),0.0f,1.0f },
			//	{ sinf(loop + 0.3f),sinf(loop * 2.0f + 0.3f),cosf(loop * 2.0f + 0.6f),1.0f },
			//	{ sinf(loop + 0.3f),sinf(loop * 2.0f + 0.3f),cosf(loop * 2.0f + 0.6f),1.0f },
			//	{ sinf(loop + 0.6f),sinf(loop * 2.0f + 0.6f),cosf(loop * 2.0f + 0.6f),1.0f }
			//	);

			//SetText(std::to_string(XYGAP(D3DXVECTOR2(i % 50, j ), g_startpos)), 455 + (int)((i % 50) * 20), 37 + (int)(j  * 20), 10, DIK_COLER_DRAKGRAY);

		}
	}
	for (int i = 0; i < 100; i++)
	{
		float texsize = 0;

		MapWidth > MapHeight ? texsize = 1000.0f / (float)MapWidth : texsize = 1000.0f / (float)MapHeight;
		for (int j = 0; j < 100; j++)
		{
			if (g_flor[i][j].cardno > -1)
			{
				DrawSpriteColor(g_cardtex,
					460 + (int)((j)*texsize) , 50 + (int)(i * texsize),
					texsize , texsize * 1.4f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					DIK_COLER_WHITE
				);
				if (g_cardpv == true)
				{
					DrawSpriteColor(g_Flortex,
						460 + (int)((j)*texsize) + 25 + texsize -10, 50 + (int)(i * texsize)+5 + texsize,
						texsize + 50, texsize  + 15,
						0.0f, 0.0f,
						1.0f, 1.0f,
						DIK_COLER_DRAKGRAY
					);
					float h = 460 + (int)((j)*texsize);
					float z = 50 + (int)(i * texsize);
					Write2->DrawString("NO." + std::to_string(g_flor[i][j].cardno) + "\nRank" + std::to_string(g_flor[i][j].cardrank), { h, z, 1920, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);

				}
			}
		}
	}

	for (int i = 0; i < 100; i++)
	{
		float texsize = 0;

		MapWidth > MapHeight ? texsize = 1000.0f / (float)MapWidth : texsize = 1000.0f / (float)MapHeight;
		for (int j = 0; j < 100; j++)
		{
			if (g_flor[i][j].enemyno > -1)
			{
				DrawSpriteColor(g_enemytex,
					460 + (int)((j)*texsize), 50 + (int)(i * texsize),
					texsize, texsize * 1.4f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					DIK_COLER_WHITE
				);
				if (g_cardpv == true)
				{
					DrawSpriteColor(g_Flortex,
						460 + (int)((j)*texsize) + 25 + texsize - 10, 50 + (int)(i * texsize) + 5 + texsize,
						texsize + 50, texsize + 15,
						0.0f, 0.0f,
						1.0f, 1.0f,
						DIK_COLER_DRAKGRAY
					);
					float h = 460 + (int)((j)*texsize);
					float z = 50 + (int)(i * texsize);
					Write2->DrawString("NO." + std::to_string(g_flor[i][j].enemyno), { h, z, 1920, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);

				}
			}
		}
	}
	float texsize = 0;
	MapWidth > MapHeight ? texsize = 1000.0f / (float)MapWidth : texsize = 1000.0f / (float)MapHeight;
	int xnum = (GetMousePos().x - 456) / texsize;
	if (xnum > MapWidth - 1)
	{
		xnum = MapWidth - 1;
	}
	if (xnum < 0)
	{
		xnum = 0;
	}
	int ynum = (GetMousePos().y - 45) / texsize;
	if (ynum > MapHeight - 1)
	{
		ynum = MapHeight - 1;
	}
	if (ynum < 0)
	{
		ynum = 0;
	}
	float shift = 1.0f;
	if (GetKeyboardPress(DIK_LSHIFT))
	{
		shift = 3.0f;
		if (GetKeyboardPress(DIK_LCONTROL))
		{
			shift = 5.0f;
		}
	}

	DrawSpriteColor(g_Flortexcursor,
		460.0f + (float)((xnum)* (int)texsize), 50 + (float)(ynum * (int)texsize),
		texsize * shift +5, texsize * shift +5,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE);

	UiDescription({0.0f,0.0f});
	UiDescriptionSelect({ 1700.0f,30.0f });
	Write->DrawString("Q:通行可能床強調表示\nF1セーブ", { 0, 0, 1920, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);
}

void onof(bool n) {
	texton = n;
}
void SetText(std::string settext, float X, float Y, float size, D3DXCOLOR coler) {
	char* lentext = new char[settext.size() + 1];
	std::char_traits<char>::copy(lentext, settext.c_str(), settext.size() + 1);


		int pos[2] = {};
		for (unsigned int i = 0; i < strlen(lentext); i++)
		{

			pos[0] = ((int)lentext[i] - 32) % 16;
			pos[1] = (((int)lentext[i] - 32) / 16);

			float a[2] = { 1.0f / 16.0f ,0.16666f };
			DrawSpriteColorRotate(
				g_TexMozi,
				i * size * 0.8f + X, size * 2.0f + Y,
				size, size * 1.3f,
				a[0] * pos[0], a[1] * pos[1], a[0], a[1],
				coler.r, coler.g, coler.b, coler.a,
				0.0f
			);


		
	}
	delete[] lentext;
}
void Setflor(int x,int y, int type) {
	if (x >= 0 && x < MapWidth &&
		y >= 0 && y < MapHeight&&
		type > -1 && type < 3)
	{
		g_flor[x][y].state = (Tile)type;
	}
}
void SetflorTex(int x, int y, int tex) {
	if (x >= 0 && x < MapWidth &&
		y >= 0 && y < MapHeight )
	{
		g_flor[x][y].tex = tex;
	}
}
void SetflorEnemy(int x, int y, int enemy) {
	if (x >= 0 && x < MapWidth &&
		y >= 0 && y < MapHeight)
	{
		g_flor[x][y].enemyno = enemy;
	}
}
void SetCard(int x, int y, int no,int rank) {
	if (x >= 0 && x < MapWidth &&
		y >= 0 && y < MapHeight)
	{
		g_flor[x][y].cardno = no;
		g_flor[x][y].cardrank = rank;
	}
}
int XYGAP(D3DXVECTOR2 num1, D3DXVECTOR2 num2) {
	return (int)((num1.x - num2.x < 0 ? num2.x - num1.x : num1.x - num2.x) + (num1.y - num2.y < 0 ? num2.y - num1.y : num1.y - num2.y));
}

void UiDescription(D3DXVECTOR2 pos) {
	float texsize = 30;

	DrawSpriteColor(g_uitex,
		pos.x + texsize / 2.0f + 20, pos.y + 100,
		texsize + 10, texsize + 10,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE
	);
	DrawSpriteColor(g_Flortexwall,
		pos.x + texsize / 2.0f + 20, pos.y + 100,
		texsize , texsize ,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE
	);
	Write->DrawString("壁床",{ pos.x + texsize / 2.0f + 50, pos.y + 80, 350, 1080}, D2D1_DRAW_TEXT_OPTIONS_NONE);

	DrawSpriteColor(g_uitex,
		pos.x + texsize / 2.0f + 20, pos.y + 150,
		texsize + 10, texsize + 10,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE
	);
	DrawSpriteColor(g_Flortex,
		pos.x + texsize / 2.0f + 20, pos.y + 150,
		texsize, texsize,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE
	);
	Write->DrawString("通常床", { pos.x + texsize / 2.0f + 50, pos.y + 130, 350, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);

	DrawSpriteColor(g_uitex,
		pos.x + texsize / 2.0f + 20, pos.y + 200,
		texsize + 10, texsize + 10,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE
	);
	DrawSpriteColor(g_Flortexpaper,
		pos.x + texsize / 2.0f + 20, pos.y + 200,
		texsize, texsize,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE
	);
	Write->DrawString("紙床", { pos.x + texsize / 2.0f + 50, pos.y + 180, 350, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);
	Write->DrawString("左クリック:塗る\nシフト左クリック:3×3塗り シフト左+Lctrl5×5\nLshift データ表示\nN,Mカードナンバー上げ下げ\nK,Lカードランク上げ下げ\nO,Pエネミーナンバー上げ下げ", { pos.x  , pos.y + 220, 350, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);
}
void UiDescriptionSelect(D3DXVECTOR2 pos) {
	float size = 220.0f;
	DrawSpriteColor(g_uitex,
		pos.x + 90, pos.y + 260 + 350,
		220, 700,
		0.1f, 0.1f,
		0.8f, 0.8f,
		DIK_COLER_WHITE);
	DrawSpriteColor(g_uitex2,
		pos.x + size / 2.0f -20 , pos.y +20,
		size, size,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE);
	DrawSpriteColor(g_uitex2,
		pos.x + size / 2.0f - 20, pos.y + 80,
		size, size,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE);
	DrawSpriteColor(g_uitex2,
		pos.x + size / 2.0f - 20, pos.y + 140,
		size, size,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE);
	DrawSpriteColor(g_uitex2,
		pos.x + size / 2.0f - 20, pos.y + 200,
		size, size,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE);
	DrawSpriteColor(g_uitex2,
		pos.x + size / 2.0f - 20, pos.y + 260,
		size, size,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE);
	DrawSpriteColor(g_uitex2,
		pos.x + size / 2.0f - 20, pos.y + 960,
		size, size,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE);
	Write->DrawString("cardno" + std::to_string(g_cardno), { pos.x - 200, pos.y + 240 , 1920, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);
	Write->DrawString("cardrank" + std::to_string(g_cardrank), { pos.x - 200, pos.y + 265 , 1920, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);
	Write->DrawString("Enemyno" + std::to_string(g_enemyno), { pos.x - 200, pos.y + 940 , 1920, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);
	if (g_mode > -1 && g_mode < 5)
	{
		DrawSpriteColor(g_Flortexcursor,
			pos.x + size / 2.0f - 20, pos.y + 20 + g_mode * 60,
			size, size * 0.3f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			DIK_COLER_WHITE);
	}
	if (g_mode == 5)
	{
		DrawSpriteColor(g_Flortexcursor,
			pos.x + size / 2.0f - 20, pos.y + 960,
			size, size * 0.3f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			DIK_COLER_WHITE);
	}
	for (int  i = 0; i < 8; i++)
	{
		if (RefImageMaterial().Floor_Image[i] != -1) {
			DrawSpriteColor(RefImageMaterial().Floor_Image[i],
				pos.x + (i % 2)* 100.0f + 30, pos.y + (float)(i / 2) * 150.0f + 370,
				70, 70 ,
				0.0f, 0.0f,
				1.0f, 1.0f,
				DIK_COLER_WHITE);
			D3DXCOLOR coler = DIK_COLER_WHITE;
			switch (RefImageMaterial().Floor_Image[i])
			{
			case 1:coler = {1.0f,0.0f,0.0f,1.0f};
				break;
			case 2:coler = { 1.0f,0.0f,1.0f,1.0f };
				break;
			case 3:coler = { 0.0f,0.0f,1.0f,1.0f };
				break;
			case 4:coler = { 1.0f,0.5f,0.0f,1.0f };
				break;
			case 5:coler = { 1.0f,1.0f,0.0f,1.0f };
				break;
			case 6:coler = { 0.5f,0.5f,0.5f,1.0f };
				break;
			case 7:coler = { 0.5f,0.75f,1.0f,1.0f };
				break;
			default:
				break;
			}
			DrawSpriteColor(g_uitex3,
				pos.x + (i % 2) * 100.0f + 30, pos.y + (float)(i / 2) * 150.0f + 370 + 50,
				70, 20,
				0.0f, 0.0f,
				1.0f, 1.0f,
				coler);
		}
		
	}
	DrawSpriteColor(g_Flortexcursor,
		pos.x + (g_texmode % 2) * 100.0f + 30, pos.y + (float)(g_texmode / 2) * 150.0f + 370,
		100, 100,
		0.0f, 0.0f,
		1.0f, 1.0f,
		DIK_COLER_WHITE);
	Write->DrawString("1:壁床モード", { pos.x , pos.y , 1920, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);
	Write->DrawString("2:普通床モード",{ pos.x , pos.y + 60, 1920, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);
	Write->DrawString("3:紙床モード", { pos.x , pos.y + 120, 1920, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);
	Write->DrawString("4:TEX設定モード", { pos.x , pos.y + 180, 1920, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);
	Write->DrawString("5:カード設置モード", { pos.x , pos.y + 240, 1920, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);
	Write->DrawString("6:エネミー設置モード", { pos.x , pos.y + 940, 1920, 1080 }, D2D1_DRAW_TEXT_OPTIONS_NONE);
}
