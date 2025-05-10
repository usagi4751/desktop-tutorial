#pragma once
#include "main.h"
#include "draw2d_Manager.h"
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
private:

protected:
	int m_maxStack = 1;//最大スタック数
public:
	ItemDataBase() {};
	virtual ~ItemDataBase() {  };

	virtual void Attack(Item itemData) = 0;
	virtual void Use(Item* itemData) = 0;
	virtual int GetIcon() = 0;
	virtual void GetItemName(Item itemData,std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription) = 0;

	virtual SetSlot GetSlot() { return None; };
	void TextBackground();//テキストのバックグラウンド
	void NomalDrawText(std::string itemname, std::string itemdescription);//通常の描画
	virtual std::string NomalStatus(Item itemData);
	virtual int GetMaxStack() { return m_maxStack; };//戻り値最大スタック数
	virtual Status GetStatus(Item itemData);
};

