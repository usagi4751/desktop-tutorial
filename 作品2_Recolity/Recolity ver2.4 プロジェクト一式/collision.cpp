//=============================================================================
//
// �Փ˔��菈�� [collision.cpp]
// Author : 
//
//=============================================================================
#include "collision.h"
#include "base_object.h"
//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Collision::Collision(Base_Object* Target, D3DXVECTOR3 Dis, float circle)
	:m_Circle(circle), m_Dis(Dis),m_Target(Target)
{
}
//=============================================================================
// ���t�@�����X
//=============================================================================
const D3DXVECTOR3& Collision::RefCollPos(void)
{
	return m_Pos;
}
const float& Collision::RefCollCircle(void)
{
	return m_Circle;
}
//=============================================================================
// �Z�b�^�[
//=============================================================================
void Collision::SetCollPos(void)
{
	m_Pos = m_Target->RefPos() + m_Dis;
}
void Collision::SetCollPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}
void Collision::SetCircle(float circle)
{
	m_Circle = circle;
}
//=============================================================================
// �����蔻��
//=============================================================================
bool Collision::IsCollision(Collision* obj)
{
	//2�_�Ԃ̋�����2��
	D3DXVECTOR3 vec = (m_Pos - obj->m_Pos);
	float dis = D3DXVec3LengthSq(&vec);

	//2�̃I�u�W�F�N�g�̔��a�̘a
	float len = m_Circle * 0.5f + obj->m_Circle * 0.5f;

	//���a�̘a��������2��ȉ���������
	if (dis <= powf(len, 2))
		return true;
	return false;
}
