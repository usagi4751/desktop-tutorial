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
	virtual void GetItemName(Item itemData, std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription);
	virtual int GetIcon() override;
};

