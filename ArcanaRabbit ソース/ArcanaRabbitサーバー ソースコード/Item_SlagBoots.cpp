#include "Item_SlagBoots.h"
#include "item.h"
#include "material.h"
void Item_SlagBoots::Attack(Item itemData)
{

}

void Item_SlagBoots::Use(Item* itemData)
{

}

void Item_SlagBoots::Draw(Item itemData)
{

	NomalDrawText("Ç™ÇÁÇ≠ÇΩåC", "É_ÉÅÅ[ÉWÇè≠Çµå∏ÇÁÇµÇƒÇ≠ÇÍÇÈåC\n\n" + NomalStatus(itemData));
}

void Item_SlagBoots::DrawIcon(XMFLOAT2 pos, float size, float Depth, Item itemData)
{
	//Draw2d::SetUI(GetImage().m_ItemTex_SlagBoots, { 1.0f,1.0f ,1.0f ,1.0f }, pos, { size ,size }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth);
}

SetSlot Item_SlagBoots::GetSlot()
{
	return BOOTS;
}
