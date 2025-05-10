#pragma once
#include "ItemDataBase.h"
class Item_SlagSword : public ItemDataBase
{
private:

public:
	Item_SlagSword() { m_maxStack = 1; };
	~Item_SlagSword() {};
	virtual void Attack(Item itemData);
	virtual void Use(Item* itemData);
	virtual void Draw(Item itemData);
	virtual void DrawIcon(XMFLOAT2 pos, float size, float Depth, Item itemData);
	virtual Status GetStatus(Item itemData) override;
};

