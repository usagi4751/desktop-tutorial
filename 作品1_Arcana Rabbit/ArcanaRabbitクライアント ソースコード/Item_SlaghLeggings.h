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
	virtual void GetItemName(Item itemData, std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription);
	virtual SetSlot GetSlot();

	virtual int GetIcon() override;
};


