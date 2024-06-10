#pragma once

#include "main.h"
#include "card_bullet_single_fier.h"
#include "carddatamanager.h"
#include "card_base.h"
#include "cardplaypdeckmanager.h"
#include "input.h"
#include "dropcard.h"

#define DRAW_CARDPOS D3DXVECTOR2(300,540)
#define CardPLAYDrawPos_X (1150) //�J�[�h�\�����W�̎n�܂�̒n�_ X
#define CardPLAYDrawPos_Y (160) //�J�[�h�\�����W�̎n�܂�̒n�_ Y
#define CardPLAYDrawPos_CREVICE_X (170) //�J�[�h�����̌��� X
#define CardPLAYDrawPos_CREVICE_Y (250) //�J�[�h�����̌��� X
#define CRADPLAY_SIZE (27)//�J�[�h�\���̃T�C�Y
#define CRAD_SIZE (60)//�J�[�h�\���̃T�C�Y

#define CARD_DISCARDPOS_X (250)
#define CARD_DISCARDPOS_Y (850)
class DropCardManager;
class Card_GetCard
{
private:
	CardPlay_Manager* m_CardData;
	DropCardManager* _pDropcardmanager;
	GameCard m_InCardData;//�����Ă����J�[�h�f�[�^
	int m_swapdata;
	int getcd;//�J�[�h�擾������̂Ă����̃N�[���^�C��
	int		m_GetCardSound;//�T�E���h
	int		m_GetCardSound2;//�T�E���h
public:
	Card_GetCard() { m_InCardData.m_Card = nullptr; m_InCardData.rank = Card_Rank_One; };
	~Card_GetCard() {};
	void LinkData(CardPlay_Manager* card, DropCardManager* _drop);
	bool InData();
	void GetCard(GameCard get);
	void Uninit();
	void Update();
	void DrawUI();
	int Getgetcd() { return getcd; }
};