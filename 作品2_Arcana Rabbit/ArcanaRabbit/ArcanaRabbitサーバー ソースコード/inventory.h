#pragma once
#include "main.h"
#include <list>
struct Status
{
	float MaxHelth;
	float Damage;
	float MoveSpeed;
	float AttackSpeed;
	float Def;
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
	static bool m_openflug;
	static float m_posY;
	static float m_size;
	static int m_haveitem;//持ってる所のナンバー
	static int Getitemno(XMFLOAT2 mousepos);
public:
	static void Init();
	static void Update();
	static void DrawRect();
	static void SetHaveItem(int hand) {m_haveitem = hand;};
	static void SetOpen(bool flug) {m_openflug = flug;};
	static void SetScale(float size) { m_size = size; };
	static void SetYpos(float posy) { m_posY = posy; };
	static Status GetStayus();
	static void Attack();
	static void Use();
	static void Getitem(Item getitem) ;
};


