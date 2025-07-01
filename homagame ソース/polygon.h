/*==============================================================================

   頂点管理[polygon.h]
   インベントリやマップの描画などをする
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
void DrawPolygon2(void);
//ウィンドウにテキストを表示する
void SetText(std::string settext, float X, float Y, float size, float r = 1.0f, float g = 1.0f, float b = 1.0f, float z = 1.0f, int font = 0);

D3DXVECTOR2 Getcamera();
D3DXVECTOR2 Getcorsor();
//ダメージの表示
void SetDamage(float damage, D3DXVECTOR2 pos//x y
	, D3DXCOLOR coler//r,g,b,aのカラー
	, int type//フォント
	,int vel//ダメージのテキストが飛んでいく方向
);
typedef struct {
	bool open;//開いているか
	int page;//階層ページ
	int dangionselect;//選んでるダンジョン
	int dangionpage;//ダンジョンページ
}PORTAL;
int haveitem();
bool gettabopen();//インベントリが開いてるか
bool shopbopen();//ショップをひらいているか
D3DXVECTOR2 GetNowcorsor();
void GetItem(WEAPONITEM n);
int GetItemtex(int n);
std::string Getskillname(int n);//スキルの名前を取得
int Getskillct(int n);//スキルのクールタイム
int* shopmoder();
int* shopppage();
int* shoppclect();
bool* craftpopen();
int* craftpcelct();
int* craftppage();
PORTAL* pGetportal();
std::string Getdangiongame(int n);
void clearPorigon();
int Getstageflag(int n, int m);
int Getbgmvol();