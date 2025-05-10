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

void Item_SlagLeggings::Draw(Item itemData)
{

	NomalDrawText("がらくたズボン", "ダメージを少し減らしてくれるズボン\n\n" + NomalStatus(itemData));
}

void Item_SlagLeggings::DrawIcon(XMFLOAT2 pos, float size, float Depth, Item itemData)
{
	//Draw2d::SetUI(GetImage().m_ItemTex_Slagwaistband, { 1.0f,1.0f ,1.0f ,1.0f }, pos, { size ,size }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth);
}

SetSlot Item_SlagLeggings::GetSlot()
{
	return LEGGINGS;
}
