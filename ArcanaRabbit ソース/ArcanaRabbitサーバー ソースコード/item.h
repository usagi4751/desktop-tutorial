#pragma once

class Item
{
public:
	int m_ItemNo = 0;//�A�C�e���̃i���o�[
	int m_ItemNum = 0;//�A�C�e���̌�
	float m_damage = 0;//�_���[�W
	float m_attackspeed = 0;//�U�����x
	float m_def = 0;//�h���
	float m_maxhelth = 0;//�ő�̗�
	float movespeed = 0;//�ړ����x
	int m_skillNo = -1;//�X�L���i���o�[
	int m_skillCD = 0;//�X�L���N�[���^�C��
	Item() {
	
	};
	virtual ~Item() {};
private:
	virtual void Init();
	virtual void Update();
	virtual Item GetItemData() { return *this; };
};

