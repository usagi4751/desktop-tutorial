//=============================================================================
//
//�����Ǘ����� [attribute_management.h]
// Author : 
//
//=============================================================================
#ifndef _ATTRIBUTE_MANAGEMENT_H_
#define _ATTRIBUTE_MANAGEMENT_H_
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_attribute.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Attribute_Management {
private:
public:
	Base_Attribute* Create(Attribute_Element att_element,Attribute_Type att_type,Base_Object* pObj);
};

#endif // !_ATTRIBUTE_MANAGEMENT_H_