//=============================================================================
//
// �������� [fire_attribute.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "fire_attribute.h"
#include "base_character.h"
#include "Game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Fire_Attribute::Fire_Attribute(Attribute_Element element)
	:Base_Attribute(element)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Fire_Attribute::~Fire_Attribute()
{
}
//=============================================================================
// �L�����N�^�[�ɑ΂��Ă̑������ʏ���
//=============================================================================
void Fire_Attribute::ToCharacter(Base_Object* pObj)
{
	//�_�E���L���X�g(���S����ۂ��߃_�C�i�~�b�N�L���X�g)
	Base_Character* pBc = dynamic_cast<Base_Character*>(pObj);
	if (pBc == nullptr)
		return;

	//�C���^�[�o������
	if (!(pBc->GetAttribute(fire)->RefElement().m_Frame % pBc->GetAttribute(fire)->RefElement().m_Interval))
	{
		pBc->IsDamageDot(pBc->GetAttribute(fire)->RefElement().m_Value);
		Emitta(3, { pBc ->RefPos().x,pBc->RefPos().y + 100.0f,pBc->RefPos().z});
	}

	//�o�߃t���[������
	pBc->GetAttribute(fire)->ReduceFrame(1);

	//�K��t���[���o������폜
	if (pBc->GetAttribute(fire)->RefElement().m_Frame <= 0)
	{
		delete pBc->GetAttribute(fire);
		pBc->SetAttribute(nullptr, fire);
	}
}
//=============================================================================
// �n�ʂɑ΂��Ă̑������ʏ���
//=============================================================================
void Fire_Attribute::ToGround(Base_Object* pObj)
{
}
//=============================================================================
// �j��\�I�u�W�F�N�g�ɑ΂��Ă̑������ʏ���
//=============================================================================
void Fire_Attribute::ToDestructible(Base_Object* pObj)
{
}
