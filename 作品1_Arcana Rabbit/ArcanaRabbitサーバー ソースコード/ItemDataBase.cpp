#include "ItemDataBase.h"
#include "material.h"
#include "item.h"
#include "inventory.h"
void ItemDataBase::TextBackground()
{
	//Draw2d::SetUI(GetImage().m_UI_image3, { 1.0f,1.0f ,1.0f ,1.0f }, { 270,365 }, { 450,550 }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, 0.5f);
}



void ItemDataBase::NomalDrawText(std::string itemname, std::string itemdescription)
{
	TextBackground();
	//Draw2d::SetText(itemname, { 55,140,490,190 }, 25, { 1.0f,1.0f,1.0f,1.0f }, 0.5f + 0.01f);
	//Draw2d::SetText(itemdescription, { 55,200,490,640 }, 15, { 1.0f,1.0f,1.0f,1.0f }, 0.5f + 0.01f);
}

std::string ItemDataBase::NomalStatus(Item itemData)
{
	std::string retunstring;
	if (itemData.m_damage > 0)retunstring += "ダメージ +" + std::to_string((int)itemData.m_damage) + "\n";
	if (itemData.m_maxhelth > 0)retunstring += "最大体力 +" + std::to_string((int)itemData.m_maxhelth) + "\n";
	if (itemData.movespeed > 0)retunstring += "移動速度 +" + std::to_string((int)itemData.movespeed) + "\n";
	if (itemData.m_def > 0)retunstring += "防御力 +" + std::to_string((int)itemData.m_def) + "\n";
	if (itemData.m_attackspeed > 0)retunstring += "攻撃速度 +" + std::to_string((int)itemData.m_attackspeed) + "\n";



	return retunstring;
}

Status ItemDataBase::GetStatus(Item itemData)
{
	return {};
}
