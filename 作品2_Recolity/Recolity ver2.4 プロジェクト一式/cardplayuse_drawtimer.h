#pragma once
#define CARD_DRAW_TIME (15)//(f)
#define CARD_DRAW_TIME2 (300)//(f)
class CardPlay_Use_DrawTime
{
private:
	int m_CardDrawTimer = 0;//�J�[�h�h���[����܂ł̎���
public:
	CardPlay_Use_DrawTime() { m_CardDrawTimer = 0; };
	~CardPlay_Use_DrawTime() {};
	void Update() {
		m_CardDrawTimer > 0 ? m_CardDrawTimer-- : m_CardDrawTimer = 0;
	}
	//�^�C�}�[���擾����
	int GetDrawTime() { return m_CardDrawTimer; };
	//�^�C�}�[���Z�b�g����
	void SetDrawTime(int time) { m_CardDrawTimer = time; };
};

