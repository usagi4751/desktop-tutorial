//=============================================================================
//
// �����蔻�菈�� [collision.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Base_Object;
class Collision
{
private:
	Base_Object* m_Target;
	D3DXVECTOR3	m_Pos;
	D3DXVECTOR3	m_Dis;
	float m_Circle;
public:
	Collision(void) = delete;
	Collision(Base_Object* Target, D3DXVECTOR3 Dis, float circle);
	~Collision(void) = default;

	//���t�@�����X
	const D3DXVECTOR3& RefCollPos(void);
	const float& RefCollCircle(void);

	//�Z�b�^�[
	void SetCollPos(void);
	void SetCollPos(D3DXVECTOR3 pos);
	void SetCircle(float circle);

	bool IsCollision(Collision* obj);
};
