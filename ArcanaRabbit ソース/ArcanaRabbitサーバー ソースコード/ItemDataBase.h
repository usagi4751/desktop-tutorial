#pragma once
#include "main.h"
//アイテム固有の表示方法や効果を表す

//装備をつけられる位置
enum SetSlot
{
	None = 0,
	Head,
	Chest,
	LEGGINGS,
	BOOTS,
};
class Item;
struct Status;
class ItemDataBase
{
protected:
	int m_maxStack = 1;//最大スタック数
public:
	ItemDataBase() { };
	virtual ~ItemDataBase() {  };

	virtual void Attack(Item itemData) = 0;
	virtual void Use(Item* itemData) = 0;
	virtual void Draw(Item itemData) = 0;
	virtual void DrawIcon(XMFLOAT2 pos, float size, float Depth, Item itemData) = 0;
	virtual SetSlot GetSlot() { return None; };
	void TextBackground();//テキストのバックグラウンド
	void NomalDrawText(std::string itemname, std::string itemdescription);//通常の描画
	virtual std::string NomalStatus(Item itemData);
	virtual int GetMaxStack() { return m_maxStack; };//戻り値最大スタック数
	virtual Status GetStatus(Item itemData);
};

