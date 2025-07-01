#pragma once
#include "main.h"
//シングルトン
//スキルの番号で呼び出して
//ゲーム開始時にスキルを生成する

class SkillDataBase;
class DictionarySkill
{
private:
	static std::vector<SkillDataBase*> m_Skilldata;
	
	DictionarySkill();
public:

	~DictionarySkill() {};
	static void UnInit();//UnInit処理ゲーム終了時に１度のみ呼ぶ
	static void Init();//Init処理ゲーム開始時に１度のみ呼ぶ
	static SkillDataBase* GetSkill(int index) {
		if (index > (int)m_Skilldata.size() - 1 || index < 0)
		{
			return nullptr;
		}
		return m_Skilldata[index]; 
	};


};

