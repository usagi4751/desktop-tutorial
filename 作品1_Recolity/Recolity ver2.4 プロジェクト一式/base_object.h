//=============================================================================
//
// �I�u�W�F�N�g���� [base_object.h]
// Author : 
//
//=============================================================================
#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_
#pragma once

#include <d3dx9.h>
#include <iostream>
#include <list>
#include <vector>
#include "renderer.h"
#include "collision.h"
#include "model.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class Base_Attribute;
enum Attribute_Type;
struct Attribute_Element;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DISTANCE_DIFF	(10.0f)					// maya�ƊJ�����̋����̍�
#define ATTRIBUTE_NUM	(3)						// �����̐�
#define NO_VECTOR3		{0.0f,0.0f,0.0f}		// 3d�x�N�^�[��0������
#define NO_COLOR		{0.0f,0.0f,0.0f,0.0f}	// �J���[��0������

//*****************************************************************************
// �񋓑�
//*****************************************************************************
enum Object_Type {	//�I�u�W�F�N�g�^�C�v
	character,
	ground,
	destructible,
	inviolability
};

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Base_Object {
private:
	D3DXVECTOR3				m_Pos;						// �|���S���̍��W
	D3DXVECTOR3				m_OldPos;					// 1�t���[���O�̍��W
	D3DXVECTOR3				m_Rot;						// �|���S���̌���(��])
	D3DXVECTOR3				m_Scl;						// �|���S���̑傫��(�X�P�[��)
	D3DXVECTOR3				m_Vel;						// ���x
	D3DXCOLOR				m_Color;					// �|���S���̃J���[
	D3DXMATRIX				m_MtxWorld;					// ���[���h�}�g���b�N�X
	MATERIAL				m_Material;					// �}�e���A��
	Object_Type				m_ObjType;					// �I�u�W�F�N�g�^�C�v
	std::vector<Collision*>	m_Collision;				// �����蔻��
	Base_Attribute*			m_Attribute[ATTRIBUTE_NUM];	// �󂯂�����
	Attribute_Type			m_AttType;					// ���g�̑���
	bool					m_Use;						// �g�p�t���O
public:
	Base_Object() = default;
	Base_Object(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, Object_Type obj_type, bool use);
	virtual ~Base_Object();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void IsDiscard(void);

	//�Q�b�^�[
	D3DXMATRIX* GetMtx(void);
	MATERIAL* GetMaterial(void);
	std::vector<Collision*>* GetColl(void);
	Collision* GetColl(int index);
	Base_Attribute* GetAttribute(int index);

	//���t�@�����X
	const D3DXVECTOR3& RefPos(void) const;
	const D3DXVECTOR3& RefOldPos(void) const;
	const D3DXVECTOR3& RefRot(void) const;
	const D3DXVECTOR3& RefScl(void) const;
	const D3DXVECTOR3& RefVel(void) const;
	const D3DXCOLOR& RefColor(void) const;
	const Object_Type& RefObjType(void) const;
	const Attribute_Type& RefAttType(void) const;
	const bool& RefUse(void) const;

	//�Z�b�^�[
	void SetPos(D3DXVECTOR3 pos);
	void SetOldPos(void);
	void SetRot(D3DXVECTOR3 rot);
	void SetScl(D3DXVECTOR3 scl);
	void SetVel(D3DXVECTOR3 vel);
	void SetColor(D3DXCOLOR color);
	void SetUse(bool use);
	void SetColl(Collision* coll);
	void SetColl(int index);
	void SetAttribute(Base_Attribute* attribute, Attribute_Type att_type);
	void SetAttType(Attribute_Type att_type);

	
};

#endif // !_BASE_OBJECT_H_