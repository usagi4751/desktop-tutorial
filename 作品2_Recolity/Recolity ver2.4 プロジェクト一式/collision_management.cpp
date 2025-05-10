//=============================================================================
//
// �����蔻��Ǘ����� [collision_management.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "collision_management.h"
#include "Game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Collision_Management::Collision_Management(std::list<Base_Enemy*>* enemey_list, std::list<Base_Bullet*>* bullet_list, Attribute_Management* att_manager)
	:m_EnemyList(enemey_list),m_BulletList(bullet_list),m_AttributeManagement(att_manager)
{
}
//=============================================================================
// �X�V
//=============================================================================
void Collision_Management::Update(void)
{
	//�G�ƒe�̓����蔻��
	for (Base_Bullet* pBullet : *m_BulletList)
	{
		//�g���Ă��Ȃ��e��������
		if (!pBullet->RefUse())
			continue;

		if (pBullet->RefSide() != enemy) {
			for (Base_Enemy* pEnemy : *m_EnemyList)
			{
				//�G�ɂ��Ă��铖���蔻��̐���
				for (int index = 0; index < pEnemy->GetColl()->size(); index++)
				{
					Collision* pColl = pEnemy->GetColl(index);
					//�e�ɂ��Ă��铖���蔻��̐���
					if (pBullet->GetColl(0) != nullptr && pBullet->GetColl(0)->IsCollision(pColl))
					{
						//�_���[�W����
						pEnemy->IsDamage(pBullet->RefDamage());
						//�����̕t�^
						if (pEnemy->GetAttribute(pBullet->RefAttType()) == nullptr)
						{
							pEnemy->SetAttribute(m_AttributeManagement->Create(pBullet->RefElemet(), pBullet->RefAttType(), pBullet), pBullet->RefAttType());
						}
						pBullet->IsDiscard();
					}
				}
			}
		}
		else {
			//�v���C���[�ɂ��Ă��铖���蔻��̐���
			for (int index = 0; index < GetPlayer()->GetColl()->size(); index++)
			{
				Collision* pColl = GetPlayer()->GetColl(index);
				//�e�ɂ��Ă��铖���蔻��̐���
				if (pBullet->GetColl(0) != nullptr && pBullet->GetColl(0)->IsCollision(pColl))
				{
					//�_���[�W����
					GetPlayer()->IsDamage(pBullet->RefDamage());
					GetPlayer()->SetAttribute(m_AttributeManagement->Create(pBullet->RefElemet(), pBullet->RefAttType(), pBullet), pBullet->RefAttType());
					if (pBullet->RefAttType() == water) {
						GetPlayer()->effect.SetEffect(slowness, low, pBullet->RefElemet().m_Frame);
					}
					pBullet->IsDiscard();
				}
			}
		}
	}
	//�G�l�~�[���m�̏Փ�
	for (Base_Enemy* pEnemy : *m_EnemyList)
	{
		for (Base_Enemy* pAnother : *m_EnemyList)
		{
			//�������g�̉��
			if (pAnother == pEnemy)
				continue;

			D3DXVECTOR2 vec = { pEnemy->RefPos().x - pAnother->RefPos().x,pEnemy->RefPos().z - pAnother->RefPos().z };
			float angle = atan2f(vec.y, vec.x);
			float lenght = D3DXVec2LengthSq(&vec);
			float speed = 3.0f;
			if (lenght <= 100.0f * 100.0f) {
				pEnemy->SetPos({ pEnemy->RefPos().x + speed * cosf(angle),pEnemy->RefPos().y,pEnemy->RefPos().z + speed * sinf(angle) });
				angle += D3DX_PI;
				pAnother->SetPos({ pAnother->RefPos().x + speed * cosf(angle),pAnother->RefPos().y,pAnother->RefPos().z + speed * sinf(angle) });
			}
		}
	}
}


