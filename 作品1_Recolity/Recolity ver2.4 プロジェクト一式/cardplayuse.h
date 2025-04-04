#pragma once
#include "card_base.h"
#include "cardplaypdeckmanager.h"
#include <list>
#define CARD_SIZE (25)
class CardPlay_Use
{
private:
	std::list<GameCard*>	m_Yamafuda;//�R�D
	std::list<GameCard*>	m_Hand;//��D
	std::list<GameCard*>	m_Boti;//��n�J�[�h
public:
	CardPlay_Use() {};
	~CardPlay_Use() {};
	//�v���C�f�b�L�Ƃ̃����N
	void InitPlayUse(CardPlay_Manager* card) {
		for (int i = 0; i < CARD_DECKMAX; i++)
		{
			m_Yamafuda.push_back(card->GetCard(i));
		}
	
	}
	void Uninit() {
		m_Yamafuda.erase(m_Yamafuda.begin(), m_Yamafuda.end());
		m_Hand.erase(m_Hand.begin(), m_Hand.end());
		m_Boti.erase(m_Boti.begin(), m_Boti.end());
	}
	//�R�D����J�[�h������
	void CardDraw() {
		if ((int)m_Yamafuda.size() == 0)
		{
			CardReset();
		}
		int index = -1;
		if ((int)m_Yamafuda.size() > 0)
		{
			index = (int)(frand() * (float)m_Yamafuda.size());
			if (index > -1)
			{
				m_Hand.push_back(*std::next(m_Yamafuda.begin(), index));
				m_Yamafuda.erase(std::next(m_Yamafuda.begin(), index));
			}
		}
	}
	//��D�����n�Ɏ̂Ă�
	//no:�̂Ă�J�[�h�̃C�e���[�^�[
	void CardDiscard(int no) {
		if (no < m_Hand.size())
		{
			GameCard* n = *std::next(m_Hand.begin(), no);
			n->m_Card->Use(n->rank);
			m_Boti.push_back(*std::next(m_Hand.begin(), no));
			m_Hand.erase(std::next(m_Hand.begin(), no));

		}
	};

	//�R�D���Ȃ��Ȃ������n����R�D�ֈړ�
	//�����Update�ŕK����т�������
	void CardReset() {
		if (m_Yamafuda.size() <= 0)
		{
			for (int i = 0; i < m_Boti.size(); i++)
			{
				m_Yamafuda.push_back(*std::next(m_Boti.begin(), i));
			}
			m_Boti.clear();
		}
	
	}
	//�\������
	void Draw(int clect);
	//�f�o�b�N�p�̕\���R�D��D��n�S��������
	void DebugDraw(int clect) ;
	//�J�[�h�̃R�X�g�擾
	int CardDiscardCost(int no) {
		GameCard* n = *std::next(m_Hand.begin(), no);
		return (int)n->rank;
	}
	//�����Ă���J�[�h�������擾����
	int CardGetHandNum() { return (int)m_Hand.size(); };
};
