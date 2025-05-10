#pragma once
#include "ItemDataBase.h"
class Item_SlagSword : public ItemDataBase
{
private:
public:
	Item_SlagSword();
	~Item_SlagSword() {};
	virtual void Attack(Item itemData);
	virtual void Use(Item* itemData);
	virtual void GetItemName(Item itemData, std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription);
	virtual Status GetStatus(Item itemData) override;

	virtual int GetIcon() override;
};

