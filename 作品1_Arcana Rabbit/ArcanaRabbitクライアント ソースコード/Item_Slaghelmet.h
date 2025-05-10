#pragma once
#pragma once
#include "ItemDataBase.h"
class Item_SlagHelmet : public ItemDataBase
{
private:

public:
	Item_SlagHelmet() { m_maxStack = 1; };
	~Item_SlagHelmet() {};
	virtual void Attack(Item itemData);
	virtual void Use(Item* itemData);
	virtual void GetItemName(Item itemData, std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription);
	virtual SetSlot GetSlot();

	virtual int GetIcon() override;
};

