#pragma once
#include "main.h"
#include "carddatamanager.h"
#include "card_base.h"
#include "cardmenumanager.h"
class CardMenu_Manager;
class CardMenu_Get
{
private:
	CardMenu_Manager*	m_PCardMenu_Manager;//���j���[�}�l�[�W���̃|�C���^�[
	CardDataManager*	m_PCardDataManager;//�J�[�h�̃f�[�^�}�l�[�W���̃|�C���^�[
	GameCard			m_InCardData;//�����Ă����J�[�h�f�[�^
	GameCard			m_PullData;//����ł�f�[�^
	bool				m_SameCard;//�����J�[�h��2���ȏ�����Ă��邩�̃e�L�X�g���o�� 
public:
	CardMenu_Get(CardMenu_Manager* pmnager, CardDataManager* pdata);
	CardMenu_Get()=delete;
	~CardMenu_Get();
	void Update();
	void DrawUI();
	bool InData() {
		if (m_InCardData.m_Card != nullptr)
		{
			return true;
		}
		return false;
	};
	void GetCard(GameCard get) {
			m_InCardData = get;
	}
	//============================
	// �����J�[�h���f�b�L��2���ȏ�����Ă��邩���m���Ă����
	//============================
	bool Search(GameCard data);
};



