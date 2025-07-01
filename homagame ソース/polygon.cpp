/*==============================================================================

   頂点管理 [polygon.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygon.h"
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "particle.h"
#include "main.h"
#include <math.h>
#include "winuser.h"
#include "player.h"
#include "sound.h"
#include "map.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_POLYGON 100	//表示するポリゴンの数
#define MAX_DAMAGETEXT 256
#define PTN_WIDTH (1.0f / 5)
#define PTN_HEIGHT (1.0f / 2)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

typedef struct {
	bool use;//使っているか
	float damage;//ダメージ
	int vel;
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXCOLOR		color;	//頂点カラー
	int type;
	int time;//存在時間
}TEXTR;
typedef struct POLYGON {
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		vel;	//速度ベクトル
	D3DXCOLOR		color;	//頂点カラー
	float			rot;
}POLYGON;
int bgmsoundvolume = 10;
int sesoundvolume = 10;
D3DXVECTOR2 camera;
D3DXVECTOR2 corsor;
D3DXVECTOR2 bgcorsor;
TEXTR damagetext[MAX_DAMAGETEXT];
float portaltime = 0; 
float portaltimeloop = 0;
static POLYGON g_Polygon[NUM_POLYGON];
static int g_bg = 0;//バックグラウンド
static int g_bgmap[2] = {};//バックグラウンド
static int g_TexNo = 0;
static int g_TexMozi[2] = {};//文字のテクスチャ
static int g_Texcursor = 0;//カーソルのテクスチャ
static int g_hitbox = 0;//ヒットボックスのテクスチャ
static int g_town = 0;//町バックグラウンド
int crafttex[3] = {};
int whitetex = 0;
int itemnom[32] = {};
int portalui[2] = {};
int gui = 0;
int gui2 = 0;
int gui3 = 0;
int gui4 = 0;
int gui5 = 0;
int guihead = 0;
int guiring = 0;
int g_hpber3 = 0;
int g_plrtal = 0;
int uitex[3] = {};
int sound[1] = {};
int flagtex = 0;
bool inventopen = false;
bool shopopen = false;//ショップが開いているか
bool craftopen = false;//クラフトが開いているか
int shopmode = 1;//ショップの売るモードか買うモード
int shopbuypage = 0;//ショップで開いているページ
int shopbuyclect = -1;//ショップで買うアイテム選択
int craftpage = 0;//クラフトで開いているページ
int craftclect = -1;//クラフトで買うアイテム選択
int gamestage = 0;//ゲームの進行度;
PORTAL portal = {};
POINT oldpoipos;
HWND hwndFound;
RECT rectpos;
POINT p;
int itemnameshowtime;
int hoir;
WEAPONITEM itemhave = {};//カーソルで持ってるアイテム
int itemhavenam = -1;
int stageflag[4][10] = {};
int stagemassage =150;
int diemassage = 150;
int stagecriar = 150;
//=============================================================================
// 初期化処理
//=============================================================================
void InitPolygon(void)
{

	ID3D11Device* pDevice = GetDevice();
	corsor.x = 0;
	corsor.y = 0;
	//sound[0] = LoadSound((char*)"data/SOUND/bomb000.wav");
	//テクスチャの読み込み
	g_bg = LoadTexture((char*)"data/TEXTURE/map.png");
	itemnom[0] = LoadTexture((char*)"data/TEXTURE/sword.png");
	itemnom[1] = LoadTexture((char*)"data/TEXTURE/magic wand.png");
	itemnom[2] = LoadTexture((char*)"data/TEXTURE/stick.png");
	itemnom[3] = LoadTexture((char*)"data/TEXTURE/slimegel.png");
	itemnom[4] = LoadTexture((char*)"data/TEXTURE/UIleatherhelmet.png");
	itemnom[5] = LoadTexture((char*)"data/TEXTURE/potion2.png");
	itemnom[6] = LoadTexture((char*)"data/TEXTURE/potion3.png");
	itemnom[7] = LoadTexture((char*)"data/TEXTURE/potion4.png");
	itemnom[8] = LoadTexture((char*)"data/TEXTURE/axe.png");
	itemnom[9] = LoadTexture((char*)"data/TEXTURE/shot sword.png");
	itemnom[10] = LoadTexture((char*)"data/TEXTURE/as sword.png");
	itemnom[11] = LoadTexture((char*)"data/TEXTURE/great axe.png");
	itemnom[12] = LoadTexture((char*)"data/TEXTURE/skill wand.png");
	itemnom[13] = LoadTexture((char*)"data/TEXTURE/crystal.png");
	itemnom[14] = LoadTexture((char*)"data/TEXTURE/iron.png");
	itemnom[15] = LoadTexture((char*)"data/TEXTURE/ring1.png");
	itemnom[16] = LoadTexture((char*)"data/TEXTURE/ring2.png");
	itemnom[17] = LoadTexture((char*)"data/TEXTURE/ring3.png");
	itemnom[18] = LoadTexture((char*)"data/TEXTURE/ring4.png");
	itemnom[19] = LoadTexture((char*)"data/TEXTURE/ring5.png");
	itemnom[20] = LoadTexture((char*)"data/TEXTURE/leatherhelmet.png");
	itemnom[21] = LoadTexture((char*)"data/TEXTURE/ironhelmet.png");
	itemnom[22] = LoadTexture((char*)"data/TEXTURE/leather.png");
	itemnom[23] = LoadTexture((char*)"data/TEXTURE/dark iron.png");
	itemnom[24] = LoadTexture((char*)"data/TEXTURE/magic chest.png");
	itemnom[25] = LoadTexture((char*)"data/TEXTURE/shotgun.png");
	g_TexMozi[0] = LoadTexture((char*)"data/TEXTURE/mozi3.png");
	g_TexMozi[1] = LoadTexture((char*)"data/TEXTURE/mozi4.png");
	g_Texcursor = LoadTexture((char*)"data/TEXTURE/cursor.png");
	g_hitbox = LoadTexture((char*)"data/TEXTURE/hitbox.png");
	gui = LoadTexture((char*)"data/TEXTURE/gui.png");
	gui2 = LoadTexture((char*)"data/TEXTURE/gui2.png");
	gui3 = LoadTexture((char*)"data/TEXTURE/gui3.png");
	gui4 = LoadTexture((char*)"data/TEXTURE/invent.png");
	gui5 = LoadTexture((char*)"data/TEXTURE/gui4.png");
	guihead = LoadTexture((char*)"data/TEXTURE/guihead.png");
	guiring = LoadTexture((char*)"data/TEXTURE/guiring.png");
	g_hpber3 = LoadTexture((char*)"data/TEXTURE/hpbar3.png");
	g_bgmap[0] = LoadTexture((char*)"data/TEXTURE/map2.png");
	g_bgmap[1] = LoadTexture((char*)"data/TEXTURE/shop.png");
	whitetex = LoadTexture((char*)"data/TEXTURE/hitbox.png");
	uitex[0] = LoadTexture((char*)"data/TEXTURE/Ficon.png");
	uitex[1] = LoadTexture((char*)"data/TEXTURE/shopui.png");
	uitex[2] = LoadTexture((char*)"data/TEXTURE/shopui2.png");
	crafttex[0] = LoadTexture((char*)"data/TEXTURE/craftui.png");
	g_plrtal = LoadTexture((char*)"data/TEXTURE/portal.png");
	portalui[0] = LoadTexture((char*)"data/TEXTURE/portalui1.png");
	portalui[1] = LoadTexture((char*)"data/TEXTURE/yazibar.png");
	flagtex = LoadTexture((char*)"data/TEXTURE/flag.png");
	//初期化

	camera.x = 0.0f;
	camera.y = 0.0f;
	for (int i = 0; i < NUM_POLYGON; i++)
	{
		g_Polygon[i].pos.x = frand() * SCREEN_WIDTH;
		g_Polygon[i].pos.y = frand() * SCREEN_HEIGHT;

		g_Polygon[i].vel.x = 0.0f;
		g_Polygon[i].vel.y = 0.0f;

		g_Polygon[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		g_Polygon[i].rot = frand() * (D3DX_PI * 2);
	}
	for (int i = 0; i < MAX_DAMAGETEXT; i++)
	{
		damagetext[i].color = { 1.0f ,1.0f ,1.0f ,1.0f };
		damagetext[i].damage = 0;
		damagetext[i].pos = { 0.0f,0.0f };
		damagetext[i].time = 1;
		damagetext[i].use = false;
		damagetext[i].type = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			stageflag[i][j] = -1;
		}
	}
	
		stageflag[0][0] = 0;
	

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
	stagemassage++;
	diemassage++;
	stagecriar++;
	PLAYER player = *GetPlayerStatus();

	if ((float)GetMouseZ() > 0)
	{
		itemnameshowtime = 80;
		hoir -= 1;
	}
	if ((float)GetMouseZ() < 0)
	{
		itemnameshowtime = 80;
		hoir += 1;
	}
	if (player.pos.x > 520 && portaltime < 40)
	{
		portaltime += 2;
	}
	if (portaltime > 38)
	{
		portaltimeloop++;
	}
	if (portaltime > 0)
	{
		portaltime--;
	}

	if (hoir > 4)
	{
		hoir = 0;
	}
	if (hoir < 0)
	{
		hoir = 4;
	}
	if (itemnameshowtime > 0)
	{
		itemnameshowtime--;
	}
	if (*Getgoalpos() < player.pos.x && *Getgoalpos() > 0)
	{
		PlaySound(5, 0);
		stageflag[0][Getgomap() ] = 0;
		Setmap(0); 
		stagemassage = 150;
		stagecriar = 0;
		
	}
	//マウスポインター座標取得
	if (GetKeyboardPress(DIK_H) && GetKeyboardPress(DIK_A) && GetKeyboardPress(DIK_N) && GetKeyboardPress(DIK_Y) && GetKeyboardPress(DIK_M)) {
		for (int i = 0; i < 10; i++)
		{
			stageflag[0][i] = 0;
		}
	}
	GetWindowRect(GetHwnd(), &rectpos);
	if (GetCursorPos(&p)) {

		if (inventopen == false && shopopen == false && craftopen == false)
		{
			bgcorsor.x = (float)p.x * SCREEN_WIDTH / (rectpos.right - rectpos.left) - rectpos.left * 2;
			bgcorsor.y = (float)p.y * SCREEN_HEIGHT / (rectpos.bottom - rectpos.top) - rectpos.top * 2;
		}
		corsor.x = (float)p.x * SCREEN_WIDTH / (rectpos.right - rectpos.left) - rectpos.left * 2;
		corsor.y = (float)p.y * SCREEN_HEIGHT / (rectpos.bottom - rectpos.top) - rectpos.top * 2;
		if ((float)p.x < rectpos.left)
		{
			corsor.x = 0;
		}
		if ((float)p.x > rectpos.right)
		{
			corsor.x = SCREEN_WIDTH;
		}

		if ((float)p.y < rectpos.top)
		{
			corsor.y = 0;
		}
		if ((float)p.y > rectpos.bottom)
		{
			corsor.y = SCREEN_HEIGHT;
		}

	}
	//カーソルが画面外に出ないように
	if (corsor.x < 20)
		corsor.x = 20;
	if (corsor.x > 1890)
		corsor.x = 1890;
	if (corsor.y < 33)
		corsor.y = 33;
	if (corsor.y > 1050)
		corsor.y = 1050;
	if (player.vel.y < -10 && frand() < 0.5f)
	{
		setparticle(
			1,
			player.pos.x, player.pos.y + 35,
			5.0f, 5.0f,
			1.0f, 1, 20,
			0.5f, 0.1f,
			0.1f, 0.0f,
			1.0f, 0.5f,
			0.85f, 0.0f,
			0.6f, 0.6f, 0.6f);
	}
	for (int i = 0; i < 14; i++)
	{
		SetVolume(i, sesoundvolume * 0.005f);
	}
	SetVolume(1, sesoundvolume * 0.05f);
	if (Getgomap() == 0)
	{

		SetVolume(6, Getbgmvol() * 0.005f);
		SetVolume(11, Getbgmvol() * 0.005f);
		SetVolume(12, 0); 
		SetVolume(13,0);

	}
	if (Getgomap() >= 1 && Getgomap() <= 9)
	{

		SetVolume(6, Getbgmvol() * 0.005f);
		SetVolume(11, 0);
		SetVolume(12, Getbgmvol() * 0.005f);
		SetVolume(13, 0);

	}
	if (Getgomap()== 10)
	{

		SetVolume(6, Getbgmvol() * 0.005f);
		SetVolume(11, 0);
		SetVolume(12, 0);
		SetVolume(13, Getbgmvol() * 0.005f);

	}
	if (IsMouseLeftTriggered() && 
		corsor.x > 350 -40 && corsor.x < 350 + 40&&
		corsor.y > 970 - 25 && corsor.y < 970 + 25 && bgmsoundvolume > 0)
	{
		bgmsoundvolume--;
	}
	if (IsMouseLeftTriggered() &&
		corsor.x > 450 - 40 && corsor.x < 450 + 40 &&
		corsor.y > 970 - 25 && corsor.y < 970 + 25 && bgmsoundvolume < 100)
	{
		bgmsoundvolume++;
	}
	if (IsMouseLeftTriggered() &&
		corsor.x > 350 - 40 && corsor.x < 350 + 40 &&
		corsor.y > 1020 - 25 && corsor.y < 1020 + 25 && sesoundvolume > 0)
	{
		sesoundvolume--;
	}
	if (IsMouseLeftTriggered() &&
		corsor.x > 450 - 40 && corsor.x < 450 + 40 &&
		corsor.y > 1020 - 25 && corsor.y < 1020 + 25 && sesoundvolume < 100)
	{
		sesoundvolume++;
	}
	//キーボード


	if (GetKeyboardPress(DIK_D) && inventopen == false && shopopen == false && craftopen == false)
	{
		camera.x -= 0.0016f;

	}
	if (GetKeyboardPress(DIK_A) && inventopen == false && shopopen == false && craftopen == false)
	{
		camera.x += 0.0016f;

	}

	if (camera.x > 0.06f)
	{
		camera.x = 0.06f;
	}
	if (camera.x < -0.06f)
	{
		camera.x = -0.06f;
	}
	if (camera.x > 0)
	{
		camera.x -= 0.0006f;
	}
	if (camera.x < 0)
	{
		camera.x += 0.0006f;
	}



	//座標を取る
	//atan2(g_Player.pos.y - corsor.y, g_Player.pos.x - corsor.x)) / PAI + 1

	if (player.nowhp <= 0)
	{
		Setmap(0);
		diemassage = 0;
		stagemassage = 150;
	}
	
	if (GetKeyboardTrigger(DIK_E))
	{
		while (1)
		{
			if (inventopen == false && shopopen == false&& craftopen == false && portal.open == false)
			{
				inventopen = true;
				PlaySound(2, 0);
				break;
			}
			if (inventopen == true)
			{
				inventopen = false;
				PlaySound(2, 0);
				break;
			}
			break;
		}

	}
	if (GetKeyboardTrigger(DIK_F))
	{

		if (player.pos.x < 20 && Getmaptex() == 0)
		{
			Setmap(0);
		}
		while (1)
		{
			if (shopopen == false && Getmaptex() == 1 && player.pos.x > 220 && player.pos.x < 250 && inventopen == false)
			{
				shopopen = true;
				PlaySound(2, 0);
				break;
			}
			if (shopopen == true)
			{
				shopopen = false;
				PlaySound(2, 0);
				break;
			}
			break;
		}
		while (1)
		{
			if (craftopen == false && Getmaptex() == 1 && player.pos.x > 380 && player.pos.x < 420 && inventopen == false)
			{
				craftopen = true;
				PlaySound(2, 0);
				break;
			}
			if (craftopen == true)
			{
				craftopen = false;
				PlaySound(2, 0);
				break;
			}
			break;
		}
		while (1)
		{
			if (portal.open == false && Getmaptex() == 1 && player.pos.x > 550 && player.pos.x < 640 && inventopen == false)
			{
				portal.open = true;
				PlaySound(2, 0);
				break;
			}
			if (portal.open == true)
			{
				portal.open = false;
				PlaySound(2, 0);
				break;
			}
			break;
		}
	}

	for (int i = 0; i < MAX_DAMAGETEXT; i++)
	{
		if (damagetext[i].use == true)
		{
			damagetext[i].time += 1;
		}
		if (damagetext[i].use == true && damagetext[i].time > 60)
		{
			damagetext[i].use = false;
		}


	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{
	PLAYER player = *GetPlayerStatus();

	//bg
	float scrollrete = 7630.0f;
	float mapscare = 1;
	if (Getmaptex() == 1)
	{
		mapscare = 400.0f / 990.0f;
	}
	DrawSpriteColorRotate(g_bgmap[Getmaptex()],
		player.pos.x * 0.000614f * -7630 - camera.x * 0.2125f * -scrollrete + (bgcorsor.x - (SCREEN_WIDTH * 0.5f)) * 0.000012882f * -scrollrete + 4750 * mapscare + (1 - mapscare) * 800
		, SCREEN_HEIGHT * 0.5f,
		SCREEN_WIDTH * 4 * mapscare, SCREEN_HEIGHT,
		0, 0.43f,
		1.0f, 0.57f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f);
	//町のポータル表示
	if (Getmaptex() == 1)
	{
		if (portaltime > 38)
		{
			DrawSpriteColorRotate(g_plrtal,
				player.pos.x * 0.000614f * -7630 - camera.x * 0.2125f * -scrollrete + (bgcorsor.x - (SCREEN_WIDTH * 0.5f)) * 0.000012882f * -scrollrete + 4750 * mapscare + (1 - mapscare) * 800 + 1400
				, SCREEN_HEIGHT * 0.5f + 5,
				300, 600,
				(int)(portaltimeloop / 15) * 0.25f, 0.5f,
				0.25f, 0.50f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f);
		}
		else
		{
			DrawSpriteColorRotate(g_plrtal,
				player.pos.x * 0.000614f * -7630 - camera.x * 0.2125f * -scrollrete + (bgcorsor.x - (SCREEN_WIDTH * 0.5f)) * 0.000012882f * -scrollrete + 4750 * mapscare + (1 - mapscare) * 800 + 1400
				, SCREEN_HEIGHT * 0.5f + 5,
				300, 600,
				(int)(portaltime / 15) * 0.25f, 0.0f,
				0.25f, 0.50f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f);
		}

	}

	//ゴールのフラッグ表示
	if (*Getgoalpos() > 0)
	{
		DrawSpriteColorRotate(flagtex,
			player.pos.x * 0.000614f * -7630 - camera.x * 0.2125f * -scrollrete + (bgcorsor.x - (SCREEN_WIDTH * 0.5f)) * 0.000012882f * -scrollrete + 4750 * mapscare + (1 - mapscare) * 800  -3700 + *Getgoalpos() * 4.6
			, 700,
			300, 300,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0.0f);
	}
	//町で店に近づいた時にＦアイコン表示
	if (player.pos.x > 220 && player.pos.x < 250 && Getmaptex() == 1)
	{
		DrawSpriteColorRotate(uitex[0],
			SCREEN_WIDTH * 0.5f + (230 - player.pos.x) * 4.7f - (bgcorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + camera.x * 1650, 650,
			70, 70,
			0, 0,
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0);
	}

	//町で鍛冶屋に近づいた時にＦアイコン表示
	if (player.pos.x >380 && player.pos.x < 420 && Getmaptex() == 1)
	{
		DrawSpriteColorRotate(uitex[0],
			SCREEN_WIDTH * 0.5f + (400 - player.pos.x) * 4.7f - (bgcorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + camera.x * 1650, 650,
			70, 70,
			0, 0,
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0);
	}
	//町でポータルに近づいた時にＦアイコン表示
	if (player.pos.x > 550 && player.pos.x < 640&& Getmaptex() == 1)
	{
		DrawSpriteColorRotate(uitex[0],
			SCREEN_WIDTH * 0.5f + (575 - player.pos.x) * 4.7f - (bgcorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + camera.x * 1650, 650,
			70, 70,
			0, 0,
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0);
	}

	//ダンジョン内で左の壁に近づいた時Ｆアイコン表示
	if (player.pos.x < 20  && Getmaptex() == 0)
	{
		DrawSpriteColorRotate(uitex[0],
			SCREEN_WIDTH * 0.5f + (10 - player.pos.x) * 4.7f - (bgcorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + camera.x * 1650, 650,
			70, 70,
			0, 0,
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0);
		SetText("Back to town", SCREEN_WIDTH * 0.5f + (10 - player.pos.x) * 4.7f - (bgcorsor.x - SCREEN_WIDTH * 0.5f) * 0.10f + camera.x * 1650, 650, 20,1.0f, 1.0f, 1.0f, 1.0f,1);
	}
	//座標の表示のボード表示
	DrawSpriteColorRotate(g_bg,
		180, 130,
		200.0f, 100.0f,
		0.0f, 0.0f,
		0.1f, 0.1f,
		1.0f, 1.0f, 0.8f, 0.5f,
		0);
	//テキスト表示
	if (((player.pos.x > 220 && player.pos.x < 250) || (player.pos.x > 380 && player.pos.x < 420) || (player.pos.x > 550 && player.pos.x < 640)) && Getmaptex() == 1)
	{
		SetText("F   Open", 25, 920, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
	}
	SetText("AD  Move", 25, 1000,30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
	SetText("E   Inventory", 25, 960, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
	SetText("Left-click  attack", 1400, 1000, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
	SetText("Right-click useitem", 1400, 960, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
}
void DrawPolygon2(void) {
	//
	PLAYER player = *GetPlayerStatus();
	std::string text;
	//プレイヤー座標表示
	{
		text = "X:" + std::to_string((int)player.pos.x);
		SetText(text, 100, 50, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
		text = "Y:" + std::to_string((int)player.pos.y - 800);
		SetText(text, 100, 100, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
	}
	//ダメージテキスト表示
	for (int i = 0; i < MAX_DAMAGETEXT; i++)
	{
		if (damagetext[i].use == true && damagetext[i].type == 1)
		{
			SetText(std::to_string((int)damagetext[i].damage) + "." + std::to_string((int)(damagetext[i].damage * 10) % 10),
				SCREEN_WIDTH * 0.5f + (damagetext[i].pos.x - player.pos.x) * 4.7f - (damagetext[i].time * damagetext[i].vel) * 1.0f + camera.x * 1600.0f - (corsor.x - (SCREEN_WIDTH * 0.5f + camera.x * 1500.0f)) * 0.1f,
				damagetext[i].pos.y - 25.0f - sinf(damagetext[i].time / 14.0f) * 10,
				20,
				damagetext[i].color.r, damagetext[i].color.g, damagetext[i].color.b, 5.0f - damagetext[i].time / 10.0f, 1);
		}
		if (damagetext[i].use == true && damagetext[i].type == 2)
		{
			SetText(std::to_string((int)damagetext[i].damage) + "." + std::to_string((int)(damagetext[i].damage * 10) % 10),
				SCREEN_WIDTH * 0.5f + (damagetext[i].pos.x - player.pos.x) * 4.7f - (damagetext[i].time * damagetext[i].vel) * 1.0f + camera.x * 1600.0f - (corsor.x - (SCREEN_WIDTH * 0.5f + camera.x * 1500.0f)) * 0.1f,
				damagetext[i].pos.y - 25.0f - sinf(damagetext[i].time / 14.0f) * 10,
				25.0f + (damagetext[i].time / 10.0f),
				damagetext[i].color.r, damagetext[i].color.g, damagetext[i].color.b, 5.0f - damagetext[i].time / 10.0f, 1);
		}
		if (damagetext[i].use == true && damagetext[i].type == 3)
		{
			DrawSpriteColorRotate(Getparticletex(1),
				SCREEN_WIDTH * 0.5f - 30 + (damagetext[i].pos.x - player.pos.x) * 4.7f - (damagetext[i].time * damagetext[i].vel) * 1.0f + camera.x * 1600.0f - (corsor.x - (SCREEN_WIDTH * 0.5f + camera.x * 1500.0f)) * 0.1f,
				damagetext[i].pos.y - 0 - sinf(damagetext[i].time / 14.0f) * 10,
				25.0f, 25.0f,
				0.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 0.2f, 0.0f, 5.0f - damagetext[i].time / 10.0f,
				0);
			SetText(std::to_string((int)damagetext[i].damage) + "." + std::to_string((int)(damagetext[i].damage * 10) % 10),
				SCREEN_WIDTH * 0.5f + (damagetext[i].pos.x - player.pos.x) * 4.7f - (damagetext[i].time * damagetext[i].vel) * 1.0f + camera.x * 1600.0f - (corsor.x - (SCREEN_WIDTH * 0.5f + camera.x * 1500.0f)) * 0.1f,
				damagetext[i].pos.y - 25.0f - sinf(damagetext[i].time / 14.0f) * 10,
				25.0f + (damagetext[i].time / 10.0f),
				damagetext[i].color.r, damagetext[i].color.g, damagetext[i].color.b, 5.0f - damagetext[i].time / 10.0f, 1);
		}

	}
	//プレイヤーホットバー
	for (int i = 0; i < 5; i++)
	{
		DrawSpriteColorRotate(gui,
			SCREEN_WIDTH * 0.5f - 220.0f + i * 115, 980.0f,
			120.0f, 120.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0);
		if (player.inventory[i].itemno > 0)
		{
			DrawSpriteColorRotate(itemnom[player.inventory[i].itemtex - 1],
				SCREEN_WIDTH * 0.5f - 170.0f + i * 115 - player.inventory[i].size * 0.5f * 1.25f, 1030.0f - player.inventory[i].size * 0.5f * 1.25f,
				player.inventory[i].size*1.25f, player.inventory[i].size * 1.25f,
				0.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0);
			if (player.inventory[i].count > 1)
			{
				text = std::to_string((int)player.inventory[i].count);
				SetText(text, SCREEN_WIDTH * 0.5f - 220.0f + i * 115 + 35, 980.0f, 20, 1.0f, 1.0f, 1.0f, 1.0f, 1);
			}
			//スキルクールタイム中ならひょうじ
			if (player.inventory[i].skill > 0 && player.inventory[i].skillct > 0)
			{
				DrawSpriteColorRotate(whitetex,
					SCREEN_WIDTH * 0.5f - 220.0f + i * 115, 980.0f + 50.0f - 50.0f * (player.inventory[i].skillct / (float)Getskillct(player.inventory[i].skill)),
					100.0f, 100.0f * (player.inventory[i].skillct / (float)Getskillct(player.inventory[i].skill)),
					0.1f, 0.1f,
					0.1f, 0.1f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0);
				SetText(std::to_string((int)(player.inventory[i].skillct / 60)) + "." + std::to_string(((int)((float)player.inventory[i].skillct / 60.0f * 10.0f) % 10)), SCREEN_WIDTH * 0.5f - 230.0f + i * 115, 940.0f, 20, 1.0f, 1.0f, 1.0f, 1.0f, 1);
			}
		}
	}
	//HPバー表示
	{
		DrawSpriteColorRotate(whitetex,
			SCREEN_WIDTH * 0.5f + 10.0f, 900,
			600.0f, 32.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
			0);
		text = std::to_string((int)player.nowhp);
		DrawSpriteColorRotate(g_hpber3,
			SCREEN_WIDTH * 0.5f + 10.0f - 300 + 300 * (player.nowhp / player.maxhp), 900,
			600.0f * (player.nowhp / player.maxhp), 32.0f,
			0.0f, 0.0f,
			1.0f * (player.nowhp / player.maxhp), 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0);
		text = std::to_string((int)player.nowhp);
		SetText(text, SCREEN_WIDTH * 0.5f - 100, 855.0f, 23.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1);
		SetText("/", SCREEN_WIDTH * 0.5f, 855.0f, 23.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1);
		text = std::to_string((int)player.maxhp);
		SetText(text, SCREEN_WIDTH * 0.5f + 100, 855.0f, 23.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1);
	}
	//プレイヤーの現在持っている場所の四角
	{
		DrawSpriteColorRotate(gui3,
			SCREEN_WIDTH * 0.5f - 220.0f + hoir * 115, 980.0f,
			120.0f, 120.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0);
	}
	//カーソルを合わせた時に武器の名前を表示する
	if (player.inventory[hoir].itemno > 0 && itemnameshowtime > 0)
	{
		SetText(player.inventory[hoir].name, SCREEN_WIDTH * 0.5f, 750, 25, 0.5f, 1.0f, 1.0f, (float)itemnameshowtime * 0.03f, 1);
	}
	//ステージ移動時の処理
	if (stagemassage < 150)
	{
		DrawSpriteColorRotate(g_bg, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, SCREEN_WIDTH, 200, 0.0f, 0.0f, 0.1f, 0.1f, 1.0f, 1.0f, 0.8f, 2.0f - (stagemassage / 75.0f), 0);
		float len = Getmapname().size();
		SetText(Getmapname(), SCREEN_WIDTH * 0.5f- len*20, SCREEN_HEIGHT * 0.5f - 75,40,1.0f, 1.0f, 1.0f, 2.0f - (stagemassage / 75.0f),1);
	}
	//死んだときの表示
	if (diemassage < 150)
	{
		DrawSpriteColorRotate(g_bg, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, SCREEN_WIDTH, 200, 0.0f, 0.0f, 0.1f, 0.1f, 1.0f, 1.0f, 0.8f, 2.0f - (diemassage / 75.0f), 0);
		
		SetText("YOU DEAD", SCREEN_WIDTH * 0.5f - 160, SCREEN_HEIGHT * 0.5f - 150, 80, 1.0f, 0.2f, 0.2f, 2.0f - (diemassage / 75.0f), 1);
	}
	//ステージクリアの時の表示
	if (stagecriar < 150)
	{
		DrawSpriteColorRotate(g_bg, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, SCREEN_WIDTH, 200, 0.0f, 0.0f, 0.1f, 0.1f, 1.5f, 1.5f, 1.2f, 2.0f - (stagecriar / 75.0f), 0);

		SetText("Stage Complete", SCREEN_WIDTH * 0.5f - 320, SCREEN_HEIGHT * 0.5f - 150, 80, 0.8f, 0.8f, 0.0f, 2.0f - (stagecriar / 75.0f), 1);
	}
	//ショップ表示
	if (shopopen == true)
	{
		DrawSpriteColorRotate(g_bg, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 0.1f, 0.1f, 1.0f, 1.0f, 0.8f, 0.5f, 0);

		if (shopmode == 0)
		{
			//インベントリスロット表示
			DrawSpriteColorRotate(gui2, SCREEN_WIDTH * 0.5f, 450.0f, 800.0f, 500.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);
			DrawSpriteColorRotate(gui2, SCREEN_WIDTH * 0.5f, 810.0f, 800.0f, 200.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);
			DrawSpriteColorRotate(gui2, 1650, 600.0f, 500.0f, 800.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);

			for (int i = 0; i < 5; i++)
			{
				for (int h = 0; h < 3; h++)
				{
					//=================================================
					//上のgui
					// //=================================================
					//頭アイコン
					if (i == 3 && h == 0)
					{
						DrawSpriteColorRotate(guihead,
							SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 310.0f + 140.0f * h,
							150.0f, 150.0f,
							0.0f, 0.0f,
							1.0f, 1.0f,
							1.0f, 1.0f, 1.0f, 1.0f,
							0);
					}
					//リングアイコン
					else if (i == 4 && h == 0)
					{
						DrawSpriteColorRotate(guiring,
							SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 310.0f + 140.0f * h,
							150.0f, 150.0f,
							0.0f, 0.0f,
							1.0f, 1.0f,
							1.0f, 1.0f, 1.0f, 1.0f,
							0);
					}
					//通常アイコン
					else {
						DrawSpriteColorRotate(gui,
							SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 310.0f + 140.0f * h,
							150.0f, 150.0f,
							0.0f, 0.0f,
							1.0f, 1.0f,
							1.0f, 1.0f, 1.0f, 1.0f,
							0);
					}


					//インベントリのアイテム表示
					if (player.inventory[5 * h + i + 5].itemno > 0)
					{

						DrawSpriteColorRotate(itemnom[player.inventory[5 * h + i + 5].itemtex - 1],
							SCREEN_WIDTH * 0.5f - 220.0f + i * 140 - player.inventory[5 * h + i + 5].size * 1.25f * 0.6f, 370.0f + 140.0f * h - player.inventory[5 * h + i + 5].size * 1.25f * 0.6f,
							player.inventory[5 * h + i + 5].size * 1.25f * 1.2f, player.inventory[5 * h + i + 5].size * 1.25f * 1.2f,

							0.0f, 0.0f,
							1.0f, 1.0f,
							1.0f, 1.0f, 1.0f, 1.0f,
							0);
						if (player.inventory[5 * h + i + 5].count > 1)
						{
							text = std::to_string((int)player.inventory[5 * h + i + 5].count);
							SetText(text, SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 35, 310.0f + 140.0f * h - 20, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
						}
						//スキルクールタイム中なら表示される
						if (player.inventory[5 * h + i + 5].skill > 0 && player.inventory[5 * h + i + 5].skillct > 0)
						{
							DrawSpriteColorRotate(whitetex,
								SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 310.0f + 140.0f * h + 65.0f - 65.0f * (player.inventory[5 * h + i + 5].skillct / (float)Getskillct(player.inventory[5 * h + i + 5].skill)),
								125.0f, 125.0f * (player.inventory[5 * h + i + 5].skillct / (float)Getskillct(player.inventory[5 * h + i + 5].skill)),
								0.1f, 0.1f,
								0.1f, 0.1f,
								1.0f, 1.0f, 1.0f, 1.0f,
								0);
						}

					}
					//インベントリにカーソルが重なると少し色がつく + アイテムがあった場合表示
					if (corsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && corsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&
						corsor.y >  310.0f + 140.0f * h - 60 && corsor.y < 310.0f + 140.0f * h + 60)
					{
						DrawSpriteColorRotate(g_bg,
							SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 310.0f + 140.0f * h,
							125.0f, 125.0f,
							0.0f, 0.0f,
							0.1f, 0.1f,
							2.0f, 2.0f, 0.7f, 0.5f,
							0);

					}


				}
				//=================================================
				//下側を表示
				//=================================================
				DrawSpriteColorRotate(gui,
					SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 810.0f,
					150.0f, 150.0f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0);
				if (player.inventory[i].itemno > 0)
				{
					DrawSpriteColorRotate(itemnom[player.inventory[i].itemtex - 1],
						SCREEN_WIDTH * 0.5f - 220.0f + i * 140 - player.inventory[i].size * 1.25f * 0.6f, 870.0f - player.inventory[i].size * 1.25f * 0.6f,
						player.inventory[i].size * 1.25f * 1.2f, player.inventory[i].size * 1.25f * 1.2f,
						0.0f, 0.0f,
						1.0f, 1.0f,
						1.0f, 1.0f, 1.0f, 1.0f,
						0);
					if (player.inventory[i].count > 1)
					{
						text = std::to_string((int)player.inventory[i].count);
						SetText(text, SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 35, 810.0f - 20, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
					}
					//スキルクールタイム中ならひょうじ
					if (player.inventory[i].skill > 0 && player.inventory[i].skillct > 0)
					{
						DrawSpriteColorRotate(whitetex,
							SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 810.0f + 65.0f - 65.0f * (player.inventory[i].skillct / (float)Getskillct(player.inventory[i].skill)),
							130.0f, 130.0f * (player.inventory[i].skillct / (float)Getskillct(player.inventory[i].skill)),
							0.1f, 0.1f,
							0.1f, 0.1f,
							1.0f, 1.0f, 1.0f, 1.0f,
							0);
					}
				}
				//インベントリにカーソルが重なると少し色がつく
				if (corsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && corsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&
					corsor.y >  810.0f - 60 && corsor.y < 810.0f + 60)
				{
					DrawSpriteColorRotate(g_bg,
						SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 810.0f,
						125.0f, 125.0f,
						0.0f, 0.0f,
						0.1f, 0.1f,
						2.0f, 2.0f, 0.7f, 0.5f,
						0);
				}
			}

			//アイテムを持っているとそこのアイコンに四角がつく
			if (hubna() > -1 && hubna() < 5)
			{
				DrawSpriteColorRotate(gui3,
					SCREEN_WIDTH * 0.5f - 280.0f + hubna() * 140, 810.0f,
					150.0f, 150.0f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0);
			}
			if (hubna() > 4)
			{
				DrawSpriteColorRotate(gui3,
					SCREEN_WIDTH * 0.5f - 280.0f + hubna() % 5 * 140, 180.0f + 140.0f * (int)(hubna() / 5),
					150.0f, 150.0f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0);
			}
			//=================================================
			//カーソルを合わせた時にテキスト表示
			//=================================================
			for (int i = 0; i < 5; i++)
			{
				for (int h = 0; h < 4; h++)
				{
					if (((corsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && corsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&
						corsor.y >  310.0f + 140.0f * h - 60 && corsor.y < 310.0f + 140.0f * h + 60 && player.inventory[5 + i + h * 5].itemno > 0 && h < 3) //インベントリ上の条件
						|| (corsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && corsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&//インベントリ下側の条件
							corsor.y >  810.0f - 60 && corsor.y < 810.0f + 60 && player.inventory[i].itemno > 0 && h == 3)))
					{
						int downinvent = 0;//下側のインベントリだった場合記録する
						if (corsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && corsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&//インベントリ下側の条件
							corsor.y >  810.0f - 60 && corsor.y < 810.0f + 60 && player.inventory[i].itemno > 0 && h == 3) {
							h = -1;
							downinvent = 1;
						}
						int a = 1;
						for (int d = 0; d < 4; d++)
						{
							if (player.inventory[5 + i + h * 5].showtext[d] != "")
							{
								a++;

							}
						}
						if (player.inventory[5 + i + h * 5].damage != 0)
						{
							a++;
						}
						if (player.inventory[5 + i + h * 5].skill != 0)
						{
							a += 2;
						}
						if (player.inventory[5 + i + h * 5].str != 0)
						{
							a++;
						}
						if (player.inventory[5 + i + h * 5].dex != 0)
						{
							a++;
						}
						if (player.inventory[5 + i + h * 5].vit != 0)
						{
							a++;
						}
						if (player.inventory[5 + i + h * 5].maxhp != 0)
						{
							a++;
						}
						if (player.inventory[5 + i + h * 5].armor != 0)
						{
							a++;
						}
						if (player.inventory[5 + i + h * 5].movespeed != 0)
						{
							a++;
						}
						if (player.inventory[5 + i + h * 5].attackspeed != 0)
						{
							a++;
						}
						if (player.inventory[5 + i + h * 5].range != 0)
						{
							a++;
						}
						int textsize = 13;
						char* lentext = new char[player.inventory[5 + i + h * 5].name.size() + 1];
						std::char_traits<char>::copy(lentext, player.inventory[5 + i + h * 5].name.c_str(), player.inventory[5 + i + h * 5].name.size() + 1);
						int f = (int)strlen(lentext);
						if (textsize < (int)strlen(lentext))
						{
							textsize = (int)strlen(lentext);


						}
						for (int d = 0; d < 4; d++)
						{
							char* lentext = new char[player.inventory[5 + i + h * 5].showtext[d].size() + 1];
							std::char_traits<char>::copy(lentext, player.inventory[5 + i + h * 5].showtext[d].c_str(), player.inventory[5 + i + h * 5].showtext[d].size() + 1);
							if (textsize < (int)strlen(lentext))
							{
								textsize = (int)strlen(lentext);
							}
						}
						if (textsize < (int)Getskillname(player.inventory[5 + i + h * 5].skill).length() + 6)
						{
							//+6は"skill "の分
							textsize = (int)Getskillname(player.inventory[5 + i + h * 5].skill).length() + 6;
						}
						DrawSpriteColorRotate(gui4,
							SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 12.5f, 310.0f + 140.0f * h + downinvent * 650 + a * 15 + 20,
							75.0f + textsize * 25, 15.0f + 30 + a * 30.0f,
							0.0f, 0.0f,
							1.0f, 0.5f,
							1.0f, 0.5f, 1.0f, 1.0f,
							PAI * 1.0f);
						DrawSpriteColorRotate(gui4,
							SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 12.5f, 310.0f + 140.0f * h + downinvent * 650,
							75.0f + textsize * 25, 15.0f,
							0.0f, 0.0f,
							1.0f, 1.0f,
							1.0f, 1.0f, 1.0f, 1.0f,
							0);
						DrawSpriteColorRotate(gui4,
							SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 12.5f,
							310.0f + 140.0f * h + downinvent * 650 + a * 30 + 40,
							75.0f + textsize * 25, 15.0f,
							0.0f, 0.0f,
							1.0f, 1.0f,
							1.0f, 1.0f, 1.0f, 1.0f,
							PAI * 1.0f);
						a = 0;
						SetText(player.inventory[5 + i + h * 5].name,
							SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3,
							290 + 140.0f * h + downinvent * 650 + 30 * a,
							25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
						a++;
						if (player.inventory[5 + i + h * 5].skill != 0)
						{
							float coler[3] = { 0.70f,0.7f,0.70f };
							SetText("Skill " + Getskillname(player.inventory[5 + i + h * 5].skill), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 27, coler[0], coler[1], coler[2], 1.0f, 1);

							a += 2;
						}
						for (int d = 0; d < 4; d++)
						{
							if (player.inventory[5 + i + h * 5].showtext[d] != "")
							{
								SetText(player.inventory[5 + i + h * 5].showtext[d], SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
								a++;

							}
						}

						if (player.inventory[5 + i + h * 5].damage != 0)
						{
							float coler[3] = { 0.75f,0.75f,0.75f };
							SetText("damage  ", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 0.2f, 0.8f, 0.2f, 1.0f, 1);
							SetText(std::to_string((int)player.inventory[5 + i + h * 5].damage) + "." + std::to_string((int)(player.inventory[5 + i + h * 5].damage * 10) % 10), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}

						if (player.inventory[5 + i + h * 5].str != 0)
						{
							float coler[3] = { 0.75f,0.82f,0.2f };
							std::string statustext = { "+" };
							if (player.inventory[5 + i + h * 5].str < 0)
							{
								coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
								statustext = { "" };
							}
							SetText("str     ", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 1.0f, 0.2f, 0.2f, 1.0f, 1);
							SetText(statustext + std::to_string((int)player.inventory[5 + i + h * 5].str), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (player.inventory[5 + i + h * 5].dex != 0)
						{
							float coler[3] = { 0.75f,0.82f,0.2f };
							std::string statustext = { "+" };
							if (player.inventory[5 + i + h * 5].dex < 0)
							{
								coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
								statustext = { "" };
							}
							SetText("dex     ", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 1.0f, 0.2f, 0.2f, 1.0f, 1);
							SetText(statustext + std::to_string((int)player.inventory[5 + i + h * 5].dex), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (player.inventory[5 + i + h * 5].vit != 0)
						{
							float coler[3] = { 0.75f,0.82f,0.2f };
							std::string statustext = { "+" };
							if (player.inventory[5 + i + h * 5].vit < 0)
							{
								coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
								statustext = { "" };
							}
							SetText("vit     ", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 1.0f, 0.2f, 0.2f, 1.0f, 1);
							SetText(statustext + std::to_string((int)player.inventory[5 + i + h * 5].vit), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (player.inventory[5 + i + h * 5].maxhp != 0)
						{
							float coler[3] = { 0.75f,0.82f,0.2f };
							std::string statustext = { "+" };
							if (player.inventory[5 + i + h * 5].maxhp < 0)
							{
								coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
								statustext = { "" };
							}
							SetText("maxhealth", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 1.0f, 0.0f, 1.0f, 1.0f, 1);
							SetText(statustext + std::to_string((int)player.inventory[5 + i + h * 5].maxhp), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (player.inventory[5 + i + h * 5].armor != 0)
						{
							float coler[3] = { 0.75f,0.82f,0.2f };
							std::string statustext = { "+" };
							if (player.inventory[5 + i + h * 5].armor < 0)
							{
								coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
								statustext = { "" };
							}
							SetText("armor", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 0.3f, 0.3f, 0.3f, 1.0f, 1);
							SetText(statustext + std::to_string((int)player.inventory[5 + i + h * 5].armor), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (player.inventory[5 + i + h * 5].movespeed != 0)
						{
							float coler[3] = { 0.75f,0.82f,0.2f };
							std::string statustext = { "+" };
							if (player.inventory[5 + i + h * 5].movespeed < 0)
							{
								coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
								statustext = { "" };
							}
							SetText("movespeed", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 0.8f, 0.8f, 1.0f, 1.0f, 1);
							SetText(statustext + std::to_string((int)player.inventory[5 + i + h * 5].movespeed) + "%", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (player.inventory[5 + i + h * 5].range != 0)
						{
							float coler[3] = { 0.75f,0.75f,0.75f };
							SetText("range   ", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 1.0f, 1.0f, 0.0f, 1.0f, 1);
							SetText(std::to_string((int)player.inventory[5 + i + h * 5].range), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (player.inventory[5 + i + h * 5].attackspeed != 0)
						{
							float coler[3] = { 0.75f,0.75f,0.75f };
							SetText("atkspeed ", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 0.7f, 0.7f, 0.7f, 1.0f, 1);
							SetText(std::to_string((int)player.inventory[5 + i + h * 5].attackspeed), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						//スキルウィンドウ表示
						if (player.inventory[5 + i + h * 5].skill != 0)
						{
							DrawSpriteColorRotate(gui4,
								1650, 700,
								500, 600,
								0.0f, 0.0f,
								1.0f, 0.5f,
								1.0f, 0.5f, 1.0f, 1.0f,
								PAI * 1.0f);
							//スキルの詳細説明
							SetText(Getskillname(player.inventory[5 + i + h * 5].skill), 1500, 400, 30, 0.70f, 0.0f, 0.70f, 1.0f, 1);
							int textsize = 25;
							std::string skilltext[32] = {};
							switch (player.inventory[5 + i + h * 5].skill)
							{
							case 1:
								skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
								skilltext[2] = "Damage       2";
								skilltext[3] = "Range        600";

								break;
							case 2:
								skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
								skilltext[2] = "Damage       3";
								skilltext[3] = "Range        600";

								break;
							case 3:
								skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
								skilltext[2] = "Damage       3";
								skilltext[3] = "Range        600";

								break;
							case 4:
								skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
								skilltext[2] = "Damage       3 * 6";
								skilltext[3] = "Range        400";

								break;
							case 5:
								skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
								skilltext[2] = "Damage       0.2 * 8";
								skilltext[3] = "Range        none";

								break;
							default:
								break;
							}
							for (int d = 0; d < 32; d++)
							{
								SetText(skilltext[d], 1500, 440 + (textsize + 4) * d, textsize, 1.00f, 1.0f, 1.00f, 1.0f, 1);
							}


						}


						if (downinvent == 1)
						{
							h = 3;
						}
					}
				}


			}
			if (shopcelectna() > 0)
			{
				DrawSpriteColorRotate(gui,
					1650, 300,
					120.0f, 120.0f,
					0.2f, 0.2f,
					0.6f, 0.6f,
					0.3f, 0.4f, 0.8f, 1.0f,
					0);

				DrawSpriteColorRotate(gui3,
					1650, 300,
					150.0f, 150.0f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					0.3f, 0.3f, 0.3f, 1.0f,
					0);
				
				DrawSpriteColorRotate(itemnom[PresetItem(shopcelectna() ).itemtex - 1],
					1650 + 60 -PresetItem(shopcelectna()).size * 0.6f * 1.25f, 300 + 60 - PresetItem(shopcelectna()).size * 0.6f * 1.25f,
					PresetItem(shopcelectna()).size * 1.2f* 1.25f, PresetItem(shopcelectna()).size * 1.2f * 1.25f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0);
				float zx = 1.0f;
				if (corsor.x > 1650 - 150 && corsor.x < 1650 + 150 &&
					corsor.y >  800 - 50 && corsor.y < 800 + 50)
				{
					zx = 0.3f;
				}
				DrawSpriteColorRotate(uitex[1],
					1650, 800,
					300.0f, 300.0f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					1.5f * zx, 1.5f * zx, 1.5f * zx, 1.0f,
					0);
				DrawSpriteColorRotate(uitex[1],
					1675, 700,
					400.0f, 300.0f,
					0.2f, 0.2f,
					0.6f, 0.6f,
					0.5f, 0.5f, 0.5f, 1.0f,
					0);
				SetText("Sold  " + std::to_string(itemselltable(shopcelectna())) + "  gold", 1530, 650, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
				SetText("Sell", 1630, 750, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);

			}
		}
		if (shopmode == 1)
		{

			DrawSpriteColorRotate(uitex[2], 900, 535.0f, 1200.0f, 1200.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);
			DrawSpriteColorRotate(uitex[1],
				1150, 870,
				200.0f, 200.0f,
				0.1f, 0.1f,
				0.8f, 0.8f,
				0.11f * 2, 0.33f * 2, 1.0f * 2, 1.0f,
				0);
			SetText("page :" + std::to_string(shopbuypage + 1), 1070, 810, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
			float hidari = 1.0f;
			float migi = 1.0f;
			if (corsor.x > 1284 - 30 && corsor.x < 1284 + 30 &&
				corsor.y >  870 - 40 && corsor.y < 870 + 40)
			{
				hidari = 0.3f;

			}
			if (corsor.x > 1348 - 30 && corsor.x < 1348 + 30 &&
				corsor.y >  870 - 40 && corsor.y < 870 + 40)
			{
				migi = 0.3f;

			}
			DrawSpriteColorRotate(uitex[1],
				1284, 870,
				60.0f, 200.0f,
				0.0f, 0.0f,
				1.0f, 1.0f,
				0.11f * 12 * hidari, 0.33f * 12 * hidari, 1.0f * 12 * hidari, 1.0f,
				0);
			DrawSpriteColorRotate(uitex[1],
				1348, 870,
				60.0f, 200.0f,
				0.0f, 0.0f,
				1.0f, 1.0f,
				0.11f * 12 * migi, 0.33f * 12 * migi, 1.0f * 12 * migi, 1.0f,
				0);
			int osjkd = 1.0f;
			if (corsor.x > 1630 - 150 && corsor.x < 1630 + 150 &&
				corsor.y >  850 - 60 && corsor.y < 850 + 60)
			{

				osjkd = 0.3f;
			}
			DrawSpriteColorRotate(uitex[1],
				1630, 850,
				300.0f, 300.0f,
				0.1f, 0.1f,
				0.8f, 0.8f,
				0.11f * 5 * osjkd, 0.33f * 5 * osjkd, 1.0f * 5 * osjkd, 1.0f,
				0);
			SetText("buy", 1610, 800, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
			DrawSpriteColorRotate(uitex[1],
				1630, 350,
				400.0f, 650.0f,
				0.3f, 0.2f,
				0.4f, 0.4f,
				0.11f * 5, 0.33f * 5, 1.0f * 5, 1.0f,
				0);
			if (shopbuyclect > -1)
			{
				DrawSpriteColorRotate(itemnom[shopitem(shopbuyclect + 4 * shopbuypage).itemtex - 1],
					1630 + 60 - shopitem(shopbuyclect + 4 * shopbuypage).size * 1.25f * 0.6f, 450 + 60 - shopitem(shopbuyclect + 4 * shopbuypage).size * 1.25f * 0.6f,
					shopitem(shopbuyclect + 4 * shopbuypage).size * 1.25f* 1.2f, shopitem(shopbuyclect + 4 * shopbuypage).size * 1.25f * 1.2f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0);
				SetText(shopitem(shopbuyclect + 4 * shopbuypage).name, 1500, 550, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
			}

			SetText("<  >", 1285, 810, 30, 0.0f, 0.0f, 0.0f, 1.0f, 1);
			for (int r = 0; r < 4; r++)
			{
				float corcoler = 1.0f;
				if (corsor.x > 900 - 440 && corsor.x < 900 + 440 &&
					corsor.y >   390 + r * 120 - 58 && corsor.y < 390 + r * 120 + 58)
				{

					corcoler = 0.3f;
				}
				DrawSpriteColorRotate(uitex[1],
					900, 390 + r * 120,
					880.0f, 450.0f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					corcoler, corcoler, corcoler, 1.0f,
					0);
				if (shopitem(r + 4 * shopbuypage).itemno > 0)
				{
					DrawSpriteColorRotate(gui,
						560, 390 + r * 120,
						80, 80.0f,
						0.2f, 0.2f,
						0.6f, 0.6f,
						0.8f, 1.4f, 2.0f, 1.0f,
						0);
					DrawSpriteColorRotate(gui3,
						560, 390 + r * 120,
						100.0f, 100.0f,
						0.0f, 0.0f,
						1.0f, 1.0f,
						0.3f, 0.3f, 0.3f, 1.0f,
						0);
					DrawSpriteColorRotate(itemnom[shopitem(r + 4 * shopbuypage).itemtex - 1],
						560 + 40 - shopitem(r + 4 * shopbuypage).size * 0.5f, 390 + r * 120 + 40 - shopitem(r + 4 * shopbuypage).size * 0.5f,
						shopitem(r + 4 * shopbuypage).size, shopitem(r + 4 * shopbuypage).size,
						0.0f, 0.0f,
						1.0f, 1.0f,
						1.0f, 1.0f, 1.0f, 1.0f,
						0);
					SetText(shopitem(r + 4 * shopbuypage).name, 650, 340 + r * 120, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1); 
					int buyswa = 0;
					for (int w = 0; w < 10; w++)
					{
						int swa = 10;
						int ws = 0;
						while (w > ws )
						{
							swa *= 10;
							ws++;
						}
						if (itembuytable(shopitem(r + 4 * shopbuypage).itemno) < swa)
						{
							buyswa = w;
							break;
						}
						
					}
				
					SetText(std::to_string(itembuytable(shopitem(r + 4 * shopbuypage).itemno)) + " GOLD", 1150 - (buyswa) * 20.0f, 340 + r * 120, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);


				}
				for (int r = 0; r < 4; r++)
				{
				
					if (corsor.x > 900 - 440 && corsor.x < 900 + 440 &&
						corsor.y >   390 + r * 120 - 58 && corsor.y < 390 + r * 120 + 58&&
						shopitem(r + 4 * shopbuypage).itemno > 0)
					{
						int a = 1;
						for (int d = 0; d < 4; d++)
						{
							if (shopitem(r + 4 * shopbuypage).showtext[d] != "")
							{
								a++;

							}
						}
						if (shopitem(r + 4 * shopbuypage).damage != 0)
						{
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).skill != 0)
						{
							a += 2;
						}
						if (shopitem(r + 4 * shopbuypage).str != 0)
						{
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).dex != 0)
						{
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).vit != 0)
						{
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).maxhp != 0)
						{
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).armor != 0)
						{
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).movespeed != 0)
						{
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).attackspeed != 0)
						{
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).range != 0)
						{
							a++;
						}
						int textsize = 13;

						if (textsize < (int)shopitem(r + 4 * shopbuypage).name.length())
						{
							textsize = (int)shopitem(r + 4 * shopbuypage).name.length();


						}
						for (int d = 0; d < 4; d++)
						{

							if (textsize < (int)shopitem(r + 4 * shopbuypage).showtext[d].length())
							{

								textsize = (int)shopitem(r + 4 * shopbuypage).showtext[d].length();
							}
						}
						if (textsize < (int)Getskillname(shopitem(r + 4 * shopbuypage).skill).length() + 6)
						{
							//+6は"skill "の分
							textsize = (int)Getskillname(shopitem(r + 4 * shopbuypage).skill).length() + 6;
						}




						int overa = 0;
						if (a > 7)
						{
							overa = a - 7;
						}
						DrawSpriteColorRotate(gui4,
							550 + textsize * 12.5f, 310 + r * 140 + a * 15 + 20 - overa * 30,
							75.0f + textsize * 25, 15.0f + 30 + a * 30.0f,
							0.0f, 0.0f,
							1.0f, 0.5f,
							1.0f, 0.5f, 1.0f, 1.0f,
							PAI * 1.0f);
						DrawSpriteColorRotate(gui4,
							550 + textsize * 12.5f, 310 + r * 140 - overa * 30,
							75.0f + textsize * 25, 15.0f,
							0.0f, 0.0f,
							1.0f, 1.0f,
							1.0f, 1.0f, 1.0f, 1.0f,
							0);
						DrawSpriteColorRotate(gui4,
							550 + textsize * 12.5f, 310 + r * 140 + a * 30 + 40 - overa * 30,
							75.0f + textsize * 25, 15.0f,
							0.0f, 0.0f,
							1.0f, 1.0f,
							1.0f, 1.0f, 1.0f, 1.0f,
							PAI * 1.0f);
						a  = 0;
						SetText(shopitem(r + 4 * shopbuypage).name, 550 + textsize * 3, 300 + 140.0f * r + 30 * a - overa * 30, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
						a++;
						if (shopitem(r + 4 * shopbuypage).skill != 0)
						{
							float coler[3] = { 0.70f,0.7f,0.70f };
							SetText("Skill " + Getskillname(shopitem(r + 4 * shopbuypage).skill), 550 + textsize * 3, 300 + 140.0f * r + 30 * a - overa * 30, 27, coler[0], coler[1], coler[2], 1.0f, 1);

							a += 2;
						}
						for (int d = 0; d < 4; d++)
						{
							if (shopitem(r + 4 * shopbuypage).showtext[d] != "")
							{
								SetText(shopitem(r + 4 * shopbuypage).showtext[d], 550 + textsize * 3, 300 + 140.0f * r + 30 * a - overa * 30, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
								a++;

							}
						}

						if (shopitem(r + 4 * shopbuypage).damage != 0)
						{
							float coler[3] = { 0.75f,0.75f,0.75f };
							SetText("damage  ", 550 + textsize * 3, 300 + 140.0f * r + 30 * a - overa * 30, 25, 0.2f, 0.8f, 0.2f, 1.0f, 1);
							SetText(std::to_string((int)shopitem(r + 4 * shopbuypage).damage) + "." + std::to_string((int)(shopitem(r + 4 * shopbuypage).damage * 10) % 10), 550 + textsize * 3 + 200, 300 + 140.0f * r + 30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}

						if (shopitem(r + 4 * shopbuypage).str != 0)
						{
							float coler[3] = { 0.75f,0.82f,0.2f };
							std::string statustext = { "+" };
							if (shopitem(r + 4 * shopbuypage).str < 0)
							{
								coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
								statustext = { "" };
							}
							SetText("str     ", 550 + textsize * 3, 300 + 140.0f * r + 30 * a - overa * 30, 25, 1.0f, 0.2f, 0.2f, 1.0f, 1);
							SetText(statustext + std::to_string((int)shopitem(r + 4 * shopbuypage).str), 550 + textsize * 3 + 200, 300 + 140.0f * r + 30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).dex != 0)
						{
							float coler[3] = { 0.75f,0.82f,0.2f };
							std::string statustext = { "+" };
							if (shopitem(r + 4 * shopbuypage).dex < 0)
							{
								coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
								statustext = { "" };
							}
							SetText("dex     ", 550 + textsize * 3, 300 + 140.0f * r + 30 * a - overa * 30, 25, 1.0f, 0.2f, 0.2f, 1.0f, 1);
							SetText(statustext + std::to_string((int)shopitem(r + 4 * shopbuypage).dex), 550 + textsize * 3 + 200, 300 + r * 140.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).vit != 0)
						{
							float coler[3] = { 0.75f,0.82f,0.2f };
							std::string statustext = { "+" };
							if (shopitem(r + 4 * shopbuypage).vit < 0)
							{
								coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
								statustext = { "" };
							}
							SetText("vit     ", 550 + textsize * 3, 300 + 140.0f * r + 30 * a - overa * 30, 25, 1.0f, 0.2f, 0.2f, 1.0f, 1);
							SetText(statustext + std::to_string((int)shopitem(r + 4 * shopbuypage).vit), 550 + textsize * 3 + 200, 300 + r * 140.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).maxhp != 0)
						{
							float coler[3] = { 0.75f,0.82f,0.2f };
							std::string statustext = { "+" };
							if (shopitem(r + 4 * shopbuypage).maxhp < 0)
							{
								coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
								statustext = { "" };
							}
							SetText("maxhealth", 550 + textsize * 3, 300 + 140.0f * r + 30 * a - overa * 30, 25, 1.0f, 0.0f, 1.0f, 1.0f, 1);
							SetText(statustext + std::to_string((int)shopitem(r + 4 * shopbuypage).maxhp), 550 + textsize * 3 + 200, 300 + r * 140.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).armor != 0)
						{
							float coler[3] = { 0.75f,0.82f,0.2f };
							std::string statustext = { "+" };
							if (shopitem(r + 4 * shopbuypage).armor < 0)
							{
								coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
								statustext = { "" };
							}
							SetText("armor", 550 + textsize * 3, 300 + 140.0f * r + 30 * a - overa * 30, 25, 0.3f, 0.3f, 0.3f, 1.0f, 1);
							SetText(statustext + std::to_string((int)shopitem(r + 4 * shopbuypage).armor), 550 + textsize * 3 + 200, 300 + r * 140.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).movespeed != 0)
						{
							float coler[3] = { 0.75f,0.82f,0.2f };
							std::string statustext = { "+" };
							if (shopitem(r + 4 * shopbuypage).movespeed < 0)
							{
								coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
								statustext = { "" };
							}
							SetText("movespeed", 550 + textsize * 3, 300 + 140.0f * r + 30 * a - overa * 30, 25, 0.8f, 0.8f, 1.0f, 1.0f, 1);
							SetText(statustext + std::to_string((int)shopitem(r + 4 * shopbuypage).movespeed) + "%", 550 + textsize * 3 + 200, 300 + r * 140.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).range != 0)
						{
							float coler[3] = { 0.75f,0.75f,0.75f };
							SetText("range   ", 550 + textsize * 3, 300 + 140.0f * r + 30 * a - overa * 30, 25, 1.0f, 1.0f, 0.0f, 1.0f, 1);
							SetText(std::to_string((int)shopitem(r + 4 * shopbuypage).range), 550 + textsize * 3 + 200, 300 + r * 140.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						if (shopitem(r + 4 * shopbuypage).attackspeed != 0)
						{
							float coler[3] = { 0.75f,0.75f,0.75f };
							SetText("atkspeed ", 550 + textsize * 3, 300 + 140.0f * r + 30 * a - overa * 30, 25, 0.7f, 0.7f, 0.7f, 1.0f, 1);
							SetText(std::to_string((int)shopitem(r + 4 * shopbuypage).attackspeed), 550 + textsize * 3 + 200,300 + r * 140.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
							a++;
						}
						//スキルウィンドウ表示
						if (shopitem(r + 4 * shopbuypage).skill != 0)
						{
							DrawSpriteColorRotate(gui4,
								1650, 700,
								500, 600,
								0.0f, 0.0f,
								1.0f, 0.5f,
								1.0f, 0.5f, 1.0f, 1.0f,
								PAI * 1.0f);
							//スキルの詳細説明
							SetText(Getskillname(shopitem(r + 4 * shopbuypage).skill), 1500, 400, 30, 0.70f, 0.0f, 0.70f, 1.0f, 1);
							int textsize = 25;
							std::string skilltext[32] = {};
							switch (shopitem(r + 4 * shopbuypage).skill)
							{
							case 1:
								skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(shopitem(r + 4 * shopbuypage).skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(shopitem(r + 4 * shopbuypage).skill) * 10 / 60.0f) % 10) + "s";
								skilltext[2] = "Damage       2";
								skilltext[3] = "Range        600";

								break;
							default:
								break;
							}
							for (int d = 0; d < 32; d++)
							{
								SetText(skilltext[d], 1500, 440 + (textsize + 4) * d, textsize, 1.00f, 1.0f, 1.00f, 1.0f, 1);
							}


						}
					}
				}
			}

			
		}





		DrawSpriteColorRotate(uitex[1],
			230, 150,
			300.0f, 300.0f,
			0.1f, 0.1f,
			0.8f, 0.8f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0);
		SetText("Gold :" + std::to_string(getgold()), 130, 100, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);

		float osjkd = 1.0f;
		if (corsor.x > 730 - 150 && corsor.x < 730 + 150 &&
			corsor.y >  150 - 60 && corsor.y < 150 + 60)
		{

			osjkd = 0.3f;
		}
		DrawSpriteColorRotate(uitex[1],
			730, 150,
			300.0f, 300.0f,
			0.1f, 0.1f,
			0.8f, 0.8f,
			0.11f * 5 * osjkd, 0.33f * 5 * osjkd, 1.0f * 5 * osjkd, 1.0f,
			0);
		SetText("buy", 710, 100, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
		osjkd = 1.0f;
		if (corsor.x > 1030 - 150 && corsor.x < 1030 + 150 &&
			corsor.y >  150 - 60 && corsor.y < 150 + 60)
		{

			osjkd = 0.3f;
		}
		DrawSpriteColorRotate(uitex[1],
			1030, 150,
			300.0f, 300.0f,
			0.1f, 0.1f,
			0.8f, 0.8f,
			0.11f * 8 * osjkd, 0.33f * 8 * osjkd, 1.0f * 8 * osjkd, 1.0f,
			0);
		SetText("sell", 1000, 100, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
		SetText("F   close", 450, 800, 40, 1.0f, 1.0f, 1.0f, 1.0f, 1);
	}
	//インベントリ表示
	if (inventopen == true)
	{
		//インベントリを開いたとき薄暗くする
		DrawSpriteColorRotate(g_bg, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 0.1f, 0.1f, 1.0f, 1.0f, 0.8f, 0.5f, 0);
		//インベントリスロット表示
		DrawSpriteColorRotate(gui2, SCREEN_WIDTH * 0.5f, 450.0f, 800.0f, 500.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);
		DrawSpriteColorRotate(gui2, SCREEN_WIDTH * 0.5f, 810.0f, 800.0f, 200.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);
		//アビリティの画像
		DrawSpriteColorRotate(gui5, 1700, 220, 450, 200, 0.0f, 0.0f, 1.0f, 1.0f, 0.8f, 0.8f, 0.8f, 1.0f, 0);
		SetText("Strength", 1550, 100, 35, 1.0f, 0.5f, 0.0f, 1.0f, 1);
		SetText(std::to_string((int)player.str), 1850, 100, 35, 1.0f, 0.5f, 0.0f, 1.0f, 1);
		SetText("Dexterity", 1550, 145, 35, 1.0f, 1.0f, 0.0f, 1.0f, 1);
		SetText(std::to_string((int)player.dex), 1850, 145, 35, 1.0f, 1.0f, 0.0f, 1.0f, 1);
		SetText("Vitality", 1550, 190, 35, 1.0f, 0.0f, 0.1f, 1.0f, 1);
		SetText(std::to_string((int)player.vit), 1850, 190, 35, 1.0f, 0.0f, 0.1f, 1.0f, 1);
		//ステータスの画像
		DrawSpriteColorRotate(gui5, 275, SCREEN_HEIGHT * 0.5f, 550, 800, 0.0f, 0.0f, 1.0f, 1.0f, 0.9f, 0.9f, 0.9f, 1.0f, 0);
		SetText("Level", 100, 190, 35, 0.0f, 0.0f, 0.0f, 1.0f, 1);
		SetText(std::to_string((int)player.lv), 250, 190, 35, 0.0f, 0.0f, 0.0f, 1.0f, 1);
		SetText("-----------", 100, 230, 45, 0.0f, 0.0f, 0.0f, 1.0f, 1);
		SetText("HP  " + std::to_string((int)player.nowhp) + "/" + std::to_string((int)player.maxhp), 100, 280, 45, 0.0f, 0.0f, 0.0f, 1.0f, 1);
		SetText("DEF      " + std::to_string((int)player.def), 100, 350, 45, 0.0f, 0.0f, 0.0f, 1.0f, 1);
		SetText("CRT Rate " + std::to_string((int)player.critcalrete) + "%", 100, 420, 45, 0.0f, 0.0f, 0.0f, 1.0f, 1);
		SetText("CRT Dmg  " + std::to_string((int)player.critcaldamage) + "%", 100, 490, 45, 0.0f, 0.0f, 0.0f, 1.0f, 1);
		SetText("MOV Spd  " + std::to_string((int)player.movespeed), 100, 560, 45, 0.0f, 0.0f, 0.0f, 1.0f, 1);
		SetText("ATK Spd  " + std::to_string((int)(player.inventory[haveitem()].attackspeed * (player.dex * 0.01f + 1.0f))), 100, 630, 45, 0.0f, 0.0f, 0.0f, 1.0f, 1);
	//bgm調整
		SetText("BGM   "+ std::to_string(bgmsoundvolume), 100, 900, 35, 1.0f,1.0f, 1.0f, 1.0f, 1);
		DrawSpriteColorRotate(portalui[1],
			350, 970,
			50.0f, 80.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f,1.0f,1.0f, 1.0f,
			PAI * 0.5f);
		DrawSpriteColorRotate(portalui[1],
			450, 970,
			50.0f, 80.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			PAI * 1.5f);
		SetText("SE    " + std::to_string(sesoundvolume), 100, 950, 35, 1.0f, 1.0f, 1.0f, 1.0f, 1);
		DrawSpriteColorRotate(portalui[1],
			350, 1020,
			50.0f, 80.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			PAI * 0.5f);
		DrawSpriteColorRotate(portalui[1],
			450, 1020,
			50.0f, 80.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			PAI * 1.5f);
		for (int i = 0; i < 5; i++)
		{
			for (int h = 0; h < 3; h++)
			{
				//=================================================
				//上のgui
				// //=================================================
				//頭アイコン
				if (i == 3 && h == 0)
				{
					DrawSpriteColorRotate(guihead,
						SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 310.0f + 140.0f * h,
						150.0f, 150.0f,
						0.0f, 0.0f,
						1.0f, 1.0f,
						1.0f, 1.0f, 1.0f, 1.0f,
						0);
				}
				//リングアイコン
				else if (i == 4 && h == 0)
				{
					DrawSpriteColorRotate(guiring,
						SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 310.0f + 140.0f * h,
						150.0f, 150.0f,
						0.0f, 0.0f,
						1.0f, 1.0f,
						1.0f, 1.0f, 1.0f, 1.0f,
						0);
				}
				//通常アイコン
				else {
					DrawSpriteColorRotate(gui,
						SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 310.0f + 140.0f * h,
						150.0f, 150.0f,
						0.0f, 0.0f,
						1.0f, 1.0f,
						1.0f, 1.0f, 1.0f, 1.0f,
						0);
				}


				//インベントリのアイテム表示
				if (player.inventory[5 * h + i + 5].itemno > 0)
				{

					DrawSpriteColorRotate(itemnom[player.inventory[5 * h + i + 5].itemtex - 1],
						SCREEN_WIDTH * 0.5f - 220.0f + i * 140 - player.inventory[5 * h + i + 5].size * 1.25f * 0.6f, 370.0f + 140.0f * h - player.inventory[5 * h + i + 5].size * 1.25f * 0.6f,
						player.inventory[5 * h + i + 5].size* 1.25f*1.2f , player.inventory[5 * h + i + 5].size * 1.25f * 1.2f,

						0.0f, 0.0f,
						1.0f, 1.0f,
						1.0f, 1.0f, 1.0f, 1.0f,
						0);
					if (player.inventory[5 * h + i + 5].count > 1)
					{
						text = std::to_string((int)player.inventory[5 * h + i + 5].count);
						SetText(text, SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 35, 310.0f + 140.0f * h - 20, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
					}
					//スキルクールタイム中なら表示される
					if (player.inventory[5 * h + i + 5].skill > 0 && player.inventory[5 * h + i + 5].skillct > 0)
					{
						DrawSpriteColorRotate(whitetex,
							SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 310.0f + 140.0f * h + 65.0f - 65.0f * (player.inventory[5 * h + i + 5].skillct / (float)Getskillct(player.inventory[5 * h + i + 5].skill)),
							125.0f, 125.0f * (player.inventory[5 * h + i + 5].skillct / (float)Getskillct(player.inventory[5 * h + i + 5].skill)),
							0.1f, 0.1f,
							0.1f, 0.1f,
							1.0f, 1.0f, 1.0f, 1.0f,
							0);
					}

				}
				//インベントリにカーソルが重なると少し色がつく + アイテムがあった場合表示
				if (corsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && corsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&
					corsor.y >  310.0f + 140.0f * h - 60 && corsor.y < 310.0f + 140.0f * h + 60)
				{
					DrawSpriteColorRotate(g_bg,
						SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 310.0f + 140.0f * h,
						125.0f, 125.0f,
						0.0f, 0.0f,
						0.1f, 0.1f,
						2.0f, 2.0f, 0.7f, 0.5f,
						0);

				}


			}
			//=================================================
			//下側を表示
			//=================================================
			DrawSpriteColorRotate(gui,
				SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 810.0f,
				150.0f, 150.0f,
				0.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0);
			if (player.inventory[i].itemno > 0)
			{
				DrawSpriteColorRotate(itemnom[player.inventory[i].itemtex - 1],
					SCREEN_WIDTH * 0.5f - 220.0f + i * 140 - player.inventory[i].size * 1.25f * 0.6f, 870.0f - player.inventory[i].size * 1.25f * 0.6f,
					player.inventory[i].size * 1.25f * 1.2f, player.inventory[i].size * 1.25f * 1.2f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0);
				if (player.inventory[i].count > 1)
				{
					text = std::to_string((int)player.inventory[i].count);
					SetText(text, SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 35, 810.0f - 20, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
				}
				//スキルクールタイム中ならひょうじ
				if (player.inventory[i].skill > 0 && player.inventory[i].skillct > 0)
				{
					DrawSpriteColorRotate(whitetex,
						SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 810.0f + 65.0f - 65.0f * (player.inventory[i].skillct / (float)Getskillct(player.inventory[i].skill)),
						130.0f, 130.0f * (player.inventory[i].skillct / (float)Getskillct(player.inventory[i].skill)),
						0.1f, 0.1f,
						0.1f, 0.1f,
						1.0f, 1.0f, 1.0f, 1.0f,
						0);
				}
			}
			//インベントリにカーソルが重なると少し色がつく
			if (corsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && corsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&
				corsor.y >  810.0f - 60 && corsor.y < 810.0f + 60)
			{
				DrawSpriteColorRotate(g_bg,
					SCREEN_WIDTH * 0.5f - 280.0f + i * 140, 810.0f,
					125.0f, 125.0f,
					0.0f, 0.0f,
					0.1f, 0.1f,
					2.0f, 2.0f, 0.7f, 0.5f,
					0);
			}
		}

		//アイテムを持っているとそこのアイコンに四角がつく
		if (hubna() > -1 && hubna() < 5)
		{
			DrawSpriteColorRotate(gui3,
				SCREEN_WIDTH * 0.5f - 280.0f + hubna() * 140, 810.0f,
				150.0f, 150.0f,
				0.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0);
		}
		if (hubna() > 4)
		{
			DrawSpriteColorRotate(gui3,
				SCREEN_WIDTH * 0.5f - 280.0f + hubna() % 5 * 140, 180.0f + 140.0f * (int)(hubna() / 5),
				150.0f, 150.0f,
				0.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0);
		}
		//=================================================
		//カーソルを合わせた時にテキスト表示
		//=================================================
		for (int i = 0; i < 5; i++)
		{
			for (int h = 0; h < 4; h++)
			{
				if (((corsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && corsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&
					corsor.y >  310.0f + 140.0f * h - 60 && corsor.y < 310.0f + 140.0f * h + 60 && player.inventory[5 + i + h * 5].itemno > 0 && h < 3) //インベントリ上の条件
					|| (corsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && corsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&//インベントリ下側の条件
						corsor.y >  810.0f - 60 && corsor.y < 810.0f + 60 && player.inventory[i].itemno > 0 && h == 3)))
				{
					int downinvent = 0;//下側のインベントリだった場合記録する
					if (corsor.x > SCREEN_WIDTH * 0.5f - 280.0f + i * 140 - 60 && corsor.x < SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + 60 &&//インベントリ下側の条件
						corsor.y >  810.0f - 60 && corsor.y < 810.0f + 60 && player.inventory[i].itemno > 0 && h == 3) {
						h = -1;
						downinvent = 1;
					}
					int a = 1;
					for (int d = 0; d < 4; d++)
					{
						if (player.inventory[5 + i + h * 5].showtext[d] != "")
						{
							a++;

						}
					}
					if (player.inventory[5 + i + h * 5].damage != 0)
					{
						a++;
					}
					if (player.inventory[5 + i + h * 5].skill != 0)
					{
						a += 2;
					}
					if (player.inventory[5 + i + h * 5].str != 0)
					{
						a++;
					}
					if (player.inventory[5 + i + h * 5].dex != 0)
					{
						a++;
					}
					if (player.inventory[5 + i + h * 5].vit != 0)
					{
						a++;
					}
					if (player.inventory[5 + i + h * 5].maxhp != 0)
					{
						a++;
					}
					if (player.inventory[5 + i + h * 5].armor != 0)
					{
						a++;
					}
					if (player.inventory[5 + i + h * 5].movespeed != 0)
					{
						a++;
					}
					if (player.inventory[5 + i + h * 5].attackspeed != 0)
					{
						a++;
					}
					if (player.inventory[5 + i + h * 5].range != 0)
					{
						a++;
					}
					int textsize = 13;
					char* lentext = new char[player.inventory[5 + i + h * 5].name.size() + 1];
					std::char_traits<char>::copy(lentext, player.inventory[5 + i + h * 5].name.c_str(), player.inventory[5 + i + h * 5].name.size() + 1);
					int f = (int)strlen(lentext);
					if (textsize < (int)strlen(lentext))
					{
						textsize = (int)strlen(lentext);


					}
					for (int d = 0; d < 4; d++)
					{
						char* lentext = new char[player.inventory[5 + i + h * 5].showtext[d].size() + 1];
						std::char_traits<char>::copy(lentext, player.inventory[5 + i + h * 5].showtext[d].c_str(), player.inventory[5 + i + h * 5].showtext[d].size() + 1);
						if (textsize < (int)strlen(lentext))
						{
							textsize = (int)strlen(lentext);
						}
					}
					if (textsize < (int)Getskillname(player.inventory[5 + i + h * 5].skill).length() + 6)
					{
						//+6は"skill "の分
						textsize = (int)Getskillname(player.inventory[5 + i + h * 5].skill).length() + 6;
					}
					DrawSpriteColorRotate(gui4,
						SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 12.5f, 310.0f + 140.0f * h + downinvent * 650 + a * 15 + 20,
						75.0f + textsize * 25, 15.0f + 30 + a * 30.0f,
						0.0f, 0.0f,
						1.0f, 0.5f,
						1.0f, 0.5f, 1.0f, 1.0f,
						PAI * 1.0f);
					DrawSpriteColorRotate(gui4,
						SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 12.5f, 310.0f + 140.0f * h + downinvent * 650,
						75.0f + textsize * 25, 15.0f,
						0.0f, 0.0f,
						1.0f, 1.0f,
						1.0f, 1.0f, 1.0f, 1.0f,
						0);
					DrawSpriteColorRotate(gui4,
						SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 12.5f, 310.0f + 140.0f * h + downinvent * 650 + a * 30 + 40,
						75.0f + textsize * 25, 15.0f,
						0.0f, 0.0f,
						1.0f, 1.0f,
						1.0f, 1.0f, 1.0f, 1.0f,
						PAI * 1.0f);
					a = 0;
					SetText(player.inventory[5 + i + h * 5].name, SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
					a++;
					if (player.inventory[5 + i + h * 5].skill != 0)
					{
						float coler[3] = { 0.70f,0.7f,0.70f };
						SetText("Skill " + Getskillname(player.inventory[5 + i + h * 5].skill), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 27, coler[0], coler[1], coler[2], 1.0f, 1);

						a += 2;
					}
					for (int d = 0; d < 4; d++)
					{
						if (player.inventory[5 + i + h * 5].showtext[d] != "")
						{
							SetText(player.inventory[5 + i + h * 5].showtext[d], SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
							a++;

						}
					}

					if (player.inventory[5 + i + h * 5].damage != 0)
					{
						float coler[3] = { 0.75f,0.75f,0.75f };
						SetText("damage  ", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 0.2f, 0.8f, 0.2f, 1.0f, 1);
						SetText(std::to_string((int)player.inventory[5 + i + h * 5].damage) + "." + std::to_string((int)(player.inventory[5 + i + h * 5].damage * 10) % 10), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}

					if (player.inventory[5 + i + h * 5].str != 0)
					{
						float coler[3] = { 0.75f,0.82f,0.2f };
						std::string statustext = { "+" };
						if (player.inventory[5 + i + h * 5].str < 0)
						{
							coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
							statustext = { "" };
						}
						SetText("str     ", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 1.0f, 0.2f, 0.2f, 1.0f, 1);
						SetText(statustext + std::to_string((int)player.inventory[5 + i + h * 5].str), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (player.inventory[5 + i + h * 5].dex != 0)
					{
						float coler[3] = { 0.75f,0.82f,0.2f };
						std::string statustext = { "+" };
						if (player.inventory[5 + i + h * 5].dex < 0)
						{
							coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
							statustext = { "" };
						}
						SetText("dex     ", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 1.0f, 0.2f, 0.2f, 1.0f, 1);
						SetText(statustext + std::to_string((int)player.inventory[5 + i + h * 5].dex), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (player.inventory[5 + i + h * 5].vit != 0)
					{
						float coler[3] = { 0.75f,0.82f,0.2f };
						std::string statustext = { "+" };
						if (player.inventory[5 + i + h * 5].vit < 0)
						{
							coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
							statustext = { "" };
						}
						SetText("vit     ", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 1.0f, 0.2f, 0.2f, 1.0f, 1);
						SetText(statustext + std::to_string((int)player.inventory[5 + i + h * 5].vit), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (player.inventory[5 + i + h * 5].maxhp != 0)
					{
						float coler[3] = { 0.75f,0.82f,0.2f };
						std::string statustext = { "+" };
						if (player.inventory[5 + i + h * 5].maxhp < 0)
						{
							coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
							statustext = { "" };
						}
						SetText("maxhealth", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 1.0f, 0.0f, 1.0f, 1.0f, 1);
						SetText(statustext + std::to_string((int)player.inventory[5 + i + h * 5].maxhp), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (player.inventory[5 + i + h * 5].armor != 0)
					{
						float coler[3] = { 0.75f,0.82f,0.2f };
						std::string statustext = { "+" };
						if (player.inventory[5 + i + h * 5].armor < 0)
						{
							coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
							statustext = { "" };
						}
						SetText("armor", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 0.3f, 0.3f, 0.3f, 1.0f, 1);
						SetText(statustext + std::to_string((int)player.inventory[5 + i + h * 5].armor), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (player.inventory[5 + i + h * 5].movespeed != 0)
					{
						float coler[3] = { 0.75f,0.82f,0.2f };
						std::string statustext = { "+" };
						if (player.inventory[5 + i + h * 5].movespeed < 0)
						{
							coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
							statustext = { "" };
						}
						SetText("movespeed", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 0.8f, 0.8f, 1.0f, 1.0f, 1);
						SetText(statustext + std::to_string((int)player.inventory[5 + i + h * 5].movespeed) + "%", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (player.inventory[5 + i + h * 5].range != 0)
					{
						float coler[3] = { 0.75f,0.75f,0.75f };
						SetText("range   ", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 1.0f, 1.0f, 0.0f, 1.0f, 1);
						SetText(std::to_string((int)player.inventory[5 + i + h * 5].range), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (player.inventory[5 + i + h * 5].attackspeed != 0)
					{
						float coler[3] = { 0.75f,0.75f,0.75f };
						SetText("atkspeed ", SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, 0.7f, 0.7f, 0.7f, 1.0f, 1);
						SetText(std::to_string((int)player.inventory[5 + i + h * 5].attackspeed), SCREEN_WIDTH * 0.5f - 280.0f + i * 140 + textsize * 3 + 200, 290 + 140.0f * h + downinvent * 650 + 30 * a, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					//スキルウィンドウ表示
					if (player.inventory[5 + i + h * 5].skill != 0)
					{
						DrawSpriteColorRotate(gui4,
							1650, 700,
							500, 600,
							0.0f, 0.0f,
							1.0f, 0.5f,
							1.0f, 0.5f, 1.0f, 1.0f,
							PAI * 1.0f);
						//スキルの詳細説明
						SetText(Getskillname(player.inventory[5 + i + h * 5].skill), 1500, 400, 30, 0.70f, 0.0f, 0.70f, 1.0f, 1);
						int textsize = 25;
						std::string skilltext[32] = {};
						switch (player.inventory[5 + i + h * 5].skill)
						{
						case 1:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "Damage       2";
							skilltext[3] = "Range        600";

							break;
						case 2:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "Damage       3";
							skilltext[3] = "Range        600";

							break;
						case 3:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "Damage       3";
							skilltext[3] = "Range        600";

							break;
						case 4:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "Damage       3 * 6";
							skilltext[3] = "Range        400";
							skilltext[4] = "Fires 6 bullets in";
							skilltext[5] = "a fan shape";

							break;
						case 5:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "Damage       0.2 * 8";
							skilltext[3] = "Produces spines that ";
							skilltext[4] = "cause continuous ";
							skilltext[5] = "damage for 2s";
							break;
						case 6:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "Damage       2";
							skilltext[3] = "Range        600";
							skilltext[4] = "Gives 30% sloww ";
							skilltext[5] = "for 1s tothe enemy";
							skilltext[6] = "hit.";
							break;
						case 7:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "30% increase in ";
							skilltext[3] = "movespeed for 15s";
							break;
						case 8:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "30% increase in ";
							skilltext[3] = "maxhp for 60s";
							break;
						case 9:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "Sloww reduced by";
							skilltext[3] = " 50% for 60s";
							break;
						case 10:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "Knockback ";
							skilltext[3] = "resistance for 60s";
							break;
						case 11:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "Critical rate ";
							skilltext[3] = "+30% for 15s";
							break;
						case 12:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "Critical damage is ";
							skilltext[3] = "+25% for 15s";
							break;
						case 13:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(player.inventory[5 + i + h * 5].skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "def+25% for 15s";
							break;
						default:
							break;
						}
						for (int d = 0; d < 32; d++)
						{
							SetText(skilltext[d], 1500, 440 + (textsize + 4) * d, textsize, 1.00f, 1.0f, 1.00f, 1.0f, 1);
						}


					}


					if (downinvent == 1)
					{
						h = 3;
					}
				}
			}


		}
		//インベントリのアビリティにカーソルを合わせると表示される
		for (int i = 0; i < 3; i++)
		{

			if (corsor.x > 1540 && corsor.x < 1800 &&
				corsor.y >  145 + i * 45 && corsor.y < 190 + i * 45)
			{
				DrawSpriteColorRotate(gui4,
					1600, 100 + i * 45,
					570, 250,
					0.0f, 0.0f,
					1.0f, 0.5f,
					1.0f, 0.5f, 1.0f, 1.0f,
					PAI * 1.0f);
				switch (i)
				{
				case 0:	SetText("     Strength", 1350, -10 + i * 45, 35, 8.0f, 8.0f, 0.0f, 1.0f, 1);
					SetText("1% of Strength is added", 1350, 50 + i * 45, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
					SetText("to all damage", 1350, 80 + i * 45, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
					break;
				case 1:
					SetText("     Dexterity", 1350, -10 + i * 45, 35, 8.0f, 8.0f, 0.0f, 1.0f, 1);
					SetText("1.6% of Dexterity is the", 1350, 50 + i * 45, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
					SetText("critical rate", 1350, 80 + i * 45, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
					break;
				case 2:
					SetText("     Vitality",           1350, -10 + i * 45, 35, 8.0f, 8.0f, 0.0f, 1.0f, 1);
					SetText("Reduces damage by 0.534%",1350, 50 + i * 45, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
					SetText("of Vitality",             1350, 80 + i * 45, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
					SetText("The current reduction is" + std::to_string((int)(player.vit * 0.534f)) + "." + std::to_string(((int)((float)player.vit * 10.0f * 0.534f) % 10)) + "%", 1320, 110 + i * 45, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
					SetText("Reduction up to 90 % ", 1350, 140 + i * 45, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
					
					break;
				default:
					break;
				}
			}
		}
		SetText("E   close", 600, 860, 40, 1.0f, 1.0f, 1.0f, 1.0f, 1);
	}
	//クラフト表示
	if (craftopen == true)
	{
		//インベントリを開いたとき薄暗くするcrafttex[0]
		DrawSpriteColorRotate(g_bg, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 0.1f, 0.1f, 1.0f, 1.0f, 0.8f, 0.5f, 0);
		DrawSpriteColorRotate(crafttex[0], 500, 535.0f, 1000.0f, 1100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);
		DrawSpriteColorRotate(crafttex[0], 1450, 435.0f, 900.0f, 700.0f, 0.2f, 0.2f, 0.6f, 0.6f, 0.5f, 0.5f, 0.5f, 1.0f, 0);

		float hidari = 1.0f;
		float migi = 1.0f;
		if (corsor.x > 300 - 60 && corsor.x < 300 + 60 &&
			corsor.y >  900 - 40 && corsor.y <900 + 40)
		{
			hidari = 0.3f;

		}
		if (corsor.x >700 - 60 && corsor.x < 700 + 60 &&
			corsor.y >  900 - 40 && corsor.y < 900 + 40)
		{
			migi = 0.3f;

		}
		DrawSpriteColorRotate(uitex[1],
			300, 900,
			120.0f, 200.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			0.11f * 12 * hidari, 0.33f * 12 * hidari, 1.0f * 12 * hidari, 1.0f,
			0);
		DrawSpriteColorRotate(uitex[1],
			700, 900,
			120.0f, 200.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			0.11f * 12 * migi, 0.33f * 12 * migi, 1.0f * 12 * migi, 1.0f,
			0);
		SetText("<               >", 317, 843, 30, 0.0f, 0.0f, 0.0f, 1.0f, 1);
		SetText("page :" + std::to_string(craftpage + 1), 400, 835.0f, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
		float craftbotun = 1.0f;
		if (corsor.x > 1450 - 400 && corsor.x < 1450 + 400 &&
			corsor.y >  935 - 70 && corsor.y < 935 + 70)
		{
			craftbotun = 4.0f;
		}
		DrawSpriteColorRotate(g_hpber3,
			1450, 935.0f,
			800.0f, 100.0f,
			0.2f, 0.2f,
			0.6f, 0.6f,
			0.8f * craftbotun, 0.2f * craftbotun, 0.8f * craftbotun, 1.0f,
			0);
		SetText("c r a f t", 1300, 835.0f, 50, 0.8f, 0.8f, 0.60f, 1.0f, 1);
		if (craftitemnom(craftclect).itemno > 0)
		{
			DrawSpriteColorRotate(gui,
				1500, 200,
				80, 80.0f,
				0.2f, 0.2f,
				0.6f, 0.6f,
				0.8f, 1.4f, 2.0f, 1.0f,
				0);
			DrawSpriteColorRotate(gui3,
				1500, 200,
				100.0f, 100.0f,
				0.0f, 0.0f,
				1.0f, 1.0f,
				0.3f, 0.3f, 0.3f, 1.0f,
				0);
			DrawSpriteColorRotate(itemnom[craftitemnom(craftclect).itemtex - 1],
				1500 + 40 - craftitemnom(craftclect).size * 0.5f, 200 + 40 - craftitemnom(craftclect).size * 0.5f,
				craftitemnom(craftclect).size, craftitemnom(craftclect).size,
				0.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0);
			bool craftflag[4] = {false,false ,false ,false };
			for (int i = 0; i < 4; i++)
			{
				if (craftitemnam(craftclect, i) > -1 && craftitemcount(craftclect, i) > -1)
				{
					int hubitem = 0;
					for (int j = 0; j < INBENTMAX; j++)
					{
						if (player.inventory[j].itemno > 0 && player.inventory[j].itemno == craftitemnam(craftclect, i))
						{
							hubitem += player.inventory[j].count;
						}

					}
					SetText(PresetItem(craftitemnam(craftclect, i)).name, 1050, 400 + i * 60, 30, 0.0f, 0.0f, 0.0f, 1.0f, 1);
					SetText(" *" + std::to_string(craftitemcount(craftclect, i)), 1500, 400 + i * 60, 30, 0.0f, 0.0f, 0.0f, 1.0f, 1);
					D3DXCOLOR coler = { 1.0f,0.0f ,0.0f,1.0f };
					if (craftitemcount(craftclect, i) <= hubitem)
					{
						coler = { 0.8f,0.8f,1.0f,1.0f };
						craftflag[i] = true;
					}
					SetText(std::to_string(hubitem), 1700, 400 + i * 60, 30, coler.r, coler.g, coler.b, 1.0f, 1);
				}
				if (craftitemnam(craftclect, i) < 0)
				{
					craftflag[i] = true;
				}
			}
		}
	
			
		for (int r = 0; r < 6; r++)
		{
			float corcoler = 1.0f;
			if (corsor.x > 500 - 380 && corsor.x < 500 + 380 &&
				corsor.y >   190 + r * 120 - 58 && corsor.y < 190 + r * 120 + 58)
			{

				corcoler = 0.3f;
			}
			DrawSpriteColorRotate(uitex[1],
				500, 190 + r * 120,
				700.0f, 450.0f,
				0.0f, 0.0f,
				1.0f, 1.0f,
				corcoler, corcoler, corcoler, 1.0f,
				0);
			if (craftitemnom(r + 6 * craftpage).itemno > 0)
			{
				DrawSpriteColorRotate(gui,
					230, 190 + r * 120,
					80, 80.0f,
					0.2f, 0.2f,
					0.6f, 0.6f,
					0.8f, 1.4f, 2.0f, 1.0f,
					0);
				DrawSpriteColorRotate(gui3,
					230, 190 + r * 120,
					100.0f, 100.0f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					0.3f, 0.3f, 0.3f, 1.0f,
					0);
				DrawSpriteColorRotate(itemnom[craftitemnom(r + 6 * craftpage).itemtex - 1],
					230 + 40 - craftitemnom(r + 6 * craftpage).size * 0.5f, 190 + r * 120 + 40 - craftitemnom(r + 6 * craftpage).size * 0.5f,
					craftitemnom(r + 6 * craftpage).size, craftitemnom(r + 6 * craftpage).size,
					0.0f, 0.0f,
					1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0);
				SetText(craftitemnom(r + 6 * craftpage).name, 300, 140 + r * 120, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);



			}
		}
		for (int r = 0; r < 6; r++)
		{

		
		if (corsor.x > 500 - 380 && corsor.x < 500 + 380 &&
					corsor.y >   190 + r * 120 - 58 && corsor.y < 190 + r * 120 + 58 &&
					craftitemnom(r + 6 * craftpage).itemno > 0)
				{
					int a = 1;
					for (int d = 0; d < 4; d++)
					{
						if (craftitemnom(r + 6 * craftpage).showtext[d] != "")
						{
							a++;

						}
					}
					if (craftitemnom(r + 6 * craftpage).damage != 0)
					{
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).skill != 0)
					{
						a += 2;
					}
					if (craftitemnom(r + 6 * craftpage).str != 0)
					{
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).dex != 0)
					{
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).vit != 0)
					{
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).maxhp != 0)
					{
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).armor != 0)
					{
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).movespeed != 0)
					{
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).attackspeed != 0)
					{
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).range != 0)
					{
						a++;
					}
					int textsize = 13;

					if (textsize < (int)craftitemnom(r + 6 * craftpage).name.length())
					{
						textsize = (int)craftitemnom(r + 6 * craftpage).name.length();


					}
					for (int d = 0; d < 4; d++)
					{

						if (textsize < (int)craftitemnom(r + 6 * craftpage).showtext[d].length())
						{

							textsize = (int)craftitemnom(r + 6 * craftpage).showtext[d].length();
						}
					}
					if (textsize < (int)Getskillname(craftitemnom(r + 6 * craftpage).skill).length() + 6)
					{
						//+6は"skill "の分
						textsize = (int)Getskillname(craftitemnom(r + 6 * craftpage).skill).length() + 6;
					}




					int overa = 0;
					if (a > 7)
					{
						overa = a - 7;
					}
					DrawSpriteColorRotate(gui4,
						550 + textsize * 12.5f, 140 + r * 120.0f + a * 15 + 20 - overa * 30,
						75.0f + textsize * 25, 15.0f + 30 + a * 30.0f,
						0.0f, 0.0f,
						1.0f, 0.5f,
						1.0f, 0.5f, 1.0f, 1.0f,
						PAI * 1.0f);
					DrawSpriteColorRotate(gui4,
						550 + textsize * 12.5f, 140 + r * 120.0f - overa * 30,
						75.0f + textsize * 25, 15.0f,
						0.0f, 0.0f,
						1.0f, 1.0f,
						1.0f, 1.0f, 1.0f, 1.0f,
						0);
					DrawSpriteColorRotate(gui4,
						550 + textsize * 12.5f, 140 + r * 120.0f + a * 30 + 40 - overa * 30,
						75.0f + textsize * 25, 15.0f,
						0.0f, 0.0f,
						1.0f, 1.0f,
						1.0f, 1.0f, 1.0f, 1.0f,
						PAI * 1.0f);
					a = 0;
					SetText(craftitemnom(r + 6 * craftpage).name, 550 + textsize * 3, 130 + 120.0f * r + 30 * a - overa * 30, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
					a++;
					if (craftitemnom(r + 6 * craftpage).skill != 0)
					{
						float coler[3] = { 0.70f,0.7f,0.70f };
						SetText("Skill " + Getskillname(craftitemnom(r + 6 * craftpage).skill), 550 + textsize * 3, 130 + 120.0f * r + 30 * a - overa * 30, 27, coler[0], coler[1], coler[2], 1.0f, 1);

						a += 2;
					}
					for (int d = 0; d < 4; d++)
					{
						if (craftitemnom(r + 6 * craftpage).showtext[d] != "")
						{
							SetText(craftitemnom(r + 6 * craftpage).showtext[d], 550 + textsize * 3, 130 + 120.0f * r + 30 * a - overa * 30, 25, 1.0f, 1.0f, 1.0f, 1.0f, 1);
							a++;

						}
					}

					if (craftitemnom(r + 6 * craftpage).damage != 0)
					{
						float coler[3] = { 0.75f,0.75f,0.75f };
						SetText("damage  ", 550 + textsize * 3, 130 + 120.0f * r+ 30 * a - overa * 30, 25, 0.2f, 0.8f, 0.2f, 1.0f, 1);
						SetText(std::to_string((int)craftitemnom(r + 6 * craftpage).damage) + "." + std::to_string((int)(craftitemnom(r + 6 * craftpage).damage * 10) % 10), 550 + textsize * 3 + 200, 130 + 120.0f * r + 30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					
					if (craftitemnom(r + 6 * craftpage).str != 0)
					{
						float coler[3] = { 0.75f,0.82f,0.2f };
						std::string statustext = { "+" };
						if (craftitemnom(r + 6 * craftpage).str < 0)
						{
							coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
							statustext = { "" };
						}
						SetText("str     ", 550 + textsize * 3, 130 + 120.0f * r+ 30 * a - overa * 30, 25, 1.0f, 0.2f, 0.2f, 1.0f, 1);
						SetText(statustext + std::to_string((int)craftitemnom(r + 6 * craftpage).str), 550 + textsize * 3 + 200, 130 + 120.0f * r+ 30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).dex != 0)
					{
						float coler[3] = { 0.75f,0.82f,0.2f };
						std::string statustext = { "+" };
						if (craftitemnom(r + 6 * craftpage).dex < 0)
						{
							coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
							statustext = { "" };
						}
						SetText("dex     ", 550 + textsize * 3, 130 + 120.0f * r+ 30 * a - overa * 30, 25, 1.0f, 0.2f, 0.2f, 1.0f, 1);
						SetText(statustext + std::to_string((int)craftitemnom(r + 6 * craftpage).dex), 550 + textsize * 3 + 200, 130 + r * 120.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).vit != 0)
					{
						float coler[3] = { 0.75f,0.82f,0.2f };
						std::string statustext = { "+" };
						if (craftitemnom(r + 6 * craftpage).vit < 0)
						{
							coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
							statustext = { "" };
						}
						SetText("vit     ", 550 + textsize * 3, 130 + 120.0f * r+ 30 * a - overa * 30, 25, 1.0f, 0.2f, 0.2f, 1.0f, 1);
						SetText(statustext + std::to_string((int)craftitemnom(r + 6 * craftpage).vit), 550 + textsize * 3 + 200, 130 + r * 120.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).maxhp != 0)
					{
						float coler[3] = { 0.75f,0.82f,0.2f };
						std::string statustext = { "+" };
						if (craftitemnom(r + 6 * craftpage).maxhp < 0)
						{
							coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
							statustext = { "" };
						}
						SetText("maxhealth", 550 + textsize * 3, 130 + 120.0f * r+ 30 * a - overa * 30, 25, 1.0f, 0.0f, 1.0f, 1.0f, 1);
						SetText(statustext + std::to_string((int)craftitemnom(r + 6 * craftpage).maxhp), 550 + textsize * 3 + 200, 130 + r * 120.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).armor != 0)
					{
						float coler[3] = { 0.75f,0.82f,0.2f };
						std::string statustext = { "+" };
						if (craftitemnom(r + 6 * craftpage).armor < 0)
						{
							coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
							statustext = { "" };
						}
						SetText("armor", 550 + textsize * 3, 130 + 120.0f * r+ 30 * a - overa * 30, 25, 0.3f, 0.3f, 0.3f, 1.0f, 1);
						SetText(statustext + std::to_string((int)craftitemnom(r + 6 * craftpage).armor), 550 + textsize * 3 + 200, 130 + r * 120.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).movespeed != 0)
					{
						float coler[3] = { 0.75f,0.82f,0.2f };
						std::string statustext = { "+" };
						if (craftitemnom(r + 6 * craftpage).movespeed < 0)
						{
							coler[0] = 1.0f; coler[1] = 0.0f; coler[2] = 0.0f;
							statustext = { "" };
						}
						SetText("movespeed", 550 + textsize * 3, 130 + 120.0f * r+ 30 * a - overa * 30, 25, 0.8f, 0.8f, 1.0f, 1.0f, 1);
						SetText(statustext + std::to_string((int)craftitemnom(r + 6 * craftpage).movespeed) + "%", 550 + textsize * 3 + 200, 130 + r * 120.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).range != 0)
					{
						float coler[3] = { 0.75f,0.75f,0.75f };
						SetText("range   ", 550 + textsize * 3, 130 + 120.0f * r+ 30 * a - overa * 30, 25, 1.0f, 1.0f, 0.0f, 1.0f, 1);
						SetText(std::to_string((int)craftitemnom(r + 6 * craftpage).range), 550 + textsize * 3 + 200, 130 + r * 120.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					if (craftitemnom(r + 6 * craftpage).attackspeed != 0)
					{
						float coler[3] = { 0.75f,0.75f,0.75f };
						SetText("atkspeed ", 550 + textsize * 3, 130 + 120.0f * r+ 30 * a - overa * 30, 25, 0.7f, 0.7f, 0.7f, 1.0f, 1);
						SetText(std::to_string((int)craftitemnom(r + 6 * craftpage).attackspeed), 550 + textsize * 3 + 200, 130 + r * 120.0f + +30 * a - overa * 30, 25, coler[0], coler[1], coler[2], 1.0f, 1);
						a++;
					}
					//スキルウィンドウ表示
					if (craftitemnom(r + 6 * craftpage).skill != 0)
					{
						DrawSpriteColorRotate(gui4,
							1650, 700,
							500, 600,
							0.0f, 0.0f,
							1.0f, 0.5f,
							1.0f, 0.5f, 1.0f, 1.0f,
							PAI * 1.0f);
						//スキルの詳細説明
						SetText(Getskillname(craftitemnom(r + 6 * craftpage).skill), 1500, 400, 30, 0.70f, 0.0f, 0.70f, 1.0f, 1);
						int textsize = 25;
						std::string skilltext[32] = {};
						switch (craftitemnom(r + 6 * craftpage).skill)
						{
						case 1:
							skilltext[1] = "Cooldown     " + std::to_string((int)(Getskillct(craftitemnom(r + 6 * craftpage).skill) / 60.0f)) + "." + std::to_string((int)(Getskillct(craftitemnom(r + 6 * craftpage).skill) * 10 / 60.0f) % 10) + "s";
							skilltext[2] = "Damage       2";
							skilltext[3] = "Range        600";

							break;
						default:
							break;
						}
						for (int d = 0; d < 32; d++)
						{
							SetText(skilltext[d], 1500, 440 + (textsize + 4) * d, textsize, 1.00f, 1.0f, 1.00f, 1.0f, 1);
						}


					}
				}
			}
			SetText("F   close", 100, 960, 40, 1.0f, 1.0f, 1.0f, 1.0f, 1);
	}
	//ポータル表示
	if (portal.open == true)
	{
		DrawSpriteColorRotate(g_bg, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 0.1f, 0.1f, 1.0f, 1.0f, 0.8f, 0.5f, 0);
		DrawSpriteColorRotate(portalui[0], 600, 540, 600, 800, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0);
		DrawSpriteColorRotate(portalui[0], 1250, 540, 700, 800, 0.0f, 0.0f, 1.0f, 1.0f, 1.5f, 1.5f, 1.5f, 1.0f, 0);
		for(int i= 0; i < 4; i++)
		{
			if (stageflag[i + portal.dangionpage * 4][0] > -1)
			{
				DrawSpriteColorRotate(uitex[1],
					600, 250 + i * 190,
					540.0f, 600.0f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					0.8f, 0.8f, 0.8f, 1.0f,
					0);
				SetText(Getdangiongame(portal.dangionselect + portal.dangionpage * 4), 400, 180 + i * 190, 30, 1.0f, 1.0f, 1.0f, 1.0f, 1);
			}

		}
		for (int i = 0; i < 5; i++)
		{
			D3DXCOLOR portaluicoler;
			portaluicoler = { 1.0f,1.0f,1.0f,1.0f };
			if (corsor.x > 1250 - 300 && corsor.x < 1250 + 300 &&
				corsor.y > i * 150 - 70 + 250 && corsor.y < i * 150 + 70 + 250)
			{
				portaluicoler = { 2.0f,2.0f ,2.0f ,1.0f };
			}
			if (stageflag[portal.dangionselect + portal.dangionpage * 4][portal.page * 5  + i] == 0)
			{
				DrawSpriteColorRotate(uitex[1],
					1250, 250 + i * 150,
					600.0f, 330.0f,
					0.2f, 0.2f,
					0.6f, 0.6f,
					portaluicoler.r, portaluicoler.g, portaluicoler.b, 1.0f,
					0);
				SetText("|  "+std::to_string(portal.page * 5 + 1 + i) + "F", 1000, 180 + i * 150, 40, 1.0f, 1.0f, 1.0f, 1.0f, 1);
			}
			
		}
		if (true)
		{

		}	
		D3DXCOLOR portaluicoler;
		portaluicoler = {1.0f,1.0f,1.0f,1.0f};
		if (corsor.x > 1600 - 25 && corsor.x < 1600 + 25 &&
			corsor.y >  750 - 100 && corsor.y < 750 + 100)
		{
			portaluicoler = { 2.0f,2.0f ,2.0f ,1.0f };
		}
		DrawSpriteColorRotate(portalui[1],
			1600, 750,
			50.0f, 200.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			portaluicoler.r, portaluicoler.g, portaluicoler.b, 1.0f,
			0);

		portaluicoler = { 1.0f,1.0f,1.0f,1.0f };
		if (corsor.x > 1600 - 25 && corsor.x < 1600 + 25 &&
			corsor.y >  350 - 100 && corsor.y < 350 + 100)
		{
			portaluicoler = { 2.0f,2.0f ,2.0f ,1.0f };
		}
		DrawSpriteColorRotate(portalui[1],
			1600, 350,
			50.0f, 200.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			portaluicoler.r, portaluicoler.g, portaluicoler.b, 1.0f,
			PAI * 1.0f);
		SetText("F   close", 350, 900, 40, 1.0f, 1.0f, 1.0f, 1.0f, 1);
	}

	//マウスでアイテムを持ってる時に表示
	if (itemhave.itemno > 0)
	{
		DrawSpriteColorRotate(itemhave.itemtex,
			corsor.x+ 60 - itemhave.size * 0.5f * 1.25f * 1.2f, corsor.y + 60 - itemhave.size * 0.5f * 1.25f * 1.2f,
			itemhave.size*1.25f * 1.2f, itemhave.size * 1.25f* 1.2f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0);
	}
	//カーソル表示
	{
		DrawSpriteColorRotate(g_Texcursor,
			corsor.x, corsor.y,
			100.0f, 100.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			-0.125f * 3.141593f);
	}

}
void SetText(std::string settext, float X, float Y, float size, float r, float g, float b, float z, int font) {
	char* lentext = new char[settext.size() + 1];
	std::char_traits<char>::copy(lentext, settext.c_str(), settext.size() + 1);
	if (font == 0)
	{

		int pos[2] = {};
		for (unsigned int i = 0; i < strlen(lentext); i++)
		{
			if (lentext[i] >= 0x20)
			{
				pos[0] = 10;
				pos[1] = 0;
			}
			if (lentext[i] >= 0x30 && lentext[i] <= 0x39)
			{
				pos[0] = (int)lentext[i] - 48;
				pos[1] = 0;
			}
			if (lentext[i] >= 0x61 && lentext[i] <= 0x6D)
			{
				pos[0] = (int)lentext[i] - 97;
				pos[1] = 1;
			}
			if (lentext[i] >= 0x6E && lentext[i] <= 0x7A)
			{
				pos[0] = (int)lentext[i] - 110;
				pos[1] = 2;
			}
			if (lentext[i] >= 0x41 && lentext[i] <= 0x4D)
			{
				pos[0] = (int)lentext[i] - 65;
				pos[1] = 3;
			}
			if (lentext[i] >= 0x4E && lentext[i] <= 0x5A)
			{
				pos[0] = (int)lentext[i] - 78;
				pos[1] = 3;
			}
			if (lentext[i] == 0x2D)
			{
				pos[0] = 11;
				pos[1] = 0;
			}
			if (lentext[i] == 0x2E)
			{
				pos[0] = 10;
				pos[1] = 0;
			}
			float a[2] = { 0.07240f ,0.142f };
			DrawSpriteColorRotate(
				g_TexMozi[font], 50.0f + i * size + X, size * 2 + Y,
				size, size * 2,
				-0.0f + a[0] * pos[0], 0.0044f + a[1] * pos[1], a[0], a[1],
				r, g, b, z,
				0.0f
			);


		}
	}
	if (font == 1)
	{
		int pos[2] = {};
		for (unsigned int i = 0; i < strlen(lentext); i++)
		{

			pos[0] = ((int)lentext[i] - 32) % 16;
			pos[1] = (((int)lentext[i] - 32) / 16);

			float a[2] = { 1.0f / 16.0f ,0.16666f };
			DrawSpriteColorRotate(
				g_TexMozi[font],
				i * size * 0.8f + X, size * 2.0f + Y,
				size, size * 1.3f,
				a[0] * pos[0], a[1] * pos[1], a[0], a[1],
				r, g, b, z,
				0.0f
			);


		}
	}
	delete[] lentext;
}
void SetDamage(float sedamage, D3DXVECTOR2 sepos, D3DXCOLOR secoler, int setype, int sevel) {

	for (int i = 0; i < MAX_DAMAGETEXT; i++)
	{
		if (damagetext[i].use == false)
		{
			damagetext[i].vel = sevel;
			damagetext[i].use = true;
			damagetext[i].color = secoler;
			damagetext[i].damage = sedamage;
			damagetext[i].type = setype;
			damagetext[i].pos = sepos;
			damagetext[i].time = 0;
			break;
		}
	}
}

D3DXVECTOR2 Getcamera() {
	return camera;
}
D3DXVECTOR2 Getcorsor() {
	return bgcorsor;
}
D3DXVECTOR2 GetNowcorsor() {
	return corsor;
}
int haveitem() {
	return hoir;
}
bool gettabopen() {
	return inventopen;
}
bool shopbopen() {
	return shopopen;
}
int* shopmoder() {
	return &shopmode;
}
int* shopppage() {
	return &shopbuypage;
}
void GetItem(WEAPONITEM n) { itemhave = n; }
int GetItemtex(int n) {
	return itemnom[n];
}
std::string Getskillname(int n) {
	switch (n)
	{
	case 1:return "Magic bullet";
		break;
	case 2:return "Magic bullet +";
		break;
	case 3:return "Magic bullet ++";
		break;
	case 4:return "Magic buckshot";
		break;
	case 5:return "Thorn in the dirt";
		break;
	case 6:return "Ice bullet";
		break;
	case 7:return "Speed";
		break;
	case 8:return "HP boost";
		break;
	case 9:return "Slow resist";
		break;
	case 10:return "Knockback resist";
		break;
	case 11:return "Crit Rete UP";
		break;
	case 12:return "Crit Damage UP";
		break;
	case 13:return "DEF UP";
		break;
	default:
		break;
	}
	return "";
}
int Getskillct(int n) {

	switch (n)
	{
	case 1:return 60 * 8;//bullet
		break;
	case 2:return 60 * 10;//bullet+
		break;
	case 3:return 60 * 8;//bullet++
		break;
	case 4:return 60 * 40;//ショットガン
		break;
	case 5:return 60 * 8;//スパイク
		break;
	case 6:return 60 * 8;//氷
		break;
	case 7:return 60 * 30;//spd
		break;
	case 8:return 60 * 300;//hp
		break;
	case 9:return 60 * 300;//slow耐性
		break;
	case 10:return 60 * 300;//ノックバック耐性
		break;
	case 11:return 60 * 60;//クリ率UP
		break;
	case 12:return 60 * 60;//クリダメUP
		break;
	case 13:return 60 * 30;//defUP
		break;

	default:
		break;
	}
	return 0;
}
int* shoppclect() {
	return &shopbuyclect;
}
bool *craftpopen() {

	return &craftopen;
}
int* craftppage() {

	return &craftpage;
}
int* craftpcelct() {
	return &craftclect;
}
PORTAL* pGetportal() {
	return &portal;
}
std::string Getdangiongame(int n) {
	switch (n)
	{
	case 0:return "skeleton dungeon";
		break;

	default:
		break;
	}
	return "";
}
void clearPorigon() {
	stagemassage = 0;

}
int Getstageflag(int n,int m) {
	return stageflag[n][m];
}
int Getbgmvol() {
	return bgmsoundvolume;
}