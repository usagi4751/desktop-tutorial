#include "Item_SlaghChest.h"
#include "item.h"
#include "material.h"
void Item_SlagChest::Attack(Item itemData)
{

}

void Item_SlagChest::Use(Item* itemData)
{

}

void Item_SlagChest::Draw(Item itemData)
{

	NomalDrawText("���炭����", "�_���[�W���������炵�Ă���镞\n\n" + NomalStatus(itemData));
}

void Item_SlagChest::DrawIcon(XMFLOAT2 pos, float size, float Depth, Item itemData)
{
	//Draw2d::SetUI(GetImage().m_ItemTex_SlagChest, { 1.0f,1.0f ,1.0f ,1.0f }, pos, { size ,size }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth);
}

SetSlot Item_SlagChest::GetSlot()
{
	return Chest;
}
