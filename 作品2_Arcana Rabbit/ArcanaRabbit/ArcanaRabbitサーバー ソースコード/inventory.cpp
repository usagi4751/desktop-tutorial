#include "inventory.h"
#include "item.h"
#include "material.h"
#include "input.h"
#include "DictionaryItem.h"
#include "ItemDataBase.h"
#include "player.h"
#include "manager.h"
#include "dropitem.h"
Item Inventory::m_itemlist[]{};
Item Inventory::m_hand{};
bool Inventory::m_openflug{};
float Inventory::m_posY{};
float Inventory::m_size{};
int Inventory::m_haveitem{};
//�A�C�e���X���b�g�Əꏊ�����������`�F�b�N
bool ItemRightRlace(int num, SetSlot slot) {
	if (num == 32 && slot == Head)
	{
		return true;
	}
	if (num == 33 && slot == Chest)
	{
		return true;
	}
	if (num == 34 && slot == LEGGINGS)
	{
		return true;
	}
	if (num == 35 && slot == BOOTS)
	{
		return true;
	}
	return false;
}


int Inventory::Getitemno(XMFLOAT2 mousepos)
{
	float Depth = 0.5f;
	float wind = 768.0f * m_size;


	float ic = 80.0f * m_size;//�Z���̃T�C�Y
	float sukima = 6.0f * m_size;//�Z�����m�̌���
	float iclen = ic + sukima;//�`�掞�̊Ԋu
	float kote = ic * 0.5f + sukima * 0.5f;//�^�񒆂̌��ԗp
	float hoiver = 120.0f * m_size;//�z�b�g�o�[�Œ�ړ�

	//�����A�C�R���p
	float soubiic = ic * 1.3f;//�A�C�R���T�C�Y
	float soubiver = -180.0f * m_size;//�����Œ�ړ�
	float soubisukima = 40.0f * m_size;//�T�C�Y
	float soubilen = soubisukima + soubiic;//�Ԋu
	float soubikote = soubiic * 0.5f + soubisukima * 0.5f;//�^�񒆂̌��ԗp
	{
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (960 - (float)i * iclen - kote - ic * 0.5f < mousepos.x && 960 - (float)i * iclen - kote + ic * 0.5f > mousepos.x &&
					540 + (float)j * iclen - ic * 0.5f < mousepos.y && 540 + (float)j * iclen + ic * 0.5f > mousepos.y)
				{
					return 27 - i - j * 8;
				}
				if (960 + (float)i * iclen + kote - ic * 0.5f < mousepos.x && 960 + (float)i * iclen + kote + ic * 0.5f > mousepos.x &&
					540 + (float)j * iclen - ic * 0.5f < mousepos.y && 540 + (float)j * iclen + ic * 0.5f > mousepos.y)
				{
					return 28 + i - j * 8;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (960 - (float)i * iclen - kote - ic * 0.5f < mousepos.x &&
				960 - (float)i * iclen - kote + ic * 0.5f > mousepos.x &&
				540 + (float)2 * iclen + hoiver - ic * 0.5f < mousepos.y &&
				540 + (float)2 * iclen + hoiver + ic * 0.5f > mousepos.y
				)
			{
				return 3 - i;
			}
			if (960 + (float)i * iclen + kote - ic * 0.5f < mousepos.x &&
				960 + (float)i * iclen + kote + ic * 0.5f > mousepos.x &&
				540 + (float)2 * iclen + hoiver - ic * 0.5f < mousepos.y &&
				540 + (float)2 * iclen + hoiver + ic * 0.5f > mousepos.y
				)
			{
				return 4 + i;
			}

		}
		for (int i = 0; i < 2; i++)
		{
			if (960 - (float)i * soubilen - soubikote - soubiic * 0.5f < mousepos.x &&
				960 - (float)i * soubilen - soubikote + soubiic * 0.5f > mousepos.x &&
				540 + soubiver - soubiic * 0.5f < mousepos.y &&
				540 + soubiver + soubiic * 0.5f > mousepos.y)
			{
				return 33 - i;
			}
			if (960 + (float)i * soubilen + soubikote - soubiic * 0.5f < mousepos.x &&
				960 + (float)i * soubilen + soubikote + soubiic * 0.5f > mousepos.x &&
				540 + soubiver - soubiic * 0.5f < mousepos.y &&
				540 + soubiver + soubiic * 0.5f > mousepos.y)
			{
				return 34 + i;
			}

		}

	}
	return -1;
}
void Inventory::Init()
{
	for (int i = 0; i < 36; i++)
	{
		m_itemlist[i].m_ItemNo = -1;
	}
	m_itemlist[0].m_skillNo = 0;
	m_itemlist[0].m_ItemNo = 1;
	m_itemlist[0].m_ItemNum = 1;
	m_itemlist[0].m_damage = 2;
	m_itemlist[0].m_maxhelth = 0;
	m_itemlist[0].m_def = 0;
	m_itemlist[0].movespeed = 0;
	m_itemlist[0].m_attackspeed = 0;


	m_hand.m_ItemNo = -1;
	m_hand.m_skillNo = -1;
	m_hand.m_ItemNum = 0;
}
void Inventory::Update()
{
	float wind = 768.0f * m_size;
	m_size = 1.0f;
	for (int i = 0; i < 36; i++)
	{
		if (m_itemlist[i].m_skillCD > 0)
		{
			m_itemlist[i].m_skillCD--;
		}
	}
	//�A�C�e���̈ړ�����
	if (m_openflug == true)
	{
		Input::SetMouseDraw(true);
		int itemno = Getitemno(Input::GetMousePos());
		if (itemno >= 0 && itemno < 32)
		{
			if (Input::IsMouseLeftTriggered())
			{
				//�C���x���g���ɃA�C�e���������ĂȂ����J�[�\�����A�C�e���������Ă���
				if (m_itemlist[itemno].m_ItemNo < 0 && m_hand.m_ItemNo >= 0)
				{
					m_itemlist[itemno] = m_hand;
					m_hand.m_ItemNo = -1;
				}
				//�C���x���g���ɃA�C�e�������肩�J�[�\�����A�C�e���������Ă��ꍇ
				else if (m_itemlist[itemno].m_ItemNo >= 0 && m_hand.m_ItemNo >= 0)
				{
					//�����A�C�e���킾������ő�X�^�b�N���܂ŉ��Z����
					if (m_itemlist[itemno].m_ItemNo == m_hand.m_ItemNo)
					{
						if (m_itemlist[itemno].m_ItemNum < DictionaryItem::GetItem(m_itemlist[itemno].m_ItemNo)->GetMaxStack())
						{
							m_itemlist[itemno].m_ItemNum += m_hand.m_ItemNum;
							m_hand.m_ItemNum = 0;
							//�ő吔�𒴂�����hand�ɖ߂�
							if (m_itemlist[itemno].m_ItemNum > DictionaryItem::GetItem(m_itemlist[itemno].m_ItemNo)->GetMaxStack())
							{
								m_hand.m_ItemNum = m_itemlist[itemno].m_ItemNum - DictionaryItem::GetItem(m_itemlist[itemno].m_ItemNo)->GetMaxStack();
								m_itemlist[itemno].m_ItemNum -= m_hand.m_ItemNum;
							}
							if (m_hand.m_ItemNum <= 0)
							{
								m_hand.m_ItemNo = -1;
							}
						}
					}
					else
					{
						Item swap = m_itemlist[itemno];
						m_itemlist[itemno] = m_hand;
						m_hand = swap;
					}

				}
				//�C���x���g���ɃA�C�e��������J�[�\�����A�C�e���������ĂȂ������ꍇ
				else if (m_itemlist[itemno].m_ItemNo >= 0 && m_hand.m_ItemNo < 0)
				{
					m_hand = m_itemlist[itemno];
					m_itemlist[itemno].m_ItemNo = -1;
				}


			}
			if (DictionaryItem::GetItem(m_itemlist[Getitemno(Input::GetMousePos())].m_ItemNo) != nullptr)
			{
				DictionaryItem::GetItem(m_itemlist[Getitemno(Input::GetMousePos())].m_ItemNo)->Draw(m_itemlist[Getitemno(Input::GetMousePos())]);
			}
		}

		//�����̌����Ȃ�
		if (itemno >= 32 && itemno < 36)
		{
			if (Input::IsMouseLeftTriggered())
			{
				//�C���x���g���ɃA�C�e���������ĂȂ����J�[�\�����A�C�e���������Ă���
				if (m_itemlist[itemno].m_ItemNo < 0 && m_hand.m_ItemNo >= 0 && ItemRightRlace(itemno, DictionaryItem::GetItem(m_hand.m_ItemNo)->GetSlot()))
				{
					m_itemlist[itemno] = m_hand;
					m_hand.m_ItemNo = -1;
					m_hand.m_maxhelth = 0;
					m_hand.m_damage = 0;
					m_hand.movespeed = 0;
					m_hand.m_attackspeed = 0;
					m_hand.m_def = 0;
				}
				//�C���x���g���ɃA�C�e�������肩�J�[�\�����A�C�e���������Ă��ꍇ
				else if (m_itemlist[itemno].m_ItemNo >= 0 && m_hand.m_ItemNo >= 0 && ItemRightRlace(itemno, DictionaryItem::GetItem(m_hand.m_ItemNo)->GetSlot()))
				{
					//�����͍ő�X�^�b�N�����Œ�łP�Ȃ̂�swap�����ł���

					Item swap = m_itemlist[itemno];
					m_itemlist[itemno] = m_hand;
					m_hand = swap;

				}
				//�C���x���g���ɃA�C�e��������J�[�\�����A�C�e���������ĂȂ������ꍇ
				else if (m_itemlist[itemno].m_ItemNo >= 0 && m_hand.m_ItemNo < 0)
				{
					m_hand = m_itemlist[itemno];
					m_itemlist[itemno].m_ItemNo = -1;
					m_itemlist[itemno].m_maxhelth = 0;
					m_itemlist[itemno].m_damage = 0;
					m_itemlist[itemno].movespeed = 0;
					m_itemlist[itemno].m_attackspeed = 0;
					m_itemlist[itemno].m_def = 0;
				}


			}
			if (DictionaryItem::GetItem(m_itemlist[Getitemno(Input::GetMousePos())].m_ItemNo) != nullptr)
			{
				DictionaryItem::GetItem(m_itemlist[Getitemno(Input::GetMousePos())].m_ItemNo)->Draw(m_itemlist[Getitemno(Input::GetMousePos())]);
			}
		}

		if (Input::IsMouseLeftTriggered() && (Input::GetMousePos().x < 960 - wind * 0.5f || Input::GetMousePos().x > 960 + wind * 0.5f ||
			Input::GetMousePos().y < 540 - wind * 0.5f || Input::GetMousePos().y > 540 + wind * 0.5f) && m_hand.m_ItemNo >= 0)
		{
			Dropitem* item = Manager::GetScene()->AddObject<Dropitem>(1);
			Player* player = Manager::GetScene()->GetGameObject<Player>();
			item->SetPosition(*player->GetPosition());
			item->Setitem(m_hand);
			m_hand.m_ItemNo = -1;
			m_hand.m_ItemNum = 0;
			m_hand.m_skillNo = -1;
			item->SetDroptime(150);
		}
	}
	else { Input::SetMouseDraw(false); }
	
}

