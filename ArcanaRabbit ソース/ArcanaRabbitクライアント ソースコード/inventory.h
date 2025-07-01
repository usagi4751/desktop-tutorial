#pragma once
#include "main.h"
#include <list>
#include "draw2d_Manager.h"
//===============================
// プレイヤーのインベントリのクラス
// ステータスの計算もここでする
//===============================
struct Status
{
	float MaxHelth;
	float Damage;
	float MoveSpeed;
	float AttackSpeed;
	float Def;
};
//スキルの描画用
struct ItemSkillDraw {
	UI_Tex		m_ItemBg;
	UI_Text		m_ItemTextName;
	UI_Text		m_ItemTextdescription;

	UI_Tex		m_SkillBg;
	UI_Text		m_SkillTextName;
	UI_Text		m_SkillTextdescription;
};
class Item;
class Inventory
{
private:
	//=======================
	// インベントリ0-31 32枠
	// 装備 32-35 4枠
	//=======================
	static Item m_itemlist[36];
	static Item m_hand;//カーソルでつまんでるアイテム
	static bool m_openflug;//インベントリが空いているか
	static float m_posY;
	static float m_size;
	static int m_haveitem;//持ってる所のナンバー

	//マウスが重なっているアイテムスロット番号
	static int Getitemno(XMFLOAT2 mousepos);

	//描画用
	static bool m_ShowUI;

	static UI_Tex m_HotBerCell[8];
	static UI_Tex m_Cell[36];
	static UI_Tex m_Bg;
	static UI_Tex m_Celect;
	static UI_Tex m_SkillText;
	static UI_Tex m_CellOnMouse;
	static UI_Tex m_Hand;

	static UI_Tex m_HotBerCellItem[8];
	static UI_Tex m_CellItem[36];

	static ItemSkillDraw m_ItemTextDraw;
public:
	//初期化
	static void Init();
	//更新
	static void Update();
	//描画
	static void DrawRect();

	//現在持っているアイテムスロット番号
	static void SetHaveItem(int hand) {m_haveitem = hand;};
	//インベントリの大きさ
	static void SetScale(float size) { m_size = size; };
	//インベントリの高さ
	static void SetYpos(float posy) { m_posY = posy; };
	//インベントリのステータスの合計値
	static Status GetStayus();


	//================================
	//プレイヤーの使用するコマンド
	//================================

	//アイテムで攻撃
	static void Attack();
	//アイテムの使用
	static void Use();
	//アイテムの取得
	static void Getitem(Item getitem) ;
	//インベントリのオープンクローズ
	static void SetOpen(bool flug) { m_openflug = flug; };


	//================================
	// 読み込みやムービー時にインベントリのロックを掛ける機能
	//================================

	//インベントリが操作可能か
	static void ShowUI(bool flug);
};


