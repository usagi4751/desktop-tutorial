#include "Item_Stick.h"
#include "item.h"
#include "material.h"
#include "inventory.h"
#include "SkilldataBase.h"
#include "manager.h"
#include "enemy.h"
#include "collision.h"
#include "gameObject.h"
#include "player.h"
void Item_Stick::Attack(Item itemData)
{
	//1�_���[�W�^����
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
		if (len < powf(player->GetNomalAttackRange(),2))
		{
			e->AddDamage(1);
		}

	}
}

void Item_Stick::Use(Item* itemData)
{
	//�Ȃ�
}

void Item_Stick::Draw(Item itemData)
{
	//���O�̂ݏo��
	NomalDrawText("�_","�l�X�ȃN���t�g�Ɏg���A�C�e��");
}

void Item_Stick::DrawIcon(XMFLOAT2 pos, float size, float Depth, Item itemData)
{
	//Draw2d::SetUI(GetImage().m_ItemTex_Stick, {1.0f,1.0f ,1.0f ,1.0f }, pos, { size ,size }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth);
}


