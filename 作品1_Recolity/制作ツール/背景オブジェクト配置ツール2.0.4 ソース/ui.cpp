//=============================================================================
//
// ユーザーインターフェース表示処理 [ui.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "ui.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量

#define	SCALE_X			(57.0f * 3.0f)
#define	SCAlE_Y			(89.0f * 3.0f)

#define	NUM_VERTEX		(4)						// 頂点数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// 頂点情報


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUI(void)
{
	
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUI(void)
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
void UpdateUI(void)
{
	CAMERA *cam = GetCamera();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUI(void)
{
	// ライト
	SetLightEnable(false);

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	for (int i = 0; i < 5; i++)
	{
		//DrawScreen(&g_Card[i], g_TexNo);
	}


	// Z比較あり
	SetDepthEnable(true);

	// ライト
	SetLightEnable(false);
}

//=============================================================================
// 2D頂点設定
//=============================================================================
void DrawScreen2(UI2 pol,int tex)
{

	//フィルタリングモード：ポイントフィルタ（フィルタリング無し　ピクセルがくっきり見える）
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);
	// ライト
	SetLightEnable(false);
	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	// 頂点バッファへのポインタを取得
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;


	float hw, hh;
	hw = pol.m_Scl.x * 0.5f;
	hh = pol.m_Scl.y * 0.5f;

	// 座標変換
	pVtx[0].Position.x = (-hw) * cosf(pol.m_Rot) - (-hh) * sinf(pol.m_Rot) + pol.m_Pos.x;
	pVtx[0].Position.y = (-hw) * sinf(pol.m_Rot) + (-hh) * cosf(pol.m_Rot) + pol.m_Pos.y;
	pVtx[1].Position.x = ( hw) * cosf(pol.m_Rot) - (-hh) * sinf(pol.m_Rot) + pol.m_Pos.x;
	pVtx[1].Position.y = ( hw) * sinf(pol.m_Rot) + (-hh) * cosf(pol.m_Rot) + pol.m_Pos.y;
	pVtx[2].Position.x = (-hw) * cosf(pol.m_Rot) - ( hh) * sinf(pol.m_Rot) + pol.m_Pos.x;
	pVtx[2].Position.y = (-hw) * sinf(pol.m_Rot) + ( hh) * cosf(pol.m_Rot) + pol.m_Pos.y;
	pVtx[3].Position.x = ( hw) * cosf(pol.m_Rot) - ( hh) * sinf(pol.m_Rot) + pol.m_Pos.x;
	pVtx[3].Position.y = ( hw) * sinf(pol.m_Rot) + ( hh) * cosf(pol.m_Rot) + pol.m_Pos.y;
	
	pVtx[0].Diffuse = D3DXCOLOR(pol.m_Color.r, pol.m_Color.g, pol.m_Color.b, pol.m_Color.a);
	pVtx[1].Diffuse = D3DXCOLOR(pol.m_Color.r, pol.m_Color.g, pol.m_Color.b, pol.m_Color.a);
	pVtx[2].Diffuse = D3DXCOLOR(pol.m_Color.r, pol.m_Color.g, pol.m_Color.b, pol.m_Color.a);
	pVtx[3].Diffuse = D3DXCOLOR(pol.m_Color.r, pol.m_Color.g, pol.m_Color.b, pol.m_Color.a);
	
	pVtx[0].TexCoord = D3DXVECTOR2(pol.m_Uv_v.x, pol.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(pol.m_Uv_v.x + pol.m_Uv_f.x, pol.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(pol.m_Uv_v.x, pol.m_Uv_v.y + pol.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(pol.m_Uv_v.x + pol.m_Uv_f.x, pol.m_Uv_v.y + pol.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));

	// ユーザーインターフェース描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

	// Z比較あり
	SetDepthEnable(true);
}
