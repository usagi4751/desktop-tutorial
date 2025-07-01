//*****************************************************************************
//	draw2d_Manager.h 
// Draw2D_Manager2....初期化、終了、更新、描画処理。生成をする
// 
// 以下クラス図
// 
//         UI(継承元)
//     ┌─┴─┐
//     │      │
// UI_Text   UI_Tex
// 文字描画  画像描画
//*****************************************************************************
#pragma once
#include "main.h"
#include "font.h"
#include "gameObject.h"
#include <list>
#define DEPTH_NOMAL (0.1f) //基本深度
//*****************************************************************************
//前方宣言
//*****************************************************************************

class UI;
class UI_Tex;
class UI_Text;
//*****************************************************************************
// 構造体宣言
//*****************************************************************************
struct DrawTex //バッファーやシェーダー関連の構造体
{
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
};

struct  UITexData //画像2D描画で使用する
{
	bool m_UpdateFlug = false;//画像の更新が入ったかの確認用ポリゴンの再生成するために使う
	bool m_DrawFlug = true;//ポリゴンの表示をするか
	XMFLOAT4   m_Color = { 1.0f,1.0f ,1.0f ,1.0f };
	XMFLOAT2   m_Position = {50.0f,50.0f};
	XMFLOAT2   m_Scale = { 100.0f,100.0f };;
	XMFLOAT2   m_UV_uv = {0.0f,0.0f};	// UV値左 : 上
	XMFLOAT2   m_UV_UV = { 1.0f,1.0f };;	// UV値右 : 下
	float   m_Rotation = 0.0f;
	int     m_Tex = 0;
};
//2D描画の管理　
//仕様
//機能：初期化、更新、描画、UIオブジェクトの追加
//UIを使いたい場合Draw2D_Managerを使用して作った物でないと表示されない
//変更は生成時に受け取ったポインタでセット関数を呼ぶことで変更可能

class Draw2D_Manager {
private:
	static bool m_ClearFlug;//テキストがクリアされるかのフラグ
	static std::list<UI*> m_DeleteList;//削除されるUI
	static std::list<UI*> m_UIList;

	static DrawTex m_Shader;//シェーダ
	static DirectWrite* m_write;//文字表示クラス
public:
	static UI_Tex* AddUI();//画像の描画追加
	static UI_Text* AddTEXT();//テキストの追加
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	//現在あるUIをすべて削除する
	static void Clear();
	//指定のUIを削除する
	static void DeleateUI(UI* ui);
};



//===============================
//基底クラス
//===============================
class UI {	

public:
	float  m_Depth;	//UIの深度
	bool   m_Active;//表示するか
	virtual ~UI() = default;

	virtual void   Init() = 0;
	virtual void   UnInit() = 0;
	virtual void   Update() = 0;
	virtual void   Draw() = 0;
};

//====================
// 文字表示用のクラス
//====================
class UI_Text : public UI{
private:
	UI_Text* m_Object;//setで変更されるText
	XMFLOAT4   m_Color = {1.0f,1.0f ,1.0f ,1.0f };		// 文字のカラー
	D2D1_RECT_F m_rect;		//描画の範囲範囲を超えると改行される
	float m_scale;			//文字サイズ
	std::string* m_text;		//描画される文字
	DirectWrite* m_write;	//描画クラス
public: 
	UI_Text(DirectWrite* write) : m_write(write) { m_scale = 30; m_text = new std::string; };
	UI_Text() { m_scale = 30; };
	void Link(UI_Text* link) { m_Object = link; };

	void SetRect(XMFLOAT4 Rect) { if (m_Object != nullptr) { m_Object ->m_rect = { Rect.x,Rect.y,Rect.z,Rect.w };}  }
	void SetColer(XMFLOAT4 coler) { if (m_Object != nullptr) { m_Object->m_Color = coler; } }
	void SetText(std::string text) { 
		if (m_Object != nullptr) { *m_Object->m_text = text; } 
	};
	void SetScale(float scale) { if (m_Object != nullptr) { m_Object->m_scale = scale; } };
	void  SetDepth(float Depth) { if (m_Object != nullptr) { m_Object->m_Depth = Depth; }; }
	void SetActive(bool active) { if (m_Object != nullptr) { m_Object->m_Active = active; }; };
	UI_Text* GetObjectData() {return m_Object;};
	void Init() {};
	void UnInit() ;
	void Update() {};
	void Draw() override;
};
//====================
// 画像表示用のクラス
//====================
class UI_Tex : public UI
{
private:
	UI_Tex* m_Object;//setで変更されるUI
	//ポリゴンの生成に必要なデータ
	UITexData m_Texdata;

	ID3D11Buffer* m_VertexBuffer = nullptr;
public:
	void Init() ;
	void UnInit();
	void Update();
	void Draw() override;

	void Link(UI_Tex* link) { m_Object = link; };

	//セッター
	void SetColer(XMFLOAT4 coler) { if (m_Object != nullptr) { m_Object->m_Texdata.m_Color = coler; } };
	void SetPosition(XMFLOAT2 position) { if (m_Object != nullptr) { m_Object->m_Texdata.m_Position = position;  m_Object->m_Texdata.m_UpdateFlug = true; } };
	void SetScale(XMFLOAT2 scale) { if (m_Object != nullptr) { m_Object->m_Texdata.m_Scale = scale;  m_Object->m_Texdata.m_UpdateFlug = true; } };
	void SetUV(XMFLOAT2   uv, XMFLOAT2   UV) { if (m_Object != nullptr) { m_Object->m_Texdata.m_UV_uv = uv; m_Object->m_Texdata.m_UV_UV = UV;  m_Object->m_Texdata.m_UpdateFlug = true; } };
	void SetRotation(float rotation) { if (m_Object != nullptr) { m_Object->m_Texdata.m_Rotation = rotation;  m_Object->m_Texdata.m_UpdateFlug = true; } };
	void SetTex(int tex) { if (m_Object != nullptr) { m_Object->m_Texdata.m_Tex = tex; } };
	void SetDrawFlug(bool flug) { if (m_Object != nullptr) { m_Object->m_Texdata.m_DrawFlug = flug; } };
	void SetDepth(float Depth) { if (m_Object != nullptr) { m_Object->m_Depth = Depth; }; }
	void SetActive(bool active) { if (m_Object != nullptr) { m_Object->m_Active = active; }; };
	UI_Tex* GetObjectData() { return m_Object; };
	UITexData GetUITexData() { return m_Texdata; }
};


