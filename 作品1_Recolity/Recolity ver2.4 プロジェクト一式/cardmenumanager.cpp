#pragma once
#include "cardmenumanager.h"
#include "carddatamanager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define InitCardRank Card_Rank_One //�J�[�h�̏��������N
#define CardDrawPos_X (300) //�J�[�h�\�����W�̎n�܂�̒n�_ X
#define CardDrawPos_Y (160) //�J�[�h�\�����W�̎n�܂�̒n�_ Y
#define CardDrawPos_CREVICE_X (150) //�J�[�h�����̌��� X
#define CardDrawPos_CREVICE_Y (250) //�J�[�h�����̌��� X
#define CRAD_SIZE (25)//�J�[�h�\���̃T�C�Y

void CardMenu_Manager::DrawCard() {
	for (int i = 0; i < CARD_DECKMAX; i++)
	{
		if (m_Card_Deck[i].m_Card != nullptr)
		{
			//=================================
			// �J�[�h��\���̎Q�Ƃ����l
			//=================================
			int no = m_Card_Deck[i].rank;
			//��ʕ\��
			m_Card_Deck[i].m_Card->DrawPreview(D3DXVECTOR2(CardDrawPos_X + (float)(i % 5) * CardDrawPos_CREVICE_X, (float)(CardDrawPos_Y + (int)((float)i / 5.0f) * CardDrawPos_CREVICE_Y)), CRAD_SIZE, (Card_Rank)no);
		}
	}

}
