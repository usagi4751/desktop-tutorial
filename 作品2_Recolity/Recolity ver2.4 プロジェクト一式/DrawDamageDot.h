#pragma once
#include "main.h"
#include "base_object.h"
class DrawDmageDot
{
private:
	int m_Life = 0;
	float m_Damage;//�S�[���̃_���[�W
	float m_Nowdamage;//���݂̃_���[�W
	float m_Length;//�J�����Ƃ̋���
	D3DXVECTOR3 m_pos;
	D3DXCOLOR	m_coler;
public:
	//===========================
	// �_���[�W�\�L
	// D3DXCOLOR coler	�\������Ƃ��̐F
	//===========================
	DrawDmageDot();
	~DrawDmageDot() = default;
	void IsDamageDot(float damage);
	void Update(D3DXVECTOR3 pos) ;
	void Draw(void) ;
	float GetLength();//�v���C���[�Ƃ̋�����Ԃ�

};