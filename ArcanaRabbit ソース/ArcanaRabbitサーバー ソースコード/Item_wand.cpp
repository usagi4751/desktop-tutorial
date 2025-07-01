#include "Item_wand.h"
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
void Item_Wand::Attack(Item itemData)
{

	std::list<Enemy*> enemylist= Manager::GetScene()->GetEntitylist<Enemy>();
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
		if (len < powf(player->GetNomalAttackRange(), 2))
		{
			e->AddDamage(Inventory::GetStayus().Damage);
		}
		
	}

}

void Item_Wand::Use(Item* itemData)
{
	if (DictionarySkill::GetSkill(itemData->m_skillNo) != nullptr)
	{
		DictionarySkill::GetSkill(itemData->m_skillNo)->Use();
		itemData->m_skillCD = DictionarySkill::GetSkill(itemData->m_skillNo)->CD();
	}

}

void Item_Wand::Draw(Item itemData)
{
	NomalDrawText("…»‚Ìñ", "æ’[‚É…»‚ª‚Â‚¢‚Ä‚¢‚éñ\n\n"  + NomalStatus(itemData));
	if (DictionarySkill::GetSkill(itemData.m_skillNo) != nullptr)
	{
		DictionarySkill::GetSkill(itemData.m_skillNo)->Draw();
	}
}

void Item_Wand::DrawIcon(XMFLOAT2 pos, float size, float Depth, Item itemData)
{
	float coler = 1.0f;
	if (itemData.m_skillCD > 0)
	{
		coler = 0.6f;
	}
	//Draw2d::SetUI(GetImage().m_ItemTex_wand, { coler,coler ,coler ,1.0f }, pos, { size ,size }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth);
}

Status Item_Wand::GetStatus(Item itemData)
{
	Status status;
	status.MaxHelth = itemData.m_maxhelth;
	status.AttackSpeed = itemData.m_attackspeed;
	status.Damage = itemData.m_damage;
	status.MoveSpeed = itemData.movespeed;
	status.Def = itemData.m_def;
	return status;
}