void Inventory::DrawRect()
{
	float Depth = 0.5f;
	float wind = 768.0f * m_size;


	float ic = 80.0f * m_size;//�Z���̃T�C�Y
	float sukima = 6.0f * m_size;//�Z�����m�̌���
	float iclen = ic + sukima;//�`�掞�̊Ԋu
	float kote = ic * 0.5f + sukima * 0.5f;//�^�񒆂̌��ԗp
	float hoiver = 120.0f * m_size;//�z�b�g�o�[�Œ�ړ�

	//�����A�C�R���p
	float soubiic = ic * 1.3f;//�A�C�R���T�C�Y
	float soubiver = -180.0f * m_size;//�����Œ�ړ�
	float soubisukima = 40.0f * m_size;//�T�C�Y
	float soubilen = soubisukima + soubiic;//�Ԋu
	float soubikote = soubiic * 0.5f + soubisukima * 0.5f;//�^�񒆂̌��ԗp


	//�z�b�g�o�[�`��
	//Draw2d::SetUI(GetImage().m_UI_image4, { 1.0f,1.0f,1.0f,1.0f }, { 960 - (float)(3 - m_haveitem) * ic - ic * 0.5f,1080 - ic * 0.5f }, { ic,ic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth - 0.013f);
	for (int i = 0; i < 4; i++)
	{
		//Draw2d::SetUI(GetImage().m_UI_image2, { 1.0f,1.0f,1.0f,1.0f }, { 960 - (float)i * ic - ic * 0.5f,1080 - ic * 0.5f }, { ic,ic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth - 0.04f);
		//Draw2d::SetUI(GetImage().m_UI_image2, { 1.0f,1.0f,1.0f,1.0f }, { 960 + (float)i * ic + ic * 0.5f,1080 - ic * 0.5f }, { ic,ic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth - 0.04f);
	}
	//�A�C�e���`��
	for (int i = 0; i < 4; i++)
	{
		if (DictionaryItem::GetItem(m_itemlist[3 - i].m_ItemNo) != nullptr)
		{
			DictionaryItem::GetItem(m_itemlist[3 - i].m_ItemNo)->DrawIcon({ 960 - (float)i * ic - ic * 0.5f,1080 - ic * 0.5f }, ic, Depth -0.015f, m_itemlist[3 - i]);
			if (m_itemlist[3 - i].m_ItemNum > 1)
			{
				//Draw2d::SetText(std::to_string(m_itemlist[3 - i].m_ItemNum), { 
					//960 - (float)i * ic - ic * 0.5f - ic * 0.4f
				////	,1080 - ic * 0.5f ,
					//960 - (float)i * iclen - kote + ic * 2.0f,
					//1080 - ic * 0.5f + ic * 2.0f }, ic * 0.3f, { 1.0f,1.0f ,1.0f ,1.0f }, Depth - 0.014);
			}
		}
		if (DictionaryItem::GetItem(m_itemlist[4 + i].m_ItemNo) != nullptr)
		{
			DictionaryItem::GetItem(m_itemlist[4 + i].m_ItemNo)->DrawIcon({ 960 + (float)i * ic + ic * 0.5f,1080 - ic * 0.5f }, ic, Depth - 0.015f, m_itemlist[4 + i]);
			if (m_itemlist[4 + i].m_ItemNum > 1)
			{
				//Draw2d::SetText(std::to_string(m_itemlist[4 + i].m_ItemNum), { 
				//	 960 + (float)i * ic + ic * 0.5f - ic * 0.4f,
				//	1080 - ic * 0.5f ,
				//	 960 + (float)i * ic + ic * 0.5f + ic * 2.0f,
				//	1080 - ic * 0.5f + ic * 2.0f }, ic * 0.3f, { 1.0f,1.0f ,1.0f ,1.0f }, Depth - 0.014);
			}
		}
	}

	if (m_openflug == true)
	{
		//Draw2d::SetUI(GetImage().m_UI_image3, { 1.0f,1.0f,1.0f,0.5f }, { 960,540 }, {1920,1080 }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth - 0.01f);
		//================================
		//�C���x���g���̔w�i
		//================================
		{
			//Draw2d::SetUI(GetImage().m_UI_image1, { 1.0f,1.0f,1.0f,1.0f }, { 960,540 }, { wind,wind }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth);
			//�Z���̕`��
			{
				for (int j = 0; j < 3; j++)
				{
					for (int i = 0; i < 4; i++)
					{
						//Draw2d::SetUI(GetImage().m_UI_image2, { 1.0f,1.0f,1.0f,1.0f }, { 960 - (float)i * iclen - kote,540 + (float)j * iclen }, { ic,ic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth + 0.01);
						//Draw2d::SetUI(GetImage().m_UI_image2, { 1.0f,1.0f,1.0f,1.0f }, { 960 + (float)i * iclen + kote,540 + (float)j * iclen }, { ic,ic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth + 0.01);
					}
				}
				for (int i = 0; i < 4; i++)
				{
					//Draw2d::SetUI(GetImage().m_UI_image2, { 1.0f,1.0f,1.0f,1.0f }, { 960 - (float)i * iclen - kote,540 + (float)2 * iclen + hoiver }, { ic,ic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth + 0.01);
					//Draw2d::SetUI(GetImage().m_UI_image2, { 1.0f,1.0f,1.0f,1.0f }, { 960 + (float)i * iclen + kote,540 + (float)2 * iclen + hoiver }, { ic,ic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth + 0.01);
				}
				for (int i = 0; i < 2; i++)
				{
					//Draw2d::SetUI(GetImage().m_UI_image2, { 1.0f,1.0f,1.0f,1.0f }, { 960 - (float)i * soubilen - soubikote,540 + soubiver }, { soubiic,soubiic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth + 0.01);
					//Draw2d::SetUI(GetImage().m_UI_image2, { 1.0f,1.0f,1.0f,1.0f }, { 960 + (float)i * soubilen + soubikote,540 + soubiver }, { soubiic,soubiic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth + 0.01);
				}
			}
		}

		//�A�C�R���ɃJ�[�\���������Ă�Ƌ����\��
		{
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					if (960 - (float)i * iclen - kote - ic * 0.5f < Input::GetMousePos().x && 960 - (float)i * iclen - kote + ic * 0.5f > Input::GetMousePos().x &&
						540 + (float)j * iclen - ic * 0.5f < Input::GetMousePos().y && 540 + (float)j * iclen + ic * 0.5f > Input::GetMousePos().y)
					{
						//Draw2d::SetUI(GetImage().m_UI_image2, { 0.0f,1.0f,0.0f,1.0f }, { 960 - (float)i * iclen - kote,540 + (float)j * iclen }, { ic,ic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth + 0.1);
					}
					if (960 + (float)i * iclen + kote - ic * 0.5f < Input::GetMousePos().x && 960 + (float)i * iclen + kote + ic * 0.5f > Input::GetMousePos().x &&
						540 + (float)j * iclen - ic * 0.5f < Input::GetMousePos().y && 540 + (float)j * iclen + ic * 0.5f > Input::GetMousePos().y)
					{
						//Draw2d::SetUI(GetImage().m_UI_image2, { 0.0f,1.0f,0.0f,1.0f }, { 960 + (float)i * iclen + kote,540 + (float)j * iclen }, { ic,ic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth + 0.1);
					}
				}
			}
			for (int i = 0; i < 4; i++)
			{
				if (960 - (float)i * iclen - kote - ic * 0.5f < Input::GetMousePos().x &&
					960 - (float)i * iclen - kote + ic * 0.5f > Input::GetMousePos().x &&
					540 + (float)2 * iclen + hoiver - ic * 0.5f < Input::GetMousePos().y &&
					540 + (float)2 * iclen + hoiver + ic * 0.5f > Input::GetMousePos().y
					)
				{
					//Draw2d::SetUI(GetImage().m_UI_image2, { 0.0f,1.0f,0.0f,1.0f }, { 960 - (float)i * iclen - kote,540 + (float)2 * iclen + hoiver }, { ic,ic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth + 0.01);
				}
				if (960 + (float)i * iclen + kote - ic * 0.5f < Input::GetMousePos().x &&
					960 + (float)i * iclen + kote + ic * 0.5f > Input::GetMousePos().x &&
					540 + (float)2 * iclen + hoiver - ic * 0.5f < Input::GetMousePos().y &&
					540 + (float)2 * iclen + hoiver + ic * 0.5f > Input::GetMousePos().y
					)
				{
					//Draw2d::SetUI(GetImage().m_UI_image2, { 0.0f,1.0f,0.0f,1.0f }, { 960 + (float)i * iclen + kote,540 + (float)2 * iclen + hoiver }, { ic,ic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth + 0.01);
				}

			}
			for (int i = 0; i < 2; i++)
			{
				if (960 - (float)i * soubilen - soubikote - soubiic * 0.5f < Input::GetMousePos().x &&
					960 - (float)i * soubilen - soubikote + soubiic * 0.5f > Input::GetMousePos().x &&
					540 + soubiver - soubiic * 0.5f < Input::GetMousePos().y &&
					540 + soubiver + soubiic * 0.5f > Input::GetMousePos().y)
				{
					//Draw2d::SetUI(GetImage().m_UI_image2, { 0.0f,1.0f,0.0f,1.0f }, { 960 - (float)i * soubilen - soubikote,540 + soubiver }, { soubiic,soubiic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth + 0.01);
				}
				if (960 + (float)i * soubilen + soubikote - soubiic * 0.5f < Input::GetMousePos().x &&
					960 + (float)i * soubilen + soubikote + soubiic * 0.5f > Input::GetMousePos().x &&
					540 + soubiver - soubiic * 0.5f < Input::GetMousePos().y &&
					540 + soubiver + soubiic * 0.5f > Input::GetMousePos().y)
				{
					//Draw2d::SetUI(GetImage().m_UI_image2, { 0.0f,1.0f,0.0f,1.0f }, { 960 + (float)i * soubilen + soubikote,540 + soubiver }, { soubiic,soubiic }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth + 0.01);
				}

			}

		}

		//==========================
		// �A�C�e���\��
		//==========================

		//===========================
		//�Z���̏ꏊ�ɃA�C�e����`��
		//===========================
		{
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					if (DictionaryItem::GetItem(m_itemlist[27 - i - j * 8].m_ItemNo) != nullptr)
					{
						DictionaryItem::GetItem(m_itemlist[27 - i - j * 8].m_ItemNo)->DrawIcon({ 960 - (float)i * iclen - kote,540 + (float)j * iclen }, ic, Depth + 0.11f, m_itemlist[27 - i - j * 8]);
						if (m_itemlist[27 - i - j * 8].m_ItemNum > 1)
						{
							//Draw2d::SetText(std::to_string(m_itemlist[27 - i - j * 8].m_ItemNum), { 960 - (float)i * iclen - kote - ic * 0.4f,540 + (float)j * iclen ,960 - (float)i * iclen - kote + ic * 2.0f,540 + (float)j * iclen + ic * 2.0f }, ic * 0.3f, { 1.0f,1.0f ,1.0f ,1.0f }, Depth + 0.12f);
						}
					}
					if (DictionaryItem::GetItem(m_itemlist[28 + i - j * 8].m_ItemNo) != nullptr)
					{
						DictionaryItem::GetItem(m_itemlist[28 + i - j * 8].m_ItemNo)->DrawIcon({ 960 + (float)i * iclen + kote,540 + (float)j * iclen }, ic, Depth + 0.11f, m_itemlist[28 + i - j * 8]);
						if (m_itemlist[28 + i - j * 8].m_ItemNum > 1)
						{
							//Draw2d::SetText(std::to_string(m_itemlist[28 + i - j * 8].m_ItemNum), { 960 + (float)i * iclen + kote - ic * 0.4f,540 + (float)j * iclen ,960 + (float)i * iclen + kote + ic * 2.0f,540 + (float)j * iclen + ic * 2.0f }, ic * 0.3f, { 1.0f,1.0f ,1.0f ,1.0f }, Depth + 0.12f);
						}
					}

				}
			}
			for (int i = 0; i < 4; i++)
			{
				if (DictionaryItem::GetItem(m_itemlist[3 - i].m_ItemNo) != nullptr)
				{
					DictionaryItem::GetItem(m_itemlist[3 - i].m_ItemNo)->DrawIcon({ 960 - (float)i * iclen - kote,540 + (float)2 * iclen + hoiver }, ic, Depth + 0.11f, m_itemlist[3 - i]);
					if (m_itemlist[3 - i].m_ItemNum > 1)
					{
						//Draw2d::SetText(std::to_string(m_itemlist[3 - i].m_ItemNum), { 960 - (float)i * iclen - kote - ic * 0.4f,540 + (float)2 * iclen + hoiver ,960 - (float)i * iclen - kote + ic * 2.0f,540 + (float)2 * iclen + hoiver + ic * 2.0f }, ic * 0.3f, { 1.0f,1.0f ,1.0f ,1.0f }, Depth + 0.12f);
					}
				}
				if (DictionaryItem::GetItem(m_itemlist[4 + i].m_ItemNo) != nullptr)
				{
					DictionaryItem::GetItem(m_itemlist[4 + i].m_ItemNo)->DrawIcon({ 960 + (float)i * iclen + kote,540 + (float)2 * iclen + hoiver }, ic, Depth + 0.11f, m_itemlist[4 + i]);
					if (m_itemlist[4 + i].m_ItemNum > 1)
					{
						//Draw2d::SetText(std::to_string(m_itemlist[4 + i].m_ItemNum), { 960 + (float)i * iclen + kote - ic * 0.4f,540 + (float)2 * iclen + hoiver ,960 + (float)i * iclen + kote + ic * 2.0f,540 + (float)2 * iclen + hoiver + ic * 2.0f }, ic * 0.3f, { 1.0f,1.0f ,1.0f ,1.0f }, Depth + 0.12f);
					}
				}
			}
			for (int i = 0; i < 2; i++)
			{
				if (DictionaryItem::GetItem(m_itemlist[33 - i].m_ItemNo) != nullptr)
				{
					DictionaryItem::GetItem(m_itemlist[33 - i].m_ItemNo)->DrawIcon({ 960 - (float)i * soubilen - soubikote,540 + soubiver }, soubiic, Depth + 0.11f, m_itemlist[33 - i]);
				}
				if (DictionaryItem::GetItem(m_itemlist[34 + i].m_ItemNo) != nullptr)
				{
					DictionaryItem::GetItem(m_itemlist[34 + i].m_ItemNo)->DrawIcon({ 960 + (float)i * soubilen + soubikote,540 + soubiver }, soubiic, Depth + 0.11f, m_itemlist[34 + i]);
				}
			}
		}

		//===========================
		// ��ɃA�C�e���������Ă���A�C�R���\��
		//===========================
		if (DictionaryItem::GetItem(m_hand.m_ItemNo) != nullptr)
		{
			DictionaryItem::GetItem(m_hand.m_ItemNo)->DrawIcon(Input::GetMousePos(), ic, Depth + 0.11f, m_hand);
			if (m_hand.m_ItemNum > 1)
			{
				//Draw2d::SetText(std::to_string(m_hand.m_ItemNum), { Input::GetMousePos().x - ic * 0.4f,Input::GetMousePos().y ,Input::GetMousePos().x + ic * 2.0f,Input::GetMousePos().y + ic * 2.0f }, ic * 0.3f, { 1.0f,1.0f ,1.0f ,1.0f }, Depth + 0.12f);
			}
		}



		//==============================
		// �A�C�e���̐����`��
		//==============================
		if (Getitemno(Input::GetMousePos()) >= 0)
		{
			if (DictionaryItem::GetItem(m_itemlist[Getitemno(Input::GetMousePos())].m_ItemNo) != nullptr)
			{
				DictionaryItem::GetItem(m_itemlist[Getitemno(Input::GetMousePos())].m_ItemNo)->Draw(m_itemlist[Getitemno(Input::GetMousePos())]);
			}
		}

		//==============================
		// �A�C�e�������̃X�e�[�^�X�̕\��
		//==============================
		{
			//Draw2d::SetUI(GetImage().m_UI_image3, { 1.0f,1.0f,1.0f,1.0f }, { 1600,250 }, { 500,400 }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth);
			std::string drawstutus;
			Status handstatus = {};
			int itemno = m_itemlist[m_haveitem].m_ItemNo;
			if (DictionaryItem::GetItem(itemno) != nullptr)
			{
				handstatus = DictionaryItem::GetItem(itemno)->GetStatus(m_itemlist[m_haveitem]);
			}
			drawstutus += "�ő�̗� " + std::to_string(DEFAULTHELTH + m_itemlist[32].m_maxhelth + m_itemlist[33].m_maxhelth + m_itemlist[34].m_maxhelth + m_itemlist[35].m_maxhelth + handstatus.MaxHelth) + "\n";
			drawstutus += "�_���[�W " + std::to_string(DEFAULTDAMAGE + m_itemlist[32].m_damage + m_itemlist[33].m_damage + m_itemlist[34].m_damage + m_itemlist[35].m_damage + handstatus.Damage) + "\n";
			drawstutus += "�ړ����x " + std::to_string(DEFAULTMOVESPEED + m_itemlist[32].movespeed + m_itemlist[33].movespeed + m_itemlist[34].movespeed + m_itemlist[35].movespeed + handstatus.MoveSpeed) + "\n";
			drawstutus += "�U�����x " + std::to_string(DEFAULTATTACKSPEED + m_itemlist[32].m_attackspeed + m_itemlist[33].m_attackspeed + m_itemlist[34].m_attackspeed + m_itemlist[35].m_attackspeed + handstatus.AttackSpeed) + "\n";
			drawstutus += "�h��� " + std::to_string(DEFAULTDEF + m_itemlist[32].m_def + m_itemlist[33].m_def + m_itemlist[34].m_def + m_itemlist[35].m_def + handstatus.Def);
			//Draw2d::SetText(drawstutus, { 1375,100,1850,650 }, 24, { 0.5f,1.0f ,0.5f ,1.0f }, Depth + 0.01f);
		}
	}
	
	
	
}

