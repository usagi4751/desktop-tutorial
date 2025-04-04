#pragma once
#pragma once
#include "ItemDataBase.h"
class Item_Wand : public ItemDataBase
{
private:

public:
	Item_Wand() { m_maxStack = 1; };
	~Item_Wand() {};
	virtual void Attack(Item itemData);
	virtual void Use(Item* itemData);
	virtual void Draw(Item itemData);
	virtual void DrawIcon(XMFLOAT2 pos, float size, float Depth, Item itemData) ;
	virtual Status GetStatus(Item itemData) override;
};

