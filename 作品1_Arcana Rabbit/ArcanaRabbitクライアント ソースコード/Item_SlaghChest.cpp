#include "Item_SlaghChest.h"
#include "item.h"
#include "material.h"
void Item_SlagChest::Attack(Item itemData)
{

}

void Item_SlagChest::Use(Item* itemData)
{

}


void Item_SlagChest::GetItemName(Item itemData, std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription)
{
	*itemname = "‚ª‚ç‚­‚½•";
	*itemdescription = "ƒ_ƒ[ƒW‚ğ­‚µŒ¸‚ç‚µ‚Ä‚­‚ê‚é•\n\n" + NomalStatus(itemData);
}

SetSlot Item_SlagChest::GetSlot()
{
	return Chest;
}

int Item_SlagChest::GetIcon()
{
	return GetImage().m_ItemTex_SlagChest;
}
