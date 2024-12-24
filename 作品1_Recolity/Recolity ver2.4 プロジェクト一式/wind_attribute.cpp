//=============================================================================
//
// �������� [wind_attribute.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "wind_attribute.h"
#include "base_character.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Wind_Attribute::Wind_Attribute(Attribute_Element element, float rot)
	:Base_Attribute(element), m_Rot(rot)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Wind_Attribute::~Wind_Attribute()
{
}
//=============================================================================
// �L�����N�^�[�ɑ΂��Ă̑������ʏ���
//=============================================================================
void Wind_Attribute::ToCharacter(Base_Object* pObj)
{
	//�_�E���L���X�g(���S����ۂ��߃_�C�i�~�b�N�L���X�g)
	Base_Character* pBc = dynamic_cast<Base_Character*>(pObj);
	if (pBc == nullptr)
		return;

	//�X�^�b�N����
	if (!pBc->RefStuck())
	{
		pBc->SetStuck(true);
	}

	//���W�̍X�V
	pBc->SetPos({
		pBc->RefPos().x + pBc->GetAttribute(wind)->RefElement().m_Value * sinf(m_Rot),
		pBc->RefPos().y,
		pBc->RefPos().z + pBc->GetAttribute(wind)->RefElement().m_Value * cosf(m_Rot),
		}
	);

	//�o�߃t���[������
	pBc->GetAttribute(wind)->ReduceFrame(1);

	//�K��t���[���o������폜
	if (pBc->GetAttribute(wind)->RefElement().m_Frame <= 1)
	{
		pBc->SetStuck(false);
		delete pBc->GetAttribute(wind);
		pBc->SetAttribute(nullptr, wind);
	}
}
//=============================================================================
// �n�ʂɑ΂��Ă̑������ʏ���
//=============================================================================
void Wind_Attribute::ToGround(Base_Object* pObj)
{
}
//=============================================================================
// �j��\�I�u�W�F�N�g�ɑ΂��Ă̑������ʏ���
//=============================================================================
void Wind_Attribute::ToDestructible(Base_Object* pObj)
{
}
