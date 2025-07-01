#pragma once
#include "main.h"
#include "base_object.h"
class DrawDmage:public Base_Object
{
private:
	int m_Life = 60;
	int m_Damage;
	float m_Length;
public:
	//===========================
	// �_���[�W�\�L
	// int damage		�\���������_���[�W
	// D3DXVECTOR3 pos	�\��������W
	// D3DXCOLOR coler	�\������Ƃ��̐F(��������Ȃ��Ɣ�)
	//===========================
	DrawDmage(int damage, D3DXVECTOR3 pos, D3DXCOLOR coler = DIK_COLER_WHITE);
	DrawDmage() = delete;
	~DrawDmage() = default;
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	float GetLength();//�v���C���[�Ƃ̋�����Ԃ�

};




