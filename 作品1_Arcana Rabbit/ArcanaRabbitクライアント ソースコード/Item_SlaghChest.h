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
	virtual void GetItemName(Item itemData, std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription);
	virtual SetSlot GetSlot();

	virtual int GetIcon() override;
};

