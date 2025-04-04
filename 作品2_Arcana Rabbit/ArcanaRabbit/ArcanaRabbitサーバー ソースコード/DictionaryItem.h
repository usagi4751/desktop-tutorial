#pragma once
#include "main.h"
//�A�C�e���̎���
//�i���o�[���󂯎��Ɩ߂�l�Ō��ʂ�Ԃ�
class ItemDataBase;
class DictionaryItem
{
private:
	static std::vector<ItemDataBase*> m_Itemlist;
public:
	DictionaryItem() {};
	~DictionaryItem() {};
	static void UnInit();//UnInit�����Q�[���I�����ɂP�x�̂݌Ă�
	static void Init();//Init�����Q�[���J�n���ɂP�x�̂݌Ă�
	static ItemDataBase* GetItem(int index) {
		if (index > (int)m_Itemlist.size() - 1 || index < 0)
		{
			return nullptr;
		}
		return m_Itemlist[index];
	};

};


