//=============================================================================
//
// �e�Ǘ����� [bullet_management.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "model.h"
#include "texture.h"
#include "bullet_management.h"
#include "normal_bullet.h"
#include "normal_bullet_life_penetration.h"
#include "hook_bullet.h"
#include "cannon_bullet.h"
#include "time_bom.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// ����������
//=============================================================================
HRESULT Bullet_Management::Init(void)
{

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Bullet_Management::Uninit(void)
{
	for (Base_Bullet* pBullet : m_BulletList)
	{
		delete pBullet;
	}
	m_BulletList.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void Bullet_Management::Update(void)
{
	//�폜
	Delete();

	//�X�V
	for (Base_Bullet* pBullet:m_BulletList)
	{
		pBullet->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Bullet_Management::Draw(void)
{
	//�`��
	for (Base_Bullet* pBullet : m_BulletList)
	{
		pBullet->Draw();
	}
}

//=============================================================================
// ����
//=============================================================================
void Bullet_Management::Create(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vec, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex, DX11_MODEL* model, float circle)
{
	if (type == bullet)
	{
		m_BulletList.push_back(new Normal_Bullet(
			pos,
			rot,
			scl,
			vec,
			color,
			true,
			side,
			damage,
			speed,
			gvt,
			dec,
			range,
			uv_v,
			uv_f,
			att_type,
			att_element,
			tex,
			model,
			circle)
		);
	}
	if (type == hook)
	{
		m_BulletList.push_back(new Hook_Bullet(
			pos,
			rot,
			scl,
			vec,
			color,
			true,
			side,
			damage,
			speed,
			gvt,
			dec,
			range,
			uv_v,
			uv_f,
			att_type,
			att_element,
			tex,
			model,
			circle)
		);
	}
	if (type == time_bom)
	{
		m_BulletList.push_back(new Time_bom_Bullet(
			pos,
			rot,
			scl,
			vec,
			color,
			true,
			side,
			damage,
			speed,
			gvt,
			dec,
			range,
			uv_v,
			uv_f,
			att_type,
			att_element,
			tex,
			model,
			circle)
		);
	}
	if (type == life_penetration)
	{
		m_BulletList.push_back(new Normal_Bullet_Life_Penetration(
			pos,
			rot,
			scl,
			vec,
			1,
			color,
			true,
			side,
			damage,
			speed,
			gvt,
			dec,
			range,
			uv_v,
			uv_f,
			att_type,
			att_element,
			tex,
			model,
			circle)
		);
	}

}
void Bullet_Management::Create(Bullet_Interface* bif, Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vec, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex, DX11_MODEL* model, float circle)
{

	if (type == cannon)
	{
		m_BulletList.push_back(new Cannon_Bullet(
			bif,
			pos,
			des,
			rot,
			scl,
			vec,
			color,
			true,
			side,
			damage,
			speed,
			gvt,
			uv_v,
			uv_f,
			att_type,
			att_element,
			tex,
			model,
			circle)
		);
	}
}

//=============================================================================
// �폜
//=============================================================================
void Bullet_Management::Delete()
{
	m_BulletList.remove_if([](Base_Bullet* pBullet) {
		if (!pBullet->RefUse()) {
			delete pBullet;
			return true;
		}
		return false; }
	);
}
//=============================================================================
// �o���b�g���X�g�Q�b�^�[
//=============================================================================
std::list<Base_Bullet*>* Bullet_Management::GetBulletList(void)
{
	return &m_BulletList;
}