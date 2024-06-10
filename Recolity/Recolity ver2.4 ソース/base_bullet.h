//=============================================================================
//
// �e���� [base_bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BASE_BULLET_H_
#define _BASE_BULLET_H_
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "model.h"
#include "base_object.h"
#include "base_attribute.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NO_DEC	(1.0f)
#define NO_GVT	(0.0f)

//*****************************************************************************
// �񋓑̐錾
//*****************************************************************************
enum Bullet_Type {	//�e�̎��
	bullet,
	life_penetration,
	cannon,
	hook,
	time_bom,
};
enum Bullet_Side {	//�e���������L�����N�^�[
	player,
	enemy,
};

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Base_Bullet: public Base_Object
{
private:
	Bullet_Type			m_Type;		//�ǂ�Ȓe��
	Bullet_Side			m_Side;		//�N�������Ă��邩
	int					m_Damage;	//�_���[�W��
	float				m_Speed;	//�ړ���
	float				m_Gvt;		//�d��
	float				m_Dec;		//�����W��
	int					m_Range;	//�˒�����
	D3DXVECTOR2			m_Uv_v;
	D3DXVECTOR2			m_Uv_f;
	Attribute_Element	m_AttElement;
	int*				m_TexId;	//�e�N�X�`��ID
	DX11_MODEL*			m_ModelId;	//���f��ID
protected:
	bool				m_Penetration;
public:
	Base_Bullet() = delete;
	Base_Bullet(
		D3DXVECTOR3 pos,
		D3DXVECTOR3 rot,
		D3DXVECTOR3 scl,
		D3DXVECTOR3 vel,
		D3DXCOLOR color,
		bool use,
		Bullet_Type type,
		Bullet_Side side,
		int damage,
		float speed,
		float gvt,
		float dec,
		int range,
		D3DXVECTOR2 uv_v,
		D3DXVECTOR2 uv_f,
		Attribute_Type att_type,
		Attribute_Element att_element,
		int* tex,
		DX11_MODEL* model
		);

	virtual ~Base_Bullet() = default;

	//�Q�b�^�[
	DX11_MODEL* GetModelId(void);

	//���t�@�����X
	const Bullet_Type&	RefType(void) const;
	const Bullet_Side&	RefSide(void) const;
	const int& RefDamage(void) const;
	const float& RefSpeed(void) const;
	const float& RefGvt(void) const;
	const float& RefDec(void) const;
	const int& RefRange(void) const;
	const D3DXVECTOR2& RefUv_v(void) const;
	const D3DXVECTOR2& RefUv_f(void) const;
	const Attribute_Element& RefElemet(void) const;
	const int& RefTexId(void) const;
	//�Z�b�^�[
	void SetType(Bullet_Type type);
	void SetSide(Bullet_Side side);
	void SetDamage(int damage);
	void SetSpeed(float speed);
	void SetGvt(float gvt);
	void SetDec(float dec);
	void SetRange(int range);
	void SetUv_v(D3DXVECTOR2 uv_v);
	void SetUv_f(D3DXVECTOR2 uv_f);

	virtual void Move(void) = 0;
	void IsDiscard() override;
};


#endif // !_BASE_BULLET_H_