#pragma once
#include "main.h"
//アイテムの辞書
//ナンバーを受け取ると戻り値で効果を返す
class ItemDataBase;
class DictionaryItem
{
private:
	static std::vector<ItemDataBase*> m_Itemlist;
public:
	DictionaryItem() {};
	~DictionaryItem() {};
	static void UnInit();//UnInit処理ゲーム終了時に１度のみ呼ぶ
	static void Init();//Init処理ゲーム開始時に１度のみ呼ぶ
	static ItemDataBase* GetItem(int index) {
		if (index > (int)m_Itemlist.size() - 1 || index < 0)
		{
			return nullptr;
		}
		return m_Itemlist[index];
	};

};


