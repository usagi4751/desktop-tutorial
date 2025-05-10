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
	virtual int GetIcon() override ;
	virtual void GetItemName(Item itemData, std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription);
	virtual Status GetStatus(Item itemData) override;
};