Status Inventory::GetStayus()
{
	Status retstatus;
	Status handstatus = {};
	int itemno =  m_itemlist[m_haveitem].m_ItemNo;
	if (DictionaryItem::GetItem(itemno) != nullptr)
	{
		handstatus = DictionaryItem::GetItem(itemno)->GetStatus(m_itemlist[m_haveitem]);
	}
	retstatus.MaxHelth = DEFAULTHELTH + m_itemlist[32].m_maxhelth + m_itemlist[33].m_maxhelth + m_itemlist[34].m_maxhelth + m_itemlist[35].m_maxhelth + handstatus.MaxHelth;
	retstatus.AttackSpeed = DEFAULTATTACKSPEED + m_itemlist[32].m_attackspeed + m_itemlist[33].m_attackspeed + m_itemlist[34].m_attackspeed + m_itemlist[35].m_attackspeed + handstatus.AttackSpeed;
	retstatus.Damage = DEFAULTDAMAGE + m_itemlist[32].m_damage + m_itemlist[33].m_damage + m_itemlist[34].m_damage + m_itemlist[35].m_damage + handstatus.Damage;
	retstatus.Def = DEFAULTDEF + m_itemlist[32].m_def + m_itemlist[33].m_def + m_itemlist[34].m_def + m_itemlist[35].m_def + handstatus.Def;
	retstatus.MoveSpeed = DEFAULTMOVESPEED + m_itemlist[32].movespeed + m_itemlist[33].movespeed + m_itemlist[34].movespeed + m_itemlist[35].movespeed + handstatus.MoveSpeed;

	return retstatus;
}

