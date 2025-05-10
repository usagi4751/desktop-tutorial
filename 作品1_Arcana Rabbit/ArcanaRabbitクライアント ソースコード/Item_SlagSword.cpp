#include "Item_SlagSword.h"
#include "main.h"
#include "item.h"
#include "DictionarySkill.h"
#include "SkilldataBase.h"
#include "material.h"
#include "manager.h"
#include "enemy.h"
#include "collision.h"
#include "gameObject.h"
#include "player.h"
#include "inventory.h"
Item_SlagSword::Item_SlagSword()
{
	m_maxStack = 1;
};
void Item_SlagSword::Attack(Item itemData)
{

	std::list<Enemy*> enemylist = Manager::GetScene()->GetEntitylist<Enemy>();
	Player* player = Manager::GetScene()->GetGameObject<Player>();
	XMFLOAT3 Playerpos = *player->GetPosition();
	Playerpos.y += 1.5f;
	XMFLOAT3 rook = player->PlayerRay();


	for (Enemy* e : enemylist) {

		XMFLOAT3 hitpoint = {};
		XMFLOAT3 posdistance;
		XMFLOAT3 enemypos = *e->GetPosition();
		float scale = e->GetHitboxrange();
		calcRaySphere(&Playerpos, rook.x, rook.y, rook.z, enemypos.x, enemypos.y, enemypos.z, scale, &hitpoint);
		posdistance = { hitpoint.x - Playerpos.x ,hitpoint.y - Playerpos.y ,hitpoint.z - Playerpos.z };
		float len = D3DXVec3LengthSq(&posdistance);
		if (len < 16)
		{
			e->AddDamage(Inventory::GetStayus().Damage);
		}

	}

}

void Item_SlagSword::Use(Item* itemData)
{
	if (DictionarySkill::GetSkill(itemData->m_skillNo) != nullptr)
	{
		DictionarySkill::GetSkill(itemData->m_skillNo)->Use();
		itemData->m_skillCD = DictionarySkill::GetSkill(itemData->m_skillNo)->CD();
	}

}


void Item_SlagSword::GetItemName(Item itemData, std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription)
{
	*itemname = "ƒKƒ‰ƒNƒ^Œ•";
	*itemdescription = "’[Þ‚Åì‚ç‚ê‚½Œ•\n\n" + NomalStatus(itemData);
	if (DictionarySkill::GetSkill(itemData.m_skillNo) != nullptr)
	{
		DictionarySkill::GetSkill(itemData.m_skillNo)->GetSkillTextData(skillname, skilldescription);
	}

}


Status Item_SlagSword::GetStatus(Item itemData)
{
	Status status;
	status.MaxHelth = itemData.m_maxhelth;
	status.AttackSpeed = itemData.m_attackspeed;
	status.Damage = itemData.m_damage;
	status.MoveSpeed = itemData.movespeed;
	status.Def = itemData.m_def;
	return status;
}

int Item_SlagSword::GetIcon()
{
	return GetImage().m_ItemTex_SlagSword;
}
