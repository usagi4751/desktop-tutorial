#pragma once
#include "card_base.h"
#include "cardmenumanager.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CARD_DECKMAX (20)//�f�b�L�̍ő吔
#define CARD_DEFAULT_RANK (Card_Rank_One)
#define InitCardRank Card_Rank_One //�J�[�h�̏��������N

#define TabDrawPos_X (1100) //�J�[�h�\�����W�̎n�܂�̒n�_ X
#define TabDrawPos_Y (160) //�J�[�h�\�����W�̎n�܂�̒n�_ Y
#define TabDrawPos_CREVICE_X (170) //�J�[�h�����̌��� X
#define TabDrawPos_CREVICE_Y (250) //�J�[�h�����̌��� X
#define Tab_SIZE (27)//�J�[�h�\���̃T�C�Y
class CardPlay_Manager
{
private:
	GameCard m_Card_Deck[CARD_DECKMAX];
public:
	CardPlay_Manager() {
		for (int i = 0; i < CARD_DECKMAX; i++)
		{
			m_Card_Deck[i].rank = CARD_DEFAULT_RANK;
			m_Card_Deck[i].m_Card = nullptr;
		}
	};
	~CardPlay_Manager() {};
	void GetDeck(CardMenu_Manager* card) {
		for (int  i = 0; i < CARD_DECKMAX; i++) 
		{
			m_Card_Deck[i] = *card->GetDeckCard(i);
		}
	}
	void DrawCard(int no, D3DXVECTOR2 pos, float size) {
		if (no > -1 && no < CARD_DECKMAX)
		{
			m_Card_Deck[no].m_Card->DrawPreview(pos,size, m_Card_Deck[no].rank);
		}
	}
	void DrawCardText(int no,D2D1_RECT_F rect) {
		m_Card_Deck[no].m_Card->DrawTextPreview(rect, m_Card_Deck[no].rank);
	}
	void UnInit() {
	
	}
	void TabDraw();
	//�J�[�h�擾����
	void SetCard(int no, GameCard card) {
		m_Card_Deck[no].m_Card = nullptr;
		m_Card_Deck[no] = card;
	}
	GameCard* GetCard(int n) {
		return &m_Card_Deck[n];
	}


};