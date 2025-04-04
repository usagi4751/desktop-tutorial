//=================================================
// �J�[�h�̑�{
// ��������J�[�h���ʂ��p�������Ďg��
//=================================================
#pragma once
#include "main.h"
enum Card_Rank
{
	Card_Rank_One = 1,
	Card_Rank_Twe ,
	Card_Rank_Three ,
};
enum Card_Type
{
	Card_Type_Fier = 1,	//��
	Card_Type_Water,	//��
	Card_Type_Wind,		//��
};
class Card_Base
{
protected:
public:
	Card_Base() {};
	~Card_Base() {};
	virtual void Use(int rank) = 0;//�g�������̌���
	virtual void DrawPreview(D3DXVECTOR2 pos, float size,Card_Rank Rank) = 0;//�J�[�h�̋�����I��ŕ\��
	virtual void DrawTextPreview( D2D1_RECT_F rect,  Card_Rank Rank) = 0;//�J�[�h�̌��ʐ���
};
//=============================
// �J�[�h�}�l�[�W�������\����
//=============================
typedef struct {
	Card_Base* m_Card;
	Card_Rank rank;
}GameCard;

