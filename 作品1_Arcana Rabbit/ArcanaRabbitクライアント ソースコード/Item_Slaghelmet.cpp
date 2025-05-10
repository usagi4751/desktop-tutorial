#include "Item_Slaghelmet.h"
#include "item.h"
#include "material.h"
void Item_SlagHelmet::Attack(Item itemData)
{

}

void Item_SlagHelmet::Use(Item* itemData)
{

}



void Item_SlagHelmet::GetItemName(Item itemData, std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription)
{
	*itemname = "がらくた帽子";
	*itemdescription = "ダメージを少し減らしてくれる帽子\n\n" + NomalStatus(itemData);


}


SetSlot Item_SlagHelmet::GetSlot()
{
	return Head;
}

int Item_SlagHelmet::GetIcon()
{
	return GetImage().m_ItemTex_SlagHelmet;
}
