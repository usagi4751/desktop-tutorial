#pragma once
#include "ItemDataBase.h"
class Item_SlagChest : public ItemDataBase
{
private:

public:
	Item_SlagChest() { m_maxStack = 1; };
	~Item_SlagChest() {};
	virtual void Attack(Item itemData);
	virtual void Use(Item* itemData);
	virtual void Draw(Item itemData);
	virtual void DrawIcon(XMFLOAT2 pos, float size, float Depth, Item itemData);
	virtual SetSlot GetSlot();
};

