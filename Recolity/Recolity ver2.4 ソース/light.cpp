//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "light.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Light::Light()
{
	m_LightArray.reserve(LIGHT_NUM);
	// ���s�����̐ݒ�i���E���Ƃ炷���j
	LIGHT light;
	light.Type = LIGHT_TYPE_DIRECTIONAL;						// ���s����
	light.Direction = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f);	// ���̌���
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ���̐F
	light.Ambient = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);		// ���̐F
	light.Enable = true;
	m_LightArray.push_back(light);

	for (int index = 0; index < m_LightArray.size(); index++)
	{
		SetLight(index, &m_LightArray[index]);
	}
}

Light::~Light()
{
	return;
}

