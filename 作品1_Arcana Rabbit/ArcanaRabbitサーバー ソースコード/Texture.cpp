/*==============================================================================

   テクスチャの読み込み [texture.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "Texture.h"
/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/
#define MAX_TEXTURE_NUM 100

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
ID3D11ShaderResourceView*	g_pTexture[MAX_TEXTURE_NUM] = {};	//テクスチャ配列
unsigned int g_TextureIndex = 0;					// テクスチャ配列の末尾を示すインデックス
wchar_t g_TextureName[MAX_TEXTURE_NUM][256] = {};	// テクスチャ名バッファ

/*------------------------------------------------------------------------------
	テクスチャの読み込み
------------------------------------------------------------------------------*/
int LoadTexture(const wchar_t* fileName)
{
	//読み込まれているテクスチャ名を調べて、同名のものが
	//すでに読み込まれていたらその番号を返す
	for (unsigned int i = 0; i < g_TextureIndex; i++)
	{
		//テクスチャ名を比較
		if (g_TextureName[i] ==fileName)
		{
			return i;
		}
	}

	//読み込み最大数を超えていたら負の値を返す
	if (g_TextureIndex == MAX_TEXTURE_NUM)
	{
		return -1;
	}
	// テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	HRESULT hr_load  = LoadFromWICFile(fileName, WIC_FLAGS_NONE, &metadata, image);
	HRESULT hr_shader =  CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &g_pTexture[g_TextureIndex]);
	assert(&g_pTexture[g_TextureIndex]);



	if (S_OK != hr_load)
	{
		//読み込みに失敗した場合、負の値を返す
		return -1;
	}
	if (S_OK != hr_shader)
	{
		//読み込みに失敗した場合、負の値を返す
		return -2;
	}
	//読み込んだテクスチャ名を保存する
	//strcpy_s(g_TextureName[g_TextureIndex], 256, fileName);
	wcscpy(g_TextureName[g_TextureIndex] , fileName);
	;
	int retIndex = g_TextureIndex;
	
	//インデックスを一つ進める
	g_TextureIndex++;

	return retIndex;

}

void UninitTexture(void)
{
	for (unsigned int i = 0; i < g_TextureIndex; i++)
	{
		if (g_pTexture[i] != NULL)
		{
			g_pTexture[i]->Release();
			g_pTexture[i] = NULL;
		}
	}
}



/*------------------------------------------------------------------------------
	テクスチャのゲッター
------------------------------------------------------------------------------*/
ID3D11ShaderResourceView** GetTexture(int index)
{
	//indexの不正値チェック(負の値)
	if (index < 0)
		return NULL;

	//indexの不正値チェック(最大数オーバー)
	if (index >= (int)g_TextureIndex)
		return NULL;

	return &g_pTexture[index];
}
