//=============================================================================
//
// �������� [base_attribute.cpp]
// Author : 
//
//=============================================================================
#include "base_attribute.h"
#include "base_object.h"

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Base_Attribute::Base_Attribute(Attribute_Element element)
	:m_Element(element)
{
}
//==========================================================
// �^�C�v�ʑ����U�蕪��
//==========================================================
void Base_Attribute::AttributeByType(Base_Object* pObj)
{
	if (pObj->RefObjType() == character)ToCharacter(pObj);
	if (pObj->RefObjType() == ground)ToGround(pObj);
	if (pObj->RefObjType() == destructible)ToDestructible(pObj);
}
//==========================================================
// �����̍\���v�f�Q��
//==========================================================
const Attribute_Element& Base_Attribute::RefElement(void) const
{
	return m_Element;
}
//==========================================================
// �o�߃t���[��
//==========================================================
void Base_Attribute::ReduceFrame(int frame)
{
	m_Element.m_Frame -= frame;
}
