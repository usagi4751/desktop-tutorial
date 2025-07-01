//=============================================================================
//
// �������� [water_attribute.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "water_attribute.h"
#include "base_character.h"
#include "Game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Water_Attribute::Water_Attribute(Attribute_Element element)
	:Base_Attribute(element)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Water_Attribute::~Water_Attribute()
{
}
//=============================================================================
// �L�����N�^�[�ɑ΂��Ă̑������ʏ���
//=============================================================================
void Water_Attribute::ToCharacter(Base_Object* pObj)
{
	//�_�E���L���X�g(���S����ۂ��߃_�C�i�~�b�N�L���X�g)
	Base_Character* pBc = dynamic_cast<Base_Character*>(pObj);
	if (pBc == nullptr)
		return;

	//���X�̑��x�x�N�g���̕ۑ��ƃX���[���ʂ̕t�^
	if (m_Once)
	{
		m_OldVel = pBc->RefVel();
		pBc->SetVel(pBc->RefVel() * pBc->GetAttribute(water)->RefElement().m_Value);
		m_Once = false;
	}
	if (!(pBc->GetAttribute(water)->RefElement().m_Frame % 10) )
	{
		Emitta(4, { pBc->RefPos().x,pBc->RefPos().y + 100.0f,pBc->RefPos().z });
	}
	//�o�߃t���[������
	pBc->GetAttribute(water)->ReduceFrame(1);

	//�K��t���[���o������폜
	if (pBc->GetAttribute(water)->RefElement().m_Frame <= 0)
	{
		pBc->SetVel(m_OldVel);
		delete pBc->GetAttribute(water);
		pBc->SetAttribute(nullptr, water);
	}
}
//=============================================================================
// �n�ʂɑ΂��Ă̑������ʏ���
//=============================================================================
void Water_Attribute::ToGround(Base_Object* pObj)
{
}
//=============================================================================
// �j��\�I�u�W�F�N�g�ɑ΂��Ă̑������ʏ���
//=============================================================================
void Water_Attribute::ToDestructible(Base_Object* pObj)
{
}
