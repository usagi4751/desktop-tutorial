#include "DictionaryItem.h"
#include "ItemDataBase.h"
#include "Item_Stick.h"
#include "Item_wand.h"
#include "Item_Slaghelmet.h"
#include "Item_SlaghChest.h"
#include "Item_SlaghLeggings.h"
#include "Item_SlagBoots.h"
#include "Item_SlagSword.h"
std::vector<ItemDataBase*> DictionaryItem::m_Itemlist{};


void DictionaryItem::UnInit()
{
	for (ItemDataBase* b : m_Itemlist)
	{
		delete b;
	}
	m_Itemlist.clear();
}

void DictionaryItem::Init()
{
	m_Itemlist.push_back(new Item_Stick);
	m_Itemlist.push_back(new Item_Wand);
	m_Itemlist.push_back(new Item_SlagHelmet);
	m_Itemlist.push_back(new Item_SlagChest);
	m_Itemlist.push_back(new Item_SlagLeggings);
	m_Itemlist.push_back(new Item_SlagBoots);
	m_Itemlist.push_back(new Item_SlagSword);
}
