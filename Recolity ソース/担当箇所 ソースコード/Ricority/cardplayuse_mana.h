#pragma once
#define CARD_MANA_MAX (6.0f)//max�l
#define CARD_MANA_REGEN (1.0f / 60.0f)//(f)
class CardPlay_Use_Mana
{
private:
	float m_CardMana = 0;//�}�i
public:
	CardPlay_Use_Mana() { m_CardMana = 0; };
	~CardPlay_Use_Mana() {};
	//�X�V����
	void Update() {
		//�}�i�̎�����
		m_CardMana < CARD_MANA_MAX ? m_CardMana+= CARD_MANA_REGEN : m_CardMana = CARD_MANA_MAX;
	}
	//���݂̃}�i�̗ʂ��擾����
	float GetMana() { return m_CardMana; };
	//�}�i������������
	void ReduceMana(float nu) { m_CardMana - nu < 0 ? m_CardMana = 0 : m_CardMana -= nu; };
	//�}�i�𑝉�������
	void IncreaseMana(float nu) { m_CardMana + nu > CARD_MANA_MAX ? m_CardMana = CARD_MANA_MAX : m_CardMana += nu; };
};
