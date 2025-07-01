//=============================================================================
//
// ポリゴン表示処理 [polygon.cpp]
// Author :
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "polygon.h"
#include "texture.h"
#include "font.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量

#define	SIZE_X			(100.0f)					// 地面のサイズ(X方向)
#define	SIZE_Y			(100.0f)					// 地面のサイズ(Y方向)
#define	SIZE_Z			(100.0f)					// 地面のサイズ(Z方向)

#define POLYGON_NUM 10000
DirectWrite* g_Write[5];
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPolygon(void);
void toVertex(int index);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// 頂点情報

static POLYGON						g_Polygon[POLYGON_NUM];			// ポリゴンデータ
static VERTEX_3D					g_VertexArray[POLYGON_NUM * 4];
static int							g_TexNo;			// テクスチャ番号
static int							g_VertexIndex;			// テクスチャ番号

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPolygon(void)
{
	int index = 0;
	float xpos = SIZE_X * (POLYGON_NUM / 100 / 2) * -1;
	float zpos = SIZE_Z * (POLYGON_NUM / 100 / 2);
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			g_Polygon[index].pos = D3DXVECTOR3(xpos + SIZE_X * j, 0.0f, SIZE_Z - SIZE_Z * i);
			index++;
		}
	}

	g_VertexIndex = 0;
	for (int i = 0; i < POLYGON_NUM; i++)
	{
		toVertex(i);
	}

	// 頂点バッファの作成
	MakeVertexPolygon();

	// テクスチャ生成
	g_TexNo = LoadTexture((char*)"data/TEXTURE/yuka.png");


	// 位置・回転・スケールの初期設定
	for (int i = 0; i < POLYGON_NUM; i++)
	{
		g_Polygon[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Polygon[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Polygon[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}


	//フォントデータの初期化
	
	FontData* fodata[5];
		for (int i = 0; i < 5; i++)
		{
			fodata[i] = new  FontData();
		}

	for (int i = 0; i < 5; i++)
	{
		fodata[i]->fontSize = 10 + i * 5;
		fodata[i]->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
		g_Write[i] = new DirectWrite(fodata[i]);
		g_Write[i]->TextInit();
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{
	// 頂点バッファの解放
	if (g_VertexBuffer) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{
	CAMERA *cam = GetCamera();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon_Field(void)
{
	//// 頂点バッファ設定
	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;
	//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	//// プリミティブトポロジ設定
	//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//// テクスチャ設定
	//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));


	//D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//for (int i = 0; i < POLYGON_NUM; i++)
	//{
	//	// ワールドマトリックスの初期化
	//	D3DXMatrixIdentity(&g_Polygon[i].mtxWorld);

	//	// スケールを反映
	//	D3DXMatrixScaling(&mtxScl, g_Polygon[i].scl.x, g_Polygon[i].scl.y, g_Polygon[i].scl.z);
	//	D3DXMatrixMultiply(&g_Polygon[i].mtxWorld, &g_Polygon[i].mtxWorld, &mtxScl);

	//	// 回転を反映
	//	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Polygon[i].rot.y, g_Polygon[i].rot.x , g_Polygon[i].rot.z);
	//	D3DXMatrixMultiply(&g_Polygon[i].mtxWorld, &g_Polygon[i].mtxWorld, &mtxRot);

	//	// 移動を反映
	//	/*D3DXMatrixTranslation(&mtxTranslate, g_Polygon[i].pos.x, g_Polygon[i].pos.y, g_Polygon[i].pos.z);
	//	D3DXMatrixMultiply(&g_Polygon[i].mtxWorld, &g_Polygon[i].mtxWorld, &mtxTranslate);*/

	//	// ワールドマトリックスの設定
	//	SetWorldMatrix(&g_Polygon[i].mtxWorld);

	//	// ポリゴン描画
	//	GetDeviceContext()->Draw(4, i * 4);
	//}
}
HRESULT MakeVertexPolygon(void)
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;;
	bd.ByteWidth = sizeof(VERTEX_3D) * POLYGON_NUM * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// グローバルの頂点配列から頂点バッファをつくる
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = g_VertexArray;

	GetDevice()->CreateBuffer(&bd, &sd, &g_VertexBuffer);

	return S_OK;
}

void toVertex(int index)
{
	//ポジション
	g_VertexArray[g_VertexIndex + 0].Position = D3DXVECTOR3(g_Polygon[index].pos.x - (SIZE_X / 2), 0.0f, g_Polygon[index].pos.z + (SIZE_Z / 2));
	g_VertexArray[g_VertexIndex + 1].Position = D3DXVECTOR3(g_Polygon[index].pos.x + (SIZE_X / 2), 0.0f, g_Polygon[index].pos.z + (SIZE_Z / 2));
	g_VertexArray[g_VertexIndex + 2].Position = D3DXVECTOR3(g_Polygon[index].pos.x - (SIZE_X / 2), 0.0f, g_Polygon[index].pos.z - (SIZE_Z / 2));
	g_VertexArray[g_VertexIndex + 3].Position = D3DXVECTOR3(g_Polygon[index].pos.x + (SIZE_X / 2), 0.0f, g_Polygon[index].pos.z - (SIZE_Z / 2));

	//法線・カラー
	for (int i = 0; i < 4; i++)
	{
		g_VertexArray[g_VertexIndex + i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_VertexArray[g_VertexIndex + i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	g_VertexArray[g_VertexIndex + 0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	g_VertexArray[g_VertexIndex + 1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	g_VertexArray[g_VertexIndex + 2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	g_VertexArray[g_VertexIndex + 3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	g_VertexIndex += 4;
}
void SetText(std::string text, D3DXVECTOR2 pos, Textsize size) {

	switch (size)
	{
	case TextSc_1:g_Write[0]->DrawString(text, { pos.x,pos.y,SCREEN_WIDTH,SCREEN_HEIGHT }, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		break;
	case TextSc_2:g_Write[1]->DrawString(text, { pos.x,pos.y,SCREEN_WIDTH,SCREEN_HEIGHT }, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		break;
	case TextSc_3:g_Write[2]->DrawString(text, { pos.x,pos.y,SCREEN_WIDTH,SCREEN_HEIGHT }, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		break;
	case TextSc_4:g_Write[3]->DrawString(text, { pos.x,pos.y,SCREEN_WIDTH,SCREEN_HEIGHT }, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		break;
	case TextSc_5:g_Write[4]->DrawString(text, { pos.x,pos.y,SCREEN_WIDTH,SCREEN_HEIGHT }, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		break;
	default:
		break;
	}
	
}