#pragma once
#include "ItemDataBase.h"
class Item_SlagLeggings : public ItemDataBase
{
private:

public:
	Item_SlagLeggings() { m_maxStack = 1; };
	~Item_SlagLeggings() {};
	virtual void Attack(Item itemData);
	virtual void Use(Item* itemData);
	virtual void Draw(Item itemData);
	virtual void DrawIcon(XMFLOAT2 pos, float size, float Depth, Item itemData);
	virtual SetSlot GetSlot();
};


