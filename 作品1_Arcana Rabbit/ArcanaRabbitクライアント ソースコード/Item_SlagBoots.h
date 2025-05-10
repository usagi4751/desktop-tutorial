#pragma once
#include "ItemDataBase.h"
class Item_SlagBoots : public ItemDataBase
{
private:

public:
	Item_SlagBoots() { m_maxStack = 1; };
	~Item_SlagBoots() {};
	virtual void Attack(Item itemData);
	virtual void Use(Item* itemData);
	virtual SetSlot GetSlot();
	virtual void GetItemName(Item itemData, std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription);

	virtual int GetIcon() override;
};

