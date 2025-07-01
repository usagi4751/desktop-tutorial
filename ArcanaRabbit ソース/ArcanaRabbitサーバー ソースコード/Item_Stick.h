#pragma once
#include "ItemDataBase.h"
class Item_Stick : public ItemDataBase
{
private:

public:
	Item_Stick() { m_maxStack = 64; };
	~Item_Stick() {};
	virtual void Attack(Item itemData) ;
	virtual void Use(Item* itemData);
	virtual void Draw(Item itemData) ;
	virtual void DrawIcon(XMFLOAT2 pos, float size, float Depth, Item itemData);
};

