#include "Item_SlagBoots.h"
#include "item.h"
#include "material.h"
void Item_SlagBoots::Attack(Item itemData)
{

}

void Item_SlagBoots::Use(Item* itemData)
{

}


void Item_SlagBoots::GetItemName(Item itemData, std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription)
{
	*itemname = "がらくた靴";
	*itemdescription = "ダメージを少し減らしてくれる靴\n\n" + NomalStatus(itemData);
}

SetSlot Item_SlagBoots::GetSlot()
{
	return BOOTS;
}

int Item_SlagBoots::GetIcon()
{
	return GetImage().m_ItemTex_SlagBoots;
}
