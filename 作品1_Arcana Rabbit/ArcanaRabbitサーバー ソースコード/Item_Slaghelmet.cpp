#include "Item_Slaghelmet.h"
#include "item.h"
#include "material.h"
void Item_SlagHelmet::Attack(Item itemData)
{

}

void Item_SlagHelmet::Use(Item* itemData)
{

}

void Item_SlagHelmet::Draw(Item itemData)
{
	
	NomalDrawText("���炭���X�q", "�_���[�W���������炵�Ă����X�q\n\n" + NomalStatus(itemData));
}

void Item_SlagHelmet::DrawIcon(XMFLOAT2 pos, float size, float Depth, Item itemData)
{
	//Draw2d::SetUI(GetImage().m_ItemTex_SlagHelmet, { 1.0f,1.0f ,1.0f ,1.0f }, pos, { size ,size }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth);
}

SetSlot Item_SlagHelmet::GetSlot()
{
	return Head;
}
