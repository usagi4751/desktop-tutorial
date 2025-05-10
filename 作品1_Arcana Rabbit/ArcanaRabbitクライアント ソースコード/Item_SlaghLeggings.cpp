#include "Item_SlaghLeggings.h"
#include "item.h"
#include "material.h"
void Item_SlagLeggings::Attack(Item itemData)
{

}

void Item_SlagLeggings::Use(Item* itemData)
{
	//なし
}


void Item_SlagLeggings::GetItemName(Item itemData, std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription)
{
	*itemname = "がらくたズボン";
	*itemdescription = "ダメージを少し減らしてくれるズボン\n\n" + NomalStatus(itemData);


}

SetSlot Item_SlagLeggings::GetSlot()
{
	return LEGGINGS;
}

int Item_SlagLeggings::GetIcon()
{
	return GetImage().m_ItemTex_Slagwaistband;
}