void Inventory::Attack()
{
	if (m_itemlist[m_haveitem].m_ItemNo >= 0)
	{
		DictionaryItem::GetItem(m_itemlist[m_haveitem].m_ItemNo)->Attack(m_itemlist[m_haveitem]);
	}

}

void Inventory::Use()
{
	if (m_itemlist[m_haveitem].m_ItemNo >= 0 && m_itemlist[m_haveitem].m_skillCD <= 0)
	{
		DictionaryItem::GetItem(m_itemlist[m_haveitem].m_ItemNo)->Use(&m_itemlist[m_haveitem]);
	}
}

void Inventory::Getitem(Item getitem)
{
	for (int i = 0; i < 32; i++)
	{
		if (m_itemlist[i].m_ItemNo >= 0 && m_itemlist[i].m_ItemNo == getitem.m_ItemNo && m_itemlist[i].m_ItemNum < DictionaryItem::GetItem(m_itemlist[i].m_ItemNo)->GetMaxStack())
		{
			m_itemlist[i].m_ItemNum += getitem.m_ItemNum;
			getitem.m_ItemNum = 0;
			getitem.m_ItemNo = -1;
			if (m_itemlist[i].m_ItemNum > DictionaryItem::GetItem(m_itemlist[i].m_ItemNo)->GetMaxStack())
			{
				getitem.m_ItemNum = m_itemlist[i].m_ItemNum - DictionaryItem::GetItem(m_itemlist[i].m_ItemNo)->GetMaxStack();
				getitem.m_ItemNo = m_itemlist[i].m_ItemNo;
				m_itemlist[i].m_ItemNum = DictionaryItem::GetItem(m_itemlist[i].m_ItemNo)->GetMaxStack();
				if (getitem.m_ItemNum > 0)
				{
					Getitem(getitem);
				}
			}
		}
	}
	if (getitem.m_ItemNum > 0)
	{
		for (int i = 0; i < 32; i++)
		{
			if (m_itemlist[i].m_ItemNo < 0)
			{
				m_itemlist[i] = getitem;
				getitem.m_ItemNo = -1;
				break;
			}
		}
	}
	if (getitem.m_ItemNo > -1)
	{
		Dropitem* item =  Manager::GetScene()->AddObject<Dropitem>(1);
		Player* player = Manager::GetScene()->GetGameObject<Player>();
		item->SetPosition(*player->GetPosition());
		item->Setitem(getitem);
		item->SetDroptime(150);
	}
}
